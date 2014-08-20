//
//  GameLayerFriendCell.cpp
//  OnceAgain
//
//  Created by mac on 14-4-17.
//
//

#include "GameLayerFriendCell.h"
#include "StringUtil.h"
#include "NumSprite.h"
#include "ImageDownloader.h"
#include "TimeUtil.h"
#include "PlayerInfoManager.h"
#include "NetHttpClient.h"
#include "MsgDefine.h"
#include "NetHttpClient.h"
#include "MsgDefine.h"
#include "PlayerInfoManager.h"
#include "XQDate.h"
#include "PlayerInfoAndFightLayer.h"
GameLayerFriendCell::GameLayerFriendCell()
{
    scoreSprite = NULL;
    cellLyaer = NULL;
    
}
GameLayerFriendCell::~GameLayerFriendCell()
{
    GUIReader::shareReader()->purgeGUIReader();
	DictionaryHelper::shareHelper()->purgeDictionaryHelper();
	ActionManager::shareManager()->purgeActionManager();
}
bool GameLayerFriendCell::init()
{
    cellLyaer = UILayer::create();
    auto myLayout = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile(CStringUtil::convertToUIResPath("FriendScoreCell.json").c_str()));
    cellLyaer->addWidget(myLayout);
    this->addChild(cellLyaer, 0, 100);
    UIImageView* cell = dynamic_cast<UIImageView*>(cellLyaer->getWidgetByName("Cell"));
    this->setContentSize(cell->getContentSize());
    
    UIImageView* cellBg = dynamic_cast<UIImageView*>(cellLyaer->getWidgetByName("GameCell_AvatarBgImg"));
    cellBg -> setTouchEnable(true);
    cellBg -> addReleaseEvent(this, coco_releaseselector(GameLayerFriendCell::getPlayerInfo));
    
    return true;
}

void GameLayerFriendCell::getPlayerInfo(cocos2d::CCObject *p) {
    CSJson::Value msg_body;
    msg_body["playerid"] = CSJson::Value(playerId);
    NetHttpClient::sharedInstance().XQsendHttpRequest(eNetMsgTypePlayerSys, eNetMsgPlayerSysGetPlayerInfoMore, &msg_body, this, coco_myevent(GameLayerFriendCell::getPlayerInfoCallBack));
}

void GameLayerFriendCell::setPlayerId(int num) {
    playerId = num;
}
void GameLayerFriendCell::getPlayerInfoCallBack(cocos2d::CCObject *p) {
    if (target_1 && callBack_1) {
        (target_1->*callBack_1)();
    }
}
void GameLayerFriendCell::setRank(int rank)
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
void GameLayerFriendCell::setName(const char *name)
{
    UILabel* nameLabel = dynamic_cast<UILabel*>(cellLyaer->getWidgetByName("Name"));
    nameLabel->setText(name);
}
void GameLayerFriendCell::setScore(int score)
{
    UIImageView* cell = dynamic_cast<UIImageView*>(cellLyaer->getWidgetByName("Cell"));
    if (scoreSprite) {
        scoreSprite->removeFromParent();
    }
    scoreSprite = NumSprite::getNumSprite(score, "./CocoStudioResources/ResouceNum", 20);
    scoreSprite->setAnchorPoint(ccp(0, 0));
    scoreSprite->setPosition(ccp(245, 40));
    cell->addRenderer(scoreSprite,10);
}
void GameLayerFriendCell::setSendType(FriendSendType type, int time)
{
    UIButton* btn = dynamic_cast<UIButton*>(cellLyaer->getWidgetByName("GameCell_Btn"));
    UIImageView* timeImg = dynamic_cast<UIImageView*>(cellLyaer->getWidgetByName("Time3"));
    UILabelAtlas* label1 =dynamic_cast<UILabelAtlas*>(cellLyaer->getWidgetByName("Time1"));
    UILabelAtlas* label2 =dynamic_cast<UILabelAtlas*>(cellLyaer->getWidgetByName("Time2"));
    
    if (type == FriendChallenge) {
        btn->setTextures("./CocoStudioResources/GameRank/ChallengeBtn.png", "./CocoStudioResources/GameRank/ChallengeBtn.png", "");
        btn->setTouchEnable(true);
        btn->setPressedActionEnabled(true);
        timeImg->setVisible(false);
        label1->setVisible(false);
        label2->setVisible(false);
    }
    if (type == FriendSendTypeSend) {
        btn->setTextures("./CocoStudioResources/FriendScore/Send_1.png", "./CocoStudioResources/FriendScore/Send_1.png","");
        btn->setTouchEnable(true);
        btn->setPressedActionEnabled(true);
        timeImg->setVisible(false);
        label1->setVisible(false);
        label2->setVisible(false);
    }
    if (type == FriendSendTypeNoSend) {
        btn->setTextures("./CocoStudioResources/FriendScore/Forbid_1.png", "./CocoStudioResources/FriendScore/Forbid_1.png","");
        btn->setTouchEnable(false);
        btn->setPressedActionEnabled(false);
        timeImg->setVisible(false);
        label1->setVisible(false);
        label2->setVisible(false);
    }
    if (type == FriendSendTypeIsSend) {
        btn->setTextures("./CocoStudioResources/FriendScore/IsSend_1.png", "./CocoStudioResources/FriendScore/IsSend_1.png","");
        btn->setTouchEnable(false);
        btn->setPressedActionEnabled(false);
        timeImg->setVisible(true);
        label1->setVisible(true);
        label2->setVisible(true);
        
        int hour = time/3600;
        int second1 = (time%3600)/600;
        int second2 = (time%3600)/60%10;
        CCString str;
        str.initWithFormat("%d",hour);
        label1->setStringValue(str.getCString());
        str.initWithFormat("%d%d",second1,second2);
        label2->setStringValue(str.getCString());
    }

}
void GameLayerFriendCell::addSendCallbackFunc(cocos2d::CCObject *target, SEL_ReleaseEvent callfun){
    UIButton* btn = dynamic_cast<UIButton*>(cellLyaer->getWidgetByName("GameCell_Btn"));
    btn->setTag(this->getTag());
    btn->addReleaseEvent(target, callfun);
}

void GameLayerFriendCell::addMySelfCallBack(cocos2d::CCObject *target, SEL_ReleaseEvent callfun, int tag) {
    UIButton* btn = dynamic_cast<UIButton*>(cellLyaer->getWidgetByName("GameCell_Btn"));
    CCString str;
    if (tag == 100) {
        str = "./CocoStudioResources/FriendScore/Send_11.png";
    }
    else {
        str = "./CocoStudioResources/FriendScore/Forbid_1.png";
    }
    btn->setTextures(str.getCString(), str.getCString(),"");
    btn->setTag(tag);
    btn->addReleaseEvent(target, callfun);
}

void GameLayerFriendCell::changePicType(int tag) {
    UIButton* btn = dynamic_cast<UIButton*>(cellLyaer->getWidgetByName("GameCell_Btn"));
    btn->setTag(tag);
    CSJson::Value msg_body;
    msg_body["playerid"] = CSJson::Value(CPlayerInfoMan::sharedInstance().getPlayerInfo().nId);
    
    if (tag == 100) {
        btn->setTextures("./CocoStudioResources/FriendScore/Send_11.png", "./CocoStudioResources/FriendScore/Send_11.png","");
        msg_body["playercanrecvpower"] = CSJson::Value(1);

    }
    else {
        btn->setTextures("./CocoStudioResources/FriendScore/Forbid_1.png", "./CocoStudioResources/FriendScore/Forbid_1.png","");
        msg_body["playercanrecvpower"] = CSJson::Value(0);
    }
    NetHttpClient::sendHttpRequest(eNetMsgTypePlayerSys, eNetMsgPlayerSysSetRiceStatus, &msg_body);
}

void GameLayerFriendCell::setAvatarImg(const char *imgUrl)
{
    UIImageView* cellBg = dynamic_cast<UIImageView*>(cellLyaer->getWidgetByName("GameCell_AvatarBgImg"));
    CCSprite* img =  CCSprite::create();
    img->setContentSize(CCSize(82, 82));
    img->setAnchorPoint(ccp(0, 0));
    cellBg->addRenderer(img, 10);
    CImageDownloader::GetInstance()->SendHttpRequest(imgUrl, img, "1000", 1000);
}
void GameLayerFriendCell::setInfoCallback(cocos2d::CCObject *targer22, SEL_CallFunc callfun)
{
    target_1 = targer22;
    callBack_1 = callfun;
}

void GameLayerFriendCell::setTiemCount(int dt) {
    timeLess = dt;
}

void GameLayerFriendCell::onEnter()
{
    CCLayer::onEnter();

}