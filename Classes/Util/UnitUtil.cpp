/***************************************************************
* 
*
*  作者：		王少培
*  文件名：		MathUtil.h
*  创建时间：	
*
***************************************************************/

#include "UnitUtil.h"

#define HOURS_PER_DAY		24
#define MINUTES_PER_HOUR	60
#define SECONDS_PER_MINUTE	60

int CUnitUtil::DayToHour( int day )
{
	return day * HOURS_PER_DAY;
}

double CUnitUtil::HourToDay( int hour )
{
	return (double)hour / HOURS_PER_DAY;
}

int CUnitUtil::HourToMinute( int hour )
{
	return hour * MINUTES_PER_HOUR;
}

double CUnitUtil::MinuteToHour( int minute )
{
	return (double)minute / MINUTES_PER_HOUR;
}

int CUnitUtil::MinuteToSecond( int minute )
{
	return minute * SECONDS_PER_MINUTE;
}

double CUnitUtil::SecondToMinute( int second )
{
	return (double)second / SECONDS_PER_MINUTE;
}