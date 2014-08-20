//
//  Hero.h
//  HelloWorld
//
//  Created by mac on 14-1-7.
//
//

#ifndef __HelloWorld__Game_MemoryCard__
#define __HelloWorld__Game_MemoryCard__
//enum imgType{a,b,c};
#include "cocos2d.h"

USING_NS_CC;
class Game_MemoryCard : public cocos2d::CCSprite,public cocos2d::CCTouchDelegate
{
public:
    Game_MemoryCard(void);
    static Game_MemoryCard* spriteModelWithFile(const char *spName); //Static create (memory automatic release)
    static Game_MemoryCard* spriteModelWithFile(void); //Static create (memory automatic release)
    virtual bool myInit();//Custom initialization function
    virtual ~Game_MemoryCard();
    
    // Get the position and size of the Sprite
    CCRect rect();
    // Whether the touch point in the Sprite
    bool isTouchInside(CCTouch* touch);

    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch *touch, CCEvent *event);
    virtual void ccTouchMoved(CCTouch *touch, CCEvent *event);
    virtual void ccTouchEnded(CCTouch *touch, CCEvent *event);
    
    void delCallBack();
    void openCard();
    void setPic(int type);
    void clickCard();
    bool isOpen();
    void setOpen();
    void setClose();
    void stopAction();
    int getType();
private:
    bool m_isOpened;
    CCActionInterval* m_openAnimIn;
    CCActionInterval* m_openAnimOut;
    CCSprite* outCard;
    int type;
    
    CCRect getRect(int type);
};


#endif /* defined(__HelloWorld__Hero__) */
