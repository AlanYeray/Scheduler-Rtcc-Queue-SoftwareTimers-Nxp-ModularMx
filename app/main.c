/**
 * @file main.c
 * @author Alan Yeray Olivas 
 * @brief here we used all the interfaces
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
#include "rtcc.h"
#include "scheduler.h"

/**
 * @brief Structure to store time and date
 */
typedef struct _Message
{
    uint8_t msg;
    uint8_t hour;
    uint8_t minutes;
    uint8_t seconds;
    uint8_t day;
    uint8_t wday;
    uint8_t month;
    uint16_t year;
} Message;

/**
 * @defgroup <control> control macros for timers structures
 * 
 */
#define TASKS_N 2
#define TICK_VAL 100
#define TIMERS_N 3

/**
 * @defgroup <control messages> define who messages will be delivered
 * 
 */
#define MSG_1 1
#define MSG_0 0

/**
 * @brief initialization of structres to run software timers , queues and the scheduler
 * 
 */
static Sched_Task tasks[TASKS_N];
static Sched_Scheduler Sche;
static Rtcc_Clock rtccClock;
static Que_Queue rtccQueue;
static Sched_Timer timer[3];

/**
 * @brief Register timers to scheduler
 * 
 */
uint8_t Timer0, Timer1;

void Init_500ms(void);
void Init_1000ms(void);
void Task_500ms(void);
void Task_1000ms(void);
void Callback();
void Callback_set_hour_date();

int main()
{
    static Message Messages[6u];

    /*create the queue to store as max 6 items*/
    rtccQueue.Buffer = Messages;
    rtccQueue.Elements = 6;
    rtccQueue.Size = sizeof(Message);
    Queue_initQueue(&rtccQueue);

    /*init the scheduler with two tasks and a tick time of 100ms and run for 10 seconds only*/
    Sched_initScheduler(&Sche);
    Sche.tick = TICK_VAL;
    Sche.tasks = TASKS_N;
    Sche.taskPtr = tasks;
    Sche.timeout = 100000;
    Sche.timers = TIMERS_N;
    Sche.timerPtr = timer;

    /*register two task with thier corresponding init fucntions and their periodicyt, 100ms and 500ms*/
    Sched_registerTask(&Sche, Init_500ms, Task_500ms, 500);
    Sched_registerTask(&Sche, Init_1000ms, Task_1000ms, 1000);
    Timer0 = Sched_registerTimer(&Sche, 1000, Callback);
    Timer1 = Sched_registerTimer(&Sche, 30000, Callback_set_hour_date);
    Sched_startTimer(&Sche, Timer0);
    Sched_startTimer(&Sche, Timer1);

    /*run the scheduler for the mount of time stablished in Sche.timeout*/
    Sched_startScheduler(&Sche);

    return 0;
}

/**
 * @brief init clock , set time and date
 * 
 * print a message
 */
void Init_500ms(void)
{
    Rtcc_clockInit(&rtccClock);
    Rtcc_setTime(&rtccClock, 12, 30, 0);
    Rtcc_setDate(&rtccClock, 24, 6, 1984);
    printf("Init task 500 millisecond\n");
}

/**
 * @brief print a message -> init task 1000 millisecods
 * 
 */
void Init_1000ms(void)
{
    printf("Init task 1000 millisecond\n");
}

/**
 * @brief read the queue and select which type of message is it
 * @param none
 * 
 */
void Task_500ms(void)
{
    Message msgToRead;

    /*Read the message in the queue*/
    Queue_readData(&rtccQueue, &msgToRead); // hour

    if (msgToRead.msg == MSG_1)
    {
        printf("Time - %d:%d:%d\n", msgToRead.hour, msgToRead.minutes, msgToRead.seconds);
    }
    else if (msgToRead.msg == MSG_0)
    {
        printf("Date - %d/%d/%d\n", msgToRead.day, msgToRead.month, msgToRead.year);
    }
}

/**
 * @brief obtain time and write one time the queue
 * @param none
 * 
 */
void Task_1000ms(void)
{
    Message time, date;

    /*Clock periodic task*/
    // Rtcc_periodicTask(&rtccClock);
    /*get time and date*/
    time.msg = MSG_1;
    date.msg = MSG_0;

    Rtcc_getTime(&rtccClock, &time.hour, &time.minutes, &time.seconds);
    Queue_writeData(&rtccQueue, &time);

    Rtcc_getDate(&rtccClock, &date.day, &date.month, &date.year, &date.wday);
    Queue_writeData(&rtccQueue, &date);
}

/**
 * @brief do one time periodicTask an realod the timer
 * @param none
 * 
 */
void Callback()
{
    // Run the Rtcc periodic task every second  using a software timer and a callback.
    Rtcc_periodicTask(&rtccClock);
    Sched_reloadTimer(&Sche, Timer0, 1000);

    /*
    using another software timer to set new time and date every 30s, 60s and 180s
    ( choose three different values ), make these changes in a periodic way
    (30s, 60s, 180s, 30s 60s, so on …. ) in the timer callback  */
}

/**
 * @brief changes the hour and time in diffets periods
 * @param none
 */
void Callback_set_hour_date()
{
    static uint8_t control_value = 2;

    if (control_value == 1)
    {
        Queue_flushQueue(&rtccQueue);
        Rtcc_setTime(&rtccClock, 1, 2, 0);
        Rtcc_setDate(&rtccClock, 4, 4, 1999);
        Sched_reloadTimer(&Sche, Timer1, 30000);
        printf(" set 30s \n");
        control_value = 2;
    }
    else if (control_value == 2)
    {
        Queue_flushQueue(&rtccQueue);
        Rtcc_setTime(&rtccClock, 10, 10, 0);
        Rtcc_setDate(&rtccClock, 6, 6, 2024);
        Sched_reloadTimer(&Sche, Timer1, 60000);
        printf(" set 60s \n");
        control_value = 3;
    }
    else
    {
        Queue_flushQueue(&rtccQueue);
        Rtcc_setTime(&rtccClock, 20, 20, 0);
        Rtcc_setDate(&rtccClock, 10, 10, 2050);
        Sched_reloadTimer(&Sche, Timer1, 180000);
        printf(" set 180s \n");
        control_value = 1;
    }
}
