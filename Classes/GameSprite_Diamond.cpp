//
//  Game_Diamond.cpp
//  OnceAgain
//
//  Created by mac on 14-3-4.
//
//

#include "GameSprite_Diamond.h"
enum KEY_SPRITE{
    Key_Diamond_Num =  100
};

GameSprite_Diamond::~GameSprite_Diamond()
{
    m_pfnSelector = NULL;
    m_pfnSelector = NULL;
}

bool GameSprite_Diamond::init()
{
    if (!CCSprite::init()) {
        return false;
    }
    
    diamondNum = 0;
    //设置大小.
    this->setContentSize(CCSize(150, 70));
    
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
    
    //钻石
    CCSprite *diamondSprite = GameShare_Texture::sharedTexture()->GetSpriteByCCRect(akoomenu_image, CCRect(900, 1986, 74, 56));
    diamondSprite->setAnchorPoint(CCPointZero);
    diamondSprite->setPosition(CCPointZero);
    this->addChild(diamondSprite,1);
    
    
    CCLabelTTF *numLabel = CCLabelTTF::create("", "Arial", 25);
    //    numLabel
    char strScore[32];
    sprintf(strScore,"%ld",diamondNum);
    numLabel->setString(strScore);
    numLabel->setPosition(CCPoint(90, 20));
    numLabel->setTag(Key_Diamond_Num);
    this->addChild(numLabel,1);
    
    
    
    return true;
}

long GameSprite_Diamond::getDiamondNum(void)
{
    return diamondNum;
}
void GameSprite_Diamond::setDiamondNum(long diamondNum)
{
    this->diamondNum = diamondNum;
    if (this->getChildByTag(Key_Diamond_Num)) {
        char strScore[32];
        sprintf(strScore,"%ld",diamondNum);
        ((CCLabelTTF*)this->getChildByTag(Key_Diamond_Num))->setString(strScore);
    }
}

cocos2d::CCRect GameSprite_Diamond::rect()
{
    return CCRectMake(getPositionX() - getContentSize().width * getAnchorPoint().x,
                      getPositionY() - getContentSize().height * getAnchorPoint().y,
                      getContentSize().width, getContentSize().height); // To be able to customize the size of their position with a function rather than inefficient use member variables directly
    
}

#pragma mark TouchDelegate
void GameSprite_Diamond::onEnter()
{
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    CCSprite::onEnter();
}
void GameSprite_Diamond::onExit()
{
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
    CCSprite::onExit();
}

bool GameSprite_Diamond::isTouchInside( CCTouch* touch )
{
    CCPoint touchLocation = touch->getLocation(); // Return to GL coordinates
    CCPoint localPos = convertToNodeSpace(touchLocation);
    CCRect rc = rect();
    rc.origin = CCPointZero;
    bool isTouched = rc.containsPoint(localPos);
    
    return isTouched;
}

bool GameSprite_Diamond::ccTouchBegan(CCTouch *touch, CCEvent *event)
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
void GameSprite_Diamond::ccTouchMoved(CCTouch *touch ,CCEvent *event)
{
    
}

void GameSprite_Diamond::ccTouchEnded(CCTouch *touch ,CCEvent *event)
{
    
}

void GameSprite_Diamond::setTarget(CCObject *rec, SEL_MenuHandler selector)
{
    m_pListener = rec;
    m_pfnSelector = selector;
}