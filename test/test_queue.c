/**
 * @file test_queue.c
 * @author Alan Yeray Olivas
 * @brief unity testing for queue.c functions
 * @version 0.1
 * @date 2024-05-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "unity.h"
#include "queue.h"

/**
 * @defgroup <1 AND 0> macro to define 1s and 0s inside of conditionals
 *
 */
#define TRUE 1
#define FALSE 0

/**
 * @brief Set the Up object
 * 
 */
void setUp(void)
{
}

/**
 * @brief teadDown
 * 
 */
void tearDown(void)
{
}

/**
 * @brief  test if it increments tail when reading data
 * 
 */
void test_Queue_readData_incrementTail__()
{
    Que_Queue hqueue;
    uint8_t buffer[8];
    hqueue.Buffer = buffer;
    hqueue.Elements = 8;
    hqueue.Size = 1;

    uint8_t aux = 1;
    Queue_initQueue(&hqueue);
    Queue_writeData(&hqueue, &aux);

    uint8_t varRead;
    Queue_readData(&hqueue, &varRead);

    TEST_ASSERT_EQUAL(1, varRead);
}

/**
 * @brief test if it values were passed to another structure
 * 
 */
void test_Queue_readData_return_false__()
{
    Que_Queue hqueue;
    uint8_t buffer[8];
    hqueue.Buffer = buffer;
    hqueue.Elements = 8;
    hqueue.Size = 1;

    uint8_t aux = 1;
    Queue_initQueue(&hqueue);
    Queue_writeData(&hqueue, &aux);

    hqueue.Empty = 1;
    uint8_t varRead;
    Queue_readData(&hqueue, &varRead);

    TEST_ASSERT_EQUAL(0, Queue_readData(&hqueue, &varRead));
}

/**
 * @brief test if it runs along the branch tail and head are different
 * 
 */
void test_Queue_readData_branch_tail_head_different__()
{
    Que_Queue hqueue;
    uint8_t buffer[4];
    hqueue.Buffer = buffer;
    hqueue.Elements = 4;
    hqueue.Size = 1;

    Queue_initQueue(&hqueue);
    uint8_t aux = 1;
    Queue_writeData(&hqueue, &aux);
    aux = 2;  
    Queue_writeData(&hqueue, &aux);
    aux = 3;  
    Queue_writeData(&hqueue, &aux); 
    aux = 4;  
    Queue_writeData(&hqueue, &aux);  
    
    uint8_t varRead;
    Queue_readData(&hqueue, &varRead);

    TEST_ASSERT_EQUAL(1, hqueue.Tail);
}

/**
 * @brief test if it Queue_readData() returns empty
 * 
 */
void test_Queue_readData_return_empty__()
{
    Que_Queue hqueue;
    uint8_t buffer[8];
    hqueue.Buffer = buffer;
    hqueue.Elements = 8;
    hqueue.Size = 2;

    uint8_t aux = 1;
    Queue_initQueue(&hqueue);
    Queue_writeData(&hqueue, &aux);

    hqueue.Empty = 1;
    uint8_t varRead;

    TEST_ASSERT_EQUAL(0, Queue_readData(&hqueue, &varRead));
} // fix

/**
 * @brief test Queue_writeData write sigle data
 * 
 */
void test__Queue_writeData__writting_a_single_data(void)
{
    typedef struct
    {
        uint8_t msg;
        uint8_t value;
    } MsgType_Message;

    Que_Queue Queue;
    MsgType_Message MsgToWrite;
    uint8_t buffer[8];

    Queue.Buffer = (void *)buffer;
    Queue.Elements = 3;

    Queue_initQueue(&Queue);
    Queue_writeData(&Queue, &MsgToWrite);

    MsgToWrite.msg = '0';

    TEST_ASSERT_EQUAL(1, Queue.Head);         // test head pointer increment by one
    TEST_ASSERT_EQUAL(&buffer, Queue.Buffer); //
    TEST_ASSERT_EQUAL(0, Queue_isQueueEmpty(&Queue));
}

/**
 * @brief test when tail and head is 0 in function Queue_writeDAta
 * 
 */
void test__Queue_writeData___tail_and_head_0_(void)
{
    typedef struct
    {
        uint8_t msg;
        uint8_t value;
    } MsgType_Message;

    Que_Queue Queue;
    MsgType_Message MsgToWrite;
    uint8_t buffer[2];

    Queue.Buffer = (void *)buffer;
    Queue.Elements = 2;

    Queue_initQueue(&Queue);
    Queue.Tail = 2;
    Queue.Head = 1;
    MsgToWrite.msg = '0';
    Queue_writeData(&Queue, &MsgToWrite);

    TEST_ASSERT_EQUAL(0, Queue.Tail); //
}

/**
 * @brief test when tail and head are same in functoin Queue_writeData
 * 
 */
void test__Queue_writeData___tail__head_same_(void)
{
    typedef struct
    {
        uint8_t msg;
        uint8_t value;
    } MsgType_Message;

    Que_Queue Queue;
    MsgType_Message MsgToWrite, MsgToRead;
    uint8_t buffer[1];

    Queue.Buffer = (void *)buffer;
    Queue.Elements = 1;

    Queue_initQueue(&Queue);
    MsgToWrite.msg = 3;
    Queue_writeData(&Queue, &MsgToWrite);
    Queue_readData(&Queue, &MsgToWrite);

    TEST_ASSERT_EQUAL(0, Queue.Empty); //
}

/**
 * @brief test when queue is full in function writeData()
 * 
 */
void test__Queue_writeData__filling_the_queue(void)
{
    typedef struct
    {
        uint8_t msg;
        uint8_t value;
    } MsgType_Message;

    Que_Queue Queue;
    MsgType_Message MsgToWrite;
    uint8_t buffer[8];

    Queue.Buffer = (void *)buffer;
    Queue.Elements = 3u;
    Queue_initQueue(&Queue);
    MsgToWrite.msg = 1;
    Queue_writeData(&Queue, &MsgToWrite);
    MsgToWrite.msg = 'g';
    Queue_writeData(&Queue, &MsgToWrite);
    MsgToWrite.msg = 3;
    Queue_writeData(&Queue, &MsgToWrite);

    TEST_ASSERT_EQUAL(1, Queue.Full); // test full flag
    TEST_ASSERT_EQUAL(3, Queue.Head); // test head pointer roll over back to zero
}

/**
 * @brief test if empties the tail
 * 
 */
void test__Queue_flushQueue(void)
{
    typedef struct
    {
        uint8_t msg;
        uint8_t value;
    } MsgType_Message;

    Que_Queue Queue;
    MsgType_Message MsgToWrite;
    uint8_t buffer[8];

    Queue.Buffer = (void *)buffer;
    Queue.Elements = 3;
    Queue_initQueue(&Queue);
    MsgToWrite.msg = '1';
    Queue_writeData(&Queue, &MsgToWrite);
    MsgToWrite.msg = '2';
    Queue_writeData(&Queue, &MsgToWrite);
    MsgToWrite.msg = '3';
    Queue_writeData(&Queue, &MsgToWrite);
    Queue_flushQueue(&Queue);

    TEST_ASSERT_EQUAL(0, Queue.Head);
}

/**
 * @brief test if function returns 1, queue is empty
 * 
 */
void test_isQueEmpty__check_param_1_()
{
    typedef struct
    {
        uint8_t msg;
        uint8_t value;
    } MsgType_Message;

    Que_Queue Queue;
    MsgType_Message MsgToWrite, MsgToRead;
    uint8_t buffer[1];
    Queue.Buffer = (void *)buffer;
    Queue.Elements = 1;
    Queue_initQueue(&Queue);
    MsgToWrite.msg = '1';

    Queue_writeData(&Queue, &MsgToWrite);
    Queue.Empty = TRUE;

    TEST_ASSERT_EQUAL(1, Queue_isQueueEmpty(&Queue));
}

/**
 * @brief test if function returns queue isn't empty
 * 
 */
void test_isQueEmpty__check_param_0_()
{
    typedef struct
    {
        uint8_t msg;
        uint8_t value;
    } MsgType_Message;

    Que_Queue Queue;
    MsgType_Message MsgToWrite;
    uint8_t buffer[8];

    Queue.Buffer = (void *)buffer;
    Queue.Elements = 3;
    Queue_initQueue(&Queue);

    TEST_ASSERT_EQUAL(0, Queue_isQueueEmpty(&Queue));
}
