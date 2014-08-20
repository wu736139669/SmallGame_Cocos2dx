//
//  GameLayer_Alert.cpp
//  OnceAgain
//
//  Created by mac on 14-3-24.
//
//

#include "GameLayer_Alert.h"

GameLayer_Alert::~GameLayer_Alert()
{
    GUIReader::shareReader()->purgeGUIReader();
    DictionaryHelper::shareHelper()->purgeDictionaryHelper();
    ActionManager::shareManager()->purgeActionManager();
}
GameLayer_Alert::GameLayer_Alert()
{
    alertUl = NULL;
    m_pListener = NULL;
    m_pfnSelector = NULL;
}
GameLayer_Alert* GameLayer_Alert::creatWithOnlySure(int type)
{
    GameLayer_Alert *pobSprite = new GameLayer_Alert();
    
    if (pobSprite)//
    {
        pobSprite->init(type);
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

bool GameLayer_Alert::init(int type)
{
    if (!CCLayer::init()) {
        return false;
    }
    //系统设置界面.
    alertUl = UILayer::create();
    Layout* layout;
//    auto layout = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("Alert1.ExportJson"));
   
   
   if(type == Type_OnlySure){
       layout = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("./CocoStudioResources/Alert2.json"));
   }
   else {
     layout = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("./CocoStudioResources/Alert1.json"));
   }
        alertUl->addWidget(layout);
    //    sysSet->setVisible(true);
    this->addChild(alertUl, 0, 101);
    //设置背景颜色.
    UIPanel* alertPanel = dynamic_cast<UIPanel*>(alertUl->getWidgetByName("Alert"));
    alertPanel->setBackGroundColor(ccBLACK);
    alertPanel->setBackGroundColorOpacity(150);
    //确定按钮
    UIButton* sureBtn = dynamic_cast<UIButton*>(alertUl->getWidgetByName("SureBtn"));
    sureBtn->addReleaseEvent(this, coco_releaseselector(GameLayer_Alert::sureBtnCallback));
    sureBtn->setPressedActionEnabled(true);
    
    //关闭按钮.
    UIButton* closeBtn = dynamic_cast<UIButton*>(alertUl->getWidgetByName("CloseBtn"));
    closeBtn->addReleaseEvent(this, coco_releaseselector(GameLayer_Alert::closeBtnCallback));
    closeBtn->setPressedActionEnabled(false);
    closeBtn->setTouchEnable(false);
    closeBtn->setVisible(false);
    if (type != Type_OnlySure) {
        UIButton* cancelBtn = dynamic_cast<UIButton*>(alertUl->getWidgetByName("CancelBtn"));
        cancelBtn->addReleaseEvent(this, coco_releaseselector(GameLayer_Alert::cancelBtnCallback));
        cancelBtn->setPressedActionEnabled(true);
    }
    

    this->m_pListener = NULL;
    this->m_pfnSelector = NULL;
    this->setVisible(true);
    return true;
}
void GameLayer_Alert::setText(const char *str)
{
    UILabel* label = dynamic_cast<UILabel*>(alertUl->getWidgetByName("Label_699"));
    label->setText(str);
}
void GameLayer_Alert::setSize(int size)
{
    UILabel* label = dynamic_cast<UILabel*>(alertUl->getWidgetByName("Label_699"));
    label->setFontSize(size);
}
void GameLayer_Alert::setVisible(bool visible)
{
    CCLayer::setVisible(visible);
    UIPanel* dayLoginPanel = dynamic_cast<UIPanel*>(alertUl->getWidgetByName("Alert"));
    dayLoginPanel->setTouchEnable(visible);
}

void GameLayer_Alert::sureBtnCallback(cocos2d::CCObject *pSender)
{
    
    if (m_pfnSelector && m_pListener) {
        UIButton* sureBtn = dynamic_cast<UIButton*>(alertUl->getWidgetByName("SureBtn"));
        (m_pListener->*m_pfnSelector)(sureBtn);
    }
    this->removeFromParent();
}
void GameLayer_Alert::closeBtnCallback(cocos2d::CCObject *pSender)
{
    this->removeFromParent();
}

void GameLayer_Alert::cancelBtnCallback(cocos2d::CCObject *pSender)
{
    this->removeFromParent();
}

void GameLayer_Alert::setSureCallbackFunc(cocos2d::CCObject *target, SEL_CallFuncO callfun)
{
    this->m_pListener = target;
    this->m_pfnSelector = callfun;
}
void GameLayer_Alert::setSureBtnTag(int tag)
{
    UIButton* sureBtn = dynamic_cast<UIButton*>(alertUl->getWidgetByName("SureBtn"));
    sureBtn->setTag(tag);
}