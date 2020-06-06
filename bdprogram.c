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