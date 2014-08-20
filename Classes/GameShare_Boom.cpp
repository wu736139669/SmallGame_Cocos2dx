//
//  GameShare_Boom.cpp
//  OnceAgain
//
//  Created by mac on 14-3-6.
//
//

#include "GameShare_Boom.h"
#include "SpriteFrameManage.h"
enum KEY_SPRITE
{
    Key_Energy = 100,
    Key_Boom
};
GameShare_Boom::GameShare_Boom(void)
{
    
}
GameShare_Boom::~GameShare_Boom(void)
{
    
}

bool GameShare_Boom::init(void)
{
    if (!CCSprite::init()) {
        return false;
    }
    maxEnergy = 40;
    //能量槽
    CCSprite* energyTank = CCSprite::createWithSpriteFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName("common/boom_slot.png"));
    energyTank->setAnchorPoint(CCPointZero);
    energyTank->setPosition(ccp(30-11, 0));
    addChild(energyTank);

    //能量条
    CCSprite* energy = CCSprite::createWithSpriteFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName("common/boom_bar.png"));
    energy->setAnchorPoint(CCPointZero);
    energy->setPosition(ccp(38-11+4, 11));
    energy->setTag(Key_Energy);
    addChild(energy);
    
    //炸弹
    CCSprite* boom = CCSprite::createWithSpriteFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName("common/boom_head.png"));
    boom->setPosition(ccp(40-11, 50));
    boom->setTag(Key_Boom);
//    boom->setVisible(false);
    addChild(boom);
    
    return true;
}

void GameShare_Boom::addEnergy(unsigned int energyNum)
{
    CCScaleTo *scaleBig = CCScaleTo::create(0.1, 1.5);
    CCScaleTo *scalemid = CCScaleTo::create(0.1, 1);
    if (this->getChildByTag(Key_Boom) && this->getChildByTag(Key_Energy)) {
        this->getChildByTag(Key_Boom)->runAction(CCSequence::create(scaleBig,scalemid,NULL));
        
        CCSprite *energy = (CCSprite*)this->getChildByTag(Key_Energy);
        CCRect rect = energy->getTextureRect();
		const CCRect& rcSrc = CCSpriteFrameManage::getInstance()->spriteFrameByName("common/boom_bar.png")->getRect();
        rect.size.width += (rcSrc.size.width/(float)maxEnergy)*((float)energyNum);
        if (rect.size.width >= rcSrc.size.width) {
            CCNotificationCenter::sharedNotificationCenter()->postNotification(kGameBoomFull, NULL);
            rect.size.width -= rcSrc.size.width;
        }
        energy->setTextureRect(rect);
    }

}
void GameShare_Boom::setEnergy(unsigned int energyNum)
{
    CCScaleTo *scaleBig = CCScaleTo::create(0.1, 1.5);
    CCScaleTo *scalemid = CCScaleTo::create(0.1, 1);
    if (this->getChildByTag(Key_Boom) && this->getChildByTag(Key_Energy)) {
        this->getChildByTag(Key_Boom)->runAction(CCSequence::create(scaleBig,scalemid,NULL));
        
        CCSprite *energy = (CCSprite*)this->getChildByTag(Key_Energy);
        CCRect rect = energy->getTextureRect();
		const CCRect& rcSrc = CCSpriteFrameManage::getInstance()->spriteFrameByName("common/boom_bar.png")->getRect();
        rect.size.width = (rcSrc.size.width/(float)maxEnergy)*((float)energyNum);
        if (rect.size.width >= rcSrc.size.width) {
            CCNotificationCenter::sharedNotificationCenter()->postNotification(kGameBoomFull, NULL);
            rect.size.width = 0;
        }
        energy->setTextureRect(rect);
    }
}
void GameShare_Boom::resetEnergy()
{
    CCSprite *energy = (CCSprite*)this->getChildByTag(Key_Energy);
    if (energy) {
        CCRect rect = energy->getTextureRect();
        rect.size.width = 0;
        energy->setTextureRect(rect);
    }

}