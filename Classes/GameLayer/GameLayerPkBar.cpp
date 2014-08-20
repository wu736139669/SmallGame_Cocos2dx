//
//  GameLayerPkBar.cpp
//  OnceAgain
//
//  Created by mac on 14-4-30.
//
//

#include "GameLayerPkBar.h"
#include "StringUtil.h"
#include "ImageDownloader.h"
GameLayerPkBar::GameLayerPkBar()
{
}
GameLayerPkBar::~GameLayerPkBar()
{
    GUIReader::shareReader()->purgeGUIReader();
	DictionaryHelper::shareHelper()->purgeDictionaryHelper();
	ActionManager::shareManager()->purgeActionManager();
}

bool GameLayerPkBar::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    ul = UILayer::create();
    auto myLayout = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile(CStringUtil::convertToUIResPath("PkBar.json").c_str()));
    ul->addWidget(myLayout);
    this->addChild(ul, 0, 100);
    
    UIButton* btn = dynamic_cast<UIButton*>(ul->getWidgetByName("Sure"));
    btn->setPressedActionEnabled(true);
    btn->setTouchEnable(true);
    btn->addReleaseEvent(this, coco_releaseselector(GameLayerPkBar::sureBtnCallback));
    
    
    return true;
}
void GameLayerPkBar::sureBtnCallback(cocos2d::CCObject *pSender)
{
    if (m_pListener && m_pfnSelector)
    {
        (m_pListener->*m_pfnSelector)(this);
    }
    
//    this->removeFromParent();

}
void GameLayerPkBar::addSureCallbackFunc(cocos2d::CCObject *target, SEL_ReleaseEvent callfun)
{
    this->m_pListener = target;
    this->m_pfnSelector = callfun;
}
void GameLayerPkBar::setAvatar(std::string avatarUrl)
{
    UIImageView* cellBg = dynamic_cast<UIImageView*>(ul->getWidgetByName("AvatarBg"));
    
    CCSprite* img =  CCSprite::create();
    img->setContentSize(CCSize(106, 106));
    img->setAnchorPoint(ccp(0, 0));
    cellBg->addRenderer(img, 10);
//    img->setPosition(ccp(0, 0));
//    ul->addChild(img,100);
    CImageDownloader::GetInstance()->SendHttpRequest(avatarUrl.c_str(), img, "1000", 1000);
}
void GameLayerPkBar::setName(std::string name)
{
    UILabel* label = dynamic_cast<UILabel*>(ul->getWidgetByName("NameLabel"));
    label->setText(name.c_str());
}
void GameLayerPkBar::setType(int type)
{
    UIImageView* btn = dynamic_cast<UIImageView*>(ul->getWidgetByName("TypeImg"));
    
    if (type == 0) {
        btn->setTexture("./CocoStudioResources/PkOver/LabelCanelCha.png");
    }
    if (type == 1) {
        btn->setTexture("./CocoStudioResources/PkOver/LabelCanelBat.png");
    }
}