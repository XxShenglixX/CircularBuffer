#include "unity.h"
#include "CircularBuffer.h"
#include "CException.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_CircularBufferNew_given_6_should_allotcate_CircularBuffer_obeject_with_a_buffer_of_6(void)
{
	CircularBuffer *cb = circularBufferNew(6);
	TEST_ASSERT_NOT_NULL(cb);
	TEST_ASSERT_NOT_NULL(cb->buffer);
	TEST_ASSERT_EQUAL(6,cb->length);
	TEST_ASSERT_EQUAL(0,cb->size);
	TEST_ASSERT_EQUAL_PTR(cb->buffer,cb->head);
	TEST_ASSERT_EQUAL_PTR(cb->buffer,cb->tail);
	circularBufferDel(cb);
}

void test_circularBufferRemove_empty_buffer_should_throw_an_error()
{
	CircularBuffer *cb = circularBufferNew(6);
	CEXCEPTION_T err;
	
	Try
	{
		circularBufferRemove(cb);
		printf("Error should generate an exception due to empty buffer\n");
	}
	Catch(err)
	{
		TEST_ASSERT_EQUAL(ERR_BUFFER_IS_EMPTY,err);
		printf("Error code [%d] Buffer is empty\n",ERR_BUFFER_IS_EMPTY);
	}
	circularBufferDel(cb);
}

void test_circularBufferAdd_bufferof_length_6_size_6_should_throw_an_error()
{
	CircularBuffer *cb = circularBufferNew(6);
	CEXCEPTION_T err;
	cb->size = 6;
	
	Try
	{
		circularBufferAdd(cb,0);
		printf("Error should generate an exception due to full buffer\n");
	}
	Catch(err)
	{
		TEST_ASSERT_EQUAL(ERR_BUFFER_IS_FULL,err);
		printf("Error code [%d] Buffer is full\n",ERR_BUFFER_IS_FULL);
	}
	circularBufferDel(cb);
}  


void test_circularBufferAdd_bufferof_given_length_6_value_5_should_return_5_for_the_1st_data_in_buffer()
{
	CircularBuffer *cb = circularBufferNew(6);
	CEXCEPTION_T err;
	
	Try
	{
		circularBufferAdd(cb,5);
		printf("Success: No exception generated.\n");
		TEST_ASSERT_EQUAL(5,*cb->tail);
	}
	Catch(err)
	{
		TEST_FAIL_MESSAGE("Do not expect exception to be generated.\n");
	}
	circularBufferDel(cb);
}

void test_circularBufferAdd_bufferof_given_length_5_value_1_2_3_4_5_6_should_return_1_2_3_4_5_and_throw_an_error()
{
	CircularBuffer *cb = circularBufferNew(5);
	CEXCEPTION_T err;
	
	Try
	{
		circularBufferAdd(cb,1);
		TEST_ASSERT_EQUAL(1,*cb->tail);
		circularBufferAdd(cb,2);
		TEST_ASSERT_EQUAL(2,*cb->tail);
		circularBufferAdd(cb,3);
		TEST_ASSERT_EQUAL(3,*cb->tail);
		circularBufferAdd(cb,4);
		TEST_ASSERT_EQUAL(4,*cb->tail);
		circularBufferAdd(cb,5);
		TEST_ASSERT_EQUAL(5,*cb->tail);
		circularBufferAdd(cb,6);
		printf("Error should generate an exception due to full buffer\n");
	}
	Catch(err)
	{
		TEST_ASSERT_EQUAL(ERR_BUFFER_IS_FULL,err);
		printf("Error code [%d] Buffer is full\n",ERR_BUFFER_IS_FULL);
	
	}
	circularBufferDel(cb);
}
