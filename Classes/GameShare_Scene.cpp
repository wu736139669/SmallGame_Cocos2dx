//
//  GameShare_Scene.cpp
//  OnceAgain
//
//  Created by mac on 14-3-6.
//
//

#include "GameShare_Scene.h"
#include "Gamelist.h"
#include "CircleScene.h"
#include "PlayerInfoManager.h"
#include "SpriteFrameManage.h"
#include "GameLayerCrazyMode.h"
#include "GameInfoManager.h"
#include "DaPaoScene.h"
#include "TaikoScene.h"
#include "PkSysManager.h"
#include "TimeUtil.h"
#include "GameUIExportJson.h"
#include "GameMedalLayer.h"
#include "MsgDefine.h"
#include "Scene_GameItem.h"
#include "GameLayerNewerGuide.h"
#include "AudioHelper.h"
#include "DataManager.h"
#include "EffectActionHelp.h"
#include "RandomUtil.h"
#include "DialogManager.h"
#include "GameItemManager.h"
#include "TaskDefine.h"


enum Key_Sprite
{
    Key_Time = 100,
	Key_NewerHelp = 60000,
};

#define CrazyTag_Left   5001
#define CrazyTag_Right  5002
#define CrazyTag_Top    5003
#define CrazyTag_Bottom 5004
#define CrazyTag_Text   5005

GameShare_Scene::GameShare_Scene(void):mpUILayer(NULL),mbShowReadyGoAni(false)
{
    batterSprite = NULL;
    boom = NULL;
    pTimeProcessLayer = NULL;
    pauseMenuItem = NULL;
    pMenu = NULL;
    gameShare_Score = NULL;
    gameLayerPause = NULL;
    batter = 0;
    score = 0;
    energy = 0;
    mTime = 0;
    game_mode = Mode_Normal;
}
GameShare_Scene::~GameShare_Scene(void)
{
	//wsp
	//superItem->release();
	gameLayerPause->release();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
}
CCScene* GameShare_Scene::scene()
{
    // 'scene' Automatic release memory
    CCScene *scene = CCScene::create();
    // 'layer' Automatic release memory
    GameShare_Scene *layer = GameShare_Scene::create();
    scene->addChild(layer);
    return scene;
}

bool GameShare_Scene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    CRandomUtil::InitRandom();
    //初始化疯狂模式
    //Crazy_Init();
    addMoney = 0;
    
    this->initBgView();
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    //添加炸弹
    boom = GameShare_Boom::create();
    boom->setPosition(ccp(visibleSize.width/2-265, visibleSize.height/2+285));
    boom->setMaxEnergy(BOOM_MAXENERGY);
    this->addChild(boom,Tag_Max);

    //添加时间条.
    pTimeProcessLayer = GameShare_TimeProcess::create();
    pTimeProcessLayer->setTag(Key_Time);
    this->addChild(pTimeProcessLayer,Tag_Max);
    
    
    //暂停按键
    pauseMenuItem = CCMenuItemImage::create();
    //pauseMenuItem->setNormalSpriteFrame(GameShare_Texture::sharedTexture()->GetSpriteFrameByCCRect(akoopang_image, CCRect(402,  1785, 88, 80)));
	pauseMenuItem->setNormalSpriteFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName("common/pause.png"));
    pauseMenuItem->setTarget(this, menu_selector(GameShare_Scene::menuPauseCallBack));
    pauseMenuItem->setAnchorPoint(ccp(0, 0));
    pauseMenuItem->setPosition(ccp(0, visibleSize.height-pauseMenuItem->getContentSize().height));
//    pauseMenuItem->setVisible(false);
    pMenu = CCMenu::create(pauseMenuItem, NULL);
    pMenu->setPosition(ccp(0, 0));
	pMenu->setVisible(false);
	pMenu->setTouchEnabled(false);
    this->addChild(pMenu,Tag_Max);
    
    //分数
    gameShare_Score = GameShare_Score::create();
    gameShare_Score->setPosition(ccp(visibleSize.width-20, visibleSize.height /*- gameShare_Score->getBg()->getContentSize().height/2*/));
    this->addChild(gameShare_Score,Tag_Max);
    
    //连击
    batterSprite = GameShare_Batter::create();
    batterSprite->setPosition(ccp(visibleSize.width/2 - batterSprite->getRealWidth()/2, visibleSize.height - 287 - 26));
	batterSprite->setVisible(false);
//    batterSprite->setBatter(50);
    this->addChild(batterSprite,Tag_Max);

    //暂停按钮.
    gameLayerPause = GameShare_Pause::create();
    gameLayerPause->retain();
    gameLayerPause->setNewGameCallbackFunc(this, callfuncO_selector(GameShare_Scene::menuNewCallBack));
    gameLayerPause->setQuitGameCallbackFunc(this, callfuncO_selector(GameShare_Scene::menuQuitCallBack));
    gameLayerPause->setContinueCallbackFunc(this, callfuncO_selector(GameShare_Scene::menuContinueCallBack));
	gameLayerPause->setHelpCallbackFunc(this, callfuncO_selector(GameShare_Scene::menuHelpCallfunc));
    //注册监听
    this->initListerner();
    
	//
	mpUILayer = CGameLayerCrazyMode::create();
	mpUILayer->setVisible(false);
	this->addChild(mpUILayer, 5);
//    CCDirector::sharedDirector()->pause();
//    scheduleOnce(schedule_selector(GameShare_Scene::popSuperItem), 1.0);

    //    //纪录体力消耗时间
    if (CPlayerInfoMan::sharedInstance().getPlayerInfo().nPower == 5) {
//        CPlayerInfoMan::sharedInstance().getPlayerInfo().riceEndTime = CTimeUtil::GetSystemTimeStamp();
        CPlayerInfoMan::sharedInstance().getPlayerInfo().riceEndTime = 480;
    }
   
    return true;
}

void GameShare_Scene::setBackgroundMusic(const char *pszFilename)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(CCFileUtils::sharedFileUtils()->fullPathFromRelativeFile(pszFilename,""));
    if (!CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(std::string(CCFileUtils::sharedFileUtils()->fullPathFromRelativeFile(pszFilename,"")).c_str(), true);
    }
}
void GameShare_Scene::sureSuperItem(cocos2d::CCObject *object)
{
	GameLayer_SuperItem* p = dynamic_cast<GameLayer_SuperItem*>(object);
	if(p == NULL)
		return;
	
	clickLayerClose();
	if (p->getEvent() == eSuperItemBuyCrazy)
	{
		if(CItemMan::sharedInstance().useItem(ItemTag_15))
		{
			sItemData* pItem = CItemMan::sharedInstance().getSuperItem(ItemTag_15)->pData;
			CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(GameShare_Scene::msgHanlde_GameTimeOutPer), kGameTimeOutNamePer, NULL);
			time_addSecond(5);
			CItemMan::sharedInstance().removeSuperItem(ItemTag_15);
			CItemMan::sharedInstance().setGameOverBuyItemCounter(CItemMan::sharedInstance().getGameOverBuyItemCounter() + 1);
			resurgeCallfunc(1);
		}else if(CItemMan::sharedInstance().useItem(ItemTag_16))
		{
			sItemData* pItem = CItemMan::sharedInstance().getSuperItem(ItemTag_16)->pData;
			CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(GameShare_Scene::msgHanlde_GameTimeOutPer), kGameTimeOutNamePer, NULL);
			time_addSecond(10);
			CItemMan::sharedInstance().removeSuperItem(ItemTag_16);
			CItemMan::sharedInstance().setGameOverBuyItemCounter(CItemMan::sharedInstance().getGameOverBuyItemCounter() + 1);
			resurgeCallfunc(2);
		}
	}
}
void GameShare_Scene::resurgeCallfunc(int nTimes)
{

}
void GameShare_Scene::cancelSuperItem(CCObject* object)
{
	GameLayer_SuperItem* p = dynamic_cast<GameLayer_SuperItem*>(object);
	if(p == NULL)
		return;
	clickLayerClose();
	if (p->getEvent() == eSuperItemBuyCrazy)
	{
		msgHanlde_GameTimeOut(NULL);
	}
}
void GameShare_Scene::showReadyGo(CCObject* p)
{
	mbShowReadyGoAni = false;
    CCSize visibleSize= CCDirector::sharedDirector()->getVisibleSize();
    CCActionInterval* rpAction = CCSequence::create(CCShow::create(), CCScaleTo::create(1, 0.7), CCHide::create(), NULL);
    //CCSprite *readySprite = GameShare_Texture::sharedTexture()->GetSpriteByCCRect(akooakoo_image, CCRect(2, 462, 323, 281));
	CCSprite *readySprite = CCSprite::createWithSpriteFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName("common/ready.png"));
    readySprite->runAction(rpAction);
    readySprite->setVisible(false);
    readySprite->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
    this->addChild(readySprite,Tag_Max);
    
    
    rpAction = CCSequence::create(CCDelayTime::create(1), CCShow::create(), CCScaleTo::create(0.8, 0.7), CCHide::create(), NULL);
    //CCSprite *goSprite = GameShare_Texture::sharedTexture()->GetSpriteByCCRect(akooakoo_image, CCRect(421, 604, 323, 281));
	CCSprite *goSprite = CCSprite::createWithSpriteFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName("common/start.png"));
    goSprite->setVisible(false);
    goSprite->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
    goSprite->runAction(rpAction);
    this->addChild(goSprite,Tag_Max);
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(muEF_play_ready_go, false);
    scheduleOnce(schedule_selector(GameShare_Scene::readyGoCallBack), 2);

	//add start score
	if(CItemMan::sharedInstance().useItem(ItemTag_12))
	{
		setScore(500000);
	}else if (CItemMan::sharedInstance().useItem(ItemTag_13))
	{
	}
    
}
void GameShare_Scene::readyGoCallBack(float dt)
{
    pTimeProcessLayer->BeginTimeProcess();
    pMenu->setVisible(true);
    pMenu->setTouchEnabled(true);
    scheduleOnce(schedule_selector(GameShare_Scene::startGame), 0);
}
void GameShare_Scene::startGame(float dt){

}
void GameShare_Scene::initBgView()
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCSprite* pSprite = CCSprite::create();
    
    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 , visibleSize.height/2));
    
    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
}
#pragma mark Public
void GameShare_Scene::time_addSecond(unsigned int second)
{
    pTimeProcessLayer->AddSeconds(second);
}
void GameShare_Scene::setScore(unsigned long score)
{
    this->score = score;
    gameShare_Score->setScore(this->score);
}
void GameShare_Scene::setBatter(unsigned int batter)
{
    this->batter = batter;
    batterSprite->setBatter(batter);
}
void GameShare_Scene::boom_addEnergy(unsigned int energy)
{
    this->energy += energy;
    boom->addEnergy(energy);
}
void GameShare_Scene::boom_setEnergy(unsigned int energy)
{
    this->energy = energy;
    boom->setEnergy(energy);
}
void GameShare_Scene::boom_setMaxBoomEnergy(unsigned int maxBoom)
{
    boom->setMaxEnergy(maxBoom);
}


//疯狂模式
//开始疯狂模式
/*
 * @rfDurationTime 疯狂模式持续时间 每0.1检测一次 到点后结束  发送
 */

void GameShare_Scene::Crazy_Start(float rfDurationTime,ECrazyMode eMode)
{
    unschedule(schedule_selector(GameShare_Scene::Crazy_Check));
    schedule(schedule_selector(GameShare_Scene::Crazy_Check), 0.1);
    m_fCrazyTime = rfDurationTime;
    m_fCrazyNowTime = 0;
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	mpUILayer->pause();
	mpUILayer->play(eMode);
	mpUILayer->setVisible(true);
    CBaseData* p = CDataManager::GetInstance().getGameData();
    if (p) {
        if(p->getLastCrazyTime() == -1.f)
        {
            p->setLastCrazyTime(CTimeUtil::GetCocos2dxTimer());
           // CCLog("22222222222---%lf",p->getLastCrazyTime());
        }
    }
}
void GameShare_Scene::Crazy_SetTime(float rfDurationTime)
{
    unschedule(schedule_selector(GameShare_Scene::Crazy_Check));
	m_fCrazyTime = rfDurationTime;
	m_fCrazyNowTime = 0;
    schedule(schedule_selector(GameShare_Scene::Crazy_Check), 0.1);
   
}
//结束疯狂模式
void GameShare_Scene::Crazy_End()
{
	mpUILayer->pause();
	mpUILayer->setVisible(false);
    //发送结束通知
    CCNotificationCenter::sharedNotificationCenter()->postNotification(kCrazyTimeOut);
    CBaseData* p = CDataManager::GetInstance().getGameData();
    if (p) {
        if(p->getLastCrazyTime() != -1.f)
        {
            CTaskManProce(eDayTaskTypeShare_6, (CTimeUtil::GetCocos2dxTimer() - p->getLastCrazyTime())/1000.f);
            p->setLastCrazyTime(-1);
        }

    }
}

//检测疯狂模式
void GameShare_Scene::Crazy_Check(float rfParas)
{
    m_fCrazyNowTime += 0.1;
    if(m_fCrazyNowTime >= m_fCrazyTime)
    {
        //结束疯狂模式
        Crazy_End();
        unschedule(schedule_selector(GameShare_Scene::Crazy_Check));
    }
}


//初始化疯狂模式
void GameShare_Scene::Crazy_Init()
{
    ccBlendFunc ccb = {GL_SRC_ALPHA, GL_ONE};
    cocos2d::CCSprite*                   m_pSpriteFireLeft;
    cocos2d::CCSprite*                   m_pSpriteFireRight;
	cocos2d::CCSprite*                   m_pSpriteFireTop;
	cocos2d::CCSprite*                   m_pSpriteFireBottom;
    cocos2d::CCSprite*					 m_pCrazyText;
    
    CCRect rcFire(1, 1, 47, 1032);
    m_pSpriteFireLeft = GameShare_Texture::sharedTexture()->GetSpriteByCCRect(akoopang_image, rcFire);
	m_pSpriteFireLeft->setVisible(false);
	m_pSpriteFireLeft->setBlendFunc(ccb);
    m_pSpriteFireLeft->setTag(CrazyTag_Left);
    
	m_pSpriteFireRight = GameShare_Texture::sharedTexture()->GetSpriteByCCRect(akoopang_image, rcFire);
	m_pSpriteFireRight->setVisible(false);
	m_pSpriteFireRight->setBlendFunc(ccb);
	m_pSpriteFireRight->setFlipX(true);
    m_pSpriteFireRight->setTag(CrazyTag_Right);
    
    
	m_pSpriteFireTop = GameShare_Texture::sharedTexture()->GetSpriteByCCRect(akoopang_image, rcFire);
	m_pSpriteFireTop->setVisible(false);
	m_pSpriteFireTop->setBlendFunc(ccb);
	m_pSpriteFireTop->setRotation(90);
    m_pSpriteFireTop->setTag(CrazyTag_Top);
    
    
	m_pSpriteFireBottom = GameShare_Texture::sharedTexture()->GetSpriteByCCRect(akoopang_image, rcFire);
	m_pSpriteFireBottom->setVisible(false);
	m_pSpriteFireBottom->setBlendFunc(ccb);
	m_pSpriteFireBottom->setRotation(-90);
    m_pSpriteFireBottom->setTag(CrazyTag_Bottom);
    
    this->addChild(m_pSpriteFireLeft, 5);
    this->addChild(m_pSpriteFireRight, 5);
	this->addChild(m_pSpriteFireTop, 5);
	this->addChild(m_pSpriteFireBottom, 5);
    
    //crazy text
	CCRect rcCrazyText(75, 181, 422, 140);
	m_pCrazyText = GameShare_Texture::sharedTexture()->GetSpriteByCCRect(akoopang_image, rcCrazyText);
	m_pCrazyText->setVisible(true);
    m_pCrazyText->setTag(CrazyTag_Text);
	this->addChild(m_pCrazyText, 5);
    
}

//重新计时
void GameShare_Scene::Crazy_ReStart()
{
    m_fCrazyNowTime = 0;
}


#pragma menuCallBack
void GameShare_Scene::menuPauseCallBack(cocos2d::CCObject *pSender)
{
    this->operateAllSchedulerAndActions(this, eSwitchPause);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    this->addChild(gameLayerPause,Tag_Max);
    pMenu->setTouchEnabled(false);
}
void GameShare_Scene::menuHelpCallfunc(CCObject* pSender)
{
	if(gameLayerPause)
		gameLayerPause->removeFromParent();
	playNewerHelp();
}


void GameShare_Scene::menuContinueCallBack(cocos2d::CCObject *pSender)
{
	gameLayerPause->removeFromParent();
    menuContinueClick();
}
void GameShare_Scene::menuContinueClick()
{
	this->operateAllSchedulerAndActions(this, eSwitcResume);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	pMenu->setTouchEnabled(true);
}
void GameShare_Scene::addTouchDelegate()
{
	if (GameShare_Global::shareGlobal()->gameType == Game_Memory) {
		CCDirector::sharedDirector() ->getTouchDispatcher()->addStandardDelegate(this, 0);
	}
	else {
		CCDirector::sharedDirector() ->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	}
}
void GameShare_Scene::removeTouchDelegate()
{
	if (GameShare_Global::shareGlobal()->gameType == Game_Memory) {
		CCDirector::sharedDirector() ->getTouchDispatcher()->removeDelegate(this);
	}
	else {
		CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	}
}
void GameShare_Scene::menuQuitCallBack(cocos2d::CCObject *pSender)
{
    CCDirector::sharedDirector()->popScene();
}
void GameShare_Scene::menuNewCallBack(cocos2d::CCObject *pSender)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
//    CCScene *gameScene = GameShare_Scene::getGameSceneByType(GameShare_Global::shareGlobal()->gameType);
//    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.4, gameScene));
    
    if (GameShare_Global::shareGlobal()->loginType != LoginType_Tourist) {
        CCScene *scene_GameItem = Scene_GameItem::scene();
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.4, scene_GameItem));
    }else{
        CCScene* scene = GameShare_Scene::getGameSceneByType(GameShare_Global::shareGlobal()->gameType);
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.4, scene));
    }
}

#pragma timer
void GameShare_Scene::initListerner()
{
    //游戏结束发送信息通知.
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(GameShare_Scene::setScoreCallback), kSetScore, NULL);
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(GameShare_Scene::msgHanlde_GameTimeOut), kGameTimeOutName, NULL);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(GameShare_Scene::msgHanlde_GameTimeOutPer), kGameTimeOutNamePer, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(GameShare_Scene::msgHanlde_BoomFull), kGameBoomFull, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(GameShare_Scene::msgHandle_CrazyTimeOut), kCrazyTimeOut, NULL);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(GameShare_Scene::noticeTimeInterval), kTimeInterval, NULL);
}

//疯狂模式结束消息通知
void GameShare_Scene::msgHandle_CrazyTimeOut(CCObject* obj)
{
    
}
void GameShare_Scene::noticeTimeInterval(CCObject* obj)
{
	if (((GameShare_TimeProcess*)obj)->GetSecondsRemain() <= 3)
	{
		if (CItemMan::sharedInstance().useItem(ItemTag_11))
		{
			time_addSecond(10.0);
			useTimeEff();
		}

	}
}
void GameShare_Scene::msgHanlde_BoomFull(cocos2d::CCObject *obj)
{
    
}

void GameShare_Scene::msgHanlde_GameTimeOut(CCObject* obj)
{
    //停止背景音乐
//     CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
//     CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, kGameTimeOutName);
//     
// 	//time over audio
// 	unschedule(schedule_selector(GameShare_TimeProcess::TimeInterval));
// 	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(muEF_play_time_up, false);
// 
// 	//time over action
// 	CCActionInterval* rpAction = CCSequence::create(CCShow::create(), CCScaleTo::create(0.5, 0.9), CCScaleTo::create(0.5, 1.1), CCDelayTime::create(2), CCHide::create(),
// 		CCCallFunc::create(this, callfunc_selector(GameShare_Scene::callback_TimeOut)), NULL);
// 	pTimeProcessLayer->getTimeOver()->runAction(rpAction);
// 	//this->setTouchEnabled(false);
// 	removeTouchDelegate();
    CTaskMan::sharedInstance().setAddMoney(addMoney);
	CTaskManProceDt(eDayTaskTypeShare_2,1);
	requestResult();
	//save game every day task data
	CTaskMan::sharedInstance().requestSaveDayTaskComplateState();

}
void GameShare_Scene::msgHanlde_GameTimeOutPer(CCObject* obj)
{
	operateAllSchedulerAndActions(this, eSwitchPause);
	operateAllSchedulerAndActions(gameShare_Score, eSwitcResume);
	//停止背景音乐
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
	 CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, kGameTimeOutNamePer);
	//time over audio
	unschedule(schedule_selector(GameShare_TimeProcess::TimeInterval));
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(muEF_play_time_up, false);

	//time over action
	CCActionInterval* rpAction = CCSequence::create(CCShow::create(), CCScaleTo::create(0.5, 0.9), CCScaleTo::create(0.5, 1.1), CCDelayTime::create(2), CCHide::create(),
		CCCallFunc::create(this, callfunc_selector(GameShare_Scene::callback_TimeOut)), NULL);
	pTimeProcessLayer->getTimeOver()->runAction(rpAction);
	removeTouchDelegate();
}
void GameShare_Scene::callback_TimeOut()
{
	addTouchDelegate();
    if (CPlayerInfoMan::sharedInstance().getLoinStatus()) {
        setScoreCallback(NULL);
        return ;
    }
	int nCounter = CItemMan::sharedInstance().getGameOverBuyItemCounter();
	if(nCounter == 0)
		_showSuperItemLayer(ItemTag_15,eSuperItemBuyCrazy);
	else if(nCounter == 1)
		_showSuperItemLayer(ItemTag_16,eSuperItemBuyCrazy);
	else{
		msgHanlde_GameTimeOut(NULL);
	}
}
void GameShare_Scene::_showSuperItemLayer(int nItemId,int nEvent)
{
	GameLayer_SuperItem* pSuperItem = GetDlgPtr(GameLayer_SuperItem);
	pSuperItem->setItem(nItemId);
	pSuperItem->setEvent((ESuperItemEven)nEvent);
	pSuperItem->setSureCallbackFunc(this, callfuncO_selector(GameShare_Scene::sureSuperItem),callfuncO_selector(GameShare_Scene::cancelSuperItem));
	_addShowlayer(pSuperItem);
	_nextShowLayer();
}
void GameShare_Scene::requestResult()
{
	//发送pk
	if (CPkSysManager::sharedInstance().pkType == PkTypeSend) {
		CPkSysManager::sharedInstance().RequestSendPk(CPkSysManager::sharedInstance().playerId, GameShare_Global::shareGlobal()->gameType, score);
	}
	if (CPkSysManager::sharedInstance().pkType == PkTypeReceive) {
		CPkSysManager::sharedInstance().RequestReceivePk(CPkSysManager::sharedInstance().pkId, score);
	}
	//设置分数
	CGameInfoMan::sharedInstance().RequestSetGameMaxScore(GameShare_Global::shareGlobal()->gameType, score);
}
void GameShare_Scene::setScoreCallback(cocos2d::CCObject *pSender)
{
    CCScene*  scene = CCScene::create();
	Scene_GameOver* layer = Scene_GameOver::create();
    layer->setResultScore(score);
    layer->setMaxScore(Maxscore);
	scene->addChild(layer);
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, scene));
}

void GameShare_Scene::creatGameOverLayer(CCObject *p) {
    CCScene*  scene = CCScene::create();
	Scene_GameOver* layer = Scene_GameOver::create();
    layer->setResultScore(score);
    layer->setMaxScore(Maxscore);
	scene->addChild(layer);
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, scene));
}

void GameShare_Scene::useTimeEff()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
// 	CCSprite* p = CCSprite::createWithSpriteFrameName("GameItem/400003.png");
// 	p->setPosition(ccp(visibleSize.width/2,visibleSize.height/2 + 283));
// 	this->addChild(p,Tag_Max);
// 	p->setOpacity(254);
// 	p->runAction(CCSequence::create(CCShow::create(),CCFadeOut::create(1.5f),CCHide::create(),NULL) );
	CEffectActionHelper::play(eHelpTime,this,ccp(visibleSize.width/2,visibleSize.height/2 + 283));
}
#pragma mark touch
bool GameShare_Scene::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    this->ccTouchMoved(touch, event);
    return true;
}
void GameShare_Scene::ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    
}
void GameShare_Scene::ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    
}

void GameShare_Scene::onEnter()
{
	CCLayer::onEnter();
    //Register click event
    addTouchDelegate();
	
	//新手指引
	if(!CDataManager::GetInstance().getGameNewerGuideState(GameShare_Global::shareGlobal()->gameType))
	//if(1)
	{
		//playNewerHelp(callfuncO_selector(GameShare_Scene::showReadyGo));
		CGameLayerNewerGuide* pNewer = CGameLayerNewerGuide::create();
		pNewer->setType(eNewerGuideStart);
		_addShowlayer(pNewer);
		CDataManager::GetInstance().setGameNewerGuideState(GameShare_Global::shareGlobal()->gameType,true);
	}
	if (CRandomUtil::RandomRange(0,100) < 30 && !CPlayerInfoMan::sharedInstance().getLoinStatus()){
		GameLayer_SuperItem* pSuperItem = GetDlgPtr(GameLayer_SuperItem);
		pSuperItem->setItem(CItemMan::sharedInstance().randSuperItem());
		pSuperItem->setSureCallbackFunc(this, callfuncO_selector(GameShare_Scene::sureSuperItem),callfuncO_selector(GameShare_Scene::cancelSuperItem));
		_addShowlayer(pSuperItem);
	}
	if(!_nextShowLayer())
	{
		this->operateAllSchedulerAndActions(this, eSwitcResume);
		showReadyGo(NULL);
	}else
		mbShowReadyGoAni = true;
}
void GameShare_Scene::_addShowlayer(CCLayer* pLayer)
{
	mArrLayerShow.addObject(pLayer);
}
void GameShare_Scene::clickLayerClose()
{
	if(!_nextShowLayer())
	{
		menuContinueClick();
		if(mbShowReadyGoAni)
			showReadyGo(NULL);
	}
}
bool GameShare_Scene::_nextShowLayer()
{
	pMenu->setTouchEnabled(true);
	if (mArrLayerShow.count()<=0)
		return false;
	CCLayer* pLayer = dynamic_cast<CCLayer*>(mArrLayerShow.objectAtIndex(0)) ;
	if (pLayer){
		this->operateAllSchedulerAndActions(this, eSwitchPause);
		CAudioHelper::stopBackgroundSound();
		this->addChild(pLayer,Tag_Max);
		mArrLayerShow.removeObjectAtIndex(0);
		pMenu->setTouchEnabled(false);
	}
	return true;
}

void GameShare_Scene::operateAllSchedulerAndActions(ESwitchFlag flag/* =eSwitcResume */)
{
	operateAllSchedulerAndActions(this,flag);
}
void GameShare_Scene::playNewerHelp(SEL_CallFuncO pCallfunc)
{
	this->operateAllSchedulerAndActions(this, eSwitchPause);
	CAudioHelper::stopBackgroundSound();
	CGameLayerNewerGuide* pNewer = CGameLayerNewerGuide::create();
	pNewer->setTag(Key_NewerHelp);
	_addShowlayer(pNewer);
	_nextShowLayer();
}
void GameShare_Scene::onExit()
{
    //Overflow click event
	removeTouchDelegate();
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    CCLayer::onExit();
#ifdef _WIN32
	//test
	//CTaskMan::sharedInstance().requestSaveDayTaskComplateState();
#endif 
	//CTaskMan::sharedInstance().requestSaveDayTaskComplateState();
	//clear data
	CItemMan::sharedInstance().resetInside();
	CTaskMan::sharedInstance().resetInside();
}

CCScene* GameShare_Scene::getGameSceneByType(e_GameType gameType)
{
    CCScene *gameScene;
    switch (gameType) {
        case Game_Link:
            gameScene = GameNewLinker::createScene();
            GameShare_Global::shareGlobal()->gameType = Game_Link;
            break;
        case Game_Memory:
            gameScene = Game_Memory::scene();
            GameShare_Global::shareGlobal()->gameType = Game_Memory;
            break;
        case Game_Fruit:
            gameScene = CGameFruitScene ::scene();
            GameShare_Global::shareGlobal()->gameType = Game_Fruit;
            break;
		case Game_Jelly:
			gameScene = CRightTouchScene::create();
			GameShare_Global::shareGlobal()->gameType = Game_Jelly;
			break;
        case Game_TaiKo:
            gameScene = CTaikoScene::scene();
            GameShare_Global::shareGlobal()->gameType = Game_TaiKo;
            break;
        case Game_Null:
            gameScene = GameDemo::scene();
            GameShare_Global::shareGlobal()->gameType = Game_Null;
			break;
        case Game_SanXiao:
            gameScene = GameSanXiaoLayer::createScene();
            GameShare_Global::shareGlobal()->gameType = Game_SanXiao;
            break;
        default:
            gameScene = GameDemo::scene();
            GameShare_Global::shareGlobal()->gameType = Game_Null;
            break;
    }
    
    return gameScene;
}

void GameShare_Scene::operateAllSchedulerAndActions(cocos2d::CCNode* node, ESwitchFlag flag)
{
    if(node->isRunning()){
        switch (flag) {
            case eSwitchPause:
                node->pauseSchedulerAndActions();
                break;
            case eSwitcResume:
                node->resumeSchedulerAndActions();
                break;
            default:
                break;
        }
        CCArray* array = node->getChildren();
        if(array != NULL && array->count()>0){
            CCObject* iterator;
            CCARRAY_FOREACH(array, iterator){
                CCNode* child = (CCNode*)iterator;
                this->operateAllSchedulerAndActions(child, flag);
            }
        }
    }
}