//
//  GameLayer_Task.cpp
//  OnceAgain
//
//  Created by mac on 14-3-25.
//
//

#include "GameLayer_Task.h"
#include "StringUtil.h"
#include "GameLayer_Tag.h"
GameLayer_Task::~GameLayer_Task()
{
    GUIReader::shareReader()->purgeGUIReader();
    DictionaryHelper::shareHelper()->purgeDictionaryHelper();
    ActionManager::shareManager()->purgeActionManager();
}

GameLayer_Task::GameLayer_Task()
{
    taskUl = NULL;
    m_pListener = NULL;
    m_pfnSelector = NULL;
}
bool GameLayer_Task::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    //系统设置界面.
    taskUl = UILayer::create();
    auto layout = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile(CStringUtil::convertToUIResPath("GameOverTask.json").c_str()));
    taskUl->addWidget(layout);
    //    sysSet->setVisible(true);
    this->addChild(taskUl, 0, 101);
    
    //设置背景颜色.
    UIPanel* taskPanel = dynamic_cast<UIPanel*>(taskUl->getWidgetByName("Task"));
    taskPanel->setBackGroundColor(ccBLACK);
    taskPanel->setBackGroundColorOpacity(150);
    //关闭按钮
    UIButton* sureBtn = dynamic_cast<UIButton*>(taskUl->getWidgetByName("SureBtn"));
    sureBtn->addReleaseEvent(this, coco_releaseselector(GameLayer_Task::sureBtnCallback));
    sureBtn->setPressedActionEnabled(true);
    
    //
    UIImageView* taskImg1 = dynamic_cast<UIImageView*>(taskUl->getWidgetByName("TaskComplete1"));
    taskImg1->setVisible(true);
    UIImageView* taskImg2 = dynamic_cast<UIImageView*>(taskUl->getWidgetByName("TaskComplete2"));
    taskImg2->setVisible(true);
    this->setVisible(true);
    
    
    return true;
}

void GameLayer_Task::setVisible(bool visible)
{
    CCLayer::setVisible(visible);
    UIPanel* taskPanel = dynamic_cast<UIPanel*>(taskUl->getWidgetByName("Task"));
    taskPanel->setTouchEnable(visible);
}

void GameLayer_Task::sureBtnCallback(cocos2d::CCObject *pSender)
{
    this->removeFromParent();
}

void GameLayer_Task::setSureCallbackFunc(cocos2d::CCObject *target, SEL_CallFuncO callfun)
{
    this->m_pListener = target;
    this->m_pfnSelector = callfun;
}