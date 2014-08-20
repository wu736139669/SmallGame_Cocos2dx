//
// FightInfoLayer.cpp
// OnceAgain
//
// Created by xiaohai on 14-5-9.
//
//

#include "FightInfoLayer.h"
#include "GameUIExportJson.h"
#include "FightItemLayer.h"
#include "GameShare_Property.h"
#include "PlayerInfoManager.h"
#include "XQDate.h"
#include "ImageDownloader.h"

CCScene* FightInfoLayer::createScene()
{
    auto scene = CCScene::create();
    auto layer = FightInfoLayer::create();
    scene->addChild(layer);
    return scene;
}

#pragma mark - initData
void FightInfoLayer::initData()
{
    ul = UILayer::create();
    addChild(ul);
    
    auto *myLayout = dynamic_cast<Layout*>(GUIReader::shareReader() -> widgetFromJsonFile(uiFightInfoLayer));
    ul -> addWidget(myLayout);
    // add your codes here...
}

void FightInfoLayer::BindingUIItems()
{

	NameLable = static_cast<UILabel*>(ul -> getWidgetByName("NameLabel"));					
	lvLable = static_cast<UILabel*>(ul -> getWidgetByName("LvLable"));					
	PlayerIcon = static_cast<UIImageView*>(ul -> getWidgetByName("PlayerIcon"));			
    newAllScore = static_cast<UILabel*>(ul -> getWidgetByName("AllScore"));					
    myTableView = static_cast<UIPanel*>(ul -> getWidgetByName("tableView"));	
	UIPanel *pan = static_cast<UIPanel*>(ul -> getWidgetByName("Panel_22"));
	pan -> setTouchEnable(false);

}

bool FightInfoLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }    
    //载入ui
    initData();
    //绑定ui
    BindingUIItems();
    
    data = XQDate::sharedInstance().GetDate("112");
   
    playertotalscore = data["playerhistoryscore"].asInt();
    gameinfo = data["gameinfo"];
	playerLv = data["playerlevel"].asInt();
	playerName = data["playername"].asString();
	totalScore = data["playertotalscore"].asInt();
	imgUrl = data["playerimg"].asString();
    creatMyTableView();
    refreshInfo();
    return true;
}

void FightInfoLayer::creatMyTableView() {
    CCTableView *tableView = CCTableView::create(this, myTableView->getContentSize());
    tableView -> setDelegate(this);
    tableView->setDirection(kCCScrollViewDirectionVertical);
    tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    myTableView -> addCCNode(tableView);
}

//定制每个cell的size
CCSize FightInfoLayer::tableCellSizeForIndex(CCTableView *table, unsigned int idx) {
    return CCSize(465, 61);
}
//确定这个tableview的cell行数
unsigned int FightInfoLayer::numberOfCellsInTableView(CCTableView *table){
    return gameinfo.size();
}
//定制每个cell的内容
CCTableViewCell* FightInfoLayer::tableCellAtIndex(CCTableView *table, unsigned int idx) {
    CCTableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = new CCTableViewCell();
        cell->autorelease();
    }
    cell -> removeAllChildren();
    FightItemLayer *layer = FightItemLayer::create();
    layer -> setInfo(gameinfo[idx]);
    cell -> addChild(layer);
    return cell;
}

//刷新表单信息
void FightInfoLayer::refreshInfo() {
    
    //总得分
    auto *newScore = getSpriteByScore(playertotalscore, newAllScore->getPosition(),2);
    newScore -> setScale(0.8);
    addChild(newScore);
    newAllScore -> removeFromParent();

	CCString str;

	str.initWithFormat("Lv %d", playerLv);
	lvLable -> setText(str.getCString());
	NameLable -> setText(playerName.c_str());

	CCSprite *img = CCSprite::create();
	img->setContentSize(CCSize(145, 145));
	img->setAnchorPoint(ccp(0, 0));
	img->setScale(0.8);
	PlayerIcon->addRenderer(img, 10);
	CImageDownloader::GetInstance()->SendHttpRequest(imgUrl.c_str(), img, "1000", 1000);

}


CCSprite* FightInfoLayer::getSpriteByScore(long score,  CCPoint p,int kind)
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
		if(kind==2)
			str.initWithFormat("s_%d.png", remainder);
		else
			str.initWithFormat("f_%d.png", remainder);
        m_Sprite = CCSprite::createWithSpriteFrameName(str.getCString());
        if(kind==2)
			m_Sprite->setPosition(ccp((digit+(digit/3))*(-21), 0));
		else
			 m_Sprite->setPosition(ccp((digit+(digit/3))*(-15), -5));
       
        scroeSprite->addChild(m_Sprite);
        scroeSprite -> setPosition(ccp(scroeSprite->getPositionX() - 6, scroeSprite->getPositionY()));
		if(kind==2)
			m_Sprite->setScale(1.5);
        if (digit%3==0 && digit>0) {
			 CCSprite *comma;
			 if(kind==2)
			 {
				  comma= CCSprite::createWithSpriteFrameName("s_point.png");
				  comma->setPosition(ccp(m_Sprite->getPositionX()+25, -5));
				  scroeSprite->addChild(comma);
				  comma->setScale(1.5);
				  scroeSprite -> setPosition(ccp(scroeSprite->getPositionX() - 10, scroeSprite->getPositionY()));
			 }
			 else
			 {
				 comma= CCSprite::createWithSpriteFrameName("f_point.png");
				 comma->setPosition(ccp(m_Sprite->getPositionX()+19, -10));
				 scroeSprite->addChild(comma);
				 scroeSprite -> setPosition(ccp(scroeSprite->getPositionX() - 6, scroeSprite->getPositionY()));
			 }
        }
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

