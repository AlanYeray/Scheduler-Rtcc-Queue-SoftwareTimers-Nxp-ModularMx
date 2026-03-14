#ifndef RTCC_H_
#define RTCC_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * @brief structure inside of Rtcc_Clock to manage registers to active alarms or clock
 * 
 */
typedef union _Rtcc_Ctrl
{
    uint8_t Register; /*8 bit vaiable*/
    struct _bits
    {
        uint8_t clk_en : 1;    /*!< clock enable flag      */
        uint8_t al_set : 1;    /*!< alarm set flag         */
        uint8_t al_active : 1; /*!< alarm active flag      */
        uint8_t none : 4;
    } bits;
} Rtcc_Ctrl;

/**
 * @brief structure to store the date and the time
 * 
 */
typedef struct _Rtcc_Clock
{
    uint8_t tm_sec;       /*!< seconds,  range 0 to 59          */
    uint8_t tm_min;       /*!< minutes, range 0 to 59           */
    uint8_t tm_hour;      /*!< hours, range 0 to 23             */
    uint8_t tm_mday;      /*!< day of the month, range 1 to 31  */
    uint8_t tm_mon;       /*!< month, range 1 to 12             */
    uint16_t tm_year;     /*!< years in rage 1900 2100          */
    uint8_t tm_wday;      /*!< day of the week, range 0 to 6    */
    uint8_t al_min;       /*!< alarm minutes, range 0 to 59     */
    uint8_t al_hour;      /*!< alarm hours, range 0 to 23       */
    uint8_t tm_days[31u]; /*!< max days on each month */
    Rtcc_Ctrl ctrl;       /*!< clock control bits */
} Rtcc_Clock;

/**
 * @brief init a specific time a date to start
 * 
 * @param rtcc [in] structure which  contain date and the hour
 */
void Rtcc_clockInit(Rtcc_Clock *rtcc);
/**
 * @brief  set hour, minutes and secods in the structure rtcc
 * 
 * @param rtcc [in] structure
 * @param hour [in] hour 24 format
 * @param minutes [in] minutes
 * @param seconds [in] seconds
 * @retval uint8_t if it was succeeded or failed
 */
uint8_t Rtcc_setTime(Rtcc_Clock *rtcc, uint8_t hour, uint8_t minutes, uint8_t seconds);
/**
 * @brief  set date, month and the year in the structure rtcc
 * 
 * @param rtcc [in] structure
 * @param day [in] day of the month range 1 to 31
 * @param month month, range 1 to 12
 * @param year years in range 1900 to 2100
 * @retval uint8_t if it was succeeded or failed
 */
uint8_t Rtcc_setDate(Rtcc_Clock *rtcc, uint8_t day, uint8_t month, uint16_t year);

/**
 * @brief set alarm hour minutes
 * 
 * @param rtcc [in] structure
 * @param hour [in] hour 24 format
 * @param minutes [in] minutes
 * @retval uint8_t if it was succeeded or failed
 */
uint8_t Rtcc_setAlarm(Rtcc_Clock *rtcc, uint8_t hour, uint8_t minutes);

/**
 * @brief set values of the hour to other structure
 * 
 * @param rtcc [in] structure
 * @param hour [out] hour 24 format
 * @param minutes [out] minutes
 * @param seconds [out] seconds
 */
void Rtcc_getTime(Rtcc_Clock *rtcc, uint8_t *hour, uint8_t *minutes, uint8_t *seconds);

/**
 * @brief set values of the Date to other structure
 * 
 * @param rtcc [in] structure
 * @param day [out] hour 24 format
 * @param month [out] minutes
 * @param year [out] seconds
 * @param weekDay [out] day of the week
 */
void Rtcc_getDate(Rtcc_Clock *rtcc, uint8_t *day, uint8_t *month, uint16_t *year, uint8_t *weekDay);

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
uint8_t Rtcc_getAlarm(Rtcc_Clock *rtcc, uint8_t *hour, uint8_t *minutes);


/**
 * @brief clear  al_active and al_set param to clear the alarm
 * 
 * @param rtcc [in] structure
 */
void Rtcc_clearAlarm(Rtcc_Clock *rtcc);

/**
 * @brief return al_active bit 
 * 
 * @param rtcc [in] structure
 * @retval uint8_t  if it was succeeded or failed
 */
uint8_t Rtcc_getAlarmFlag(Rtcc_Clock *rtcc);

/**
 * @brief increment one seconds then a minute, then one hour, day of the month, month, year
 * 
 * @param rtcc [in] structure
 * @note needs to run every second
 */
void Rtcc_periodicTask(Rtcc_Clock *rtcc);

#endif