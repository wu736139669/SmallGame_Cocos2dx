//
// GameMedalLayer.cpp
// OnceAgain
//
// Created by xiaohai on 14-4-28.
//
//

#include "GameMedalLayer.h"
#include "GameUIExportJson.h"
#include "GameMedalItemLayer.h"
#include "Scene_GameOver.h"
#include "GameShare_Global.h"
#include "MsgDefine.h"
#include "NetCallBack.h"
#include "XQDate.h"
#include "PlayerInfoManager.h"

GameMedalLayer::GameMedalLayer():m_bSetBadge(false)
{
 
}

GameMedalLayer::~GameMedalLayer()
{
//    CC_SAFE_RELEASE(ul);
}

bool GameMedalLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    isGameFinishCall = false;
    this->setTouchEnabled(true);
    isBeforeGame = false;
    infoList.clear();
    initData();
    BindingUIItems();
    return true;
}

#pragma mark - initData
void GameMedalLayer::initData()
{
   CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

    // add your codes here...
    CCLayerColor *backGround = CCLayerColor::create(ccc4(0, 0, 0, 120));
    backGround->setContentSize(visibleSize);
    backGround->setZOrder(0);
    this -> addChild(backGround);
    ul = UILayer::create();
    ul->retain();
    auto myLayout = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("./CocoStudioResources/GameMedalLayer.json"));
    ul->addWidget(myLayout);
    ul->setContentSize(visibleSize);
    this->addChild(ul, 1, 100);
}
void GameMedalLayer::BindingUIItems() {
    //绑定ui界面item
    sureBtn = dynamic_cast<UIButton*>(ul->getWidgetByName("Button_7"));
}


void GameMedalLayer::setCallBackByGameFinish(cocos2d::CCObject *target1, SEL_CallFunc callFun) {
    tar = target1;
    selector = callFun;
    isGameFinishCall = true;
}


void GameMedalLayer::httpCallBack(CCObject* p) {
//     CCString str;
//     str.initWithFormat("%d%d%d", eNetMsgTypeMissionSys, eNetMsgEveryDay, GameType);
//     CSJson::Value root = XQDate::sharedInstance().GetDate(str.getCString());
//     for (int i = 0; i < root.size(); i++) {
//         CSJson::Value& val = root[i];
//         int isGet = XQDate::sharedInstance().getValueForInt(val, "taskcomplete");
//         int kid = XQDate::sharedInstance().getValueForInt(val, "taskid");
//         SMeDalTaskData *medalinfo = CTaskMan::sharedInstance().getMedalTaskDataById(kid);
//         GameMedalItemLayer *medal = GameMedalItemLayer::create();
//         medal -> setMadelInfo(medalinfo, isGet, GameType);
//         CCString str;
//         str.initWithFormat("Medal_%d", i+1);
//         UIPanel *box = static_cast<UIPanel*>(ul -> getWidgetByName(str.getCString()));
//         box -> addCCNode(medal);
//     }
	createItems();
}

void GameMedalLayer::createItems(SMeDalTaskData *medalinfo, int isGet,int i) {
    GameMedalItemLayer *medal = GameMedalItemLayer::create();
    medal -> setMadelInfo(medalinfo, isGet, GameType);
    CCString str;
    str.initWithFormat("Medal_%d", i+1);
    UIPanel *box = static_cast<UIPanel*>(ul -> getWidgetByName(str.getCString()));
    box -> addCCNode(medal);
    
}

void GameMedalLayer::createItems()
{
//	if(m_bSetBadge==true)
//		SetBadge();

	 visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	VEC_EVERYDAYPTR vec;
	CTaskMan::sharedInstance().getEveryDayTaskByGamaId(vec);
	for (int i = 0; i < vec.size(); i++) {
		CEveryDayCell* p = vec[i];
		GameMedalItemLayer *medal = GameMedalItemLayer::create();
		//
		//medal->BadgeUpdate(visibleSize.width/3,visibleSize.height/4);
		medal -> setMadelInfo(p->getData(), p->getTaskComplete(), p->getGameId(),p->getPlayAni());
		CCString str;
		str.initWithFormat("Medal_%d", i+1);
		UIPanel *box = static_cast<UIPanel*>(ul -> getWidgetByName(str.getCString()));
		box -> addCCNode(medal);
	}
    int nCounter=0;
    for (int i = 0; i < vec.size(); i++) {
		CEveryDayCell* p = vec[i];
        if (p->getTaskComplete()) {
            nCounter++;
        }
    }
    if(CTaskMan::sharedInstance().isNewDayTaskComplate(GameShare_Global::shareGlobal()->gameType)) {
        if (nCounter>=3) {
            SetBadge();
        }
    }
    
    CTaskMan::sharedInstance().resetNewDayTask(GameShare_Global::shareGlobal()->gameType);
}

void GameMedalLayer::setGameType(int GameId) {
    GameType = GameId;
    isBeforeGame = true;
    sureBtn->setPressedActionEnabled(true);
    sureBtn->addReleaseEvent(this, coco_releaseselector(GameMedalLayer::exitLayer));
}

void GameMedalLayer::exitLayer(CCObject *p) {
    if (isGameFinishCall) {
        (tar->*selector)();
    }
    else {
        this->removeFromParent();
    }
}

void GameMedalLayer::setCallback(CCObject* target1, SEL_CallFuncO callfun,int btnTag) {
    sureBtn->setPressedActionEnabled(true);
    sureBtn->addReleaseEvent(target1, callfun);
    sureBtn->setTag(btnTag);
}

void GameMedalLayer::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    CCLayer::registerWithTouchDispatcher();
}

bool GameMedalLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    return true;
}

void GameMedalLayer::onEnter() {
    CCLayer::onEnter();
    CCString str;
    str.initWithFormat("%d%d%d", eNetMsgTypeMissionSys, eNetMsgEveryDay, GameType);
    
    XQDate::sharedInstance().setGameType(GameType);
    CSJson::Value msg_body;
    msg_body["playerid"] = CSJson::Value(CPlayerInfoMan::sharedInstance().getPlayerInfo().nId);
    msg_body["gameid"] = CSJson::Value(GameType);
    NetHttpClient::sharedInstance().XQsendHttpRequest(eNetMsgTypeMissionSys, eNetMsgEveryDay, &msg_body, this, coco_myevent(GameMedalLayer::httpCallBack));

}
void GameMedalLayer::SetBadge(){

	//设置 背景颜色
	//
	//;			//光效 精灵 ;
	//CCSprite *m_pRay2;			//光束 
	//;			//徽章
	//CCSprite* m_pGrade;			//分数；
	//CCSprite *m_pBackground;

	CCSize Size = CCDirector::sharedDirector()->getVisibleSize();
	m_pBackGroundColor = CCLayerColor::create(ccc4(0, 0, 0, 120));		//设置背景颜色;
	m_pBackGroundColor->setContentSize(Size);
	m_pBackGroundColor->setZOrder(0);
	m_pBackGroundColor->setPosition(ccp(0,0));
	addChild(m_pBackGroundColor,2);
	
	CCActionInterval * rotateby = CCRotateBy::create(2.8, 360);
	CCActionInterval * scaleby = CCScaleBy::create(0.5, 1.2);
	CCActionInterval * scaleby2 = CCScaleBy::create(2.5, 1.0);
	CCActionInterval * scaleby3 = CCScaleBy::create(0.5, 0.5);

	CCActionInterval * scaleby4 = CCScaleBy::create(0.5, 2.0);
	CCActionInterval * scaleby5 = CCScaleBy::create(0.5, 0.5);
	CCActionInterval * scaleby6 = CCScaleBy::create(0.5, 1.0);
	
	m_pRay = CCSprite::create("MedalImages/Ray.png");
	m_pRay->setPosition(ccp(Size.width/2,Size.height/2));
	this->addChild(m_pRay,2);
	m_pRay->setScale(0.5);
	CCFiniteTimeAction* action1 = CCSequence::create(scaleby4,rotateby,scaleby5 ,NULL);
	m_pRay->runAction(action1);

	m_pRay2 = CCSprite::create("MedalImages/Ray3.png");
	m_pRay2->setPosition(ccp(Size.width/2,Size.height/2));
	this->addChild(m_pRay2,2);
		
	m_pBadge = CCSprite::create("MedalImages/Badge.png");
	m_pBadge->setPosition(ccp(Size.width/2,Size.height/2));
	this->addChild(m_pBadge,2);
	m_pRay->setScale(0.5);
	CCFiniteTimeAction* action2 = CCSequence::create(scaleby6,scaleby,scaleby2,scaleby3,NULL);
	m_pBadge->runAction(action2);


	//m_pRay = CCSprite::create("MedalImages/Ray.png");

	//

	//m_pRay2 = CCSprite::create("");
	//  

	this->scheduleOnce(schedule_selector(GameMedalLayer::SetGrade), 2.0f);
	this->scheduleOnce(schedule_selector(GameMedalLayer::SetStar), 1.3f);
	this->scheduleOnce(schedule_selector(GameMedalLayer::deleteSprite), 4.0f);
	this->scheduleOnce(schedule_selector(GameMedalLayer::deleteGrade), 3.0f);
}
void GameMedalLayer::SetGrade(float td)
{
	CCSize Size = CCDirector::sharedDirector()->getVisibleSize();
	m_pGrade = CCSprite::create("MedalImages/Grade.png");
	m_pGrade->setPosition(ccp(Size.width/2,Size.height/2));
	this->addChild(m_pGrade,3);

	m_pRay3 = CCSprite::create("MedalImages/Ray2.png");
	m_pRay3->setPosition(ccp(Size.width/2,Size.height/2));
	this->addChild(m_pRay3,3);

	CCActionInterval * moveBy = CCMoveBy::create(1.0,ccp(0, 300));
	CCActionInterval * moveBy2 = CCMoveBy::create(1.0,ccp(0, 300));
	CCActionInterval * scaleby8 = CCScaleBy::create(1.0, 1.5);
	m_pGrade->runAction(moveBy);
	m_pGrade->runAction(scaleby8);
	m_pRay3->runAction(moveBy2);	
}
void GameMedalLayer::SetStar(float td)
{
	CCSize Size = CCDirector::sharedDirector()->getVisibleSize();
	m_pStart = CCSprite::create("./CocoStudioResources/ItemStrengthern/EffectStar.png");
	m_pStart->setPosition(ccp(Size.width/2-100,Size.height/2-100));
	this->addChild(m_pStart,3);

	m_pStart1 = CCSprite::create("./CocoStudioResources/ItemStrengthern/EffectStar.png");
	m_pStart1->setPosition(ccp(Size.width/2-100,Size.height/2+100));
	this->addChild(m_pStart1,3);

	m_pStart2 = CCSprite::create("./CocoStudioResources/ItemStrengthern/EffectStar.png");
	m_pStart2->setPosition(ccp(Size.width/2+100,Size.height/2+100));
	this->addChild(m_pStart2,3);

	CCActionInterval * scaleby7 = CCScaleBy::create(0.5, 0.8);

	CCFiniteTimeAction* seq1 = CCSequence::create(scaleby7,scaleby7->reverse(),NULL);
	CCFiniteTimeAction *repeat = CCRepeat::create(seq1, 3);
	CCFiniteTimeAction *repeat1 = CCRepeat::create(seq1, 3);
	CCFiniteTimeAction *repeat2 = CCRepeat::create(seq1, 3);
	m_pStart->runAction(repeat);
	m_pStart1->runAction(repeat1);
	m_pStart1->runAction(repeat2);
	
}
void GameMedalLayer::deleteSprite(float td)
{
	this->removeChild(m_pBackGroundColor);
	this->removeChild(m_pRay);
	this->removeChild(m_pRay2);
	this->removeChild(m_pBadge);
	this->removeChild(m_pStart);
	this->removeChild(m_pStart1);
	this->removeChild(m_pStart2);
}
void GameMedalLayer::deleteGrade(float td)
{
	this->removeChild(m_pRay3);
	this->removeChild(m_pGrade);
}