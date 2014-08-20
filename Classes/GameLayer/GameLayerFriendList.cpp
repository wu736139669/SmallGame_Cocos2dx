//
//  GameLayerFriendList.cpp
//  OnceAgain
//
//  Created by mac on 14-4-16.
//
//

#include "GameLayerFriendList.h"
#include "FriendManager.h"
#include "PlayerInfoManager.h"
#include "GameLayer_Tag.h"
#include "NetPacket.h"
#include "MsgDefine.h"
#include "GameLayer_Alert.h"
#include "CsvStringData.h"
#include "TimeUtil.h"
#include "Constant.h"
#include "PlayerInfoAndFightLayer.h"
#include "ImageDownloader.h"
#include "GameShare_Msg.h"
#include "NetHttpClient.h"

#include "XQDate.h"

IMPLEMENT_DLG_ID(GameLayerFriendList,FirendList);

GameLayerFriendCell* nowCell;
GameLayerFriendList::GameLayerFriendList()
{
    showScrollView = NULL;
    sendId = -1;
    nowCell = NULL;
    layer = NULL;
}
GameLayerFriendList::~GameLayerFriendList()
{
    GUIReader::shareReader()->purgeGUIReader();
	DictionaryHelper::shareHelper()->purgeDictionaryHelper();
	ActionManager::shareManager()->purgeActionManager();
}

void GameLayerFriendList::onEnter()
{
    CCLayer::onEnter();
    
    if(showScrollView != NULL){
        showScrollView->removeFromParent();
        showScrollView = NULL;
    }
	//注册获得好友总分排行的通知.
//    CCDirector::sharedDirector()
    
    
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(GameLayerFriendList::getTop), kGetAllScoreRank, NULL);
	CFriendManager::sharedInstance().RequestGetAllRank();
}

void GameLayerFriendList::onExit(){
    this -> unscheduleAllSelectors();
	CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
    CCLayer::onExit();
}

bool GameLayerFriendList::init()
{
	if (!CCLayer::init()) {
        return false;
    }
    //获取窗口大小
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    ul = UILayer::create();
    
    auto myLayout = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("./CocoStudioResources/FriendScore.json"));
    ul->addWidget(myLayout);
    ul->setContentSize(visibleSize);
    this->addChild(ul);
    
    
    UIPanel* panel = dynamic_cast<UIPanel*>(ul->getWidgetByName("Panel"));
    panel->setBackGroundColor(ccBLACK);
    panel->setBackGroundColorOpacity(150);
    panel->setTouchEnable(true);
    
    //关闭按钮
    UIButton* sysCloseBtn = dynamic_cast<UIButton*>(ul->getWidgetByName("Close"));
    sysCloseBtn->addReleaseEvent(this, coco_releaseselector(GameLayerFriendList::closeSysSetCallback));
//    sysCloseBtn->setPressedActionEnabled(true);
    sysCloseBtn->setTouchEnable(true);
    //
    timeLabel = dynamic_cast<UILabel*>(ul -> getWidgetByName("TimeLabel"));
    
    UICheckBox *myBox = dynamic_cast<UICheckBox*>(ul -> getWidgetByName("IsShow"));
    myBox -> setSelectedState(!CCUserDefault::sharedUserDefault() -> getBoolForKey("WellShowFriend"));
    myBox -> addReleaseEvent(this, coco_releaseselector(GameLayerFriendList::checkBoxCallBack));
    
    return true;
}

void GameLayerFriendList::getTop(CCObject* pSender)
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	UIImageView* bgImg = dynamic_cast<UIImageView*>(ul->getWidgetByName("TableBg"));

	showScrollView = CCScrollviewSimple::create(CCSizeMake(bgImg->getContentSize().width, 525));
	showScrollView->ignoreAnchorPointForPosition(false);
	showScrollView->setAnchorPoint(ccp(0.5, 0.5));


	//false自己写touch事件
	showScrollView->setTouchEnabled(true);
	showScrollView->setDelegate(this);

	//滚动方向
	showScrollView->setDirection(kCCScrollViewDirectionVertical);

	showScrollView->setBounceable(true);
	//  slayer->setContentSize(CCSizeMake(visibleSize.width*3, visibleSize.height));
	//    showScrollView->setContentSize(CCSizeMake(visibleSize.width, 100));

	VEC_GAMERANK gameRank = CFriendManager::sharedInstance().getAllRankTmpData();

	layer=UILayer::create();
	for (int i=0; i<gameRank.size(); i++) {
		if (i==gameRank.size()) {
			UIButton* btn = UIButton::create();
			btn->setTextures("./CocoStudioResources/InviteFriendBtn.png", "./CocoStudioResources/InviteFriendBtn.png", "");
			btn->setAnchorPoint(ccp(0.0, 0.0));
			btn->setPosition(ccp((showScrollView->getViewSize().width-btn->getContentSize().width)/2, (gameRank.size()-i)*105+15));
			layer->addWidget(btn);
		}else
		{
			GameLayerFriendCell* cell = GameLayerFriendCell::create();
			cell->setPosition(ccp((showScrollView->getViewSize().width-cell->getContentSize().width)/2, (gameRank.size()-1-i)*105+5));
			cell->setTag(i);
			layer->addChild(cell);
			cell->setRank(i+1);
			cell->setAvatarImg(gameRank[i].avatarUrl.c_str());
			cell->setName(gameRank[i].name.c_str());
			cell->setScore(gameRank[i].score);
			if (gameRank[i].powernoticeexpiretime <= 0) {
				cell->setSendType(FriendSendTypeSend);

			}else{
				cell->setSendType(FriendSendTypeIsSend,gameRank[i].powernoticeexpiretime);
			}

			cell -> setPlayerId(gameRank[i].playerId);
			cell -> setInfoCallback(this, callfunc_selector(GameLayerFriendList::gotoUserInfo));
			if (gameRank[i].playerId == CPlayerInfoMan::sharedInstance().getPlayerInfo().nId) {
				mySelfCell = cell;
				cell->setSendType(FriendSendTypeSend);
				int tag = gameRank[i].playercanrecvpower == 1? 100:101;
				cell->addMySelfCallBack(this, coco_releaseselector(GameLayerFriendList::mySelfCellClickCallBack), tag);
			}
			else {
				cell->addSendCallbackFunc(this, coco_releaseselector(GameLayerFriendList::sendRiceCallback));

			}
		}

	}
	showScrollView->setPosition(ccp(showScrollView->getPositionX(), showScrollView->getPositionY()-10));
	showScrollView->setContainer(layer);
	showScrollView->setContentSize(CCSizeMake(visibleSize.width, (gameRank.size())*105+5));
	showScrollView->setContentOffset(ccp(0, showScrollView->getViewSize().height-showScrollView->getContentSize().height));
	bgImg->addRenderer(showScrollView,10);
    
    
    
    //获取更新时间并注册倒计时。
    CSJson::Value msg_body;
    NetHttpClient::sharedInstance().XQsendHttpRequest(eNetMsgTypeFriendSys, eNetMsgFriendSysGetTime, &msg_body, this, coco_myevent(GameLayerFriendList::timeBeginCount));

}
void GameLayerFriendList::timeBeginCount(cocos2d::CCObject *p) {
    CCString str;
    str.initWithFormat("%d%d",eNetMsgTypeFriendSys,eNetMsgFriendSysGetTime);
    CSJson::Value root = XQDate::sharedInstance().GetDate(str.getCString());
    for (int i = 0; i < root.size() ; i++) {
        CSJson::Value &val = root[i];
        TIME = val["timeout"].asInt();
    }
    int day = TIME/3600/24;
    int hour = TIME/3600%24;
    str.initWithFormat(GET_STRING_CSV(1020000004),day, hour);
    timeLabel -> setText(str.getCString());
}

void GameLayerFriendList::sendRiceCallback(cocos2d::CCObject *pSender)
{
    UIButton* cell = (UIButton*)pSender;
    int tag = cell->getTag();
    VEC_GAMERANK gameRank = CFriendManager::sharedInstance().getAllRankTmpData();
    CPlayerInfoMan::sharedInstance().RequestSendRice(gameRank[tag].playerId);
    sendId = tag;
}
void GameLayerFriendList::closeSysSetCallback(cocos2d::CCObject *pSender)
{
	CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
    this->removeFromParent();
}
void GameLayerFriendList::gotoUserInfo()
{
    auto *layer = PlayerInfoAndFightLayer::create();
    this->addChild(layer, 100);
}
void GameLayerFriendList::scrollViewDidZoom(CCScrollviewSimple* view){
    
//        CCLOG("scrollViewDidZoom");
    
}
void GameLayerFriendList::scrollViewDidScroll(CCScrollviewSimple* view){
    
    
//    CCLOG("scrollViewDidScroll");
}

void GameLayerFriendList::mySelfCellClickCallBack(CCObject *p) {
    int tag = ((UIButton*)p) -> getTag();
    tag = tag == 100 ? 101: 100;
    if (tag == 101) {
        GameLayer_Alert *alertUl = GameLayer_Alert::creatWithOnlySure();
        alertUl->setText(GET_STRING_CSV(1020000005));
        alertUl->setSureCallbackFunc(this, callfuncO_selector(GameLayerFriendList::alertCallBack));
        this->addChild(alertUl, 10);
    }
    else {
        mySelfCell -> changePicType(tag);
    }
}
void GameLayerFriendList::alertCallBack(cocos2d::CCObject *p) {
    mySelfCell -> changePicType(101);
}

bool GameLayerFriendList::onPackageFilter(void *pDataPkg) {
	CResponsePacket* pPkt = (CResponsePacket*)pDataPkg;
	unsigned int unMsgType = pPkt->getMsgType();
	unsigned int unMsgCode = pPkt->getMsgCode();
	//网络数据传输完成
	if (pPkt->getDataState() == eNetMsgDataStateComplete)
	{
        if (unMsgType == eNetMsgTypeSend) {
            if (unMsgCode == eNetMsgSendRice) {
               // GameLayer_Alert *alertUl = GameLayer_Alert::creatWithOnlySure(Type_OnlySure);
              //  alertUl->setText(GET_STRING_CSV(1010000028));
              //  this->getParent()->addChild(alertUl);
                VEC_GAMERANK& gameRank = CFriendManager::sharedInstance().getAllRankTmpData();
                gameRank[sendId].powernoticeexpiretime = RICESEND;
                GameLayerFriendCell* cell = ((GameLayerFriendCell*)layer->getChildByTag(sendId));
                if (cell) {
                    cell->setSendType(FriendSendTypeIsSend,gameRank[sendId].powernoticeexpiretime);
                }
            }
        }
	}
	return true;
}

void GameLayerFriendList::checkBoxCallBack(cocos2d::CCObject *p) {
    bool isChecked = ((UICheckBox*)p) -> getSelectedState();
    CCUserDefault::sharedUserDefault() -> setBoolForKey("WellShowFriend", isChecked);
}
