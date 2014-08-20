/***************************************************************
* 
*
*  作者：		王少培
*  文件名：		MathUtil.h
*  创建时间：	
*
***************************************************************/

#ifndef __TIME_UTIL_H__
#define __TIME_UTIL_H__

enum EDAY_IN_WEEK
{
	EDAY_IN_WEEK_SUNDAY		=		0,			// 星期日
	EDAY_IN_WEEK_MONDAY		=		1,			// 星期一
	EDAY_IN_WEEK_TUESDAY	=		2,			// 星期二
	EDAY_IN_WEEK_WEDNESDAY	=		3,			// 星期三
	EDAY_IN_WEEK_THURSDAY	=		4,			// 星期四
	EDAY_IN_WEEK_FRIDAY		=		5,			// 星期五
	EDAY_IN_WEEK_SATURDAY	=		6			// 星期六
};

// 日期
struct Date
{
	int				year;		// 年
	int				month;		// 月 [1 ~ 12]
	int				day;		// 日 [1 ~ 31]

	Date() : year(0), month(0), day(0) {}
};

// 时间
struct Time
{
	int				hour;		// 时 [0 ~ 23]
	int				minute;		// 分 [0 ~ 59]
	int				second;		// 秒 [0 ~ 59]

	Time() : hour(0), minute(0), second(0) {}
};

// 日期时间
struct DateTime
{
	Date				date;			// 日期
	Time				time;			// 时间
};

// 系统日期时间
struct SystemDateTime
{
	DateTime			dateTime;
	int				dayInWeek;		// 星期
	int				dayInYear;		// 一年中的第几天

	SystemDateTime() : dayInWeek(EDAY_IN_WEEK_SUNDAY), dayInYear(1) {}
};


// 时间间隔
struct TimeSpan
{
	int				day;				// 天
	int				hour;				// 时
	int				minute;				// 分
	int				second;				// 秒

	TimeSpan() : day(0), hour(0), minute(0), second(0) {}
};


// 时间工具
class CTimeUtil
{
public:

	// 获取 Unix 时间戳,从1970年1月1日0时0分0秒到当前的秒数 
	static long GetSystemTimeStamp();
	// 获取系统当前的日期时间
	static SystemDateTime GetSystemDateTime();

	// 转化日期时间到时间戳
	static long ToTimeStamp(const DateTime& dateTime);
	// 转化时间戳到日期时间
	static DateTime FromTimeStamp(long timestamp);
	
	// 获取经过一段时间后的日期
	static DateTime CalcDateTime(const DateTime& start, const TimeSpan& span);
	// 计算两个日期时间的时间间隔
	static TimeSpan CalcTimeSpan(const DateTime& start, const DateTime& end);

	// 获取cocosdx时间，返回毫秒
	static double GetCocos2dxTimer();
};


#endif