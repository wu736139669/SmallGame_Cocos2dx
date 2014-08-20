//
// GameNewLinker.h
// OnceAgain
//
// Created by xiaohai on 14-5-19.
//
//

#ifndef __OnceAgain__GameNewLinker__
#define __OnceAgain__GameNewLinker__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"          //To Play audio
#include "GameShare_TimeProcess.h"      //time proces layer
#include "GameScenelist.h"              //GameScene
#include "GameShare_Scene.h"
#include "GameNewLinkerItems.h"


USING_NS_CC_EXT;
USING_NS_CC;

struct lineTiem {
    CCSprite *pic;
    int kind;// 种类
    bool haveNext;//是否有后一个点
    int beginIndex;//起始点
    int endIndex;//终止点
    int drawKind;//画出的颜色
};

struct sharderPic {
    CCSprite *cLayer;
    int index;
};

struct colorBox {
    ccColor4B color;
    int index;
};

class GameNewLinker : public GameShare_Scene
{
public:
    GameNewLinker(){};
    ~GameNewLinker(){};
    static CCScene* createScene();
    virtual bool init();
    virtual void onExit();
    
    virtual void Update(float fDelta){};
    virtual void initBgView(void);
    
    virtual bool ccTouchBegan(CCTouch *touch, CCEvent *event);
    virtual void ccTouchMoved(CCTouch *touch, CCEvent *event);
    virtual void ccTouchEnded(CCTouch *touch, CCEvent *event);
    
    virtual void resurgeCallfunc(int nTimes);
    
    CREATE_FUNC(GameNewLinker);
    
private:
 
    //开始游戏.
    virtual void startGame(float dt=1.0);
    
    //时间结束的处理
    virtual void msgHanlde_GameTimeOut(CCObject* obj);
    
    //炸弹能量满的通知.
    virtual void msgHanlde_BoomFull(CCObject* obj);
    
    //疯狂模式结束消息处理函数
    virtual void msgHandle_CrazyTimeOut(CCObject* obj);

    virtual void noticeTimeInterval(CCObject* obj);
public:
    //外部调用接口
    
    
private:
    //绑定地图ui
    void creatTileMaps();
    void creatAnamils();
    void initPointsStuta();
    long getCurrentTime();//获取时间
    void setScore_link();
    void showBatterPic();//连击图片显示
    void showPointPic();//关卡图片显示
    void showOtherPic(int kind, CCPoint point);//加分图片显示
    
    void showSharder();//显示阴影
    
    void rookTheList();//倒转图形方向
    void drawLineByOwn();//点击星星自动连线
    void drawLine_1(int m, int n, int t);
    void clickOnBoom();//点击炸弹效果
    void batterCountAndShow();//连击计数方法
    void getScoreByStar();//连接星星后计算分数
    void chechLjStatus(float);

    
    
    vector<colorBox>colorList;
    
    CCSprite *clickRoundTabel;
    CCNode *lineNode;//用来存放所有线条的容器
    CCNode *sharderNode;//阴影层
    
    //获取点击的位置
    int getTouchItem(CCPoint p);
    float littleMiles;//小地图比例
    float bigMidles;//大地图比例
    float size;
    
    bool isCanDrawLine;//当前是否可以画线
    int LineKind;//线的类型
    int drawLineKind;
    int getLineDirection();//获取线的方向
    
    int first_box;//前一个点击的位置
    int sencond_box;//后一个点击的位置
    int animal_begin;//开始动物的位置
    
    void beginDrawLine();
    
    std::vector<CCSprite*>littleMapsIcons;//小地图块
    std::vector<CCSprite*>bigMapsIcons;//大地图块
    std::vector<int>list;//地图数据
    std::vector<GameNewLinkerItems*>AnimalList;//动物列表
    vector<CCSprite*>spritelistNow;//当前地图
    vector<lineTiem>thisLineWellHide;//需要暂时隐藏的线段
    vector<lineTiem>linelist;
    vector<sharderPic>sharderList;
    vector<int>picKindList;//动物头像列表
private:
    //道具，强化
    bool _HaveStar;
    bool _HaveBox;
    bool _EasyGame;
    
    bool isBoomMap;
    bool isBoomAddTime;//炸弹爆炸增加时间

    void checkThePropsUseStatus();//判断强化使用情况
    
    bool p_1_miss;
    bool p_2_superModel;
    bool p_3_timeAdd;
    bool p_4_batter;
    
    //超级道具
    bool super_Props_Strengthen;//满级强化
    bool super_Props_notMiss;//避免两次失误
    
private:
    int pointsCount;//关卡
    int linkOkCounts;//需要配对成功的对数
    
    bool isBoomFull;//炸弹能量是否充满
    int betterTime;//连击间隔时间
    
    unsigned long preTime;//上一次点击的时间.
    
    int gameBatterType;
    int numberBeChaneg;//当出现礼盒或星星时，被置换掉的数
    
    float Strengthen;//礼盒
    float starShow;//星星
    float easyGameList;//简单排布
    
    
    int boxCount;
    int easyListCount;
    int starCount;
    
    bool timeBefore10;
    int rigthCount;
    
    //不同模式连击保持时间.
    float Batter_Normal_link;
    float Batter_Crazy_link;
    float Batter_SuperCrazy_link;
    
    
    int allbatter;
    
    int superModelCount;
    
    int scoreBy20;
    
    int superModelTime;
    int superModelTimecount;
    void superModelTimeCountbegin(float);
    
    int bigestBatter;
    
    int boomCount;
    
    int missNumber;
};


#endif /* defined(__OnceAgain__GameNewLinker__) */