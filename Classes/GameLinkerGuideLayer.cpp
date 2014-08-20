//
// GameLinkerGuideLayer.cpp
// OnceAgain
//
// Created by xiaohai on 14-5-6.
//
//

#include "GameLinkerGuideLayer.h"
#include "GameUIExportJson.h"

CCScene* GameLinkerGuideLayer::createScene()
{
    auto scene = CCScene::create();
    auto layer = GameLinkerGuideLayer::create();
    scene->addChild(layer);
    return scene;
}

bool GameLinkerGuideLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    //载入ui
    initData();
    //绑定ui
    BindingUIItems();
    //播放动画
    loopAnimaton();
    return true;
}

#pragma mark - initData
void GameLinkerGuideLayer::initData()
{
    // add your codes here...
    ul = UILayer::create();
    addChild(ul);
    auto *myLayout = dynamic_cast<Layout*>(GUIReader::shareReader() -> widgetFromJsonFile(uiGameLinkerGuideLayer));
    ul -> addWidget(myLayout);
    UIPanel *p = static_cast<UIPanel*>(ul -> getWidgetByName("Panel_3"));
    p -> setTouchEnabled(false);
   
    this -> schedule(schedule_selector(GameLinkerGuideLayer::checkFingerPoint));
}

void GameLinkerGuideLayer::BindingUIItems()
{
    line_1 = static_cast<UIImageView*>(ul -> getWidgetByName("line_1"));
    line_2 = static_cast<UIImageView*>(ul -> getWidgetByName("line_2"));
    finger = static_cast<UIImageView*>(ul -> getWidgetByName("finger"));
    endImg = static_cast<UIImageView*>(ul -> getWidgetByName("Image_3_0"));
    fingerPoint = finger -> getPosition();
    line_1 -> setAnchorPoint(ccp(0, 0.5));
    line_1 -> setPosition(fingerPoint);
    line_2 -> removeFromParent();
    // bind ui images
}

void GameLinkerGuideLayer::loopAnimaton() {
    CCCallFunc *ani_1 = CCCallFunc::create(this, callfunc_selector(GameLinkerGuideLayer::lineHind));
    CCMoveBy *down = CCMoveBy::create(0.3, ccp(-50, -40));
    line_1 -> setScaleX(0);
    CCMoveTo *fingerMove = CCMoveTo::create(1, endImg -> getPosition());
    finger -> runAction(CCRepeatForever::create(CCSequence::create(ani_1, down,CCDelayTime::create(0.5),fingerMove, CCDelayTime::create(0.8),NULL)));
}

void GameLinkerGuideLayer::lineHind() {
    line_1 -> setVisible(false);
    finger -> setPosition(ccp(fingerPoint.x+50, fingerPoint.y+40));
}

void GameLinkerGuideLayer::checkFingerPoint(float a) {
    float fingerY = (finger ->getPosition()).y;
    line_1 -> setVisible(true);
    line_1 -> setScaleX((fingerPoint.y - fingerY)/ line_1->getContentSize().width);    
}