//
//  Game_Memory1.cpp
//  OnceAgain
//
//  Created by mac on 14-3-7.
//
//

#include "Game_Memory.h"
#include "StringUtil.h"
#include "PlayerInfoManager.h"
#include "NetHttpClient.h"
#include "NetPacket.h"
#include "PlayerInfoManager.h"
#include "StrengthenManager.h"
#include "GameShare_Property.h"
#include "GameUIExportJson.h"
#include "TaskManager.h"
#include "XQDate.h"
#include "GameItemManager.h"
#include "TaskDefine.h"

Game_Memory::~Game_Memory()
{
    
}

CCScene* Game_Memory::scene()
{
    // 'scene' Automatic release memory
    CCScene *scene = CCScene::create();
    // 'layer' Automatic release memory
    Game_Memory *layer = Game_Memory::create();
    scene->addChild(layer);
    return scene;
}

bool Game_Memory::init()
{
    if (!GameShare_Scene::init()) {
        return false;
    }
    UILayer *ul = UILayer::create();
    addChild(ul, 200);
    back = UIPanel::create();
    back -> setTouchEnabled(true);
    back -> setSize(CCSize(640, 1136));
    ul->addWidget(back);
    
    superModelCount = 0;
    addGoldNumber = 0;
    
    CCString str1;
    str1.initWithFormat("medal60007_%d", GameShare_Global::shareGlobal()->gameType);
    
   // JudgeMedalGet::isMedalInfoHave(GameShare_Global::shareGlobal()->gameType, this, coco_myevent(Game_Memory::MedalInfoBack));
    
     CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("./GameMemoryLayer/Game_SuperMemory.plist");
    
    super_Props_notMiss = false;
    
    isMiss = true;
    MissCount = 0;
    
    cardTypeList.clear();
    
    superModelCount = 0;
    secore2wCount = 0;
    oneAgainCount = 0;
    propEasyGameCount = 0;
    pointCount = 0;
    bigestBatter = 0;
    superModelTime = 0;
    superModelTimecount = 0;
    boomCount = 0;
    missNumber = 0;

    
    nowtype = -1;
    total = 0;
    nowCilck = 0;
    batterTime = Batter_Normal;
    preTime = 0;
    allbatter = 0;
    isHighScoreCard = false;
    isGoldCard = false;
    isHighScoreCard_1 = false;
    onceAgain = false;
    isBoom = false;
    
    //各种道具的使用与否
    Props_one = CCUserDefault::sharedUserDefault()->getBoolForKey("P_1");
    Props_tow = CCUserDefault::sharedUserDefault()->getBoolForKey("P_2");
    Props_three = CCUserDefault::sharedUserDefault()->getBoolForKey("P_3");
    Props_four = CCUserDefault::sharedUserDefault()->getBoolForKey("P_4");
    
    have_props_one = Props_one;
    //声音
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(CCFileUtils::sharedFileUtils()->fullPathFromRelativeFile(EFFECT_BINGO,""));
    for (int i=0; i<11; i++) {
        char str[32];
        if (i==9) {
            sprintf(str,"%s10.caf",EFFECT_CLICK);
        }
        else if(i==10){
            sprintf(str,"%s_max.caf",EFFECT_CLICK);
        }else{
            sprintf(str,"%s0%d.caf",EFFECT_CLICK,i+1);
        }
        CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(CCFileUtils::sharedFileUtils()->fullPathFromRelativeFile(str,""));
    }
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(CCFileUtils::sharedFileUtils()->fullPathFromRelativeFile(MUSIC_TENSEC,""));
    this->setBackgroundMusic(muBG_in_game04);

    //点击正确的精灵。
    clickTrueSprite = CCSprite::create("./effect/bomb/1.png");
    clickTrueSprite->setPosition(CCPointZero);
    clickTrueSprite->setOpacityModifyRGB(true);
    clickTrueSprite->setVisible(false);
    ccBlendFunc cBlendFunc = {GL_SRC_ALPHA, GL_ONE};
    clickTrueSprite->setBlendFunc(cBlendFunc);
    this->addChild(clickTrueSprite,Tag_Max);
    
    //点击错误的精灵
    clickFalseSprite = CCSprite::create(imgclickWrong);
    clickFalseSprite->setVisible(false);
    this->addChild(clickFalseSprite,Tag_Max);
    
    //正确过关的精灵
    rightSprite = CCSprite::create(imgclickRight);
    rightSprite->setScale(1.5);
    rightSprite->setVisible(false);
    rightSprite->setPosition(ccp(this->getContentSize().width/2, this->getContentSize().height/2-100));
    this->addChild(rightSprite,Tag_Max);
    
    this->boom_setMaxBoomEnergy(100);
    this->boom_setEnergy(0);
    
    //若使用道具4，则随机出6个固定牌
    if (Props_four) {
        for (int i = 1; i <= 6; i++) {
            cardTypy.push_back(i);
        }
    }
    //金币
    sMGameStrengthen pStreng1;
    CPlayerInfoMan::sharedInstance().getMStrengthenByGameId(1, StrengThenTag_11, pStreng1);
    //高分
    sMGameStrengthen pStreng2;
    CPlayerInfoMan::sharedInstance().getMStrengthenByGameId(1, StrengThenTag_12, pStreng2);
    //奖励
    sMGameStrengthen pStreng3;
    CPlayerInfoMan::sharedInstance().getMStrengthenByGameId(1, StrengThenTag_13, pStreng3);
    Gold = CStringUtil::ToDouble(pStreng1.strengthenValue);
    Scorecard = CStringUtil::ToDouble(pStreng2.strengthenValue);
    Otherscore = CStringUtil::ToDouble(pStreng3.strengthenValue);
    
    CCSize visibleSize = CCDirector::sharedDirector() -> getVisibleSize();
    CCAnimation* pAni = CCAnimation::create();
    CCString str;
    for (int i = 1; i <=8; i ++)
    {
        str.initWithFormat("PigLittleBrother_%d.png",i);
        
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str.getCString());
        pAni-> addSpriteFrame(frame);
    }
    
    pAni->setDelayPerUnit(0.12f);
    pAni->setLoops(1);
    CCSprite* p = CCSprite::createWithSpriteFrameName("PigLittleBrother_1.png");
    p->setPosition(ccp(visibleSize.width/2 - 15,visibleSize.height - p->getContentSize().height/2 - 93 + 68));
    p->runAction(CCRepeatForever::create(CCAnimate::create(pAni)));
    this->addChild(p, 0);

    return true;
}

void Game_Memory::RewardByStrengthen(double a, double b, double c) {
   
    srand((unsigned)this->getCurrentTime());
    int number = rand()%1000 + 1;
    if (number <= 1000*a) {
        onceAgain = true;
    }
    else if (number <= 1000 * (a+c)) {
        isHighScoreCard_1 = true;
        //5k
    }
    else if (number <= 1000 * (a+c+b)) {
        isGoldCard = true;
        //金币
    }
}
void Game_Memory::startGame(float dt)
{
    if (Props_three) {
        Props_three = false;
        Crazy_Start(3, eSuperCrazyMode);
        game_mode = Mode_SuperCrazy;
    }
    
    //超强道具
    super_Props_Strengthen = CItemMan::sharedInstance().useItem(ItemTag_13);
    super_Props_notMiss = CItemMan::sharedInstance().useItem(ItemTag_14);
    
    if (super_Props_Strengthen) {
        Gold = 0.25;
        Scorecard = 0.2;
        Otherscore = 0.11;
        super_Props_Strengthen = false;
    }
    
    if (super_Props_notMiss) {
        Props_one = true;
        have_props_one = true;
    }
    
    
    //牌初始化
    for (int i=0; i<4; i++) {
        for (int j=0; j<3; j++) {
            Game_MemoryCard *hero1 = Game_MemoryCard::spriteModelWithFile();
            hero1->setPosition(ccp(130+j*188, 235+i*163));
            this->addChild(hero1);
            hero1->setTag(i*3+j);
            hero1->setPic(0);
        }
    }
    back -> setTouchEnable(false);
    this->resetView(0);
    this->schedule(schedule_selector(Game_Memory::showHelp), Time_Help);
}
void Game_Memory::setCareWithType(int type)
{
    nowCilck = 0;
    nowtype = -1;
    total = 12;
    
    for (int i=0; i<4; i++) {
        for (int j=0; j<3; j++) {
            
            ((Game_MemoryCard*)this->getChildByTag(i*3+j))->setPic(0);
            ((Game_MemoryCard*)this->getChildByTag(i*3+j))->setClose();
        }
    }
    for (int i=0; i<total/2; i++) {
        
        if (((Game_MemoryCard*)this->getChildByTag(i))->getType() == 0) {
            ((Game_MemoryCard*)this->getChildByTag(i))->setPic(type);
            ((Game_MemoryCard*)this->getChildByTag(i))->openCard();
        }
        if (((Game_MemoryCard*)this->getChildByTag(i+6))->getType() == 0) {
            ((Game_MemoryCard*)this->getChildByTag(i+6))->setPic(type);
            ((Game_MemoryCard*)this->getChildByTag(i+6))->openCard();
        }
    }
    preTime = getCurrentTime();
    this->isBoom = false;
}
void Game_Memory::resetView(float)
{
    cardListByOneBox cardBox;

    firstCard = 0;
    secondCard = 100;
    onceAgain = false;
    isHighScoreCard_1 = false;
    isGoldCard = false;

    
    this->RewardByStrengthen(Otherscore, Gold, Scorecard);
    if (isBoom) {
        this->setCareWithType(23);
        return;
    }
    srand((unsigned)this->getCurrentTime());
    int isLucky = rand()%99;
    if (isLucky<3) {
        srand((unsigned)this->getCurrentTime());
        oneAgainCount++;
        this->setCareWithType(rand()%3 + 18);
        return;
    }
    nowCilck = 0;
    nowtype = -1;
    //According to the difficulty of computing
    total = 2;
    srand((unsigned)this->getCurrentTime());

    if (batter>Level_0 && batter<Level_1) {
        total = 2*(rand()%2+1);
    }else if(batter>=Level_1 && batter<Level_2){
        total = 2*(rand()%2+2);
    }else if(batter>=Level_2 && batter<Level_3){
        total = 2*(rand()%2+3);
    }else if (batter>=Level_3){
        total = 2*(rand()%2+4);
    }else if (batter>=Level_4){
        total = 2*(rand()%2+5);
    }
    for (int i=0; i<4; i++) {
        for (int j=0; j<3; j++) {
            ((Game_MemoryCard*)this->getChildByTag(i*3+j))->setPic(0);
            ((Game_MemoryCard*)this->getChildByTag(i*3+j))->setClose();
        }
    }
    srand((unsigned)this->getCurrentTime());
    if (onceAgain) {
        oneAgainCount++;
        srand((unsigned)this->getCurrentTime());
        int type = rand()%3 + 18;
        cardBox.cardList.push_back(type);
        this->setCareWithType(type);
        return;
    }
    // 使用道具2 ，20%几率出现3行同样的卡
    else if (Props_tow && rand()%5 == 1) {
        propEasyGameCount ++;
        total = 12;
        for (int i = 0; i < 3; i ++) {
            int type = rand()%17 + 1;
            if (batter <=Level_0) {
                type = rand()%2 + 1;
            }else if (batter>Level_0 && batter<Level_1) {
                type = rand()%3 + 1;
            }else if (batter>=Level_1 && batter<Level_2){
                type = rand()%6 + 1;
            }else if (batter>=Level_2 && batter<Level_3){
                type = rand()%10 + 1;
            }else if (batter>=Level_3){
                type = rand()%12 + 1;
            }else if (batter>=Level_4){
                type = rand()%16 + 1;
            }
            
            //道具4
            if (Props_four) {
                type = cardTypy[rand()%6];
            }
            bool wellPush = true;
            for (int k = 0; k < cardTypeList.size(); k++) {
                if (cardTypeList[k] == type) {
                    wellPush = false;
                }
            }
            if (wellPush) {
                cardTypeList.push_back(type);
            }
            cardBox.cardList.push_back(type);
            for (int j = i; j < 12; j+=3) {
                ((Game_MemoryCard*)this->getChildByTag(j))->setPic(type);
                ((Game_MemoryCard*)this->getChildByTag(j))->openCard();
            }
        }
    }
    else {
        for (int i=0; i<total/2; i++) {
            int type = rand()%18 + 1;
            if (batter <=Level_0) {
                type = rand()%2 + 1;
            }else if (batter>Level_0 && batter<Level_1) {
                type = rand()%3 + 1;
            }else if (batter>=Level_1 && batter<Level_2){
                type = rand()%6 + 1;
            }else if (batter>=Level_2 && batter<Level_3){
                type = rand()%10 + 1;
            }else if (batter>=Level_3){
                type = rand()%12 + 1;
            }else if (batter>=Level_4){
                type = rand()%16 + 1;
            }
            //道具4
            if (Props_four) {
                type = cardTypy[rand()%6];
            }

            //是否出现高分牌
            if (isHighScoreCard && i==0) {
                type = 21;
                isHighScoreCard = false;
            }
            if (isHighScoreCard_1 && i==0) {
                type = 22;
                isHighScoreCard_1 = false;
            }
            if (isGoldCard && i==0) {
                type = 26;
                isGoldCard = false;
            }
            
            bool wellPush = true;
            for (int k = 0; k < cardTypeList.size(); k++) {
                if (cardTypeList[k] == type) {
                    wellPush = false;
                }
            }
            if (wellPush) {
                cardTypeList.push_back(type);
            }
            cardBox.cardList.push_back(type);
            int position;
            position = rand()%12;
            
            while (((Game_MemoryCard*)this->getChildByTag(position))->getType() != 0) {
                srand((unsigned)this->getCurrentTime());
                position = rand()%12;
            }
            if (((Game_MemoryCard*)this->getChildByTag(position))->getType() == 0) {
                ((Game_MemoryCard*)this->getChildByTag(position))->setPic(type);
                ((Game_MemoryCard*)this->getChildByTag(position))->openCard();
            }
            
            position = (rand()%12);
            while (((Game_MemoryCard*)this->getChildByTag(position))->getType() != 0) {
                srand((unsigned)this->getCurrentTime());
                position = (rand()%12);
            }
            if (((Game_MemoryCard*)this->getChildByTag(position))->getType() == 0) {
                ((Game_MemoryCard*)this->getChildByTag(position))->setPic(type);
                ((Game_MemoryCard*)this->getChildByTag(position))->openCard();
            }
            
        }
    }
    allCardList.push_back(cardBox);
    preTime = getCurrentTime();
}

#pragma mark get time;
long  Game_Memory::getCurrentTime()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

#pragma mark touch
cocos2d::CCRect Game_Memory::rect(CCNode *pNode)
{
    //
    CCRect rc;
    rc.origin = pNode->getPosition();
    rc.size = pNode->getContentSize();
    rc.origin.x -= rc.size.width*pNode->getAnchorPoint().x;
    rc.origin.y -= rc.size.height*pNode->getAnchorPoint().y;
    return rc;
}
int Game_Memory::isTouchInside( CCTouch* touch)
{
    CCPoint touchLocation = touch->getLocation(); //
    CCPoint localPos = convertToNodeSpace(touchLocation);
    bool isTouched = -1;
    for (int i=0; i<4; i++) {
        for (int j=0; j<3; j++) {
            CCRect rc = rect(((Game_MemoryCard*)this->getChildByTag(i*3+j)));
            isTouched = rc.containsPoint(localPos);
            if (isTouched) {
                if (((Game_MemoryCard*)this->getChildByTag(i*3+j))->isOpen()) {
                    return -1;
                }
                return i*3+j;
            }
        }
    }
    return -1;
}


void Game_Memory::ccTouchesBegan(CCSet * set,CCEvent * e)
{
        CCSetIterator iter=set->begin();
        for(;iter!=set->end();iter++){
            CCTouch * mytouch=(CCTouch *)(* iter);
            if (set->count() == 2) {
                this->TouchMoved(mytouch, e, true);
            }else {
                this->TouchMoved(mytouch, e, false);
            }
        }
    
}
void Game_Memory::ccTouchesMoved(CCSet * set,CCEvent * e) {
    if (set -> count() == 1) {
        CCSetIterator iter=set->begin();
        CCTouch * mytouch=(CCTouch *)(* iter);
        this->TouchMoved(mytouch, e, false);
    }
}
void Game_Memory::ccTouchesEnded(CCSet * set, CCEvent *e) {
    
}

void Game_Memory::TouchMoved(CCTouch* touch, CCEvent* event, bool isFirstDoubel)
{
    int i = isTouchInside(touch);
    //Judge which button is clicked.
    
    if( i >= 0 && clickFalseSprite->numberOfRunningActions()==0 && rightSprite->numberOfRunningActions()==0)
    {
        this->Crazy_ReStart();
        //Judge is now type.
        if (nowCilck == 0) {
            nowtype = -1;
        }
        nowCilck ++;
        if (nowCilck % 2 == 1) {
            firstCard = ((Game_MemoryCard*)this->getChildByTag(i))->getType();
        }
        else {
            secondCard = ((Game_MemoryCard*)this->getChildByTag(i))->getType();
        }
        if (((Game_MemoryCard*)this->getChildByTag(i))->getType() == 0 || (firstCard != secondCard && nowCilck % 2 == 0)) {
            if (isMiss) {
                MissCount ++;
            }
            missNumber ++;
            isMiss = true;
            //若有道具1
            if (Props_one && (((Game_MemoryCard*)this->getChildByTag(i))->getType() == 0 || (firstCard != secondCard && nowCilck % 2 == 0))) {
//                back -> setTouchEnable(true);
                if (have_props_one) {
                    this->rewardEffect(i, 0);
                    have_props_one = false;
                }
            }
            else {
                this->Crazy_End();
                this -> unscheduleAllSelectors();
                if (superModelTimecount > superModelTime) {
                    superModelTime = superModelTimecount;
                }
                superModelTimecount = 0;
                batter = 0;
                this->clickFalse(((Game_MemoryCard*)this->getChildByTag(i))->getPosition());
            }
        }
        else {
            ((Game_MemoryCard*)this->getChildByTag(i))->clickCard();
            if (nowCilck == 0 || nowCilck == 1) {
                if (isFirstDoubel && nowCilck == 0) {
                    firstPlace = i;
                } else if (isFirstDoubel && nowCilck == 1) {
                    for (int k=0; k<4; k++) {
                        for (int j=0; j<3; j++) {
                            if (i != (k*3+j) || firstPlace != (k*3+j)) {
                                ((Game_MemoryCard*)this->getChildByTag(k*3+j))->setClose();
                            }
                            
                        }
                    }
                }
                else if (!isFirstDoubel){
                    for (int k=0; k<4; k++) {
                        for (int j=0; j<3; j++) {
                            if (i != (k*3+j)) {
                                ((Game_MemoryCard*)this->getChildByTag(k*3+j))->setClose();
                            }
                            
                        }
                    }
                }
            }
            long nowTime = this->getCurrentTime();
            if (nowTime-preTime > 1000.0f*batterTime) {
                batter = 0;
                batterTime = Batter_Normal;
                this->Crazy_End();
                this -> unscheduleAllSelectors();
                if (superModelTimecount > superModelTime) {
                    superModelTime = superModelTimecount;
                }
                superModelTimecount = 0;
            }
            preTime = this->getCurrentTime();
            char str[32];
            if (batter == 0) {
                sprintf(str,"%s0%d.caf",EFFECT_CLICK,1);
            }
            else if (batter<BatterToCrazy-1) {
                sprintf(str,"%s0%d.caf",EFFECT_CLICK,batter);
            }else if (batter == BatterToCrazy-1) {
                sprintf(str,"%s10.caf",EFFECT_CLICK);
            }else if (batter > BatterToCrazy-1) {
                sprintf(str,"%s_max.caf",EFFECT_CLICK);
            }
            
            if (nowCilck % 2 == 1) {
                auto *pic = CCSprite::create("./effect/bomb_little/1.png");
                pic -> setPosition(((Game_MemoryCard*)this->getChildByTag(i))->getPosition());
                CCAnimation* pAni = CCAnimation::create();
                CCString str_1;
                for (int i = 1; i <= 5; ++i)
                {
                    str_1.initWithFormat("./effect/bomb_little/%d.png",i);
                    pAni->addSpriteFrameWithFileName(str_1.getCString());
                }
                addChild(pic, 5);
                pAni->setDelayPerUnit(.04);
                
                CCAnimate *animate = CCAnimate::create(pAni);
                pic->runAction(CCSequence::create(CCShow::create(),CCRepeat::create(animate, 1),CCHide::create(),NULL));
                
            }
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(std::string(CCFileUtils::sharedFileUtils()->fullPathFromRelativeFile(str,"")).c_str());
            if (firstCard == secondCard) {
                isMiss = false;
                
                rightCardCount ++;
                //判断是否是第一个炸弹.
                if (nowtype == 23 && nowCilck == 2) {
                    this->time_addSecond(5);
                    this->rewardEffect(i, nowtype);
                }
                if (nowCilck % 2 == 0) {
                    batter++;
                    allbatter++;
                    setBatter(batter);
                    if (batter > bigestBatter) {
                        bigestBatter = batter;
                    }
                }
              
                if (allbatter%20 == 0) {
                    isHighScoreCard = true;
                }
                
                if (batter == BatterToCrazy && game_mode != Mode_SuperCrazy) {
                    this->Crazy_Start(Batter_Normal, eComCrazyMode);
                    
                }
                else if (batter == BatterToSuperCrazy) {
                    superModelCount++;
                    this -> schedule(schedule_selector(Game_Memory::superModeltimeCountbegin), 1);
                    this->Crazy_Start(Batter_Normal, eSuperCrazyMode);
                }
                this->clickTrue(((Game_MemoryCard*)this->getChildByTag(i))->getPosition());
                //分数的倍数
                int level;
                switch (game_mode) {
                    case Mode_Normal:
                        level = NormalMultiple;
                        break;
                    case Mode_Crazy:
                        level = CrazyMultiple;
                        break;
                    case Mode_SuperCrazy:
                        level = SuperCrazyMultiple;
                        break;
                        
                    default:
                        break;
                }
                long addition = 0;
                //是否加成牌
                if (nowtype == 21) {
                    addition = 20000;
                    rewardCardCount ++;
                    secore2wCount ++;
                    CCUserDefault::sharedUserDefault()->setIntegerForKey("medal600165", rewardCardCount);
        

                    this->rewardEffect(i, nowtype);
                }
                if (nowtype == 22) {
                    addition = 50000;
                    this->rewardEffect(i, nowtype);
                }
                if (nowtype == 26) {
                    //增加金币
                    addGoldNumber += 3;
                }
                score += addition + (batter + batter*batter)*level + (BaseSocre + AddSocre*(batter-1));
                this->setScore(score);
                if (batter>=BatterToSuperCrazy) {
                    game_mode = Mode_SuperCrazy;
                    batterTime = Batter_SuperCrazy;

                    
                }else if (batter>=BatterToCrazy) {
                    game_mode = Mode_Crazy;
                    batterTime = Batter_Crazy;
                    
                  
                }
                this->boom_addEnergy(EachEnergy);
                
                CCString str;
                str.initWithFormat("medal600019_%d", GameShare_Global::shareGlobal()->gameType);
                int number = CCUserDefault::sharedUserDefault()->getIntegerForKey(str.getCString());
                number = number?number:0;
                if (batter > number) {
                     CCUserDefault::sharedUserDefault()->setIntegerForKey(str.getCString(), batter);
                }
            }
            nowtype = ((Game_MemoryCard*)this->getChildByTag(i))->getType();
            
            if (nowCilck == total ) {
                this->showRight();
            }
        }
        preTime = this->getCurrentTime();
    }
    
}

void Game_Memory::initBgView()
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCSprite* pSprite = CCSprite::create("./CocoStudioResources/GameMemory/GameMemoryBg.png");
	pSprite->setPosition(ccp(visibleSize.width/2 , visibleSize.height/2));
	this->addChild(pSprite, 0);
}

#pragma mark effect
void Game_Memory::clickTrue(cocos2d::CCPoint point)
{
    CCAnimation* pAni = CCAnimation::create();
    CCString str;
    for (int i = 1; i <=5; ++i)
    {
        str.initWithFormat("./effect/bomb/%d.png",i);
        pAni->addSpriteFrameWithFileName(str.getCString());
    }
    
    pAni->setDelayPerUnit(.12);

    CCAnimate *animate = CCAnimate::create(pAni);
    
    clickTrueSprite->setPosition(point);
    clickTrueSprite->runAction(CCSequence::create(CCShow::create(),CCRepeat::create(animate, 1),CCHide::create(),NULL));
}
void Game_Memory::clickFalse(cocos2d::CCPoint point)
{
    clickFalseSprite->setPosition(point);
    
    CCPoint pointL=point;
    CCPoint pointR=point;
    pointL.x-=15;
    pointR.x+=15;
    CCFiniteTimeAction* moveLeft = CCMoveTo::create(0.04, pointL);
    CCFiniteTimeAction* moveRight=CCMoveTo::create(0.04, pointR);
    CCFiniteTimeAction* moveMiddle=CCMoveTo::create(0.04, point);
    CCFiniteTimeAction* action= CCSequence::create(moveLeft,moveRight,NULL);
    clickFalseSprite->runAction(CCSequence::create(CCShow::create(),CCRepeat::create(action, 1),moveMiddle,CCDelayTime::create(0.2), CCHide::create(), NULL));
    scheduleOnce(schedule_selector(Game_Memory::resetView), 0.5);
}
void Game_Memory::showRight()
{
    CCActionInterval *blinkAction = CCBlink::create(0.5, 2);
    rightSprite->runAction(CCSequence::create(CCShow::create(), blinkAction, CCHide::create(), NULL));
    scheduleOnce(schedule_selector(Game_Memory::resetView), 0.5);
}
#pragma mark boom
void Game_Memory::msgHanlde_BoomFull(cocos2d::CCObject *obj)
{
    boomCount ++;
    this->isBoom = true;
}
#pragma mark help
void Game_Memory::showHelp(float dt)
{
    long time = this->getCurrentTime();
    if (time-preTime > 1000.0f*Time_Help) {
        if (nowCilck%2==0) {
            for (int i=0; i<4; i++) {
                for (int j=0; j<3; j++) {
                    if (!((Game_MemoryCard*)this->getChildByTag(i*3+j))->isOpen() && ((Game_MemoryCard*)this->getChildByTag(i*3+j))->getType() != 0) {
                        ((Game_MemoryCard*)this->getChildByTag(i*3+j))->clickCard();
                        nowCilck++;
                        firstCard = ((Game_MemoryCard*)this->getChildByTag(i*3+j))->getType();
                        break;
                    }
                }
                if (nowCilck%2 != 0) {
                    break;
                }
            }
        }
    }
}

void Game_Memory::rewardEffect(int tag, int kind) {
    CCSprite *pic;
    if (kind == 23) {
        pic = CCSprite::create(img5Second);
        pic ->setScale(0.3);
    }
    else if (kind == 21) {
        pic = CCSprite::create(img20000);
        pic -> setScale(0.7);
    }
    else if (kind == 22){
        pic = CCSprite::create(img50000);
        pic -> setScale(0.7);
    }
    else {
        pic = CCSprite::create(imgShield);
        pic ->setScale(2);
    }
    pic ->setPosition(((Game_MemoryCard*)this->getChildByTag(tag))->getPosition());
    pic ->setTag(1000);
    CCMoveBy *upMove = CCMoveBy::create(0.3, ccp(0, 10));
    CCScaleTo *sizeChange = CCScaleTo::create(0.3, 0.1);
    CCFadeTo *aph = CCFadeTo::create(0.3, 0);
    CCCallFunc *actionStopCallBack = CCCallFunc::create(this, callfunc_selector(Game_Memory::callBack));
    CCCallFunc *actionStopCallBack_1 = CCCallFunc::create(this, callfunc_selector(Game_Memory::callBack_1));
    this->addChild(pic);
    if (kind == 0) {
        pic-> runAction(CCSequence::create(upMove,sizeChange,aph,actionStopCallBack,actionStopCallBack_1, NULL));
    }
    else {
           pic-> runAction(CCSequence::create(upMove,sizeChange,aph,actionStopCallBack, NULL));
    }
}
void Game_Memory::MedalInfoBack(CCObject *p) {
    CCLOG("medalinfoget");
}
void Game_Memory::callBack() {
    this->removeChildByTag(1000);
}
void Game_Memory::callBack_1() {
    if (Props_one) {
        resetView();
        Props_one = super_Props_notMiss;
        have_props_one = Props_one;
        super_Props_notMiss = false;
        back -> setTouchEnable(false);
    }
}

void Game_Memory::resurgeCallfunc(int nTimes) {
    resetView();
}

void Game_Memory::msgHanlde_GameTimeOut(CCObject* obj) {
    addMoney = addGoldNumber;
    if (CCUserDefault::sharedUserDefault()->getBoolForKey("P_2")) {
        CTaskManProceDt(eDayTaskTypeTK_64, 1);
    }
    if (CCUserDefault::sharedUserDefault()->getBoolForKey("P_4")) {
        CTaskManProceDt(eDayTaskTypeTK_65, 1);
    }
    CTaskManProce(eDayTaskTypeShare_1, score);
    CTaskManProce(eDayTaskTypeShare_4, allbatter);
    CTaskManProce(eDayTaskTypeShare_5, scoreBy20);
    CTaskManProce(eDayTaskTypeShare_6, superModelTime);
    CTaskManProce(eDayTaskTypeShare_7, bigestBatter);
    CTaskManProce(eDayTaskTypeShare_8, boomCount);
    if (!CCUserDefault::sharedUserDefault()->getBoolForKey("P_1") && !CCUserDefault::sharedUserDefault()->getBoolForKey("P_2")&&!CCUserDefault::sharedUserDefault()->getBoolForKey("P_3")&&!CCUserDefault::sharedUserDefault()->getBoolForKey("P_4")) {
        CTaskManProceDt(eDayTaskTypeShare_9, 1);
    }
    int count = 0;
    CCString str;
    for (int i = 1; i <= 4; i++) {
        str.initWithFormat("P_%d", i);
        if (CCUserDefault::sharedUserDefault()->getBoolForKey(str.getCString())) {
            count ++;
        }
    }
    CTaskManProce(eDayTaskTypeShare_10, count);
    if (score == 0) {
        CTaskManProceDt(eDayTaskTypeShare_11, 1);
    }
    CTaskManProce(eDayTaskTypeShare_12, missNumber);
    if (score>= 50000 && boomCount == 0) {
        CTaskManProceDt(eDayTaskTypeShare_13, 1);
    }
    
    
    
    CTaskManProce(eDayTaskTypeTK_66, cardTypeList.size());
    CTaskManProceDt(eDayTaskTypeTK_67, rightCardCount);
    CTaskManProce(eDayTaskTypeTK_68, secore2wCount);
    CTaskManProceDt(eDayTaskTypeTK_69, secore2wCount);
    CTaskManProceDt(eDayTaskTypeTK_70, addGoldNumber/3);
    CTaskManProceDt(eDayTaskTypeTK_71, oneAgainCount);
    CTaskManProceDt(eDayTaskTypeTK_72, MissCount);
    CTaskManProce(eDayTaskTypeTK_73, checkNumberOfTheLongestCard());
    CTaskManProce(eDayTaskTypeTK_74, propEasyGameCount);
    CTaskManProce(eDayTaskTypeTK_75, addGoldNumber);
    
    allCardList.clear();
    CPlayerInfoMan::sharedInstance().RequestAddGold(addGoldNumber);
    GameShare_Scene::msgHanlde_GameTimeOut(obj);
}

void Game_Memory::superModeltimeCountbegin(float) {
    superModelTimecount ++;
}

void Game_Memory::noticeTimeInterval(cocos2d::CCObject *obj) {
    if (((GameShare_TimeProcess*)obj)->GetSecondsRemain() == 40) {
        scoreBy20 = score;
    }
   
    GameShare_Scene::noticeTimeInterval(obj);
}
int Game_Memory::checkNumberOfTheLongestCard() {
    int longth = 0;
    for (int j = 1; j <= 26; j ++) {
        int lg = 0;
        for (int i = 0; i < allCardList.size(); i++) {
            cardListByOneBox box = allCardList[i];
            bool haveNumber = false;
            for (int k = 0; k < box.cardList.size(); k ++) {
                if (j == box.cardList[k]) {
                    haveNumber = true;
                    lg ++;
                }
            }
            if (!haveNumber) {
                if (lg > longth) {
                    longth = lg;
                }
                lg = 0;
            }
        }
        if (lg > longth) {
            longth = lg;
        }
    }
    return longth;
}
