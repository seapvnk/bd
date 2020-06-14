#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

void meminfo(unsigned char *mem, int length, int ptr) {
   puts("\n\n       BRAINDUCK       \nAddress  Value  Pointer");
   for (int i = 0; i <= length; i++) {
     bool is_pointer = i == ptr;
     printf("%7d  %5d  %s\n", i, mem[i], is_pointer? "  <-" : " ");
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

void loops_push(Loops *lp, int pc) {
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

void loops_pop(Loops *lp, unsigned char cell, int *pc) {
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
	unsigned char mem[MEM_SIZE] = {0};
	unsigned int ptr = 0;
  int max_ptr = 0;

	for (int i = 0; i < strlen(program); i++) {
		switch (program[i]) {
      // add or sub operation
			case '+': mem[ptr]++; break;
			case '-': mem[ptr]--; break;
      
      // move pointer
			case '>': { if (ptr < MEM_SIZE) ptr++; break; }
			case '<': if (ptr) ptr--; break;
      
      // flow control
			case '[': loops_push(&loops, i); break;
      case ']': loops_pop(&loops, mem[ptr], &i); break;

			// i/o
      case '.': putchar(mem[ptr]); break;
			case ',': mem[ptr] = getchar();
		}
   
    // update righmost position used in memory
    if (ptr > max_ptr) {
      max_ptr++;
    }

  }
  // free memory for loops
	loops_free(&loops);
  
  // debug memory usage at final of program
  if (debug) { 
    meminfo(mem, max_ptr, ptr);
  }
}


int main(int argc, char **argv) {
  bool debug = false;
	if (argc == 1) {
		puts("\tUsage: ./brainduck <filename> [-d]\n\t-d: show memory info");
		exit(1);
	}
  if (argc == 3) {
    if (!strcmp(argv[2], "-d")) {
      debug = true;
    }
  }

  char *program = readf(argv[1]);
	bd_execute(program, debug);
  free(program);

	return 0;
}
