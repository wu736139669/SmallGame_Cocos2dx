//
//  GameShare_Score.h
//  OnceAgain
//
//  Created by mac on 14-3-6.
//
//

#ifndef __OnceAgain__GameShare_Score__
#define __OnceAgain__GameShare_Score__

#include <iostream>
#include "cocos2d.h"
#include "platform/CCPlatformMacros.h"

#include "GameShare_Texture.h"
USING_NS_CC;
class CCounterImage;
class GameShare_Score : public CCSprite
{
public:
    virtual bool init(void);
    GameShare_Score(void){};
    ~GameShare_Score(void);
    
    CREATE_FUNC(GameShare_Score);
private:
    CC_PROPERTY(long, score, Score);
    CCSprite *scroeSprite;
	CCounterImage* mpCounterImage;

	CC_SYNTHESIZE(CCSprite*, mpBg, Bg);
};

#endif /* defined(__OnceAgain__GameShare_Score__) */
