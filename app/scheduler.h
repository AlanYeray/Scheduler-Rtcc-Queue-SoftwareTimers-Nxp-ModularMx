#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct _Schedched_Timer
{
    uint32_t timeout;          /*!< timer timeout to decrement and reload when the timer is re-started */
    uint32_t count;             /*!< actual timer decrement count */
    uint8_t startFlag;         /*!< flag to start timer count */
    void (*callbackPtr)(void); /*!< pointer to callback function function */
} Sched_Timer;

typedef struct _task
{
    uint32_t period;        /*How often the task shopud run in ms*/
    uint32_t elapsed;       /*the cuurent elapsed time*/
    uint8_t startFlag;      /*flag to run task*/
    void (*initFunc)(void); /*pointer to init task function*/
    void (*taskFunc)(void); /*pointer to task function*/
    uint8_t id;
    uint32_t lastTime;
} Sched_Task;

/**
 * @brief structure to contain everything to run a scheduler
 * 
 */
typedef struct _scheduler
{
    uint8_t tasks;           /*number of task to handle*/
    uint32_t tick;           /*the time base in ms*/
    uint32_t timeout;        /*the number of milliseconds the scheduler should run*/
    uint8_t tasksCount;      /*internal task counter*/
    Sched_Task *taskPtr;  /*Pointer to buffer for the TCB tasks*/
    uint8_t timers;          /*number of software timer to use*/
    uint8_t timersCount;
    Sched_Timer *timerPtr; /*Pointer to buffer timer array*/
    uint32_t actualTime;
} Sched_Scheduler;

/**
 * @brief init al elements of the structure to zero
 * 
 * @param scheduler [in] structure
 */
void Sched_initScheduler(Sched_Scheduler *scheduler);

/**
 * @brief register a new task
 * 
 * @param scheduler [in] structure
 * @param initPtr [in] function to init the functions to manage (taskPtr)
 * @param taskPtr [in] function to manage
 * @param period [in] period to do the function
 * @retval uint8_t if it was succeeded or failed
 */
uint8_t Sched_registerTask(Sched_Scheduler *scheduler, void (*initPtr)(void), void (*taskPtr)(void), uint32_t period);

/**
 * @brief stop the task, prevents the scheduler from processing it
 * 
 * @param scheduler [in] structure
 * @param task [in] the number of the task previusly registered
 * @retval uint8_t if it was succeeded or failed
 */
uint8_t Sched_stopTask(Sched_Scheduler *scheduler, uint8_t task);

/**
 * @brief start the task,  the scheduler can processing it
 *          
 *          set the flag
 * 
 * @param scheduler [in] structure
 * @param task [in] the number of the task previusly registered
 * @retval uint8_t if it was succeeded or failed
 */
uint8_t Sched_startTask(Sched_Scheduler *scheduler, uint8_t task);

/**
 * @brief realod the period of the task and set the flag in 1
 * 
 * @param scheduler [in] structure
 * @param task [in] the number of the task previusly registered
 * @param period [in] the time to start to processing it
 * @retval uint8_t if it was succeeded or failed
 */
uint8_t Sched_periodTask(Sched_Scheduler *scheduler, uint8_t task, uint32_t period);

/**
 * @brief function to runs all the tasks and the timers
 * 
 *      main function of the scheduler
 * 
 * @param scheduler [in] structure
 */
void Sched_startScheduler(Sched_Scheduler *scheduler);


/**
 * @brief register a new software timer
 * 
 * @param scheduler [in] structure
 * @param timeout [in] the max count to wait
 * @param callbackPtr [in] the function to run when the timeout is out
 * @retval uint8_t if it was succeeded or failed 
 */
uint8_t Sched_registerTimer(Sched_Scheduler *scheduler, uint32_t timeout, void (*callbackPtr)(void));

/**
 * @brief  return the count of the timer
 * 
 * @param scheduler [in] structure
 * @param timer [in] the function to run when the timeout is out
 * @retval uint32_t return the milliseconds// count
 */
uint32_t Sched_getTimer(Sched_Scheduler *scheduler, uint8_t timer);

/**
 * @brief change the value for the timeout and set flag in 1
 * 
 * @param scheduler [in] structure
 * @param timer [in]s the number of the task previusly registered
 * @param timeout [in] the max count to wait
 * @retval uint8_t if it was succeeded or failed 
 */
uint8_t Sched_reloadTimer(Sched_Scheduler *scheduler, uint8_t timer, uint32_t timeout);

/**
 * @brief start timer, set flag in 1 and reaload the timeout
 * 
 * @param scheduler [in] structure
 * @param timer [in] the number of the task previusly registered
 * @return  uint8_t if it was succeeded or failed 
 */
uint8_t Sched_startTimer(Sched_Scheduler *scheduler, uint8_t timer);

/**
 * @brief stop the timer and clear the flag
 * 
 * @param scheduler [in] structure
 * @param timer [in] the number of the task previusly registered
 * @return uint8_t if it was succeeded or failed 
 */
uint8_t Sched_stopTimer(Sched_Scheduler *scheduler, uint8_t timer);



#endif