//
// GameNewLinkerItems.cpp
// OnceAgain
//
// Created by xiaohai on 14-5-19.
//
//

#include "GameNewLinkerItems.h"
#include "GameUIExportJson.h"

CCScene* GameNewLinkerItems::createScene()
{
    auto scene = CCScene::create();
    auto layer = GameNewLinkerItems::create();
    scene->addChild(layer);
    return scene;
}

bool GameNewLinkerItems::init()
{
    if ( !CCSprite::init() )
    {
        return false;
    }
    isLinkOk = false;
    isOnLine = false;
    return true;
}

void GameNewLinkerItems::createPicByTag(int tag, bool isboom, int picKind) {
    type = tag;
    isBoomMap = isboom;
    picType = picKind;
    CCString str;
    if (tag <= 6) {
        str.initWithFormat("icons/%d/images/face_%d_0.png", picKind, picKind);
        pic_face = CCSprite::createWithSpriteFrameName(str.getCString());
        this -> addChild(pic_face,1);
        
        str.initWithFormat("icons/%d/images/face_%d_1.png", picKind, picKind);
        pic_normol = CCSprite::createWithSpriteFrameName(str.getCString());
        pic_normol -> setPosition(ccp(pic_face->getContentSize().width/2, pic_face->getContentSize().height/2));
        pic_face -> addChild(pic_normol);
        
        str.initWithFormat("icons/%d/images/face_%d_2.png", picKind, picKind);
        pic_onClick = CCSprite::createWithSpriteFrameName(str.getCString());
        pic_onClick -> setPosition(pic_normol->getPosition());
        pic_face -> addChild(pic_onClick);
        pic_onClick -> setVisible(false);
    }
    else if (tag == 7) {
        pic_face = CCSprite::create("Link/star_g.png");
        CCAnimation* pAni = CCAnimation::create();
        pAni->addSpriteFrameWithFileName("Link/star_g.png");
        pAni->addSpriteFrameWithFileName("Link/star_b.png");
        pAni->setDelayPerUnit(0.15f);
        pAni->setLoops(1);
        pic_face -> runAction(CCRepeatForever::create(CCAnimate::create(pAni)));
        picType = 7;
        this -> addChild(pic_face,1);
    }
    else if (tag == 8) {
        str.initWithFormat("icons/box_5w.png");
        pic_face = CCSprite::createWithSpriteFrameName(str.getCString());
        picType = 8;
        this -> addChild(pic_face,1);
    }
    if (isboom) {
        str.initWithFormat("Link/linker_boom.png");
        boom_pic = CCSprite::create(str.getCString());
        boom_pic -> setPosition(ccp(pic_face->getContentSize().width-20 , pic_face->getContentSize().height));
//        boom_pic -> setScale(0.5);
        boom_pic -> setRotation(20);
        pic_face -> addChild(boom_pic, 10);
        CCActionInterval* actionto = CCScaleTo::create(0.8, 1.03);
        CCActionInterval* actionback = CCScaleTo::create(0.8, 0.98);
        CCActionInterval* rpAction = CCSequence::create(actionto, actionback, NULL);
        CCRepeatForever*  pRepeateScale = CCRepeatForever::create(rpAction);
        boom_pic -> runAction(pRepeateScale);
        
    }
    
    str.initWithFormat("./Link/lightClick.png");
    pic =  CCSprite::create(str.getCString());
    pic -> setZOrder(0);
    pic -> setVisible(false);
    this -> addChild(pic);
 
}

int GameNewLinkerItems::getItemType() {
    return type;
}
int GameNewLinkerItems::getPicType() {
    return picType;
}


void GameNewLinkerItems::picBeClick() {
    if (picType == 7) {
        return;
    }
    CCActionInterval *a = CCRotateBy::create(2, 45);
    CCActionInterval* rpAction1 = CCSequence::create(a, NULL);
    CCRepeatForever*  pRepeateRotate= CCRepeatForever::create(rpAction1);
    pRepeateRotate -> setTag(101);
    pic -> setVisible(true);
    pic -> runAction(pRepeateRotate);
    if (type <= 6) {
        pic_normol->setVisible(false);
        pic_onClick->setVisible(true);
    }
    CCActionInterval* actionto = CCScaleTo::create(0.4, 1.1);
    CCActionInterval* actionback = CCScaleTo::create(0.4, 1);
    CCActionInterval* rpAction = CCSequence::create(actionto, actionback, NULL);
    CCRepeatForever*  pRepeateScale = CCRepeatForever::create(rpAction);
    pRepeateScale -> setTag(100);
    pic_face -> runAction(pRepeateScale);
}

//所有动作停止
void GameNewLinkerItems::stopAllAction() {
    pic -> setVisible(false);
    
    if (type <= 6) {
        pic_normol->setVisible(true);
        pic_onClick->setVisible(false);
    }
   
    pic_face -> stopActionByTag(100);
    pic -> stopActionByTag(101);
}

void GameNewLinkerItems::doLinkOKAction() {
    isLinkOk = true;
    isOnLine = true;
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
    pic->runAction(CCSequence::create(CCShow::create(),CCRepeat::create(animate, 1),CCHide::create(), CCRemoveSelf::create(), NULL));
    
    
    if (isBoomMap) {
        boom_pic -> stopAllActions();
        boom_pic -> removeFromParentAndCleanup(true);
    }
}
