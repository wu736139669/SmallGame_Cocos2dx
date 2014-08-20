//
//  Game_Rice.h
//  OnceAgain
//
//  Created by mac on 14-3-5.
//
//

#ifndef __OnceAgain__GameSprite_Rice__
#define __OnceAgain__GameSprite_Rice__


#include "cocos2d.h"
#include "platform/CCPlatformMacros.h"

#include "GameShare_Texture.h"
#include "Constant.h"

USING_NS_CC;

class GameSprite_Rice : public CCSprite
{
public:
    
    //有动画效果的饭。

    virtual bool init();
    GameSprite_Rice(void){};
    ~GameSprite_Rice();
    void setTarget(CCObject *rec, SEL_MenuHandler selector);
    CREATE_FUNC(GameSprite_Rice);
    bool addOneRice(void);
    bool reduceOneRice(void);
    
private:
    CC_PROPERTY(int, riceNum, RiceNum);
    int addRiceTime;
    long nowTime;
    
    void timeUpdate(float dt);
    long getCurrentTime();
    
};

class RiceSprite : public CCSprite{
public:
    virtual bool init();
    RiceSprite(void){};
    ~RiceSprite();
    CREATE_FUNC(RiceSprite);
private:
    void showAction(float dt=1.0);
};
#endif /* defined(__OnceAgain__GameSprite_Rice__) */
