//
//  Scene_Reward.cpp
//  OnceAgain
//
//  Created by mac on 14-4-17.
//
//

#include "Scene_Reward.h"
#include "StringUtil.h"
#include "GameLayerFriendList.h"
#include "GameLayerFriendTaskList.h"
#include "GameLayerGameRank.h"
#include "GameLayerSysInfo.h"
CCScene* Scene_Reward::scene()
{
    // 'scene' auto release memory
    CCScene *scene = CCScene::create();
    // 'layer' auto release memory
    Scene_Reward *layer = Scene_Reward::create();
    scene->addChild(layer);
    return scene;
}
Scene_Reward::Scene_Reward()
{
    
}
Scene_Reward::~Scene_Reward()
{
    GUIReader::shareReader()->purgeGUIReader();
    DictionaryHelper::shareHelper()->purgeDictionaryHelper();
    ActionManager::shareManager()->purgeActionManager();
}

bool Scene_Reward::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    GameLayerSysInfo* layer = GameLayerSysInfo::create();
    this->addChild(layer);
    return true;
}
void Scene_Reward::rewardBtnCallback(cocos2d::CCObject *pSender)
{
    CCDirector::sharedDirector()->popScene();
}