/**
 * @file scheduler.c
 * @author Alan Yeray Olivas
 * @brief funtions to work on manage the scheduler
 * @version 0.1
 * @date 2024-05-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "scheduler.h"

/**
 * @defgroup <1 AND 0> macro to define 1s and 0s inside of conditionals
 *
 */
#define SET 1
#define CLEAR 0

/**
 * @brief obtain the time since start to run
 *
 * @return long the milliseconds
 */
long milliseconds(void)
{
    return clock() / (CLOCKS_PER_SEC / 1000);
}

/**
 * @brief init al elements of the structure to zero
 *
 * @param scheduler [in] structure
 */
void Sched_initScheduler(Sched_Scheduler *scheduler)
{

    scheduler->tasks = 0;
    scheduler->tick = 0;
    scheduler->timeout = 0;
    scheduler->tasksCount = 0;
    scheduler->timers = 0;
    scheduler->timersCount = 0;
    scheduler->actualTime = 0;
}

/**
 * @brief register a new task
 *
 * @param scheduler [in] structure
 * @param initPtr [in] function to init the functions to manage (taskPtr)
 * @param taskPtr [in] function to manage
 * @param period [in] period to do the function
 * @retval uint8_t the number of the task on the list . Start by 1
 */
uint8_t Sched_registerTask(Sched_Scheduler *scheduler, void (*initPtr)(void), void (*taskPtr)(void), uint32_t period)
{

    if (period < scheduler->tick) // Zero at first moment
    {

        return 0;
    }
    else
    {
        scheduler->taskPtr[scheduler->tasksCount].period = period; // always be multiple
    }

    // register functions
    scheduler->taskPtr[scheduler->tasksCount].taskFunc = taskPtr; // register task function

    if (initPtr == NULL) // check if it is void field
    {
        scheduler->taskPtr[scheduler->tasksCount].initFunc = NULL; // register with void init function
    }
    else
    {
        scheduler->taskPtr[scheduler->tasksCount].initFunc = initPtr; // register init function
    }

    static uint8_t id_task = 0;
    scheduler->taskPtr[scheduler->tasksCount].id = ++id_task;

    scheduler->taskPtr[scheduler->tasksCount].startFlag = 1; // ready to start task

    scheduler->tasksCount++;

    return id_task;
}

/**
 * @brief stop the task, prevents the scheduler from processing it
 *
 *          clear the flag
 *
 * @param scheduler [in] structure
 * @param task [in] the number of the task previusly registered
 * @retval uint8_t if it was succeeded or failed
 */
uint8_t Sched_stopTask(Sched_Scheduler *scheduler, uint8_t task)
{
    if (scheduler->taskPtr[task - 1].startFlag == SET)
    {
        scheduler->taskPtr[task - 1].startFlag = CLEAR;

        scheduler->tasksCount--;

        return true;
    }

    return false;
}

/**
 * @brief start the task,  the scheduler can processing it
 *
 *          set the flag
 *
 * @param scheduler [in] structure
 * @param task [in] the number of the task previusly registered
 * @retval uint8_t if it was succeeded or failed
 */
uint8_t Sched_startTask(Sched_Scheduler *scheduler, uint8_t task)
{

    if (scheduler->taskPtr[task - 1].startFlag == SET)
    {
        scheduler->taskPtr[task - 1].startFlag = CLEAR;

        scheduler->tasksCount++;

        return true; // set to start
    }

    return false;
    // Once a task is stopped using the function Scheduler_StopTask, it can be active again using this function. The second parameter indicates the task to be started, which is a
    // number from 1 to n task registered. Number zero is forbidden. the function will return a TRUE if the task was stopped otherwise returns FALSE
}

/**
 * @brief realod the period of the task and set the flag in 1
 *
 * @param scheduler [in] structure
 * @param task [in] the number of the task previusly registered
 * @param period [in] the time to start to processing it
 * @retval uint8_t if it was succeeded or failed
 */
uint8_t Sched_periodTask(Sched_Scheduler *scheduler, uint8_t task, uint32_t period)
{
    // The new periodicity shall be a multiple of the tick value otherwise won’t be affected by the new period. The second parameter indicates the task to be started, which is a number
    // from 1 to n task registered. Number zero is forbidden. the function will return a TRUE if the task was stopped otherwise returns FALSE.

    if (period >= scheduler->tick && period % scheduler->tick == 0)
    {
        scheduler->taskPtr[task - 1].period = period; // always be multiple
        return true;
    }

    return false;
}

/**
 * @brief register a new software timer
 *
 * @param scheduler [in] structure
 * @param timeout [in] the max count to wait
 * @param callbackPtr [in] the function to run when the timeout is out
 * @retval uint8_t if it was succeeded or failed
 */
uint8_t Sched_registerTimer(Sched_Scheduler *scheduler, uint32_t timeout, void (*callbackPtr)(void))
{

    if ((timeout % scheduler->tick) == 0 || timeout > scheduler->tick)
    {
        scheduler->timerPtr[scheduler->timersCount].timeout = timeout; // always be multiple
        scheduler->timerPtr[scheduler->timersCount].count = timeout;
    }
    else
    {
        return 0; // timer couldn't be registered.
    }

    // register callback function
    scheduler->timerPtr[scheduler->timersCount].callbackPtr = callbackPtr;
    scheduler->timerPtr[scheduler->timersCount].startFlag = 0;

    // register Id task
    if (scheduler->timersCount <= scheduler->timers)
    {
        scheduler->timersCount++;
        return scheduler->timersCount;
    }
    return 0; // timer couldn't be registered.
}

/**
 * @brief  return the count of the timer
 *
 * @param scheduler [in] structure
 * @param timer [in] the number of the task previusly registered
 * @retval uint32_t return the milliseconds// count
 */
uint32_t Sched_getTimer(Sched_Scheduler *scheduler, uint8_t timer)
{

    if (timer <= scheduler->timersCount) // check timer is registered
    {
        return scheduler->timerPtr[timer - 1].count;
    }

    return 0; // timer does not been registered the function returns a zero value
}

/**
 * @brief change the value for the timeout and set flag in 1
 *
 * @param scheduler [in] structure
 * @param timer [in] the number of the task previusly registered
 * @param timeout [in] the max count to wait
 * @retval uint8_t if it was succeeded or failed
 */
uint8_t Sched_reloadTimer(Sched_Scheduler *scheduler, uint8_t timer, uint32_t timeout)
{                                        // The timer will be reloaded with a new value in milliseconds it will also start the timer
    if (timer <= scheduler->timersCount) // check timer is registered
    {
        scheduler->timerPtr[timer - 1].timeout = timeout;
        scheduler->timerPtr[timer - 1].count = timeout;
        scheduler->timerPtr[timer - 1].startFlag = 1;
        return 1; // succeed
    }

    return 0;
}

/**
 * @brief start timer, set flag in 1 and reaload the timeout
 *
 * @param scheduler [in] structure
 * @param timer [in] the number of the task previusly registered
 * @return  uint8_t if it was succeeded or failed
 */
uint8_t Sched_startTimer(Sched_Scheduler *scheduler, uint8_t timer)
{
    // check timer is registered
    if ((timer <= scheduler->timersCount))
    {
        // reset flag
        if (scheduler->timerPtr[timer - 1].startFlag == 0)
        {
            scheduler->timerPtr[timer - 1].startFlag = 1;
        }

        // restart the timer
        scheduler->timerPtr[timer - 1].count = scheduler->timerPtr[timer - 1].timeout;

        return 1; // succeed
    }

    return 0; // timer to start has not been registered no action will be taken and it will return a zero
}

/**
 * @brief stop the timer and clear the flag
 *
 * @param scheduler [in] structure
 * @param timer [in] the number of the task previusly registered
 * @return uint8_t if it was succeeded or failed
 */
uint8_t Sched_stopTimer(Sched_Scheduler *scheduler, uint8_t timer)
{

    if (timer <= scheduler->timersCount) // check timer is registered
    {
        scheduler->timerPtr[timer - 1].startFlag = 0;
        return 1; // succeed
    }
    return 0; // timer to start has not been registered no action will be taken and it will return a zero
}

/**
 * @brief function to runs all the tasks and the timers
 *
 *      main function of the scheduler
 *
 * @param scheduler [in] structure
 */
void Sched_startScheduler(Sched_Scheduler *scheduler)
{
    // This is the function in charge of running the task init functions one single time and actual run each registered task according to their periodicity in an infinite loop, the function
    // will never return at least something wrong happens, but this will be considered a malfunction. A timer will need to accomplish this purpose, for practical reasons,

    // init initFunction once
    for (uint8_t i = 0; i < scheduler->tasksCount; i++)
    {
        scheduler->taskPtr[i].initFunc();
    }

    // start scheduler
    time_t control_timeout = milliseconds();
    while (1)
    {

        if (milliseconds() - scheduler->actualTime >= scheduler->tick)
        {
            scheduler->actualTime = milliseconds();

            // Handle timers
            if (scheduler->timers != 0) // activate timers
            {
                for (uint8_t i = 0; i < scheduler->timersCount; i++) // Handle timers
                {
                    scheduler->timerPtr[i].count -= scheduler->tick;

                    if (scheduler->timerPtr[i].startFlag == 1)
                    {
                        if (scheduler->timerPtr[i].count == 0)
                        {
                            scheduler->timerPtr[i].callbackPtr();
                        }
                    }
                }
            }

            // Heart of the scheduler code
            for (uint8_t i = 0; i < scheduler->tasksCount; i++)
            {

                scheduler->taskPtr[i].elapsed += scheduler->tick;
                
                if (scheduler->taskPtr[i].startFlag == 1)
                {
                    if (scheduler->taskPtr[i].elapsed >= scheduler->taskPtr[i].period)
                    {
                        scheduler->taskPtr[i].taskFunc();
                        scheduler->taskPtr[i].elapsed = 0;
                    }
                }
            }
        }

        if ((milliseconds() - control_timeout) >= scheduler->timeout)
        {
            break; // time is up
        }
    }
}

/**
 * @brief printf a messegas of the task with 500 millisecds
 *
 */
void xInit_500ms(void)
{
    printf("Init task 500 millisecond.\n");
}

/**
 * @brief printf a messegas of the task with 500 millisecds and increment a variable by 1
 *
 */
void xTask_500ms(void)
{
    static int loop = 0;
    printf("\nThis is a counter from task 500ms_: %d ", loop++);
}