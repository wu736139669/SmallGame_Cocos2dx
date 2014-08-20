//
//  Game_Experience.h
//  OnceAgain
//
//  Created by mac on 14-3-4.
//
//

#ifndef __OnceAgain__GameSprite_Experience__
#define __OnceAgain__GameSprite_Experience__

#include "cocos2d.h"
#include "platform/CCPlatformMacros.h"
#include "GameShare_Texture.h"
USING_NS_CC;

class GameSprite_Experience : public CCSprite
{
public:
    virtual bool init(void);
    GameSprite_Experience(void){};
    virtual ~GameSprite_Experience();
    CREATE_FUNC(GameSprite_Experience);
    
private:
    CC_PROPERTY(unsigned int, percent, Percent);
    CC_PROPERTY(unsigned int, level, Level);
    
    
};
#endif /* defined(__OnceAgain__Game_Experience__) */
