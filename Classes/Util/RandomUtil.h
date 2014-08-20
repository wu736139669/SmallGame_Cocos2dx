/***************************************************************
* 
*
*  作者：		王少培
*  文件名：		MathUtil.h
*  创建时间：	
*
***************************************************************/

#ifndef __CFCRandomUtil_H__
#define __CFCRandomUtil_H__

#include "cocos2d.h"
USING_NS_CC;
// 随机数工具类
class CRandomUtil
{
public:
    //初始化随机种子
    static void InitRandom();
	// 随机 ( lower_bound, upper_bound ) 中的某个值
	static int RandomRange(int lower_bound, int upper_bound);
	// 随机整形值
	static int Random();
	// 随机 0 ~ 1 的比例
	static double RandomOneRatio();
	// 随机角度 [ 0, 360 ]
	static double RandomAngle();
	// 随机弧度 [ 0, 2pi ]
	static double RandomRadian();
	// 随机圆形区域
	static CCPoint RandomCirclePoint(const CCPoint& center, int radius);
	// 随机矩形区域
	static CCPoint RandomRectPoint(const CCPoint& leftTopPoint, const CCSize& dimension);
};


#endif