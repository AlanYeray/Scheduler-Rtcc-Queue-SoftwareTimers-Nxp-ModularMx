/**
 * @file test_scheduler.c
 * @author Alan Yeray Olivas
 * @brief unity testing for scheduler functions
 * @version 0.1
 * @date 2024-05-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "unity.h"
#include "scheduler.h"

/**
 * @brief function returns milliseconds
 * 
 * @return long millisecondss
 */
extern long milliseconds(void);

/**
 * @brief printf messages "init 500ms task"
 * 
 */
extern void xInit_500ms(void);

/**
 * @brief set the task Task_500ms
 * 
 */
extern void xTask_500ms(void);

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
 * @brief function returns milliseconds
 * 
 */
void test_milliseconds__()
{
    uint8_t aux1, aux2 = 1;
    if (milliseconds() > aux2)
    {
        aux1 = 0;
    }
    TEST_ASSERT_EQUAL(0, aux1);
}

/**
 * @brief test if it set all the parameters in the structure
 * 
 */
void test__Sched__initScheduler()
{
    Sched_Scheduler sche1;
    Sched_Task tasks[2];

    Sched_initScheduler(&sche1);
    sche1.taskPtr = tasks;

    TEST_ASSERT_EQUAL(0, sche1.tasks);
    TEST_ASSERT_EQUAL(0, sche1.tasksCount);
    TEST_ASSERT_EQUAL(0, sche1.tick);
    TEST_ASSERT_EQUAL(0, sche1.timeout);
    TEST_ASSERT_EQUAL(tasks, sche1.taskPtr);
}

/**
 * @brief  test register one task
 * 
 */
void test__Sched__RegisterTask()
{
    Sched_Scheduler sche2;
    Sched_Task task[4];
    Sched_initScheduler(&sche2);
    sche2.tick = 100;
    sche2.tasks = 4;
    sche2.timeout = 10000;
    sche2.taskPtr = task;

    uint8_t task1 = Sched_registerTask(&sche2, xInit_500ms, xTask_500ms, 500);

    TEST_ASSERT_EQUAL(1, task1);

    TEST_ASSERT_EQUAL(500, sche2.taskPtr[0].period);

    TEST_ASSERT_EQUAL(&xInit_500ms, sche2.taskPtr[0].initFunc);

    TEST_ASSERT_EQUAL(&xTask_500ms, sche2.taskPtr[0].taskFunc);
}

/**
 * @brief test register fails register one task returns uint8_t 0
 * 
 */
void test__Sched__RegisterTask__return_0__()
{
    Sched_Scheduler sche2;
    Sched_Task task[4];
    Sched_initScheduler(&sche2);
    sche2.tick = 100;
    sche2.tasks = 4;
    sche2.timeout = 10000;
    sche2.taskPtr = task;

    TEST_ASSERT_EQUAL(0, Sched_registerTask(&sche2, xInit_500ms, xTask_500ms, 50));
}

/**
 * @brief  test register one task with parameter Null is correct
 * 
 */
void test__Sched__RegisterTask__registe_NULL__()
{
    Sched_Scheduler sche2;
    Sched_Task task[4];
    Sched_initScheduler(&sche2);
    sche2.tick = 100;
    sche2.tasks = 4;
    sche2.timeout = 10000;
    sche2.taskPtr = task;

    Sched_registerTask(&sche2, NULL, xTask_500ms, 500);
    TEST_ASSERT_EQUAL(NULL, sche2.taskPtr[0].initFunc);
}

/**
 * @brief test if it runs along branch
 * 
 */
void test_Sched__RegisterTask__branch__()
{
    Sched_Scheduler sche2;
    Sched_Task task[4];
    Sched_initScheduler(&sche2);
    sche2.tick = 3;
    sche2.tasks = 4;
    sche2.timeout = 100;
    sche2.taskPtr = task;

    TEST_ASSERT_EQUAL(3, Sched_registerTask(&sche2, xInit_500ms, xTask_500ms, 10));
}

/**
 * @brief  test if it stops a task
 * 
 */
void test__Sched_one_stopTask()
{
    Sched_Scheduler sche2;
    Sched_Task task[4];
    Sched_initScheduler(&sche2);
    sche2.tick = 100;
    sche2.tasks = 4;
    sche2.timeout = 10000;
    sche2.taskPtr = task;

    Sched_registerTask(&sche2, xInit_500ms, xTask_500ms, 500);

    uint8_t aux = 0;

    // Stop single tas0
    aux = Sched_stopTask(&sche2, 1);
    TEST_ASSERT_EQUAL(1, aux);
    TEST_ASSERT_EQUAL(0, sche2.tasksCount); // remaining tasks
    TEST_ASSERT_EQUAL(0, sche2.taskPtr[0].startFlag);
}

/**
 * @brief  test if it function returns uint8_t 0, function
 * 
 */
void test__Sched__stopTask__return__false__()
{
    Sched_Scheduler sche2;
    Sched_Task task[4];
    Sched_initScheduler(&sche2);
    sche2.tick = 100;
    sche2.tasks = 4;
    sche2.timeout = 10000;
    sche2.taskPtr = task;

    Sched_registerTask(&sche2, xInit_500ms, xTask_500ms, 500);

    sche2.taskPtr[0].startFlag = 0;

    TEST_ASSERT_EQUAL(0, Sched_stopTask(&sche2, 1)); // remaining tasks
}

/**
 * @brief  test returns uint8_t 1 starTask succeed 
 * 
 */
void test__Sched_one_startTask_return_value__()
{
    Sched_Scheduler sche2;
    Sched_Task task[4];
    Sched_initScheduler(&sche2);
    sche2.tick = 100;
    sche2.tasks = 4;
    sche2.timeout = 10000;
    sche2.taskPtr = task;

    uint8_t task1 = Sched_registerTask(&sche2, xInit_500ms, xTask_500ms, 500);

    uint8_t aux = Sched_startTask(&sche2, task1);

    TEST_ASSERT_EQUAL(0, aux); // false beceouse task 1 is already started
}

/**
 * @brief test if contional startFlag is 0 and return uint8_t 0, function failed
 * 
 */
void test__Sched_startTask_starFlag_0__()
{
    Sched_Scheduler sche2;
    Sched_Task task[4];
    Sched_initScheduler(&sche2);
    sche2.tick = 100;
    sche2.tasks = 4;
    sche2.timeout = 10000;
    sche2.taskPtr = task;

    sche2.taskPtr[0].startFlag = 0;
    uint8_t aux = Sched_startTask(&sche2, 1);

    TEST_ASSERT_EQUAL(0, aux); // false beceouse task 1 is already started
}

/**
 * @brief test if contional startFlag is 1 and return uint8_t 0, function succeed
 * 
 */
void test__Sched_startTask_starFlag_1__()
{
    Sched_Scheduler sche2;
    Sched_Task task[4];
    Sched_initScheduler(&sche2);
    sche2.tick = 100;
    sche2.tasks = 4;
    sche2.timeout = 10000;
    sche2.taskPtr = task;

    Sched_registerTask(&sche2, xInit_500ms, xTask_500ms, 500);
    uint8_t aux = Sched_startTask(&sche2, 1);

    TEST_ASSERT_EQUAL(1, aux); // false beceouse task 1 is already started
}

/**
 * @brief test parameters passed were succeed
 * 
 */
void test__Sched__periodTask_param__check()
{
    Sched_Scheduler sche2;
    Sched_Task task[4];
    Sched_initScheduler(&sche2);
    sche2.tick = 100;
    sche2.tasks = 4;
    sche2.timeout = 10000;
    sche2.taskPtr = task;

    uint8_t task1 = Sched_registerTask(&sche2, xInit_500ms, xTask_500ms, 500);

    uint8_t aux = Sched_periodTask(&sche2, 1, 2000);
    TEST_ASSERT_EQUAL(2000, sche2.taskPtr[0].period);
}

/**
 * @brief  test returns false when function failed
 * 
 */
void test__Sched__periodTask_return__false__()
{
    Sched_Scheduler sche2;
    Sched_Task task[4];
    Sched_initScheduler(&sche2);
    sche2.tick = 100;
    sche2.tasks = 4;
    sche2.timeout = 10000;
    sche2.taskPtr = task;

    uint8_t task1 = Sched_registerTask(&sche2, xInit_500ms, xTask_500ms, 500);

    uint8_t aux = Sched_periodTask(&sche2, task1, 99);
    TEST_ASSERT_EQUAL(0, aux);
}

/**
 * @brief test runs along branch both conditionals are failed
 * 
 */
void test__Sched__periodTask_branch__both_negative__()
{
    Sched_Scheduler sche2;
    Sched_Task task[4];
    Sched_initScheduler(&sche2);
    sche2.tick = 98;
    sche2.tasks = 4;
    sche2.timeout = 10000;
    sche2.taskPtr = task;

    uint8_t task1 = Sched_registerTask(&sche2, xInit_500ms, xTask_500ms, 99);

    uint8_t aux = Sched_periodTask(&sche2, task1, 99);
    TEST_ASSERT_EQUAL(0, aux);
}

/**
 * @brief test parameters are incorrect and functions failed
 * 
 */
void test_Sched_registerTimer_failed_conditions_(){

     Sched_Scheduler sche3;
    Sched_Task task[4];
    Sched_initScheduler(&sche3);
    sche3.tick = 100;
    sche3.tasks = 4;
    sche3.timeout = 10000;
    sche3.taskPtr = task;

    Sched_Timer temp[2];
    sche3.timeout = 1000;
    sche3.timers = 1;
    sche3.timerPtr = temp;

    
    TEST_ASSERT_EQUAL(1,Sched_registerTimer(&sche3,150,xInit_500ms));

}

/**
 * @brief test returns count of the timer previously registered
 * 
 */
void test_getTimer_return_count__()
{

    Sched_Scheduler sche3;
    Sched_Task task[4];
    Sched_initScheduler(&sche3);
    sche3.tick = 100;
    sche3.tasks = 4;
    sche3.timeout = 10000;
    sche3.taskPtr = task;

    Sched_Timer temp[2];
    sche3.timeout = 100000;
    sche3.timers = 1;
    sche3.timerPtr = temp;

    sche3.timersCount = 2;
    uint8_t timer = Sched_registerTimer(&sche3, 10, xTask_500ms);

    
}

/**
 * @brief test function retuns uint8_t 0 if timer has not been registered
 * 
 */
void test_getTimer_return__0___()
{

    Sched_Scheduler sche3;
    Sched_Task task[4];
    Sched_initScheduler(&sche3);
    sche3.tick = 100;
    sche3.tasks = 4;
    sche3.timeout = 10000;
    sche3.taskPtr = task;

    Sched_Timer temp[2];
    sche3.timeout = 10000;
    sche3.timers = 1;
    sche3.timerPtr = temp;

    sche3.timersCount = 2;
    uint8_t timer = 3;

    TEST_ASSERT_EQUAL(0, Sched_getTimer(&sche3, timer));
}

/**
 * @brief test if functions was succeed, reload the timeout/count of the timer, 
 * 
 */
void test_Sched_reloadTimer_return_1__()
{
    Sched_Scheduler sche3;
    Sched_Task task[4];
    Sched_initScheduler(&sche3);
    sche3.tick = 100;
    sche3.tasks = 4;
    sche3.timeout = 10000;
    sche3.taskPtr = task;

    Sched_Timer temp[2];
    sche3.timeout = 10000;
    sche3.timers = 1;
    sche3.timerPtr = temp;

    sche3.timersCount = 2;
    uint8_t timer = Sched_registerTimer(&sche3, 1000, xTask_500ms);

    TEST_ASSERT_EQUAL(1, Sched_reloadTimer(&sche3, timer, 1000));
}

/**
 * @brief test if functions can not reaload the timers and returns a 0
 * 
 */
void test_Sched_reloadTimer_return_0__()
{
    Sched_Scheduler sche3;
    Sched_Task task[4];
    Sched_initScheduler(&sche3);
    sche3.tick = 100;
    sche3.tasks = 4;
    sche3.timeout = 10000;
    sche3.taskPtr = task;

    Sched_Timer temp[2];
    sche3.timeout = 10000;
    sche3.timers = 1;
    sche3.timerPtr = temp;

    sche3.timersCount = 1;
    uint8_t xtimer1 = 2;

    TEST_ASSERT_EQUAL(0, Sched_reloadTimer(&sche3, xtimer1, 1000));
}

/**
 * @brief test runs along function
 * 
 */
void test_Sched_startTimer__general__()
{
    Sched_Scheduler sche3;
    Sched_Task task[4];
    Sched_initScheduler(&sche3);
    sche3.tick = 100;
    sche3.tasks = 4;
    sche3.timeout = 1000;
    sche3.taskPtr = task;

    Sched_Timer temp[2];
    sche3.timeout = 1000;
    sche3.timers = 1;
    sche3.timerPtr = temp;

    uint8_t timer = Sched_registerTimer(&sche3, 1000, xTask_500ms);

    TEST_ASSERT_EQUAL(1, Sched_startTimer(&sche3, timer));
}

/**
 * @brief test runs along stopTimer
 * 
 */
void test_Sched_stopTimer__general__()
{
    Sched_Scheduler sche3;
    Sched_Task task[4];
    Sched_initScheduler(&sche3);
    sche3.tick = 100;
    sche3.tasks = 4;
    sche3.timeout = 10000;
    sche3.taskPtr = task;

    Sched_Timer temp[2];
    sche3.timeout = 10000;
    sche3.timers = 1;
    sche3.timerPtr = temp;

    uint8_t timer = Sched_registerTimer(&sche3, 1000, xTask_500ms);

    TEST_ASSERT_EQUAL(1, Sched_stopTimer(&sche3, timer));
}

/**
 * @brief test stoptimer failed and returns 0
 * 
 */
void test_Sched_stopTimer__return_0__()
{
    Sched_Scheduler sche3;
    Sched_Task task[4];
    Sched_initScheduler(&sche3);
    sche3.tick = 100;
    sche3.tasks = 4;
    sche3.timeout = 10000;
    sche3.taskPtr = task;

    Sched_Timer temp[2];
    sche3.timeout = 10000;
    sche3.timers = 1;
    sche3.timerPtr = temp;

    sche3.timersCount = 1;
    uint8_t timer = 2;

    TEST_ASSERT_EQUAL(0, Sched_stopTimer(&sche3, timer));
}

/**
 * @brief test StartSchedulers
 * 
 */
void test_Sched_startScheduler__general__()
{
    Sched_Scheduler sche3;
    Sched_Task task[4];
    Sched_initScheduler(&sche3);
    sche3.tick = 1;
    sche3.tasks = 4;
    sche3.timeout = 10;
    sche3.taskPtr = task;

    Sched_Timer temp[2];
    sche3.timeout = 11;
    sche3.timers = 1;
    sche3.timerPtr = temp;

    Sched_registerTask(&sche3, xInit_500ms, xTask_500ms, 500);
    uint8_t timer = Sched_registerTimer(&sche3, 1000, xInit_500ms);
    Sched_startTimer(&sche3, timer);

    Sched_startScheduler(&sche3);

    TEST_ASSERT_EQUAL(11, sche3.timeout);
}


/**
 * @brief test startTimers runs along branch flag in 1
 * 
 */
void test_Sched_startTimer_branch_flag_1_()
{
    Sched_Scheduler sche3;
    Sched_Task task[4];
    Sched_initScheduler(&sche3);
    sche3.tick = 100;
    sche3.tasks = 4;
    sche3.timeout = 10000;
    sche3.taskPtr = task;

    Sched_Timer temp[2];
    sche3.timeout = 10000;
    sche3.timers = 1;
    sche3.timerPtr = temp;

    uint8_t timer = Sched_registerTimer(&sche3, 1000, xTask_500ms);
    sche3.timerPtr[0].startFlag = 1;
    Sched_startTimer(&sche3, timer);

    TEST_ASSERT_EQUAL(1, sche3.timerPtr[0].startFlag);
}

/**
 * @brief test starScheduler runs along branch with no timers init
 * 
 */
void test_starScheduler_branch_no_timers_()
{
    Sched_Scheduler sche3;
    Sched_Task task[4];
    Sched_initScheduler(&sche3);
    sche3.tick = 1;
    sche3.tasks = 4;
    sche3.timeout = 10;
    sche3.taskPtr = task;

    Sched_Timer temp[2];
    sche3.timeout = 11;
    sche3.timers = 0;
    sche3.timerPtr = temp;

    Sched_registerTask(&sche3, xInit_500ms, xTask_500ms, 500);

    Sched_startScheduler(&sche3);

    TEST_ASSERT_EQUAL(11, sche3.timeout);
}

/**
 * @brief test starScheduler runs along branch timers with flag in 1
 * 
 */
void test_starScheduler_branch_timers_flag_1_()
{
    Sched_Scheduler sche3;
    Sched_Task task[4];
    Sched_initScheduler(&sche3);
    sche3.tick = 1;
    sche3.tasks = 4;
    sche3.timeout = 10;
    sche3.taskPtr = task;

    Sched_Timer temp[2];
    sche3.timeout = 11;
    sche3.timers = 1;
    sche3.timerPtr = temp;

    Sched_registerTask(&sche3, xInit_500ms, xTask_500ms, 500);
    uint8_t timer = Sched_registerTimer(&sche3, 1000, xInit_500ms);
    Sched_stopTimer(&sche3, timer);
    Sched_startScheduler(&sche3);

    TEST_ASSERT_EQUAL(11, sche3.timeout);
}

/**
 * @brief test starScheduler runs along branch use element of the structure *taskFunc
 * 
 */
void test_Sched_startScheduler__branch_use_taskFunc__()
{
    Sched_Scheduler sche3;
    Sched_Task task[4];
    Sched_initScheduler(&sche3);
    sche3.tick = 1;
    sche3.tasks = 4;
    sche3.timeout = 100;
    sche3.taskPtr = task;

    Sched_Timer temp[2];
    sche3.timeout = 11;
    sche3.timers = 1;
    sche3.timerPtr = temp;

    Sched_registerTask(&sche3, xInit_500ms, xTask_500ms, 10);

    Sched_startScheduler(&sche3);

    TEST_ASSERT_EQUAL(11, sche3.timeout);
}

/**
 * @brief  test starchScheduler runs along branch use a element of the structhre *CallbackPtr
 * 
 */
void test_Sched_startScheduler__branch_use_callbackPtr__()
{
    Sched_Scheduler sche3;
    Sched_Task task[4];
    Sched_initScheduler(&sche3);
    sche3.tick = 1;
    sche3.tasks = 4;
    sche3.timeout = 100;
    sche3.taskPtr = task;

    Sched_Timer temp[2];
    sche3.timeout = 11;
    sche3.timers = 1;
    sche3.timerPtr = temp;

    Sched_registerTask(&sche3, xInit_500ms, xTask_500ms, 10);
    uint8_t timer1 = Sched_registerTimer(&sche3, 10, xInit_500ms);
    Sched_startTimer(&sche3, timer1);
    Sched_startScheduler(&sche3);

    TEST_ASSERT_EQUAL(11, sche3.timeout);
}

/**
 * @brief test runs along conditionals startFlag and elapsed
 * 
 */
void test_Sched_startScheduler__branch_test_condition_split_flag_and_elapsed__()
{
    Sched_Scheduler sche3;
    Sched_Task task[4];
    Sched_initScheduler(&sche3);
    sche3.tick = 1;
    sche3.tasks = 4;
    sche3.timeout = 1000;
    sche3.taskPtr = task;

    Sched_Timer temp[2];
    sche3.timeout = 100;
    sche3.timers = 1;
    sche3.timerPtr = temp;

    Sched_registerTask(&sche3, xInit_500ms, xTask_500ms, 20);
   // sche3.taskPtr[0].elapsed = 200;
    Sched_startScheduler(&sche3);

    TEST_ASSERT_EQUAL(100, sche3.timeout);
}

/**
 * @brief test functions runs along branch startflag in 0
 * 
 */
void test_Sched_startScheduler__branch_flag_0__()
{
    Sched_Scheduler sche3;
    Sched_Task task[4];
    Sched_initScheduler(&sche3);
    sche3.tick = 1;
    sche3.tasks = 4;
    sche3.timeout = 1000;
    sche3.taskPtr = task;

    Sched_Timer temp[2];
    sche3.timeout = 100;
    sche3.timers = 1;
    sche3.timerPtr = temp;

    Sched_registerTask(&sche3, xInit_500ms, xTask_500ms, 20);
    sche3.taskPtr[0].startFlag = 0;
    Sched_startScheduler(&sche3);

    TEST_ASSERT_EQUAL(100, sche3.timeout);
}

/**
 * @brief test xtask_500ms
 * 
 */
void test_xtask_500ms_()
{
    xTask_500ms();
}