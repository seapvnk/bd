/*
 *  Brainduck
 *  Initial Version: Pedro Sérgio <www.psro@gmail.com> 
 * 
*/

void bd_meminfo(unsigned char *memory, int rightmost_cell, int pointer);
void bd_execute(char *program, bool debug);

void bd_execute(char *program, bool debug)
{
	// loops
  bdl loops;
	bdl_init(&loops);
  
  // memory
	unsigned char * memory = malloc(sizeof (char));
  *memory = 0;
	unsigned int pointer = 0;
  int rightmost_cell  = 0;

	for (int i = 0; i < strlen(program); i++) {
		switch (program[i]) {
      // add or sub operation
			case '+': memory[pointer]++; break;
			case '-': memory[pointer]--; break;
      
      // memory operations
			case '>': {
        if (pointer+1 > rightmost_cell) {
          memory = realloc(memory, pointer+1);
          rightmost_cell++;
          memory[rightmost_cell] = 0;
        }
        pointer++;
        break; 
      }

			case '<': {
        if (pointer) pointer--;
        break;
      }
      
      // flow control
			case '[': bdl_add(&loops, i); break;
      case ']': bdl_remove(&loops, memory[pointer], &i); break;

			// i/o
      case '.': putchar(memory[pointer]); break;
			case ',': memory[pointer] = getchar();
		}

  }

  // free memory used by loops
	bdl_free(&loops);
  
  // debug memory usage at final of program
  if (debug) { 
    bd_meminfo(memory, rightmost_cell, pointer);
  }

  free(memory);

}


void bd_meminfo(unsigned char *memory, int rightmost_cell, int pointer)
{
   putchar('\n');
   puts(BD_LOGO);
   puts("Address  Value  Pointer");
   for (int i = 0; i <= rightmost_cell; i++) {
     bool is_pointer = (i == pointer);
     printf("%7d  %5d  %s\n", i, memory[i], is_pointer? "  <-" : " ");
   }
}








