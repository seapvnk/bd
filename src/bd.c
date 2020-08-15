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

#define MSG_VERSION "brainduck - version 2.0.2"

char *readf(char *filename);
void terminate(const char* msg);
void show_help(void);

// executing brainf*ck 
int main(int argc, char **argv) {
  bool debug = false;
  
  // end program without any brainfuck program input
	if (argc == 1) {
    show_help();
    terminate("");
	} else if (argc == 2 && 
    (!strcmp(argv[1], "-v") || !strcmp(argv[1], "--version"))) {
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

void show_help(void)
{
  puts(MSG_VERSION);
  puts("usage: ./bd file.bd");
  puts("flags:");
  puts("\tversion : --version or -v");
  puts("\tmemory info: -d");
}

char *readf(char *filename)
{

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

void terminate(const char* msg)
{
  if (strlen(msg))
    puts(msg);
  exit(0);
}


