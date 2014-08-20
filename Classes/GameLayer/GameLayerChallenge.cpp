//
//  GameLayerChallenge.cpp
//  OnceAgain
//
//  Created by mac on 14-4-25.
//
//

#include "GameLayerChallenge.h"
#include "ChallengeCell.h"
#include "ChallengeCell2.h"
#include "PkSysManager.h"
#include "GameLayer_Tag.h"
#include "NetPacket.h"
#include "MsgDefine.h"
#include "GameLayer_Alert.h"
#include "GameShare_Global.h"
#include "GameInfoManager.h"
IMPLEMENT_DLG_ID(GameLayerChallenge,GameChallenge);

VEC_SPKINFO sendPkList;
VEC_SPKINFO receivePkList;
GameLayerChallenge::GameLayerChallenge()
{
    showScrollView = NULL;
    proposeBtn1 = NULL;
    proposeBtn2 = NULL;
    reciveBtn1 = NULL;
    reciveBtn2 = NULL;
    layerSend = NULL;
    layerReceive = NULL;
    ul = NULL;
}
GameLayerChallenge::~GameLayerChallenge()
{
    GUIReader::shareReader()->purgeGUIReader();
	DictionaryHelper::shareHelper()->purgeDictionaryHelper();
	ActionManager::shareManager()->purgeActionManager();
    
    CC_SAFE_RELEASE(layerSend);
    CC_SAFE_RELEASE(layerReceive);
}

void GameLayerChallenge::onEnter()
{
    CCLayer::onEnter();
    
    //获取窗口大小
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    if (showScrollView) {
        showScrollView->removeFromParent();
        showScrollView = NULL;
    }
    
    sGameInfoData* gameInfo = CGameInfoMan::sharedInstance().getChgTempData(GameShare_Global::shareGlobal()->gameType);
    UILabel* nameLabel = dynamic_cast<UILabel*>(ul->getWidgetByName("Name"));
    nameLabel->setText(gameInfo->gameName.c_str());
    
    UIImageView* bgImg = dynamic_cast<UIImageView*>(ul->getWidgetByName("Bg1"));
    
    
    
    showScrollView = CCScrollviewSimple::create(CCSizeMake(bgImg->getContentSize().width, 460));
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
    
    
    //创建一个层
    sendPkList = CPkSysManager::sharedInstance().getSendPk();
    receivePkList = CPkSysManager::sharedInstance().getReceivePk();
    layerReceive=UILayer::create();
    layerReceive->retain();
    for (int i=0; i<receivePkList.size(); i++) {
        ChallengeCell* cell = ChallengeCell::create();
        cell->setTag(i);
        cell->setName(receivePkList[i].pkName.c_str());
        cell->setTime(receivePkList[i].time);
        cell->addSendCallbackFunc(this, coco_releaseselector(GameLayerChallenge::battleBtnCallback));
        cell->setAvatarImg(receivePkList[i].avatarUrl.c_str());
        cell->setPosition(ccp((showScrollView->getViewSize().width-cell->getContentSize().width)/2, (receivePkList.size()-1-i)*105+5));
        layerReceive->addChild(cell);
        
        //        cell->addSendCallbackFunc(NULL, NULL);
    }
    layerSend=UILayer::create();
    layerSend->retain();
    for (int i=0; i<sendPkList.size(); i++) {
        ChallengeCell2* cell = ChallengeCell2::create();
        cell->setTag(i);
        cell->setName(sendPkList[i].pkName.c_str());
        cell->setScore(sendPkList[i].score);
        cell->setTime(sendPkList[i].time);
        cell->setAvatarImg(sendPkList[i].avatarUrl.c_str());
        cell->setPosition(ccp((showScrollView->getViewSize().width-cell->getContentSize().width)/2, (sendPkList.size()-1-i)*110+5));
        layerSend->addChild(cell);
    }
    
    showScrollView->setPosition(ccp(showScrollView->getPositionX(), showScrollView->getPositionY()-45));
    showScrollView->setContainer(layerSend);
    showScrollView->setContentSize(CCSizeMake(visibleSize.width, sendPkList.size()*110+5));
    showScrollView->setContentOffset(ccp(0, showScrollView->getViewSize().height-showScrollView->getContentSize().height));
    bgImg->addRenderer(showScrollView,10);
    

}

bool GameLayerChallenge::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    
    //获取窗口大小
    //获取窗口大小
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    ul = UILayer::create();
    auto myLayout = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("./CocoStudioResources/Challenge.json"));
    ul->addWidget(myLayout);
    ul->setContentSize(visibleSize);
    this->addChild(ul, 1, 100);
    
    UIPanel* panel = dynamic_cast<UIPanel*>(ul->getWidgetByName("Panel"));
    panel->setBackGroundColor(ccBLACK);
    panel->setBackGroundColorOpacity(150);
    panel->setTouchEnable(true);
    
    //关闭按钮
    UIButton* sysCloseBtn = dynamic_cast<UIButton*>(ul->getWidgetByName("Close"));
    sysCloseBtn->addReleaseEvent(this, coco_releaseselector(GameLayerChallenge::closeSysSetCallback));
    sysCloseBtn->setPressedActionEnabled(true);
    sysCloseBtn->setTouchEnable(true);
   
    proposeBtn1 = dynamic_cast<UIButton*>(ul->getWidgetByName("Btn2"));
    proposeBtn1->setTouchEnable(false);
    proposeBtn2 = dynamic_cast<UIButton*>(ul->getWidgetByName("Btn3"));
    proposeBtn2->setTouchEnable(true);
    proposeBtn2->setPressedActionEnabled(true);
    proposeBtn2->addReleaseEvent(this, coco_releaseselector(GameLayerChallenge::btnCallback));
    
    reciveBtn1 = dynamic_cast<UIButton*>(ul->getWidgetByName("Btn1"));
    reciveBtn1->setTouchEnable(true);
    reciveBtn1->setPressedActionEnabled(true);
    reciveBtn1->addReleaseEvent(this, coco_releaseselector(GameLayerChallenge::btnCallback));
    reciveBtn2 = dynamic_cast<UIButton*>(ul->getWidgetByName("Btn4"));
    reciveBtn2->setTouchEnable(false);
    
    return true;
}

void GameLayerChallenge::btnCallback(cocos2d::CCObject *pSender)
{
    
    if (pSender->isEqual(reciveBtn1)) {
        this->setState(0);
    }
    if (pSender->isEqual(proposeBtn2)) {
        this->setState(1);
    }
}
void GameLayerChallenge::setState(int type)
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    if (type == 0) {
        reciveBtn1->setVisible(false);
        reciveBtn1->setTouchEnable(false);
        reciveBtn2->setVisible(true);
        reciveBtn2->setTouchEnable(false);
        proposeBtn1->setTouchEnable(false);
        proposeBtn1->setVisible(false);
        proposeBtn2->setVisible(true);
        proposeBtn2->setTouchEnable(true);
        if (layerReceive && layerSend) {
            layerSend->removeFromParent();
            showScrollView->setContainer(layerReceive);
            showScrollView->setContentSize(CCSizeMake(visibleSize.width, 105*receivePkList.size()+5));
            showScrollView->setContentOffset(ccp(0, showScrollView->getViewSize().height-showScrollView->getContentSize().height));
        }

    }
    if (type == 1) {
        reciveBtn1->setVisible(true);
        reciveBtn1->setTouchEnable(true);
        reciveBtn2->setVisible(false);
        reciveBtn2->setTouchEnable(false);
        proposeBtn1->setTouchEnable(false);
        proposeBtn1->setVisible(true);
        proposeBtn2->setVisible(false);
        proposeBtn2->setTouchEnable(false);
        if (layerReceive && layerSend) {
            layerReceive->removeFromParent();
            showScrollView->setContainer(layerSend);
            showScrollView->setContentSize(CCSizeMake(visibleSize.width, 110*sendPkList.size()+5));
            showScrollView->setContentOffset(ccp(0, showScrollView->getViewSize().height-showScrollView->getContentSize().height));
        }

    }
}
void GameLayerChallenge::closeSysSetCallback(cocos2d::CCObject *pSender)
{
    this->removeFromParent();
}
void GameLayerChallenge::addSureCallbackFunc(cocos2d::CCObject *target, SEL_ReleaseEvent callfun)
{
    this->m_pListener = target;
    this->m_pfnSelector = callfun;
}
void GameLayerChallenge::battleBtnCallback(cocos2d::CCObject *pSender)
{
    UIWidget* btn = (UIWidget*)pSender;
    
    CPkSysManager::sharedInstance().pkType = PkTypeReceive;
    CPkSysManager::sharedInstance().pkId = receivePkList[btn->getTag()].pkId;
    CPkSysManager::sharedInstance().playerName = receivePkList[btn->getTag()].pkName;
    CPkSysManager::sharedInstance().playerUrl = receivePkList[btn->getTag()].avatarUrl;
    if (m_pListener && m_pfnSelector)
    {
        (m_pListener->*m_pfnSelector)(this);
    }
    this->removeFromParent();
}
void GameLayerChallenge::scrollViewDidZoom(CCScrollviewSimple* view){
    
//        CCLOG("scrollViewDidZoom");
    
}
void GameLayerChallenge::scrollViewDidScroll(CCScrollviewSimple* view){
    
    
    //    CCLOG("scrollViewDidScroll");
}
bool GameLayerChallenge::onPackageFilter(void *pDataPkg) {
	CResponsePacket* pPkt = (CResponsePacket*)pDataPkg;
	unsigned int unMsgType = pPkt->getMsgType();
	unsigned int unMsgCode = pPkt->getMsgCode();
	//网络数据传输完成
	if (pPkt->getDataState() == eNetMsgDataStateComplete)
	{
        if (unMsgType == eNetMsgTypeMsgSys) {
            if (unMsgCode == eNetMsgGetBePkInfo) {

            }
        }
		
	}
	return true;
}