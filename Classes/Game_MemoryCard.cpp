//
//  Hero.cpp
//  HelloWorld
//
//  Created by mac on 14-1-7.
//
//

#include "Game_MemoryCard.h"
#include "GameUIExportJson.h"

USING_NS_CC;
#define kInAngleZ        270 //Starting Z axis angle inside the card

#define kInDeltaZ        90  //Z-axis rotation angle difference inside the card

#define kOutAngleZ       0   //Starting Z-axis angle of the cover card

#define kOutDeltaZ       90  //Z-axis rotation angle difference between the cover card

#define kDelay           0.2

#define kShowTime        0.8

Game_MemoryCard::Game_MemoryCard(void)
{
    
}
Game_MemoryCard::~Game_MemoryCard(void)
{
    m_openAnimIn->release();
    m_openAnimOut->release();
    
}

Game_MemoryCard* Game_MemoryCard::spriteModelWithFile(const char *spName)
{
    Game_MemoryCard *pobSprite = new Game_MemoryCard();
    
    if (pobSprite && pobSprite->initWithFile(spName))//
    {
        pobSprite->myInit();
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}
Game_MemoryCard* Game_MemoryCard::spriteModelWithFile(void)
{
    Game_MemoryCard *pobSprite = new Game_MemoryCard();
    
    if (pobSprite && pobSprite->myInit())//
    {
        pobSprite->setContentSize(CCSize(184, 155));
//        pobSprite->setAnchorPoint(CCPoint(0, 0));
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}
bool Game_MemoryCard::myInit()
{
    if (!CCSprite::init())
        
    {
        
        return false;
        
    }
    m_isOpened = false;
    type = 0;
   
    
    CCSprite* inCard = CCSprite::createWithSpriteFrameName("GameMemoryCard00.png");
    
    inCard->setPosition(CCPoint(92, 77.5));
    
    inCard->setVisible(false);
    
    inCard->setTag(1);
    
    addChild(inCard);
    

    outCard = CCSprite::createWithSpriteFrameName("GameMemoryCard00.png");
    outCard->setPosition(CCPoint(92, 77.5));
    
    outCard->setTag(2);
    
    addChild(outCard);
    m_openAnimIn = (CCActionInterval*)CCSequence::create(CCDelayTime::create(kDelay * .5),
                                                         
                                                         CCShow::create(),
                                                         
                                                         CCOrbitCamera::create(kDelay * .5, 1, 0, kInAngleZ, kInDeltaZ, 0, 0),
                                                         
                                                         NULL);
    
    m_openAnimIn->retain();
    
    m_openAnimOut = (CCActionInterval *)CCSequence::create(CCOrbitCamera::create(kDelay * .5, 1, 0, kOutAngleZ, kOutDeltaZ, 0, 0),
                                                           
                                                           CCHide::create(),
                                                           
                                                           CCDelayTime::create(kDelay * .5),
                                                           
                                                           NULL);
    
    m_openAnimOut->retain();
    return true;
}

void Game_MemoryCard::onEnter()
{
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    CCSprite::onEnter();
}
void Game_MemoryCard::onExit()
{
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
    CCSprite::onExit();
}

cocos2d::CCRect Game_MemoryCard::rect()
{
    return CCRectMake(getPositionX() - getContentSize().width * getAnchorPoint().x,
                      getPositionY() - getContentSize().height * getAnchorPoint().y,
                      getContentSize().width, getContentSize().height); // To be able to customize the size of their position with a function rather than inefficient use member variables directly

}

bool Game_MemoryCard::isTouchInside( CCTouch* touch )
{
    CCPoint touchLocation = touch->getLocation(); // Return to GL coordinates
    CCPoint localPos = convertToNodeSpace(touchLocation);
    CCRect rc = rect();
    rc.origin = CCPointZero;
    bool isTouched = rc.containsPoint(localPos);
    
    return isTouched;
}


bool Game_MemoryCard::ccTouchBegan(CCTouch *touch, CCEvent *event)
{
    return false;
}
void Game_MemoryCard::ccTouchMoved(CCTouch *touch ,CCEvent *event)
{
    
}



void Game_MemoryCard::ccTouchEnded(CCTouch *touch ,CCEvent *event)
{
    
}

void Game_MemoryCard::clickCard()
{
    if (!m_isOpened) {
        m_isOpened = true;
        CCSprite* inCard = (CCSprite*)getChildByTag(1);
        
        CCSprite* outCard = (CCSprite*)getChildByTag(2);
        inCard->stopAllActions();
        outCard->stopAllActions();
        inCard->runAction(m_openAnimOut);
        
        outCard->runAction(m_openAnimIn);
    }

}
void  Game_MemoryCard::delCallBack()
{
    this->getChildByTag(10)->removeFromParentAndCleanup(true);
    
}
void Game_MemoryCard::openCard()
{
    
    m_isOpened = false;
    CCSprite* inCard = (CCSprite*)getChildByTag(1);
    
    CCSprite* outCard = (CCSprite*)getChildByTag(2);
    
    outCard->runAction((CCActionInterval *)CCSequence::create(CCDelayTime::create(kShowTime),
                                                              
                                                              CCHide::create(),
                                                              CCDelayTime::create(kDelay *.5),
                                                              
                                                              NULL));
    inCard->runAction((CCActionInterval*)CCSequence::create(CCDelayTime::create(kShowTime+kDelay*.5),
                                                            
                                                            CCShow::create(),
                                                            
                                                            CCOrbitCamera::create(kDelay * 1, 1, 0, kInAngleZ, kInDeltaZ, 0, 0),
                                                            NULL));
    
//    outCard->runAction(m_openAnimOut);
//    
//    inCard->runAction(m_openAnimIn);
}
void Game_MemoryCard::setPic(int type)
{
    this->type = type;
    CCRect rect;
    
    char str[32];
    sprintf(str,"GameMemoryCard%d.png",type);
   
    if (type>0) {

       
        CCSprite* inCard = (CCSprite*)getChildByTag(1);
        
        CCSprite* outCard = (CCSprite*)getChildByTag(2);
        inCard->setVisible(true);
        outCard->setVisible(false);
        inCard->stopAllActions();
        outCard->stopAllActions();
        inCard->runAction(m_openAnimOut);
        
        outCard->runAction(m_openAnimIn);
        
    }else{
        sprintf(str,"GameMemoryCard00.png");
    }

    outCard->setTextureRect(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str)->getRect());
    this->type = type;
}
bool Game_MemoryCard::isOpen()
{
    return m_isOpened;
}
void Game_MemoryCard::setOpen(){
    m_isOpened = true;
}
void Game_MemoryCard::setClose(){
    m_isOpened = false;
}
int Game_MemoryCard::getType(void){
    return type;
}
void Game_MemoryCard::stopAction()
{
    CCSprite* inCard = (CCSprite*)getChildByTag(1);
    
    CCSprite* outCard = (CCSprite*)getChildByTag(2);
    inCard->stopAllActions();
    outCard->stopAllActions();
}
