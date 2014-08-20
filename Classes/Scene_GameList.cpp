//
//  Scene_GameList.cpp
//  OnceAgain
//
//  Created by xiaohai on 14-2-21.
//
//

#include "Scene_GameList.h"
#include "DialogManager.h"
#include "TimeUtil.h"
#include "PlayerInfoManager.h"
#include "Scene_Reward.h"
#include "GameLayerSysInfo.h"
#include "GameLayerFriendTaskList.h"
#include "GameLayerFriendList.h"
#include "GameLayerChallenge.h"
#include "FriendManager.h"
#include "GameShare_Msg.h"
#include "GameLayerChallenge.h"
#include "InfoSysManager.h"
#include "TaskManager.h"
#include "GameLayerInvite.h"
#include "GameWeekRewardLayer.h"
#include "PlayerInfoAndFightLayer.h"
#include "GameItemManager.h"
#include "NetHttpClient.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#include "QQInterface.h"
#include "SinaInterface.h"
#include "GameItemManager.h"

#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#endif

enum GameList_Tag{
    GameLayer_Tag = 100
};

Scene_GameList::Scene_GameList()
{
    gameLayer = NULL;
    dayLoginLayer = NULL;
   // isGetFriendList = false;
}
Scene_GameList::~Scene_GameList()
{
//    CC_SAFE_RELEASE(gameLayer);
//    CC_SAFE_RELEASE(gameResource);
    GUIReader::shareReader()->purgeGUIReader();
    DictionaryHelper::shareHelper()->purgeDictionaryHelper();
    ActionManager::shareManager()->purgeActionManager();
    
    CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
}
CCScene* Scene_GameList::scene()
{
    CCScene *scene = CCScene::create();
    Scene_GameList *layer = Scene_GameList::create();
    scene->addChild(layer);
    return scene;
}

bool Scene_GameList::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    //初始化游戏数据.
    
    //背景图片.
    CCSprite* bgSprite = CCSprite::create("./CocoStudioResources/bg.png");
    bgSprite->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
    this->addChild(bgSprite);
    
    //上面的游戏资源
    

    //游戏列表
    gameLayer = GetDlgPtr(GameTableLayer);
    gameLayer->ignoreAnchorPointForPosition(false);
    gameLayer->setAnchorPoint(ccp(0.5, 0.5));
    gameLayer->setPosition(visibleSize.width/2, visibleSize.height/2);
    gameLayer->setTag(GameLayer_Tag);
    this->addChild(gameLayer);
    
    this->initListen();

    //下面的游戏菜单.
    GameLayer_Menu* gameMenu = GetDlgPtr(GameLayer_Menu);
    gameMenu->addSetBtnCallback(this, coco_releaseselector(Scene_GameList::setButtonCallback));
    gameMenu->addTaskBtnCallback(this, coco_releaseselector(Scene_GameList::setTaskCallback));
    gameMenu->addSysInfoCallback(this, coco_releaseselector(Scene_GameList::setSysInfoCallback));
    gameMenu->addFriendCallBack(this, coco_releaseselector(Scene_GameList::setFriendCallback));
    gameMenu->addRankCallBack(this, coco_releaseselector(Scene_GameList::setRankCallback));
    if (GameShare_Global::shareGlobal()->loginType == LoginType_Tourist) {
        gameMenu->setNoLogin(false);
    }else
    {
        gameMenu->setNoLogin(true);
    }
    
    this->addChild(gameMenu);
    
    if (GameShare_Global::shareGlobal()->loginType != LoginType_Tourist) {
        gameResource = GetDlgPtr(GameLayer_Resource);
        gameResource->addGoldCallback(this, coco_releaseselector(Scene_GameList::addGoldCallback));
        gameResource->addDiamondCallback(this, coco_releaseselector(Scene_GameList::addDiamondCallback));
        this->addChild(gameResource);
        gameLayer->riceBar->setVisible(true);
        gameLayer->riceBar->addRiceCallbackFunc(this, coco_releaseselector(Scene_GameList::addRiceCallback));
    }else{
        gameLayer->riceBar->setVisible(false);
        gameLayer->riceBar->addRiceCallbackFunc(NULL, NULL);
    }

    
    //每日登陆.
    //先判断是否已经过了一天.

    
    DateTime nowTime = CTimeUtil::GetSystemDateTime().dateTime;
    DateTime lastDailyTaskTime = CTimeUtil::FromTimeStamp(CPlayerInfoMan::sharedInstance().getPlayerInfo().lastDailyTaskTime);
    if ((nowTime.date.year>lastDailyTaskTime.date.year || nowTime.date.month>lastDailyTaskTime.date.month || nowTime.date.day>lastDailyTaskTime.date.day) && GameShare_Global::shareGlobal()->loginType != LoginType_Tourist) {
        dayLoginLayer = GameLayer_DayLogin::create();
        dayLoginLayer -> setCallBcak(this, callfunc_selector(Scene_GameList::setListForTheShowFriendScoreList));
        this->addChild(dayLoginLayer);
    }
    else {
        setListForTheShowFriendScoreList();
    }
    
    return true;
}

void Scene_GameList::setListForTheShowFriendScoreList() {
    bool isShow = true;
    isShow = CCUserDefault::sharedUserDefault() -> getBoolForKey("WellShowFriend");
    if (isShow&&!CPlayerInfoMan::sharedInstance().getLoinStatus()) {
        this -> runAction(CCSequence::create(CCDelayTime::create(0.01), CCCallFunc::create(this, callfunc_selector(Scene_GameList::addFriendListLayer)), NULL));
    }
}
void Scene_GameList::addFriendListLayer() {
    GameLayerFriendList* layer = GetDlgPtr(GameLayerFriendList);
    this->addChild(layer);
}

void Scene_GameList::initListen()
{
    //注册获得好友总分排行的通知.
   // CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(Scene_GameList::getFriendTotalRank), kGetAllScoreRank, NULL);
    //注册获得系统消息列表的通知.
   // CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(Scene_GameList::getInfoList), kGetSysInfo, NULL);
    //获取好友列表的通知.
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(Scene_GameList::getFriendList), kSinaGetFriendSuccess, NULL);
    //获取周任务列表的通知.
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(Scene_GameList::getTask), kGetWeekTask, NULL);
    //获取通知数量的更新.
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(Scene_GameList::setInfoNumCallback), kGetSysNum, NULL);
    //注册获得邀请好友列表的通知
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(Scene_GameList::requestPlayerMoneyInfoMation), kRefreshMoney, NULL);

}

#pragma mark  CallBack
//加载好友总排行榜框
void Scene_GameList::getFriendTotalRank(cocos2d::CCObject *pSender)
{
    
}
void Scene_GameList::getInfoList(cocos2d::CCObject *pSender)
{
 
}
void Scene_GameList::setSysInfoCallback(cocos2d::CCObject *pSender)
{
	GameLayerSysInfo* layer = GetDlgPtr(GameLayerSysInfo);
	this->addChild(layer);
}
void Scene_GameList::getFriendInfoListCallBack(cocos2d::CCObject *pSender) {
//    GameLayerInvite *layer = GameLayerInvite::create();
//    this->addChild(layer);
}
void Scene_GameList::setFriendCallback(cocos2d::CCObject *pSender)
{
    //获取玩家个人信息.
//    auto *layer = PlayerInfoAndFightLayer::create();
//    addChild(layer); 

//    GameLayerInvite *layer = GameLayerInvite::create();
//    this->addChild(layer);
    GameLayerInvite* layer = GetDlgPtr(GameLayerInvite);
    this->addChild(layer);
//#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
//    if (CPlayerInfoMan::sharedInstance().getLognFirst()) {
//        isGetFriendList = true;
//        SinaInterface::shareInstant()->getFriend();
//        CPlayerInfoMan::sharedInstance().setLognFirst(false);
//    }
//    else {
//        CInfoSysManager::sharedInstance().RequestFriendListFromSql();
//    }
// 
//    
//#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
//    
//#endif
//    CFriendManager::sharedInstance().RequestGetAllRank();
}
void Scene_GameList::getFriendList(cocos2d::CCObject *pSender)
{
//    if (isGetFriendList) {
//        CInfoSysManager::sharedInstance().RequestFriendListFromSql();
//        isGetFriendList = false;
//    }

}

void Scene_GameList::setRankCallback(cocos2d::CCObject *pSender)
{
	GameLayerFriendList* layer = GetDlgPtr(GameLayerFriendList);
	this->addChild(layer);
}
void Scene_GameList::setButtonCallback(cocos2d::CCObject *pSender)
{
    //系统设置
    GameShare_SysSet* sysSetLayer = GameShare_SysSet::create();
    sysSetLayer->setVisible(true);
   // sysSetLayer->retain();
    this->addChild(sysSetLayer);
//    sysSetLayer->setVisible(true);
}

void Scene_GameList::setTaskCallback(cocos2d::CCObject *pSender)
{
    CTaskMan::sharedInstance().requestWeekTaskTemp();

//    CCScene *scene = Scene_Reward::scene();
//    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.4, scene));
}
void Scene_GameList::setInfoNumCallback(cocos2d::CCObject *pSender)
{
    CInfoSysManager::sharedInstance().RequestGetInfoNum();
}
void Scene_GameList::getTask(cocos2d::CCObject *pSender)
{
    bool showTop = true;
    //循环排查是否所有任务完成
    VEC_SWEEKTASK& data = CTaskMan::sharedInstance().getWeekTaskData();
    for (int i = 0; i < data.size(); i ++) {
        if (data[i].haveGetReward == 0) {
            showTop = false;
        }
    }
    if (!showTop) {
        GameLayerFriendTaskList* layer = GameLayerFriendTaskList::create();
        this->addChild(layer);
    }
    else {
        //弹出抽奖页面
        auto *layer = GameWeekRewardLayer::create();
        this -> addChild(layer);
    }
}

void Scene_GameList::requestPlayerMoneyInfoMation(cocos2d::CCObject *p) {
    gameResource -> reSetLv(CPlayerInfoMan::sharedInstance().getPlayerInfo().nLevel, CPlayerInfoMan::sharedInstance().getPlayerInfo().nExp);
    gameResource->reSetDiamondNum(CPlayerInfoMan::sharedInstance().getPlayerInfo().nGem);
    gameResource->reSetGoldNum(CPlayerInfoMan::sharedInstance().getPlayerInfo().nMoney);
}

void Scene_GameList::addGoldCallback(cocos2d::CCObject *pSender)
{
    GameLayer_GoldMarket* goldMarket = GameLayer_GoldMarket::create();
    this->addChild(goldMarket);
}
void Scene_GameList::addDiamondCallback(cocos2d::CCObject *pSender)
{
    GameLayer_DiamondMarket* diamondMarket = GameLayer_DiamondMarket::create();
    this->addChild(diamondMarket);
}
void Scene_GameList::addRiceCallback(cocos2d::CCObject *pSender)
{
    GameLayer_RiceMarket* riceMarket = GameLayer_RiceMarket::create();
    this->addChild(riceMarket);
}
void Scene_GameList::onEnter()
{
    CCLayer::onEnter();
    gameLayer->reFresh();
    if (!CPlayerInfoMan::sharedInstance().getLoinStatus()) {
        CPlayerInfoMan::sharedInstance().RequestPlayerMoneyInfoMation();
        CInfoSysManager::sharedInstance().RequestGetInfoNum();
    }
}
void Scene_GameList::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
	CItemMan::sharedInstance().RequestGetPackItem();
}