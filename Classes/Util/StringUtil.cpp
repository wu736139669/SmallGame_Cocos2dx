/********************************************************************
	created:	2014/04/09 
	filename: 	StringUtil.h
	author:		王少培
	purpose:	
*********************************************************************/
#include "StringUtil.h"
#include <sstream>
#include <ctype.h>
#include <iomanip>

std::string CStringUtil::convertToUIResPath(char* pszFileName)
{
	std::string str = "./CocoStudioResources/";
	str += pszFileName;
	return str;
}


std::string CStringUtil::BLANK = "";


std::string CStringUtil::ToString(int value) {
	std::stringstream ss;
	ss << value;
	return ss.str();
}
std::string CStringUtil::ToString(unsigned int value) {
	std::stringstream ss;
	ss << value;
	return ss.str();
}
std::string CStringUtil::ToString(long long value) {
	std::stringstream ss;
	ss << value;
	return ss.str();
}

std::string CStringUtil::ToString(unsigned long long value) {
	std::stringstream ss;
	ss << value;
	return ss.str();
}

std::string CStringUtil::ToString(short value) {
	std::stringstream ss;
	ss << value;
	return ss.str();
}

std::string CStringUtil::ToString(bool value) {
	std::stringstream ss;
	ss << value;
	return ss.str();
}

std::string CStringUtil::ToString(double value) {
	std::stringstream ss;
	ss << value;
	return ss.str();
}

std::string CStringUtil::ToString(Date value) {
	std::stringstream ss;
	ss << std::setw(2) << std::setfill('0') << value.year << "/" << std::setw(2) << std::setfill('0') << value.month << "/" << std::setw(2) << std::setfill('0') << value.day;
	return ss.str();
}

std::string CStringUtil::ToString(DateTime value) {
	std::stringstream ss;
	ss << std::setw(4) << std::setfill('0') << value.date.year << "/" << std::setw(2) << std::setfill('0') << value.date.month << "/" << std::setw(2) << std::setfill('0') << value.date.day;
	ss << " ";
	ss << std::setw(2) << std::setfill('0') << value.time.hour << ":" << std::setw(2) << std::setfill('0') << value.time.minute << ":" << std::setw(2) << std::setfill('0') << value.time.second;
	return ss.str();
}

std::string CStringUtil::ToString(float value, unsigned int nPrecision/*=2*/) {
	std::stringstream ss;
	ss.precision(nPrecision);
	ss.setf(std::ios::fixed, std::ios::floatfield);
	ss << value;
	return ss.str();
}

std::string CStringUtil::ToString(SystemDateTime value) {
	std::stringstream ss;
	ss << value.dateTime.date.year << '-' << value.dateTime.date.month << '-' << value.dateTime.date.day << ' '
		<< value.dateTime.time.hour << ':' << value.dateTime.time.minute << ':' << value.dateTime.time.second;
	return ss.str();
}

int CStringUtil::ToInt(const std::string &value) {
	std::stringstream ss;
	ss << value;
	int i;
	ss >> i;
	return i;
}
long long CStringUtil::ToInt64(const std::string &value) {
	std::stringstream ss;
	ss << value;
	long long i;
	ss >> i;
	return i;
}
double CStringUtil::ToDouble(const std::string &value) {
	std::stringstream ss;
	ss << value;
	double d;
	ss >> d;
	return d;
}
unsigned int CStringUtil::HashString(char *str)
{
    register unsigned int hash;
    register unsigned char *p;
    
    for(hash = 0, p = (unsigned char *)str; *p ; p++)
        hash = 31 * hash + *p;
    
    return (hash & 0x7FFFFFFF);
}