//
// GameTakeRewardLayer.cpp
// OnceAgain
//
// Created by xiaoqiang on 14-5-23.
//
//

#include "GameTakeRewardLayer.h"
#include "GameUIExportJson.h"
#include "XQDate.h"
#include "NetHttpClient.h"
#include "MsgDefine.h"
#include "PlayerInfoManager.h"
GameTakeRewardLayer::GameTakeRewardLayer()
{
    
}

GameTakeRewardLayer::~GameTakeRewardLayer()
{
    
}

CCScene* GameTakeRewardLayer::createScene()
{
    auto scene = CCScene::create();
    auto layer = GameTakeRewardLayer::create();
    scene->addChild(layer);
    return scene;
}

bool GameTakeRewardLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    selectorPic = 0;
    //载入ui
    initData();
    //绑定ui
    BindingUIItems();
    return true;
}

#pragma mark - initData
void GameTakeRewardLayer::initData()
{
    idlist.clear();
    CCString str1;
    str1.initWithFormat("%d%d",eNetMsgTypeMissionSys, eNetMsgMissionSysWeekRewardKind);
    CSJson::Value root = XQDate::sharedInstance().GetDate(str1.getCString());
    
    for (int i = 0; i < root.size(); i ++) {
        CSJson::Value &val = root[i];
        CCLOG("BBBBBBBBB_____%d", val["lotteryid"].asInt());
        idlist.push_back(val["lotteryid"].asInt());
    }
    
    ul = UILayer::create();
    addChild(ul);
    
    auto myLayout = static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("./CocoStudioResources/Reward.json"));
    // add your codes here...
    ul -> addWidget(myLayout);
    
    UIPanel *myPanel = dynamic_cast<UIPanel*>(ul -> getWidgetByName("Panel"));
    myPanel -> setTouchEnable(true);
    myPanel -> addReleaseEvent(this, coco_releaseselector(GameTakeRewardLayer::touchTabelCallBack));
    
    UIImageView *face_1 = dynamic_cast<UIImageView*>(ul -> getWidgetByName("face_1"));
    imgList.push_back(face_1);
    
    UIImageView *face_2 = dynamic_cast<UIImageView*>(ul -> getWidgetByName("face_2"));
    imgList.push_back(face_2);
    
    UIImageView *face_3 = dynamic_cast<UIImageView*>(ul -> getWidgetByName("face_3"));
    imgList.push_back(face_3);
    
    UIImageView *face_4 = dynamic_cast<UIImageView*>(ul -> getWidgetByName("face_4"));
    imgList.push_back(face_4);
    
    UIImageView *face_5 = dynamic_cast<UIImageView*>(ul -> getWidgetByName("face_5"));
    imgList.push_back(face_5);
    
    UIImageView *face_6 = dynamic_cast<UIImageView*>(ul -> getWidgetByName("face_6"));
    imgList.push_back(face_6);
    
    CCString str;
    for (int i = 0; i < imgList.size(); i ++) {
        UIPanel *face_1_1 = UIPanel::create();
        face_1_1 -> setAnchorPoint(ccp(0.5, 0.5));
        face_1_1 -> setSize(imgList[i] -> getContentSize());
        face_1_1 -> setPosition(imgList[i] -> getPosition());
        face_1_1 -> setTouchEnable(true);
        face_1_1 -> setTag(i + 1);
        face_1_1 -> addReleaseEvent(this, coco_releaseselector(GameTakeRewardLayer::picClick));
        str.initWithFormat("./CocoStudioResources/takeReward/images/face_%d.png", i + 1);
        auto *pic = CCSprite::create(str.getCString());
        pic -> setAnchorPoint(ccp(0, 0));
        face_1_1 -> addCCNode(pic);
        ul -> addWidget(face_1_1);
        imgList[i] -> removeFromParent();
        myImgList.push_back(pic);
    }
    imgList.clear();
}

void GameTakeRewardLayer::BindingUIItems()
{
    // bind ui images
}

void GameTakeRewardLayer::picClick(CCObject *p) {
    int tag = ((UIImageView*)p) -> getTag();
    if (selectorPic == tag) {
        //打开盒子。请求后端
        for (int i = 0;  i < idlist.size(); i++) {
            CCLOG("AAAAAAAAAAAAAAAAAAAAAAAA________%d",idlist[i]);
        }
        CSJson::Value msg_body;
        msg_body["playerid"] = CSJson::Value(CPlayerInfoMan::sharedInstance().getPlayerInfo().nId);
        msg_body["lotteryid"] = CSJson::Value(idlist[selectorPic - 1]);
        NetHttpClient::sharedInstance().XQsendHttpRequest(eNetMsgTypeMissionSys, eNetMsgMissionSysWeekGetReward, &msg_body, this, coco_myevent(GameTakeRewardLayer::touchTabelCallBack));
    }
    else {
        selectorPic = tag;
        picRunAction();
    }
}

void GameTakeRewardLayer::picRunAction() {
    for (int i = 0; i < myImgList.size(); i ++) {
        myImgList[i] -> stopAllActions();
    }
    
    CCAnimation* pAni = CCAnimation::create();
    CCString str;
    for (int i = 1; i <=2; i ++)
    {
        str.initWithFormat("./CocoStudioResources/takeReward/images/face_%d_%d.png",selectorPic, i);
        pAni->addSpriteFrameWithFileName(str.getCString());
    }
    pAni -> setDelayPerUnit(0.12f);
    pAni -> setLoops(1);
    myImgList[selectorPic -1] -> runAction(CCRepeatForever::create(CCAnimate::create(pAni)));
}

void GameTakeRewardLayer::touchTabelCallBack(CCObject *p) {
    if (target && callback) {
        (target->*callback)(this);
    }
}

void GameTakeRewardLayer::setCallBack(cocos2d::CCObject *p, SEL_CallFuncO call) {
    target = p;
    callback = call;
}
