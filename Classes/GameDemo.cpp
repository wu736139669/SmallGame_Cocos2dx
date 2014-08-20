//
//  GameDemo.cpp
//  OnceAgain
//
//  Created by mac on 14-3-10.
//
//

#include "GameDemo.h"

GameDemo::~GameDemo()
{
    
}

CCScene* GameDemo::scene()
{
    // 'scene' Automatic release memory
    CCScene *scene = CCScene::create();
    // 'layer' Automatic release memory
    GameDemo *layer = GameDemo::create();
    scene->addChild(layer);
    return scene;
}

bool GameDemo::init()
{
    if (!GameShare_Scene::init()) {
        return false;
    }
    
    //开始
    this->showReadyGo();
    //设置分数
    this->setScore(100);
    //设置能量最大值.
    this->boom_setMaxBoomEnergy(40);
    //增加能量
    this->boom_addEnergy(10);
    

    
    //是否积满一次炸弹.

    
    //设置连击.
    this->setBatter(10);
    return true;
}