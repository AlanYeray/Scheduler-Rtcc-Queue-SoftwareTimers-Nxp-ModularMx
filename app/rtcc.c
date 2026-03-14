/**
 * @file rtcc.c
 * @author Alan Yeray Olivas
 * @brief to work on date and time
 * @version 0.1
 * @date 2024-05-09
 *
 * @copyright Copyright (c) 2024
 *
 */

/**
 * @defgroup <1 AND 0> macro to define 1s and 0s inside of conditionals
 *
 */
#define SET 1
#define CLEAR 0

#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>
#include "rtcc.h"

/**
 * @brief init a specific time a date to start
 *
 * @param rtcc [in] structure which  contain date and the hour
 */
void Rtcc_clockInit(Rtcc_Clock *rtcc)
{
    // the hour set to 00:00:00
    rtcc->tm_sec = 0;
    rtcc->tm_min = 0;
    rtcc->tm_hour = 0;

    // valid date to January 1, 1900
    rtcc->tm_mday = 1;
    rtcc->tm_mon = 1;
    rtcc->tm_year = 1900;

    // enable the clock bit and disable the alarm control, bits
    rtcc->ctrl.bits.clk_en = SET;
    rtcc->ctrl.bits.al_active = CLEAR;
}

/**
 * @brief  set hour, minutes and secods in the structure rtcc
 *
 * @param rtcc [in] structure
 * @param hour [in] hour 24 format
 * @param minutes [in] minutes
 * @param seconds [in] seconds
 * @retval  uint8_t if it was succeeded or failed
 */
uint8_t Rtcc_setTime(Rtcc_Clock *rtcc, uint8_t hour, uint8_t minutes, uint8_t seconds)
{
    // receive the hour
    if ((hour <= 24) && (hour >= 0))
    {
        rtcc->tm_hour = hour;
    }
    else
    {
        return false;
    }

    // minutes
    if ((minutes <= 59) && (minutes >= 0))
    {
        rtcc->tm_min = minutes;
    }
    else
    {
        return false;
    }

    // seconds in 24 hours format
    if ((seconds <= 59) && (seconds >= 0))
    {
        rtcc->tm_sec = seconds;
    }
    else
    {
        return 0;
    }

    return true;

    // shout be validated id they make a valid hour
    // in case true the new values shall be assigened to the corresponding internal clock structure
    // return true is the new time could be set
    // otherwise returns false
}

/**
 * @brief  set date, month and the year in the structure rtcc
 *
 *  should be validated if they make a valid date
    // in case ture the new values shall be assigned to the corresponding internal clock struture
    // calculate the day of the weak  and assigned to the corresponding clock structure element
    // return true is the new time could be set
    // otherwise return false
 * @param rtcc [in] structure
 * @param day [in] day of the month range 1 to 31
 * @param month month, range 1 to 12
 * @param year years in range 1900 to 2100
 * @retval uint8_t if it was succeeded or failed
 */
uint8_t Rtcc_setDate(Rtcc_Clock *rtcc, uint8_t day, uint8_t month, uint16_t year)
{
    // receive the day of the month
    // month of the year in four digits
    if ((day < 32) != 0)//x
    {
        rtcc->tm_mday = day;
    }
    else
    {
        return false;
    }

    if ((month <= 12) != 0)//x
    {
        rtcc->tm_mon = month;
    }
    else
    {
        return false;
    }

    if (2100 > year > 1900)//y
    {

        rtcc->tm_year = year;
    }
    else
    {
        return false;
    }

    return true; // done!
}

/**
 * @brief set alarm hour minutes
 *
 * @param rtcc [in] structure
 * @param hour [in] hour 24 format
 * @param minutes [in] minutes
 * @retval uint8_t if it was succeeded or failed
 */
uint8_t Rtcc_setAlarm(Rtcc_Clock *rtcc, uint8_t hour, uint8_t minutes)
{
    // receive the hour
    if ((hour <= 24) && (hour > 0))
    {
        rtcc->al_hour = hour;
    }
    else
    {
        return false;
    }

    // minutes
    if ((minutes < 60) > 0)
    {
        rtcc->al_min = minutes;
    }
    else
    {
        return false;
    }

    rtcc->ctrl.bits.al_set = SET; // which indicate a alarm will be activated as soon as the time match the alarm value.

    return true; // new time could be set
}

/**
 * @brief set values of the hour to other structure
 *
 * @param rtcc [in] structure
 * @param hour [out] hour 24 format
 * @param minutes [out] minutes
 * @param seconds [out] seconds
 */
void Rtcc_getTime(Rtcc_Clock *rtcc, uint8_t *hour, uint8_t *minutes, uint8_t *seconds)
{
    // The function returns by reference the current time values, hour, minutes and seconds, all the values will be
    // taken from the clock control structure
    *hour = rtcc->tm_hour;
    *minutes = rtcc->tm_min;
    *seconds = rtcc->tm_sec;
}

/**
 * @brief set values of the Date to other structure
 *
 * @param rtcc [in] structure
 * @param day [out] hour 24 format
 * @param month [out] minutes
 * @param year [out] seconds
 * @param weekDay [out] day of the week
 */
void Rtcc_getDate(Rtcc_Clock *rtcc, uint8_t *day, uint8_t *month, uint16_t *year, uint8_t *weekDay)
{
    *day = rtcc->tm_mday;
    *month = rtcc->tm_mon;
    *year = rtcc->tm_year;
    *weekDay = rtcc->tm_wday;
}

/**
 * @brief obtain the values of hour and minutes previously configured with Rtcc_setAlarm()
 *
 *      check if al_active bit is set
 *
 * @param rtcc [in] structure
 * @param hour  [out] hour 24 format
 * @param minutes [out] minutes
 * @retval uint8_t if it was succeeded or failed
 */
uint8_t Rtcc_getAlarm(Rtcc_Clock *rtcc, uint8_t *hour, uint8_t *minutes)
{

    *hour = rtcc->al_hour;
    *minutes = rtcc->al_min;

    if (rtcc->ctrl.bits.al_active == SET)
    {
        return true;
    }

    return false;
}

/**
 * @brief clear  al_active and al_set param to clear the alarm
 *
 * @param rtcc [in] structure
 */
void Rtcc_clearAlarm(Rtcc_Clock *rtcc)
{
    /*Once the alarm is active (time and alarm values are the same) this function will be use to clear the active
    flag and also will disable the alarm, been necessary to call the AppClk_setAlarm function again to set the alarm*/

    rtcc->ctrl.bits.al_active = CLEAR;
    rtcc->ctrl.bits.al_set = CLEAR;
}

/**
 * @brief return al_active bit
 *
 * @param rtcc [in] structure
 * @retval uint8_t  if it was succeeded or failed
 */
uint8_t Rtcc_getAlarmFlag(Rtcc_Clock *rtcc)
{
    return rtcc->ctrl.bits.al_active;
}

/**
 * @brief increment one seconds then a minute, then one hour, day of the month, month, year
 *
 * @param rtcc [in] structure
 * @note needs to run every second
 */

void Rtcc_periodicTask(Rtcc_Clock *rtcc)
{
    // increment values of hour and date
    rtcc->tm_sec++;

    if (rtcc->tm_sec > 59)
    {
        rtcc->tm_sec = 0;
        rtcc->tm_min++;

        if (rtcc->tm_min > 59)
        {
            rtcc->tm_min = 0;
            rtcc->tm_hour++;

            if (rtcc->tm_hour > 23)
            {
                rtcc->tm_hour = 0;
                rtcc->tm_mday++;

                if (rtcc->tm_mday > rtcc->tm_days[rtcc->tm_mon])
                {
                    rtcc->tm_mday = 1;
                    rtcc->tm_mon++;

                    if (rtcc->tm_mon > 12)
                    {
                        rtcc->tm_mon = 1;
                        rtcc->tm_year++;

                        if (rtcc->tm_year % 4 == 0 /*&& rtcc->tm_year % 100 != 0)*/)
                        {
                            rtcc->tm_days[2] = 29;
                            // Si un año es divisible entre 4 pero no es divisible entre 100, es un año bisiesto.
                            // Si un año es divisible entre 400, también es un año bisiesto.
                        }
                        else
                        {
                            rtcc->tm_days[2] = 28;
                        }
                    }
                }
                // Increment day of the week
                rtcc->tm_wday++;
                if (rtcc->tm_wday > 6)
                {
                    rtcc->tm_wday = 0;
                }
            }

            if (rtcc->ctrl.bits.al_set == SET)
            {
                if (rtcc->tm_hour == rtcc->al_hour /* && rtcc->tm_min == rtcc->al_min */)
                {
                    rtcc->ctrl.bits.al_active = SET;
                }
            }
        }
    }
}
