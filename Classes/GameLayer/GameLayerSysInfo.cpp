//
//  GameLayerSysInfo.cpp
//  OnceAgain
//
//  Created by mac on 14-4-24.
//
//

#include "GameLayerSysInfo.h"
#include "SysInfoCell.h"
#include "InfoSysManager.h"
#include "CsvStringData.h"
#include "PlayerInfoManager.h"
#include "GameLayer_Tag.h"
#include "NetPacket.h"
#include "MsgDefine.h"
#include "GameLayer_Alert.h"
#include "GameInfoManager.h"
#include "Scene_GameItem.h"
#include "GameShare_Global.h"
#include "DialogManager.h"
IMPLEMENT_DLG_ID(GameLayerSysInfo,SysInfo);
GameLayerSysInfo::GameLayerSysInfo()
{
    showScrollView = NULL;
    ul = NULL;
    layer = NULL;
    selectTag = -1;
}
GameLayerSysInfo::~GameLayerSysInfo()
{
    GUIReader::shareReader()->purgeGUIReader();
	DictionaryHelper::shareHelper()->purgeDictionaryHelper();
	ActionManager::shareManager()->purgeActionManager();
}

void GameLayerSysInfo::onEnter()
{
    CCLayer::onEnter();
 
    this->reloadView();
}
void GameLayerSysInfo::reloadView()
{
    if (showScrollView != NULL) {
        showScrollView->removeFromParent();
        showScrollView = NULL;
    }
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(GameLayerSysInfo::getNewsList), kGetSysInfo, NULL);
	   CInfoSysManager::sharedInstance().RequestGetInfo();
}
bool GameLayerSysInfo::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    //获取窗口大小
    //获取窗口大小
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    ul = UILayer::create();
    auto myLayout = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("./CocoStudioResources/SysInfo.json"));
    ul->addWidget(myLayout);
    ul->setContentSize(visibleSize);
    this->addChild(ul, 1, 100);
    
    UIPanel* panel = dynamic_cast<UIPanel*>(ul->getWidgetByName("Panel"));
    panel->setBackGroundColor(ccBLACK);
    panel->setBackGroundColorOpacity(150);
    panel->setTouchEnable(true);
    
    //关闭按钮
    UIButton* sysCloseBtn = dynamic_cast<UIButton*>(ul->getWidgetByName("Button_3368"));
    sysCloseBtn->addReleaseEvent(this, coco_releaseselector(GameLayerSysInfo::closeSysSetCallback));
    sysCloseBtn->setPressedActionEnabled(true);
    sysCloseBtn->setTouchEnable(true);
    
    return true;
}
void GameLayerSysInfo::getNewsList(CCObject* pSender)
{
	//获取窗口大小
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	UIImageView* bgImg = dynamic_cast<UIImageView*>(ul->getWidgetByName("Bg1"));
	showScrollView = CCScrollviewSimple::create(CCSizeMake(bgImg->getContentSize().width, 545));
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


	//获取消息列表.
	VEC_INFOSYS infoSys = CInfoSysManager::sharedInstance().getInfoSys();
	//创建一个层
	layer=UILayer::create();
	for (int i=0; i<infoSys.size(); i++) {
		SysInfoCell* cell = SysInfoCell::create();
		cell->setPosition(ccp((showScrollView->getViewSize().width-cell->getContentSize().width)/2, (infoSys.size()-1-i)*105+5));
		layer->addChild(cell);
		cell->setTag(i);
		cell->setAvatar(infoSys[i].avatarImg.c_str());
		cell->setName(infoSys[i].name.c_str());
		cell->addSendCallbackFunc(NULL, NULL);
		if (infoSys[i].type == InfoRiceType) {

			cell->setType(InfoTypeSendRice);
			cell->addSendCallbackFunc(this, coco_releaseselector(GameLayerSysInfo::receiveRiceCallback));
			cell->setInfo(GET_STRING_CSV(1010000026),24);
		}
		if (infoSys[i].type == InfoSendPkType) {
			cell->setType(InfoTypeChallenge);
			CCString str;
			sGameInfoData* data = CGameInfoMan::sharedInstance().getChgTempData(infoSys[i].gameType);
			str.initWithFormat(GET_STRING_CSV(1010000030),data->gameName.c_str(),infoSys[i].name.c_str());
			cell->setGameType(infoSys[i].gameType);
			cell->addSendCallbackFunc(this, coco_releaseselector(GameLayerSysInfo::gotoPkList));
			cell->setInfo(str.getCString(),18);
		}
		if (infoSys[i].type == InfoRecPkType) {
			cell->setType(InfoTypeChallenge);
			CCString str;
			sGameInfoData* data = CGameInfoMan::sharedInstance().getChgTempData(infoSys[i].gameType);
			str.initWithFormat(GET_STRING_CSV(1010000029),infoSys[i].name.c_str(),data->gameName.c_str());
			cell->setGameType(infoSys[i].gameType);
			cell->addSendCallbackFunc(this, coco_releaseselector(GameLayerSysInfo::gotoPkList));
			cell->setInfo(str.getCString(),18);
		}

	}
	showScrollView->setPosition(ccp(showScrollView->getPositionX(), showScrollView->getPositionY()-10));
	showScrollView->setContainer(layer);
	showScrollView->setContentSize(CCSizeMake(visibleSize.width, infoSys.size()*105+5));
	showScrollView->setContentOffset(ccp(0, showScrollView->getViewSize().height-showScrollView->getContentSize().height));
	bgImg->addRenderer(showScrollView,10);
}
void GameLayerSysInfo::gotoPkList(cocos2d::CCObject *pSender)
{
    UIButton* button = (UIButton*)pSender;
    SysInfoCell* cell = (SysInfoCell*)layer->getChildByTag(button->getTag());
    this->removeFromParent();
    GameShare_Global::shareGlobal()->gameType = (e_GameType)cell->getGameType();
//    CCScene *scene_GameItem = Scene_GameItem::scene();

    CCScene *scene = CCScene::create();
    Scene_GameItem* layer = GetDlgPtr(Scene_GameItem);
    scene->addChild(layer);
    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.4, scene));
    layer->showRankList();
}
void GameLayerSysInfo::receiveRiceCallback(cocos2d::CCObject *pSender)
{
    UIButton* button = (UIButton*)pSender;
    VEC_INFOSYS infoSys = CInfoSysManager::sharedInstance().getInfoSys();
    selectTag = button->getTag();
    CPlayerInfoMan::sharedInstance().RequestReceiverice(infoSys[button->getTag()].infoId);
}
void GameLayerSysInfo::closeSysSetCallback(cocos2d::CCObject *pSender)
{
    CCNotificationCenter::sharedNotificationCenter()->postNotification(kGetSysNum, NULL);
    this->removeFromParent();
}
void GameLayerSysInfo::scrollViewDidZoom(CCScrollviewSimple* view){
    
    //        CCLOG("scrollViewDidZoom");
    
}
void GameLayerSysInfo::scrollViewDidScroll(CCScrollviewSimple* view){
    
    
    //    CCLOG("scrollViewDidScroll");
}

bool GameLayerSysInfo::onPackageFilter(void *pDataPkg) {
	CResponsePacket* pPkt = (CResponsePacket*)pDataPkg;
	unsigned int unMsgType = pPkt->getMsgType();
	unsigned int unMsgCode = pPkt->getMsgCode();
	//网络数据传输完成
	if (pPkt->getDataState() == eNetMsgDataStateComplete)
	{
        if (unMsgType == eNetMsgTypeSend) {
            if (unMsgCode == eNetMsgReceiveRice) {
              //  GameLayer_Alert *alertUl = GameLayer_Alert::creatWithOnlySure(Type_OnlySure);
              //  alertUl->setText(GET_STRING_CSV(1010000027));
               // this->getParent()->addChild(alertUl);
                VEC_INFOSYS &infoSys = CInfoSysManager::sharedInstance().getInfoSys();
                VEC_INFOSYS::iterator itr = infoSys.begin();
                for (int i=0; i<infoSys.size(); i++) {
                    if (i == selectTag) {
                        infoSys.erase(itr);
                        this->reloadView();
//                        this->removeFromParent();
                        break;
                    }
                    itr++;
                }

            }
        }
		
	}
	return true;
}