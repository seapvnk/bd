typedef struct {
	int length;
	int *breakpoints;
	bool firstUse;
} Loops;

void initLoops(Loops *lp) {
	/** set only length **/
	lp->length = 0;
	lp->firstUse = true;
}

int peek(Loops *lp) {
	if (lp->length == 0) return -1;
	return lp->breakpoints[lp->length - 1];
}

void beginOfLoop(Loops *lp, int programCounter) {
	if (lp->firstUse) {
		/** first time using memory **/
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
			/** end the loop **/
			lp->breakpoints = realloc(lp->breakpoints, --lp->length * sizeof(int));
		} else {
			/** set program counter back to the last loop **/
			*programCounter = peek(lp);
		}	
	}
	
}

void closeLoops(Loops *lp) {
	free(lp->breakpoints);
	lp->length = 0;
}

