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

void circularBufferAdd(CircularBuffer *cb,int value)
{
	if (cb->size == cb->length)
	{
		Throw(ERR_BUFFER_IS_FULL);
	}

	cb->head = cb->buffer;
		
	if (cb->size != 0) 
		{
			cb->head += (cb->size);
			cb->tail = cb->head ;
			cb->tail -- ;
		}
		
	*cb->head = value ;
	cb->head ++;
	
	if (cb->size > 0)
		cb->tail ++;
		
	cb->size +=1 ;
	
	
}



int circularBufferRemove(CircularBuffer *cb)
{
	if (cb->size == 0)
	{
		Throw(ERR_BUFFER_IS_EMPTY);
	}
}