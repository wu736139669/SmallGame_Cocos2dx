//
//  GameLayerFriendTaskCell.cpp
//  OnceAgain
//
//  Created by mac on 14-4-18.
//
//

#include "GameLayerFriendTaskCell.h"
#include "StringUtil.h"
#include "XQDate.h"
#include "GameShare_Msg.h"
#include "MsgDefine.h"
#include "PlayerInfoManager.h"
GameLayerFriendTaskCell::GameLayerFriendTaskCell()
{
    
}
GameLayerFriendTaskCell::~GameLayerFriendTaskCell()
{
    GUIReader::shareReader()->purgeGUIReader();
	DictionaryHelper::shareHelper()->purgeDictionaryHelper();
	ActionManager::shareManager()->purgeActionManager();
}

bool GameLayerFriendTaskCell::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    myTaskId = 0;
    cellLyaer = UILayer::create();
    auto myLayout = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("./CocoStudioResources/FriendTaskCell.json"));
    cellLyaer->addWidget(myLayout);
    this->addChild(cellLyaer, 0, 100);
    
    UIButton *btn = dynamic_cast<UIButton*>(cellLyaer -> getWidgetByName("GainBtn"));
    btn -> setVisible(false);

    
    UIPanel* cell = dynamic_cast<UIPanel*>(cellLyaer->getWidgetByName("Cell"));
    this->setContentSize(cell->getContentSize());
    return true;
}

void GameLayerFriendTaskCell::setCellInfo(sWeekTask data) {
    info = data;
    UILabel* taskLabel = dynamic_cast<UILabel*>(cellLyaer->getWidgetByName("TaskInfo"));
    taskLabel->setText(info.taskName.c_str());
    
    if (info.completeValue == 1) {
        UIButton *btn = dynamic_cast<UIButton*>(cellLyaer -> getWidgetByName("GainBtn"));
        btn -> addReleaseEvent(this, coco_releaseselector(GameLayerFriendTaskCell::requestReward));
        btn -> setVisible(true);
    }
    else {
        int allcount = info.taskValue;
        int nowCount = info.taskAppendvalue;
        if (allcount > 1000) {

        }
        else {
            CCString str;
            str.initWithFormat("%d/%d", nowCount, allcount);
            UILabel *textLabel = dynamic_cast<UILabel*>(cellLyaer -> getWidgetByName("TaskCompleteLabel"));
            textLabel -> setVisible(true);
            textLabel -> setText(str.getCString());
        }
    }
}

void GameLayerFriendTaskCell::setCallBack(cocos2d::CCObject *p, SEL_CallFunc call)
{
    target = p;
    callBack = call;
}
void GameLayerFriendTaskCell::btnClickcallBack(cocos2d::CCObject *p) {
    CCString str;
    str.initWithFormat("%d%d", eNetMsgTypeMissionSys, eNetMsgMissionSysWeeked);
    CSJson::Value root = XQDate::sharedInstance().GetDate(str.getCString());
    for (int i = 0; i < root.size(); i ++) {
        CSJson::Value &val = root[i];
        CPlayerInfoMan::sharedInstance().getPlayerInfo().nMoney = val["playermoney"].asInt();
        CPlayerInfoMan::sharedInstance().getPlayerInfo().nPower = val["playergem"].asInt();
    }
    //发出消息.
    CCNotificationCenter::sharedNotificationCenter()->postNotification(kRefreshMoney, NULL);
    if (target && callBack) {
        (target->*callBack)();
    }
}
void GameLayerFriendTaskCell::requestReward(cocos2d::CCObject *p) {
    //领取奖励
    CSJson::Value msg_body;
    msg_body["playerid"] = CSJson::Value(CPlayerInfoMan::sharedInstance().getPlayerInfo().nId);
    msg_body["weektaskid"] = CSJson::Value(info.taskId);
    NetHttpClient::sharedInstance().XQsendHttpRequest(eNetMsgTypeMissionSys, eNetMsgMissionSysWeeked, &msg_body, this, coco_myevent(GameLayerFriendTaskCell::btnClickcallBack));
}

