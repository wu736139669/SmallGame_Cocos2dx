//
//  Game_Gold.cpp
//  OnceAgain
//
//  Created by mac on 14-3-4.
//
//

#include "GameSprite_Gold.h"
enum KEY_SPRITE{
    Key_Gold_Num =  100
};

GameSprite_Gold::~GameSprite_Gold()
{
    
}

bool GameSprite_Gold::init()
{
    if (!CCSprite::init()) {
        return false;
    }
    //设置大小.
    this->setContentSize(CCSize(200, 70));
    goldNum = 0;
    //字体背景.
    CCSprite *labelBgSprite = GameShare_Texture::sharedTexture()->GetSpriteByCCRect(akoomenu_image, CCRect(324, 938, 166, 48));
    labelBgSprite->setAnchorPoint(CCPointZero);
    labelBgSprite->setPosition(ccp(40,0));
    this->addChild(labelBgSprite,1);
    
    //加号
    CCSprite *addSprite = GameShare_Texture::sharedTexture()->GetSpriteByCCRect(akoomenu_image, CCRect(1970,1772,30,34));
    addSprite->setAnchorPoint(CCPointZero);
    addSprite->setPosition(ccp(185,30));
    this->addChild(addSprite,1);
    
    //金币
    CCSprite *goldSprite = GameShare_Texture::sharedTexture()->GetSpriteByCCRect(akoomenu_image, CCRect(1976, 474, 68, 68));
    goldSprite->setAnchorPoint(CCPointZero);
    goldSprite->setPosition(CCPointZero);
    this->addChild(goldSprite,1);
    
    
    CCLabelTTF *numLabel = CCLabelTTF::create("", "Arial", 25);
//    numLabel
    char strScore[32];
    sprintf(strScore,"%ld",goldNum);
    numLabel->setString(strScore);
    numLabel->setPosition(CCPoint(90, 20));
    numLabel->setTag(Key_Gold_Num);
    this->addChild(numLabel,1);
    
    
    
    return true;
}

long GameSprite_Gold::getGoldNum(void)
{
    return goldNum;
}
void GameSprite_Gold::setGoldNum(long goldNum)
{
    this->goldNum = goldNum;
    if (this->getChildByTag(Key_Gold_Num)) {
        char strScore[32];
        sprintf(strScore,"%ld",goldNum);
        ((CCLabelTTF*)this->getChildByTag(Key_Gold_Num))->setString(strScore);
    }
}

cocos2d::CCRect GameSprite_Gold::rect()
{
    return CCRectMake(getPositionX() - getContentSize().width * getAnchorPoint().x,
                      getPositionY() - getContentSize().height * getAnchorPoint().y,
                      getContentSize().width, getContentSize().height); // To be able to customize the size of their position with a function rather than inefficient use member variables directly
    
}

#pragma mark TouchDelegate
void GameSprite_Gold::onEnter()
{
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    CCSprite::onEnter();
}
void GameSprite_Gold::onExit()
{
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
    CCSprite::onExit();
}

bool GameSprite_Gold::isTouchInside( CCTouch* touch )
{
    CCPoint touchLocation = touch->getLocation(); // Return to GL coordinates
    CCPoint localPos = convertToNodeSpace(touchLocation);
    CCRect rc = rect();
    rc.origin = CCPointZero;
    bool isTouched = rc.containsPoint(localPos);
    
    return isTouched;
}

bool GameSprite_Gold::ccTouchBegan(CCTouch *touch, CCEvent *event)
{
    if (isTouchInside(touch)) {
        if (m_pListener && m_pfnSelector)
        {
            (m_pListener->*m_pfnSelector)(this);
        }
        return true;
    }
    
    return false;
}
void GameSprite_Gold::ccTouchMoved(CCTouch *touch ,CCEvent *event)
{
    
}

void GameSprite_Gold::ccTouchEnded(CCTouch *touch ,CCEvent *event)
{
    
}
void GameSprite_Gold::setTarget(CCObject *rec, SEL_MenuHandler selector)
{
    m_pListener = rec;
    m_pfnSelector = selector;
}