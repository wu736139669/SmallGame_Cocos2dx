//
// GameSanXiaoLayer.cpp
// OnceAgain
//
// Created by xiaoqiang on 14-6-13.
//
//

#include "GameSanXiaoLayer.h"
#include "SanXiaoConfigAnalytical.h"
#include "SanXiaoRuleController.h"
#include "PlayerInfoManager.h"
#include "StringUtil.h"

#define SXDATE_GET  sanxiaoConfigData::sharedInstance().getSanXiaoConfig()
#define SXDATE_INT sanxiaoConfigData::sharedInstance().getIntDataByName
#define SXDATE_STR sanxiaoConfigData::sharedInstance().getStringDataByName
#define ProPs CCUserDefault::sharedUserDefault()->getBoolForKey
#define up 3
#define down 4
#define left 1
#define right 2

CCScene* GameSanXiaoLayer::createScene()
{
    auto scene = CCScene::create();
    auto layer = GameSanXiaoLayer::create();
    scene->addChild(layer);
    return scene;
}

bool GameSanXiaoLayer::init()
{
    if ( !GameShare_Scene::init() )
    {
        return false;
    }
    empytItemBox.clear();
    batter = 0;
    score = 0;
    batterScoreModel = 1;
    batterModel = 1;
    moveStatus = false;
    boom_setEnergy(90);
    isboomFull = false;
    isShowHengItem = false;
    isShowZongItem = false;
    hengXiaoCount = 0;
    zongXiaoCount = 0;
    isInPropModel = false;
    delItemsCounts = 0;
    isShowSanHengItem = false;
    getPropUsedInfo();
    
    canBeTouch = true;
    NewCreatNumber = 0;
    MoveDFinishnumber = 0;
    ITEMSNODE = CCNode::create();
    ITEMSNODE -> setPosition(0, 0);
    this -> addChild(ITEMSNODE, 0);
    SXDATE_GET;//获取配置表
    BindingUIItems();//绑定ui
    return true;
}

void GameSanXiaoLayer::initBgView(void) {
    CCSprite *gameBackGround = CCSprite::create("SanXiao/GameBackGround.jpg");
    gameBackGround -> setAnchorPoint(ccp(0, 0));
    gameBackGround -> setPosition(ccp(0, 0));
    this -> addChild(gameBackGround, 0);
}

void GameSanXiaoLayer::onExit() {
    
}

#pragma mark - initData
void GameSanXiaoLayer::initUiData()
{
    CCSize visize = CCDirector::sharedDirector() -> getVisibleSize();
    for (int y = 0; y < 7; y ++) {
        for (int x = 0; x < 7; x ++) {
            ItemBox ib;
            CCPoint pt = ccp(visize.width * 0.093 + 87 * x, visize.height * 0.202 + 87 *y);
            ib.itemNode = SanXiaoItemLayer::create();
            ib.itemNode-> setContentSize(CCSize(87, 87));
            int b = 1;
            if (score >= SXDATE_INT(picNumByScore)) {
                b = 2;
            }
            ib.itemNode -> creatItemByTag(b);
            ib.ItemPoint = pt;
            ib.itemNode -> setPosition(pt);
            ib.number = y * 7 + x;
            ib.wellRemove = false;
            ib.type = ib.itemNode -> getItemType();
            ITEMSNODE -> addChild(ib.itemNode, 0);
            itemList.push_back(ib);
        }
    }
}

void GameSanXiaoLayer::BindingUIItems()
{

}

void GameSanXiaoLayer::getPropUsedInfo() {
    Prop_superModel = ProPs("P_1");
    Prop_timeAdd = ProPs("P_2");
    Prop_sameColorDel = ProPs("P_3");
    Prop_crossDel = ProPs("P_4");
    sMGameStrengthen pStreng1;
    CPlayerInfoMan::sharedInstance().getMStrengthenByGameId(Game_SanXiao, StrengThenTag_17, pStreng1);
    sMGameStrengthen pStreng2;
    CPlayerInfoMan::sharedInstance().getMStrengthenByGameId(Game_SanXiao, StrengThenTag_18, pStreng2);
    sMGameStrengthen pStreng3;
    CPlayerInfoMan::sharedInstance().getMStrengthenByGameId(Game_SanXiao, StrengThenTag_19, pStreng3);
    Strengthen_star_number = CStringUtil::ToDouble(pStreng1.strengthenValue);
    Strengthen_threeCross_number = CStringUtil::ToDouble(pStreng2.strengthenValue);
    Strengthen_addScore_number = CStringUtil::ToDouble(pStreng3.strengthenValue);
}

#pragma mark - gameStatus
void GameSanXiaoLayer::startGame(float dt) {
    initUiData();//载入ui
    if (Prop_superModel) {
        Prop_superModel = false;
        batterModel = 3;
        Crazy_Start(100.f, eSuperCrazyMode);
        batterScoreModel = SXDATE_INT(superInsaneScore);
    }

}

void GameSanXiaoLayer::msgHanlde_GameTimeOut(CCObject* obj) {
    GameShare_Scene::msgHanlde_GameTimeOut(obj);
}

void GameSanXiaoLayer::msgHanlde_BoomFull(CCObject* obj) {
    isboomFull = true;
}

void GameSanXiaoLayer::msgHandle_CrazyTimeOut(CCObject* obj) {
    
}

void GameSanXiaoLayer::noticeTimeInterval(CCObject* obj) {
    if (((GameShare_TimeProcess*)obj)->GetSecondsRemain() <= 2)
	{
        if (Prop_timeAdd) {
            time_addSecond(5);
            Prop_timeAdd = false;
            useTimeEff();
        }
        return;
	}
    GameShare_Scene::noticeTimeInterval(obj);
}

#pragma mark - touchController
bool GameSanXiaoLayer::ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event) {
    if (!canBeTouch) {
        return true;
    }
    ItemInMovingList.clear();
    touchBeginIndex = getIndexByPoint(touch -> getLocation());
    int number;
    for (int i = 0; i < itemList.size(); i ++) {
        if (itemList[i].number == touchBeginIndex) {
            number = itemList[i].itemNode -> getItemType();
            if (number >= 10) {
                isInPropModel = true;
                std::vector<ItemBox>lbox;
                if (number == boomPic) {
                    //若点击的是炸弹
                    lbox = SanXiaoRuleController::sharedInstance().refreshItemBoxWithClickBoom(itemList, touchBeginIndex);
                    time_addSecond(5);
                    itemList.clear();
                    itemList = lbox;
                    lbox.clear();
                    moveStatus = true;
                    refreshCallBack();
                }
                if (number == heng_Cross) {
                    std::vector<ItemBox>lbox;
                    lbox = SanXiaoRuleController::sharedInstance().refreshItemBoxWithHengCross(itemList, touchBeginIndex);
                    itemList.clear();
                    itemList = lbox;
                    lbox.clear();
                    moveStatus = true;
                    refreshCallBack();
                                    }
                if (number == zong_Cross) {
                    std::vector<ItemBox>lbox;
                    lbox = SanXiaoRuleController::sharedInstance().refreshItemBoxWithZongCross(itemList, touchBeginIndex);
                    itemList.clear();
                    itemList = lbox;
                    lbox.clear();
                    moveStatus = true;
                    refreshCallBack();
                }
                if (number == threeCross) {
                    std::vector<ItemBox>lbox;
                    lbox = SanXiaoRuleController::sharedInstance().refreshItemBoxWithThreeCross(itemList, touchBeginIndex);
                    itemList.clear();
                    itemList = lbox;
                    lbox.clear();
                    moveStatus = true;
                    refreshCallBack();
                }
                
    
                return true;
            }
            
        }
    }
    isInPropModel = false;
    return true;
}

void GameSanXiaoLayer::ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event) {
   
}

void GameSanXiaoLayer::ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event) {
    if (!canBeTouch) {
        return;
    }
    ItemBox ib;
    for (int i = 0; i < itemList.size(); i ++) {
        if (itemList[i].number == touchBeginIndex) {
            ib = itemList[i];
        }
    }
    ItemBox ib2;
    int number2 = getIndexByPoint(touch -> getLocation());
    for (int i = 0; i < itemList.size(); i ++) {
        if (itemList[i].number == number2) {
            ib2 = itemList[i];
        }
    }
    CCPoint Pend = ib2.ItemPoint;
    int moveKind = 0;// 0.无 1左 ，2右 ，3上 ，4下
    if (abs((int)(Pend.x - ib.ItemPoint.x)) > abs((int)(Pend.y - ib.ItemPoint.y))) {
        if (abs((int)(Pend.x - ib.ItemPoint.x)) >= 87/2) {
            if (Pend.x - ib.ItemPoint.x > 0) {
                moveKind = right;
            }
            if (Pend.x - ib.ItemPoint.x < 0) {
                moveKind = left;
            }
        }
    }
    if (abs((int)(Pend.x - ib.ItemPoint.x)) < abs((int)(Pend.y - ib.ItemPoint.y))) {
        if (abs((int)(Pend.y - ib.ItemPoint.y)) >= 87/2) {
            if (Pend.y - ib.ItemPoint.y > 0) {
                moveKind = up;
            }
            if (Pend.y - ib.ItemPoint.y < 0) {
                moveKind = down;
            }
        }
    }
    for (int i = 0; i < itemList.size(); i++) {
        if (moveKind == up || moveKind == down) {//若上下移动
            if (abs(itemList[i].number - touchBeginIndex) % 7 == 0) {
                ItemInMovingList.push_back(itemList[i]);
            }
        }
    }
    if (moveKind == left || moveKind == right) {//若左右移动
        int num = touchBeginIndex;
        while (1) {
            for (int j = 0; j < itemList.size(); j ++) {
                if (itemList[j].number == num) {
                    ItemInMovingList.push_back(itemList[j]);
                }
            }
            if (num % 7 == 0) {
                break;
            }
            num --;
        }
        if(ItemInMovingList.size() < 7) {
            num = touchBeginIndex;
            while (1) {
                bool wellCont = false;
                for (int k = 0; k < ItemInMovingList.size(); k ++) {
                    if (ItemInMovingList[k].number == num) {
                        num++;
                        wellCont = true;
                    }
                }
                if (wellCont) {
                    continue;
                }
                for (int j = 0; j < itemList.size(); j ++) {
                    if (itemList[j].number == num) {
                        ItemInMovingList.push_back(itemList[j]);
                    }
                }
                if (num % 7 == 6) {
                    break;
                }
                num ++;
            }
        }
    }
    if (moveKind > 0) {
        MoveItems(moveKind);
    }
}

int GameSanXiaoLayer::getIndexByPoint(CCPoint p) {
    for (int i = 0; i < itemList.size(); i ++) {
        float Px1 = itemList[i].itemNode -> getPositionX() - (float)87/(float)2;
        float Px2 = itemList[i].itemNode -> getPositionX() + (float)87/(float)2;
        float Py1 = itemList[i].itemNode -> getPositionY() - (float)87/(float)2;
        float Py2 = itemList[i].itemNode -> getPositionY() + (float)87/(float)2;
        if (p.x >= Px1 && p.x <= Px2 && p.y >= Py1 && p.y <= Py2) {
            return itemList[i].number;
        }
    }
    return 100;
}

void GameSanXiaoLayer::MoveItems(int MoveR) {
    canBeTouch = false;
    MoveDFinishnumber = 0;
    if (MoveR == left || MoveR == right) {
        int addNum1 = MoveR == left ? 0 : 6;
        int addNum2 = MoveR == left ? -1 : 1;
        int addNum3 = MoveR == left ? 6 : 0;
        for (int i = 0;  i < ItemInMovingList.size(); i ++) {
            if (ItemInMovingList[i].number % 7 != addNum1) {
                CCPoint p;
                for (int j = 0; j < ItemInMovingList.size(); j ++) {
                    if (ItemInMovingList[j].number == ItemInMovingList[i].number + addNum2) {
                        p = ItemInMovingList[j].ItemPoint;
                    }
                }
                ItemInMovingList[i].itemNode -> runAction(CCSequence::create(CCMoveTo::create(0.15, p), CCCallFunc::create(this, callfunc_selector(GameSanXiaoLayer::callBackByMoveFinish)), NULL));
                ItemInMovingList[i].itemNode -> onClick();
            }
        }
        for (int i = 0; i < ItemInMovingList.size(); i ++) {
            if (ItemInMovingList[i].number % 7 == addNum1) {
                CCPoint p;
                for (int j = 0; j < ItemInMovingList.size(); j ++) {
                    if (ItemInMovingList[j].number % 7 == addNum3) {
                        p = ItemInMovingList[j].ItemPoint;
                    }
                }
                ItemInMovingList[i].itemNode -> setPosition(ccp(p.x + 87*((-1)*addNum2), p.y));
                ItemInMovingList[i].itemNode -> runAction(CCSequence::create(CCMoveTo::create(0.15, p), CCCallFunc::create(this, callfunc_selector(GameSanXiaoLayer::callBackByMoveFinish)), NULL));
                ItemInMovingList[i].itemNode -> onClick();
            }
        }
        for (int i = 0; i < ItemInMovingList.size(); i ++) {
            if (ItemInMovingList[i].number % 7 == addNum1) {
                ItemInMovingList[i].number -= 6*(addNum2);
                continue;
            }
            ItemInMovingList[i].number += addNum2;
        }
    }
    if (MoveR == up) {
        for (int i = 0; i <= 6; i ++) {
            CCPoint p;
            for (int j  = 0; j < ItemInMovingList.size(); j ++) {
                if (ItemInMovingList[j].number - 7*i >= 0 && ItemInMovingList[j].number - 7*i < 7) {
                    for (int k = 0; k < ItemInMovingList.size(); k ++) {
                        if (i != 6 && ItemInMovingList[k].number - 7*(i+1) >= 0 && ItemInMovingList[k].number - 7*(i+1) < 7) {
                            p = ItemInMovingList[k].ItemPoint;
                        }
                        if (i == 6 && ItemInMovingList[k].number < 7) {
                            p = ItemInMovingList[k].ItemPoint;
                            ItemInMovingList[j].itemNode -> setPosition(ccp(p.x, p.y - 87));
                        }
                    }
                    ItemInMovingList[j].itemNode -> runAction(CCSequence::create(CCMoveTo::create(0.15, p), CCCallFunc::create(this, callfunc_selector(GameSanXiaoLayer::callBackByMoveFinish)), NULL));
                    ItemInMovingList[j].itemNode -> onClick();
                }
            }
        }
        for (int j = 0; j < ItemInMovingList.size(); j ++) {
            if (ItemInMovingList[j].number >= 42) {
                ItemInMovingList[j].number -= 42;
            }
            else {
                ItemInMovingList[j].number += 7;
            }
        }
    }
    if (MoveR == down) {
        for (int i = 0; i <= 6; i ++) {
            CCPoint p;
            for (int j  = 0; j < ItemInMovingList.size(); j ++) {
                if (ItemInMovingList[j].number - 7*i >= 0 && ItemInMovingList[j].number - 7*i < 7) {
                    for (int k = 0; k < ItemInMovingList.size(); k ++) {
                        if (i != 0 && ItemInMovingList[k].number - 7*(i-1) >= 0 && ItemInMovingList[k].number - 7*(i-1) < 7) {
                            p = ItemInMovingList[k].ItemPoint;
                        }
                        if (i == 0 && ItemInMovingList[k].number >= 42) {
                            p = ItemInMovingList[k].ItemPoint;
                            ItemInMovingList[j].itemNode -> setPosition(ccp(p.x, p.y + 87));
                        }
                    }
    
                    ItemInMovingList[j].itemNode -> runAction(CCSequence::create(CCMoveTo::create(0.15, p), CCCallFunc::create(this, callfunc_selector(GameSanXiaoLayer::callBackByMoveFinish)), NULL));
                    ItemInMovingList[j].itemNode -> onClick();
                }
            }
        }
        for (int j = 0; j < ItemInMovingList.size(); j ++) {
            if (ItemInMovingList[j].number < 7) {
                ItemInMovingList[j].number += 42;
            }
            else {
                ItemInMovingList[j].number -= 7;
            }
        }
    }
}

void GameSanXiaoLayer::callBackByMoveFinish() {
    MoveDFinishnumber ++;
    moveStatus = false;
    if (MoveDFinishnumber >= 7) {
        for (int i = 0; i < ItemInMovingList.size(); i ++) {
            ItemInMovingList[i].itemNode -> freeClick();
        }
        for (int i = 0; i < ItemInMovingList.size(); i ++) {
            ItemInMovingList[i].ItemPoint = ItemInMovingList[i].itemNode -> getPosition();
        }
        for (int i = 0; i < ItemInMovingList.size(); i ++) {
            for (int j = 0; j < itemList.size(); j ++) {
                if (itemList[j].number == ItemInMovingList[i].number) {
                    itemList[j] = ItemInMovingList[i];
                }
            }
        }
        this -> runAction(CCSequence::create(CCDelayTime::create(0.03f), CCCallFunc::create(this, callfunc_selector(GameSanXiaoLayer::refreshCallBack)), NULL));
    }
}

void GameSanXiaoLayer::refreshCallBack() {
    canBeTouch = false;
    std::vector<ItemBox>l;
    l = SanXiaoRuleController::sharedInstance().refreshItemBoxWithDoMove(itemList);
    itemList.clear();
    itemList = l;
    l.clear();
    begainDeleItem();
}
void GameSanXiaoLayer::begainDeleItem() {
    NewCreatNumber = 0;
    bool well = false;
    for (int i = 0; i < itemList.size(); i ++) {
        if (itemList[i].wellRemove == true) {
            itemList[i].itemNode -> boomAndDel();
            well = true;
        }
    }
    if (well) {
        this -> runAction(CCSequence::create(CCDelayTime::create(0.2), CCCallFunc::create(this, callfunc_selector(GameSanXiaoLayer::DeleDCallBackRefreshMap)) ,NULL));
    }
    else {
        if (!moveStatus) {
            batterModel = 1;
            batter = 0;
            Crazy_End();
        }
        canBeTouch = true;
    }
}

void GameSanXiaoLayer::DeleDCallBackRefreshMap() {
    empytItemBox.clear();
    for (int i = 0; i < 7; i ++) {
        //每一列
        std::vector<ItemBox>m_box;
        int boomCount = 7;
        for (int j = 0; j < itemList.size(); j++) {
            if ((itemList[j].number - i) % 7 == 0 ) {
                m_box.push_back(itemList[j]);
            }
        }
        //循环每一列，下落
        while (1) {
            if (boomCount == 0) {
                break;
            }
            //获取最底下的一个空位
            int boomIndex = 100;
            //掉落的item number
            int drawItemIndex = 100;
            for (int j = 0; j < m_box.size(); j ++) {
                if (m_box[j].wellRemove && boomIndex > m_box[j].number) {
                    boomIndex = m_box[j].number;
                }
            }
            int max = boomIndex;
            while (1) {
                max += 7;
                bool wellagain = false;
                for (int k = 0; k < m_box.size(); k ++) {
                    if (m_box[k].number == max) {
                        if (!m_box[k].wellRemove) {
                            drawItemIndex = m_box[k].number;
                            wellagain = true;
                        }
                    }
                }
                if (wellagain) {
                    break;
                }
                if (max > 41) {
                    break;
                }
            }
            CCPoint p1;
            //若存在掉落item
            if (drawItemIndex != 100) {
                ItemBox b1;
                ItemBox b2;
                for (int j = 0; j < m_box.size(); j ++) {
                    if (m_box[j].number == drawItemIndex) {
                        b2 = m_box[j];
                    }
                    if (m_box[j].number == boomIndex) {
                        b1 = m_box[j];
                    }
                }
                CCPoint p = b2.ItemPoint;
                b2.itemNode -> runAction(CCMoveTo::create(0.15, b1.ItemPoint));
                int n = b2.number;
                b2.number = b1.number;
                b1.number = n;
                b1.ItemPoint = p;
                for (int j = 0; j < m_box.size(); j ++) {
                    if (m_box[j].number == boomIndex) {
                        m_box[j] = b2;
                    }
                    if (m_box[j].number == drawItemIndex) {
                        m_box[j] = b1;
                    }
                }
            }
            boomCount --;
        }
        
        for (int j = 0; j < m_box.size(); j++) {
            for (int k = 0; k < itemList.size(); k++) {
                if (itemList[k].number == m_box[j].number) {
                    itemList[k] = m_box[j];
                }
            }
        }
    }
    for (int i = 0; i < itemList.size(); i++) {
        if (itemList[i].wellRemove) {
            empytItemBox.push_back(itemList[i]);
        }
    }
    this -> runAction(CCSequence::create(CCDelayTime::create(0.15), CCCallFunc::create(this, callfunc_selector(GameSanXiaoLayer::RefreshMapCallBack)) ,NULL));
}

void GameSanXiaoLayer::RefreshMapCallBack() {
    CCSize visize = CCDirector::sharedDirector() -> getVisibleSize();
    for (int i = 0; i < empytItemBox.size(); i++) {
        ItemBox ib = empytItemBox[i];
        ib.itemNode = SanXiaoItemLayer::create();
        int b = 1;
        if (score >= SXDATE_INT(picNumByScore)) {
            b = 2;
        }
        if (isboomFull) {
            isboomFull = false;
            b = boomPic;
        } else if (isShowHengItem) {
            isShowHengItem = false;
            hengXiaoCount = 0;
            b = heng_Cross;
            
        } else if (isShowZongItem) {
            isShowZongItem = false;
            zongXiaoCount = 0;
            b = zong_Cross;
        }
        else if (isShowSanHengItem) {
            isShowSanHengItem = false;
            b = threeCross;
        }
        ib.itemNode -> creatItemByTag(b);
        ib.type = ib.itemNode -> getItemType();
        ib.itemNode->setPosition(ccp(ib.ItemPoint.x,visize.height * 0.202 + 87 * 6.5));
        ITEMSNODE -> addChild(ib.itemNode, 0);
        ib.wellRemove = false;
        empytItemBox[i] = ib;
    }
    for (int i = 0; i < empytItemBox.size(); i++) {
        empytItemBox[i].itemNode -> runAction(CCSequence::create(CCMoveTo::create(0.15, empytItemBox[i].ItemPoint), CCCallFunc::create(this, callfunc_selector(GameSanXiaoLayer::refreshItemPoints)),NULL) );
    }
    for (int j = 0; j < empytItemBox.size(); j ++) {
        for (int i = 0; i < itemList.size(); i ++) {
            if (itemList[i].number == empytItemBox[j].number) {
                itemList[i] = empytItemBox[j];
            }
        }
    }
    if (empytItemBox.size() < 1) {
        canBeTouch = true;
    }
    
}
void GameSanXiaoLayer::refreshItemPoints() {
    NewCreatNumber ++;
    if (NewCreatNumber == empytItemBox.size()) {
        for (int i = 0; i < itemList.size(); i ++) {
            itemList[i].ItemPoint = itemList[i].itemNode -> getPosition();
            itemList[i].type = itemList[i].itemNode -> getItemType();
        }
        if (!isInPropModel) {
            for (int i = 0; i < SanXiaoRuleController::sharedInstance().getDelCountBy3(); i ++) {
                setMyScore(3);
            }
            for (int i = 0; i < SanXiaoRuleController::sharedInstance().getDelCountBy4(); i ++) {
                setMyScore(4);
            }
            for (int i = 0; i < SanXiaoRuleController::sharedInstance().getDelCountBy5(); i ++) {
                setMyScore(5);
            }
            hengXiaoCount += SanXiaoRuleController::sharedInstance().getHengCount();
            zongXiaoCount += SanXiaoRuleController::sharedInstance().getZongCount();
            if (hengXiaoCount >= SXDATE_INT(lateral)) {
                isShowHengItem = true;
            }
            if (zongXiaoCount >= SXDATE_INT(longitudinal)) {
                isShowZongItem = true;
            }
        }
        else {
            setMyScore(empytItemBox.size());
        }
        delItemsCounts += empytItemBox.size();
        if (delItemsCounts % (SXDATE_INT(sd_picNum) - Strengthen_threeCross_number) == 0) {
            isShowSanHengItem = true;
        }
        moveStatus = true;
        refreshCallBack();
    }
}

void GameSanXiaoLayer::setMyScore(int kind) {
    isInPropModel = false;
    boom_addEnergy(SXDATE_INT(boomAddE));
    if (batter >= SXDATE_INT(BatterToBeInsane) && batter < SXDATE_INT(BatterToBeSuperInsane)) {
        if (batterModel == 1) {
            Crazy_Start(100.f, eComCrazyMode);
            batterModel = 2;
            batterScoreModel = SXDATE_INT(InsaneScore);

        }
    }
    if (batter >= SXDATE_INT(BatterToBeSuperInsane)) {
        if (batterModel == 2) {
            Crazy_Start(100.f, eSuperCrazyMode);
            batterModel = 3;
            batterScoreModel = SXDATE_INT(superInsaneScore);
        }
    }
  
    int numberX = 50 * batter;
    int numberY;
    if (kind == 3) {
        numberY = 100 * 3;
    }
    if (kind == 4) {
        numberY = 200 * 4;
    }
    if (kind >= 5) {
        numberY = 400 * kind;
    }
    int z = Strengthen_addScore_number;
    if (batter > 0) {
        setBatter(batter);
    }
    
    score += ((numberX + numberY) * batterScoreModel + z);
    setScore(score);
    batter ++;
}