/** Memory **/

typedef struct {
	unsigned char *data;
	unsigned int pointer;
	int length;
} Memory;

void initMemory(Memory *mem) {
	mem->length = 0;
	mem->pointer = 0;
	mem->data = malloc(1);
	mem->data[0] = 0;
}

void movePointerLeft(Memory *mem) {
	if (mem->pointer > 0)
		mem->pointer--;
}

void movePointerRight(Memory *mem) {
	/** 
		increment pointer, if this position don't exists then 
		create this memory position 
	**/
	if (++mem->pointer > mem->length) {
		mem->data = realloc(mem->data, ++mem->length);
		mem->data[mem->pointer] = 0;
	}
}

void freeMemory(Memory *mem) {
	free(mem->data);
}