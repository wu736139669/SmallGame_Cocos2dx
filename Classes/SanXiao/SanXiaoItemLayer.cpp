//
//  SanXiaoItemLayer.cpp
//  OnceAgain
//
//  Created by xiaoqiang on 14-6-16.
//
//

#include "SanXiaoItemLayer.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#define myRand arc4random()

#else

#define myRand rand()

#endif

#define scroePic 250


CCScene* SanXiaoItemLayer::createScene()
{
    auto scene = CCScene::create();
    auto layer = SanXiaoItemLayer::create();
    scene->addChild(layer);
    return scene;
}

bool SanXiaoItemLayer::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    picNumber = 0;
    initUiData();
    BindingUIItems();
    return true;
}

void SanXiaoItemLayer::creatItemByTag(int num) {
    this -> stopAllActions();
    this -> removeAllChildrenWithCleanup(true);
    CCString str;
    if (num == 1) {
        picNumber = myRand%4 + 1;
    }
    else if (num == 2) {
        picNumber = myRand%5 + 1;
    }
    else {
        picNumber = num;
    }
        
    if (num <= 2) {
        str.initWithFormat("SanXiao/Items/Item_%d_0.png", picNumber);
        picNormol = CCSprite::create(str.getCString());
        str.initWithFormat("SanXiao/Items/Item_%d_2.png", picNumber);
        picOnClick = CCSprite::create(str.getCString());
        this -> addChild(picNormol);
        this -> addChild(picOnClick);
        picOnClick -> setVisible(false);
        this -> runAction(CCSequence::create(CCDelayTime::create(CCRANDOM_0_1()* 60), CCCallFunc::create(this, callfunc_selector(SanXiaoItemLayer::doOpenEyeAction)), NULL));
    }
    else if (num == boomPic) {
        str.initWithFormat("common/bomb.png");
        picNormol = CCSprite::createWithSpriteFrameName(str.getCString());
        picNormol -> setPosition(ccp(0, 5));
        picNormol -> setScale(0.7);
        this -> addChild(picNormol);
        picNormol -> runAction(CCRepeatForever::create(CCSequence::create(CCScaleTo::create(2, 0.72), CCScaleTo::create(2, 0.68), NULL)));
        
    }
    else if (num == heng_Cross) {
        str.initWithFormat("SanXiao/heng_1.png");
        picNormol = CCSprite::create(str.getCString());
        this -> addChild(picNormol);
        CCAnimation* pAni = CCAnimation::create();
        
        for (int i = 0; i < 4; i ++) {
            str.initWithFormat("SanXiao/heng_%d.png", i + 1);
            pAni->addSpriteFrameWithFileName(str.getCString());
        }
      
        pAni->setDelayPerUnit(0.06f);
        pAni->setLoops(1);
        
        CCAnimate *animate = CCAnimate::create(pAni);
        picNormol -> runAction(CCRepeatForever::create(CCSequence::create(animate, NULL)));
        
    }
    else if (num == zong_Cross) {
        str.initWithFormat("SanXiao/zong_1.png");
        picNormol = CCSprite::create(str.getCString());
        this -> addChild(picNormol);
        CCAnimation* pAni = CCAnimation::create();
        
        for (int i = 0; i < 4; i ++) {
            str.initWithFormat("SanXiao/zong_%d.png", i + 1);
            pAni->addSpriteFrameWithFileName(str.getCString());
        }
        
        pAni->setDelayPerUnit(0.06f);
        pAni->setLoops(1);
        
        CCAnimate *animate = CCAnimate::create(pAni);
        picNormol -> runAction(CCRepeatForever::create(CCSequence::create(animate, NULL)));

    } else if (num == threeCross) {
        str.initWithFormat("SanXiao/sanHeng_1.png");
        picNormol = CCSprite::create(str.getCString());
        this -> addChild(picNormol);
        CCAnimation* pAni = CCAnimation::create();
        
        for (int i = 0; i < 4; i ++) {
            str.initWithFormat("SanXiao/sanHeng_%d.png", i + 1);
            pAni->addSpriteFrameWithFileName(str.getCString());
        }
        
        pAni->setDelayPerUnit(0.06f);
        pAni->setLoops(1);
        
        CCAnimate *animate = CCAnimate::create(pAni);
        picNormol -> runAction(CCRepeatForever::create(CCSequence::create(animate, NULL)));

    }
}

int SanXiaoItemLayer::getItemType() {
    return picNumber;
}

void SanXiaoItemLayer::doOpenEyeAction() {
    CCString str;
    CCAnimation* pAni = CCAnimation::create();
    
    str.initWithFormat("SanXiao/Items/Item_%d_0.png", picNumber);
    pAni->addSpriteFrameWithFileName(str.getCString());
    
    str.initWithFormat("SanXiao/Items/Item_%d_1.png", picNumber);
    pAni->addSpriteFrameWithFileName(str.getCString());
    
    str.initWithFormat("SanXiao/Items/Item_%d_0.png", picNumber);
    pAni->addSpriteFrameWithFileName(str.getCString());
    
    pAni->setDelayPerUnit(1.3f);
    pAni->setLoops(1);
    
    CCAnimate *animate = CCAnimate::create(pAni);
  
    picNormol -> runAction(CCRepeatForever::create(CCSequence::create(animate, CCDelayTime::create(30), NULL)));
}


void SanXiaoItemLayer::boomAndDel() {
    picNormol -> setVisible(false);
    CCAnimation* pAni = CCAnimation::create();
    CCString str;
    for (int i = 1; i <=5; i ++)
    {
        str.initWithFormat("./effect/bomb/%d.png",i);
        pAni->addSpriteFrameWithFileName(str.getCString());
    }
    
    pAni->setDelayPerUnit(.06);
    
    CCAnimate *animate = CCAnimate::create(pAni);
    auto *pic = CCSprite::create("./effect/bomb/1.png");
    this -> addChild(pic, 100);
    pic->runAction(CCSequence::create(CCShow::create(),CCRepeat::create(animate, 1),CCHide::create(), CCCallFunc::create(this, callfunc_selector(SanXiaoItemLayer::removeSelFromp)), NULL));
}

void SanXiaoItemLayer::removeSelFromp() {
    this -> removeFromParentAndCleanup(true);
}

void SanXiaoItemLayer::onClick() {
    if (picNumber < 10) {
        picOnClick -> setVisible(true);
    }
}
void SanXiaoItemLayer::freeClick() {
    if (picNumber < 10) {
         picOnClick -> setVisible(false);
    }
}
#pragma mark - initData
void SanXiaoItemLayer::initUiData()
{
    
}

void SanXiaoItemLayer::BindingUIItems()
{
    
}
