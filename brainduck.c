#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "bdutil.c"
#include "bdprogram.c"
#include "bdmemory.c"
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
void execBrainfuck(Program *prog, Memory *mem) {
	Loops loops;
	initLoops(&loops);

	for (; prog->counter < strlen(prog->code); prog->counter++) {
		switch (prog->code[prog->counter]) {
			
			/** math operations **/
			case '+': mem->data[mem->pointer]++; break;
			case '-': mem->data[mem->pointer]--; break;
			
			/** move memory pointer **/
			case '<': movePointerLeft(mem); break;
			case '>': movePointerRight(mem); break;

			/** loops **/
			case '[': beginOfLoop(&loops, prog->counter); break;
			case ']': endOfLoop(&loops, mem->data[mem->pointer], &prog->counter); break;

			/** i/o **/
			case '.': putchar(mem->data[mem->pointer]); break;
		}
	}
	printr(mem->data, mem->length, mem->pointer); 
}


int main(int argc, char *argv[]) {
	if (argc == 1) {
		puts("\tusage brainduck <filename>");
		exit(1);
	}
	Program prog;
	initProgram(&prog, argv[1]);

	Memory mem;
	initMemory(&mem);

	execBrainfuck(&prog, &mem);
	closeProgram(&prog);
	freeMemory(&mem);

	return 0;
}