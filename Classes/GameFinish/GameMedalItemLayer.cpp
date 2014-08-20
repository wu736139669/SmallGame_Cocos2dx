//
// GameMedalItemLayer.cpp
// OnceAgain
//
// Created by xiaohai on 14-4-28.
//
//

#include "GameMedalItemLayer.h"
#include "GameUIExportJson.h"
#include "StringUtil.h"
#include "CounterByImage.h"
#include "NetHttpClient.h"
#include "NetCallBack.h"
#include "MsgDefine.h"
#include "PlayerInfoManager.h"
#include "XQDate.h"
#include "ItemDefine.h"
#include "GameShare_Global.h"

GameMedalItemLayer::GameMedalItemLayer()
{
    
}

GameMedalItemLayer::~GameMedalItemLayer()
{
    CC_SAFE_RELEASE(ul);
}

CCScene* GameMedalItemLayer::createScene()
{
    auto scene = CCScene::create();
    auto layer = GameMedalItemLayer::create();
    scene->addChild(layer);
    return scene;
}

bool GameMedalItemLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    //载入ui
    this->initData();
    
    //绑定ui
    this->BindingUIItems();
    
    // 图标名称MedalIcon
    
    return true;
}

#pragma mark - initData
void GameMedalItemLayer::initData()
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    ul = UILayer::create();
//    ul->retain();
    auto myLayout = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("./CocoStudioResources/GameMedalItemLayer.json"));
    ul->addWidget(myLayout);
    ul->setContentSize(visibleSize);
    this->addChild(ul, 0, 100); 
}

void GameMedalItemLayer::BindingUIItems() {
    //绑定ui界面item
    madelIcon = dynamic_cast<UIImageView*>(ul->getWidgetByName("MedalIcon"));
    ScoreNumber = dynamic_cast<UILabel*>(ul->getWidgetByName("DisCriptLabel"));
    ScoreNumber -> setPosition(ccp(ScoreNumber->getPosition().x + 15, ScoreNumber ->getPosition().y-25));
    
    isSeal = dynamic_cast<UIImageView*>(ul->getWidgetByName("IsGet"));
}

#pragma mark - otherClass Call
void GameMedalItemLayer::setMadelInfo(SMeDalTaskData *info, int isGeted, int gameId,bool bPlayerAni) {

    CCLog("setMadelInfo %d,%d,%d",isGeted,gameId,bPlayerAni);
    //通过网络数值信息设置madel
    gameType = gameId;
    medalId = info->TaskId;
    madelIcon->setTexture("");
	
    CCString str;
    str.initWithFormat(info->TaskDetail.c_str(),CStringUtil::ToString(info->TaskValue).c_str());
	if (info->TaskRange == 2)
	{
		CEveryDayCell* pDayCell = CTaskMan::sharedInstance().getEveryDayTask(GameShare_Global::shareGlobal()->gameType,info->TaskCatelog);
		if(pDayCell)
		{
			CCString strVal;
			strVal.initWithFormat("%d/%d",pDayCell->getCounter(),info->TaskValue);
			str.initWithFormat(info->TaskDetail.c_str(),strVal.getCString());
		}

	}
    ScoreNumber->setText(str.getCString());
    
    isSeal -> setVisible(false);
    
    int taskrewardvalue = info -> TaskRewardId;
        
    CCSprite *pic;
 
    if (taskrewardvalue == eItemBigTypeGold) {
        pic = CCSprite::create("./MedalImages/medal_1.png");
    }
    else if (taskrewardvalue == eItemBigTypeDiam) {
        pic = CCSprite::create("./MedalImages/medal_2.png");
    }else if (taskrewardvalue == eItemBigTypePower)
    {
		pic = CCSprite::create("./MedalImages/medal_3.png");
    }
    else {
		CCString str;
		str.initWithFormat("./CocoStudioResources/GameItem/%d.png",taskrewardvalue);
        pic = CCSprite::create(str.getCString());
    }
  
    pic->setPosition(madelIcon->getPosition());
    addChild(pic);
    
    CCSprite *number = this -> getCountNumber(info->TaskRewardValue);
    number->setAnchorPoint(ccp(0.5, 0.5));
    number->setPosition(ccp(pic->getContentSize().width*1/3+ 15 - (numberPicLength-2) *6, pic->getContentSize().height*2/7-45));
    number -> setScale(0.8);
    pic->addChild(number);
    
    CCString str1;
    str1.initWithFormat("medal%d",info->TaskId);
 
    if (isGeted == 1) {
        if (bPlayerAni) {
            isMedalGet();
        }else
            isSeal -> setVisible(true);
        
    }
    else {
            //isMedalGet();
    }
   madelIcon -> removeFromParent();
}

void GameMedalItemLayer::medalGetCallBack(CCObject *p) {
//    XQDate::sharedInstance().CompleteTask(gameType, medalId);
}

void GameMedalItemLayer::isMedalGet() {

    isSeal->setScale(4.0);
    isSeal->setVisible(true);
    CCScaleTo *sizeChange = CCScaleTo::create(0.4, 1);
    CCFiniteTimeAction* action= CCSequence::create(sizeChange,NULL);
    isSeal->runAction(CCSequence::create(CCShow::create(),CCRepeat::create(action, 1),CCDelayTime::create(0.3), NULL));
}

CCSprite * GameMedalItemLayer::getCountNumber(int count) {
    CCSprite *Multiply = CCSprite::createWithSpriteFrameName("number_10.png");
    int width = 12;
    std::vector<int>picList;
    picList.clear();
    do {
        int k = count%10;
        count = (count - k)/10;
        picList.push_back(k);
    } while (count >= 1);
    for (int i =0; i < picList.size(); i++) {
        CCString str;
        str.initWithFormat("number_%d.png", picList[picList.size() - i -1]);
        CCSprite *pic = CCSprite::createWithSpriteFrameName(str.getCString());
        width += 23;
     
        pic->setPosition(ccp(width, 13));
        
        Multiply->addChild(pic);

    }
    numberPicLength = picList.size();
    return Multiply;
}
