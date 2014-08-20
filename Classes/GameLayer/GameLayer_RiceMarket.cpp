//
//  GameLayer_RiceMarket.cpp
//  OnceAgain
//
//  Created by mac on 14-3-25.
//
//

#include "GameLayer_RiceMarket.h"
#include "GameLayer_Alert.h"
#include "MoneyManager.h"
#include "CsvStringData.h"
#include "PlayerInfoManager.h"
enum Buy_Tag
{
    Buy_0 = 1,
    Buy_1 = 2,
    Buy_2 = 3,
    Buy_3 = 4,
    Buy_4 = 5
};
GameLayer_RiceMarket::~GameLayer_RiceMarket()
{
    GUIReader::shareReader()->purgeGUIReader();
    DictionaryHelper::shareHelper()->purgeDictionaryHelper();
    ActionManager::shareManager()->purgeActionManager();
}


bool GameLayer_RiceMarket::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    //系统设置界面.
    riceMarket = UILayer::create();
    auto layout = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("./CocoStudioResources/RiceMarket.json"));
    riceMarket->addWidget(layout);
    //    sysSet->setVisible(true);
    this->addChild(riceMarket, 0, 101);
    
    UIPanel* panel = dynamic_cast<UIPanel*>(riceMarket->getWidgetByName("Panel"));
    panel->setBackGroundColor(ccBLACK);
    panel->setBackGroundColorOpacity(150);
    //关闭按钮
    UIButton* closeBtn = dynamic_cast<UIButton*>(riceMarket->getWidgetByName("CloseBtn"));
    closeBtn->setTouchEnable(true);
    closeBtn->addReleaseEvent(this, coco_releaseselector(GameLayer_RiceMarket::closeBtnCallback));
    closeBtn->setPressedActionEnabled(true);
    
    //购买按钮.
    UIButton* buyBtn_0 = dynamic_cast<UIButton*>(riceMarket->getWidgetByName("BuyBtn_0"));
    buyBtn_0->setTag(Buy_0);
    buyBtn_0->setPressedActionEnabled(true);
    buyBtn_0->addReleaseEvent(this, coco_releaseselector(GameLayer_RiceMarket::buyBtnCallback));
    UIButton* buyBtn_1 = dynamic_cast<UIButton*>(riceMarket->getWidgetByName("BuyBtn_1"));
    buyBtn_1->setTag(Buy_1);
    buyBtn_1->setPressedActionEnabled(true);
    buyBtn_1->addReleaseEvent(this, coco_releaseselector(GameLayer_RiceMarket::buyBtnCallback));
    UIButton* buyBtn_2 = dynamic_cast<UIButton*>(riceMarket->getWidgetByName("BuyBtn_2"));
    buyBtn_2->setTag(Buy_2);
    buyBtn_2->setPressedActionEnabled(true);
    buyBtn_2->addReleaseEvent(this, coco_releaseselector(GameLayer_RiceMarket::buyBtnCallback));
    UIButton* buyBtn_3 = dynamic_cast<UIButton*>(riceMarket->getWidgetByName("BuyBtn_3"));
    buyBtn_3->setTag(Buy_3);
    buyBtn_3->setPressedActionEnabled(true);
    buyBtn_3->addReleaseEvent(this, coco_releaseselector(GameLayer_RiceMarket::buyBtnCallback));
    //UIButton* buyBtn_4 = dynamic_cast<UIButton*>(riceMarket->getWidgetByName("BuyBtn_4"));
    //buyBtn_4->setTag(Buy_4);
    //buyBtn_4->setPressedActionEnabled(true);
    //buyBtn_4->addReleaseEvent(this, coco_releaseselector(GameLayer_RiceMarket::buyBtnCallback));
    
    //添加兑换按钮
    this->setVisible(true);
    this->setValue();
    return true;
}

void GameLayer_RiceMarket::setVisible(bool visible)
{
    CCLayer::setVisible(visible);
    UIPanel* dayLoginPanel = dynamic_cast<UIPanel*>(riceMarket->getWidgetByName("Panel"));
    dayLoginPanel->setTouchEnable(visible);
}

void GameLayer_RiceMarket::closeBtnCallback(cocos2d::CCObject *pSender)
{
    this->removeFromParent();
}

void GameLayer_RiceMarket::setValue()
{
    UILabel* diamondNum_0 = dynamic_cast<UILabel*>(riceMarket->getWidgetByName("DiamondNum_0"));
    UILabelAtlas* goldNum_0 = dynamic_cast<UILabelAtlas*>(riceMarket->getWidgetByName("GoldNum_0"));
    SMoneySysChgTempData* pData = CMoneyMan::sharedInstance().getChgTempData(GoldToRice_1);
    if (pData)
    {
        CCString str;
        str.initWithFormat("%d", pData->ExchangeToValue);
        diamondNum_0->setText(str.getCString());
        str.initWithFormat("%d",pData->ExchangeFromValue);
        goldNum_0->setStringValue(str.getCString());
    }
    UILabel* diamondNum_1 = dynamic_cast<UILabel*>(riceMarket->getWidgetByName("DiamondNum_1"));
    UILabelAtlas* goldNum_1 = dynamic_cast<UILabelAtlas*>(riceMarket->getWidgetByName("GoldNum_1"));
    pData = CMoneyMan::sharedInstance().getChgTempData(GoldToRice_2);
    if (pData)
    {
        CCString str;
        str.initWithFormat("%d", pData->ExchangeToValue);
        diamondNum_1->setText(str.getCString());
        str.initWithFormat("%d",pData->ExchangeFromValue);
        goldNum_1->setStringValue(str.getCString());
    }
    UILabel* diamondNum_2 = dynamic_cast<UILabel*>(riceMarket->getWidgetByName("DiamondNum_2"));
    UILabelAtlas* goldNum_2 = dynamic_cast<UILabelAtlas*>(riceMarket->getWidgetByName("GoldNum_2"));
    pData = CMoneyMan::sharedInstance().getChgTempData(GoldToRice_3);
    if (pData)
    {
        CCString str;
        str.initWithFormat("%d", pData->ExchangeToValue);
        diamondNum_2->setText(str.getCString());
        str.initWithFormat("%d",pData->ExchangeFromValue);
        goldNum_2->setStringValue(str.getCString());
    }
    UILabel* diamondNum_3 = dynamic_cast<UILabel*>(riceMarket->getWidgetByName("DiamondNum_3"));
    UILabelAtlas* goldNum_3 = dynamic_cast<UILabelAtlas*>(riceMarket->getWidgetByName("GoldNum_3"));
    pData = CMoneyMan::sharedInstance().getChgTempData(GoldToRice_4);
    if (pData)
    {
        CCString str;
        str.initWithFormat("%d", pData->ExchangeToValue);
        diamondNum_3->setText(str.getCString());
        str.initWithFormat("%d",pData->ExchangeFromValue);
        goldNum_3->setStringValue(str.getCString());
    }
    //UILabel* diamondNum_4 = dynamic_cast<UILabel*>(riceMarket->getWidgetByName("DiamondNum_4"));
    //UILabelAtlas* goldNum_4 = dynamic_cast<UILabelAtlas*>(riceMarket->getWidgetByName("GoldNum_4"));
    //pData = CMoneyMan::sharedInstance().getChgTempData(GoldToRice_5);
    //if (pData)
    //{
    //    CCString str;
    //    str.initWithFormat("%d", pData->ExchangeToValue);
    //    diamondNum_4->setText(str.getCString());
    //    str.initWithFormat("%d",pData->ExchangeFromValue);
    //    goldNum_4->setStringValue(str.getCString());
    //}
}
void GameLayer_RiceMarket::buyBtnCallback(cocos2d::CCObject *pSender)
{
    UIButton* button = (UIButton*)pSender;
    GameLayer_Alert *alertUl = GameLayer_Alert::creatWithOnlySure(Type_Noraml);
    
    alertUl->setSureCallbackFunc(this, callfuncO_selector(GameLayer_RiceMarket::sureBuyCallback));
    alertUl->setSureBtnTag(button->getTag());
    SMoneySysChgTempData* pData = NULL;
    switch (button->getTag()) {
        case Buy_0:
        {
            pData = CMoneyMan::sharedInstance().getChgTempData(GoldToRice_1);
			if (pData)
			{
                CCString str;
                str.initWithFormat(GET_STRING_CSV(101000006), pData->ExchangeFromValue,pData->ExchangeToValue);
                alertUl->setText(str.getCString());
			}
            
        }
            break;
        case Buy_1:
            //alertUl->setText("确定要用10宝石兑换4500金币吗？");
        {
            pData = CMoneyMan::sharedInstance().getChgTempData(GoldToRice_2);
			if (pData)
			{
                CCString str;
                str.initWithFormat(GET_STRING_CSV(101000007), pData->ExchangeFromValue,pData->ExchangeToValue);
                alertUl->setText(str.getCString());
			}
            
        }
            break;
        case Buy_2:
            //alertUl->setText("确定要用50宝石兑换1200金币吗？");
        {
            pData = CMoneyMan::sharedInstance().getChgTempData(GoldToRice_3);
			if (pData)
			{
                CCString str;
                str.initWithFormat(GET_STRING_CSV(101000008), pData->ExchangeFromValue,pData->ExchangeToValue);
                alertUl->setText(str.getCString());
			}
            
        }
            break;
        case Buy_3:
            //alertUl->setText("确定要用100宝石兑换10000金币吗？");
        {
            pData = CMoneyMan::sharedInstance().getChgTempData(GoldToRice_4);
			if (pData)
			{
                CCString str;
                str.initWithFormat(GET_STRING_CSV(101000009), pData->ExchangeFromValue,pData->ExchangeToValue);
                alertUl->setText(str.getCString());
			}
            
        }
            break;
        case Buy_4:
            //alertUl->setText("确定要用500宝石兑换60000金币吗？");
        {
            pData = CMoneyMan::sharedInstance().getChgTempData(GoldToRice_5);
			if (pData)
			{
                CCString str;
                str.initWithFormat(GET_STRING_CSV(1010000010), pData->ExchangeFromValue,pData->ExchangeToValue);
                alertUl->setText(str.getCString());
			}
            
        }
            break;
            
        default:
            break;
    }
    if (CPlayerInfoMan::sharedInstance().getPlayerInfo().nGem-pData->ExchangeFromValue < 0) {
       // GameLayer_Alert *alertUl = GameLayer_Alert::creatWithOnlySure(Type_OnlySure);
       // alertUl->setText(GET_STRING_CSV(1010000022));
       // this->addChild(alertUl);
        return;
    }
    this->addChild(alertUl);
}
void GameLayer_RiceMarket::sureBuyCallback(cocos2d::CCObject *pSender)
{
    UIButton* btn = (UIButton*)pSender;
    switch (btn->getTag()) {
        case Buy_0:
        {
            CPlayerInfoMan::sharedInstance().RequestDiamondToRice(GoldToRice_1);
           // GameLayer_Alert *alertUl = GameLayer_Alert::creatWithOnlySure(Type_OnlySure);
           /// alertUl->setText(GET_STRING_CSV(1010000016));
           // this->addChild(alertUl);
        }
            break;
        case Buy_1:
        {
            CPlayerInfoMan::sharedInstance().RequestDiamondToRice(GoldToRice_2);
            //GameLayer_Alert *alertUl = GameLayer_Alert::creatWithOnlySure(Type_OnlySure);
            //alertUl->setText(GET_STRING_CSV(1010000016));
           // this->addChild(alertUl);
        }
            break;
        case Buy_2:
        {
            CPlayerInfoMan::sharedInstance().RequestDiamondToRice(GoldToRice_3);
           // GameLayer_Alert *alertUl = GameLayer_Alert::creatWithOnlySure(Type_OnlySure);
          //  alertUl->setText(GET_STRING_CSV(1010000016));
            //this->addChild(alertUl);
        }
            break;
        case Buy_3:
        {
            CPlayerInfoMan::sharedInstance().RequestDiamondToRice(GoldToRice_4);
           // GameLayer_Alert *alertUl = GameLayer_Alert::creatWithOnlySure(Type_OnlySure);
            //alertUl->setText(GET_STRING_CSV(1010000016));
            //this->addChild(alertUl);
        }
            break;
        case Buy_4:
        {
            CPlayerInfoMan::sharedInstance().RequestDiamondToRice(GoldToRice_5);
           // GameLayer_Alert *alertUl = GameLayer_Alert::creatWithOnlySure(Type_OnlySure);
           // alertUl->setText(GET_STRING_CSV(1010000016));
          //  this->addChild(alertUl);
        }
            break;
        default:
            break;
    }
}
