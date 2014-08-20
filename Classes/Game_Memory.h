//
//  Game_Memory1.h
//  OnceAgain
//
//  Created by mac on 14-3-7.
//
//

#ifndef __OnceAgain__Game_Memory1__
#define __OnceAgain__Game_Memory1__

#include "GameShare_Scene.h"
#include "Game_MemoryCard.h"
#include "JudgeMedalGet.h"

#if   (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define EFFECT_BINGO "EF_play_pang_fever01_voc.ogg"
#define EFFECT_CLICK "EF_play_pang"
#define MUSIC_TENSEC "EF_play_10sec.ogg"
#elif (CC_TARCET_PLATFORM == CC_PLATFORM_MARMALADE)
#define EFFECT_FILE   "effect1.raw"
#else
#define EFFECT_BINGO "EF_play_pang_fever01_voc.caf"
#define EFFECT_CLICK "EF_play_pang"
#define MUSIC_TENSEC "EF_play_10sec.caf"

#endif

struct cardListByOneBox {
    vector<int>cardList;
};


class Game_Memory : public GameShare_Scene/*, public JudgeMedalGet*/
{
public:
    Game_Memory(void){};
    ~Game_Memory(void);
    virtual bool init();
    static cocos2d::CCScene* scene();
    
    // Get the position and size of the sprite
    CCRect rect(CCNode* pNode);
    // Whether the touch point in the sprite
    int isTouchInside(CCTouch* touch);
    virtual void startGame(float dt=1.0);
    
    void TouchMoved(CCTouch *touch, CCEvent *event, bool isfirstdouble);
    virtual void msgHanlde_GameTimeOut(CCObject* obj);
    
    virtual void ccTouchesBegan(CCSet * set,CCEvent * e);
    virtual void ccTouchesMoved(CCSet * set,CCEvent * e);
    virtual void ccTouchesEnded(CCSet * set,CCEvent * e);
    
    virtual void resurgeCallfunc(int nTimes);
    virtual void noticeTimeInterval(CCObject* obj);

    CREATE_FUNC(Game_Memory);
private:
    
    //继承方法,初始化背景.
    virtual void initBgView(void);
    //继承方法.炸弹爆炸.
    virtual void msgHanlde_BoomFull(CCObject* obj);
    //重置界面
    void resetView(float r=0.5);
    //设置炸弹界面.
    void setCareWithType(int type);
    //获取当前时间.
    long getCurrentTime();

    void Boom_addTime();

    void clickTrue(CCPoint point);   //Click on the correct animation.
    void clickFalse(CCPoint point);  //Click on the error animation.
    
    int checkNumberOfTheLongestCard();
    
    //正确过关显示.
    void showRight();
    
    //正确点击显示的.
    CCSprite *clickTrueSprite;
    
    //错误点击显示的.
    CCSprite *clickFalseSprite;
    
    //正确过关.
    CCSprite *rightSprite;
    
    //当前难度.
//    unsigned int difficult;
    //当前的点击类型.
    int nowtype;
    
    //当前屏幕卡牌总数.
    unsigned int total;
    //当前屏幕点击数量.
    unsigned int nowCilck ;
    //连击保持时间.
    float batterTime ;
    //上一次点击的时间.
    unsigned long preTime;
    //判断是否爆炸
    bool isBoom;
    //设置帮助。
    void showHelp(float dt);
    
    //总的连击次数.
    int allbatter;
    //是否出现高2k分牌.
    bool isHighScoreCard;
    
    //5K分牌
    bool isHighScoreCard_1;

    //金币
    bool isGoldCard;
    
    //once again
    bool onceAgain;
    
    //道具1：避免一次误操作
    bool Props_one;
    bool have_props_one;
    //道具2：简单排布
    bool Props_tow;
    //道具3：以疯狂模式开局
    bool Props_three;
    //道具4：该局游戏只会出现6种牌
    bool Props_four;
    
    //超级道具——时间
    bool super_Props_time;
    //超级道具——分数
    bool super_Props_score;
    //超级道具——强化
    bool super_Props_Strengthen;
    //超级道具——避免失误
    bool super_Props_notMiss;
    
    //疯狂3， 防御1， 6卡4， 简单2
    //购买道具4后，固定的6张牌
    std::vector <int> cardTypy;
    
    //强化系统
    //额外分数
    double Otherscore;
    //金币出现概率
    double Gold;
    //奖励牌加强
    double Scorecard;
    
    //获得3个几率
    void setAllProbability(int lv);
    
    //强化后出现何种奖励
    void RewardByStrengthen(double a, double b, double c);
    
    //第一次同时点击,点击位置
    int firstPlace;
    
    //前后两次点击的卡片
    int firstCard;
    int secondCard;

    int pointCount;//关卡
    //增加的金币
    int addGoldNumber;
    
    UIPanel *back;
    
    int superModelCount;
    
    int rightCardCount;
    
    int secore2wCount;

    int oneAgainCount;
    
    int propEasyGameCount;
    
    int scoreBy20;
    
    int superModelTime;
    int superModelTimecount;
    void superModeltimeCountbegin(float);
    
    int bigestBatter;
    
    int boomCount;
    
    int missNumber;
    
    //点击2k，5k，炸弹的特效
    void rewardEffect(int tag, int kind);
    void callBack();
    void callBack_1();
    
    void MedalInfoBack(CCObject *p);
    std::vector<cardListByOneBox>allCardList;
    
private:
    //勋章计数
    int rewardCardCount;
    //是否连续失误
    bool isMiss;
    int MissCount;
    
    std::vector<int>cardTypeList;
};

//不同连击数代表等级.
enum BatterLevel
{
    Level_0 = 0,
    Level_1 = 5,
    Level_2 = 20,
    Level_3 = 40,
    Level_4 = 60
};
//不同模式连击分数的倍数.
enum SocreMultiple
{
    NormalMultiple      =    1,
    CrazyMultiple       =    2,
    SuperCrazyMultiple  =    4
};
//显示帮助的间隔时间.
const float Time_Help           = 3.0;
//不同模式连击保持时间.
const float Batter_Normal       = 2.5;
const float Batter_Crazy        = 1.5;
const float Batter_SuperCrazy   = 0.8;
//连击到达疯狂模式的次数.
const unsigned int BatterToCrazy = 10;
//连击到达超级疯狂模式的次数.
const unsigned int BatterToSuperCrazy = 25;
//第一次基础分.
const unsigned int BaseSocre = 30;
//累加的分
const unsigned int AddSocre = 65;

//每次能量加成.
const unsigned int EachEnergy = 3;
//多少次连击出现高分牌.
const unsigned int TimesHighScore = 20;
#endif /* defined(__OnceAgain__Game_Memory1__) */
