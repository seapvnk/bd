#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "bdloops.c" // loop functions

// helper functions
char *readf(char *filename) {
	// copy the content of a text file to a c-string
	FILE *source = fopen(filename, "r");
	char *program = malloc(1);
	int len = 1;
	char c;

	// read till the end
	while ((c = fgetc(source)) != EOF) {
		// copy program to string 
		program[len-1] = c;
		program = realloc(program, ++len);
			
	}

	// end of string
	program = realloc(program, len+1);
	program[len] = '\0';
	fclose(source);

	return program;
}

typedef struct {
	int length;
	int *breakpoints;
	bool firstUse;
} Loops;

void initLoops(Loops *lp) {
	// set only length
	lp->length = 0;
	lp->firstUse = true;
}

int peek(Loops *lp) {
	if (lp->length == 0) return -1;
	return lp->breakpoints[lp->length - 1];
}

void beginOfLoop(Loops *lp, int programCounter) {
	if (lp->firstUse) {
		// first time using memory
		lp->breakpoints = malloc(sizeof(int));
		lp->breakpoints[lp->length++] = programCounter;
		lp->firstUse = false;
	} else {
		lp->breakpoints = realloc(lp->breakpoints, ++lp->length * sizeof(int));
		lp->breakpoints[lp->length - 1] = programCounter;
	}
}

void endOfLoop(Loops *lp, unsigned char dataCell, int *programCounter) {
	if (!lp->firstUse && lp->length > 0) {
		if (!dataCell) {
			// end the loop
			lp->breakpoints = realloc(lp->breakpoints, --lp->length * sizeof(int));
		} else {
			// set program counter back to the last loop
			*programCounter = peek(lp);
		}	
	}
	
}

void closeLoops(Loops *lp) {
	free(lp->breakpoints);
	lp->length = 0;
}


// executing brainf*ck 
void execBrainfuck(char *program) {
	Loops loops;
	initLoops(&loops);

	int *lp = malloc(sizeof(int));
	int lptr = 0;
	int len = 1;

	unsigned char mem[30000] = {0};
	unsigned int ptr = 0;

	for (int i = 0; i < strlen(program); i++) {
		switch (program[i]) {
			case '+': mem[ptr]++; break;
			case '-': mem[ptr]--; break;
			case '<': (ptr)? ptr--: 0; break;
			case '>': ptr++; break;
			case '[': beginOfLoop(&loops, i); break;
			case ']': endOfLoop(&loops, mem[ptr], &i); break;
			case '.': putchar(mem[ptr]); break;
		}
	}
}


int main(int argc, char *argv[]) {
	if (argc == 1) {
		puts("\tusage brainduck <filename>");
		exit(1);
	}
	execBrainfuck(readf(argv[1]));

	return 0;
}