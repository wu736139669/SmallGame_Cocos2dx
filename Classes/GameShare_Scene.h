//
//  GameShare_Scene.h
//  OnceAgain
//
//  Created by mac on 14-3-6.
//
//

#ifndef __OnceAgain__GameShare_Scene__
#define __OnceAgain__GameShare_Scene__

#include <iostream>
#include "cocos2d.h"



#include "GameShare_Data.h"
#include "GameShare_Global.h"
#include "GameShare_Property.h"
#include "GameShare_Msg.h"
#include "GameShare_Boom.h"
#include "GameShare_TimeProcess.h"
#include "Scene_GameOver.h"
#include "GameShare_Pause.h"
#include "GameShare_Score.h"
#include "GameShare_Batter.h"
#include "Constant.h"
#include "GameLayer_SuperItem.h"
#include "ComData.h"
USING_NS_CC;

//背景音乐.
#define MUSIC_BG     "BG_in_game05.caf"
//游戏模式
enum Game_Mode{
    Mode_Normal     = 0,
    Mode_Crazy      = 1,
    Mode_SuperCrazy = 2
};
class CGameLayerCrazyMode;
class CGameLayerNewerGuide;
class GameShare_Scene : public CCLayer
{
public:
    static CCScene* getGameSceneByType(e_GameType gameType=Game_Null);
    void creatGameOverLayer(CCObject *p);
    //////////可继承.
protected:
    //注册背景界面，子类游戏继承之后自己改.
    virtual void initBgView(void);
    //开始游戏.
    virtual void startGame(float dt=1.0);
    //时间结束的处理
    virtual void msgHanlde_GameTimeOut(CCObject* obj);
    //炸弹能量满的通知.
    virtual void msgHanlde_BoomFull(CCObject* obj);
    //疯狂模式结束消息处理函数
    virtual void msgHandle_CrazyTimeOut(CCObject* obj);
	//
	virtual void noticeTimeInterval(CCObject* obj);
	//时间图片消失回调
	void callback_TimeOut();
	//request score result
	void requestResult();
    //使用闹钟效果
	void useTimeEff();
	//time out per procces
	virtual void msgHanlde_GameTimeOutPer(CCObject* obj);

    /////////共有方法.
public:
    
    //设置游戏分数回调
    void setScoreCallback(CCObject* pSender);

    void setBackgroundMusic(const char *pszFilename);
    //关于时间的。
    void time_addSecond(unsigned int second);
    
    //设置分数.
    void setScore(unsigned long score=0);
    //设置连击.
    void setBatter(unsigned int batter=1);
    
    //关于炸弹的.
    //增加能量
    void boom_addEnergy(unsigned int energy=1);
    //设置能量.
    void boom_setEnergy(unsigned int energy=0);
    //设置能量最大值.
    void boom_setMaxBoomEnergy(unsigned int maxBoom=BOOM_MAXENERGY);
	//播放新手教程
	void playNewerHelp(SEL_CallFuncO pCallfunc = NULL);
	//继续
	void menuContinueClick();
	//添加点击事件
	void addTouchDelegate();
	//删除点击事件
	void removeTouchDelegate();
	//the windows is close
	void clickLayerClose();
    //
	void operateAllSchedulerAndActions(ESwitchFlag flag=eSwitcResume);
    //疯狂模式
    //开始疯狂模式
    /*
     * @rfDurationTime 疯狂模式持续时间 每0.1检测一次 到点后结束  发送
     */
    virtual void Crazy_Start(float rfDurationTime = 1.0,ECrazyMode eMode = eComCrazyMode);
    
    //重新计时
    virtual void Crazy_ReStart();
    
    //结束疯狂模式
    virtual void Crazy_End();
    
    //设置疯狂模式持续时间.
    virtual void Crazy_SetTime(float rfDurationTime=1.0);

	//检测疯狂模式
	virtual void Crazy_Check(float rfParas);
    
protected:

    //初始化疯狂模式
    void Crazy_Init();

public:	
    GameShare_Scene(void);
    ~GameShare_Scene(void);
    static cocos2d::CCScene* scene();
    virtual bool init(void);
    
    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch *touch, CCEvent *event);
    virtual void ccTouchMoved(CCTouch *touch, CCEvent *event);
    virtual void ccTouchEnded(CCTouch *touch, CCEvent *event);
    
    
    CREATE_FUNC(GameShare_Scene);
private:

    //游戏的属性.
    sGameProperty gameProperty;
    //连击数.
    GameShare_Batter *batterSprite;
    //炸弹.
    GameShare_Boom *boom;
    //暂停按钮.
    CCMenuItemImage *pauseMenuItem;
    CCMenu* pMenu;
    GameShare_Score *gameShare_Score;

    //暂停界面.
    GameShare_Pause* gameLayerPause;
	//
	CGameLayerCrazyMode* mpUILayer;
    //注册消息监听
    void initListerner();
    //暂停按钮事件
    void menuPauseCallBack(CCObject* pSender);
    //继续游戏
    void menuContinueCallBack(CCObject* pSender);
    //重新开始游戏
    void menuNewCallBack(CCObject* pSender);
    //退出游戏.
    void menuQuitCallBack(CCObject* pSender);
	//新手帮助
	void menuHelpCallfunc(CCObject* pSender);

protected:
	//开始的动画。
	virtual void showReadyGo(CCObject* p = NULL);
	//start callfunc
	virtual void readyGoCallBack(float dt=1.0);
	//复活成功回调
	virtual void resurgeCallfunc(int nTimes);
	//
	void sureSuperItem(CCObject* object);
	void cancelSuperItem(CCObject* object);
	//暂停或恢复场景内运行的所有节点
	void operateAllSchedulerAndActions(cocos2d::CCNode* node, ESwitchFlag flag=eSwitcResume);
	//add show layer
	void _addShowlayer(CCLayer* pLayer);
	bool _nextShowLayer();
	//show super crazy mode continue buy item
	void _showSuperItemLayer(int nItemId,int nEvent);

protected:
	//时间条.
	GameShare_TimeProcess *pTimeProcessLayer;
    //疯狂模式总执行时间
    float   m_fCrazyTime;
    //疯狂模式当前执行时间
    float   m_fCrazyNowTime;
    //当前的连击数.
    unsigned int batter;
    //分数
    unsigned long score;
    //当前能量
    unsigned int energy;
    //当前剩余时间。
    unsigned int mTime;
    //最大分数
    unsigned long Maxscore;
    //当前的模式
    Game_Mode  game_mode;
	//
    int addMoney;
    
	std::vector<CCSprite*> mVecCrazy;
	//show start layer list
	CCArray mArrLayerShow;
	//if show ready go animate
	CC_SYNTHESIZE(bool,mbShowReadyGoAni,IsShowReadyGoAni);
};
#endif /* defined(__OnceAgain__GameShare_Scene__) */
