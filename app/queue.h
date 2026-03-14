#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdio.h>
#include <stdint.h>

/**
 * @brief structre to define a message
 * 
 */
typedef struct
{
    uint8_t msg;
    uint8_t value;
} MsgType_Message;


/**
 * @brief structure to make a queue
 * 
 */
typedef struct
{
    void *Buffer;      // pointer to array that store buffer data
    uint32_t Elements; // number of elements to store (the queue lenght)
    uint8_t Size;      // size of the elements to store
    uint8_t Head;      // variable to signal the next queue space to write
    uint8_t Tail;      // variable to signal the next queue space to read
    uint8_t Empty;     // flag to indicate if the queue is empty
    uint8_t Full;      // flag to indicate if the queue is full
    // agregar más elementos si se requieren
} Que_Queue;

/**
 * @brief init elements of the structure to zero
 * 
 * @param queue [in] queue structure
 */
void Queue_initQueue(Que_Queue *queue);

/**
 * @brief write one element to the queue a
 * 
 * @param queue [in] queue structure
 * @param data [in] the element to write
 * @retval uint8_t if it was succeeded or failed
 */
uint8_t Queue_writeData(Que_Queue *queue, void *data);
/**
 * @brief read an element from the queue
 *
 * @param queue [in] queue structure
 * @param data [out] the element to read it
 * @retval uint8_t uint8_t if it was succeeded or failed
 */
uint8_t Queue_readData(Que_Queue *queue, void *data);
/**
 * @brief check if it empty or not
 *
 * @param queue [in] queue structure
 * @retval uint8_t uint8_t if it was succeeded or failed
 */
uint8_t Queue_isQueueEmpty(Que_Queue *queue);
/**
 * @brief empty the queues
 *
 * @param queue [in] queue structure
 */
void Queue_flushQueue(Que_Queue *queue);

#endif