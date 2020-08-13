/*
 *  Brainduck
 *  Initial Version: Pedro Sérgio <www.psro@gmail.com> 
 * 
*/

#include <stdlib.h>

// BRAINDUCK LOOPS
typedef struct {
	int length;
	int *positions;
} bdl;

void bdl_init(bdl *lp)
{
	// set length zero by default
	lp->length = 0;
}

int bdl_last(bdl *lp)
{
	// return the last position
	if (!lp->length) {
    exit(-1);
  }
	return lp->positions[lp->length - 1];
}

void bdl_add(bdl *lp, int pc) 
{
	// add a new position to loops

	if (!lp->length) {
		lp->positions = malloc(sizeof(int));
		lp->positions[lp->length] = pc;
    lp->length++;
	} else {
		lp->length++;
		lp->positions = realloc(lp->positions, lp->length * sizeof(int));
		lp->positions[lp->length - 1] = pc;
	}
}

void bdl_remove(bdl *lp, unsigned char cell, int *pc) 
{
	// remove the last position
	  
  if (!cell) {
	  	lp->length--;
	  	lp->positions = realloc(lp->positions, lp->length * sizeof(int));
	  } else {
		  *pc = bdl_last(lp);
	  }	
}

void bdl_free(bdl *lp) 
{
	free(lp->positions);
	lp->length = 0;
}
