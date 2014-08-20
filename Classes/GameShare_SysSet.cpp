//
//  GameShare_SysSet.cpp
//  OnceAgain
//
//  Created by mac on 14-3-13.
//
//

#include "GameShare_SysSet.h"
#include "Constant.h"
#include "StringUtil.h"
#include "GameShare_Data.h"
#include "GameShare_Global.h"
#include "PlayerInfoManager.h"
GameShare_SysSet::~GameShare_SysSet()
{
    GUIReader::shareReader()->purgeGUIReader();
    DictionaryHelper::shareHelper()->purgeDictionaryHelper();
    ActionManager::shareManager()->purgeActionManager();
}

bool GameShare_SysSet::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    //系统设置界面.
    sysSet = UILayer::create();
    auto sysLayout = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile(CStringUtil::convertToUIResPath("SysSet.json").c_str()));
    sysSet->addWidget(sysLayout);
//    sysSet->setVisible(true);
    this->addChild(sysSet, 0, 101);
    
    UIPanel* panel = dynamic_cast<UIPanel*>(sysSet->getWidgetByName("Panel"));
    panel->setBackGroundColor(ccBLACK);
    panel->setTouchEnable(true);
    panel->setBackGroundColorOpacity(150);
    //关闭按钮
    UIButton* sysCloseBtn = dynamic_cast<UIButton*>(sysSet->getWidgetByName("CloseBtn"));
    sysCloseBtn->addReleaseEvent(this, coco_releaseselector(GameShare_SysSet::closeSysSetCallback));
    sysCloseBtn->setPressedActionEnabled(true);
    //退出按钮.
    UIButton* logOutBtn = dynamic_cast<UIButton*>(sysSet->getWidgetByName("Logout"));
    logOutBtn->addReleaseEvent(this, coco_releaseselector(GameShare_SysSet::logOutCallback));
    if (GameShare_Global::shareGlobal()->loginType == LoginType_QQ) {
        logOutBtn->setTextures("./CocoStudioResources/SystemSet/QQBtn.png", "./CocoStudioResources/SystemSet/QQBtn.png", "");
    }
    if (GameShare_Global::shareGlobal()->loginType == LoginType_Sina) {
        logOutBtn->setTextures("./CocoStudioResources/SystemSet/SinaBtn.png", "./CocoStudioResources/SystemSet/SinaBtn.png", "");
    }
    logOutBtn->setPressedActionEnabled(true);
    

    //声音
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("FriendList0.plist", "FriendList0.png");
    
    UIButton* musicSwitch = dynamic_cast<UIButton*>(sysSet->getWidgetByName("MusicSwitch"));
    musicSwitch->addReleaseEvent(this, coco_releaseselector(GameShare_SysSet::musicSwitchCallBack));
//    musicSwitch->setPressedActionEnabled(true);
    if (!CCUserDefault::sharedUserDefault()->getBoolForKey(KEY_ISMUSIC)) {
        musicSwitch->setNormalTexture("./CocoStudioResources/SystemSet/images/btn_open.png");
        
    }else{
        musicSwitch->setNormalTexture("./CocoStudioResources/SystemSet/images/btn_close.png");
    }
    
    UIButton* musicEffectSwitch = dynamic_cast<UIButton*>(sysSet->getWidgetByName("MusicEffectSwitch"));
    musicEffectSwitch->addReleaseEvent(this, coco_releaseselector(GameShare_SysSet::musicEffectSwitchCallBack));
//    musicEffectSwitch->setPressedActionEnabled(true);
    if (!CCUserDefault::sharedUserDefault()->getBoolForKey(KEY_ISMUSICEFFECT)) {
        musicEffectSwitch->setNormalTexture("./CocoStudioResources/SystemSet/images/btn_open.png");
        
    }else{
        musicEffectSwitch->setNormalTexture("./CocoStudioResources/SystemSet/images/btn_close.png");
    }
    
//    sysSet->setTouchEnabled(false);
//    this->setVisible(false);
    return true;
} 

void GameShare_SysSet::logOutCallback(cocos2d::CCObject *pSender)
{
    GameShare_Data::shareData()->setSinaId("", "", 0);
    GameShare_Data::shareData()->setQQID("", "", 0);
    GameShare_Data::shareData()->setUserUUID("");
    GameShare_Global::shareGlobal()->reSet();
    CPlayerInfoMan::sharedInstance().reset();
    CCDirector::sharedDirector()->popScene();
}
void GameShare_SysSet::closeSysSetCallback(cocos2d::CCObject *pSender)
{
    this->removeFromParent();
}

void GameShare_SysSet::setVisible(bool visible)
{
    CCLayer::setVisible(visible);
    UIImageView* sys = dynamic_cast<UIImageView*>(sysSet->getWidgetByName("Image_11"));
    sys->setTouchEnable(visible);
}

void GameShare_SysSet::musicSwitchCallBack(cocos2d::CCObject *pSender)
{
    CCUserDefault::sharedUserDefault()->setBoolForKey(KEY_ISMUSIC, !CCUserDefault::sharedUserDefault()->getBoolForKey(KEY_ISMUSIC));
    CCUserDefault::sharedUserDefault()->flush();
    UIButton* musicSwitch = dynamic_cast<UIButton*>(sysSet->getWidgetByName("MusicSwitch"));

    if (!CCUserDefault::sharedUserDefault()->getBoolForKey(KEY_ISMUSIC)) {
        musicSwitch->setNormalTexture("./CocoStudioResources/SystemSet/images/btn_open.png");
        CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1);
        
        
    }else{
        musicSwitch->setNormalTexture("./CocoStudioResources/SystemSet/images/btn_close.png");
        CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0);
    }
    
}
void GameShare_SysSet::musicEffectSwitchCallBack(cocos2d::CCObject *pSender)
{
    CCUserDefault::sharedUserDefault()->setBoolForKey(KEY_ISMUSICEFFECT, !CCUserDefault::sharedUserDefault()->getBoolForKey(KEY_ISMUSICEFFECT));
    CCUserDefault::sharedUserDefault()->flush();
    UIButton* musicEffectSwitch = dynamic_cast<UIButton*>(sysSet->getWidgetByName("MusicEffectSwitch"));

    if (!CCUserDefault::sharedUserDefault()->getBoolForKey(KEY_ISMUSICEFFECT)) {
        musicEffectSwitch->setNormalTexture("./CocoStudioResources/SystemSet/images/btn_open.png");
        CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(1);
    }else{
        musicEffectSwitch->setNormalTexture("./CocoStudioResources/SystemSet/images/btn_close.png");
        CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(0);
    }
}