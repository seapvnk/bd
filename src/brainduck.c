#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
	//return the last position
	if (!lp->length) exit(-1);
	return lp->positions[lp->length - 1];
}

void loops_push(Loops *lp, int pc) {
	// add a new position to loop

	if (!lp->length) {
		lp->positions = malloc(sizeof(int));
		lp->positions[lp->length++] = pc;
	} else {
		lp->length++;
		lp->positions = realloc(lp->positions, lp->length * sizeof(int));
		lp->positions[lp->length - 1] = pc;
	}
}

void loops_pop(Loops *lp, unsigned char cell, int *pc) {
	// remove the last loop position

	if (lp->length > 0) {
		// if data provided is 0 then end the loop
		if (!cell) {
			lp->length--;
			lp->positions = realloc(lp->positions, lp->length * sizeof(int));
		} else {
			// set program counter back to the last loop
			*pc = loops_last(lp);
		}	
	}
	
}

void loops_free(Loops *lp) {
	free(lp->positions);
	lp->length = 0;
}


// executing brainf*ck 
void bd_execute(char *program) {
	Loops loops;
	loops_init(&loops);

	unsigned char mem[30000] = {0};
	unsigned int ptr = 0;

	for (int i = 0; i < strlen(program); i++) {
		switch (program[i]) {
			case '+': mem[ptr]++; break;
			case '-': mem[ptr]--; break;
			case '>': {
				if (ptr > 30000) ptr++;	
				break;
			}
			case '<': {
				if (ptr) ptr--;
				break;	
			}
			case '[': loops_push(&loops, i); break;
			case ']': loops_pop(&loops, mem[ptr], &i); break;
			case '.': putchar(mem[ptr]); break;
			case ',': mem[ptr] = getchar();
		}
	}
	loops_free(&loops);
}


int main(int argc, char *argv[]) {
	if (argc == 1) {
		puts("\tusage brainduck <filename>");
		exit(1);
	}
	bd_execute(readf(argv[1]));

	return 0;
}