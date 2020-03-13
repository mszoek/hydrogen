/*
 * H2 Real-Time Clock Driver
 * Copyright (C) 2017-2019 Zoe & Alexis Knox. All rights reserved.
 */

#include <hw/types.h>
#include <hw/cmos.h>

#define RTC_SECOND 0x00
#define RTC_MINUTE 0x02
#define RTC_HOUR 0x04
#define RTC_DAY 0x07
#define RTC_MONTH 0x08
#define RTC_YEAR 0x09
#define RTC_STATUS_A 0x0A
#define RTC_STATUS_B 0x0B

static const int monthDays[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

int rtcUpdateInProgress()
{
    UInt8 val = cmosRead(RTC_STATUS_A);
    return (val & 0x80);
}

inline UInt8 rtcDecodeBCD(UInt8 bcd)
{
    return (bcd & 0x0F) + ((bcd & 0xF0) >> 3) + ((bcd & 0xF0) >> 1);
}

// return number of days since January 1, ignoring leap years
inline int daysSinceJan1(UInt8 month, UInt8 day)
{
    int yday = 0;
    for(int i = 0; i < month - 1; ++i)
        yday += monthDays[i];
    return yday + day - 1;
}

UInt64 rtcRead()
{
    UInt8 lastSecond, lastMinute, lastHour, lastDay, lastMonth, lastYear;
    UInt8 second, minute, hour, day, month, year;

    while(rtcUpdateInProgress()); // wait until any update is done
    second = cmosRead(RTC_SECOND);
    minute = cmosRead(RTC_MINUTE);
    hour = cmosRead(RTC_HOUR);
    day = cmosRead(RTC_DAY);
    month = cmosRead(RTC_MONTH);
    year = cmosRead(RTC_YEAR);

    // now read everything again until we get the same values twice
    // to ensure consistency. Stupid RTC.
    do
    {
        lastSecond = second;
        lastMinute = minute;
        lastHour = hour;
        lastDay = day;
        lastMonth = month;
        lastYear = year;

        while(rtcUpdateInProgress()); // wait for update to finish
        second = cmosRead(RTC_SECOND);
        minute = cmosRead(RTC_MINUTE);
        hour = cmosRead(RTC_HOUR);
        day = cmosRead(RTC_DAY);
        month = cmosRead(RTC_MONTH);
        year = cmosRead(RTC_YEAR);
    }
    while(lastSecond != second || lastMinute != minute || lastHour != hour || lastDay != day || lastMonth != month || lastYear != year);

    UInt8 statusB = cmosRead(RTC_STATUS_B);
    if(!(statusB & 0x04)) // values are in BCD
    {
        second = rtcDecodeBCD(second);
        minute = rtcDecodeBCD(minute);
        day = rtcDecodeBCD(day);
        month = rtcDecodeBCD(month);
        year = rtcDecodeBCD(year);
        hour = ((hour & 0x0F) + (((hour & 0x70) / 16 * 10) | (hour & 0x80)));
    }

    if(!(statusB & 0x02) && (hour & 0x80)) // convert from 12h clock
    {
        hour = ((hour & 0x7F) + 12) % 24;
    }

    year += 100; // assume year is >2000
    int yday = daysSinceJan1(month, day);

    // POSIX "seconds since the epoch"
    // http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap04.html#tag_04_15
    return (second + minute*60 + hour*3600 + yday*86400 +
     (year-70)*31536000 + ((year-69)/4)*86400 -
     ((year-1)/100)*86400 + ((year+299)/400)*86400);
}
