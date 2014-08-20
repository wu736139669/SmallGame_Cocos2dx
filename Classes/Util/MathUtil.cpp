/***************************************************************
* 
*
*  作者：		王少培
*  文件名：		MathUtil.h
*  创建时间：	
*
***************************************************************/

#include "MathUtil.h"
#include <math.h>

double CMathUtil::PI = 3.1415926535897932;

int CMathUtil::abs( int x )
{
	return x < 0 ? -x : x;
}

double CMathUtil::abs( double x )
{
	return x < 0.0 ? -x : x;
}

int CMathUtil::round( double x )
{
	return x > 0.0 ? CMathUtil::floor(x + 0.5) : CMathUtil::ceiling(x - 0.5);
}

int CMathUtil::floor( double x )
{
	return (int)::floor(x);
}

int CMathUtil::ceiling( double x )
{
	return (int)::ceil(x);
}

double CMathUtil::sqrt( double x )
{
	return (double)::sqrt(x);
}

double CMathUtil::sin( double alpha )
{
	return (double)::sin(alpha);
}

double CMathUtil::cos( double alpha )
{
	return (double)::cos(alpha);
}

double CMathUtil::angle2radian( double angle )
{
	return angle * CMathUtil::PI / 180.0;
}

double CMathUtil::radian2angle( double radian )
{
	return radian * 180.0 / CMathUtil::PI;
}

double CMathUtil::tan( double alpha )
{
	return (double)::tan(alpha);
}

double CMathUtil::fmod( double f, double r )
{
	return (double)::fmod(f, r);
}

double CMathUtil::acos( double value )
{
	if (value > 1.0)
		value = 1.0;
	if (value < -1.0)
		value = -1.0;
	return (double)::acos(value);
}