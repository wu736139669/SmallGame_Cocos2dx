/***************************************************************
* 
*
*  作者：		王少培
*  文件名：		MathUtil.h
*  创建时间：	
*
***************************************************************/

#include "MathUtil.h"
#include <cstdlib>
#include <limits>
#include <utility>
#include "RandomUtil.h"
void CRandomUtil::InitRandom()
{
    srand( (unsigned)time( NULL ) );
}
int CRandomUtil::RandomRange( int lower_bound, int upper_bound )
{
    
	if (lower_bound > upper_bound)
		std::swap(lower_bound, upper_bound);

    //srand(time(NULL));
	return lower_bound + rand() % (upper_bound - lower_bound + 1);
}

int CRandomUtil::Random()
{
	return rand();
}

double CRandomUtil::RandomOneRatio()
{
	return (double)Random() / INT_MAX;
}

double CRandomUtil::RandomAngle()
{
	return RandomOneRatio() * 360.0;
}

double CRandomUtil::RandomRadian()
{
	return CMathUtil::angle2radian(RandomAngle());
}

CCPoint CRandomUtil::RandomCirclePoint( const CCPoint& center, int radius )
{
	double radian = RandomRadian();
	CCPoint pos;
	pos.x = CMathUtil::round(center.x + radius * CMathUtil::cos(radian));
	pos.y = CMathUtil::round(center.y + radius * CMathUtil::sin(radius));
	return pos;
}

CCPoint CRandomUtil::RandomRectPoint( const CCPoint& leftTopPoint, const CCSize& dimension )
{
	CCPoint pos;
	pos.x = leftTopPoint.x + RandomRange(0, (int)dimension.width);
	pos.y = leftTopPoint.y + RandomRange(0, (int)dimension.height);
	return pos;
}

