//
//  GameShare_Pause.cpp
//  OnceAgain
//
//  Created by mac on 14-3-4.
//
//

#include "GameShare_Pause.h"
#include "GameShare_Global.h"
#include "Gamelist.h"
#include "StringUtil.h"
#include "PlayerInfoManager.h"

GameShare_Pause::~GameShare_Pause()
{
    GUIReader::shareReader()->purgeGUIReader();
    DictionaryHelper::shareHelper()->purgeDictionaryHelper();
    ActionManager::shareManager()->purgeActionManager();
}
CCScene* GameShare_Pause::scene()
{
    
    
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameShare_Pause *layer = GameShare_Pause::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
CCScene* GameShare_Pause::scene(CCRenderTexture *spr, bool isFlip)
{
    
    
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSprite *_spr = CCSprite::createWithTexture(spr->getSprite()->getTexture());
    _spr->setPosition(ccp(size.width/2, size.height/2));
    _spr->setFlipY(isFlip);
    _spr->setColor(ccGRAY);
    scene->addChild(_spr);
    // 'layer' is an autorelease object
    GameShare_Pause *layer = GameShare_Pause::create();
//    layer->setPosition(ccp(size.width/2, size.height/2));
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool GameShare_Pause::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    

    //系统设置界面.
    pauseLayer = UILayer::create();
    auto pauseLayout = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile(CStringUtil::convertToUIResPath("Pause.json").c_str()));
    pauseLayer->addWidget(pauseLayout);
    //    sysSet->setVisible(true);
    this->addChild(pauseLayer, 0, 101);
    
//    this->setTouchEnabled(true);
    this->setVisible(true);
    return true;
}
void GameShare_Pause::setVisible(bool visible)
{
    CCLayer::setVisible(visible);
    UIPanel* dayLoginPanel = dynamic_cast<UIPanel*>(pauseLayer->getWidgetByName("Pause"));
    dayLoginPanel->setTouchEnable(visible);
}
void GameShare_Pause::continueGame(cocos2d::CCObject *object)
{
    if (!CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    }
    CCDirector::sharedDirector()->popScene();
    
}
void GameShare_Pause::newGame(cocos2d::CCObject *object)
{
//    CCScene *gameScene = GameShare_Scene::getGameSceneByType(GameShare_Global::shareGlobal()->gameType);
//
//    CCDirector::sharedDirector()->popScene();
//    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.4, gameScene));
    
    
}
void GameShare_Pause::quitGame(cocos2d::CCObject *object)
{
    CCDirector::sharedDirector()->popToSceneStackLevel(2);
}

void GameShare_Pause::setContinueCallbackFunc(cocos2d::CCObject *target, SEL_CallFuncO callfun)
{
    //继续开始按钮.
    UIButton* resumeBtn = dynamic_cast<UIButton*>(pauseLayer->getWidgetByName("ResumeBtn"));
    resumeBtn->addReleaseEvent(target, callfun);
    resumeBtn->setPressedActionEnabled(true);
}
void GameShare_Pause::setQuitGameCallbackFunc(cocos2d::CCObject *target, SEL_CallFuncO callfun)
{
    //退出按钮.
    UIButton* quitBtn = dynamic_cast<UIButton*>(pauseLayer->getWidgetByName("QuitBtn"));
    quitBtn->addReleaseEvent(target, callfun);
    quitBtn->setPressedActionEnabled(true);
}
void GameShare_Pause::setNewGameCallbackFunc(cocos2d::CCObject *target, SEL_CallFuncO callfun)
{

//    CPlayerInfoMan::sharedInstance().RequestUseRice();
    //重新开始按钮.
    UIButton* againBtn = dynamic_cast<UIButton*>(pauseLayer->getWidgetByName("AgainBtn"));
    againBtn->addReleaseEvent(target, callfun);
    againBtn->setPressedActionEnabled(true);
}
void GameShare_Pause::setHelpCallbackFunc(cocos2d::CCObject *target, SEL_CallFuncO callfun)
{
	//重新开始按钮.
	UIButton* againBtn = dynamic_cast<UIButton*>(pauseLayer->getWidgetByName("HelpBtn"));
	againBtn->addReleaseEvent(target, callfun);
	againBtn->setPressedActionEnabled(true);
}