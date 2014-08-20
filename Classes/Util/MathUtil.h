/***************************************************************
* 
*
*  作者：		王少培
*  文件名：		MathUtil.h
*  创建时间：	
*
***************************************************************/

#ifndef __MATH_UTIL_H__
#define __MATH_UTIL_H__

// 数据工具函数
class CMathUtil
{
public:
	static int abs(int x);					// 取绝对值（整型）
	static double abs(double x);				// 取绝对值（双精）
	static int round(double x);				// 四舍五入（双精）
	static int floor(double x);				// 下取整（双精）
	static int ceiling(double x);				// 上取整（双精）
	static double sqrt(double x);				// 开根号（双精）
	static double sin(double alpha);			// sin
	static double cos(double alpha);			// cos
	static double tan(double alpha);			// tan
	static double angle2radian(double angle);	// 角度到弧度
	static double radian2angle(double radian);// 弧度到角度
	static double fmod(double f, double r);
	static double acos(double value);		// 反余弦

public:

	static double PI;
};

#define ABS(x)		CMathUtil::abs(x)
#define ROUND(x)	CMathUtil::round(x)
#define FLOOR(x)	CMathUtil::floor(x)
#define CEIL(x)		CMathUtil::ceil(x)


#endif