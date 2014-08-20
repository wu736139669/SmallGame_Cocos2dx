//
//  Scene_Welcome.cpp
//  OnceAgain
//
//  Created by xiaohai on 14-2-21.
//
//

#include "Scene_Welcome.h"
#include "Scene_GameOver.h"
#include "NetHttpClient.h"
#include "MsgDefine.h"
#include "PlayerInfoManager.h"
#include "SpriteFrameManage.h"
#include "StrengthenManager.h"
#include "GameItemManager.h"
#include "MoneyManager.h"
#include "GameLayer_Logo.h"
#include "GameUIExportJson.h"
#include "GameInfoManager.h"
#include "DialogManager.h"
#include "GameLayerLoading.h"
#include "StringUtil.h"
#include "GameShare_NetSystem.h"
#include "TaskManager.h"
#include "aes.h"
using namespace cocos2d::extension;


CCScene* Scene_Welcome::scene()
{
    // 'scene' auto release memory
    CCScene *scene = CCScene::create();
    // 'layer' auto release memory
    Scene_Welcome *layer = Scene_Welcome::create();
    
    scene->addChild(layer);
    return scene;
}

void Scene_Welcome::onEnter()
{
     CCLayer::onEnter();
    GameShare_Global::shareGlobal()->loginType = LoginType_QQ;
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    GameShare_Global::shareGlobal()->loginType = LoginType_Tourist;
    
#endif
    
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

    
//    UIImageView* logoImg = dynamic_cast<UIImageView*>(ul->getWidgetByName("Logo"));
//    logoImg->setPosition(ccp(logoImg->getPosition().x,visibleSize.height-200));
    
    //设置是否显示其他登陆按钮.
    if (GameShare_Data::shareData()->getUserUUID() != "") {
        this->setBtnState(true);
//        this->setBtnState(false);
    }else{
        this->setBtnState(false);
    }
    
    //是否关闭声音和音效.
    if (CCUserDefault::sharedUserDefault()->getBoolForKey(KEY_ISMUSIC)){
        CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0);
    }
    if (CCUserDefault::sharedUserDefault()->getBoolForKey(KEY_ISMUSICEFFECT)){
        CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(0);
    }

// 	//请求玩家数据
//     CItemMan::sharedInstance().RequestGetAllItem();
//     CMoneyMan::sharedInstance().RequestGetMoneyTmpInfo();
//     CStrengthenMan::sharedInstance().RequestGetAllStrength();
//     CGameInfoMan::sharedInstance().RequestgetGameInfo();
//     
//     //一些游戏共有数据
//     for (int i = Game_Memory; i<Game_Cir; i++) {
//         
//         CStrengthenMan::sharedInstance().RequestGetInfoByGameId(i);
//         CItemMan::sharedInstance().RequestGetItemInfoByGame(i);
//     }
}
void Scene_Welcome::onEnterTransitionDidFinish()
{
//    GameShare_NetSystem::ShareNetSystem()->NetSystem_HTTPRequest("http://raw.github.com/minggo/AssetsManagerTest/master/version","0");
    requestLoadData();
	//requestLoadData();
}
bool Scene_Welcome::init()
{
    char mingwen[] = "http://www.baidu.com";
    char miwen_hex[1024];
    //char miwen_hex[] = "8FEEEFE524F8B68DC1FCA2899AC1A6B82E636F6D";
    char result[1024];
    unsigned char key[] = "xcysoft123";
    AES aes(key);
    aes.Cipher(mingwen, miwen_hex);
    CCLog("AES:%s\n",miwen_hex);
    aes.InvCipher(miwen_hex, result);
    CCLog("AES:%s\n",result);
    getchar();

    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
	CCSpriteFrameManage::getInstance()->addSpriteFramesWithFile("common/common0.plist");
//	
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("./CocoStudioResources/FriendList0.plist", "./CocoStudioResources/FriendList0.png");
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("./CocoStudioResources/FriendList1.plist", "./CocoStudioResources/FriendList1.png");
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("./Link/linkerPic.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("./GameMemoryLayer/PigBrother.plist");

    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plMedalImages, imgMedalImages);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(Scene_Welcome::qqLoginSuccess), kQQLoginSuccess, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(Scene_Welcome::sinaLoginSuccess), kSinaLoginSuccess, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(Scene_Welcome::loginFail), kLoginFail, NULL);
    
    for (int i = 1; i <= 5; i++) {
        CCString str;
        str.initWithFormat("medal600001_%d", i);
        CCUserDefault::sharedUserDefault() -> setIntegerForKey(str.getCString(), 0);
    }
   
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    CCSprite* bg = CCSprite::create("./CocoStudioResources/welcomeBg.jpg");
    bg->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
    this->addChild(bg);
    
    
    
    ul = UILayer::create();
    auto myLayout = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("./CocoStudioResources/Login.json"));
    ul->addWidget(myLayout);
    ul->setContentSize(visibleSize);
    this->addChild(ul, 0, 100);
    GameLayer_Logo  *gameLayer_Login = GameLayer_Logo::create();
    ul->addChild(gameLayer_Login);
    return true;
}



void Scene_Welcome::setBtnState(bool isLogin)
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    UIButton* noLoginBtn = dynamic_cast<UIButton*>(ul->getWidgetByName("NoLogin"));
    noLoginBtn->setOpacity(128);
    noLoginBtn->setTouchEnable(true);
    noLoginBtn->setPressedActionEnabled(true);
    noLoginBtn->addReleaseEvent(this, coco_releaseselector(Scene_Welcome::startGameNoLogin));
    
    UIButton* sinaLoginBtn = dynamic_cast<UIButton*>(ul->getWidgetByName("SinaLogin"));
    sinaLoginBtn->addReleaseEvent(this, coco_releaseselector(Scene_Welcome::startGameSinaLogin));
    sinaLoginBtn->setPressedActionEnabled(true);
    
    UIButton* qqLoginBtn = dynamic_cast<UIButton*>(ul->getWidgetByName("QQLogin"));
    qqLoginBtn->addReleaseEvent(this, coco_releaseselector(Scene_Welcome::startGameQQLogin));
    qqLoginBtn->setPressedActionEnabled(true);
    
    if (isLogin) {
        qqLoginBtn->setTouchEnabled(false);
        sinaLoginBtn->setTouchEnabled(false);
        qqLoginBtn->setVisible(false);
        sinaLoginBtn->setVisible(false);
        noLoginBtn->setTextures("./CocoStudioResources/IsLoginImg.png", "./CocoStudioResources/IsLoginImg.png", "");
        noLoginBtn->setPosition(ccp(visibleSize.width/2, noLoginBtn->getPosition().y));
        if (GameShare_Data::shareData()->getSinaID() != "") {
            GameShare_Global::shareGlobal()->loginType = LoginType_Sina;
        }else{
            GameShare_Global::shareGlobal()->loginType = LoginType_QQ;
        }
    }else{
        qqLoginBtn->setTouchEnabled(false);
        sinaLoginBtn->setTouchEnabled(true);
        qqLoginBtn->setVisible(false);
        sinaLoginBtn->setVisible(true);
        noLoginBtn->setTextures("./CocoStudioResources/btn_17.png", "./CocoStudioResources/btn_17.png", "");
        noLoginBtn->setPosition(ccp(visibleSize.width/2, noLoginBtn->getPosition().y));
    }
    
}
void Scene_Welcome::loginFail(cocos2d::CCObject *object)
{
    GameShare_Data::shareData()->setUserUUID("");
    this->setBtnState(false);
}
void Scene_Welcome::qqLoginSuccess(cocos2d::CCObject *object)
{
    this->setBtnState(true);
    CPlayerInfoMan::sharedInstance().RequestPlayRegist(GameShare_Data::shareData()->getUserName().c_str(),GameShare_Data::shareData()->getUserUrl().c_str(),LoginType_QQ,CPlayerInfoMan::sharedInstance().getPlayerInfo().strQQ.c_str(),GameShare_Data::shareData()->getQQTime());
    GameShare_Global::shareGlobal()->loginType = LoginType_QQ;
//    sleep(1);

}
void Scene_Welcome::sinaLoginSuccess(cocos2d::CCObject *object)
{
    this->setBtnState(true);
    CPlayerInfoMan::sharedInstance().RequestPlayRegist(GameShare_Data::shareData()->getUserName().c_str(),GameShare_Data::shareData()->getUserUrl().c_str(),LoginType_Sina,CPlayerInfoMan::sharedInstance().getPlayerInfo().strSina.c_str(),GameShare_Data::shareData()->getSinaTime());
//    sleep(1);
    GameShare_Global::shareGlobal()->loginType = LoginType_Sina;
//    CCScene *scene_GameList = Scene_GameList::scene();
//    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.4, scene_GameList));
}
void Scene_Welcome::startGameQQLogin(cocos2d::CCObject *object)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    QQInterface::shareInstant()->login();
//        CPlayerInfoMan::sharedInstance().RequestPlayRegist(CPlayerInfoMan::sharedInstance().getPlayerInfo().strSina.c_str());
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    

    
#endif
}
void Scene_Welcome::startGameSinaLogin(cocos2d::CCObject *object)
{
    //    [QQInterface shareInstance];
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    SinaInterface::shareInstant()->login();

#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    
    
#endif
}
void Scene_Welcome::startGameNoLogin(cocos2d::CCObject *object){
    
//    ((UIButton*)object)->setTouchEnable(false);
  //  GameShare_Global::shareGlobal()->loginType = LoginType_Tourist;
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
//    UILayer *ul1 = UILayer::create();
//    this -> addChild(ul1);
//    std::string str = GameShare_Data::shareData()->getUserUUID();
//    UILabel *label = UILabel::create();
//    label ->setText(str.c_str());
//    label -> setPosition(ccp(350, 400));
//    label -> setColor(ccBLACK);
//    label -> setScale(2);
//    ul -> addWidget(label);
    
//    label -> runAction(CCSequence::create(CCDelayTime::create(3), CCRemoveSelf::create(),NULL));

    if (GameShare_Data::shareData()->getUserUUID() != "") {
        
        CPlayerInfoMan::sharedInstance().setLoginPreson(false);
        //requestLoadData();
        CPlayerInfoMan::sharedInstance().getPlayerInfo().strUuId = GameShare_Data::shareData()->getUserUUID();
        CPlayerInfoMan::sharedInstance().RequestPlayerInfo();
        SinaInterface::shareInstant()->getFriend();
        CPlayerInfoMan::sharedInstance().setLognFirst(true);
        
    }else
    {
        CPlayerInfoMan::sharedInstance().setLoginPreson(true);
        CCScene *scene_GameList = Scene_GameList::scene();
        CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.4, scene_GameList));
        
    }
    
#else
    CPlayerInfoMan::sharedInstance().setLoginPreson(false);
    
    CPlayerInfoMan::sharedInstance().RequestPlayerInfo();
    
#endif
    CCLOG("startGameNoLogin(): UUID = %s",GameShare_Data::shareData()->getUserUUID().c_str());
}
void Scene_Welcome::requestLoadData()
{
	//请求玩家数据
	CItemMan::sharedInstance().RequestGetAllItem();
	CMoneyMan::sharedInstance().RequestGetMoneyTmpInfo();
	CStrengthenMan::sharedInstance().RequestGetAllStrength();
	CGameInfoMan::sharedInstance().RequestgetGameInfo();
	CTaskMan::sharedInstance().requestDayTaskTemp();
    
    
	//一些游戏共有数据
	for (int i = Game_Memory; i<Game_Cir; i++) {
        
		CStrengthenMan::sharedInstance().RequestGetInfoByGameId(i);
		CItemMan::sharedInstance().RequestGetItemInfoByGame(i);
	}

}