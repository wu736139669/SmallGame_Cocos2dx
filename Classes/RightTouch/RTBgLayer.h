

#ifndef _RT_BG_Layer_H
#define _RT_BG_Layer_H
#include "cocos2d.h"
USING_NS_CC;
class CRTBgLayer : public cocos2d::CCLayer
{
public:
    CREATE_FUNC(CRTBgLayer);
    bool init();

	CC_SYNTHESIZE(CCSprite*,mpBg,Bg)
};

#endif /* defined(__FishingJoy__BackgroundLayer__) */
