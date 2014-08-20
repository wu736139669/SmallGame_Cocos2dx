//
//  GameLayerInvite.cpp
//  OnceAgain
//
//  Created by mac on 14-5-6.
//
//

#include "GameLayerInvite.h"
#include "StringUtil.h"
#include "InviteCell.h"
#include "FriendManager.h"
#include "GameLayer_Alert.h"
#include "CsvStringData.h"
#include "InfoSysManager.h"
#include "PlayerInfoManager.h"
#include "GameLayer_Tag.h"
#include "NetPacket.h"
#include "DialogManager.h"
#include "GameItemManager.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#include "JudgeNetEnvironment.h"
#include "QQInterface.h"
#include "SinaInterface.h"

#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#endif

IMPLEMENT_DLG_ID(GameLayerInvite,GameLayerInvite_tag);
GameLayerInvite::GameLayerInvite():showScrollView(NULL)
{
    
}
GameLayerInvite::~GameLayerInvite()
{
//    GUIReader::shareReader()->purgeGUIReader();
//	DictionaryHelper::shareHelper()->purgeDictionaryHelper();
//	ActionManager::shareManager()->purgeActionManager();
    
}
bool GameLayerInvite::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    //获取窗口大小
  
    ul = UILayer::create();
    auto myLayout = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("./CocoStudioResources/InviteFriend.json"));
    ul->addWidget(myLayout);
    this->addChild(ul, 0, 100);
    //背景
    UIPanel* panel = dynamic_cast<UIPanel*>(ul->getWidgetByName("Panel"));
    panel->setBackGroundColor(ccBLACK);
    panel->setBackGroundColorOpacity(150);
    panel->setTouchEnable(true);
    
    //关闭按钮
    UIButton* closeBtn = dynamic_cast<UIButton*>(ul->getWidgetByName("Close"));
    closeBtn->addReleaseEvent(this, coco_releaseselector(GameLayerInvite::closeCallback));
    closeBtn->setPressedActionEnabled(true);
    closeBtn->setTouchEnable(true);
    
    UIImageView *title = dynamic_cast<UIImageView*>(ul -> getWidgetByName("Label"));
    
    for (int i=0; i<5; i++) {
        CCSprite* starSprite = CCSprite::create("./CocoStudioResources/ItemStrengthern/EffectStar.png");
        CCSequence *seque = CCSequence::create(CCFadeTo::create(0.2, 150),CCFadeTo::create(0.3, 255),NULL);
        CCActionInterval* ccScale = CCSequence::create(CCScaleTo::create(0.2, 0.3), CCScaleTo::create(0.3, 0.8), NULL);
        CCActionInterval *spawn = CCSpawn::create(seque, ccScale, NULL);
        
        starSprite->runAction(CCRepeatForever::create(spawn));
        starSprite->setPosition(title->getPosition());
        title->addRenderer(starSprite, 10);
        switch (i) {
            case 0:
                starSprite->setPosition(ccp(-110, 10));
                break;
            case 1:
                starSprite->setPosition(ccp(0, 60));
                break;
            case 2:
                starSprite->setPosition(ccp(130, -30));
                break;
            case 3:
                starSprite->setPosition(ccp(20, -20));
                break;
            case 4:
                starSprite->setPosition(ccp(-40, -80));
                break;
                
            default:
                break;
        }
        
        
    }
    //creatScrollView();
    scheduleUpdate();
    return true;
}
void GameLayerInvite::onEnter()
{
    GameLayer_Base::onEnter();
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    if (CPlayerInfoMan::sharedInstance().getLognFirst()) {
        isGetFriendList = true;
        SinaInterface::shareInstant()->getFriend();
        CPlayerInfoMan::sharedInstance().setLognFirst(false);
    }
    else {
        CInfoSysManager::sharedInstance().RequestFriendListFromSql();
    }

#elif CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	CInfoSysManager::sharedInstance().RequestFriendListFromSql();
#endif
}
bool GameLayerInvite::onPackageFilter(void *pDataPkg) {
	CResponsePacket* pPkt = (CResponsePacket*)pDataPkg;
	unsigned int unMsgType = pPkt->getMsgType();
	unsigned int unMsgCode = pPkt->getMsgCode();
	//网络数据传输完成
	if (pPkt->getDataState() == eNetMsgDataStateComplete)
	{
        if (unMsgType == eNetMsgTypeFriendSys && unMsgCode == eNetMsgFriendSysGetAll) {
            creatScrollView();
        }
        if (unMsgType ==  eNetMsgTypeFriendSys && unMsgCode == eNetMsgFriendSysSetFriend) {
            CInfoSysManager::sharedInstance().RequestFriendListFromSql();
        }
		
	}
	return true;
}
void GameLayerInvite::closeCallback(cocos2d::CCObject *pSender)
{
//    UIImageView* bgImg = dynamic_cast<UIImageView*>(ul->getWidgetByName("Bg1"));
//    bgImg -> removeAllChildrenAndCleanUp(true);
//    bgImg->getRenderer()->removeChildByTag(11, true);
//    this->removeFromParent();
    ReleaseDlg(GameLayerInvite);
}

void GameLayerInvite::refreshCallBack(cocos2d::CCObject *p) {
    creatScrollView();
}

void GameLayerInvite::creatScrollView() {
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    UIImageView* bgImg = dynamic_cast<UIImageView*>(ul->getWidgetByName("Bg1"));
    bgImg -> removeAllChildrenAndCleanUp(true);
    
    showScrollView = CCScrollviewSimple::create(CCSizeMake(bgImg->getContentSize().width, 640));
    showScrollView->ignoreAnchorPointForPosition(false);
    showScrollView->setAnchorPoint(ccp(0.5, 0.5));
    
    //false自己写touch事件
    showScrollView->setTouchEnabled(true);
    showScrollView->setDelegate(this);
    
    //滚动方向
    showScrollView->setDirection(kCCScrollViewDirectionVertical);
    
    showScrollView->setBounceable(true);
    
    //获取消息列表.
    VEC_GAMERANK infoSys = CFriendManager::sharedInstance().getFriendListFromSql();
    //创建一个层
    UILayer *layer=UILayer::create();
    int hight = 0;
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	if (is3GEnabled()) {
		char str[80] = "./CocoStudioResources/InviteFriend/refreshfriends.png";
		UIButton *refreshBtn = UIButton::create();
		refreshBtn -> loadTextures(str, str, str);
		refreshBtn -> setAnchorPoint(ccp(0, 0));
		refreshBtn -> setPosition(ccp(5, 0));
		refreshBtn -> addReleaseEvent(this, coco_releaseselector(GameLayerInvite::refreshCallBack));
		refreshBtn -> setTouchEnable(true);
		layer -> addWidget(refreshBtn);
		hight = 90;
	}

#endif
   
   
    for (int i=0; i<infoSys.size(); i++) {
        InviteCell* cell = InviteCell::create();
        cell->setPosition(ccp((i%4)*135+5, (infoSys.size()/4-1-i/4)*160+5 + hight));
        cell -> setInfo(infoSys[i]);
        cell->setNode(this);
        layer->addChild(cell);
    }
    
    showScrollView->setPosition(ccp(showScrollView->getPositionX(), showScrollView->getPositionY()));
    showScrollView->setContainer(layer);
    showScrollView->setContentSize(CCSizeMake(visibleSize.width, (infoSys.size()/4)*160+5 + hight));
    showScrollView->setContentOffset(ccp(0, showScrollView->getViewSize().height-showScrollView->getContentSize().height));
    showScrollView->setTag(11);
    bgImg->addRenderer(showScrollView,10);
}

void GameLayerInvite::update(float delta)
{
	if(showScrollView == NULL)
		return;
	CCRect rc = showScrollView->getViewRect();
	CCNode *pContainer =showScrollView->getContainer();
    if(pContainer == NULL)
        return;
    //CCRect rc = CCRectMake(0, 0, showScrollView->getViewSize().width, showScrollView->getViewSize().height);
    
    CCArray* pArr = pContainer->getChildren();
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(pArr, pObj)
    {
        InviteCell* pCell = dynamic_cast<InviteCell*>(pObj);
        if (pCell) {
            CCPoint ptCellWorld = pCell->convertToWorldSpace(ccp(0,0));
            CCRect rc1 = CCRectMake(ptCellWorld.x ,ptCellWorld.y,
                                    pCell->getContentSize().width, pCell->getContentSize().height);
            if(rc.intersectsRect(rc1))
            {
               
                if (!pCell->getLoadImg()) {
                    CCLog("showScrollView：l:%02f,r:%02f,b:%02f,t:%02f",rc.getMinX(),rc.getMaxX(),rc.getMinY(),rc.getMaxY());
                    CCLog("InviteCell：l:%02f,r:%02f,b:%02f,t:%02f",rc1.getMinX(),rc1.getMaxX(),rc1.getMinY(),rc1.getMaxY());
                    pCell->setLoadImg(true);
                    pCell->requestIcon();
                }
            }
        }
    }
 	
}

