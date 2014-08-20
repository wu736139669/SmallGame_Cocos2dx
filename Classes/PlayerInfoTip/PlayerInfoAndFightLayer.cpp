//
// PlayerInfoAndFightLayer.cpp
// OnceAgain
//
// Created by xiaohai on 14-5-9.
//
//

#include "PlayerInfoAndFightLayer.h"
#include "GameUIExportJson.h"
#include "FightInfoLayer.h"
#include "MySelfInfoLayer.h"

#define FightLayer 1
#define InfoLayer 2
#define CloseBtn 3

CCScene* PlayerInfoAndFightLayer::createScene()
{
    auto scene = CCScene::create();
    auto layer = PlayerInfoAndFightLayer::create();
    scene->addChild(layer);
    return scene;
}
#pragma mark - initData
void PlayerInfoAndFightLayer::initData()
{
    ul = UILayer::create();
    addChild(ul);
    
    auto myLayout = dynamic_cast<Layout*>(GUIReader::shareReader() -> widgetFromJsonFile(uiPlayerInfoAndFightLayer));
    ul -> addWidget(myLayout);
    
}

void PlayerInfoAndFightLayer::BindingUIItems()
{
    Button_1 = static_cast<UIButton*>(ul -> getWidgetByName("MyFightBtn"));
    Button_1 -> setTag(FightLayer);
    Button_1 -> addReleaseEvent(this, coco_releaseselector(PlayerInfoAndFightLayer::ButtonClickCallBack));
    Button_1 -> disable();
    Button_2 = static_cast<UIButton*>(ul -> getWidgetByName("MyInfoBtn"));
    Button_2 -> setTag(InfoLayer);
    Button_2 -> addReleaseEvent(this, coco_releaseselector(PlayerInfoAndFightLayer::ButtonClickCallBack));
    
    Btn_close = static_cast<UIButton*>(ul -> getWidgetByName("BtnClose"));
    Btn_close -> setTag(CloseBtn);
    Btn_close -> setTouchEnable(false);
    Btn_close -> addReleaseEvent(this, coco_releaseselector(PlayerInfoAndFightLayer::ButtonClickCallBack));
    
    TextImage_1 = static_cast<UIImageView*>(ul -> getWidgetByName("Text_1"));
    TextImage_2 = static_cast<UIImageView*>(ul -> getWidgetByName("Text_2"));
    
    InfoNode = static_cast<UIPanel*>(ul -> getWidgetByName("InfoNode"));
    InfoNode -> setVisible(false);
    FightNode = static_cast<UIPanel*>(ul -> getWidgetByName("FightNode"));
    FightNode -> setVisible(false);
    // bind ui images
    
}

bool PlayerInfoAndFightLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plPlayerInfoAndFightNumber);
    CCSize visibleSize = CCDirector::sharedDirector() -> getVisibleSize();
    CCLayerColor *backGround = CCLayerColor::create(ccc4(0, 0, 0, 30));
    backGround->setContentSize(visibleSize);
    backGround->setZOrder(0);
    this -> addChild(backGround);
    //载入ui
    initData();
    //绑定ui
    BindingUIItems();
    
    //创建各个子页面
    creatLayers();
    
    judgeStatu();
    return true;
}

void PlayerInfoAndFightLayer::ButtonClickCallBack(cocos2d::CCObject *p) {
    int tag = ((UIButton*)p) -> getTag();
    if (tag == CloseBtn) {
        this -> removeFromParent();
    }
    else if (tag == FightLayer) {
        Button_1 -> disable();
        Button_2 -> active();
        judgeStatu();
    }
    else {
        Button_2 -> disable();
        Button_1 -> active();
        judgeStatu();
    }
}

void PlayerInfoAndFightLayer::judgeStatu() {
    bool b_1_isAction = Button_1 -> isActive();
    std:: string url_1 = !b_1_isAction?imgmyInfo_1:imgmyInfo_2; 
    std:: string url_2 = !b_1_isAction?imgmyFight_2:imgmyFight_1;
    TextImage_1 -> setTexture(url_1.c_str());
    TextImage_2 -> setTexture(url_2.c_str());
    FightNode -> setVisible(!b_1_isAction);
    InfoNode -> setVisible(b_1_isAction);
    Btn_close -> setTouchEnable(true);
}

void PlayerInfoAndFightLayer::creatLayers() {
    auto *fightLayer = FightInfoLayer::create();
    auto *myselfInfoLayer = MySelfInfoLayer::create();
    InfoNode -> addCCNode(myselfInfoLayer);
    FightNode -> addCCNode(fightLayer);
}

void PlayerInfoAndFightLayer::onExit() {
    CCLayer::onExit();
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(plPlayerInfoAndFightNumber);
}
