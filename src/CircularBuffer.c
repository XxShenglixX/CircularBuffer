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
 
/* Initialise the circular buffer
 *
 * Input :
 *	length is the maximum of data that can be allocated in the buffer	
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

/* Free the memory
 * 
 */
void circularBufferDel(CircularBuffer *circularBuffer)
{
	free(circularBuffer);
}

/* *
 * Add data to the circular buffer 
 * Note : Will throw an error if the buffer is full
 *
 * Input : 
 *	cb is the circular buffer
 *	value is the data needed to be written
 *
 * Precondition :
 *	size must not be negative
 */
void circularBufferAdd(CircularBuffer *cb,int value)
{
	if (cb->size >= cb->length)	// if size of the buffer is larger or equal to the length of the buffer, the buffer is considered full and will
	{							// throw an error
		Throw(ERR_BUFFER_IS_FULL);
	}

	cb->head = cb->buffer; // reset head to the starting location of buffer for later use
		
	if (cb->size != 0)  // if the buffer already contains data,
		{
			cb->head += (cb->size);	 //move head to last written location + 1 by using the size of buffer to determine
			cb->tail = cb->head ; 	 // move tail to head and then  
			cb->tail -- ;			// decrement once
		}
		
	*cb->head = value ; 	// load the head with value
	
	if (cb->size > 0)		//tail will only increment if size is greater than 0 to make sure tail is always 1 step behind head 
		cb->tail ++;
		
	cb->size +=1 ;	// increase the size of buffer
	
	
}


/** 
 * Retrieve the last data in the circular buffer and allow the location to be overwritten with new data
 * Note : will throw an error if the buffer is empty
 *
 * Input : 
 *	cb is the circular buffer
 * Return :
 * value is the data contain in the last location of the circular buffer
 */
int circularBufferRemove(CircularBuffer *cb)
{
	if (cb->size == 0) // the buffer is empty if the size is 0 and will throw an error
	{
		Throw(ERR_BUFFER_IS_EMPTY);
	}
	

	int value ; // use to retrieve data in the buffer

	value = *cb->tail ; // load value with data in the tail 
	cb->size -- ; 	// decrease size of buffer
	
	if (cb->size != 0) //will stop decrement tail is size is 0 to prevent over decrement
	{
		cb->tail -- ;
	}
	
	return value; // returns the value retrieved
}