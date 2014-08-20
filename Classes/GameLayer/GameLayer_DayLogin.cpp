//
//  GameLayer_DayLogin.cpp
//  OnceAgain
//
//  Created by mac on 14-3-24.
//
//

#include "GameLayer_DayLogin.h"
#include "GameLayer_Tag.h"
#include "TaskManager.h"
#include "PlayerInfoManager.h"

GameLayer_DayLogin::~GameLayer_DayLogin()
{
    GUIReader::shareReader()->purgeGUIReader();
    DictionaryHelper::shareHelper()->purgeDictionaryHelper();
    ActionManager::shareManager()->purgeActionManager();
}


bool GameLayer_DayLogin::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    //系统设置界面.
    dayLogin = UILayer::create();
    auto layout = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("./CocoStudioResources/DayLogin.json"));
    dayLogin->addWidget(layout);
    //    sysSet->setVisible(true);
    this->addChild(dayLogin, 0, 101);
    
    UIPanel* panel = dynamic_cast<UIPanel*>(dayLogin->getWidgetByName("DayLogin"));
    panel->setBackGroundColor(ccBLACK);
    panel->setBackGroundColorOpacity(150);
    //关闭按钮
    UIButton* sureBtn = dynamic_cast<UIButton*>(dayLogin->getWidgetByName("SureBtn"));
    sureBtn->addReleaseEvent(this, coco_releaseselector(GameLayer_DayLogin::sureBtnCallback));
    sureBtn->setPressedActionEnabled(true);
    
    CCScaleTo *beSm0le = CCScaleTo::create(1, 0.8);
    CCScaleTo *beBig = CCScaleTo::create(1, 1);
    
    UIImageView *image_3 = dynamic_cast<UIImageView*>(dayLogin-> getWidgetByName("Image_3"));
    image_3 -> runAction(CCRepeatForever::create(CCSequence::create(beSm0le,beBig,NULL)));
    
    
    UIImageView *light = dynamic_cast<UIImageView*>(dayLogin -> getWidgetByName("Image_4"));
    light->runAction(CCRepeatForever::create(CCRotateBy::create(5.0, 360)));
    this->setShowState();
    this->setVisible(true);
    return true;
}
void GameLayer_DayLogin::setShowState()
{
    if (CPlayerInfoMan::sharedInstance().getPlayerInfo().nDailyTaskId == 1) {

        UIImageView* isGetImg = dynamic_cast<UIImageView*>(dayLogin->getWidgetByName("Day1"));
        isGetImg->setTexture("./CocoStudioResources/DayLogin/IsOneBg.png");
    }
    if (CPlayerInfoMan::sharedInstance().getPlayerInfo().nDailyTaskId == 7) {
        
        UIImageView* isGetImg = dynamic_cast<UIImageView*>(dayLogin->getWidgetByName("Day7"));
        isGetImg->setTexture("./CocoStudioResources/DayLogin/IsSevenBg.png");
    }

    for (int i=1; i<CPlayerInfoMan::sharedInstance().getPlayerInfo().nDailyTaskId; i++) {
        CCString isStr;
        isStr.initWithFormat("IsGet%d",i);
        UIImageView* isGetImg = dynamic_cast<UIImageView*>(dayLogin->getWidgetByName(isStr.getCString()));
        isGetImg->setVisible(true);
        if (i==CPlayerInfoMan::sharedInstance().getPlayerInfo().nDailyTaskId-1) {
            isStr.initWithFormat("Day%d",CPlayerInfoMan::sharedInstance().getPlayerInfo().nDailyTaskId);
            UIImageView* isGetImg = dynamic_cast<UIImageView*>(dayLogin->getWidgetByName(isStr.getCString()));
            isGetImg->setTexture("./CocoStudioResources/DayLogin/IsDayBg.png");
            //加入转圈
            CCSprite* light = CCSprite::create("./CocoStudioResources/DayLogin/Light.png");
            light->runAction(CCRepeatForever::create(CCRotateBy::create(5.0, 360)));
            isGetImg->addRenderer(light, 0);
            //加入星星
            for (int i=0; i<5; i++) {
                CCSprite* starSprite = CCSprite::create("./CocoStudioResources/ItemStrengthern/EffectStar.png");
                CCSequence *seque = CCSequence::create(CCFadeTo::create(0.2, 150),CCFadeTo::create(0.3, 255),NULL);
                CCActionInterval* ccScale = CCSequence::create(CCScaleTo::create(0.2, 0.3), CCScaleTo::create(0.3, 0.8), NULL);
                CCActionInterval *spawn = CCSpawn::create(seque, ccScale, NULL);
                
                starSprite->runAction(CCRepeatForever::create(spawn));
                starSprite->setPosition(isGetImg->getPosition());
                isGetImg->addRenderer(starSprite, 10);
                switch (i) {
                    case 0:
                        starSprite->setPosition(ccp(-40, 30));
                        break;
                    case 1:
                        starSprite->setPosition(ccp(0, 50));
                        break;
                    case 2:
                        starSprite->setPosition(ccp(40, 30));
                        break;
                    case 3:
                        starSprite->setPosition(ccp(00, 0));
                        break;
                    case 4:
                        starSprite->setPosition(ccp(0, -50));
                        break;
                        
                    default:
                        break;
                }
                
                
            }

        }
        
    }
    for (int i=0; i<CTaskMan::sharedInstance().getMoneyChgTmpData().size(); i++) {
        sTaskData *pData = CTaskMan::sharedInstance().getChgTempData(i);
        
        if (pData) {
            CCString goldNumStr;
            goldNumStr.initWithFormat("GoldText%d",i);
            UILabel* goldText = dynamic_cast<UILabel*>(dayLogin->getWidgetByName(goldNumStr.getCString()));
            goldNumStr.initWithFormat("+%d",pData->TaskRewardValue);
            goldText->setText(goldNumStr.getCString());
        }
    }
}
void GameLayer_DayLogin::setVisible(bool visible)
{
    CCLayer::setVisible(visible);
    UIPanel* dayLoginPanel = dynamic_cast<UIPanel*>(dayLogin->getWidgetByName("DayLogin"));
    dayLoginPanel->setTouchEnable(visible);
}

void GameLayer_DayLogin::sureBtnCallback(cocos2d::CCObject *pSender)
{
    CTaskMan::sharedInstance().RequestGetReward(CPlayerInfoMan::sharedInstance().getPlayerInfo().nDailyTaskId);
//    this->removeFromParent();
//    CPlayerInfoMan::sharedInstance().getPlayerInfo().nDailyTaskId = 6;
    CCSize visableSize = CCDirector::sharedDirector()->getVisibleSize();
    CCString str;
    UIImageView* isGetImg = dynamic_cast<UIImageView*>(dayLogin->getWidgetByName("Bg"));
    
    
    //消失
    isGetImg->runAction(CCSequence::create(CCFadeOut::create(0.4), CCHide::create(), NULL));
    //获取开始的位置
    CCPoint point = isGetImg->getPosition();
    switch (CPlayerInfoMan::sharedInstance().getPlayerInfo().nDailyTaskId) {
        case 1:
            point.x-=200;
            point.y+=100;
            break;
        case 2:
            point.x-=80;
            point.y+=100;
            break;
        case 3:
            point.x+=50;
            point.y+=100;
            break;
        case 4:
            point.x+=170;
            point.y+=100;
            break;
        case 5:
            point.x-=200;
            point.y-=70;
            break;
        case 6:
            point.x-=70;
            point.y-=70;
            break;
            
        default:
            point.x-=70;
            point.y-=70;
            break;
    }
    
    CCPoint goldPosition = ccp(visableSize.width/2-60,visableSize.height-45);
    
    //最后亮一下的金币.
    CCSprite* lightGold1 = CCSprite::create("./CocoStudioResources/DayLogin/WhiteGold.png");
    this->addChild(lightGold1,10);
    lightGold1->setPosition(goldPosition);
    lightGold1->setVisible(false);
    CCSequence* lightGoldAction1 = CCSequence::create(CCShow::create() ,CCFadeOut::create(0.5),NULL);
    CCSprite* lightGold2 = CCSprite::create("./CocoStudioResources/DayLogin/WhiteGold.png");
    this->addChild(lightGold2,10);
    lightGold2->setPosition(goldPosition);
    lightGold2->setVisible(false);
    CCSequence* lightGoldAction2 = CCSequence::create(CCShow::create() ,CCFadeOut::create(0.5),NULL);
    CCSprite* lightGold3 = CCSprite::create("./CocoStudioResources/DayLogin/WhiteGold.png");
    this->addChild(lightGold3,10);
    lightGold3->setVisible(false);
    CCSequence* lightGoldAction3 = CCSequence::create(CCShow::create() ,CCFadeOut::create(0.5),NULL);
    lightGold3->setPosition(goldPosition);
    
    //钱的闪光.
    CCAnimation* pAni = CCAnimation::create();
    for (int i=1; i<=3; i++) {
        str.initWithFormat("./CocoStudioResources/DayLogin/Star%d.png",i);
        pAni->addSpriteFrameWithFileName(str.getCString());
    }
    pAni->setDelayPerUnit(0.3f/3.f);
    pAni->setLoops(1);
    
   
    //金币爆炸效果.
    CCSprite* goldEffect1 = CCSprite::create();
    goldEffect1->setVisible(false);
    auto *pic_1 = CCSprite::create("./CocoStudioResources/DayLogin/Star1.png");
    goldEffect1->setTexture(pic_1 -> getTexture());
    goldEffect1->setTextureRect(CCRectMake(0, 0, pic_1 -> getContentSize().width, pic_1 -> getContentSize().height));
    goldEffect1->setPosition(ccp(visableSize.width/2,visableSize.height-50));
    CCSequence* goldAction1 = CCSequence::create(CCShow::create(), CCAnimate::create(pAni), CCHide::create(), NULL);
    this->addChild(goldEffect1, 10);
    
    CCSprite* goldEffect2 = CCSprite::create();
    goldEffect2->setVisible(false);
    auto *pic_2 = CCSprite::create("./CocoStudioResources/DayLogin/Star1.png");
    goldEffect2->setTexture(pic_2 -> getTexture());
    goldEffect2 -> setTextureRect(CCRectMake(0, 0, pic_2-> getContentSize().width, pic_2->getContentSize().height));
    goldEffect2->setPosition(ccp(visableSize.width/2,visableSize.height-50));
    CCSequence* goldAction2 = CCSequence::create(CCShow::create(), CCAnimate::create(pAni), CCHide::create(), NULL);
    this->addChild(goldEffect2, 10);
    
    CCSprite* goldEffect3 = CCSprite::create();
    goldEffect3->setVisible(false);
    auto *pic_3 = CCSprite::create("./CocoStudioResources/DayLogin/Star1.png");
    
    goldEffect3->setTexture(pic_3 -> getTexture());
    goldEffect3->setTextureRect(CCRectMake(0, 0, pic_3 -> getContentSize().width, pic_3 -> getContentSize().height));
    goldEffect3->setPosition(ccp(visableSize.width/2,visableSize.height-50));
    CCSequence* goldAction3 = CCSequence::create(CCShow::create(), CCAnimate::create(pAni), CCHide::create(),CCCallFunc::create(this, callfunc_selector(GameLayer_DayLogin::DoCallBack)) ,CCCallFunc::create(this, callfunc_selector(GameLayer_DayLogin::removeFromParent)), NULL);
//        CCSequence* goldAction3 = CCSequence::create(CCShow::create(), CCAnimate::create(pAni), CCHide::create(), NULL);
    this->addChild(goldEffect3, 10);
    //飞行的钱币.
    CCSprite* flyGold1 = CCSprite::create("./CocoStudioResources/DayLogin/FlyGold.png");
    flyGold1->setVisible(false);
    flyGold1->setPosition(point);
    this->addChild(flyGold1, 10);
    CCSequence* flyAction1 = CCSequence::create(CCShow::create(), CCMoveTo::create(0.6, goldPosition),  CCCallFuncO::create(lightGold3, callfuncO_selector(CCSprite::runAction), lightGoldAction3), CCCallFuncO::create(goldEffect1, callfuncO_selector(CCSprite::runAction), goldAction1), CCHide::create(), NULL);
    CCSprite* flyGold2 = CCSprite::create("./CocoStudioResources/DayLogin/FlyGold.png");
    flyGold2->setVisible(false);
    flyGold2->setScale(0.9);
    flyGold2->setPosition(point);
    this->addChild(flyGold2, 10);
    CCSequence* flyAction2 = CCSequence::create(CCDelayTime::create(0.3), CCShow::create(), CCMoveTo::create(0.6, goldPosition),CCCallFuncO::create(lightGold2, callfuncO_selector(CCSprite::runAction), lightGoldAction2), CCCallFuncO::create(goldEffect2, callfuncO_selector(CCSprite::runAction), goldAction2),  CCHide::create(), NULL);
    CCSprite* flyGold3 = CCSprite::create("./CocoStudioResources/DayLogin/FlyGold.png");
    flyGold3->setVisible(false);
    flyGold3->setScale(0.8);
    flyGold3->setPosition(point);
    this->addChild(flyGold3, 10);
    CCSequence* flyAction3 = CCSequence::create(CCDelayTime::create(0.6), CCShow::create(), CCMoveTo::create(0.6, goldPosition), CCCallFuncO::create(goldEffect3, callfuncO_selector(CCSprite::runAction), goldAction3), CCCallFuncO::create(lightGold1, callfuncO_selector(CCSprite::runAction), lightGoldAction1), CCHide::create(), NULL);
    
    //爆炸的闪光效果.
    CCSprite* riceEffect = CCSprite::create();
    pAni = CCAnimation::create();
    for (int i=1; i<=4; i++) {
        str.initWithFormat("./CocoStudioResources/DayLogin/Boom%d.png",i);
        pAni->addSpriteFrameWithFileName(str.getCString());
    }
    pAni->setDelayPerUnit(0.3f/4.f);
    pAni->setLoops(1);
    auto *pic_4 = CCSprite::create("./CocoStudioResources/DayLogin/Boom1.png");
    riceEffect->setTexture(pic_4 -> getTexture());
    riceEffect->setTextureRect(CCRectMake(0, 0, pic_4 -> getContentSize().width, pic_4 -> getContentSize().height));
    riceEffect->setPosition(point);
    this->addChild(riceEffect, 0);
    riceEffect->runAction(CCSequence::create(CCAnimate::create(pAni),CCHide::create(), CCCallFuncO::create(flyGold1, callfuncO_selector(CCSprite::runAction), flyAction1), CCCallFuncO::create(flyGold2, callfuncO_selector(CCSprite::runAction), flyAction2), CCCallFuncO::create(flyGold3, callfuncO_selector(CCSprite::runAction), flyAction3),NULL));

    
}

void GameLayer_DayLogin::setCallBcak(cocos2d::CCObject *p, SEL_CallFunc call) {
    target = p;
    callBack = call;
}

void GameLayer_DayLogin::DoCallBack() {
    if (target && callBack) {
        (target->*callBack)();
    }
}