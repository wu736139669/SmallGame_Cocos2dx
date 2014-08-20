//
//  GameLayer_DiamondMarket.cpp
//  OnceAgain
//
//  Created by mac on 14-3-25.
//
//

#include "GameLayer_DiamondMarket.h"
#include "GameLayer_Alert.h"
#include "MoneyManager.h"
#include "CsvStringData.h"
#include "PlayerInfoManager.h"
#include "GameLayer_GoldMarket.h"
enum Buy_Tag
{
    Buy_0 = 1,
    Buy_1 = 2,
    Buy_2 = 3,
    Buy_3 = 4,
    Buy_4 = 5
};
GameLayer_DiamondMarket::~GameLayer_DiamondMarket()
{
    GUIReader::shareReader()->purgeGUIReader();
    DictionaryHelper::shareHelper()->purgeDictionaryHelper();
    ActionManager::shareManager()->purgeActionManager();
}


bool GameLayer_DiamondMarket::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    //系统设置界面.
    diamondMarket = UILayer::create();
    auto layout = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("./CocoStudioResources/DiamondMarket.json"));
    diamondMarket->addWidget(layout);
    //    sysSet->setVisible(true);
    this->addChild(diamondMarket, 0, 101);
    
    UIPanel* panel = dynamic_cast<UIPanel*>(diamondMarket->getWidgetByName("Panel"));
    panel->setBackGroundColor(ccBLACK);
    panel->setBackGroundColorOpacity(150);
    //关闭按钮
    UIButton* closeBtn = dynamic_cast<UIButton*>(diamondMarket->getWidgetByName("CloseBtn"));
    closeBtn->setTouchEnable(true);
    closeBtn->addReleaseEvent(this, coco_releaseselector(GameLayer_DiamondMarket::closeBtnCallback));
    closeBtn->setPressedActionEnabled(true);
    
    //购买按钮.
    UIButton* buyBtn_0 = dynamic_cast<UIButton*>(diamondMarket->getWidgetByName("BuyBtn_0"));
    buyBtn_0->setTag(Buy_0);
    buyBtn_0->setPressedActionEnabled(true);
    buyBtn_0->addReleaseEvent(this, coco_releaseselector(GameLayer_DiamondMarket::buyBtnCallback));
    UIButton* buyBtn_1 = dynamic_cast<UIButton*>(diamondMarket->getWidgetByName("BuyBtn_1"));
    buyBtn_1->setTag(Buy_1);
    buyBtn_1->setPressedActionEnabled(true);
    buyBtn_1->addReleaseEvent(this, coco_releaseselector(GameLayer_DiamondMarket::buyBtnCallback));
    UIButton* buyBtn_2 = dynamic_cast<UIButton*>(diamondMarket->getWidgetByName("BuyBtn_2"));
    buyBtn_2->setTag(Buy_2);
    buyBtn_2->setPressedActionEnabled(true);
    buyBtn_2->addReleaseEvent(this, coco_releaseselector(GameLayer_DiamondMarket::buyBtnCallback));
    UIButton* buyBtn_3 = dynamic_cast<UIButton*>(diamondMarket->getWidgetByName("BuyBtn_3"));
    buyBtn_3->setTag(Buy_3);
    buyBtn_3->setPressedActionEnabled(true);
    buyBtn_3->addReleaseEvent(this, coco_releaseselector(GameLayer_DiamondMarket::buyBtnCallback));
    //UIButton* buyBtn_4 = dynamic_cast<UIButton*>(diamondMarket->getWidgetByName("BuyBtn_4"));
    //buyBtn_4->setTag(Buy_4);
    //buyBtn_4->setPressedActionEnabled(true);
	this->setVisible(true);
    this->setValue();
    return true;
}

void GameLayer_DiamondMarket::setVisible(bool visible)
{
    CCLayer::setVisible(visible);
    UIPanel* dayLoginPanel = dynamic_cast<UIPanel*>(diamondMarket->getWidgetByName("Panel"));
    dayLoginPanel->setTouchEnable(visible);
}

void GameLayer_DiamondMarket::closeBtnCallback(cocos2d::CCObject *pSender)
{
    this->removeFromParent();
}

void GameLayer_DiamondMarket::setValue()
{
    UILabel* diamondNum_0 = dynamic_cast<UILabel*>(diamondMarket->getWidgetByName("DiamondNum_0"));
    UILabelAtlas* goldNum_0 = dynamic_cast<UILabelAtlas*>(diamondMarket->getWidgetByName("GoldNum_0"));
    SMoneySysChgTempData* pData = CMoneyMan::sharedInstance().getChgTempData(RMBToDiamond_1);
    if (pData)
    {
        CCString str;
        str.initWithFormat(GET_STRING_CSV(1010000017), pData->ExchangeFromValue);
        diamondNum_0->setText(str.getCString());
        str.initWithFormat("%d",pData->ExchangeToValue);
        goldNum_0->setStringValue(str.getCString());
    }
    UILabel* diamondNum_1 = dynamic_cast<UILabel*>(diamondMarket->getWidgetByName("DiamondNum_1"));
    UILabelAtlas* goldNum_1 = dynamic_cast<UILabelAtlas*>(diamondMarket->getWidgetByName("GoldNum_1"));
    pData = CMoneyMan::sharedInstance().getChgTempData(RMBToDiamond_2);
    if (pData)
    {
        CCString str;
        str.initWithFormat(GET_STRING_CSV(1010000017), pData->ExchangeFromValue);
        diamondNum_1->setText(str.getCString());
        str.initWithFormat("%d",pData->ExchangeToValue);
        goldNum_1->setStringValue(str.getCString());
    }
    UILabel* diamondNum_2 = dynamic_cast<UILabel*>(diamondMarket->getWidgetByName("DiamondNum_2"));
    UILabelAtlas* goldNum_2 = dynamic_cast<UILabelAtlas*>(diamondMarket->getWidgetByName("GoldNum_2"));
    pData = CMoneyMan::sharedInstance().getChgTempData(RMBToDiamond_3);
    if (pData)
    {
        CCString str;
        str.initWithFormat(GET_STRING_CSV(1010000017), pData->ExchangeFromValue);
        diamondNum_2->setText(str.getCString());
        str.initWithFormat("%d",pData->ExchangeToValue);
        goldNum_2->setStringValue(str.getCString());
    }
    UILabel* diamondNum_3 = dynamic_cast<UILabel*>(diamondMarket->getWidgetByName("DiamondNum_3"));
    UILabelAtlas* goldNum_3 = dynamic_cast<UILabelAtlas*>(diamondMarket->getWidgetByName("GoldNum_3"));
    pData = CMoneyMan::sharedInstance().getChgTempData(RMBToDiamond_4);
    if (pData)
    {
        CCString str;
        str.initWithFormat(GET_STRING_CSV(1010000017), pData->ExchangeFromValue);
        diamondNum_3->setText(str.getCString());
        str.initWithFormat("%d",pData->ExchangeToValue);
        goldNum_3->setStringValue(str.getCString());
    }
}
void GameLayer_DiamondMarket::buyBtnCallback(cocos2d::CCObject *pSender)
{
    UIButton* button = (UIButton*)pSender;
    GameLayer_Alert *alertUl = GameLayer_Alert::creatWithOnlySure(Type_Noraml);
    
    alertUl->setSureCallbackFunc(this, callfuncO_selector(GameLayer_DiamondMarket::sureBuyCallback));
    alertUl->setSureBtnTag(button->getTag());
    this->addChild(alertUl);
    switch (button->getTag()) {
        case Buy_0:
        {
            SMoneySysChgTempData* pData = CMoneyMan::sharedInstance().getChgTempData(RMBToDiamond_1);
			if (pData)
			{
                CCString str;
                str.initWithFormat(GET_STRING_CSV(1010000011), pData->ExchangeFromValue,pData->ExchangeToValue);
                alertUl->setText(str.getCString());
			}
            
        }
            break;
        case Buy_1:
            //alertUl->setText("确定要用10宝石兑换4500金币吗？");
        {
            SMoneySysChgTempData* pData = CMoneyMan::sharedInstance().getChgTempData(RMBToDiamond_2);
			if (pData)
			{
                CCString str;
                str.initWithFormat(GET_STRING_CSV(1010000012), pData->ExchangeFromValue,pData->ExchangeToValue);
                alertUl->setText(str.getCString());
			}
            
        }
            break;
        case Buy_2:
            //alertUl->setText("确定要用50宝石兑换1200金币吗？");
        {
            SMoneySysChgTempData* pData = CMoneyMan::sharedInstance().getChgTempData(RMBToDiamond_3);
			if (pData)
			{
                CCString str;
                str.initWithFormat(GET_STRING_CSV(1010000013), pData->ExchangeFromValue,pData->ExchangeToValue);
                alertUl->setText(str.getCString());
			}
            
        }
            break;
        case Buy_3:
            //alertUl->setText("确定要用100宝石兑换10000金币吗？");
        {
            SMoneySysChgTempData* pData = CMoneyMan::sharedInstance().getChgTempData(RMBToDiamond_4);
			if (pData)
			{
                CCString str;
                str.initWithFormat(GET_STRING_CSV(1010000014), pData->ExchangeFromValue,pData->ExchangeToValue);
                alertUl->setText(str.getCString());
			}
            
        }
            break;
        case Buy_4:
            //alertUl->setText("确定要用500宝石兑换60000金币吗？");
        {
            SMoneySysChgTempData* pData = CMoneyMan::sharedInstance().getChgTempData(RMBToDiamond_5);
			if (pData)
			{
                CCString str;
                str.initWithFormat(GET_STRING_CSV(1010000015), pData->ExchangeFromValue,pData->ExchangeToValue);
                alertUl->setText(str.getCString());
			}
            
        }
            break;
            
        default:
            break;
    }
}
void GameLayer_DiamondMarket::sureBuyCallback(cocos2d::CCObject *pSender)
{
    UIButton* btn = (UIButton*)pSender;
    switch (btn->getTag()) {
        case Buy_0:
        {
			CPlayerInfoMan::sharedInstance().RequsetRMBToDiamond(RMBToDiamond_1);
            //GameLayer_Alert *alertUl = GameLayer_Alert::creatWithOnlySure(Type_OnlySure);
            //alertUl->setText(GET_STRING_CSV(1010000016));
           // this->addChild(alertUl);
        }
            break;
        case Buy_1:
        {
            CPlayerInfoMan::sharedInstance().RequsetRMBToDiamond(RMBToDiamond_2);
           // GameLayer_Alert *alertUl = GameLayer_Alert::creatWithOnlySure(Type_OnlySure);
           // alertUl->setText(GET_STRING_CSV(1010000016));
           // this->addChild(alertUl);
        }
            break;
        case Buy_2:
        {
            CPlayerInfoMan::sharedInstance().RequsetRMBToDiamond(RMBToDiamond_3);
           // GameLayer_Alert *alertUl = GameLayer_Alert::creatWithOnlySure(Type_OnlySure);
            //alertUl->setText(GET_STRING_CSV(1010000016));
           // this->addChild(alertUl);
        }
            break;
        case Buy_3:
        {
            CPlayerInfoMan::sharedInstance().RequsetRMBToDiamond(RMBToDiamond_4);
          //  GameLayer_Alert *alertUl = GameLayer_Alert::creatWithOnlySure(Type_OnlySure);
           // alertUl->setText(GET_STRING_CSV(1010000016));
            //this->addChild(alertUl);
        }
            break;
        case Buy_4:
        {
            CPlayerInfoMan::sharedInstance().RequsetRMBToDiamond(RMBToDiamond_5);
          //  GameLayer_Alert *alertUl = GameLayer_Alert::creatWithOnlySure(Type_OnlySure);
           // alertUl->setText(GET_STRING_CSV(1010000016));
            //this->addChild(alertUl);
        }
            break;
        default:
            break;
    }
	sureBuyCallEffect(btn->getTag(),2);
}
void GameLayer_DiamondMarket::sureBuyCallEffect(int i,int iType)
{
	CCPoint point;
	switch (i) {
	case 1:
		point.x =105;
		point.y =725;
		break;
	case 2:
		point.x =105;
		point.y =625;
		break;
	case 3:
		point.x =105;
		point.y =525;
		break;
	case 4:
		point.x =105;
		point.y =425;
		break;
	case 5:
		point.x =105;
		point.y =325;
		break;
	default:
		break;
	}
	CCSize visableSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint goldPosition = ccp(450,visableSize.height-45);

	char str1[100]={0};
	switch(iType)
	{
	case 1:
		sprintf(str1,"./CocoStudioResources/DayLogin/WhiteGold.png");
		break;
	case 2:
		sprintf(str1,"./CocoStudioResources/DayLogin/WhiteJewel.png");
	default:
		break;
	}
	char str2[100]={0};
	switch(iType)
	{
	case 1:
		sprintf(str2,"./CocoStudioResources/DayLogin/Star1.png");
		break;
	case 2:
		sprintf(str2,"./CocoStudioResources/DayLogin/jewelStar1.png");
		break;
	default:
		break;
	}
	char str3[100]={0};
	switch(iType)
	{
	case 1:
		sprintf(str3,"./CocoStudioResources/DayLogin/FlyGold.png");
		break;
	case 2:
		sprintf(str3,"./CocoStudioResources/DayLogin/FlyJewel.png");
		break;
	default:
		break;
	}
	//最后亮一下的金币.
	CCSprite* lightGold1 = CCSprite::create(str1);
	this->addChild(lightGold1,10);
	lightGold1->setPosition(goldPosition);
	lightGold1->setVisible(false);
	CCSequence* lightGoldAction1 = CCSequence::create(CCShow::create() ,CCFadeOut::create(0.5),NULL);
	CCSprite* lightGold2 = CCSprite::create(str1);
	this->addChild(lightGold2,10);
	lightGold2->setPosition(goldPosition);
	lightGold2->setVisible(false);
	CCSequence* lightGoldAction2 = CCSequence::create(CCShow::create() ,CCFadeOut::create(0.5),NULL);
	CCSprite* lightGold3 = CCSprite::create(str1);
	this->addChild(lightGold3,10);
	lightGold3->setVisible(false);
	CCSequence* lightGoldAction3 = CCSequence::create(CCShow::create() ,CCFadeOut::create(0.5),NULL);
	lightGold3->setPosition(goldPosition);

	//钱的闪光.
	CCString str;
	CCAnimation* pAni = CCAnimation::create();
	for (int i=1; i<=3; i++) {
		if (iType==1)
			str.initWithFormat("./CocoStudioResources/DayLogin/Star%d.png",i);
		else if(iType==2)
			str.initWithFormat("./CocoStudioResources/DayLogin/jewelStar%d.png",i);
		pAni->addSpriteFrameWithFileName(str.getCString());
	}
	pAni->setDelayPerUnit(0.3f/3.f);
	pAni->setLoops(1);


	//金币爆炸效果.
	CCSprite* goldEffect1 = CCSprite::create();
	goldEffect1->setVisible(false);
	auto *pic_1 = CCSprite::create(str2);
	goldEffect1->setTexture(pic_1 -> getTexture());
	goldEffect1->setTextureRect(CCRectMake(0, 0, pic_1 -> getContentSize().width, pic_1 -> getContentSize().height));
	goldEffect1->setPosition(ccp(visableSize.width/2,visableSize.height-50));
	CCSequence* goldAction1 = CCSequence::create(CCShow::create(), CCAnimate::create(pAni), CCHide::create(), NULL);
	this->addChild(goldEffect1, 10);

	CCSprite* goldEffect2 = CCSprite::create();
	goldEffect2->setVisible(false);
	auto *pic_2 = CCSprite::create(str2);
	goldEffect2->setTexture(pic_2 -> getTexture());
	goldEffect2 -> setTextureRect(CCRectMake(0, 0, pic_2-> getContentSize().width, pic_2->getContentSize().height));
	goldEffect2->setPosition(ccp(visableSize.width/2,visableSize.height-50));
	CCSequence* goldAction2 = CCSequence::create(CCShow::create(), CCAnimate::create(pAni), CCHide::create(), NULL);
	this->addChild(goldEffect2, 10);

	CCSprite* goldEffect3 = CCSprite::create();
	goldEffect3->setVisible(false);
	auto *pic_3 = CCSprite::create(str2);

	goldEffect3->setTexture(pic_3 -> getTexture());
	goldEffect3->setTextureRect(CCRectMake(0, 0, pic_3 -> getContentSize().width, pic_3 -> getContentSize().height));
	goldEffect3->setPosition(ccp(visableSize.width/2,visableSize.height-50));
	//CCSequence* goldAction3 = CCSequence::create(CCShow::create(), CCAnimate::create(pAni), CCHide::create(),CCCallFunc::create(this, callfunc_selector(GameLayer_DayLogin::DoCallBack)) ,CCCallFunc::create(this, callfunc_selector(GameLayer_DayLogin::removeFromParent)), NULL);
	CCSequence* goldAction3 = CCSequence::create(CCShow::create(), CCAnimate::create(pAni), CCHide::create(), NULL);
	this->addChild(goldEffect3, 10);
	//飞行的钱币.
	CCSprite* flyGold1 = CCSprite::create(str3);
	flyGold1->setVisible(false);
	flyGold1->setPosition(point);
	this->addChild(flyGold1, 10);
	CCSequence* flyAction1 = CCSequence::create(CCShow::create(), CCMoveTo::create(0.6, goldPosition),  CCCallFuncO::create(lightGold3, callfuncO_selector(CCSprite::runAction), lightGoldAction3), CCCallFuncO::create(goldEffect1, callfuncO_selector(CCSprite::runAction), goldAction1), CCHide::create(), NULL);
	CCSprite* flyGold2 = CCSprite::create(str3);
	flyGold2->setVisible(false);
	flyGold2->setScale(0.9);
	flyGold2->setPosition(point);
	this->addChild(flyGold2, 10);
	CCSequence* flyAction2 = CCSequence::create(CCDelayTime::create(0.3), CCShow::create(), CCMoveTo::create(0.6, goldPosition),CCCallFuncO::create(lightGold2, callfuncO_selector(CCSprite::runAction), lightGoldAction2), CCCallFuncO::create(goldEffect2, callfuncO_selector(CCSprite::runAction), goldAction2),  CCHide::create(), NULL);
	CCSprite* flyGold3 = CCSprite::create(str3);
	flyGold3->setVisible(false);
	flyGold3->setScale(0.8);
	flyGold3->setPosition(point);
	this->addChild(flyGold3, 10);
	CCSequence* flyAction3 = CCSequence::create(CCDelayTime::create(0.6), CCShow::create(), CCMoveTo::create(0.6, goldPosition), CCCallFuncO::create(goldEffect3, callfuncO_selector(CCSprite::runAction), goldAction3), CCCallFuncO::create(lightGold1, callfuncO_selector(CCSprite::runAction), lightGoldAction1), CCHide::create(), NULL);

	//爆炸的闪光效果.
	CCSprite* riceEffect = CCSprite::create();
	pAni = CCAnimation::create();
	for (int i=1; i<=4; i++) {
		str.initWithFormat("./CocoStudioResources/DayLogin/Boom%d.png",i);
		pAni->addSpriteFrameWithFileName(str.getCString());
	}
	pAni->setDelayPerUnit(0.3f/4.f);
	pAni->setLoops(1);
	auto *pic_4 = CCSprite::create("./CocoStudioResources/DayLogin/Boom1.png");
	riceEffect->setTexture(pic_4 -> getTexture());
	riceEffect->setTextureRect(CCRectMake(0, 0, pic_4 -> getContentSize().width, pic_4 -> getContentSize().height));
	riceEffect->setPosition(point);
	this->addChild(riceEffect, 0);
	riceEffect->runAction(CCSequence::create(CCAnimate::create(pAni),CCHide::create(), CCCallFuncO::create(flyGold1, callfuncO_selector(CCSprite::runAction), flyAction1), CCCallFuncO::create(flyGold2, callfuncO_selector(CCSprite::runAction), flyAction2), CCCallFuncO::create(flyGold3, callfuncO_selector(CCSprite::runAction), flyAction3),NULL));
}