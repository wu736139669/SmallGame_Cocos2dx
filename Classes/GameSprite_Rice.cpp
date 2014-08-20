//
//  Game_Rice.cpp
//  OnceAgain
//
//  Created by mac on 14-3-5.
//
//

#include "GameSprite_Rice.h"
enum KEY_SPRITE
{
    Key_Add = 100,
    Key_Time,
    Key_Rice = 1000
};
GameSprite_Rice::~GameSprite_Rice()
{
    
}

bool GameSprite_Rice::init()
{
    if (!CCSprite::init()) {
        return false;
    }
    this->setContentSize(CCSize(500, 70));
    addRiceTime = RICEADDTIME;
    riceNum = 0;
    nowTime = 0;
    nowTime = this->getCurrentTime();
    //字体背景.
    CCMenuItemImage *labelBgSprite = CCMenuItemImage::create();
    labelBgSprite->setNormalSpriteFrame(GameShare_Texture::sharedTexture()->GetSpriteFrameByCCRect(akoomenu_image, CCRect(1763, 255, 120, 49)));
    labelBgSprite->setAnchorPoint(CCPointZero);
    labelBgSprite->setPosition(CCPointZero);
    labelBgSprite->setTag(Key_Add);
    CCMenu* pMenu = CCMenu::create(labelBgSprite, NULL);
    pMenu->setPosition(ccp(300,0));
    pMenu->setTag(Key_Add);
    this->addChild(pMenu);
    
    //时间标签.
    CCLabelTTF *timeLabel = CCLabelTTF::create("", "Arial", 20);
    ccColor3B color = ccc3(95, 46, 33);
    char strTime[32];
    sprintf(strTime,"%d:%d%d",addRiceTime/60,addRiceTime%60/10,addRiceTime%60%10);
    timeLabel->setColor(color);
    timeLabel->setString(strTime);
    timeLabel->setTag(Key_Time);
    timeLabel->setPosition(ccp(pMenu->getPositionX()+40, pMenu->getPositionY()+20));
    this->addChild(timeLabel);
    //饭的背景
    CCSprite *riceBgSprite = GameShare_Texture::sharedTexture()->GetSpriteByCCRect(akoomenu_image, CCRect(1, 1570, 278, 30));
    riceBgSprite->setAnchorPoint(CCPointZero);
    riceBgSprite->setPosition(ccp(0,5));
    this->addChild(riceBgSprite);
    
    this->schedule(schedule_selector(GameSprite_Rice::timeUpdate), 1.0);
    return true;
}


#pragma mark rice

int GameSprite_Rice::getRiceNum()
{
    return riceNum;
}
void GameSprite_Rice::setRiceNum(int var)
{
    riceNum = var;
    if (riceNum > 5) {
        
    }
}
bool GameSprite_Rice::addOneRice(void)
{
    riceNum++;
    if (riceNum <= 5) {
        RiceSprite *riceSprite = RiceSprite::create();
        riceSprite->setPosition(ccp(20+60*(riceNum-1),20));
        riceSprite->setTag(Key_Rice+riceNum);
        this->addChild(riceSprite);
        if (riceNum == 5) {
            if (this->getChildByTag(Key_Time)) {
                ((CCLabelTTF*)this->getChildByTag(Key_Time))->setString("Max");
            }
            this->unschedule(schedule_selector(GameSprite_Rice::timeUpdate));
        }

    }else if(riceNum > 5){
        char strTime[32];
        sprintf(strTime,"+%d",riceNum-5);
        if (this->getChildByTag(Key_Time)) {
            ((CCLabelTTF*)this->getChildByTag(Key_Time))->setString(strTime);
        }
        this->unschedule(schedule_selector(GameSprite_Rice::timeUpdate));
    }
    
    return true;
}
bool GameSprite_Rice::reduceOneRice(void)
{
    if (riceNum<=0) {
        return false;
    }
    if (riceNum <= 5) {
        if ( this->getChildByTag(Key_Rice+riceNum)) {
            this->getChildByTag(Key_Rice+riceNum)->removeFromParent();
        }
        if (riceNum == 5) {
            this->schedule(schedule_selector(GameSprite_Rice::timeUpdate), 1.0);
        }
       
    }
    riceNum--;
    return true;
}

void GameSprite_Rice::setTarget(cocos2d::CCObject *rec, SEL_MenuHandler selector)
{
    if (this->getChildByTag(Key_Add)->getChildByTag(Key_Add)) {
        ((CCMenuItemImage*)this->getChildByTag(Key_Add)->getChildByTag(Key_Add))->setTarget(rec, selector);
    }
}

#pragma mark time
void GameSprite_Rice::timeUpdate(float dt)
{
    long current = this->getCurrentTime();
    
    int riceAddNum = (current-nowTime)/(1000.0*RICEADDTIME);
    if (riceAddNum>=1) {
        addRiceTime = RICEADDTIME-((current-nowTime)- riceAddNum*(1000.0*RICEADDTIME))/1000.0;
        nowTime = current;
        //计算下一个要的时间
        for (int i = 0; i<riceAddNum; i++) {
            
            this->addOneRice();
            if (riceNum>=5) {
                break;
            }
        }
    }else{
        addRiceTime = RICEADDTIME-(current-nowTime)/1000.0;

    }
    if (riceNum < 5) {
        char strTime[32];
        sprintf(strTime,"%d:%d%d",addRiceTime/60,addRiceTime%60/10,addRiceTime%60%10);
        if (this->getChildByTag(Key_Time)) {
            ((CCLabelTTF*)this->getChildByTag(Key_Time))->setString(strTime);
        }
    }

    
}
long  GameSprite_Rice::getCurrentTime()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
    
}

#pragma mark RiceSprite
enum KEY_RICESPRITE
{
    Key_Normal = 100,
    Key_Cry,
    Key_Laugh
    
};
bool RiceSprite::init()
{
    if (!CCSprite::init()) {
        return false;
    }

    
    //平时的饭.
    CCSprite *normalSprite = GameShare_Texture::sharedTexture()->GetSpriteByCCRect(akoomenu_image, CCRect(564, 534, 62, 66));
    normalSprite->setPosition(CCPointZero);
    normalSprite->setTag(Key_Normal);
//    normalSprite->setVisible(false);
    this->addChild(normalSprite);
    
    //哭的时候的饭
    CCSprite *crySprite = GameShare_Texture::sharedTexture()->GetSpriteByCCRect(akoomenu_image, CCRect(839, 873, 62, 66));
    crySprite->setTag(Key_Cry);
    crySprite->setPosition(CCPointZero);
//    crySprite->setVisible(false);
    crySprite->runAction(CCSequence::create(CCScaleTo::create(0.5, 1.2),CCScaleTo::create(0.5, 1.0),CCHide::create(),NULL));
    this->addChild(crySprite);
    
    //笑的时候的饭
    CCSprite *laughSprite = GameShare_Texture::sharedTexture()->GetSpriteByCCRect(akoomenu_image, CCRect(1581, 95, 34, 17));
    laughSprite->setTag(Key_Laugh);
    laughSprite->setPosition(ccp(0,-10));
    laughSprite->setVisible(false);
    this->addChild(laughSprite);
    
    this->schedule(schedule_selector(RiceSprite::showAction), 8.0);
    return true;
}
void RiceSprite::showAction(float)
{
    CCSprite* normalSprite = (CCSprite*)this->getChildByTag(Key_Normal);
    CCSprite* crySprite = (CCSprite*)this->getChildByTag(Key_Cry);
    CCSprite* laughSprite = (CCSprite*)this->getChildByTag(Key_Laugh);
    
    if (normalSprite && crySprite && laughSprite) {
        crySprite->runAction(CCSequence::create(CCShow::create(),CCScaleTo::create(0.5, 0.9, 1.1),CCScaleTo::create(0.5, 1.0),CCScaleTo::create(0.5, 0.9, 1.1),CCScaleTo::create(0.5, 1.0),CCDelayTime::create(0.5),CCHide::create(),NULL));
        laughSprite->runAction(CCSequence::create(CCDelayTime::create(4.0),CCShow::create(),CCDelayTime::create(0.3),CCHide::create(),CCDelayTime::create(0.3),CCShow::create(),CCDelayTime::create(0.3),CCHide::create(),CCDelayTime::create(1.0),NULL));
    }
}
RiceSprite::~RiceSprite()
{
    
}