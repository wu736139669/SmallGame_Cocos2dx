/***************************************************************
* 
*
*  作者：		王少培
*  文件名：		MathUtil.h
*  创建时间：	
*
***************************************************************/

#ifndef __UNIT_UTIL_H__
#define __UNIT_UTIL_H__

class CUnitUtil
{
public:

	// 天 -> 小时
	static int DayToHour(int day);
	// 小时 -> 天
	static double HourToDay(int hour);
	// 小时 -> 分钟
	static int HourToMinute(int hour);
	// 分钟 -> 小时
	static double MinuteToHour(int minute);
	// 分钟 -> 秒
	static int MinuteToSecond(int minute);
	// 秒 -> 分钟
	static double SecondToMinute(int second);
};



#endif