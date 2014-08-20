//
//  GameLayer_SuperItem.cpp
//  OnceAgain
//
//  Created by mac on 14-3-25.
//
//

#include "GameLayer_SuperItem.h"
#include "GameLayer_Tag.h"
#include "GameItemManager.h"
#include "DialogManager.h"
#include "MsgDefine.h"
#include "NetPacket.h"
#include "CounterByImage.h"
#include "PlayerInfoManager.h"
#include "GameLayer_Alert.h"
#include "CsvStringData.h"

IMPLEMENT_DLG_ID(GameLayer_SuperItem,SuperItem_Tag);
GameLayer_SuperItem::~GameLayer_SuperItem()
{
    GUIReader::shareReader()->purgeGUIReader();
    DictionaryHelper::shareHelper()->purgeDictionaryHelper();
    ActionManager::shareManager()->purgeActionManager();
}

// CCScene* GameLayer_SuperItem::scene(CCRenderTexture *spr, bool isFlip)
// {
//     
//     
//     // 'scene' is an autorelease object
//     CCScene *scene = CCScene::create();
//     
//     CCSize size = CCDirector::sharedDirector()->getWinSize();
//     CCSprite *_spr = CCSprite::createWithTexture(spr->getSprite()->getTexture());
//     _spr->setPosition(ccp(size.width/2, size.height/2));
//     _spr->setFlipY(isFlip);
//     _spr->setColor(ccGRAY);
//     scene->addChild(_spr);
//     // 'layer' is an autorelease object
//     GameLayer_SuperItem *layer = GameLayer_SuperItem::create();
//     //    layer->setPosition(ccp(size.width/2, size.height/2));
//     // add layer as a child to scene
//     scene->addChild(layer);
//     
//     // return the scene
//     return scene;
// }
bool GameLayer_SuperItem::onPackageFilter(void *pDataPkg) {
	CResponsePacket* pPkt = (CResponsePacket*)pDataPkg;
	unsigned int unMsgType = pPkt->getMsgType();
	unsigned int unMsgCode = pPkt->getMsgCode();
	//网络数据传输完成
	if (pPkt->getDataState() == eNetMsgDataStateComplete)
	{
		 if (unMsgType == eNetMsgTypeItemSys && unMsgCode == eNetMsgItemSysBuy)
		 {
			 CSJson::Value root ;
			 if(!CJsonHelper::getJsonFromString(pPkt->getContent().c_str(),root))
				 return true;
			 CSJson::Value& val = root[0];
			 //if(root.isArray())
			//	return false;
			 SClientItemData* itemData = CItemMan::sharedInstance().getSuperItem(val["propsid"].asInt());
			 if(itemData&&itemData->pData)
			 {
				 if (itemData->pData->ItemType == eItemTypeSuper)
				 {
					 if (m_pfnSelector && m_pListener) {
						 (m_pListener->*m_pfnSelector)(this);
					 }
					 _close();
				 }
			 }
			 else
			 {
				 closeBtnCallback(NULL);
			 }
		 }
	}
	return true;
}
bool GameLayer_SuperItem::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    //系统设置界面.
    superItem = UILayer::create();
    auto layout = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("./CocoStudioResources/SuperItem.json"));
    superItem->addWidget(layout);
    //    sysSet->setVisible(true);
    this->addChild(superItem, 0, 101);
    
    //设置背景颜色.
    UIPanel* taskPanel = dynamic_cast<UIPanel*>(superItem->getWidgetByName("Panel"));
    taskPanel->setBackGroundColor(ccBLACK);
    taskPanel->setBackGroundColorOpacity(150);
	 taskPanel->setTouchEnable(true);
    //确定按钮
    UIButton* sureBtn = dynamic_cast<UIButton*>(superItem->getWidgetByName("SureBtn"));
    sureBtn->setTouchEnable(true);
    sureBtn->addReleaseEvent(this, coco_releaseselector(GameLayer_SuperItem::sureBtnCallback));
    sureBtn->setPressedActionEnabled(true);
    //关闭按钮.
    UIButton* cancelBtn = dynamic_cast<UIButton*>(superItem->getWidgetByName("CancelBtn"));
    cancelBtn->addReleaseEvent(this, coco_releaseselector(GameLayer_SuperItem::closeBtnCallback));
    cancelBtn->setPressedActionEnabled(true);
    this->setVisible(true);

	setTouchPriority(kCCMenuHandlerPriority - 1);

	VEC_NUMFILENAME vecNumFileName;
// 	for (int i = 0; i < 10; ++i)
// 	{
// 		CCString str;
// 		str.initWithFormat("common/num_1/common_num_%d.png",i);
// 		vecNumFileName.push_back(str.getCString());	
// 	}
	vecNumFileName.push_back("numberBox/whiteNumberZero.png");
	vecNumFileName.push_back("numberBox/whiteNumberOne.png");
	vecNumFileName.push_back("numberBox/whiteNumberTwo.png");
	vecNumFileName.push_back("numberBox/whiteNumberThree.png");
	vecNumFileName.push_back("numberBox/whiteNumberFour.png");
	vecNumFileName.push_back("numberBox/whiteNumberFive.png");
	vecNumFileName.push_back("numberBox/whiteNumberSix.png");
	vecNumFileName.push_back("numberBox/whiteNumberSeven.png");
	vecNumFileName.push_back("numberBox/whiteNumberEight.png");
	vecNumFileName.push_back("numberBox/whiteNumberNine.png");
	CCounterImage* pNum= CCounterImage::create(vecNumFileName,"numberBox/whiteNumberComma.png",0,false);
	//mpCounterImage->setPosition(ccp(120, 0));
	pNum->setCellNumberWidth(42);
	pNum->setNumber(0);
	pNum->setTag(8);
	pNum->setScale(0.4f);
    UIImageView* pUiImg = ((UIImageView*)superItem->getWidgetByName("buy_num"));
    pUiImg->setVisible(false);
    sureBtn->getRenderer()->addChild(pNum);
    pNum->setPosition(pUiImg->getPosition());
	//superItem->getWidgetByName("buy_num")->getRenderer()->addChild(pNum);
    return true;
}

void GameLayer_SuperItem::setVisible(bool visible)
{
    CCLayer::setVisible(visible);
   // UIPanel* panel = dynamic_cast<UIPanel*>(superItem->getWidgetByName("Panel"));
   // panel->setTouchEnable(visible);
}

void GameLayer_SuperItem::sureBtnCallback(cocos2d::CCObject *pSender)
{
    sItemData* pData = CItemMan::sharedInstance().getChgTempData(mnItemID);
    int hMoney = CPlayerInfoMan::sharedInstance().getPlayerInfo().nMoney;
    int nMoney = pData->CurrencyValue;
    if (nMoney > hMoney) {
        GameLayer_Alert *alertUl = GameLayer_Alert::creatWithOnlySure(Type_OnlySure);
        alertUl->setText(GET_STRING_CSV(1010000021));
        this->addChild(alertUl, 10);
    }
    else {
        CCObject *p;
        requestItems(p);
    }
	//this->removeFromParent(); 
}
void GameLayer_SuperItem::requestItems(cocos2d::CCObject *p) {
    if(mnItemID)
        CItemMan::sharedInstance().RequestBuyItem(mnItemID);

}
void GameLayer_SuperItem::closeBtnCallback(CCObject* pSender)
{
    if (m_pfnSelector && m_pListener) {
        UIButton* sureBtn = dynamic_cast<UIButton*>(superItem->getWidgetByName("SureBtn"));
        (m_pListener->*m_pfnSelectorClose)(this);
    }
    //this->removeFromParent();
	_close();
}
void GameLayer_SuperItem::_close()
{
	ReleaseDlg(GameLayer_SuperItem);
}
void GameLayer_SuperItem::setSureCallbackFunc(CCObject* target, SEL_CallFuncO pCallfuncOk, SEL_CallFuncO pCallfuncCancel)
{
    this->m_pListener = target;
    this->m_pfnSelector = pCallfuncOk;
	this->m_pfnSelectorClose = pCallfuncCancel;
}
void GameLayer_SuperItem::setSureBtnTag(int tag)
{
    UIButton* sureBtn = dynamic_cast<UIButton*>(superItem->getWidgetByName("SureBtn"));
    sureBtn->setTag(tag);
}
void GameLayer_SuperItem::setItemInfo(const char *str)
{
    UILabel* label = dynamic_cast<UILabel*>(superItem->getWidgetByName("ItemInfo"));
    label->setText(str);
}
void GameLayer_SuperItem::setItem(int nItemId)
{
	mnItemID = nItemId;
	UIImageView* img = dynamic_cast<UIImageView*>(superItem->getWidgetByName("ItemImg"));
	CCString str;
	str.initWithFormat("CocoStudioResources/GameItem/%d.png",nItemId);
	img->setTexture(str.getCString());
	sItemData* pData = CItemMan::sharedInstance().getChgTempData(nItemId);
	if(pData == NULL)
		return;
	setItemInfo(pData->ItemDetail.c_str());
	((CCounterImage*)superItem->getWidgetByName("SureBtn")->getRenderer()->getChildByTag(8))->setNumber(pData->CurrencyValue);
	 img = dynamic_cast<UIImageView*>(superItem->getWidgetByName("guobi"));
	img->setTexture("CocoStudioResources/GoldImg.png");
	if (pData->CurrencyId == 5)
	{
		img->setTexture("CocoStudioResources/DiamondImg.png");
	}
}