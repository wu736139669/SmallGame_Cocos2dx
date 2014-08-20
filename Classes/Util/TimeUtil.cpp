/***************************************************************
* 
*
*  作者：		王少培
*  文件名：		MathUtil.h
*  创建时间：	
*
***************************************************************/

#include "TimeUtil.h"
#include "UnitUtil.h"
#include <time.h>
#include "platform/platform.h"

long CTimeUtil::GetSystemTimeStamp()
{
	return (long)::time(NULL);
}

DateTime CTimeUtil::FromTimeStamp( long timestamp )
{
	time_t time = (time_t)timestamp;
	struct tm* p = ::localtime(&time);
	DateTime dt;
	dt.date.year = p->tm_year + 1900;
	dt.date.month = p->tm_mon + 1;
	dt.date.day = p->tm_mday;
	dt.time.hour = p->tm_hour;
	dt.time.minute = p->tm_min;
	dt.time.second = p->tm_sec;
	return dt;
}

SystemDateTime CTimeUtil::GetSystemDateTime()
{
	time_t t = ::time(NULL);
	struct tm* p = localtime(&t);
	SystemDateTime dt;
	dt.dateTime.date.year = p->tm_year + 1900;
	dt.dateTime.date.month = p->tm_mon + 1;
	dt.dateTime.date.day = p->tm_mday;
	dt.dateTime.time.hour = p->tm_hour;
	dt.dateTime.time.minute = p->tm_min;
	dt.dateTime.time.second = p->tm_sec;
	dt.dayInWeek = p->tm_wday;
	dt.dayInYear = p->tm_yday + 1;
	return dt;
}

DateTime CTimeUtil::CalcDateTime( const DateTime& start, const TimeSpan& span )
{
	long time = ToTimeStamp(start);
	
	int nDays = span.day;
	int nHours = CUnitUtil::DayToHour(nDays) + span.hour;
	int nMinutes = CUnitUtil::HourToMinute(nHours) + span.minute;
	int nSeconds = CUnitUtil::MinuteToSecond(nMinutes) + span.second;
	time += nSeconds;

	return FromTimeStamp(time);
}

TimeSpan CTimeUtil::CalcTimeSpan( const DateTime& start, const DateTime& end )
{
	long timeStampStart = ToTimeStamp(start);
	long timeStampEnd = ToTimeStamp(end);
	int timeDiff = (int)::difftime(timeStampEnd, timeStampStart);
	int minute = (int)CUnitUtil::SecondToMinute(timeDiff);
	int second = timeDiff - CUnitUtil::MinuteToSecond(minute);
	int hour = (int)CUnitUtil::MinuteToHour(minute);
	minute -= CUnitUtil::HourToMinute(hour);
	int day = (int)CUnitUtil::HourToDay(hour);
	hour -= CUnitUtil::DayToHour(day);
	TimeSpan span;
	span.day = day;
	span.hour = hour;
	span.minute = minute;
	span.second = second;
	return span;
}

long CTimeUtil::ToTimeStamp( const DateTime& dateTime )
{
	struct tm t;
	t.tm_year = dateTime.date.year - 1900;
	t.tm_mon = dateTime.date.month - 1;
	t.tm_mday = dateTime.date.day;
	t.tm_hour = dateTime.time.hour;
	t.tm_min = dateTime.time.minute;
	t.tm_sec = dateTime.time.second;
	t.tm_wday = 0;
	t.tm_yday = 0;
	t.tm_isdst = -1;
	return (long)mktime(&t);
}

double CTimeUtil::GetCocos2dxTimer()
{
	struct cocos2d::cc_timeval now;
	cocos2d::CCTime::gettimeofdayCocos2d(&now, NULL);
	return now.tv_sec * 1000.0 + now.tv_usec / 1000.0;
}