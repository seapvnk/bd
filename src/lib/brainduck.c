/*
 *  Brainduck
 *  Initial Version: Pedro Sérgio <www.psro@gmail.com> 
 * 
*/

#include <stdlib.h>

#define MEM_SIZE 30000

// BRAINDUCK LOOPS
typedef struct {
	int length;
	int *positions;
} bdl;

void bdl_init(bdl *lp)
{
	// set length zero by default
	lp->length = 0;
}

int bdl_last(bdl *lp)
{
	// return the last position
	if (!lp->length) {
    exit(-1);
  }
	return lp->positions[lp->length - 1];
}

void bdl_add(bdl *lp, int pc) 
{
	// add a new position to loops

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

void bdl_remove(bdl *lp, unsigned char cell, int *pc) 
{
	// remove the last position
	  
  if (!cell) {
	  	lp->length--;
	  	lp->positions = realloc(lp->positions, lp->length * sizeof(int));
	  } else {
		  *pc = bdl_last(lp);
	  }	
}

void bdl_free(bdl *lp) 
{
	free(lp->positions);
	lp->length = 0;
}

// INTERPRETER

void bd_meminfo(unsigned char *memory, int rightmost_cell, int pointer){
   puts("\n\n       BRAINDUCK       \nAddress  Value  Pointer");
   for (int i = 0; i <= rightmost_cell; i++) {
     bool is_pointer = (i == pointer);
     printf("%7d  %5d  %s\n", i, memory[i], is_pointer? "  <-" : " ");
   }
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
    bd_meminfo(memory, rightmost_cell, pointer);
  }
}
