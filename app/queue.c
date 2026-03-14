/**
 * @file queue.c
 * @author Alan Yeray Olivas
 * @brief queue buffers to store messages
 * @version 0.1
 * @date 2024-05-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h> 
#include "queue.h"
#include <string.h>


/**
 * @brief init elements of the structure to zero
 * 
 * @param queue [in] queue structure
 */
void Queue_initQueue(Que_Queue *queue)
{
    queue->Head = 0;
    queue->Tail = 0;
    queue->Empty = 0;
    queue->Full = 0;
}

/**
 * @brief write one element to the queue a
 * 
 * @param queue [in] queue structure
 * @param data [in] the element to write
 * @retval uint8_t if it was succeeded or failed
 */
uint8_t Queue_writeData(Que_Queue *queue, void *data)
{
    // It should have an interface that allows writing an element to the queue.
    // Copy the data to the queue buffer

    uint32_t position;
    position = queue->Head * queue->Size;
    memcpy(queue->Buffer + position, data, queue->Size);

    queue->Head++;
    queue->Empty = false;

    if (queue->Head == queue->Elements)
    {
        // queue->Head = 0;
        queue->Full = true;

        if (queue->Head == queue->Tail)
        { // Full
            queue->Tail = 0;
            queue->Head = 0;
            queue->Full = false;
        }
    }

    if (queue->Full == true)
    {

        return false;
    }

    return true; // ready
}


/**
 * @brief read an element from the queue
 * 
 * @param queue [in] queue structure
 * @param data [out] the element to read it
 * @retval uint8_t uint8_t if it was succeeded or failed
 */
uint8_t Queue_readData(Que_Queue *queue, void *data)
{
    if (queue->Empty == true)
    {
        return false;
    }

    uint32_t position;
    position = queue->Tail * queue->Size;
    memcpy(data, queue->Buffer + position, queue->Size);

    queue->Tail++;

    if (queue->Tail >= queue->Elements)
    {
        queue->Empty = true;
    }

    if (queue->Head == queue->Tail)///FIX?      
    { // Full
        queue->Tail = 0;
        queue->Head = 0;
        queue->Empty = false;
    }

    return true;
}

/**
 * @brief check if it empty or not
 * 
 * @param queue [in] queue structure
 * @retval uint8_t uint8_t if it was succeeded or failed
 */
uint8_t Queue_isQueueEmpty(Que_Queue *queue)
{
    // It should have an interface that indicates if the queue is empty.
    if (queue->Empty == true)
    {
        return 1; // empty
    }
    else
    {
        return 0; // isn't empty
    }
}

/**
 * @brief empty the queues
 * 
 * @param queue [in] queue structure
 */
void Queue_flushQueue(Que_Queue *queue)
{

    Queue_initQueue(queue);
    // function must empty the queue in case it has elements inside it, the information will be discarded
    /*
    uint32_t position = 0;
    while (position == queue->Elements)
    {
        position = position * queue->Size;
        memcpy(queue->Buffer + position, 0, queue->Size);
        position++;
    }
    queue->Empty = true;
    queue->Tail = 0;
    queue->Head = 0;
    */
}
