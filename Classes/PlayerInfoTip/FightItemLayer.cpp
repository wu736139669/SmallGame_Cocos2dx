//
// FightItemLayer.cpp
// OnceAgain
//
// Created by xiaohai on 14-5-9.
//
//

#include "FightItemLayer.h"
#include "GameUIExportJson.h"
#include "GameShare_Property.h"
#include "PlayerInfoManager.h"
#include "GameTableLayer.h"
CCScene* FightItemLayer::createScene()
{
    auto scene = CCScene::create();
    auto layer = FightItemLayer::create();
    scene->addChild(layer);
    return scene;
}
#pragma mark - initData
void FightItemLayer::initData()
{
    // add your codes here...
    ul = UILayer::create();
    addChild(ul);
    
    auto *mylayout = dynamic_cast<Layout*>(GUIReader::shareReader() -> widgetFromJsonFile(uiFightItemLayer));
    ul -> addWidget(mylayout);
}

void FightItemLayer::BindingUIItems()
{
    
    Gameicon = static_cast<UIImageView*>(ul -> getWidgetByName("Image_2"));
    GameName = static_cast<UILabel*>(ul -> getWidgetByName("Label_3"));
    ScoreNumber = static_cast<UILabel*>(ul -> getWidgetByName("Label_4"));
    // bind ui images
}

bool FightItemLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    //载入ui
    initData();
    //绑定ui
    BindingUIItems();
    return true;
}

void FightItemLayer::setInfo(CSJson::Value data) {
    std::string str_1;
    std::string str_2;
    int GameType = data["gameid"].asInt();
    switch (GameType) {
        case Game_Memory:
            str_1 = "./CocoStudioResources/GameMemoryAvatar.png";
            str_2 = "./CocoStudioResources/GameMemoryName.png";
            break;
        case Game_Jelly:
            str_1 = "./CocoStudioResources/GameRightTouchAvatar.png";
            str_2 = "./CocoStudioResources/GameRightTouchName.png";
            break;
        case Game_Fruit:
            str_1 = "./CocoStudioResources/GameFruitAvatar.png";
            str_2 = "./CocoStudioResources/GameFruitName.png";
            break;
            
        case Game_Link:
            str_1 = "./CocoStudioResources/GameLinkAvatar.png";
            str_2 = "./CocoStudioResources/GameLinkName.png";
            break;
 		case Game_TaiKo:
            str_1 = "./CocoStudioResources/taiko_icon.png";
            str_2 = "./CocoStudioResources/taiko_name.png";
 			break;
        case Game_SanXiao:
            str_1 = "./CocoStudioResources/GameSanXiaoIcon.png";
            str_2 = "./CocoStudioResources/taiko_name.png";
        default:
            break;
    }
    auto *IconPic = CCSprite::create(str_1.c_str());
    auto *NamePic = CCSprite::create(str_2.c_str());
    NamePic -> setPosition(GameName -> getPosition());
    NamePic -> setScale(0.65);
    IconPic -> setScale(1.37);
    Gameicon -> addCCNode(IconPic);
    addChild(NamePic);
    GameName -> removeFromParent();
    
//    int score;
//    for (int i = 0; i < CPlayerInfoMan::sharedInstance().getPlayerInfo().mGameData.size(); ++i)
//    {
//        if(CPlayerInfoMan::sharedInstance().getPlayerInfo().mGameData[i].gameId == GameType)
//        {
//            score = CPlayerInfoMan::sharedInstance().getPlayerInfo().mGameData[i].highestScore;
//            break;
//        }
//    }
    auto *ScorePic = getSpriteByScore(data["highestscore"].asInt());
    ScorePic -> setScale(0.8);
    addChild(ScorePic);
    ScoreNumber -> removeFromParent();
}

CCSprite* FightItemLayer::getSpriteByScore(long score)
{
    long temp = score;
    //位数,用于设置横坐标偏移量.
    int digit = 0;
    CCSprite* scroeSprite = CCSprite::create();
    scroeSprite ->setPosition(ScoreNumber->getPosition());
    
    while (temp>0 || (digit==0 && temp==0)) {
        int remainder = temp % 10;
        temp = temp/10;
        CCSprite *m_Sprite;
        CCRect rc;
        CCString str;
        str.initWithFormat("f_%d.png", remainder);
        m_Sprite = CCSprite::createWithSpriteFrameName(str.getCString());
        
        m_Sprite->setPosition(ccp((digit+(digit/3))*(-18), 0));
        scroeSprite->addChild(m_Sprite);
        scroeSprite -> setPosition(ccp(scroeSprite->getPositionX() - 6, scroeSprite->getPositionY()));
        if (digit%3==0 && digit>0) {
            CCSprite *comma = CCSprite::createWithSpriteFrameName("f_point.png");;
            comma->setPosition(ccp(m_Sprite->getPositionX()+23, -2));
            scroeSprite->addChild(comma);
            scroeSprite -> setPosition(ccp(scroeSprite->getPositionX() - 6, scroeSprite->getPositionY()));
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

