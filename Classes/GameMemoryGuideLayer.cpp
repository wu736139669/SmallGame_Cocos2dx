//
// GameMemoryGuideLayer.cpp
// OnceAgain
//
// Created by xiaohai on 14-5-6.
//
//

#include "GameMemoryGuideLayer.h"
#include "GameUIExportJson.h"
CCScene* GameMemoryGuideLayer::createScene()
{
    auto scene = CCScene::create();
    auto layer = GameMemoryGuideLayer::create();
    scene->addChild(layer);
    return scene;
}

bool GameMemoryGuideLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    initData();
    BindingUIItems();
    loopAnmitaton();
    return true;
}
#pragma mark - initData
void GameMemoryGuideLayer::initData()
{
    ul = UILayer::create();
    addChild(ul);
    auto *myLayout = dynamic_cast<Layout*>(GUIReader::shareReader() -> widgetFromJsonFile(uiGameMemoryGuideLayer));
    ul -> addWidget(myLayout);
}
void GameMemoryGuideLayer::BindingUIItems()
{
    // bind ui images
    auto* card_1 = static_cast<UIImageView*>(ul -> getWidgetByName("Card_1"));
    auto* card_2 = static_cast<UIImageView*>(ul -> getWidgetByName("Card_2"));
    auto* card_3 = static_cast<UIImageView*>(ul -> getWidgetByName("Card_3"));
    auto* card_4 = static_cast<UIImageView*>(ul -> getWidgetByName("Card_4"));
    auto* card_5 = static_cast<UIImageView*>(ul -> getWidgetByName("Card_5"));
    auto* card_6 = static_cast<UIImageView*>(ul -> getWidgetByName("Card_6"));
    
    cardList.push_back(card_1);
    cardList.push_back(card_2);
    cardList.push_back(card_3);
    cardList.push_back(card_4);
    cardList.push_back(card_5);
    cardList.push_back(card_6);
    
    finger = static_cast<UIImageView*>(ul -> getWidgetByName("finger"));
    fingerPoint = finger -> getPosition();
    
}
void GameMemoryGuideLayer::loopAnmitaton() {
    //动画开始预备
    CCCallFunc *ani_1 = CCCallFunc::create(this, callfunc_selector(GameMemoryGuideLayer::anmitionBegin));
    //所有卡牌翻背
    CCCallFunc *ani_2 = CCCallFunc::create(this, callfunc_selector(GameMemoryGuideLayer::allCardClose));
    //卡3翻开
    CCCallFuncND *ani_3 = CCCallFuncND::create(this, callfuncND_selector(GameMemoryGuideLayer::openCard), (void *)3);
    //卡4翻开
    CCCallFuncND *ani_4 = CCCallFuncND::create(this, callfuncND_selector(GameMemoryGuideLayer::openCard), (void *)4);
    //卡1翻开
    CCCallFuncND *ani_5 = CCCallFuncND::create(this, callfuncND_selector(GameMemoryGuideLayer::openCard), (void *)1);
    //卡2翻开
    CCCallFuncND *ani_6 = CCCallFuncND::create(this, callfuncND_selector(GameMemoryGuideLayer::openCard), (void *)2);
    //卡5翻开
    CCCallFuncND *ani_7 = CCCallFuncND::create(this, callfuncND_selector(GameMemoryGuideLayer::openCard), (void *)5);
    //卡6翻开
    CCCallFuncND *ani_8 = CCCallFuncND::create(this, callfuncND_selector(GameMemoryGuideLayer::openCard), (void *)6);
    
    
    //按下动作
    CCMoveBy *down = CCMoveBy::create(0.4, ccp(-50, -40));
    //手指拿起
    CCMoveBy *up = CCMoveBy::create(0.4, ccp(50, 40));
    //从卡3移动到卡4
    CCMoveTo *move_1 = CCMoveTo::create(0.4, ccp(cardList[3]->getPosition().x+ 50, cardList[3]->getPosition().y+ 40));
    //从卡4移动到卡1
    CCMoveTo *move_2 = CCMoveTo::create(0.4, ccp(cardList[0]->getPosition().x+ 50, cardList[0]->getPosition().y+ 40));
    //从卡1到卡2
    CCMoveTo *move_3 = CCMoveTo::create(0.25, cardList[1]->getPosition());
    //从卡2到卡5
    CCMoveTo *move_4 = CCMoveTo::create(0.25, cardList[4]->getPosition());
    //从卡5到卡6
    CCMoveTo *move_5 = CCMoveTo::create(0.25, cardList[5]->getPosition());
    CCMoveTo *move_6 = CCMoveTo::create(0.2, ccp(cardList[5]->getPosition().x + 80, cardList[5]->getPosition().y));
    
    finger -> runAction(CCRepeatForever::create(CCSequence::create(ani_1, CCDelayTime::create(.8), ani_2, CCDelayTime::create(1), down, ani_3, up, move_1, down,  ani_4, up, move_2, down, ani_5, move_3, ani_6, move_4, ani_7, move_5, ani_8, move_6, CCDelayTime::create(.8), NULL)));
    
}
void GameMemoryGuideLayer::anmitionBegin() {
    for (int i = 0; i < cardList.size(); i++) {
        std::string str = (i == 2 || i == 3)?imgGameMemoryCard9:imgGameMemoryCard10;
        cardList[i] -> setTexture(str.c_str());
    }
    finger -> setPosition(ccp(fingerPoint.x + 50, fingerPoint.y + 40));
}
void GameMemoryGuideLayer::allCardClose() {
    for (int i = 0; i < cardList.size(); i++) {
        CCCallFuncND *a = CCCallFuncND::create(this, callfuncND_selector(GameMemoryGuideLayer::closeCard), (void *)i);
        cardList[i] -> runAction(CCSequence::create(CCOrbitCamera::create(.4 * .4, 1, 0, 0, 90, 0, 0),
                                                    a,
                                                    CCOrbitCamera::create(.4 * .4, 1, 0, 90, 90, 0, 0),
                                                    NULL));
    }
}
void GameMemoryGuideLayer::closeCard(CCNode*p ,void* num) {
    cardList[(int)num] -> setTexture(imgGameMemoryCard00);
}
//////////////////////////////////////////
void GameMemoryGuideLayer::openCard(CCNode *p, void *num) {
     CCCallFuncND *open = CCCallFuncND::create(this, callfuncND_selector(GameMemoryGuideLayer::openCardByNum), num);
    cardList[(int)num - 1] -> runAction(CCSequence::create(CCOrbitCamera::create(.4 * .4, 1, 0, 180, 90, 0, 0),
                                           open,
                                           CCOrbitCamera::create(.4 * .4, 1, 0, 270, 90, 0, 0),
                                           NULL));
}

void GameMemoryGuideLayer::openCardByNum(CCNode *p, void *num) {
    int number = (int)num;
    int index = number - 1;
    std::string str = (number == 3 || number == 4)?imgGameMemoryCard9:imgGameMemoryCard10;
    cardList[index]->setTexture(str.c_str());
}
