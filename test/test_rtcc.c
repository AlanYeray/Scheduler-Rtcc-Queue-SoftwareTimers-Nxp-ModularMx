/**
 * @file test_rtcc.c
 * @author Alan Yeray Olivas Díaz
 * @brief   unity testing for rtcc.c functions
 * @version 0.1
 * @date 2024-05-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */


#include "unity.h"
#include "rtcc.h"

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
 * @brief  set sec, min, hour,day of the month, numerber of the month and the year.
 *
 *  
 */
void test__clockInit__set_all_values()
{
    Rtcc_Clock test;
    uint8_t two = 2;
    uint8_t tree = 3;
    uint8_t four = 4;

    Rtcc_clockInit(&test);
    TEST_ASSERT_EQUAL(0, test.tm_sec);
    TEST_ASSERT_EQUAL(0, test.tm_min);
    TEST_ASSERT_EQUAL(0, test.tm_hour);

    TEST_ASSERT_EQUAL(1, test.tm_mday);
    TEST_ASSERT_EQUAL(1, test.tm_mon);
    TEST_ASSERT_EQUAL(1900, test.tm_year);
}

/**
 * @brief function test compare parameters of function Rtcc_setTime()
 * 
 */
void test__setTime__pass__()
{

    Rtcc_Clock test;
    uint8_t two = 2;
    uint8_t tree = 3;
    uint8_t four = 4;

    Rtcc_setTime(&test, two, tree, four);
    TEST_ASSERT_EQUAL(two, test.tm_hour);
    TEST_ASSERT_EQUAL(tree, test.tm_min);
    TEST_ASSERT_EQUAL(four, test.tm_sec);
}

/**
 * @brief test when function is false and return 0 in fuction Rtcc_setTime()
 * 
 */
void test_setTime__return__false_hour_()
{
    Rtcc_Clock test;
    uint8_t two = 70;
    uint8_t tree = 70;
    uint8_t four = 70;

    TEST_ASSERT_EQUAL(0, Rtcc_setTime(&test, two, tree, four));
}

/**
 * @brief test return 0 when minutes are wrong in fuction Rtcc_setTime()
 * 
 */
void test_setTime__return__false_minutes_()
{
    Rtcc_Clock test;
    uint8_t two = 12;
    uint8_t tree = 70;
    uint8_t four = 70;

    TEST_ASSERT_EQUAL(0, Rtcc_setTime(&test, two, tree, four));
}

/**
 * @brief test return 0 when seconds are wrong in fuction Rtcc_setTime()
 * 
 */
void test_setTime__return__false_seconds_()
{
    Rtcc_Clock test;
    uint8_t two = 12;
    uint8_t tree = 12;
    uint8_t seconds = 80;

    TEST_ASSERT_EQUAL(0, Rtcc_setTime(&test, two, tree, seconds));
}

/**
 * @brief test return value uint8_t in function Rtcc_setTime()
 * 
 */
void test__setTime__return__v()
{
    Rtcc_Clock test;
    uint8_t two = 2;
    uint8_t tree = 3;
    uint8_t four = 4;

    uint8_t return_test = Rtcc_setTime(&test, two, tree, four);

    TEST_ASSERT_EQUAL(1, return_test);
}

/**
 * @brief test runs along the branch and pass condition day in function Rtcc_setDate()
 * 
 */
void test__setDate_branch_pass_condition_day()
{
    Rtcc_Clock test;
    uint8_t day = 1;
    uint8_t month = 5;
    uint16_t year = 2000;

    Rtcc_setDate(&test, day, month, year);

    TEST_ASSERT_EQUAL(day, test.tm_mday);
}

/**
 * @brief test runs along the branch and not pass condition day in function Rtcc_setDate()
 * 
 */
void test__setDate_branch_not_pass_condition_day()
{
    Rtcc_Clock test;
    uint8_t day = 32;
    uint8_t month = 5;
    uint16_t year = 2000;

    Rtcc_setDate(&test, day, month, year);

    TEST_ASSERT_EQUAL(0, test.tm_mday);
}

/**
 * @brief test runs along the branch  pass condition month in function Rtcc_setDate()
 * 
 */
void test__setDate_branch__pass_condition_month()
{
    Rtcc_Clock test;
    uint8_t day = 1;
    uint8_t month = 14;
    uint16_t year = 2000;

    Rtcc_setDate(&test, day, month, year);

    TEST_ASSERT_EQUAL(1, test.tm_mday);
}

/**
 * @brief test runs along the branch and not pass condition year in function Rtcc_setDate()
 * 
 */
void test__setDate_branch__not_pass_condition_year()
{
    Rtcc_Clock test;
    uint8_t day = 1;
    uint8_t month = 14;
    uint16_t year = 2000;

    Rtcc_setDate(&test, day, month, year);

    TEST_ASSERT_EQUAL(1, test.tm_mday);
}

/**
 * @brief test if bit al_set was changed is function Rtcc_setAlarm()
 * 
 */
void test__setAlarm_bit_al_set__change()
{
    Rtcc_Clock test;

    Rtcc_setAlarm(&test, 1, 1);

    TEST_ASSERT_EQUAL(1, test.ctrl.bits.al_set);
}

/**
 * @brief test when pass the values hour and minutes in functuin Rtcc_setAlarm()
 * 
 */
void test__setAlarm__passValues__()
{
    Rtcc_Clock test;
    uint8_t two = 2;
    uint8_t tree = 3;
    uint8_t four = 4;

    Rtcc_setAlarm(&test, two, tree);

    TEST_ASSERT_EQUAL(two, test.al_hour);
    TEST_ASSERT_EQUAL(tree, test.al_min);
}

/**
 * @brief test when values are wrong and not pass values in fuction RTcc_setAlarm()
 * 
 */
void test__setAlarm__wrong_param_hour_()
{
    Rtcc_Clock test;
    uint8_t two = 0;
    uint8_t tree = 3;
    Rtcc_setAlarm(&test, two, tree);
}

/**
 * @brief test return values uint8_t in function Rtcc_setAlarm()
 * 
 */
void test__setAlarm__returnValues__()
{
    Rtcc_Clock test;
    uint8_t two = 2;
    uint8_t tree = 3;
    uint8_t four = 4;

    uint8_t return_test = Rtcc_setAlarm(&test, two, tree);

    TEST_ASSERT_EQUAL(1, return_test);
}

/**
 * @brief test return false in hours in function Rtcc_setAlarm()
 * 
 */
void test__setAlarm__returnHours__()
{
    Rtcc_Clock test;
    uint8_t two = 30;
    uint8_t tree = 0;

    TEST_ASSERT_EQUAL(0, Rtcc_setAlarm(&test, two, tree));
}

/**
 * @brief test return false in minutes in function Rtcc_setAlarm()
 * 
 */
void test__setAlarm__returnMinutes__()
{
    Rtcc_Clock test;
    uint8_t hours = 23;
    uint8_t seconds = 0;

    TEST_ASSERT_EQUAL(1, Rtcc_setAlarm(&test, hours, seconds));
}

/**
 * @brief test runs along the brach not pass minutes in function Rtcc_setAlarm()
 * 
 */
void test_SETAlarm__branch_not_pass_minutes_()
{

    Rtcc_Clock clock;
    uint8_t hour = 1;
    uint8_t minutes = 61;
    TEST_ASSERT_EQUAL(0, Rtcc_setAlarm(&clock, hour, minutes));
}

/**
 * @brief test general pass all values correct in function Rtcc_setAlarm()
 * 
 */
void test__getAlarm__values__param__()
{
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

    Rtcc_Clock clock;
    Message tempo;

    uint8_t two = 2;
    uint8_t tree = 3;

    Rtcc_setAlarm(&clock, two, tree);

    clock.ctrl.bits.al_active = 1;

    TEST_ASSERT_EQUAL(1, Rtcc_getAlarm(&clock, &tempo.hour, &tempo.minutes));
}

/**
 * @brief test return 0 uint8_t in function Rtcc_setAlarm()
 * 
 */
void test__getAlarm__return_0__()
{
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

    Rtcc_Clock clock;
    Message tempo;

    uint8_t two = 2;
    uint8_t tree = 3;

    Rtcc_setAlarm(&clock, two, tree);

    clock.ctrl.bits.al_active = 0;

    TEST_ASSERT_EQUAL(0, Rtcc_getAlarm(&clock, &tempo.hour, &tempo.minutes));
}

/**
 * @brief test if values were passed in function Rtcc_getTime()
 * 
 */
void test__getTime__check__memorieAddress__()
{
    Rtcc_Clock test;

    test.tm_sec = 10;
    test.tm_min = 20;
    test.tm_hour = 23;

    uint8_t sec, min, hour;

    Rtcc_clockInit(&test);
    Rtcc_getTime(&test, &sec, &min, &hour);

    TEST_ASSERT_EQUAL(sec, test.tm_sec);
    TEST_ASSERT_EQUAL(min, test.tm_min);
    TEST_ASSERT_EQUAL(hour, test.tm_hour);
}

/**
 * @brief test if values were passed in function Rtcc_getDate()
 * 
 */
void test__getDate__check__memorieAddress__()
{
    Rtcc_Clock test;
    test.tm_mday = 1;
    test.tm_mon = 2;
    test.tm_year = 1901;
    test.tm_wday = 6;
    uint8_t mday, mon, wday;
    uint16_t year;

    Rtcc_clockInit(&test);
    Rtcc_getDate(&test, &mday, &mon, &year, &wday);

    TEST_ASSERT_EQUAL(mday, test.tm_mday);
    TEST_ASSERT_EQUAL(mon, test.tm_mon);
    TEST_ASSERT_EQUAL(year, test.tm_year);
    TEST_ASSERT_EQUAL(wday, test.tm_wday);
}

/**
 * @brief test if function clear bits al_active and al_set 
 * 
 */
void test__clearAlarm__clearBits__()
{
    Rtcc_Clock test;
    Rtcc_clockInit(&test);
    Rtcc_clearAlarm(&test);

    TEST_ASSERT_EQUAL(0, test.ctrl.bits.al_active);

    TEST_ASSERT_EQUAL(0, test.ctrl.bits.al_set);
}

/**
 * @brief test if function return 0 uint8_t 
 * 
 */
void test__getAlarmFlag__returnValue__()
{
    Rtcc_Clock test;
    Rtcc_clockInit(&test);
    uint8_t test_value = Rtcc_getAlarmFlag(&test);

    TEST_ASSERT_EQUAL(0, test.ctrl.bits.al_active);
}

/**
 * @brief test when one second left to change
 * 
 */
void test__periodicTask__call59_times__()
{
    Rtcc_Clock test;
    Rtcc_clockInit(&test);

    test.tm_sec = 59;
    Rtcc_periodicTask(&test);

    TEST_ASSERT_EQUAL(0, test.tm_sec);
    TEST_ASSERT_EQUAL(1, test.tm_min);
}

/**
 * @brief test if hour change
 * 
 */
void test__periodicTask__testHour__()
{

    Rtcc_Clock test;
    Rtcc_clockInit(&test);
    test.tm_sec = 59;
    test.tm_min = 59;

    Rtcc_periodicTask(&test);

    TEST_ASSERT_EQUAL(0, test.tm_min);
    TEST_ASSERT_EQUAL(1, test.tm_hour);
}

/**
 * @brief test if day change
 * 
 */
void test__periodicTask__Test_1_day__()
{
    Rtcc_Clock test;
    Rtcc_clockInit(&test);
    test.tm_sec = 59;
    test.tm_min = 59;
    test.tm_hour = 23;
    Rtcc_periodicTask(&test);

    TEST_ASSERT_EQUAL(2, test.tm_mday);
}


/**
 * @brief test if month change
 * 
 */
void test__periodicTask__test_one_month__()
{
    Rtcc_Clock test;
    Rtcc_clockInit(&test);
    test.tm_sec = 59;
    test.tm_min = 59;
    test.tm_hour = 23;
    test.tm_mon = 12;
    Rtcc_periodicTask(&test);

    TEST_ASSERT_EQUAL(1, test.tm_mday);
}

/**
 * @brief  test if weekday change
 * 
 */
void test__periodicTask__testWeekday__()
{
    Rtcc_Clock test;
    Rtcc_clockInit(&test);
    test.tm_sec = 59;
    test.tm_min = 59;
    test.tm_hour = 23;
    Rtcc_periodicTask(&test);

    TEST_ASSERT_EQUAL(0, test.tm_wday);
}

/**
 * @brief test if the bit was set
 * 
 */
void test__periodicTask__Bit_al_actice__()
{
    Rtcc_Clock test;
    Rtcc_clockInit(&test);
    test.tm_sec = 59;

    test.tm_min = 59;
    test.al_min = 0;

    test.tm_hour = 22;
    test.al_hour = 23;
    test.ctrl.bits.al_set = 1;
    Rtcc_periodicTask(&test);

    TEST_ASSERT_EQUAL(1, test.ctrl.bits.al_active);
}

/**
 * @brief test if day change
 * 
 */
void test__periodicTask__tm_days__()
{
    Rtcc_Clock test;
    Rtcc_clockInit(&test);
    test.tm_sec = 59;
    test.tm_min = 59;
    test.tm_hour = 23;
    test.tm_mon = 12;
    test.tm_year = 2023;

    Rtcc_periodicTask(&test);

    TEST_ASSERT_EQUAL(29, test.tm_days[2]);
}

/**
 * @brief test if rund along branch sencods
 * 
 */
void test_periodicTask__branch_tm_sec__()
{
    Rtcc_Clock test;
    Rtcc_clockInit(&test);
    test.tm_sec = 58;

    Rtcc_periodicTask(&test);
}

/**
 * @brief test if runs along branch mday
 * 
 */
void test_periodicTask__branch_tm_mday__()
{
    Rtcc_Clock test;
    Rtcc_clockInit(&test);
    test.tm_sec = 60;
    test.tm_min = 60;
    test.tm_hour = 24;
    test.tm_mon = 1;

    Rtcc_periodicTask(&test);
}

/**
 * @brief test if runs along branch wday
 * 
 */
void test_periodicTask_branch_tm_wday__()
{
    Rtcc_Clock test;
    Rtcc_clockInit(&test);
    test.tm_sec = 60;
    test.tm_min = 60;
    test.tm_hour = 24;
    test.tm_mon = 12;
    test.tm_wday = 1;

    Rtcc_periodicTask(&test);
    TEST_ASSERT_EQUAL(2, test.tm_wday);
}

/**
 * @brief test if runs along branch year
 * 
 */
void test_periodicTask_branch_tm_year__()
{ // branch 3/4
    Rtcc_Clock test;
    Rtcc_clockInit(&test);
    test.tm_sec = 60;
    test.tm_min = 60;
    test.tm_hour = 23;
    test.tm_mday = 30;
    test.tm_mon = 11;

    Rtcc_periodicTask(&test);
    TEST_ASSERT_EQUAL(1900, test.tm_year);
}

/**
 * @brief test if runs along branch month
 * 
 */
void test_periodicTask_branch_tm_mon__()
{
    Rtcc_Clock test;
    Rtcc_clockInit(&test);
    test.tm_sec = 60;
    test.tm_min = 60;
    test.tm_hour = 23;
    test.tm_mday = 30;
    test.tm_mon = 11;

    Rtcc_periodicTask(&test);
    TEST_ASSERT_EQUAL(1, test.tm_mday);
}