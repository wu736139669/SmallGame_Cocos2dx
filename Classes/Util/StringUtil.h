/********************************************************************
	created:	2014/04/09 
	filename: 	StringUtil.h
	author:		王少培
	purpose:	
*********************************************************************/
#ifndef __STRING_UTIL_H__
#define __STRING_UTIL_H__
#include <string>
#include "TimeUtil.h"

class CStringUtil
{
public:
	//转为UI资源目录
	static std::string convertToUIResPath(char* pszFileName);

	static std::string BLANK;

	// int -> string
	static std::string ToString(int value);
	// uint -> string
	static std::string ToString(unsigned int value);
	// double -> string
	static std::string ToString(double value);
	// double -> string
	static std::string ToString(long long value);

	static std::string ToString(unsigned long long value);

	static std::string ToString(short value);

	static std::string ToString(bool value);
	// float -> string
	static std::string ToString(float value, unsigned int nPrecision = 2);
	// date -> string
	static std::string ToString(Date value);
	// date time -> string
	static std::string ToString(DateTime value);
	// sys date time -> string
	static std::string ToString(SystemDateTime value);
	
	// string -> int
	static int ToInt(const std::string &value);
	// string -> int64
	static long long ToInt64(const std::string &value);
	// string -> double
	static double ToDouble(const std::string &value);
    //
    static unsigned int HashString(char *str);
};

#endif