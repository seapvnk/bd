/*
 *  Brainduck
 *  Initial Version: Pedro Sérgio <www.psro@gmail.com> 
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lib/brainduck.c"

#define MSG_VERSION "brainduck - version 2.0.1"
#define MSG_HELP "\tUsage: ./brainduck <filename>|flag [-d]\n\t-d: show memory info\n\t-v: show version"

#define MEM_SIZE 30000

char *readf(char *filename);
void memory_info(unsigned char *memory, int rightmost_cell, int pointer);
void bd_execute(char *program, bool debug);
void terminate(const char* msg);


// executing brainf*ck 
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

char *readf(char *filename){

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

void memory_info(unsigned char *memory, int rightmost_cell, int pointer){
   puts("\n\n       BRAINDUCK       \nAddress  Value  Pointer");
   for (int i = 0; i <= rightmost_cell; i++) {
     bool is_pointer = (i == pointer);
     printf("%7d  %5d  %s\n", i, memory[i], is_pointer? "  <-" : " ");
   }
}

void terminate(const char* msg){
  puts(msg);
  exit(0);
}

void bd_execute(char *program, bool debug){
	// loops
  bdl loops;
	bdl_init(&loops);
  
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
			case '[': bdl_add(&loops, i); break;
      case ']': bdl_remove(&loops, memory[pointer], &i); break;

			// i/o
      case '.': putchar(memory[pointer]); break;
			case ',': memory[pointer] = getchar();
		}
   
    // update righmost position used in memory
    if (pointer > rightmost_cell) {
      rightmost_cell++;
    }

  }

  // free memory used by loops
	bdl_free(&loops);
  
  // debug memory usage at final of program
  if (debug) { 
    memory_info(memory, rightmost_cell, pointer);
  }
}


