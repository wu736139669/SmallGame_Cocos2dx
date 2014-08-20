
#ifndef Game_Fruit_Scene_h
#define Game_Fruit_Scene_h

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"  ///播放声音文件
#include "GameFruitField.h"
#include <vector>
#include "GameShare_Scene.h"
#include "GameFruitDefine.h"
#include "FruitData.h"
// enum
// {
// 	eFruitTypeMax = 8,
// };
static const int FIELD_X = 7;
static const int FIELD_Y = 7;
USING_NS_CC;
USING_NS_CC_EXT;
class GameShare_TimeProcess;
class CGameFruitScene : public GameShare_Scene
{
public:
    CGameFruitScene();
    ~CGameFruitScene();
public:

	static cocos2d::CCScene* scene();

    //初始化 进行当前层的一些初始化
    virtual bool init();

	virtual void initBgView(void);

    //单击事件开始
    virtual bool ccTouchBegan(cocos2d::CCTouch * pTouch, cocos2d::CCEvent *pEvent);
    //单击事件拖动
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    //单击事件结束
    virtual void ccTouchEnded(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
    //注册单击事件
    virtual void registerWithTouchDispatcher();
	virtual void onEnter();
	virtual void onExit();
    virtual void update(float fDelta);
    // a selector callback
    virtual void menuCloseCallback(CCObject* pSender);

	virtual void msgHanlde_GameTimeOut(CCObject* obj);
    void noticeBombEffect(CCObject* obj);

	void start();
	//取得格子信息
	CGameFruitField* GetFieldByTouch(const CCPoint* pPt);
	//CGameFruitField* GetFieldByIndex(const CCPoint* pPt);
	//计算角度
	static float GetCalcAngle(CCPoint ptTarget,CCPoint ptStart);
	//计算缩放
	static float GetCalcScale(CCPoint ptTarget,CCPoint ptStart,float fOriginLen);
	//是否路径存在
	bool IsExistPath(CGameFruitField* pField);
	//是否在连接范围
	bool IsConnectRange(CGameFruitField* pTargetField,CGameFruitField* pStartField);
	//选择水果效果
	void SelectFruitEffect(CCSprite* pSprite);
	void UpdataField();
	void ClearField();
	void RandEffcet(EFruitEffect state);
	void RandCrazyMode();
	void AllMoveEnd();
	virtual void noticeTimeInterval(CCObject* obj);
	virtual void startGame(float dt=1.0);
	virtual void msgHandle_CrazyTimeOut(CCObject* obj);
	//计算消除个数
	void calcDelNumByState(CGameFruitField* pCurField,bool bIsRecursion = true);
	//是否包含在容器内
	bool isContainDelVec(CGameFruitField* pCurField);
	//是否包含在路径容器内
	bool isContainPathVec(CGameFruitField* pCurField);
	//执行消除
	void executeDel();
	//使用道具
	bool useItem(EFrEffectType eType);

	//检测特效是否可用
	bool checkEffecValid(CGameFruitField* pCurField);

	//点击事件
	void OnImgEvent(CCObject* sender);
	CCRect getFieldGameArea(){return mRcFieldArea;}

    CREATE_FUNC(CGameFruitScene);
protected:
	void _calcScore();
private:
	UILayer* m_pUILayer;

   CCSprite* mpBg;
 
   CCSprite* mpFruitType[FRUIT_TYPE_NUM];
   CCSprite* mpFruitPressType[FRUIT_TYPE_NUM];
   CGameFruitField mField[FIELD_Y][FIELD_X];
   //第一次消除格数
   std::vector<CGameFruitField*> mVecPath;
   //道具效果使用后的总消除格数
   std::vector<CGameFruitField*> mVecPathTotal;
   std::vector<CGameFruit*> mVecFruit;
   bool	mbFinger;
   unsigned long mulLastTouchTime;
   unsigned long mulContinueHitTimeLimit;
   CCRect mRcFieldArea;
   bool mbUseCrossBomb;
   bool mbUseColour;
};

#endif
