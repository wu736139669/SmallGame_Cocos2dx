
#ifndef TAIKO_SCENE_H
#define TAIKO_SCENE_H

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"  ///播放声音文件
#include <vector>
#include "GameShare_Scene.h"
#include "TaikoData.h"

USING_NS_CC;
USING_NS_CC_EXT;
class GameShare_TimeProcess;
class CTaikoCell;
class CTaikoScene : public GameShare_Scene
{
public:
    CTaikoScene();
    ~CTaikoScene();
public:
	static cocos2d::CCScene* scene();

	void start();
	void initBgView();

	//初始化 进行当前层的一些初始化
    virtual bool init();
	virtual void startGame(float dt/* =1.0 */);
	//////////////////////////////////////////////////////////////////////////
	//事件相关
    //单击事件开始
    virtual bool ccTouchBegan(cocos2d::CCTouch * pTouch, cocos2d::CCEvent *pEvent);
    //单击事件拖动
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    //单击事件结束
    virtual void ccTouchEnded(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	virtual void onEnter();
	virtual void onExit();
    virtual void update(float fDelta);
    // a selector callback
    virtual void menuCloseCallback(CCObject* pSender);
	virtual void msgHanlde_GameTimeOut(CCObject* obj);
	virtual void msgHanlde_GameTimeOutPer(CCObject* obj);
	virtual void noticeTimeInterval(CCObject* obj);
	virtual void msgHandle_CrazyTimeOut(CCObject* obj);
	
	void callFuncDrumL();
	void callFuncDrumR();
	void callFuncDrumLHide();
	void callFuncDrumRHide();

	//////////////////////////////////////////////////////////////////////////
	
	//////////////////////////////////////////////////////////////////////////
	//功能函数
	void addTarget();
	void clickBtn0();
	void clickBtnPushDown0();
	void clickBtnCancel0();
	void clickBtn1();
	void clickBtnPushDown1();
	void clickBtnCancel1();
	bool clickBtnDrum(int nType);
	void clickBtnType(int nType);
	bool isContainOpVec(CTaikoCell* pValidCell);	
	void delCell(CTaikoCell* pCell,bool bCleanup = false);
	//使用道具
	bool useItem(ETaikoEffectType eType);
	//处理道具
	bool processItem(ETaikoEffectType eType);
	bool processItem(ETaikoEffectType eType,int nVal);
	void opErr(CTaikoCell* pCell,bool bDel = true);
	void setLightRotateAct(CCNode* p,float fTime,float fAngle);
	//////////////////////////////////////////////////////////////////////////
	
    CREATE_FUNC(CTaikoScene);
protected:
	void _calcScore();
	//计算震鼓分数
	void _calcBrumScore();
	void _calcLongScore();
	void _calcBoom();
	void _calc(CTaikoCell* pCell);
	void _calcOpNum(CTaikoCell* pCell);
	void _executeDel();
    void _updataGenInterval();
	void _updataASpeed();
    void _executeASpeed(float fASpeed);
    void _setCrazyMode(bool bImmediately = false);
	void _executeOpStateEff(CTaikoCell* pCell);
	
private:
	//操作的细胞
   std::vector<CTaikoCell*> mVecCellOp;
   //有效细胞
   std::vector<CTaikoCell*> mVecCellValid;
   //无效细胞
   std::vector<CTaikoCell*> mVecCellInvalid;
   //CCRect mRcTarget;
   CCRect mRcTargetPrefect;
   CCRect mRcTargetGreen;
   CCPoint mptSplit;
   GameShare_TimeProcess*   mpTimeProcessLayer;

   float mfLastTouchTime;
   //细胞到达时间间隔
   float	mfCellArriveTimeInterval;
    float mfASpeed;
    float mfStartSpeed;
    float mfGenCellInterval;
	bool mbClickCellLong;
	int mnCounter;
   //出生位置
   //CCPoint mptStartPos;
   //到达位置
   CCPoint mptArrivePos;
   CC_SYNTHESIZE(bool,mbStart,IsStart);
   CC_SYNTHESIZE(CCSprite*,mpDrumEff,DrumEff);
    CC_SYNTHESIZE_READONLY(CCPoint, mptStartPos, StartPos);
    CC_SYNTHESIZE_READONLY(CCRect, mRcTarget, RcTarget);
    CC_SYNTHESIZE(CCSprite*,mpOpState,OpState);
	//////////////////////////////////////////////////////////////////////////
	//日常任务统计相关
	//是否使用一击即中
	bool mbUseHit;
	//是否使用快速生成
	bool mbUseQuickRhythm;
	//计数perfect击中次数
	int mnCounterPerfectHitTimes;
	//计数perfect击中次数
	int mnCounterGreatHitTimes;
	//当前使用的图片类型
	int meCurrentHitType;
	//上次使用的图形类型
	int meLastHitType;
	//是否保存任务57分数
	bool mbSaveTask57Score;
	//////////////////////////////////////////////////////////////////////////
};

#endif
