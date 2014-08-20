
#ifndef __Counter__
#define __Counter__
#include "cocos2d.h"
USING_NS_CC;
class CCounter : public cocos2d::CCNode
{
public:
    CCounter();
    /**
     *	@brief
     *
     *	@param 	presenters 	0-9这10个数字对应的节点的数组
     *	@param 	digit 	默认的数值
     *
     *	@return
     */
    static CCounter* create(cocos2d::CCArray* presenters, int digit = 0);
    bool init(cocos2d::CCArray* presenters, int digit = 0);
   
	void setDigit(int digit,bool bAnimate); 
	CCNode* getCurrDigit();
	CC_PROPERTY_READONLY(int,_digit,Digit);
protected:
    void visit();

	void _moveTo(int digit,const CCPoint& pt);

	//改变数字时播放滚动动画
	void animation(int digit);

    //存放0-9数字对应的节点
    cocos2d::CCNode* _presenters;
};

#endif /* defined(__FishingJoy__Counter__) */
