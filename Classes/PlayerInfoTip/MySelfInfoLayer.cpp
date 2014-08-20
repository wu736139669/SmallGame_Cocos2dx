//
// MySelfInfoLayer.cpp
// OnceAgain
//
// Created by xiaohai on 14-5-9.
//
//

#include "MySelfInfoLayer.h"
#include "GameUIExportJson.h"
#include "PlayerInfoManager.h"
#include "XQDate.h"
CCScene* MySelfInfoLayer::createScene()
{
    auto scene = CCScene::create();
    auto layer = MySelfInfoLayer::create();
    scene->addChild(layer);
    return scene;
}

#pragma mark - initData
void MySelfInfoLayer::initData()
{
    // add your codes here...
    
    ul = UILayer::create();
    addChild(ul);
    
    auto *myLayout = dynamic_cast<Layout*>(GUIReader::shareReader() -> widgetFromJsonFile(uiMySelfInfoLayer));
    ul -> addWidget(myLayout);
    
}

void MySelfInfoLayer::BindingUIItems()
{
	GoldNumber = static_cast<UILabel*>(ul -> getWidgetByName("Gold"));						//第一名
	Sliver = static_cast<UILabel*>(ul -> getWidgetByName("sliver"));						//2
	Broze = static_cast<UILabel*>(ul -> getWidgetByName("broze"));							//3
	allFightTimes = static_cast<UILabel*>(ul -> getWidgetByName("AllFightTime"));			//总 战场次数
	winTimes = static_cast<UILabel*>(ul -> getWidgetByName("WinTimes"));					//成功场次
	loseTimes = static_cast<UILabel*>(ul -> getWidgetByName("LoseTimes"));					//失败
	alike = static_cast<UILabel*>(ul -> getWidgetByName("alike"));							//平局 
	 allMedals = static_cast<UIPanel*>(ul -> getWidgetByName("MedalLable"));					
	 UIPanel *pan = static_cast<UIPanel*>(ul -> getWidgetByName("Panel_8"));
	 pan -> setTouchEnable(false);
}

bool MySelfInfoLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    } 
	data = XQDate::sharedInstance().GetDate("112");
	CSJson::Value &val = data;
	totalpk = val["totalpk"].asInt();
	winPk = val["winpk"].asInt();
	losePk = val["losepk"].asInt();
	goldmodel = val["playergoldmedal"].asInt();
	silverMedal = val["playersilvermedal"].asInt();
	copperMedal = val["playercoppermedal"].asInt();
	medalNumber = val["playermedal"].asInt();
	alikePk = (totalpk-winPk-losePk);
    //载入ui
    initData();
    //绑定ui
    BindingUIItems();
    
    refreshInfo();
    return true;
}


void MySelfInfoLayer::refreshInfo() {

	auto *GoldPic = getSpriteByScore(goldmodel, GoldNumber->getPosition(),1);
	addChild(GoldPic);
	GoldNumber -> removeFromParent();

	auto *SliverPic = getSpriteByScore(silverMedal, Sliver->getPosition(),1);
	addChild(SliverPic);
	Sliver -> removeFromParent();

	auto *brozePic = getSpriteByScore(copperMedal, Broze->getPosition(),1);
	addChild(brozePic);
	Broze -> removeFromParent();

	auto *winPic = getSpriteByScore(winPk, winTimes->getPosition(),1);
	addChild(winPic);
	winTimes -> removeFromParent();

	auto *losePic = getSpriteByScore(losePk, loseTimes->getPosition(),1);
	addChild(losePic);
	loseTimes -> removeFromParent();

	auto *allfightPic = getSpriteByScore(totalpk, allFightTimes->getPosition(),1);
	addChild(allfightPic);
	allFightTimes -> removeFromParent();

	auto *alikePic = getSpriteByScore(alikePk, alike->getPosition(),1);
	this->addChild(alikePic);
	alike-> removeFromParent();
    //
    auto *MedalPic = getSpriteByScore(medalNumber, allMedals -> getPosition(), 2);
    MedalPic -> setScale(1.2);
    addChild(MedalPic);
    allMedals -> removeFromParent();
    //
}

CCSprite* MySelfInfoLayer::getSpriteByScore(long score,  CCPoint p, int kind)
{
    long temp = score;
    //位数,用于设置横坐标偏移量.
    int digit = 0;
    CCSprite* scroeSprite = CCSprite::create();
    scroeSprite ->setPosition(p);
    
    while (temp>0 || (digit==0 && temp==0)) {
        int remainder = temp % 10;
        temp = temp/10;
        CCSprite *m_Sprite;
        CCRect rc;
        CCString str;
	
		 
        if (kind == 1)
            str.initWithFormat("f_%d.png", remainder);
        else
            str.initWithFormat("m_%d.png", remainder);	
        
        m_Sprite = CCSprite::createWithSpriteFrameName(str.getCString());
		if(kind ==1)
			m_Sprite->setPosition(ccp((digit+(digit/3))*(-15), 0));
		else
			m_Sprite->setPosition(ccp((digit+(digit))*(-20), 0));
        scroeSprite->addChild(m_Sprite);
        scroeSprite -> setPosition(ccp(scroeSprite->getPositionX() - 6, scroeSprite->getPositionY()));
        digit++;
    }
    digit--;
    CCArray* array = scroeSprite->getChildren();
    for (int i=0; i<array->count(); i++) {
        CCPoint point = ((CCSprite*)array->objectAtIndex(i))->getPosition();
        point.x += (digit+(digit/3))*15.0;
        ((CCSprite*)array->objectAtIndex(i))->setPosition(point);
    }
    return scroeSprite;
}
