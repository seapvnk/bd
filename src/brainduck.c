#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>




#define MSG_VERSION "brainduck - version 1.0.1"
#define MSG_HELP "\tUsage: ./brainduck <filename>|flag [-d]\n\t-d: show memory info\n\t-v: show version"

#define MEM_SIZE 30000

// helper functions
char *readf(char *filename) {
	// copy the content of a file to a string
  // return 

	FILE *source = fopen(filename, "r");
	char c, *string = malloc(1);
	int len = 1;

	// read file
	while ((c = fgetc(source)) != EOF) {
		string[len-1] = c;
		string = realloc(string, ++len);
	}

	// end of string
	string = realloc(string, len+1);
	string[len] = '\0';
	fclose(source);

	return string;
}

void memory_info(unsigned char *memory, int rightmost_cell, int pointer) {
   puts("\n\n       BRAINDUCK       \nAddress  Value  Pointer");
   for (int i = 0; i <= rightmost_cell; i++) {
     bool is_pointer = (i == pointer);
     printf("%7d  %5d  %s\n", i, memory[i], is_pointer? "  <-" : " ");
   }
}

// Loops
// definition: data structure responsible to take care of loops
typedef struct {
	int length;
	int *positions;
} Loops;

void loops_init(Loops *lp) {
	// start with length 0
	lp->length = 0;
}

int loops_last(Loops *lp) {
	// return the last position
	if (!lp->length) {
    exit(-1);
  }
	return lp->positions[lp->length - 1];
}

void loops_add(Loops *lp, int pc) {
	// add a new position to loop

	if (!lp->length) {
		lp->positions = malloc(sizeof(int));
		lp->positions[lp->length] = pc;
    lp->length++;
	} else {
		lp->length++;
		lp->positions = realloc(lp->positions, lp->length * sizeof(int));
		lp->positions[lp->length - 1] = pc;
	}
}

void loops_remove(Loops *lp, unsigned char cell, int *pc) {
	// remove the last loop position
  
	  // if data provided is 0 then end the loop
	  if (!cell) {
	  	lp->length--;
	  	lp->positions = realloc(lp->positions, lp->length * sizeof(int));
	  } else {
		  // set program counter back to the last loop
		  *pc = loops_last(lp);
	  }	
}

void loops_free(Loops *lp) {
	free(lp->positions);
	lp->length = 0;
}


// executing brainf*ck 
void bd_execute(char *program, bool debug) {
	// loops
  Loops loops;
	loops_init(&loops);
  
  // memory
	unsigned char memory[MEM_SIZE] = {0};
	unsigned int pointer = 0;
  int rightmost_cell  = 0;

	for (int i = 0; i < strlen(program); i++) {
		switch (program[i]) {
      // add or sub operation
			case '+': memory[pointer]++; break;
			case '-': memory[pointer]--; break;
      
      // move pointer
			case '>': { if (pointer < MEM_SIZE) pointer++; break; }
			case '<': if (pointer) pointer--; break;
      
      // flow control
			case '[': loops_add(&loops, i); break;
      case ']': loops_remove(&loops, memory[pointer], &i); break;

			// i/o
      case '.': putchar(memory[pointer]); break;
			case ',': memory[pointer] = getchar();
		}
   
    // update righmost position used in memory
    if (pointer > rightmost_cell) {
      rightmost_cell++;
    }

  }
  // free memory for loops
	loops_free(&loops);
  
  // debug memory usage at final of program
  if (debug) { 
    memory_info(memory, rightmost_cell, pointer);
  }
}

void terminate(const char* msg) {
  puts(msg);
  exit(0);
}

int main(int argc, char **argv) {
  bool debug = false;
  
  // end program without any brainfuck program input
	if (argc == 1) {
    terminate(MSG_HELP);
	} else if (argc == 2 && !(strcmp(argv[1], "-v"))) {
    terminate(MSG_VERSION);
  } else {
  // execute brainfuck  
    if (argc >= 3) {
      if (!strcmp(argv[2], "-d")) {
       debug = true;
      }
    }
    char *program = readf(argv[1]);
	  bd_execute(program, debug);
    free(program);
  }
	return 0;
}
