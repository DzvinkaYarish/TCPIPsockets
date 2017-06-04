//
// Created by dzvinka on 04.06.17.
//

#include "date.time.h"

const char* getTime()
{
    struct tm *timeinfo;
    time_t timev;
    time(&timev);
    const char* ftime;
    timeinfo = localtime (&timev);
    std::string hour = std::to_string(timeinfo->tm_hour);
    if(hour.size() < 2) {
        hour = "0" + hour;
    }
    std::string minute = std::to_string(timeinfo->tm_min);
    if(minute.size() < 2) {
        minute = "0" + minute;
    }
    std::string sec = std::to_string(timeinfo->tm_sec);
    if(sec.size() < 2) {
        sec = "0" + sec;
    }
    std::string  stime =  hour + ":" + minute + ":" + sec;
    ftime = stime.c_str();
    return ftime;
}

const char* getDate()
{
    struct tm *dateinfo;
    time_t timev;
    time(&timev);
    const char* fdate;
    dateinfo = localtime (&timev);
    std::string mday = std::to_string(dateinfo->tm_mday);
    if(mday.size() < 2) {
        mday = "0" + mday;
    }
    std::string mon = std::to_string(dateinfo->tm_mon);
    if(mon.size() < 2) {
        mon = "0" + mon;
    }

    std::string  stime = mday + "-" + mon + "-" + std::to_string(1900 + dateinfo->tm_year);
    fdate = stime.c_str();
    return fdate;
}
