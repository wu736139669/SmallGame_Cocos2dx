//
//  GameLayer_NormalScore.cpp
//  OnceAgain
//
//  Created by mac on 14-4-17.
//
//

#include "GameLayer_NormalScore.h"
#include "StringUtil.h"
#include "NumSprite.h"
GameLayer_NormalScore::~GameLayer_NormalScore()
{
    GUIReader::shareReader()->purgeGUIReader();
	DictionaryHelper::shareHelper()->purgeDictionaryHelper();
	ActionManager::shareManager()->purgeActionManager();
}

bool GameLayer_NormalScore::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    ul = UILayer::create();
    Layout* myLayout;
    myLayout  = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile(CStringUtil::convertToUIResPath("GameOverNormal.json").c_str()));
    
    myLayout->setTag(100);
    ul->addWidget(myLayout);
    ul->setContentSize(visibleSize);
    this->addChild(ul, 0, 100);
 
    UIImageView* upImg = dynamic_cast<UIImageView*>(ul->getWidgetByName("UpImg"));
    upImg->runAction(CCRepeatForever::create( CCSequence::create(CCMoveBy::create(0.3, ccp(0,10)),CCMoveBy::create(0.3, ccp(0,-10)),NULL)));

    //获得最高分.
    return true;
}
void GameLayer_NormalScore::setMaxAndResult(int max, int result)
{
    UIImageView* scoreBgImg = dynamic_cast<UIImageView*>(ul->getWidgetByName("ScoreBgImg"));
    
    CCSprite* resultSprite = NumSprite::getNumSprite(result, "./CocoStudioResources/GameOverNormal", 35.0,0.5);
    scoreBgImg->addRenderer(resultSprite, 0);
    resultSprite->setPosition(ccp(0, 20));
    CCSprite* maxScoreSprite = NumSprite::getNumSprite(max, "./CocoStudioResources/GameOverNormal", 35.0,0.5);
    maxScoreSprite->setScale(0.5);
    scoreBgImg->addRenderer(maxScoreSprite, 0);
}