//
//  GameLayer_Logo.cpp
//  OnceAgain
//
//  Created by mac on 14-4-16.
//
//

#include "GameLayer_Logo.h"
GameLayer_Logo::GameLayer_Logo()
{
    
}
GameLayer_Logo::~GameLayer_Logo()
{
    GUIReader::shareReader()->purgeGUIReader();
	DictionaryHelper::shareHelper()->purgeDictionaryHelper();
	ActionManager::shareManager()->purgeActionManager();
}

bool GameLayer_Logo::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    //获取屏幕大小
    CCSize visiableSize = CCDirector::sharedDirector()->getVisibleSize();
    
    UILayer* ul = UILayer::create();
    auto myLayout = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("./CocoStudioResources/Logo.json"));
    ul->addWidget(myLayout);
    ul->setContentSize(visiableSize);
    this->addChild(ul, 1, 100);
    

    

    
    //背后的彩虹.
    UIImageView* rainBow = dynamic_cast<UIImageView*>(ul->getWidgetByName("Label5"));
    rainBow->setVisible(false);
    CCActionInterval* ranBowAct = CCFadeIn::create(0.5);
    //火箭
    CCSprite* rocket = CCSprite::create("CocoStudioResources/Welcome/Rocket1.png");
    this->addChild(rocket,0);
    rocket->setVisible(false);
    rocket->setPosition(ccp(visiableSize.width/2+180, visiableSize.height-80));
    CCAnimation* pAni = CCAnimation::create();
    CCString str;
    for (int i=1; i<=5; i++) {
        str.initWithFormat("CocoStudioResources/Welcome/Rocket%d.png",i);
        pAni->addSpriteFrameWithFileName(str.getCString());
//        pAni->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str.getCString()));
    }
    pAni->setDelayPerUnit(1.5f/5.f);
    pAni->setLoops(1);
//    rocket->setDisplayFrame(CCSprite::create(("Welcome/Rocket1.png"));
    CCFiniteTimeAction* rocketAct1 = CCRepeatForever::create(CCAnimate::create(pAni));
    CCFiniteTimeAction* rocketAct2 = CCSequence::create(CCShow::create(), CCMoveBy::create(0.0, ccp(-10, -20)), CCMoveBy::create(0.1, ccp(10, 20)), CCCallFuncO::create(rocket, callfuncO_selector(CCSprite::runAction), rocketAct1), NULL);

    
    //第四个字.
    UIImageView* label4 = dynamic_cast<UIImageView*>(ul->getWidgetByName("Label4"));
    label4->setRotation(10);
    CCSequence* label1Act4 = CCSequence::create(CCDelayTime::create(0.5), CCShow::create(), CCMoveBy::create(0.0, ccp(0, 500)), CCMoveBy::create(0.3, ccp(0, -500)),
                                                CCCallFuncO::create(rainBow, callfuncO_selector(UIImageView::runAction), ranBowAct), CCCallFuncO::create(rocket, callfuncO_selector(CCSprite::runAction), rocketAct2), CCRotateTo::create(0.1, 0),   NULL);
    //第三个字.
    UIImageView* label3 = dynamic_cast<UIImageView*>(ul->getWidgetByName("Label3"));
    label3->setRotation(-10);
    CCSequence* label1Act3 = CCSequence::create(CCCallFuncO::create(label4, callfuncO_selector(UIImageView::runAction), label1Act4),CCDelayTime::create(0.5), CCShow::create(), CCMoveBy::create(0.0, ccp(0, 500)), CCMoveBy::create(0.3, ccp(0, -500)), CCRotateTo::create(0.1, 0),NULL);
    //第二个字.
    UIImageView* label2 = dynamic_cast<UIImageView*>(ul->getWidgetByName("Label2"));
    
    CCSequence* label1Act2 = CCSequence::create(CCCallFuncO::create(label3, callfuncO_selector(UIImageView::runAction), label1Act3),CCDelayTime::create(0.2), CCShow::create(), CCMoveBy::create(0.0, ccp(0, 500)), CCMoveBy::create(0.3, ccp(0, -500)), CCScaleTo::create(0.1, 1.0, 0.9), CCScaleTo::create(0.1, 1.0, 1.1), CCScaleTo::create(0.1, 1.0, 1.0),NULL);
    //第一个字.
    UIImageView* label1 = dynamic_cast<UIImageView*>(ul->getWidgetByName("Label1"));
    
    CCSequence* label1Act1 = CCSequence::create( CCCallFuncO::create(label2, callfuncO_selector(UIImageView::runAction), label1Act2), CCMoveBy::create(0.0, ccp(0, 500)),CCShow::create(), CCMoveBy::create(0.3, ccp(0, -500)), CCScaleTo::create(0.1, 1.0, 0.9), CCScaleTo::create(0.1, 1.0, 1.1), CCScaleTo::create(0.1, 1.0, 1.0),NULL);
    

    
  
    
    
    //第一个中间的人物
    UIImageView* people1 = dynamic_cast<UIImageView*>(ul->getWidgetByName("People1"));
    people1->setPosition(ccp(people1->getPosition().x, people1->getPosition().y-200));
    CCRepeatForever* people1Act1 = CCRepeatForever::create(CCSequence::create(CCMoveBy::create(0.6, ccp(0, 30)),CCMoveBy::create(0.6, ccp(0, -30)),NULL));
    CCSequence* people1Act2 = CCSequence::create(CCShow::create(), CCMoveBy::create(0.3, ccp(0, 200)), CCCallFuncO::create(people1, callfuncO_selector(UIImageView::runAction), people1Act1),  CCCallFuncO::create(label1, callfuncO_selector(UIImageView::runAction), label1Act1),  NULL);
    
    //周围的4个人.
    UIImageView* people2 = dynamic_cast<UIImageView*>(ul->getWidgetByName("People2"));
    CCSequence* people2Act = CCSequence::create( CCShow::create(), CCMoveBy::create(0.0, ccp(-30, 0)), CCMoveBy::create(0.2, ccp(30, 0)),NULL);
    people2->runAction(people2Act);
    UIImageView* people3 = dynamic_cast<UIImageView*>(ul->getWidgetByName("People3"));
    CCSequence* people3Act = CCSequence::create( CCShow::create(), CCMoveBy::create(0.0, ccp(30, 0)), CCMoveBy::create(0.2, ccp(-30, 0)),NULL);
    people3->runAction(people3Act);
    UIImageView* people4 = dynamic_cast<UIImageView*>(ul->getWidgetByName("People4"));
    CCSequence* people4Act = CCSequence::create( CCShow::create(), CCMoveBy::create(0.0, ccp(30, 0)), CCMoveBy::create(0.2, ccp(-30, 0)),NULL);
    people4->runAction(people4Act);
    UIImageView* people5 = dynamic_cast<UIImageView*>(ul->getWidgetByName("People5"));
    CCSequence* people5Act = CCSequence::create( CCShow::create(), CCMoveBy::create(0.0, ccp(-30, 0)), CCMoveBy::create(0.2, ccp(30, 0)), CCCallFuncO::create(people1, callfuncO_selector(UIImageView::runAction), people1Act2), NULL);
    people5->runAction(people5Act);
    
    UIImageView *shadow = dynamic_cast<UIImageView*>(ul -> getWidgetByName("shadow"));
    shadow -> setVisible(true);
    return true;
}