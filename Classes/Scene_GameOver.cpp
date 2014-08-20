//
//  Scene_GameOver.cpp
//  OnceAgain
//
//  Created by xiaohai on 14-2-21.
//
//

#include "Scene_GameOver.h"
#include "Gamelist.h"
#include "StringUtil.h"
#include "GameLayer_MaxScore.h"
#include "GameLayer_LvUp.h"
#include "GameLayer_NormalScore.h"
#include "PlayerInfoManager.h"
#include "GameUIExportJson.h"
#include "GameMedalLayer.h"
#include "GameLayerPk.h"
#include "GameLayerPk2.h"
#include "PkSysManager.h"
#include "XQDate.h"
#include "GameLayer_Resource.h"
#include "GameMedalItemLayer.h"
#include "GameLayer_RiceBar.h"

enum Btn_Key{
    TagMaxScore = 100,
    TagPk = 101,
    LevelUp_Btn = 102
};
CCScene* Scene_GameOver::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    Scene_GameOver *layer = Scene_GameOver::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    
    return scene;
}
Scene_GameOver::Scene_GameOver()
{
    levelSprite = NULL;
    resultSprite = NULL;
    maxScoreSprite = NULL;
    ul = NULL;
    obtainTitleUl = NULL;
    taskUl = NULL;
}
Scene_GameOver::~Scene_GameOver()
{
	GUIReader::shareReader()->purgeGUIReader();
	DictionaryHelper::shareHelper()->purgeDictionaryHelper();
	ActionManager::shareManager()->purgeActionManager();

    CC_SAFE_RELEASE(ul);
    CC_SAFE_RELEASE(obtainTitleUl);
    
    //结束时候设置等级.
    CPlayerInfoMan::sharedInstance().getPlayerInfo().nLevel = GameShare_Global::shareGlobal()->gameProperty.playerlevel;
//    CC_SAFE_RELEASE(taskUl);
    
}
// on "init" you need to initialize your instance
bool Scene_GameOver::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    layerList.clear();
    layerCount = 0;
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    //background
    auto* pSpriteBG = CCSprite::create("./CocoStudioResources/GameOverBg.jpg");
    pSpriteBG->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    pSpriteBG->setColor(ccGRAY);
    this->addChild(pSpriteBG, 0);
    
    
    return true;
}
void Scene_GameOver::onEnter()
{
    CCLayer::onEnter();
    this->setResultAndMaxScore(resultScore, maxScore);
	judgeShowLayers();
}

void Scene_GameOver::judgeShowLayers() {
    //判断挑战界面显示与
    if (CPkSysManager::sharedInstance().pkType == PkTypeReceive) {
        auto* layer = GameLayerPk::create();
        layer->addSureCallbackFunc(this, callfunc_selector(Scene_GameOver::sureBtnCallBack));
        layer -> retain();
        layerList.push_back(layer);
    }
    if (CPkSysManager::sharedInstance().pkType == PkTypeSend) {
        auto* layer = GameLayerPk2::create();
        layer->addSureCallbackFunc(this, callfunc_selector(Scene_GameOver::sureBtnCallBack));
        layer -> retain();
        layerList.push_back(layer);
    }
    // 判断升级界面显示与否
    int nowLv = CPlayerInfoMan::sharedInstance().getPlayerLevel();
    sGameProperty& gameProperty = GameShare_Global::shareGlobal()->gameProperty;
    int nowlv_1 = gameProperty.playerlevel;
    if (nowlv_1 > nowLv) {
        auto *lvUp =  GameLayer_LvUp::create();
        lvUp->addSureCallback(this, callfunc_selector(Scene_GameOver::sureBtnCallBack));
        lvUp -> retain();
        lvUp->setLv(nowlv_1);
        layerList.push_back(lvUp);
		if(CPlayerInfoMan::sharedInstance().getPlayerInfo().nPower<5){
			GameLayer_RiceBar *Rice = GameLayer_RiceBar::create();
			 Rice->setRiceNum(CPlayerInfoMan::sharedInstance().getPlayerInfo().nPower);
		}
    }
    //判断勋章界面显示与否
	if(CTaskMan::sharedInstance().isNewDayTaskComplate(GameShare_Global::shareGlobal()->gameType))
	{
        auto *layer_1 = GameMedalLayer::create();
        layer_1 -> retain();
		layer_1->m_bSetBadge = true;
        layer_1 -> setCallBackByGameFinish(this, callfunc_selector(Scene_GameOver::sureBtnCallBack));
        layer_1 -> setGameType(GameShare_Global::shareGlobal()->gameType);
        layerList.push_back(layer_1);
		
		//layer_1->SetBadge();
    }
    sureBtnCallBack();
}
void Scene_GameOver::sureBtnCallBack()
{
    if (layerCount == layerList.size()) {
        layerList[layerCount - 1] -> release();
        CCDirector::sharedDirector()->popScene();
    }
    else {
        if (layerCount != 0) {
            layerList[layerCount - 1] -> release();
            layerList[layerCount - 1] -> removeFromParent();
        }
        this -> addChild(layerList[layerCount]);
        layerCount ++;
    }
}

void Scene_GameOver::menuOkCallBack(CCObject* pSender)
{
    CCDirector::sharedDirector()->popScene();
}

void Scene_GameOver::menuRestartCallBack(CCObject* pSender)
{
    //消耗体力,纪录体力消耗时间
    if (CPlayerInfoMan::sharedInstance().getPlayerInfo().nPower == 5) {
//        CPlayerInfoMan::sharedInstance().getPlayerInfo().riceEndTime = CTimeUtil::GetSystemTimeStamp();
        CPlayerInfoMan::sharedInstance().getPlayerInfo().riceEndTime = 480;
    }
    CPlayerInfoMan::sharedInstance().RequestUseRice();
    CCScene *gameScene = GameShare_Scene::getGameSceneByType(GameShare_Global::shareGlobal()->gameType);
    
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.4, gameScene));
}

#pragma mark num sprite

void Scene_GameOver::setResultAndMaxScore(long resultScore, long maxScore)
{
	auto *layer = GameLayer_MaxScore::create();

	// 判断升级界面显示与否
	int nowLv = CPlayerInfoMan::sharedInstance().getPlayerLevel();
	sGameProperty& gameProperty = GameShare_Global::shareGlobal()->gameProperty;
	int nowlv_1 = gameProperty.playerlevel;

	if (CPkSysManager::sharedInstance().pkType == PkTypeReceive||CPkSysManager::sharedInstance().pkType == PkTypeSend||nowlv_1 > nowLv||CTaskMan::sharedInstance().isNewDayTaskComplate(GameShare_Global::shareGlobal()->gameType))
	{
		layer->getButton(true);
	}
	else
		layer->getButton(false);
    layer->addSureCallbackFunc(this, callfunc_selector(Scene_GameOver::sureBtnCallBack));
    layer->setMaxScore(maxScore);
    layer -> retain();
    layer->setResultScore(resultScore);
    layerList.push_back(layer);
    return;
}




