#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "bdloops.c"

/** helper functions **/
char *readf(char *filename) {
	/** copy the content of a text file to a c-string**/
	FILE *source = fopen(filename, "r");
	char *program = malloc(1);
	int len = 1;
	char c;

	/** read till the end **/
	while ((c = fgetc(source)) != EOF) {
		/** copy program to string */
		program[len-1] = c;
		program = realloc(program, ++len);
			
	}

	/** end of string **/
	program = realloc(program, len+1);
	program[len] = '\0';
	fclose(source);

	return program;
}


/** executing brainf*ck **/
void execBrainfuck(char *program) {
	Loops loops;
	initLoops(&loops);

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