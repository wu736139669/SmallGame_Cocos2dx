//
//  GameSprite_Gold.h
//  OnceAgain
//
//  Created by mac on 14-3-4.
//
//

#ifndef __OnceAgain__GameSprite_Gold__
#define __OnceAgain__GameSprite_Gold__

#include <iostream>
#include "cocos2d.h"
#include "platform/CCPlatformMacros.h"

#include "GameShare_Texture.h"
USING_NS_CC;

class GameSprite_Gold : public CCSprite, public cocos2d::CCTouchDelegate
{
public:
    virtual bool init();
    GameSprite_Gold(void){};
    virtual ~GameSprite_Gold();
    
    //金币数量
    CC_PROPERTY(long, goldNum, GoldNum);
    
    // Get the position and size of the Sprite
    CCRect rect();
    // Whether the touch point in the Sprite
    bool isTouchInside(CCTouch* touch);
    
    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch *touch, CCEvent *event);
    virtual void ccTouchMoved(CCTouch *touch, CCEvent *event);
    virtual void ccTouchEnded(CCTouch *touch, CCEvent *event);
    
    void setTarget(CCObject *rec, SEL_MenuHandler selector);
    
    CREATE_FUNC(GameSprite_Gold);
protected:
    CCObject*       m_pListener;
    SEL_MenuHandler    m_pfnSelector;
    
};
#endif /* defined(__OnceAgain__GameSprite_Gold__) */
