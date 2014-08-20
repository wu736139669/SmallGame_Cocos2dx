//
//  GameTableLayer.cpp
//  ChallengesMaster
//
//  Created by mac on 14-2-21.
//
//

#include "GameTableLayer.h"

#include "Constant.h"
#include "GameShare_Property.h"
#include "Gamelist.h"
#include "GameShare_Data.h"
#include "TaikoScene.h"
#include "Scene_GameItem.h"
#include "StringUtil.h"
#include "PlayerInfoManager.h"
#include "NetPacket.h"
#include "MsgDefine.h"
#include "GameLayer_Tag.h"
//#include "ComData.h"
#include "DialogManager.h"

IMPLEMENT_DLG_ID(GameTableLayer,GameTable_Tag);

using namespace cocos2d::extension;
enum GameTableLayer_Tag{
    Table_tag = 101,
    Score_Tag
};
GameTableLayer::~GameTableLayer(void)
{
    GUIReader::shareReader()->purgeGUIReader();
    DictionaryHelper::shareHelper()->purgeDictionaryHelper();
    ActionManager::shareManager()->purgeActionManager();
}
GameTableLayer::GameTableLayer(void)
{
    riceBar = NULL;
}
void GameTableLayer::onEnter()
{
    CCLayer::onEnter();
}
bool GameTableLayer::init()
{
    if (!CCLayer::init()) {
        return false;
    }

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //背景.
    UILayer *ul = UILayer::create();
    addChild(ul);
    auto *myLayout = dynamic_cast<Layout*>(GUIReader::shareReader() -> widgetFromJsonFile("./CocoStudioResources/GameListBackGround.json"));
    ul -> addWidget(myLayout);
    UIImageView *tableBg = static_cast<UIImageView*>(ul -> getWidgetByName("Image_2"));
    riceBar = GameLayer_RiceBar::create();

    riceBar = GetDlgPtr(GameLayer_RiceBar);
    riceBar->setPosition(ccp(0,85));
    addChild(riceBar, 5);
    
    
    //Game List
    CCTableView* tableView = CCTableView::create(this,CCSizeMake(GAMETABLE_WEIDTH, GAMETABLE_HEIGH*6-15));
    tableView->setPosition(ccp(52, tableBg->getContentSize().height/2- 55));
    //Set Direction
    tableView->setDirection(kCCScrollViewDirectionVertical);
    tableView -> setTouchEnabled(true);

    tableView->setAnchorPoint(CCPointZero);
    
    tableView->setTag(Table_tag);
    // Order From Top To Bottom
    tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    
    tableView->setDelegate(this);
    
    tableView->reloadData();
//    tableView->setTag(Table_tag);
    this->addChild(tableView, 100);
   

//    //Top Img
    return true;
    
}
#pragma mark CCTableViewDelegate
CCSize GameTableLayer::cellSizeForTable(CCTableView *table){
    
    return CCSizeMake(table->getContentSize().width, 105);
    
}

CCTableViewCell* GameTableLayer::tableCellAtIndex(CCTableView *table, unsigned int idx){
    
    CCTableViewCell *cell = table->dequeueCell();
    
    if(!cell){
        
        cell = new CCTableViewCell();
        
        cell->autorelease();
        
    }
    cell->removeAllChildrenWithCleanup(true);
    
    if (idx >= GAMENUM) {
        CCSprite* moreGame = CCSprite::create("./CocoStudioResources/MoreGameImg.png");
        moreGame->setAnchorPoint(CCPointZero);
        cell->addChild(moreGame);
        return cell;
    }
    UILayer* cellLyaer = UILayer::create();
    auto myLayout = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile(CStringUtil::convertToUIResPath("GameCell.json").c_str()));
    cellLyaer->addWidget(myLayout);
    cell->addChild(cellLyaer, 0, 100);
    
    UIImageView* memoryAvatar = dynamic_cast<UIImageView*>(cellLyaer->getWidgetByName("GameCell_AvatarBgImg"));
    
    
    UIImageView* nameImg = dynamic_cast<UIImageView*>(cellLyaer->getWidgetByName("GameCell_NameImg"));
    nameImg->setAnchorPoint(ccp(0, 0));
    nameImg->setPosition(ccp(nameImg->getPosition().x-80, nameImg->getPosition().y-10));
    //按钮
    UIButton* startBtn = dynamic_cast<UIButton*>(cellLyaer->getWidgetByName("GameCell_StartBtn"));
    startBtn -> setTextures("GameStarBtn.png", "GameStarBtn.png", "GameStarBtn.png");
    startBtn->setTag(idx+1);
    startBtn->setPressedActionEnabled(true);
    startBtn->addReleaseEvent(this, coco_releaseselector(GameTableLayer::beginGame));
    
    //分数
    CCSprite* scoreSprite;
    long score = 0;
    switch (idx+1) {
        case Game_Memory:
            memoryAvatar->setTexture("./CocoStudioResources/GameMemoryAvatar.png");
            nameImg->setTexture("./CocoStudioResources/GameMemoryName.png");
            break;
        case Game_Jelly:
            
            memoryAvatar->setTexture("./CocoStudioResources/GameRightTouchAvatar.png");
            nameImg->setTexture("./CocoStudioResources/GameRightTouchName.png");

            break;
        case Game_Fruit:
            memoryAvatar->setTexture("./CocoStudioResources/GameFruitAvatar.png");
            nameImg->setTexture("./CocoStudioResources/GameFruitName.png");
            break;
            
        case Game_Link:
            memoryAvatar->setTexture("./CocoStudioResources/GameLinkAvatar.png");
            nameImg->setTexture("./CocoStudioResources/GameLinkName.png");
            break;
 		case Game_TaiKo:
 			memoryAvatar->setTexture("./CocoStudioResources/taiko_icon.png");
 			nameImg->setTexture("./CocoStudioResources/taiko_name.png");
 			break;
        case Game_SanXiao:
            memoryAvatar->setTexture("./CocoStudioResources/GameSanXiaoIcon.png");
            nameImg->setTexture("./CocoStudioResources/GameSanXiaoIcon_name.png");
        default:
            break;
    }
    for (int i = 0; i < CPlayerInfoMan::sharedInstance().getPlayerInfo().mGameData.size(); ++i)
    {
        if (idx+1 == Game_SanXiao) {
            score = 0;
        }
        if(CPlayerInfoMan::sharedInstance().getPlayerInfo().mGameData[i].gameId == idx+1)
        {
            score = CPlayerInfoMan::sharedInstance().getPlayerInfo().mGameData[i].highestScore;
            break;
        }
    }
    
    if (score == 0) {
        CCLabelTTF *label = CCLabelTTF::create("快来考验你的眼疾手快~", "", 21);
        ccColor3B color3 = {0xf5,0x98,0x16};
        label->setColor(color3);
        label->setPosition(ccp(235, 25));
        cell->addChild(label);
    }else{
        scoreSprite = this->getSpriteByScore(score);
        scoreSprite->setTag(Score_Tag);
        scoreSprite->setPosition(ccp(135, 25));
        scoreSprite->setAnchorPoint(CCPointZero);
        cell->addChild(scoreSprite);
    }

    cell->setTag(idx);
    
    
    return cell;
    
}

unsigned int GameTableLayer::numberOfCellsInTableView(CCTableView *table){
    
    return GAMENUM+1;
    
}
void GameTableLayer::tableCellHighlight(cocos2d::extension::CCTableView *table, cocos2d::extension::CCTableViewCell *cell){
    
}
void GameTableLayer::tableCellUnhighlight(cocos2d::extension::CCTableView *table, cocos2d::extension::CCTableViewCell *cell){
    
}
void GameTableLayer::tableCellTouched(CCTableView* table, CCTableViewCell* cell){
    
//        CCLog("tableCellTouched");
    
}

void GameTableLayer::scrollViewDidZoom(CCScrollView* view){
    
//        CCLOG("scrollViewDidZoom");
    
}
void GameTableLayer::scrollViewDidScroll(cocos2d::extension::CCScrollView* view){
    

//    if (view->getContentOffset().y >= 100.0) {
//        view->getContainer()->setPosition(ccp(view->getContentOffset().x, 101.0));
//    }
//    if (view->getContentOffset().y <= -1000.0) {
//        view->getContainer()->setPosition(ccp(view->getContentOffset().x, -1001.0));
//    }
}
void GameTableLayer::beginGame(CCObject *object){
    UIButton* button = (UIButton*)object;
    GameShare_Global::shareGlobal()->gameType = (e_GameType)button->getTag();
    if (GameShare_Global::shareGlobal()->loginType != LoginType_Tourist) {
        CCScene *scene_GameItem = Scene_GameItem::scene();
        CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.4, scene_GameItem));
    }else{
        CCScene* scene = GameShare_Scene::getGameSceneByType(GameShare_Global::shareGlobal()->gameType);
        CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.4, scene));
    }
}
void GameTableLayer::reFresh()
{
    if (this->getChildByTag(Table_tag)) {
        ((CCTableView*)this->getChildByTag(Table_tag))->reloadData();
    }
}
CCSprite* GameTableLayer::getSpriteByScore(long score)
{
    long temp = score;
    //位数,用于设置横坐标偏移量.
    int digit = 0;
    CCSprite* scroeSprite = CCSprite::create();
    
    while (temp>0 || (digit==0 && temp==0)) {
        int remainder = temp % 10;
        temp = temp/10;
        CCSprite *m_Sprite;
        CCRect rc;
        switch(remainder)
        {
            case 0:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/ScoreNumZero.png");
                break;
            }
            case 1:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/ScoreNumOne.png");
                break;
            }
            case 2:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/ScoreNumTwo.png");
                break;
            }
            case 3:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/ScoreNumThree.png");
                break;
            }
            case 4:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/ScoreNumFour.png");
                break;
            }
            case 5:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/ScoreNumFive.png");
                break;
            }
            case 6:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/ScoreNumSix.png");
                break;
            }
            case 7:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/ScoreNumSeven.png");
                break;
            }
            case 8:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/ScoreNumEight.png");
                break;
            }
            case 9:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/ScoreNumNine.png");
                
                break;
            }
            default:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/ScoreNumZero.png");
                break;
            }
        }
        
        m_Sprite->setPosition(ccp((digit+(digit/3))*(-15), 0));
        scroeSprite->addChild(m_Sprite);
        if (digit%3==0 && digit>0) {
            CCSprite *comma = CCSprite::create("./CocoStudioResources/ScoreNumComma.png");;
            comma->setPosition(ccp(m_Sprite->getPositionX()+15, -10));
            scroeSprite->addChild(comma);
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

bool GameTableLayer::onPackageFilter(void *pDataPkg) {
	CResponsePacket* pPkt = (CResponsePacket*)pDataPkg;
	unsigned int unMsgType = pPkt->getMsgType();
	unsigned int unMsgCode = pPkt->getMsgCode();
	//网络数据传输完成
	if (pPkt->getDataState() == eNetMsgDataStateComplete)
	{
		if (unMsgType == eNetMsgTypePlayerSys)
		{
			if (unMsgCode == eNetMsgPlayerSysBugGem)
			{
//				reSetDiamondNum(CPlayerInfoMan::sharedInstance().getPlayerInfo().nGem);
			}
            if (unMsgCode == eNetMsgPlayerSysChgGold)
			{
//				reSetDiamondNum(CPlayerInfoMan::sharedInstance().getPlayerInfo().nGem);
//                reSetGoldNum(CPlayerInfoMan::sharedInstance().getPlayerInfo().nMoney);
			}
            if (unMsgCode == eNetMsgPlayerSysChgTiLi)
			{
//				reSetDiamondNum(CPlayerInfoMan::sharedInstance().getPlayerInfo().nGem);
			}
		}
        if (pPkt->getDataState() == eNetMsgTypeGameSys)
        {
             if (unMsgCode == eNetMsgGameSysGetMax)
             {
                 this->reFresh();
             }
            if (unMsgCode == eNetMsgGameSysSetMax)
            {
                this->reFresh();
            }
        }
        
		
	}
	return true;
}