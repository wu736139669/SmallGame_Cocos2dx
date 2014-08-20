//
//  GameLayer_RiceBar.cpp
//  OnceAgain
//
//  Created by mac on 14-3-25.
//
//

#include "GameLayer_RiceBar.h"
#include "GameShare_Global.h"
#include "Constant.h"
#include "PlayerInfoManager.h"
#include "NetPacket.h"
#include "MsgDefine.h"
#include "GameLayer_Tag.h"
#include "TimeUtil.h"
#include "NetHttpClient.h"
#include "MsgDefine.h"

IMPLEMENT_DLG_ID(GameLayer_RiceBar,RiceBar_Tag);

GameLayer_RiceBar::~GameLayer_RiceBar()
{
    GUIReader::shareReader()->purgeGUIReader();
    DictionaryHelper::shareHelper()->purgeDictionaryHelper();
    ActionManager::shareManager()->purgeActionManager();
}

void GameLayer_RiceBar::onEnter()
{
    CCLayer::onEnter();

    if (GameShare_Global::shareGlobal()->loginType != LoginType_Tourist) {
//        CCLOG("~%ld",nowTime);
//        nowTime = CPlayerInfoMan::sharedInstance().getPlayerInfo().riceEndTime;
//        CCLOG("~%ld",nowTime);
        if (CPlayerInfoMan::sharedInstance().getPlayerInfo().nPower<5) {
            this->schedule(schedule_selector(GameLayer_RiceBar::timeUpdate), 1.0);
        }
//        this->setRiceNum(CPlayerInfoMan::sharedInstance().getPlayerInfo().nPower);
    }
    
//    willrequistInfo
//    if (!willrequistInfo) {
//        CSJson::Value msg_body;
//        msg_body["playerid"] = CSJson::Value(CPlayerInfoMan::sharedInstance().getPlayerInfo().nId);
//        NetHttpClient::sendHttpRequest(eNetMsgTypePlayerSys, eNetMsgPlayerSysGetPlayerRiceInfo, &msg_body);
//    }
   
}
bool GameLayer_RiceBar::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    willrequistInfo = true;
    addRiceTime = RICEADDTIME;
    nowTime = 0;
//    nowTime = CTimeUtil::GetSystemTimeStamp();
    
    //系统设置界面.
    riceBar = UILayer::create();
    auto layout = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("./CocoStudioResources/RiceBar.json"));
    riceBar->addWidget(layout);
    //    sysSet->setVisible(true);
    this->addChild(riceBar, 0, 101);
    
//    UIPanel* panel = dynamic_cast<UIPanel*>(riceBar->getWidgetByName("DayLogin"));
//    panel->setBackGroundColor(ccBLACK);
//    panel->setBackGroundColorOpacity(150);
    //关闭按钮

    if (willrequistInfo) {
        willrequistInfo = false;
        CSJson::Value msg_body;
        msg_body["playerid"] = CSJson::Value(CPlayerInfoMan::sharedInstance().getPlayerInfo().nId);
        NetHttpClient::sendHttpRequest(eNetMsgTypePlayerSys, eNetMsgPlayerSysGetPlayerRiceInfo, &msg_body);
    }

    return true;
}

void GameLayer_RiceBar::setVisible(bool visible)
{
    CCLayer::setVisible(visible);
    UIPanel* dayLoginPanel = dynamic_cast<UIPanel*>(riceBar->getWidgetByName("Panel"));
    dayLoginPanel->setTouchEnable(visible);
}

void GameLayer_RiceBar::addRiceCallback(cocos2d::CCObject *pSender)
{
//    this->removeFromParent();
    
}
void GameLayer_RiceBar::addRiceCallbackFunc(cocos2d::CCObject *target, SEL_CallFuncO callfun)
{
    UIButton* addBtn = dynamic_cast<UIButton*>(riceBar->getWidgetByName("AddBtn"));
    addBtn->addReleaseEvent(target, callfun);
    addBtn->setPressedActionEnabled(true);
}

void GameLayer_RiceBar::setRiceNum(int riceNum)
{
	UIImageView* rice_0 = dynamic_cast<UIImageView*>(riceBar->getWidgetByName("Rice_0"));
	UIImageView* rice_1 = dynamic_cast<UIImageView*>(riceBar->getWidgetByName("Rice_1"));
	UIImageView* rice_2 = dynamic_cast<UIImageView*>(riceBar->getWidgetByName("Rice_2"));
	UIImageView* rice_3 = dynamic_cast<UIImageView*>(riceBar->getWidgetByName("Rice_3"));
	UIImageView* rice_4 = dynamic_cast<UIImageView*>(riceBar->getWidgetByName("Rice_4"));
	UIImageView* riceAdd = dynamic_cast<UIImageView*>(riceBar->getWidgetByName("RiceAdd"));
	UILabelAtlas* riceNumLabel = dynamic_cast<UILabelAtlas*>(riceBar->getWidgetByName("RiceNum"));
	UILabelAtlas* timeSecond = dynamic_cast<UILabelAtlas*>(riceBar->getWidgetByName("TimeSecond"));
	UILabelAtlas* timeMinute = dynamic_cast<UILabelAtlas*>(riceBar->getWidgetByName("TimeMinute"));
	UIImageView* colonImg = dynamic_cast<UIImageView*>(riceBar->getWidgetByName("Colon"));
	UIImageView* maxImg = dynamic_cast<UIImageView*>(riceBar->getWidgetByName("MaxImg"));
	iFaceRend = riceNum;
	if(bSprite==false)
	{
		pFace0 = CCSprite::create("./CocoStudioResources/Rice/phiz_11.png");
		pFace0->setPosition(ccp(72,874));
		pFace1 = CCSprite::create("./CocoStudioResources/Rice/phiz_11.png");
		pFace1->setPosition(ccp(124,874));
		pFace2 = CCSprite::create("./CocoStudioResources/Rice/phiz_11.png");
		pFace2->setPosition(ccp(174,874));
		pFace3 = CCSprite::create("./CocoStudioResources/Rice/phiz_11.png");
		pFace3->setPosition(ccp(228,874));
		pFace4 = CCSprite::create("./CocoStudioResources/Rice/phiz_11.png");
		pFace4->setPosition(ccp(284,874));
		this->addChild(pFace0,2);
		this->addChild(pFace1,2);
		this->addChild(pFace2,2);
		this->addChild(pFace3,2);
		this->addChild(pFace4,2);
	}
	bSprite=true;
	if (riceNum < 5) {
		this->unschedule(schedule_selector(GameLayer_RiceBar::timeUpdate));
		this->schedule(schedule_selector(GameLayer_RiceBar::timeUpdate), 1.0);
		maxImg->setVisible(false);
		riceAdd->setVisible(false);
		riceNumLabel->setVisible(false);
		colonImg->setVisible(true);
		timeSecond->setVisible(true);
		timeMinute->setVisible(true);

		char strSecnod[32];
		sprintf(strSecnod,"%d%d",addRiceTime%60/10,addRiceTime%60%10);
		timeSecond->setStringValue(strSecnod);


		char strMinute[32];
		sprintf(strMinute,"%d%d",addRiceTime/600,addRiceTime%600/60);
		timeMinute->setStringValue(strMinute);



		switch (CPlayerInfoMan::sharedInstance().getPlayerInfo().nPower) {
		case 0:
			{

				rice_0->setTexture("./CocoStudioResources/RiceNo.png");
				rice_1->setTexture("./CocoStudioResources/RiceNo.png");
				rice_2->setTexture("./CocoStudioResources/RiceNo.png");
				rice_3->setTexture("./CocoStudioResources/RiceNo.png");
				rice_4->setTexture("./CocoStudioResources/RiceNo.png");
				pFace0->setVisible(false);
				pFace1->setVisible(false);
				pFace2->setVisible(false);
				pFace3->setVisible(false);
				pFace4->setVisible(false);

			}
			break;
		case 1:
			{
				rice_0->setTexture("./CocoStudioResources/RiceHave.png");
				rice_1->setTexture("./CocoStudioResources/RiceNo.png");
				rice_2->setTexture("./CocoStudioResources/RiceNo.png");
				rice_3->setTexture("./CocoStudioResources/RiceNo.png");
				rice_4->setTexture("./CocoStudioResources/RiceNo.png");
				pFace0->setVisible(true);
				pFace1->setVisible(false);
				pFace2->setVisible(false);
				pFace3->setVisible(false);
				pFace4->setVisible(false);
			}
			break;
		case 2:
			{
				rice_0->setTexture("./CocoStudioResources/RiceHave.png");
				rice_1->setTexture("./CocoStudioResources/RiceHave.png");
				rice_2->setTexture("./CocoStudioResources/RiceNo.png");
				rice_3->setTexture("./CocoStudioResources/RiceNo.png");
				rice_4->setTexture("./CocoStudioResources/RiceNo.png");
				pFace0->setVisible(true);
				pFace1->setVisible(true);
				pFace2->setVisible(false);
				pFace3->setVisible(false);
				pFace4->setVisible(false);

			}
			break;
		case 3:
			{
				rice_0->setTexture("./CocoStudioResources/RiceHave.png");
				rice_1->setTexture("./CocoStudioResources/RiceHave.png");
				rice_2->setTexture("./CocoStudioResources/RiceHave.png");
				rice_3->setTexture("./CocoStudioResources/RiceNo.png");
				rice_4->setTexture("./CocoStudioResources/RiceNo.png");
				pFace0->setVisible(true);
				pFace1->setVisible(true);
				pFace2->setVisible(true);
				pFace3->setVisible(false);
				pFace4->setVisible(false);
			}
			break;
		case 4:
			{
				rice_0->setTexture("./CocoStudioResources/RiceHave.png");
				rice_1->setTexture("./CocoStudioResources/RiceHave.png");
				rice_2->setTexture("./CocoStudioResources/RiceHave.png");
				rice_3->setTexture("./CocoStudioResources/RiceHave.png");
				rice_4->setTexture("./CocoStudioResources/RiceNo.png");
				pFace0->setVisible(true);
				pFace1->setVisible(true);
				pFace2->setVisible(true);
				pFace3->setVisible(true);
				pFace4->setVisible(false);
			}
			break;
		default:
			break;
		}
	}else
	{
		this->unschedule(schedule_selector(GameLayer_RiceBar::timeUpdate));
		if (riceNum == 5) {
			riceAdd->setVisible(false);
			riceNumLabel->setVisible(false);
		}else{
			riceAdd->setVisible(true);
			riceNumLabel->setVisible(true);
		}
		maxImg->setVisible(true);
		colonImg->setVisible(false);
		timeSecond->setVisible(false);
		timeMinute->setVisible(false);
		rice_0->setTexture("./CocoStudioResources/RiceHave.png");
		rice_1->setTexture("./CocoStudioResources/RiceHave.png");
		rice_2->setTexture("./CocoStudioResources/RiceHave.png");
		rice_3->setTexture("./CocoStudioResources/RiceHave.png");
		rice_4->setTexture("./CocoStudioResources/RiceHave.png");
		pFace0->setVisible(true);
		pFace1->setVisible(true);
		pFace2->setVisible(true);
		pFace3->setVisible(true);
		pFace4->setVisible(true);

		UILabelAtlas* riceNumLabel = dynamic_cast<UILabelAtlas*>(riceBar->getWidgetByName("RiceNum"));
		char str[32];
		sprintf(str,"%d", riceNum-5);
		riceNumLabel->setStringValue(str);
	}
	this->schedule(schedule_selector(GameLayer_RiceBar::RiceFace), 5.0f);

}
#pragma mark time
void GameLayer_RiceBar::timeUpdate(float dt)
{
    CPlayerInfoMan::sharedInstance().getPlayerInfo().riceEndTime -= 1;
    addRiceTime = nowTime - CTimeUtil::GetSystemTimeStamp();
//    CCLOG("qqqqqqq__%d", addRiceTime);
//
//    long current = CTimeUtil::GetSystemTimeStamp();
//    int riceAddNum = (current-nowTime)/(1.0*RICEADDTIME);
//    if (riceAddNum>=1) {
//        addRiceTime = RICEADDTIME-((current-nowTime)- riceAddNum*(1.0*RICEADDTIME))/1.0;
//        nowTime = current;
//        //计算下一个要的时间
//        for (int i = 0; i<riceAddNum; i++) {
//            
//            CPlayerInfoMan::sharedInstance().getPlayerInfo().nPower++;
//            
//            if (CPlayerInfoMan::sharedInstance().getPlayerInfo().nPower>=5) {
//                break;
//            }
//        }
//        
//    }else{
//        addRiceTime = RICEADDTIME-(current-nowTime)/1.0;
//        
//    }
    if (addRiceTime <= 0) {
        this->unschedule(schedule_selector(GameLayer_RiceBar::timeUpdate));
        CSJson::Value msg_body;
        msg_body["playerid"] = CSJson::Value(CPlayerInfoMan::sharedInstance().getPlayerInfo().nId);
        NetHttpClient::sendHttpRequest(eNetMsgTypePlayerSys, eNetMsgPlayerSysGetPlayerRiceInfo, &msg_body);
    }
    this->setRiceNum(CPlayerInfoMan::sharedInstance().getPlayerInfo().nPower);
    
}

void GameLayer_RiceBar::checkTimeIsUp() {
    
    int addRiceTime1 = CPlayerInfoMan::sharedInstance().getPlayerInfo().riceEndTime;
    if (addRiceTime1 > 0) {
        nowTime = CTimeUtil::GetSystemTimeStamp() + addRiceTime1;
        this->unschedule(schedule_selector(GameLayer_RiceBar::timeUpdate));
        this->schedule(schedule_selector(GameLayer_RiceBar::timeUpdate), 1.0);
        
    }
}

bool GameLayer_RiceBar::onPackageFilter(void *pDataPkg) {
	CResponsePacket* pPkt = (CResponsePacket*)pDataPkg;
	unsigned int unMsgType = pPkt->getMsgType();
	unsigned int unMsgCode = pPkt->getMsgCode();
	//网络数据传输完成
	if (pPkt->getDataState() == eNetMsgDataStateComplete)
	{
		if (unMsgType == eNetMsgTypePlayerSys)
		{
            if (unMsgCode == eNetMsgPlayerSysChgTiLi)
			{
                this->setRiceNum(CPlayerInfoMan::sharedInstance().getPlayerInfo().nPower);
			}
            if (unMsgCode == eNetMsgPlayerSysReduceEnergy) {
                this->setRiceNum(CPlayerInfoMan::sharedInstance().getPlayerInfo().nPower);
            }
            if (unMsgCode == eNetMsgPlayerSysGetPlayerRiceInfo) {
                this -> checkTimeIsUp();
            }
		}
        if (unMsgType == eNetMsgTypeSend) {
            if (unMsgCode == eNetMsgReceiveRice) {
                this->setRiceNum(CPlayerInfoMan::sharedInstance().getPlayerInfo().nPower);
            }
        }
	}
	return true;
}
void GameLayer_RiceBar::RiceFace(float td)
{
	iFaceType = CCRANDOM_0_1()*iFaceRend+1;

	animation = CCAnimation::create();
	CCString str;
	for (int i = 1; i <=3; i++)  
	{
		str.initWithFormat("./CocoStudioResources/Rice/phiz_1%d.png",i);	
		animation->addSpriteFrameWithFileName(str.getCString()); 
	}
	animation->setDelayPerUnit(0.5f);
	animation->setLoops(1);
	if(iFaceType == 1)
		pFace0->runAction(CCRepeat::create(CCAnimate::create(animation),1.0f));
	else if(iFaceType==2)
		pFace1->runAction(CCRepeat::create(CCAnimate::create(animation),1.0f));
	else if(iFaceType==3)
		pFace2->runAction(CCRepeat::create(CCAnimate::create(animation),1.0f));
	else if(iFaceType==4)
		pFace3->runAction(CCRepeat::create(CCAnimate::create(animation),1.0f));
	else 
		pFace4->runAction(CCRepeat::create(CCAnimate::create(animation),1.0f));
}