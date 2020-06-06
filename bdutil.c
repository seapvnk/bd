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