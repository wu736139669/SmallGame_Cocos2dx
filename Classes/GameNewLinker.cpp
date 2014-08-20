//
// GameNewLinker.cpp
// OnceAgain
//
// Created by xiaohai on 14-5-19.
//
//

#include "GameNewLinker.h"
#include "GameUIExportJson.h"
#include <time.h>
#include "RandomUtil.h"
#include "TimeUtil.h"
#include "SpriteFrameManage.h"
#include "GameUIExportJson.h"
#include "PlayerInfoManager.h"
#include "StringUtil.h"
#include "GameNewLinkerMaps.h"
#include "TaskDefine.h"
#include "GameItemManager.h"

//星星
#define StarIcon 7
//礼盒
#define Box_5w 8

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#define myRand arc4random()

#else

#define myRand rand()

#endif

CCScene* GameNewLinker::createScene()
{
    auto scene = CCScene::create();
    auto layer = GameNewLinker::create();
    scene->addChild(layer);
    return scene;
}

bool GameNewLinker::init()
{
    if ( !GameShare_Scene::init() )
    {
        return false;
    }
    Batter_Normal_link       = 2;
    Batter_Crazy_link        = 1.5;
    Batter_SuperCrazy_link   = 1.5;
    
    boxCount = 0;
    easyListCount = 0;
    starCount = 0;
    timeBefore10 = true;
    rigthCount = 0;
    allbatter = 0;
    superModelCount = 0;
    scoreBy20 = 0;
    superModelTimecount = 0;
    superModelTime = 0;
    bigestBatter = 0;
    boomCount = 0;
    missNumber = 0;
    
    lineNode = CCNode::create();
    lineNode -> setPosition(0, 0);
    this -> addChild(lineNode, 2);
    
    sharderNode = CCNode::create();
    sharderNode -> setPosition(0, 0);
    this -> addChild(sharderNode, 1);
  
    colorBox cBox_1;
    cBox_1.color = ccc4(10,103,108,255);
    cBox_1.index = 1;
    
    colorBox cBox_2;
    cBox_2.color = ccc4(126,112,0,255);
    cBox_2.index = 2;

    colorBox cBox_3;
    cBox_3.color = ccc4(110,25,36,255);
    cBox_3.index = 3;

    colorBox cBox_4;
    cBox_4.color = ccc4(21,59,93,255);
    cBox_4.index = 4;

    colorBox cBox_5;
    cBox_5.color = ccc4(16,98,0,255);
    cBox_5.index = 5;

    colorBox cBox_6;
    cBox_6.color = ccc4(144,51,110,255);
    cBox_6.index = 6;
    
    colorList.push_back(cBox_1);
    colorList.push_back(cBox_2);
    colorList.push_back(cBox_3);
    colorList.push_back(cBox_4);
    colorList.push_back(cBox_5);
    colorList.push_back(cBox_6);
    
    _HaveBox = false;
    _HaveStar = false;
    _EasyGame = false;
    
    boom_setEnergy(0);
    isBoomFull = false;
    isCanDrawLine = false;
    first_box = 100;
    sencond_box = 100;
    score = 0;
    gameBatterType = 1;
    pointsCount = 0;//关卡计数
    linkOkCounts = 0;//需要成功配对的对数
    betterTime = Batter_Normal_link;
    littleMapsIcons.clear();
    bigMapsIcons.clear();
    list.clear();
    creatTileMaps();
    
    p_1_miss = CCUserDefault::sharedUserDefault() -> getBoolForKey("P_2");
    p_2_superModel = CCUserDefault::sharedUserDefault() -> getBoolForKey("P_1");
    p_3_timeAdd = CCUserDefault::sharedUserDefault() -> getBoolForKey("P_3");
    p_4_batter = CCUserDefault::sharedUserDefault() -> getBoolForKey("P_4");
    
    sMGameStrengthen pStreng1;
    CPlayerInfoMan::sharedInstance().getMStrengthenByGameId(Game_Link, StrengThenTag_8, pStreng1);
    //高分
    sMGameStrengthen pStreng2;
    CPlayerInfoMan::sharedInstance().getMStrengthenByGameId(Game_Link, StrengThenTag_9, pStreng2);
    //奖励
    sMGameStrengthen pStreng3;
    CPlayerInfoMan::sharedInstance().getMStrengthenByGameId(Game_Link, StrengThenTag_10, pStreng3);
    
    Strengthen = CStringUtil::ToDouble(pStreng1.strengthenValue);
    starShow = CStringUtil::ToDouble(pStreng2.strengthenValue);
    easyGameList = CStringUtil::ToDouble(pStreng3.strengthenValue);
    
    if (p_4_batter) {
        Batter_Normal_link += 0.5;
        Batter_Crazy_link += 0.5;
        Batter_SuperCrazy_link += 0.5;
    }
    return true;
}

void GameNewLinker::checkThePropsUseStatus() {
    _HaveBox = false;
    _HaveStar = false;
    _EasyGame = false;
    if (!isBoomMap) {
        int num = myRand%1000 + 1;
        if (num >= 0 && num < easyGameList*1000) {
            _EasyGame = true;
        }
        if (num >= easyGameList*1000 && num < (easyGameList+starShow) * 1000) {
            _HaveStar = true;
        }
        if (num >= (easyGameList+starShow) * 1000 && num < (easyGameList+starShow+Strengthen) * 1000) {
            _HaveBox = true;
        }
    }
}

void GameNewLinker::initBgView(void) {
    CCSize vis = CCDirector::sharedDirector() -> getVisibleSize();
    //设置背景
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("./Link/Link0.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("./Link/linkerPic.plist");
    
    auto *picTop = CCSprite::createWithSpriteFrameName("top.png");
    picTop -> setAnchorPoint(ccp(0, 1));
    picTop -> setPosition(ccp(0, vis.height));

    auto *picDown = CCSprite::createWithSpriteFrameName("bottom.png");
    picDown -> setAnchorPoint(ccp(0, 0));
    picDown -> setPosition(ccp(0, 0));
    
    clickRoundTabel = CCSprite::create("./Link/clickCircle.png");
    clickRoundTabel -> setVisible(false);
    addChild(clickRoundTabel, 1000);
    
    addChild(picTop);
    addChild(picDown);
    
    CCAnimation* pAni = CCAnimation::create();
    CCString str;
    for (int i = 1; i <=13; ++i)
    {
        str.initWithFormat("role/pig_grandpa/%d.png",i);
        pAni->addSpriteFrameWithFileName(str.getCString());
    }
    
    pAni->setDelayPerUnit(0.12f);
    pAni->setLoops(1);
    CCSprite* p = CCSprite::create("role/pig_grandpa/1.png");
    p->setPosition(ccp(vis.width/2 ,vis.height - p->getContentSize().height/2 - 93 + 68));
    p->runAction(CCRepeatForever::create(CCAnimate::create(pAni)));
    this->addChild(p, 0);
}

void GameNewLinker::creatTileMaps() {
    //5*5地图
    std::string yellow = "yellow.png";
    std::string blue = "blue.png";
    CCSprite *modlePic = CCSprite::createWithSpriteFrameName(blue.c_str());
    littleMiles = (CCDirector::sharedDirector()->getVisibleSize().width/5)/(modlePic->getContentSize().width);
    bigMidles = (CCDirector::sharedDirector()->getVisibleSize().width/6)/(modlePic->getContentSize().width);
    modlePic -> release();
    for (int i = 0; i < 5; i ++) {
        for (int j = 0; j < 5; j ++) {
            CCSprite *pic;
            if ((i+j)%2 == 0) {
                pic = CCSprite::createWithSpriteFrameName(yellow.c_str());
            }
            else {
                pic = CCSprite::createWithSpriteFrameName(blue.c_str());
            }
            pic -> setScale(littleMiles);
            pic -> setAnchorPoint(ccp(0, 0));
            pic -> setPosition(ccp(pic->getContentSize().width*j +2, pic->getContentSize().height * i + 160));
            this -> addChild(pic, 0);
            littleMapsIcons.push_back(pic);
        }
    }
    //6*6地图
    for (int m = 0; m < 6; m ++) {
        for (int n = 0; n < 6; n ++) {
            CCSprite *pic;
            if ((m+n)%2 == 0) {
                pic = CCSprite::createWithSpriteFrameName(yellow.c_str());
            }
            else {
                pic = CCSprite::createWithSpriteFrameName(blue.c_str());
            }
            pic -> setScale(bigMidles);
            pic -> setAnchorPoint(ccp(0, 0));
            pic -> setPosition(ccp(pic->getContentSize().width*bigMidles*n +2, pic->getContentSize().height*bigMidles * m + 160));
            this -> addChild(pic, 0);
            bigMapsIcons.push_back(pic);
            pic -> setVisible(false);
        }
    }
}
void GameNewLinker::initPointsStuta() {
    preTime = this->getCurrentTime();
    isCanDrawLine = false;
    picKindList.clear();
    for (int i = 0; i < 6; i ++) {
        picKindList.push_back(i+1);
    }
    if (p_2_superModel) {
        p_2_superModel = false;
        betterTime = Batter_SuperCrazy_link;
        Crazy_Start(10.f, eSuperCrazyMode);
        this -> schedule(schedule_selector(GameNewLinker::superModelTimeCountbegin), 1);
        superModelCount ++;
        gameBatterType = 3;
    }
    lineNode -> removeAllChildrenWithCleanup(true);
    sharderNode -> removeAllChildrenWithCleanup(true);
    //当前页面是否是炸弹页面
    isBoomMap = isBoomFull;
    isBoomAddTime = isBoomMap;
    isBoomFull = false;
    pointsCount ++;//关卡加1
    //强化随机
    checkThePropsUseStatus();
    //清除所有线条
    linelist.clear();
    sharderList.clear();
    //清除动物列表
    for (int i = 0; i < AnimalList.size(); i++) {
        AnimalList[i] -> removeFromParent();
    }
    AnimalList.clear();
    //根据关卡重新获取地图
    std::vector<int>list1;//地图数据
    while (1) {
        list1 = GameNewLinkerMaps::getMapByPoints(pointsCount);
        if (list != list1) {
            list.clear();
            list = list1;
            break;
        }
        list1.clear();
    }
    if (_EasyGame) {
        easyListCount ++;
        list.clear();
        list = GameNewLinkerMaps::getEasyListMap(pointsCount);
    }
    if (isBoomMap) {
        list.clear();
        list = GameNewLinkerMaps::getBoomMap(pointsCount);
    }
    //倒转地图
    rookTheList();
    //地图方块显示
    for (int i = 0; i < littleMapsIcons.size(); i ++) {
        littleMapsIcons[i] -> setVisible(pointsCount <= 25);
    }
    for (int j = 0; j < bigMapsIcons.size(); j ++) {
        bigMapsIcons[j] -> setVisible(pointsCount > 25);
    }
    size = (pointsCount <= 25)?littleMiles:bigMidles;
    //动物显示
    spritelistNow = (pointsCount <= 25)?littleMapsIcons:bigMapsIcons;
    std::vector<int>animalsKinds;
    for (int i = 0; i < list.size(); i ++) {
        if (list[i] < 10 && list[i] > 0) {
            bool push = true;
            for (int j = 0; j < animalsKinds.size(); j ++) {
                if (animalsKinds[j] == list[i]) {
                    push = false;
                }
            }
            if (push) {
                animalsKinds.push_back(list[i]);
            }
        }
    }
    for (int i = 0;  i < animalsKinds.size(); i++) {
        int length = picKindList.size();
        int index = myRand%length;
        int picNumber = picKindList[index];
        std::vector<int>piclist_1;
        for (int j = 0 ;j < picKindList.size(); j ++) {
            if (picKindList[j] == picNumber) {
                
            }
            else {
                piclist_1.push_back(picKindList[j]);
            }
        }
        picKindList.clear();
        picKindList = piclist_1;
        piclist_1.clear();
        for (int j = 0; j < list.size(); j ++) {
            if (list[j] == animalsKinds[i]) {
                auto *pic = GameNewLinkerItems::create();
                pic -> createPicByTag(list[j], isBoomMap, picNumber);
                pic -> setPosition(ccp(spritelistNow[j]->getPosition().x+spritelistNow[1]->getContentSize().width/2*size, spritelistNow[j]->getPosition().y+ spritelistNow[1]->getContentSize().height/2*size));
                pic -> setScale(size);
                addChild(pic, 3);
                AnimalList.push_back(pic);
            }
        }
    }
    linkOkCounts = AnimalList.size()/2;
    //线条边缘颜色随机排列
    vector<colorBox>colorlist1;
    while (1) {
        int length = colorList.size();
        if (length > 0) {
            int index = myRand%length;
            colorlist1.push_back(colorList[index]);
            vector<colorBox>colorlist2;
            for (int i = 0; i < length; i ++) {
                if (colorList[i].index == colorList[index].index){
                    continue;
                }
                colorlist2.push_back(colorList[i]);
            }
            colorList.clear();
            colorList = colorlist2;
            colorlist2.clear();
        }
        else{
            break;
        }
    }
    colorList.clear();
    colorList = colorlist1;
    colorlist1.clear();
}

void GameNewLinker::onExit() {
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("./Link/linkerPic.plist");
    GameShare_Scene::onExit();
}
void GameNewLinker::startGame(float dt) {
    super_Props_Strengthen = CItemMan::sharedInstance().useItem(ItemTag_13);
    super_Props_notMiss = CItemMan::sharedInstance().useItem(ItemTag_14);
    p_1_miss = super_Props_notMiss;
    if (super_Props_Strengthen) {
        Strengthen = 0.35;
        starShow = 0.15;
        easyGameList = 0.3;
    }
    initPointsStuta();
    setBackgroundMusic(muBG_in_game04);
    
    this -> schedule(schedule_selector(GameNewLinker::chechLjStatus));
}
void GameNewLinker::chechLjStatus(float) {
    long nowTime = this->getCurrentTime();
    if (nowTime - preTime > 1000.0f*betterTime) {
        batter = 0;
        gameBatterType = 1;
        betterTime = Batter_Normal_link;
        this->Crazy_End();
//        this -> unscheduleAllSelectors();
        if (superModelTime < superModelTimecount) {
            superModelTime = superModelTimecount;
        }
        superModelTimecount = 0;
    }
}
bool GameNewLinker::ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event) {
    clickRoundTabel -> setVisible(true);
    //设置点击的位置
    clickRoundTabel -> setPosition(touch -> getLocation());
    int itemClickCount = getTouchItem(touch ->getLocation());
    //若是炸弹地图
    if (isBoomMap) {
        int clickType = list[itemClickCount];
        for (int i = 0; i <AnimalList.size(); i++) {
            int ccc = 0;
            if (AnimalList[i] -> getItemType() == clickType) {
                ccc ++;
                bool isLinked = AnimalList[i] -> getLinkStatus();
                if (isLinked) {
                    return true;
                }
                else {
                    //开始连线///////////////////////
                    int length = list.size() == 25? 5:6;
                    std::vector<int>linelist_q;
                    for (int j = 0; j< list.size(); j ++) {
                        if (list[j] == clickType || list[j] == clickType * 10) {
                            linelist_q.push_back(j);
                        }
                    }
                    for (int k = 0; k < linelist_q.size(); k ++) {
                        bool wellDraw = false;
                        for (int m = 0; m < linelist_q.size(); m ++) {
                            if (linelist_q[m] == linelist_q[k]-1) {
                                 wellDraw = true;
                            }
                            if (linelist_q[m] == linelist_q[k]+1) {
                                 wellDraw = true;
                            }
                            if (linelist_q[m] == linelist_q[k]+length) {
                                 wellDraw = true;
                            }
                            if (linelist_q[m] == linelist_q[k]-length) {
                                 wellDraw = true;
                            }
                            if (wellDraw) {
                                int type = 0;
                                for (int o = 0; o < AnimalList.size(); o ++) {
                                    if (AnimalList[o] -> getItemType() == clickType) {
                                        type = AnimalList[o] -> getPicType();
                                    }
                                }
                                drawLine_1(linelist_q[m], linelist_q[k], type);
                            }
                        }
                    }
                    if (isBoomAddTime) {
                        isBoomAddTime = false;
                        time_addSecond(5);
                    }
                    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("EF_play_pang10.caf", false);
                    AnimalList[i] -> doLinkOKAction();
                    if (ccc == 1) {
                        batterCountAndShow();
                    }
                    ///////////////////////////////
                    //判断是否过关
                    int count = 0 ;
                    for (int j = 0; j < AnimalList.size(); j ++) {
                        if (AnimalList[j] -> getLinkStatus()) {
                            count++;
                        }
                    }
                    if (linkOkCounts == count/2) {
                        //过关
                        score += 1000 * pointsCount;
                        setScore((long)score);
                        //过关图片
                        showPointPic();
                        this -> runAction(CCSequence::create(CCDelayTime::create(0.2), CCCallFunc::create(this, callfunc_selector(GameNewLinker::initPointsStuta)), NULL));
                    }

                }
            }
        }
        showSharder();
        return true;
    }
    //点击动物开始动作
    if(list[itemClickCount] < 10) {
        for (int i = 0; i < AnimalList.size(); i++) {
            int type =  AnimalList[i] -> getItemType();
            if (type == list[itemClickCount]) {
                AnimalList[i] -> picBeClick();
                isCanDrawLine = true;
                LineKind = type;
                drawLineKind = AnimalList[i] -> getPicType();
                animal_begin = itemClickCount;
            }
        }
        //点击动物头像移除所有它的连线
        vector<lineTiem>linelist1;
        for (int i = 0; i < linelist.size(); i ++) {
            if (linelist[i].kind == LineKind) {
                linelist[i].pic -> removeFromParentAndCleanup(true);
            }
            else {
                linelist1.push_back(linelist[i]);
            }
        }
        linelist.clear();
        linelist = linelist1;
        linelist1.clear();
    }
    //点击连线的末尾
    for (int i = 0; i < linelist.size(); i ++) {
        if (linelist[i].endIndex == itemClickCount) {
            int type = linelist[i].kind;
            int index = itemClickCount;
            while (1) {
                bool wellContine = true;
                for (int j = 0; j < linelist.size(); j ++) {
                    if (linelist[j].beginIndex == index && linelist[j].kind == type) {
                        linelist[j].pic -> setVisible(false);
                        index = linelist[j].endIndex;
                        continue;
                    }
                    wellContine = false;
                }
                if (!wellContine) {
                    break;
                }
            }
            for (int j = 0; j < AnimalList.size(); j++) {
                int type =  AnimalList[j] -> getItemType();
                if (type == linelist[i].kind) {
                    AnimalList[j] -> picBeClick();
                }
            }
            isCanDrawLine = true;
            LineKind = linelist[i].kind;
            drawLineKind = linelist[i].drawKind;
        }
    }
    //将未显示的线条全部移除
    vector<lineTiem>linelist1;
    for (int i = 0; i < linelist.size(); i ++) {
        if (!linelist[i].pic->isVisible()) {
            //移除所有移除的线条
            linelist[i].pic -> removeFromParentAndCleanup(true);
        }
        else {
            linelist1.push_back(linelist[i]);
        }
    }
    linelist.clear();
    linelist = linelist1;
    linelist1.clear();
    first_box = itemClickCount;
    sencond_box = 100;
    return true;
}
void GameNewLinker::ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event) {
    int itemClickCount = getTouchItem(touch ->getLocation());
    clickRoundTabel -> setVisible(true);
    clickRoundTabel -> setPosition(touch -> getLocation());
    if (itemClickCount == 100) {
        clickRoundTabel -> setVisible(false);
        return;
    }
    if (first_box != itemClickCount && first_box != 100 && itemClickCount != 100 && isCanDrawLine) {
        if (list[itemClickCount] < 10 && list[itemClickCount] > 0 && list[itemClickCount] != LineKind) {
            //若移动到其他动物的头像上面则不处理
            bool thisKindCanDraw = true;
            bool bool_1 = false;
            bool bool_2 = false;
            for (int i = 0; i < list.size(); i ++) {
                if (list[i] == LineKind) {
                    for (int j = 0; j < linelist.size(); j ++) {
                        if (i == linelist[j].endIndex) {
                            bool_1 = true;
                        }
                        if (i == linelist[j].beginIndex) {
                            bool_2 = true;
                        }
                    }
                }
            }
            thisKindCanDraw = bool_2 && bool_1;
            if (thisKindCanDraw) {
                isCanDrawLine = false;
                return;
            }

            missNumber ++;
            if (p_1_miss) {
                p_1_miss = super_Props_notMiss;
                super_Props_notMiss = false;
                showOtherPic(2, touch ->getLocation());
            }
            else {
                float x = spritelistNow[itemClickCount] -> getPositionX() + spritelistNow[itemClickCount] -> getContentSize().width/2 *size;
                float y = spritelistNow[itemClickCount] -> getPositionY() + spritelistNow[itemClickCount] -> getContentSize().height/2 *size;
                showOtherPic(3, ccp(x,y));
                batter = 0;
                gameBatterType = 1;
                betterTime = Batter_Normal_link;
                this -> Crazy_End();
                this -> unscheduleAllSelectors();
                if (superModelTime < superModelTimecount) {
                    superModelTime = superModelTimecount;
                }
                superModelTimecount = 0;
            }
            isCanDrawLine = false;
        }
        else {
            bool thisKindCanDraw = true;
            bool bool_1 = false;
            bool bool_2 = false;
            for (int i = 0; i < list.size(); i ++) {
                if (list[i] == LineKind) {
                    for (int j = 0; j < linelist.size(); j ++) {
                        if (i == linelist[j].endIndex) {
                            bool_1 = true;
                        }
                        if (i == linelist[j].beginIndex) {
                            bool_2 = true;
                        }
                    }
                }
            }
            thisKindCanDraw = bool_2 && bool_1;
            if (!thisKindCanDraw && itemClickCount != 100 &&isCanDrawLine) {
                if (itemClickCount == animal_begin) {
                    int lintk = 0;
                    for (int t = 0; t < linelist.size(); t ++) {
                        if (linelist[t].kind == LineKind) {
                            lintk ++;
                        }
                    }
                    if (lintk > 1) {
                        isCanDrawLine = false;
                        return;
                    }
                }
                sencond_box = itemClickCount;
                beginDrawLine();
            }
        }
    }
}
void GameNewLinker::ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event) {
    //停止所有动物的动作
    isCanDrawLine = false;
    clickRoundTabel -> setVisible(false);
    for (int i = 0; i < AnimalList.size(); i++) {
        AnimalList[i] -> stopAllAction();
    }
    //将未显示的线条全部移除
    vector<lineTiem>linelist1;
    for (int i = 0; i < linelist.size(); i ++) {
        if (!linelist[i].pic->isVisible()) {
            //移除所有移除的线条
            linelist[i].pic -> removeFromParentAndCleanup(true);
        }
        else {
            linelist1.push_back(linelist[i]);
        }
    }
    linelist.clear();
    linelist = linelist1;
    linelist1.clear();
    //重新设置线条的末端
    for (int i = 0; i < linelist.size(); i ++) {
        int type = linelist[i].kind;
        int end = linelist[i].endIndex;
        while (1) {
            for (int j = 0; j < linelist.size(); j ++) {
                if (linelist[j].beginIndex == end &&linelist[j].kind == type) {
                    end = linelist[j].endIndex;
                    continue;
                }
            }
            break;
        }
        
        for (int j = 0; j < linelist.size(); j ++) {
            if (type == linelist[j].kind &&linelist[j].endIndex == end) {
                linelist[j].haveNext = false;
            }
        }
    }
    //判断是否成功连线
    bool musicOk = false;//是否播放音乐
    bool isLinkOK = false;//炸弹是否增加能量
    for (int i = 0; i < AnimalList.size(); i ++) {
            //获取种类
            bool isOk = false;
            bool beganOk = false;
            bool endOk = false;
            int type = AnimalList[i]  -> getItemType();
            for (int j = 0; j < list.size(); j ++) {
                if (type == list[j]) {
                    for (int m = 0; m < linelist.size(); m ++) {
                        if (linelist[m].endIndex == j) {
                            endOk = true;
                        }
                        if (linelist[m].beginIndex == j) {
                            beganOk = true;
                        }
                    }
                }
            }
            isOk = beganOk && endOk;
            if (isOk && !AnimalList[i] -> getOnLinkStatus()) {
                musicOk = isOk;
                isLinkOK = isOk && !AnimalList[i] -> getLinkStatus();
                AnimalList[i] -> doLinkOKAction();
            }
            if (!isOk) {
                AnimalList[i] -> setOnLinkFalse();
            }
    }
    if (musicOk) {
        //播放连线成功的效果音
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("EF_play_pang10.caf", false);
    }
    if (isLinkOK) {
        if (timeBefore10) {
            rigthCount ++;
        }
        //炸弹增加nengl
        boom_addEnergy(5);
        //连击计数
        batterCountAndShow();
        if (LineKind == Box_5w) {
            score += 50000;
            setScore((long)score);
            boxCount ++;
            showOtherPic(1, touch ->getLocation());
        }
        //连接星星直接过关
        if (LineKind == StarIcon) {
            lineNode -> removeAllChildrenWithCleanup(true);
            linelist.clear();
            //自动连线
            drawLineByOwn();
            //自动记分
            getScoreByStar();
            //过关积分
            score += 1000 * pointsCount;
            setScore((long)score);
            //过关图片
            showPointPic();
            
            starCount++;
            
            lineNode -> runAction(CCSequence::create(CCDelayTime::create(0.3),CCCallFunc::create(this, callfunc_selector(GameNewLinker::initPointsStuta)), NULL));
            return;
        }
    }
    showSharder();
    //判断关卡是否通过
    int count = 0;
    for (int i = 0; i < AnimalList.size(); i++) {
        if (AnimalList[i] -> getOnLinkStatus()) {
            count ++;
        }
    }
    if (linkOkCounts == (count/2) && LineKind != StarIcon && !isBoomMap) {
        //过关积分
        score += 1000 * pointsCount;
        setScore((long)score);
        //过关图片
        showPointPic();
        isCanDrawLine = false;
        this -> runAction(CCSequence::create(CCDelayTime::create(0.2), CCCallFunc::create(this, callfunc_selector(GameNewLinker::initPointsStuta)), NULL));
    }
}
int GameNewLinker::getTouchItem(cocos2d::CCPoint p) {
    float pointX = p.x;
    float pointY = p.y;
    for (int i = 0; i < spritelistNow.size(); i ++) {
        float pointXBegin = spritelistNow[i] -> getPositionX();
        float pointXend = pointXBegin + spritelistNow[i] -> getContentSize().width;
        float pointYbegin = spritelistNow[i] -> getPositionY();
        float pointYend = pointYbegin + spritelistNow[i] -> getContentSize().height;
        if (pointX > pointXBegin && pointX < pointXend) {
            if (pointY > pointYbegin && pointY < pointYend) {
                return i;
            }
        }
    }
    return 100;
}
void GameNewLinker::beginDrawLine() {
    CCPoint first = spritelistNow[first_box] -> getPosition();
    CCPoint second = spritelistNow[sencond_box] -> getPosition();
    float x = first.x - second.x;
    float y = first.y - second.y;
    CCPoint point;
    bool wellDraw = false;
    if (sencond_box - first_box == 1 || sencond_box - first_box == -1) {
        wellDraw = true;
    }
    int length = list.size() == 25 ? 5 :6;
    if (sencond_box - first_box == length || sencond_box -first_box == (-1*length)) {
        wellDraw = true;
    }
    if (!wellDraw) {
        isCanDrawLine = false;
        return;
    }
    //判断线的方向
    if (x < 0 && y == 0) {
        point = CCPoint(spritelistNow[first_box] -> getPositionX()+spritelistNow[first_box]->getContentSize().width*size, spritelistNow[first_box] -> getPositionY() + spritelistNow[first_box]->getContentSize().height /2*size);
    }
    if (x > 0 && y == 0) {
        point = CCPoint(spritelistNow[first_box] -> getPositionX(), spritelistNow[first_box] -> getPositionY() + spritelistNow[first_box] -> getContentSize().height /2*size);
    }
    if (x == 0 && y < 0) {
         point = CCPoint(spritelistNow[first_box] -> getPositionX()+spritelistNow[first_box]->getContentSize().width/2*size, spritelistNow[first_box] -> getPositionY() + spritelistNow[first_box]->getContentSize().height*size);
    }
    if (x == 0 && y > 0) {
        point = CCPoint(spritelistNow[first_box] -> getPositionX()+spritelistNow[first_box]->getContentSize().width/2*size, spritelistNow[first_box] -> getPositionY());
    }
    //将所有线条设置为显示
    for (int i = 0;  i < linelist.size(); i ++) {
        linelist[i].pic -> setVisible(true);
    }
    for (int i = 0; i < linelist.size(); i++) {
        vector<lineTiem>linelist1;
        if (linelist[i].kind == LineKind) {
            int end = linelist[i].endIndex;
            for (int j = 0; j < linelist.size(); j ++) {
                linelist1.clear();
                if (linelist[j].endIndex == end && linelist[j].kind != LineKind) {
                    for (int m = 0; m < linelist.size(); m ++) {
                        if (linelist[m].kind == linelist[j].kind) {
                            linelist1.push_back(linelist[m]);
                        }
                    }
                    for (int n = 0; n < linelist1.size(); n ++) {
                        if (linelist1[n].endIndex == end) {
                            lineTiem a = linelist1[n];
                            a.pic -> setVisible(false);
                            while (1) {
                                for (int k = 0; k < linelist1.size(); k++) {
                                    if (linelist1[k].beginIndex == end) {
                                        linelist1[k].pic -> setVisible(false);
                                        end = linelist1[k].endIndex;
                                        continue;
                                    }
                                }
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    //按照条件设置部分线条为隐藏
    for (int i = 0; i < linelist.size(); i ++) {
        //回滚原来的线条，会删除图片
        if (linelist[i].beginIndex == sencond_box && linelist[i].endIndex == first_box && LineKind == linelist[i].kind) {
            vector<lineTiem>linelist1;
            for (int j = 0 ; j < linelist.size(); j ++) {
                if (linelist[j].beginIndex == linelist[i].beginIndex && linelist[j].endIndex == linelist[i].endIndex) {
                    continue;
                }
                else
                    linelist1.push_back(linelist[j]);
            }
            linelist[i].pic -> removeFromParentAndCleanup(true);
            linelist.clear();
            linelist = linelist1;
            linelist1.clear();
            first_box = sencond_box;
            return;
        }
        //不同颜色尾部相交
        if (linelist[i].endIndex == sencond_box && LineKind != linelist[i].kind) {
            lineTiem model = linelist[i];
            model.pic -> setVisible(false);
            int next = model.endIndex;
            while (1) {
                for (int j = 0; j < linelist.size(); j ++) {
                    if (linelist[j].beginIndex == next && linelist[j].kind == linelist[i].kind) {
                        linelist[j].pic -> setVisible(false);
                        next = linelist[j].endIndex;
                        continue;
                    }
                }
                break;
            }
        }
    }
    CCString str;
    int t = drawLineKind;
    if (LineKind == StarIcon) {
        t = 4;
    }
    if (LineKind == Box_5w) {
        t = 5;
    }
    str.initWithFormat("line/link_line_%d.png", t);
    auto line = CCSprite::createWithSpriteFrameName(str.getCString());
    
    if (x == 0 && y < 0) {
        line -> setRotation(90);
    }
    if (x == 0 && y > 0) {
        line -> setRotation(90);
    }
    line -> setScaleY(0.8*size);
    line -> setScaleX(0.9*size);
    line -> setPosition(point);
    CCString str1;
    lineTiem item;
    item.pic = line;
    item.kind = LineKind;
    item.beginIndex = first_box;
    item.endIndex = sencond_box;
    item.haveNext = false;
    item.drawKind = drawLineKind;
    for (int i = 0; i < linelist.size(); i ++) {
        if (linelist[i].kind == LineKind && !linelist[i].haveNext) {
            linelist[i].haveNext = true;
        }
    }
    linelist.push_back(item);
    lineNode -> addChild(line);
    first_box = sencond_box;
    showSharder();
}
void GameNewLinker::msgHanlde_GameTimeOut(CCObject* obj) {
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

    
    if (p_4_batter) {
        p_4_batter = false;
        CTaskManProceDt(eDayTaskTypeTK_76, 1);
    }
    if (CCUserDefault::sharedUserDefault() -> getBoolForKey("P_1")) {
        CTaskManProceDt(eDayTaskTypeTK_77, 1);
    }
    
    CTaskManProceDt(eDayTaskTypeTK_78, boxCount);
    CTaskManProceDt(eDayTaskTypeTK_79, easyListCount);
    CTaskManProceDt(eDayTaskTypeTK_80, starCount);
    CTaskManProce(eDayTaskTypeTK_81, rigthCount);
    this -> unscheduleAllSelectors();
    GameShare_Scene::msgHanlde_GameTimeOut(obj);
}
void GameNewLinker::superModelTimeCountbegin(float) {
    superModelTimecount ++;
}

void GameNewLinker::noticeTimeInterval(cocos2d::CCObject *obj) {
    if (((GameShare_TimeProcess*)obj)->GetSecondsRemain() <= 50) {
        timeBefore10 = false;
    }
    if (((GameShare_TimeProcess*)obj)->GetSecondsRemain() == 40) {
        scoreBy20 = score;
    }
    if (((GameShare_TimeProcess*)obj)->GetSecondsRemain() <= 2)
	{
        if (p_3_timeAdd) {
            time_addSecond(5);
            p_3_timeAdd = false;
            useTimeEff();
        }
        return ;
	}
    GameShare_Scene::noticeTimeInterval(obj);
}
void GameNewLinker::msgHanlde_BoomFull(CCObject* obj) {
    boomCount ++;
    isBoomFull = true;
}
void GameNewLinker::msgHandle_CrazyTimeOut(CCObject* obj) {
    
}
long GameNewLinker::getCurrentTime()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}
void GameNewLinker::setScore_link() {
    int link_score = 50 * batter;
    int points_score = pointsCount * 100 + 100;
    int allscore = (link_score + points_score) * gameBatterType;
    score += allscore;
    setScore((long)score);
}
void GameNewLinker::showOtherPic(int kind, CCPoint point) {
    //显示加分5W
    CCString str;
    float scale;
    if (kind == 1) {
        str = "./GameMemoryLayer/50000.png";
        scale = 0.7;
    }
    else if (kind == 2) {
        str = "./GameMemoryLayer/Shield.png";
        scale = 2;
    }
    else if (kind == 3) {
        str = "./GameMemoryLayer/clickWrong.png";
        scale = 1;
    }
    CCSprite *pic = CCSprite::create(str.getCString());
    pic->setScale(scale);
    pic ->setPosition(point);
    CCMoveBy *upMove = CCMoveBy::create(0.3, ccp(0, 10));
    CCScaleTo *sizeChange = CCScaleTo::create(0.3, 0.1);
    CCFadeTo *aph = CCFadeTo::create(0.3, 0);
    this->addChild(pic, 105);
    pic-> runAction(CCSequence::create(upMove, sizeChange, aph, CCRemoveSelf::create(), NULL));
}
void GameNewLinker::showPointPic() {
    CCSize visablesize = CCDirector::sharedDirector() -> getVisibleSize();
    auto *pic = CCSprite::create("./Link/linkerNumber/linkerNumber_F.png");
    pic -> setPosition(ccp(visablesize.width, visablesize.height/2));
    int numAll = pointsCount;
    int num = numAll%10;
    int width = -80;
    std::vector<int>Number;
    while (1) {
        Number.push_back(num);
        numAll = ((numAll - num)/10);
        if (numAll <= 0) {
            break;
        }
        num = numAll%10;
    }
    CCString str;
    for (int i = 0; i < Number.size(); i++) {
        str.initWithFormat("./Link/linkerNumber/linkerNumber_%d.png", Number[i]);
        auto *pic1 = CCSprite::create(str.getCString());
        pic1 -> setPosition(ccp(width, 50));
        width -= 75;
        pic -> addChild(pic1);
    }
    this -> addChild(pic, 100);
    pic -> runAction(CCSequence::create(CCMoveBy::create(0.2, ccp(-visablesize.width/2 + 40, 0)),CCDelayTime::create(0.5),CCRemoveSelf::create(),NULL));
}
void GameNewLinker::rookTheList() {
    //倒转地图
    int num = myRand%2 + 1;
    if (num == 1 && !isBoomMap) {
        int length = list.size() == 25? 5 : 6;
        std::vector<int>list1;
        for (int i = 0; i < length; i ++) {
            for (int j = i; j < list.size(); j+= length) {
                list1.push_back(list[j]);
            }
        }
        list.clear();
        list = list1;
        list1.clear();
    }
    //若有星星，或礼盒
    int num1 = 0;
    for (int i = 0; i < list.size(); i++) {
        if (list[i] > 0 &&list[i] < 10) {
            num1 = list[i];
            break;
        }
    }
    if (_HaveStar) {
        for (int i = 0; i < list.size(); i++) {
            if (list[i] == num1) {
                numberBeChaneg = list[i];
                list[i] = StarIcon;
            }
            if (list[i] == num1*10) {
                list[i] = StarIcon*10;
            }
        }
    }
    if (_HaveBox) {
        for (int i = 0; i < list.size(); i++) {
            if (list[i] == num1) {
                numberBeChaneg = list[i];
                list[i] = Box_5w;
            }
            if (list[i] == num1*10) {
                list[i] = Box_5w*10;
            }
        }
    }
}
//点击星星自动连线
void GameNewLinker::drawLineByOwn() {
    int length = list.size() == 25 ? 5 : 6;
    std::vector<int>drawLineType;
    for (int i = 0; i < list.size(); i ++) {
        if (list[i] < 10 && list[i] > 0) {
            bool wellpush = true;
            for (int j = 0; j < drawLineType.size(); j ++) {
                if (drawLineType[j] == list[i]) {
                    wellpush = false;
                }
            }
            if (wellpush) {
                drawLineType.push_back(list[i]);
            }
        }
    }
    for (int i = 0; i < drawLineType.size(); i ++) {
        std::vector<int>linelist_q;
        for (int j = 0; j< list.size(); j ++) {
            if (list[j] == drawLineType[i] || list[j] == drawLineType[i] * 10) {
                linelist_q.push_back(j);
            }
        }
        for (int k = 0; k < linelist_q.size(); k ++) {
            for (int m = 0; m < linelist_q.size(); m ++) {
                bool wellDrow = false;
                if (linelist_q[m] == linelist_q[k]-1) {
                    wellDrow = true;
                }
                if (linelist_q[m] == linelist_q[k]+1) {
                    wellDrow = true;

                }
                if (linelist_q[m] == linelist_q[k]+length) {
                    wellDrow = true;
                }
                if (linelist_q[m] == linelist_q[k]-length) {
                    wellDrow = true;
                }
                if (wellDrow) {
                    int type = 0;
                    for (int o = 0; o < AnimalList.size(); o ++) {
                        if (AnimalList[o] -> getItemType() == drawLineType[i]) {
                            type = AnimalList[o] -> getPicType();
                        }
                    }
                    drawLine_1(linelist_q[m], linelist_q[k], type);
                }
            }
        }
    }
    showSharder();
}
void GameNewLinker::drawLine_1(int m, int n, int t) {
    CCPoint first = spritelistNow[m] -> getPosition();
    CCPoint second = spritelistNow[n] -> getPosition();
    float x = first.x - second.x;
    float y = first.y - second.y;
    CCPoint point;
    int kind = t;
    if (t == StarIcon) {
        t = 4;
    }
    if (t == Box_5w) {
        t = 5;
    }
    //判断线的方向
    bool wellDraw = false;
    if (x < 0 && y == 0) {
        wellDraw = true;
        point = CCPoint(spritelistNow[m] -> getPositionX()+spritelistNow[m]->getContentSize().width*size, spritelistNow[m] -> getPositionY() + spritelistNow[m]->getContentSize().height /2*size);
    }
    if (x > 0 && y == 0) {
        wellDraw = true;
        point = CCPoint(spritelistNow[m] -> getPositionX(), spritelistNow[m] -> getPositionY() + spritelistNow[m] -> getContentSize().height /2*size);
    }
    if (x == 0 && y < 0) {
        wellDraw = true;
        point = CCPoint(spritelistNow[m] -> getPositionX()+spritelistNow[m]->getContentSize().width/2*size, spritelistNow[m] -> getPositionY() + spritelistNow[m]->getContentSize().height*size);
    }
    if (x == 0 && y > 0) {
        wellDraw = true;
        point = CCPoint(spritelistNow[m] -> getPositionX()+spritelistNow[m]->getContentSize().width/2*size, spritelistNow[m] -> getPositionY());
    }
    if (wellDraw) {
        CCString str;
        str.initWithFormat("line/link_line_%d.png", t);
        auto line = CCSprite::createWithSpriteFrameName(str.getCString());
        if (x == 0 && y < 0) {
            line -> setRotation(90);
        }
        if (x == 0 && y > 0) {
            line -> setRotation(90);
        }
        line -> setScaleY(0.8*size);
        line -> setScaleX(0.9*size);
        line -> setPosition(point);
        lineNode -> addChild(line);
        lineTiem lineItem;
        lineItem.pic = line;
        lineItem.kind = kind;
        lineItem.beginIndex = m;
        lineItem.endIndex = n;
        linelist.push_back(lineItem);
    }
}
void GameNewLinker::batterCountAndShow() {
    long nowTime = this->getCurrentTime();
    if (nowTime - preTime > 1000.0f*betterTime) {
        batter = 0;
        gameBatterType = 1;
        betterTime = Batter_Normal_link;
        this->Crazy_End();
        this -> unscheduleAllSelectors();
        if (superModelTime < superModelTimecount) {
            superModelTime = superModelTimecount;
        }
        superModelTimecount = 0;
    }
    preTime = this->getCurrentTime();
    if (batter >= 20 && gameBatterType == 2) {
        betterTime = Batter_SuperCrazy_link;
        Crazy_Start(100.f, eSuperCrazyMode);
        this -> schedule(schedule_selector(GameNewLinker::superModelTimeCountbegin), 1);
        superModelCount ++;
        gameBatterType = 3;
    }else if (batter >= 10 && gameBatterType == 1) {
        betterTime = Batter_Crazy_link;
        Crazy_Start(100.f, eComCrazyMode);
        gameBatterType = 2;
    }
    //显示连击数
    if (batter > 0) {
        setBatter(batter);
    }
    batter++;
    allbatter ++;
    if (batter > bigestBatter) {
        bigestBatter = batter;
    }
    //设置分数
    setScore_link();
}
void GameNewLinker::showSharder(){
    //显示阴影
    for (int i = 0; i < sharderList.size(); i ++) {
        sharderList[i].cLayer -> removeFromParentAndCleanup(true);
    }
    sharderList.clear();
    for (int i = 0; i < linelist.size(); i ++) {
        int beg = linelist[i].beginIndex;
        int end = linelist[i].endIndex;
        bool draw_beg = true;
        bool draw_end = true;
        for (int j = 0; j < sharderList.size(); j ++) {
            if (sharderList[j].index == beg) {
                draw_beg = false;
            }
            if (sharderList[j].index == end) {
                draw_end = false;
            }
        }
        int lineBackType = linelist[i].kind >= StarIcon ? numberBeChaneg : linelist[i].kind;
        lineBackType -= 1;
        CCString str1;
        if (draw_beg) {
            sharderPic pic;
            str1.initWithFormat("Link/EdgeColor_%d.jpg", colorList[lineBackType].index);
            pic.cLayer = CCSprite::create(str1.getCString());
            pic.cLayer -> setAnchorPoint(ccp(0,0));
            pic.index = beg;
            pic.cLayer -> setPosition(spritelistNow[beg] -> getPosition());
            pic.cLayer -> setContentSize(spritelistNow[beg] -> getContentSize());
            pic.cLayer -> setScale(size);
            sharderNode -> addChild(pic.cLayer);
            sharderList.push_back(pic);
        }
        if (draw_end) {
            sharderPic pic;
            str1.initWithFormat("Link/EdgeColor_%d.jpg", colorList[lineBackType].index);
            pic.cLayer = CCSprite::create(str1.getCString());
            pic.cLayer -> setAnchorPoint(ccp(0,0));
            pic.index = end;
            pic.cLayer -> setPosition(spritelistNow[end] -> getPosition());
            pic.cLayer -> setContentSize(spritelistNow[end] -> getContentSize());
            pic.cLayer -> setScale(size);
            sharderNode -> addChild(pic.cLayer);
            sharderList.push_back(pic);
        }
    }
}
void GameNewLinker::getScoreByStar() {
    std::vector<int>animalUnLink;
    //未连接的图像数组
    for (int i = 0; i < AnimalList.size(); i++) {
        if (AnimalList[i] -> getLinkStatus()) {
            bool wellPush = true;
            for (int j = 0; j < animalUnLink.size(); j++) {
                if (animalUnLink[j] == AnimalList[i] -> getItemType()) {
                    wellPush = false;
                }
            }
            if (wellPush) {
                animalUnLink.push_back(AnimalList[i] -> getItemType());
            }
        }
    }
    for (int i = 0; i < animalUnLink.size(); i++) {
        batter++;
        if (batter > bigestBatter) {
            bigestBatter = batter;
        }
        allbatter ++;
        if (animalUnLink[i] == Box_5w) {
            score += 50000;
            setScore((long)score);
        }
        setScore_link();
    }
}
void GameNewLinker::resurgeCallfunc(int nTimes) {
    if (nTimes == 1) {
        p_2_superModel = false;
        betterTime = Batter_SuperCrazy_link;
        Crazy_Start(100.f, eSuperCrazyMode);
        this -> schedule(schedule_selector(GameNewLinker::superModelTimeCountbegin), 1);
        gameBatterType = 3;
    }
    else {
        p_2_superModel = false;
        betterTime = Batter_SuperCrazy_link;
        Crazy_Start(100.f, eSuperCrazyMode);
        this -> schedule(schedule_selector(GameNewLinker::superModelTimeCountbegin), 1);
        gameBatterType = 3;
    }
}