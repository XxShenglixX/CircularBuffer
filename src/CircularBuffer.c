#include "CircularBuffer.h"
#include <stdio.h>
#include <malloc.h>
#include "CException.h"

/* void dummy()
{
	int integer ; //static allocation
	int *ptr2integer ;
	
	ptr2integer = malloc(sizeof(int)); //dynamic allocation
	
	free(ptr2integer); // free the memory
}
 */
 
CircularBuffer *circularBufferNew(int length)
{
	CircularBuffer *circularBuffer;
	
	circularBuffer = malloc(sizeof(CircularBuffer));
	circularBuffer->buffer = malloc(sizeof(int) * length);
	circularBuffer->length = length;
	circularBuffer->size = 0;
	circularBuffer->head = circularBuffer->buffer ;
	circularBuffer->tail = circularBuffer->buffer ;
	
	return circularBuffer;
}

void circularBufferDel(CircularBuffer *circularBuffer)
{
	free(circularBuffer);
}