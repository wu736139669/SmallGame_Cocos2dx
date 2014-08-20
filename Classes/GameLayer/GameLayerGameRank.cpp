//
//  GameLayerGameRank.cpp
//  OnceAgain
//
//  Created by mac on 14-4-24.
//
//

#include "GameLayerGameRank.h"
#include "GameRankCell.h"
#include "FriendManager.h"
#include "GameShare_Global.h"
#include "GameLayerChallenge.h"
#include "PlayerInfoManager.h"
#include "PkSysManager.h"
#include "InfoSysManager.h"
#include "GameLayer_Tag.h"
#include "NetPacket.h"
#include "MsgDefine.h"
#include "GameLayer_Alert.h"
#include "DialogManager.h"
#include "GameInfoManager.h"
#include "NetHttpClient.h"
#include "XQDate.h"
#include "CsvStringData.h"
IMPLEMENT_DLG_ID(GameLayerGameRank,GameRank);
GameLayerGameRank::GameLayerGameRank()
{
    showScrollView = NULL;
    ul = NULL;
}
GameLayerGameRank::~GameLayerGameRank()
{
    GUIReader::shareReader()->purgeGUIReader();
	DictionaryHelper::shareHelper()->purgeDictionaryHelper();
	ActionManager::shareManager()->purgeActionManager();
}
void GameLayerGameRank::closeSysSetCallback(cocos2d::CCObject *pSender)
{
    this->removeFromParent();
}
void GameLayerGameRank::onEnter()
{
    CCLayer::onEnter();
    
    if (showScrollView) {
        showScrollView->removeFromParent();
        showScrollView=NULL;
    }
    CSJson::Value msg_body;
	msg_body["playerid"] = CSJson::Value(CPlayerInfoMan::sharedInstance().getPlayerInfo().nId);
    NetHttpClient::sharedInstance().XQsendHttpRequest(eNetMsgTypePlayerSys, eNetMsgPlayerSysGetPlayerPkInfoMation, &msg_body, this, coco_myevent(GameLayerGameRank::requestPkInfoCallBack));
    
}
void GameLayerGameRank::requestPkInfoCallBack(cocos2d::CCObject *p) {
    CCString str;
    str.initWithFormat("%d%d", eNetMsgTypePlayerSys, eNetMsgPlayerSysGetPlayerPkInfoMation);
    CSJson::Value root = XQDate::sharedInstance().GetDate(str.getCString());
    CSJson::Value &val = root[0];
    modelCount = val["playermedal"].asInt();
    sendCount = val["pksendcount"].asInt();
    pkrecvCount = val["pkrecvcount"].asInt();
    
    sGameInfoData* gameInfo = CGameInfoMan::sharedInstance().getChgTempData(GameShare_Global::shareGlobal()->gameType);
    UILabel* nameLabel = dynamic_cast<UILabel*>(ul->getWidgetByName("NameLabel"));
    nameLabel->setText(gameInfo->gameName.c_str());
    
    UIImageView* bgImg = dynamic_cast<UIImageView*>(ul->getWidgetByName("Image_18"));
    
    //获取窗口大小
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    showScrollView = CCScrollviewSimple::create(CCSizeMake(bgImg->getContentSize().width, 480));
    showScrollView->ignoreAnchorPointForPosition(false);
    showScrollView->setAnchorPoint(ccp(0, 0));
    
    //false自己写touch事件
    showScrollView->setTouchEnabled(true);
    showScrollView->setDelegate(this);
    
    //滚动方向
    showScrollView->setDirection(kCCScrollViewDirectionVertical);
    
    showScrollView->setBounceable(true);
    VEC_GAMERANK gameRank = CFriendManager::sharedInstance().getGameRankTmpData();
    //创建一个层
    UILayer *layer=UILayer::create();
    for (int i=0; i<gameRank.size(); i++) {
        GameRankCell* cell = GameRankCell::create();
        cell->setPosition(ccp((showScrollView->getViewSize().width-cell->getContentSize().width)/2, (gameRank.size()-1-i)*105+5));
        layer->addChild(cell,1);
        cell->setTag(i);
        cell->setRank(i+1);
        cell->setAvatarImg(gameRank[i].avatarUrl.c_str());
        cell->addSendCallbackFunc(this, coco_releaseselector(GameLayerGameRank::challengeBtnCallbackFunc));
        //如果是用户自己.
        if (gameRank[i].playerId == CPlayerInfoMan::sharedInstance().getPlayerInfo().nId) {
            cell->addSendCallbackFunc(NULL, NULL);
        }
        if (gameRank[i].canPk == false) {
            cell->addSendCallbackFunc(NULL, NULL);
        }
        cell->setScore(gameRank[i].score);
        cell->setName(gameRank[i].name.c_str());
    }
    showScrollView->setPosition(ccp(showScrollView->getPositionX() - 16, showScrollView->getPositionY() + 15));
    showScrollView->setContainer(layer);
    showScrollView->setContentSize(CCSizeMake(visibleSize.width, 105*gameRank.size()+5));
    showScrollView->setContentOffset(ccp(0, showScrollView->getViewSize().height-showScrollView->getContentSize().height));
    bgImg->addRenderer(showScrollView,10);
	

}
bool GameLayerGameRank::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    modelCount = 0;
    sendCount = 0;
    pkrecvCount = 0;
    
    //获取窗口大小
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
//    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    ul = UILayer::create();
    auto myLayout = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("./CocoStudioResources/GameRank.json"));
    ul->addWidget(myLayout);
    ul->setContentSize(visibleSize);
    this->addChild(ul, 1, 100);
    UIPanel* panel = dynamic_cast<UIPanel*>(ul->getWidgetByName("Panel"));
    panel->setBackGroundColor(ccBLACK);
    panel->setBackGroundColorOpacity(150);
    panel->setTouchEnable(true);
    
    //关闭按钮
    UIButton* sysCloseBtn = dynamic_cast<UIButton*>(ul->getWidgetByName("CloseBtn"));
    sysCloseBtn->addReleaseEvent(this, coco_releaseselector(GameLayerGameRank::closeSysSetCallback));
    sysCloseBtn->setPressedActionEnabled(true);
    sysCloseBtn->setTouchEnable(true);
    

    //查看好友对战列表
    UIButton* seeListBtn = dynamic_cast<UIButton*>(ul->getWidgetByName("SeeList"));
    seeListBtn->setPressedActionEnabled(true);
    seeListBtn->addReleaseEvent(this, coco_releaseselector(GameLayerGameRank::seeListCallback));
    
    return true;
}

void GameLayerGameRank::challengeBtnCallbackFunc(cocos2d::CCObject *pSender)
{
    if (modelCount - sendCount <= 0) {
        GameLayer_Alert *alertUl = GameLayer_Alert::creatWithOnlySure(Type_OnlySure);
        alertUl->setText(GET_STRING_CSV(1020000006));
  
        this->addChild(alertUl, 10);
        return;
    }
    VEC_GAMERANK gameRank = CFriendManager::sharedInstance().getGameRankTmpData();
    UIButton* btn = (UIButton*)pSender;
    CPkSysManager::sharedInstance().pkType = PkTypeSend;
    CPkSysManager::sharedInstance().playerId = gameRank[btn->getTag()].playerId;
    CPkSysManager::sharedInstance().playerName = gameRank[btn->getTag()].name;
    CPkSysManager::sharedInstance().playerUrl = gameRank[btn->getTag()].avatarUrl;
    if (m_pListener && m_pfnSelector)
    {
        (m_pListener->*m_pfnSelector)(this);
    }
    this->removeFromParent();
}
void GameLayerGameRank::seeListCallback(cocos2d::CCObject *pSender)
{
    CInfoSysManager::sharedInstance().RequestGetPkInfo();
    CInfoSysManager::sharedInstance().RequestGetBePkInfo();

//    this->addChild(layer);
}
void GameLayerGameRank::addSureCallbackFunc(cocos2d::CCObject *target, SEL_ReleaseEvent callfun)
{
    this->m_pListener = target;
    this->m_pfnSelector = callfun;
    
    
}
void GameLayerGameRank::scrollViewDidZoom(CCScrollviewSimple* view){
    
    //        CCLOG("scrollViewDidZoom");
    
}
void GameLayerGameRank::scrollViewDidScroll(CCScrollviewSimple* view){
    
    
    //    CCLOG("scrollViewDidScroll");
}

bool GameLayerGameRank::onPackageFilter(void *pDataPkg) {
	CResponsePacket* pPkt = (CResponsePacket*)pDataPkg;
	unsigned int unMsgType = pPkt->getMsgType();
	unsigned int unMsgCode = pPkt->getMsgCode();
	//网络数据传输完成
	if (pPkt->getDataState() == eNetMsgDataStateComplete)
	{
        if (unMsgType == eNetMsgTypeMsgSys) {
            if (unMsgCode == eNetMsgGetBePkInfo) {
                GameLayerChallenge* layer = GetDlgPtr(GameLayerChallenge);
                layer->setState(1);
                this->removeFromParent();
            }
        }
		
	}
	return true;
}

