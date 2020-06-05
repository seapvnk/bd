#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

void printr(unsigned char *array, int size, int pointer) {
	putchar('\n');
	for (int i = 0; i < size; i++) {
		printf("%c [%x] %d\n", (i == pointer)? '>':' ', i, array[i]);
	}
}

/** Program **/

typedef struct {
	char *code;
	int counter;
} Program;

void initProgram(Program *prog, char *filename) {
	prog->code = readf(filename); 
	prog->counter = 0;
}

void closeProgram(Program *prog) {
	free(prog->code);
}

/** Memory **/

typedef struct {
	unsigned char *data;
	unsigned int pointer;
	int length;
} Memory;

void initMemory(Memory *mem) {
	mem->length = 1;
	mem->pointer = 0;
	mem->data = malloc(1);
	mem->data[0] = 0;
}

void expandMemory(Memory *mem) {
	mem->data = realloc(mem->data, ++mem->length);
	mem->data[++mem->pointer] = 0;
}

void freeMemory(Memory *mem) {
	free(mem->data);
}

/** executing brainf*ck **/
void execBrainfuck(Program *prog, Memory *mem) {
	for (int i = 0; i < strlen(prog->code); i++) {
		switch (prog->code[i]) {
			case '+': mem->data[mem->pointer]++; break;
			case '-': mem->data[mem->pointer]--; break;
			case '<': (mem->pointer > 0)? mem->pointer-- : 0; break;
			case '>': (mem->pointer >= mem->length)? mem->pointer++ : expandMemory(mem); break;
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