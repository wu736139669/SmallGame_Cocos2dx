//
// GameWeekRewardLayer.cpp
// OnceAgain
//
// Created by xiaohai on 14-5-22.
//
//

#include "GameWeekRewardLayer.h"
#include "GameUIExportJson.h"
#include "GameTakeRewardLayer.h"
#include "PlayerInfoManager.h"
#include "NetHttpClient.h"
#include "MsgDefine.h"
#include "XQDate.h"

GameWeekRewardLayer::GameWeekRewardLayer()
{
    
}

GameWeekRewardLayer::~GameWeekRewardLayer()
{
    
}

CCScene* GameWeekRewardLayer::createScene()
{
    auto scene = CCScene::create();
    auto layer = GameWeekRewardLayer::create();
    scene->addChild(layer);
    return scene;
}

bool GameWeekRewardLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }

    CSJson::Value msg_body;
    msg_body["playerid"] = CSJson::Value(CPlayerInfoMan::sharedInstance().getPlayerInfo().nId);
    NetHttpClient::sharedInstance().XQsendHttpRequest(eNetMsgTypeMissionSys, eNetMsgMissionSysWeekRewardKind, &msg_body,this , coco_myevent(GameWeekRewardLayer::BindingUIItems));
    //载入ui
    initData();
    //绑定ui
    return true;
}

#pragma mark - initData
void GameWeekRewardLayer::initData()
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCLayerColor *backGround = CCLayerColor::create(ccc4(0, 0, 0, 150));
    backGround->setContentSize(visibleSize);
    backGround->setZOrder(0);
    this -> addChild(backGround);
    // add your codes here...
    
}

void GameWeekRewardLayer::BindingUIItems(CCObject *p)
{
    CCString str;
    str.initWithFormat("%d%d",eNetMsgTypeMissionSys, eNetMsgMissionSysWeekRewardKind);
    CSJson::Value root = XQDate::sharedInstance().GetDate(str.getCString());
    
    bool isShowBtn = false;
    
    for (int i = 0; i < root.size(); i ++) {
        CSJson::Value & val = root[i];
        if (val["iscomplete"].asInt() == 1) {
            isShowBtn = true;
        }
    }
    
    ul = UILayer::create();
    addChild(ul, 1);
    auto myLayout = static_cast<Layout*>(GUIReader::shareReader() -> widgetFromJsonFile("./CocoStudioResources/WeekRewardLayer.json"));
    ul -> addWidget(myLayout);
    
    UIPanel *myPanel = dynamic_cast<UIPanel*>(ul -> getWidgetByName("Panel_2"));
    myPanel -> addReleaseEvent(this, coco_releaseselector(GameWeekRewardLayer::touchWindow));
    // bind ui images
    
    UIButton *btn = dynamic_cast<UIButton*>(ul -> getWidgetByName("LotteryBtn"));
    if (isShowBtn) {
        btn->disable();
        btn->setVisible(false);
    }
    else {
        btn -> addReleaseEvent(this, coco_releaseselector(GameWeekRewardLayer::getWeekRewardBtnClick));
    }

	//设置字体不被选中;
}

void GameWeekRewardLayer::getWeekRewardBtnClick(cocos2d::CCObject *p) {
    auto layer = GameTakeRewardLayer::create();
    layer -> setCallBack(this, callfuncO_selector(GameWeekRewardLayer::touchWindow));
    this -> addChild(layer, 10);
}

void GameWeekRewardLayer::touchWindow(cocos2d::CCObject *p) {
    this -> removeFromParent();
}

