//
//  GameLayer_Menu.cpp
//  OnceAgain
//
//  Created by mac on 14-3-25.
//
//

#include "GameLayer_Menu.h"
#include "GameLayer_Tag.h"
#include "NetPacket.h"
#include "PlayerInfoManager.h"
#include "MsgDefine.h"
IMPLEMENT_DLG_ID(GameLayer_Menu,GameMenu);
GameLayer_Menu::~GameLayer_Menu()
{
    GUIReader::shareReader()->purgeGUIReader();
    DictionaryHelper::shareHelper()->purgeDictionaryHelper();
    ActionManager::shareManager()->purgeActionManager();
}


bool GameLayer_Menu::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    //系统设置界面.
    gameMenu = UILayer::create();
    auto layout = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("./CocoStudioResources/GameMenu.json"));
    gameMenu->addWidget(layout);
    //    sysSet->setVisible(true);
    this->addChild(gameMenu, 0, 101);
    
    //    UIPanel* panel = dynamic_cast<UIPanel*>(gameResource->getWidgetByName("DayLogin"));
    //    panel->setBackGroundColor(ccBLACK);
    //    panel->setBackGroundColorOpacity(150);
    //关闭按钮
    //    UIButton* sureBtn = dynamic_cast<UIButton*>(gameResource->getWidgetByName("SureBtn"));
    //    sureBtn->addReleaseEvent(this, coco_releaseselector(GameLayer_Resource::sureBtnCallback));
    //    sureBtn->setPressedActionEnabled(true);
    
    return true;
}

void GameLayer_Menu::setNoLogin(bool visiable)
{
    UIPanel* dayLoginPanel = dynamic_cast<UIPanel*>(gameMenu->getWidgetByName("MenuBtn"));
    dayLoginPanel->setVisible(visiable);
    UIButton* taskBtn = dynamic_cast<UIButton*>(gameMenu->getWidgetByName("SysInfoBtn"));
    taskBtn->setTouchEnable(visiable);
    UIButton* emailBtn = dynamic_cast<UIButton*>(gameMenu->getWidgetByName("EmailBtn"));
    emailBtn->setTouchEnable(visiable);
    UIButton* addFriendBtn = dynamic_cast<UIButton*>(gameMenu->getWidgetByName("AddFriendBtn"));
    addFriendBtn->setTouchEnable(visiable);
    UIButton* rankBtn = dynamic_cast<UIButton*>(gameMenu->getWidgetByName("RankBtn"));
    rankBtn->setVisible(visiable);
    rankBtn->setTouchEnable(visiable);
}
void GameLayer_Menu::setVisible(bool visible)
{
    CCLayer::setVisible(visible);
    UIPanel* dayLoginPanel = dynamic_cast<UIPanel*>(gameMenu->getWidgetByName("Panel"));
    dayLoginPanel->setTouchEnable(visible);
}

void GameLayer_Menu::sureBtnCallback(cocos2d::CCObject *pSender)
{
    this->removeFromParent();
}
void GameLayer_Menu::addSetBtnCallback(cocos2d::CCObject *target, SEL_CallFuncO callfun)
{
    UIButton* setBtn = dynamic_cast<UIButton*>(gameMenu->getWidgetByName("SetBtn"));
    setBtn->addReleaseEvent(target, callfun);
    setBtn->setPressedActionEnabled(true);
}
void GameLayer_Menu::addTaskBtnCallback(cocos2d::CCObject *target, SEL_CallFuncO callfun)
{
    
    UIButton* taskBtn = dynamic_cast<UIButton*>(gameMenu->getWidgetByName("SysInfoBtn"));
    taskBtn->addReleaseEvent(target, callfun);
    taskBtn->setPressedActionEnabled(true);

}
void GameLayer_Menu::addSysInfoCallback(cocos2d::CCObject *target, SEL_CallFuncO callfun)
{
    UIButton* taskBtn = dynamic_cast<UIButton*>(gameMenu->getWidgetByName("EmailBtn"));
    taskBtn->addReleaseEvent(target, callfun);
    taskBtn->setPressedActionEnabled(true);
}
void GameLayer_Menu::addFriendCallBack(cocos2d::CCObject *target, SEL_CallFuncO callfun)
{
    UIButton* taskBtn = dynamic_cast<UIButton*>(gameMenu->getWidgetByName("AddFriendBtn"));
    taskBtn->addReleaseEvent(target, callfun);
    taskBtn->setPressedActionEnabled(true);
}
void GameLayer_Menu::addRankCallBack(cocos2d::CCObject *target, SEL_CallFuncO callfun)
{
    UIButton* rankBtn = dynamic_cast<UIButton*>(gameMenu->getWidgetByName("RankBtn"));
    rankBtn->addReleaseEvent(target, callfun);
    rankBtn->setPressedActionEnabled(true);
}
void GameLayer_Menu::setInfoNum()
{
    UIImageView* img = dynamic_cast<UIImageView*>(gameMenu->getWidgetByName("Email_RemindImg"));
    if (CPlayerInfoMan::sharedInstance().getPlayerInfo().sysInfoNum <= 0) {
        img->setVisible(false);
    }else{
        img->setVisible(true);
        UILabel* label = dynamic_cast<UILabel*>(gameMenu->getWidgetByName("InfoLabel"));
        CCString str;
        str.initWithFormat("%d",CPlayerInfoMan::sharedInstance().getPlayerInfo().sysInfoNum);
        label->setText(str.getCString());
    }
}
bool GameLayer_Menu::onPackageFilter(void *pDataPkg)
{
    CResponsePacket* pPkt = (CResponsePacket*)pDataPkg;
	unsigned int unMsgType = pPkt->getMsgType();
	unsigned int unMsgCode = pPkt->getMsgCode();
	//网络数据传输完成
	if (pPkt->getDataState() == eNetMsgDataStateComplete)
	{

        if (unMsgType == eNetMsgTypeMsgSys) {
            if (unMsgCode == eNetMsgGetInfoNum) {
                this->setInfoNum();
            }
        }
		
	}
	return true;
}
