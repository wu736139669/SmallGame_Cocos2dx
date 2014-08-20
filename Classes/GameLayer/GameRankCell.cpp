//
//  GameRankCell.cpp
//  OnceAgain
//
//  Created by mac on 14-4-24.
//
//

#include "GameRankCell.h"
#include "StringUtil.h"
#include "NumSprite.h"
#include "ImageDownloader.h"

GameRankCell::GameRankCell()
{
    scoreSprite = NULL;
    cellLyaer = NULL;
}
GameRankCell::~GameRankCell()
{
    GUIReader::shareReader()->purgeGUIReader();
	DictionaryHelper::shareHelper()->purgeDictionaryHelper();
	ActionManager::shareManager()->purgeActionManager();
}
bool GameRankCell::init()
{
    cellLyaer = UILayer::create();
    auto myLayout = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile(CStringUtil::convertToUIResPath("GameRankCell.json").c_str()));
    cellLyaer->addWidget(myLayout);
    this->addChild(cellLyaer, 0, 100);
    UIImageView* cell = dynamic_cast<UIImageView*>(cellLyaer->getWidgetByName("Cell"));
    this->setContentSize(cell->getSize());
    
    return true;
}
void GameRankCell::setRank(int rank)
{
    if (rank == 1) {
        return;
    }
    UIImageView* rankImg = dynamic_cast<UIImageView*>(cellLyaer->getWidgetByName("RankImg"));
    UILabelAtlas* numLabel = dynamic_cast<UILabelAtlas*>(cellLyaer->getWidgetByName("NumLabel"));
    numLabel->setVisible(false);
    if (rank == 2) {
        rankImg->setTexture("./CocoStudioResources/FriendScore/Rank2.png");
    }
    if (rank == 3) {
        rankImg->setTexture("./CocoStudioResources/FriendScore/Rank3.png");
    }
    if (rank > 3) {
        CCString str;
        str.initWithFormat("%d",rank);
        rankImg->setVisible(false);
        numLabel->setVisible(true);
        numLabel->setStringValue(str.getCString());
        //        numLabel->set
    }
}
void GameRankCell::setName(const char *name)
{
    UILabel* nameLabel = dynamic_cast<UILabel*>(cellLyaer->getWidgetByName("Name"));
    nameLabel->setText(name);
}
void GameRankCell::setScore(int score)
{
    UIImageView* cell = dynamic_cast<UIImageView*>(cellLyaer->getWidgetByName("Cell"));
    if (scoreSprite) {
        scoreSprite->removeFromParent();
    }
    scoreSprite = NumSprite::getNumSprite(score, "./CocoStudioResources/ResouceNum", 20);
    scoreSprite->setScale(0.7);
    scoreSprite->setAnchorPoint(ccp(0, 0));
    scoreSprite->setPosition(ccp(230, 40));
    cell->addRenderer(scoreSprite,10);
}

void GameRankCell::addSendCallbackFunc(cocos2d::CCObject *target, SEL_ReleaseEvent callfun){

    UIButton* btn = dynamic_cast<UIButton*>(cellLyaer->getWidgetByName("GameCell_Btn"));
    btn->setTag(this->getTag());
    btn->addReleaseEvent(target, callfun);
    btn->setPressedActionEnabled(true);
    if (target==NULL) {
        btn->setTouchEnable(false);
        btn->setVisible(false);
    }
}
void GameRankCell::setAvatarImg(const char *imgUrl)
{
    UIImageView* cellBg = dynamic_cast<UIImageView*>(cellLyaer->getWidgetByName("GameCell_AvatarBgImg"));
    CCSprite* img =  CCSprite::create();
    img->setContentSize(CCSize(82, 82));
    img->setAnchorPoint(ccp(0, 0));
    cellBg->addRenderer(img, 0);
    CImageDownloader::GetInstance()->SendHttpRequest(imgUrl, img, "1000", 1000);
}