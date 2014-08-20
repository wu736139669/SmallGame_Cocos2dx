//
//  GameLayerGameCell.cpp
//  OnceAgain
//
//  Created by mac on 14-4-16.
//
//

#include "GameLayerGameCell.h"
#include "StringUtil.h"
GameLayerGameCell::GameLayerGameCell()
{
    
}
GameLayerGameCell::~GameLayerGameCell()
{
    GUIReader::shareReader()->purgeGUIReader();
	DictionaryHelper::shareHelper()->purgeDictionaryHelper();
	ActionManager::shareManager()->purgeActionManager();
}
bool GameLayerGameCell::init()
{
    UILayer* cellLyaer = UILayer::create();
    auto myLayout = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile(CStringUtil::convertToUIResPath("GameCell.json").c_str()));
    cellLyaer->addWidget(myLayout);
    this->addChild(cellLyaer, 0, 100);

    return true;
}