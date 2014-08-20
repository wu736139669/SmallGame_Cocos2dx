//
//  GameLayerFriendTaskList.cpp
//  OnceAgain
//
//  Created by mac on 14-4-18.
//
//

#include "GameLayerFriendTaskList.h"
#include "GameLayerFriendTaskCell.h"
#include "GameShare_Msg.h"
#include "XQDate.h"
#include "GameLayer_Alert.h"
#include "PlayerInfoManager.h"
#include "CsvStringData.h"


GameLayerFriendTaskList::GameLayerFriendTaskList()
{
    
}
GameLayerFriendTaskList::~GameLayerFriendTaskList()
{
    GUIReader::shareReader()->purgeGUIReader();
	DictionaryHelper::shareHelper()->purgeDictionaryHelper();
	ActionManager::shareManager()->purgeActionManager();
}

bool GameLayerFriendTaskList::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    //获取窗口大小
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    UILayer* ul = UILayer::create();
    auto myLayout = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("./CocoStudioResources/FriendTask.json"));
    ul->addWidget(myLayout);
    ul->setContentSize(visibleSize);
    this->addChild(ul, 1, 100);
    
    UIPanel* panel = dynamic_cast<UIPanel*>(ul->getWidgetByName("Panel"));
    panel->setBackGroundColor(ccBLACK);
    panel->setBackGroundColorOpacity(150);
    panel->setTouchEnable(true);
    
    //关闭按钮
    UIButton* sysCloseBtn = dynamic_cast<UIButton*>(ul->getWidgetByName("Close"));
    sysCloseBtn->addReleaseEvent(this, coco_releaseselector(GameLayerFriendTaskList::closeSysSetCallback));
    sysCloseBtn->setPressedActionEnabled(true);
    sysCloseBtn->setTouchEnable(true);
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(GameLayerFriendTaskList::reloadMyTableView), kGetWeekTask, NULL);
    //获取周任务表.
    VEC_SWEEKTASK& data = CTaskMan::sharedInstance().getWeekTaskData();
    
    datalist.clear();
    for (int i = 0; i < data.size(); i ++) {
        if (data[i].haveGetReward == 0) {
            datalist.push_back(data[i]);
        }
    }
    
    UIPanel *mypanel = dynamic_cast<UIPanel*>(ul -> getWidgetByName("tableview"));
    mytableview = CCTableView::create(this, mypanel->getContentSize());
    mytableview -> setDelegate(this);
    mytableview->setDirection(kCCScrollViewDirectionVertical);
    mytableview->setVerticalFillOrder(kCCTableViewFillTopDown);
    mypanel -> addCCNode(mytableview);

    return true;
}

void GameLayerFriendTaskList::getRewardCallBack() {
    //获取的奖励的弹窗
    int type = 0;
    int value = 0;
    CSJson::Value root = XQDate::sharedInstance().GetDate("68");
    for (int i = 0; i < root.size(); i++) {
        CSJson::Value &val = root[i];
        type = val["weektaskrewardtype"].asInt();
        value = val["weektaskrewardvalue"].asInt();
        CPlayerInfoMan::sharedInstance().getPlayerInfo().nMoney = val["playermoney"].asInt();
        CPlayerInfoMan::sharedInstance().getPlayerInfo().nGem = val["playergem"].asInt();
    }
    CCString str;
    if (type == 4) {
        str.initWithFormat(GET_STRING_CSV(1010000032), value);
    }
    if (type == 5) {
        str.initWithFormat(GET_STRING_CSV(1010000033), value);
    }
    
    auto *top = GameLayer_Alert::creatWithOnlySure(Type_OnlySure);
    top -> setSureCallbackFunc(this, callfuncO_selector(GameLayerFriendTaskList::topBtnCallBack));
    top -> setText(str.getCString());
    this -> addChild(top, 10);
}

void GameLayerFriendTaskList::closeSysSetCallback(cocos2d::CCObject *pSender)
{
    this->removeFromParent();
}

void GameLayerFriendTaskList::topBtnCallBack(cocos2d::CCObject *p) {
    //窗口点击回调
    CTaskMan::sharedInstance().requestWeekTaskTemp();
}

CCSize GameLayerFriendTaskList::tableCellSizeForIndex(CCTableView *table, unsigned int idx) {
    return CCSize(520, 100);
}
//确定这个tableview的cell行数
unsigned int GameLayerFriendTaskList::numberOfCellsInTableView(CCTableView *table){
    return datalist.size();
}
//定制每个cell的内容
CCTableViewCell* GameLayerFriendTaskList::tableCellAtIndex(CCTableView *table, unsigned int idx) {
    CCTableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = new CCTableViewCell();
        cell->autorelease();
    }
    cell -> removeAllChildren();
    GameLayerFriendTaskCell* layer = GameLayerFriendTaskCell::create();
    layer -> setCellInfo(datalist[idx]);
    layer -> setCallBack(this, callfunc_selector(GameLayerFriendTaskList::getRewardCallBack));
    cell ->addChild(layer);
    return cell;
}

void GameLayerFriendTaskList::reloadMyTableView(cocos2d::CCObject *p) {
    this -> removeFromParent();
}

void GameLayerFriendTaskList::onExit() {
    CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
    CCLayer::onExit();
}
