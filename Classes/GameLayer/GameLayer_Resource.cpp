//
//  GameLayer_Resource.cpp
//  OnceAgain
//
//  Created by mac on 14-3-25.
//
//

#include "GameLayer_Resource.h"
#include "PlayerInfoManager.h"
#include "NetPacket.h"
#include "MsgDefine.h"
#include "GameLayer_Tag.h"
#include "GameShare_Scene.h"
#include "GameFruitScene.h"
IMPLEMENT_DLG_ID(GameLayer_Resource,Resource_Tag);

GameLayer_Resource::~GameLayer_Resource()
{
    GUIReader::shareReader()->purgeGUIReader();
    DictionaryHelper::shareHelper()->purgeDictionaryHelper();
    ActionManager::shareManager()->purgeActionManager();
}
void GameLayer_Resource::onEnter()
{
    CCLayer::onEnter();
    this->reSetDiamondNum(CPlayerInfoMan::sharedInstance().getPlayerInfo().nGem);
    this->reSetGoldNum(CPlayerInfoMan::sharedInstance().getPlayerInfo().nMoney);
    this->reSetLv(CPlayerInfoMan::sharedInstance().getPlayerInfo().nLevel, CPlayerInfoMan::sharedInstance().getPlayerInfo().nExp);
    
}
bool GameLayer_Resource::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    //系统设置界面.
    gameResource = UILayer::create();
    auto layout = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("./CocoStudioResources/GameResource.json"));
    gameResource->addWidget(layout);
    //    sysSet->setVisible(true);
    this->addChild(gameResource, 0, 101);
    
    
    UIImageView* goldPanel = dynamic_cast<UIImageView*>(gameResource->getWidgetByName("Gold_BgImg"));
//    CCLOG("~~~~~~~~~~~~%d",CPlayerInfoMan::sharedInstance().getPlayerInfo().nMoney);
    goldNum = this->getSpriteByScore(CPlayerInfoMan::sharedInstance().getPlayerInfo().nMoney);
    goldNum->setScale(0.8);
    goldNum->ignoreAnchorPointForPosition(false);
    goldNum->setAnchorPoint(ccp(0.0, 0.0));
    goldPanel->addRenderer(goldNum, 10);
    
    UIImageView* diamondPanel = dynamic_cast<UIImageView*>(gameResource->getWidgetByName("Diamond_BgImg"));
    diamondNum = this->getSpriteByScore(CPlayerInfoMan::sharedInstance().getPlayerInfo().nGem);
    diamondNum->setScale(0.8);
    diamondNum->ignoreAnchorPointForPosition(false);
    diamondNum->setAnchorPoint(ccp(0.0, 0.0));
    diamondPanel->addRenderer(diamondNum, 10);
    

    
    UIImageView* levelPanel = dynamic_cast<UIImageView*>(gameResource->getWidgetByName("Level_FlowerImg"));
    lvNum = this->getLvByNum(CPlayerInfoMan::sharedInstance().getPlayerInfo().nLevel);
    lvNum -> setPosition(ccp(-8, -2));
    lvNum -> setScale(1.2);
    levelPanel->addRenderer(lvNum, 10);
    
    //进度条.
    UILoadingBar* experenceBar = dynamic_cast<UILoadingBar*>(gameResource->getWidgetByName("Level_Exprience"));
    experenceBar->setPercent(CPlayerInfoMan::sharedInstance().getPlayerInfo().nExp);
    
    
    
    UILabel *label = dynamic_cast<UILabel*>(gameResource -> getWidgetByName("Precentage"));
    label -> setText("");
    lvPrecentage = getLvPrecentageNumber((int)CPlayerInfoMan::sharedInstance().getPlayerInfo().nExp);
    lvPrecentage -> setScale(0.2);
//    lvPrecentage -> setPosition(label -> getPosition());
    label -> addRenderer(lvPrecentage, 100);

    
    return true;
}


void GameLayer_Resource::setVisible(bool visible)
{
    CCLayer::setVisible(visible);
    UIPanel* dayLoginPanel = dynamic_cast<UIPanel*>(gameResource->getWidgetByName("Panel"));
    dayLoginPanel->setTouchEnable(visible);
}

void GameLayer_Resource::addGoldCallback(CCObject* target, SEL_CallFuncO callfun)
{
    UIPanel* addGoldPanel = dynamic_cast<UIPanel*>(gameResource->getWidgetByName("GoldPanel"));
    addGoldPanel->addReleaseEvent(target, callfun);
}
void GameLayer_Resource::addDiamondCallback(CCObject* target, SEL_CallFuncO callfun)
{
    UIPanel* addGoldPanel = dynamic_cast<UIPanel*>(gameResource->getWidgetByName("DiamondPanel"));
    addGoldPanel->addReleaseEvent(target, callfun);
}
bool GameLayer_Resource::onPackageFilter(void *pDataPkg) {
	CResponsePacket* pPkt = (CResponsePacket*)pDataPkg;
	unsigned int unMsgType = pPkt->getMsgType();
	unsigned int unMsgCode = pPkt->getMsgCode();
	//网络数据传输完成
	if (pPkt->getDataState() == eNetMsgDataStateComplete)
	{
        //玩家系统.
		if (unMsgType == eNetMsgTypePlayerSys)
		{
			if (unMsgCode == eNetMsgPlayerSysBugGem)
			{
				reSetDiamondNum(CPlayerInfoMan::sharedInstance().getPlayerInfo().nGem);
                //CCScene *gameScene = GameShare_Scene::getGameSceneByType(Game_Fruit);
                
                //CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.4, CGameFruitScene ::scene()));

			}
            if (unMsgCode == eNetMsgPlayerSysChgGold)
			{
				reSetDiamondNum(CPlayerInfoMan::sharedInstance().getPlayerInfo().nGem);
                reSetGoldNum(CPlayerInfoMan::sharedInstance().getPlayerInfo().nMoney);
			}
            if (unMsgCode == eNetMsgPlayerSysChgTiLi)
			{
				reSetDiamondNum(CPlayerInfoMan::sharedInstance().getPlayerInfo().nGem);
			}
		}
        //任务系统
        if (unMsgType == eNetMsgTypeMissionSys) {
            if (unMsgCode == eNetMsgMissionSysTask)
			{
				reSetDiamondNum(CPlayerInfoMan::sharedInstance().getPlayerInfo().nGem);
                reSetGoldNum(CPlayerInfoMan::sharedInstance().getPlayerInfo().nMoney);
			}
        }
        //道具系统
        if (unMsgType == eNetMsgTypeItemSys) {
            if (unMsgCode == eNetMsgMissionSysTask)
			{
				reSetDiamondNum(CPlayerInfoMan::sharedInstance().getPlayerInfo().nGem);
                reSetGoldNum(CPlayerInfoMan::sharedInstance().getPlayerInfo().nMoney);
			}
        }
        //强化系统
        if (unMsgType == eNetMsgTypeIntensifySys) {
            if (unMsgCode == eNetMsgItemSysBuy)
			{
				reSetDiamondNum(CPlayerInfoMan::sharedInstance().getPlayerInfo().nGem);
                reSetGoldNum(CPlayerInfoMan::sharedInstance().getPlayerInfo().nMoney);
			}
        }
		
	}
	return true;
}
void GameLayer_Resource::reSetDiamondNum(long num)
{
    if (diamondNum) {
//        diamondNum->removeFromParent();
        diamondNum->removeFromParentAndCleanup(true);
    }
    UIImageView* diamondPanel = dynamic_cast<UIImageView*>(gameResource->getWidgetByName("Diamond_BgImg"));
    diamondNum = this->getSpriteByScore(num);
    diamondNum->setScale(0.8);
    diamondNum->ignoreAnchorPointForPosition(false);
    diamondNum->setAnchorPoint(ccp(0.0, 0.0));
    diamondNum->setPosition(ccp(10, 0));
    diamondPanel->addRenderer(diamondNum, 10);
}
void GameLayer_Resource::reSetGoldNum(long num)
{
    if (goldNum) {
        goldNum->removeFromParentAndCleanup(true);
    }
    UIImageView* goldPanel = dynamic_cast<UIImageView*>(gameResource->getWidgetByName("Gold_BgImg"));
    goldNum = this->getSpriteByScore(num);
    goldNum->setScale(0.8);
    goldNum->ignoreAnchorPointForPosition(false);
    goldNum->setPosition(ccp(10, 0));
    goldNum->setAnchorPoint(ccp(0.0, 0.0));
    goldPanel->addRenderer(goldNum, 10);
    
    
}

void GameLayer_Resource::reSetLvPrecentageNumber(int num) {
    if (lvPrecentage) {
        lvPrecentage -> removeFromParentAndCleanup(true);
    }
    UILabel *label = dynamic_cast<UILabel*>(gameResource -> getWidgetByName("Precentage"));
    label -> setText("");
    lvPrecentage = getLvPrecentageNumber(num);
    lvPrecentage -> setScale(0.2);
//    lvPrecentage -> setPosition(label -> getPosition());
    label -> addRenderer(lvPrecentage, 100);
}

void GameLayer_Resource::reSetLv(int num, float persent)
{
    if (lvNum) {
        lvNum->removeFromParentAndCleanup(true);
    }
    UIImageView* levelPanel = dynamic_cast<UIImageView*>(gameResource->getWidgetByName("Level_FlowerImg"));
    lvNum = this->getLvByNum(num);
    lvNum -> setScale(1.2);
    lvNum -> setPosition(ccp(-8, -2));
    levelPanel->addRenderer(lvNum, 10);
    UILoadingBar* experenceBar = dynamic_cast<UILoadingBar*>(gameResource->getWidgetByName("Level_Exprience"));

    experenceBar->setPercent(persent);
    
    reSetLvPrecentageNumber((int)persent);
//    str.initWithFormat("%.0lf%%", persent);
//    label -> setText(str.getCString());

}
CCSprite* GameLayer_Resource::getSpriteByScore(long score)
{

    long temp = score;
    //位数,用于设置横坐标偏移量.
    int digit = 0;
    CCSprite* scroeSprite = CCSprite::create();
    float offSetX = 20.0;
    if (temp<0) {
        return scroeSprite;
    }
    while (temp>0 || (digit==0 && temp==0)) {
        int remainder = temp % 10;
        temp = temp/10;
        CCSprite *m_Sprite;
        CCRect rc;
        switch(remainder)
        {
            case 0:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/ResouceNumZero.png");
                break;
            }
            case 1:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/ResouceNumOne.png");
                break;
            }
            case 2:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/ResouceNumTwo.png");
                break;
            }
            case 3:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/ResouceNumThree.png");
                break;
            }
            case 4:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/ResouceNumFour.png");
                break;
            }
            case 5:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/ResouceNumFive.png");
                break;
            }
            case 6:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/ResouceNumSix.png");
                break;
            }
            case 7:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/ResouceNumSeven.png");
                break;
            }
            case 8:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/ResouceNumEight.png");
                break;
            }
            case 9:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/ResouceNumNine.png");
                
                break;
            }
            default:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/ResouceNumZero.png");
                break;
            }
        }
        m_Sprite->setPosition(ccp((digit)*(-offSetX), 0));
        scroeSprite->addChild(m_Sprite);
        digit++;
    }
    digit--;
    //    scroeSprite->setContentSize(CCSize(30.0*digit, 20));
    CCArray* array = scroeSprite->getChildren();
    for (int i=0; i<array->count(); i++) {
        CCPoint point = ((CCSprite*)array->objectAtIndex(i))->getPosition();
        point.x += (digit)*(offSetX/2.0);
        ((CCSprite*)array->objectAtIndex(i))->setPosition(point);
    }
    
    return scroeSprite;
}

CCSprite* GameLayer_Resource::getLvPrecentageNumber(int num) {
    int temp =num;
    //位数,用于设置横坐标偏移量.
    int digit = 0;
    CCSprite* scroeSprite = CCSprite::create();
    float offSetX = 88.0;
    while (temp>0 || (digit==0 && temp==0)) {
        int remainder = temp % 10;
        temp = temp/10;
        CCSprite *m_Sprite;
        CCRect rc;
        switch(remainder)
        {
            case 0:
            {
                m_Sprite = CCSprite::create("./numberBox/lightBrownZero.png");
                break;
            }
            case 1:
            {
                m_Sprite = CCSprite::create("./numberBox/lightBrownOne.png");
                break;
            }
            case 2:
            {
                m_Sprite = CCSprite::create("./numberBox/lightBrownTwo.png");
                break;
            }
            case 3:
            {
                m_Sprite = CCSprite::create("./numberBox/lightBrownThree.png");
                break;
            }
            case 4:
            {
                m_Sprite = CCSprite::create("./numberBox/lightBrownFour.png");
                break;
            }
            case 5:
            {
                m_Sprite = CCSprite::create("./numberBox/lightBrownFive.png");
                break;
            }
            case 6:
            {
                m_Sprite = CCSprite::create("./numberBox/lightBrownSix.png");
                break;
            }
            case 7:
            {
                m_Sprite = CCSprite::create("./numberBox/lightBrownSeven.png");
                break;
            }
            case 8:
            {
                m_Sprite = CCSprite::create("./numberBox/lightBrownEight.png");
                break;
            }
            case 9:
            {
                m_Sprite = CCSprite::create("./numberBox/lightBrownNine.png");
                
                break;
            }
            default:
            {
                m_Sprite = CCSprite::create("./numberBox/lightBrownZero.png");
                break;
            }
        }
        
        m_Sprite->setPosition(ccp((digit)*(-offSetX), 0));
        scroeSprite->addChild(m_Sprite);
        digit++;
    }
    
    CCSprite* lvSprite = CCSprite::create("./numberBox/lightBrownPrecentage.png");
	if(num<10)
	lvSprite->setPosition(ccp((digit)*(offSetX)+25, 0));
	else
    lvSprite->setPosition(ccp((digit)*(offSetX) -55, 0));
    scroeSprite->addChild(lvSprite);
    
    CCArray* array = scroeSprite->getChildren();
    for (int i=0; i<array->count(); i++) {
        CCPoint point = ((CCSprite*)array->objectAtIndex(i))->getPosition();
        point.x += (digit)*(offSetX/2.0);
        ((CCSprite*)array->objectAtIndex(i))->setPosition(point);
    }
    
    return scroeSprite;
}


CCSprite* GameLayer_Resource::getLvByNum(int num)
{
    int temp = num;
    //位数,用于设置横坐标偏移量.
    int digit = 0;
    CCSprite* scroeSprite = CCSprite::create();
    float offSetX = 15.0;
    while (temp>0 || (digit==0 && temp==0)) {
        int remainder = temp % 10;
        temp = temp/10;
        CCSprite *m_Sprite;
	
        CCRect rc;
        switch(remainder)
        {
            case 0:
            {
                m_Sprite = CCSprite::create("./numberBox/lightBrownZero.png");
				m_Sprite->setScale(0.2);
                break;
            }
            case 1:
            {
                m_Sprite = CCSprite::create("./numberBox/lightBrownOne.png");
				m_Sprite->setScale(0.2);
                break;
            }
            case 2:
            {
                m_Sprite = CCSprite::create("./numberBox/lightBrownTwo.png");
				m_Sprite->setScale(0.2);
                break;
            }
            case 3:
            {
                m_Sprite = CCSprite::create("./numberBox/lightBrownThree.png");
				m_Sprite->setScale(0.2);
                break;
            }
            case 4:
            {
                m_Sprite = CCSprite::create("./numberBox/lightBrownFour.png");
				m_Sprite->setScale(0.2);
                break;
            }
            case 5:
            {
                m_Sprite = CCSprite::create("./numberBox/lightBrownFive.png");
				m_Sprite->setScale(0.2);
                break;
            }
            case 6:
            {
                m_Sprite = CCSprite::create("./numberBox/lightBrownSix.png");
				m_Sprite->setScale(0.2);
                break;
            }
            case 7:
            {
                m_Sprite = CCSprite::create("./numberBox/lightBrownSeven.png");
				m_Sprite->setScale(0.2);
                break;
            }
            case 8:
            {
                m_Sprite = CCSprite::create("./numberBox/lightBrownEight.png");
				m_Sprite->setScale(0.2);
                break;
            }
            case 9:
            {
                m_Sprite = CCSprite::create("./numberBox/lightBrownNine.png");
				m_Sprite->setScale(0.2);
                break;
            }
            default:
            {
                m_Sprite = CCSprite::create("./numberBox/lightBrownZero.png");
				m_Sprite->setScale(0.2);
                break;
            }
        }
        
        m_Sprite->setPosition(ccp((digit)*(-offSetX), 0));
        scroeSprite->addChild(m_Sprite);
        digit++;
    }

//    CCSprite* lvSprite = CCSprite::create("./CocoStudioResources/sz_14.png");
//    lvSprite->setPosition(ccp((digit)*(-offSetX), 0));
//    scroeSprite->addChild(lvSprite);
//
    CCArray* array = scroeSprite->getChildren();
    for (int i=0; i<array->count(); i++) {
        CCPoint point = ((CCSprite*)array->objectAtIndex(i))->getPosition();
        point.x += (digit)*(offSetX/2.0);
        ((CCSprite*)array->objectAtIndex(i))->setPosition(point);
    }
    
    return scroeSprite;
}