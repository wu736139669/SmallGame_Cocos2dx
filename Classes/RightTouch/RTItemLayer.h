

#ifndef _RT_ITEM_Layer_H
#define _RT_ITEM_Layer_H
#include "cocos2d.h"
#include "RTItem.h"
#include "GameShare_Scene.h"
USING_NS_CC;
class CRTItemLayer : public GameShare_Scene
{
public:
	CRTItemLayer();
	~CRTItemLayer();
    CREATE_FUNC(CRTItemLayer);
	//初始化
    virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	virtual void initBgView(void);
	bool start();
	void click(CCTouch* touch);
	CRTItemField* GetFieldByTouch(const cocos2d::CCPoint* pPt);
	bool isExistPath(CRTItemField* pField);
	void updateData(float delta);

	//设置疯狂模式
	void setCrazyMode(bool bImmediately = false);
	//退出疯狂模式
	void exitCrazyMode();
	//消除成功
	void delSucceed(ERTOpretateType eOpType);
	//分数计算
	void calcScore();
	//计算需要消除元素
	void calcDelNumByState( CRTItemField* pCurField);
	void exeIntensifyEffQuickGrow();

	bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	void ccTouchMoved(CCTouch* touch, CCEvent* event);
	void ccTouchEnded(CCTouch* touch, CCEvent* event);

	//消息回调
	virtual void msgHandle_CrazyTimeOut(CCObject* obj);
	virtual void msgHanlde_GameTimeOut(CCObject* obj);

	//疯狂模式重写
	virtual void Crazy_Start(float rfDurationTime = 1.0f,ECrazyMode eMode = eComCrazyMode);
	virtual void Crazy_ReStart();

	virtual void startGame(float dt=1.0);

	void noticeBombEffect(CCObject* obj);
	void noticeColourEffect(CCObject* obj);
	virtual void noticeTimeInterval(CCObject* obj);
	//使用道具
	bool useItem(ERTEffectType eType);
	//处理道具
	void processItem(ERTEffectType eType);
	void executeEffect(CRTItemField* pField);
	CCRect& getFieldGameArea(){return mRcFieldArea;}
protected:
	void _setTitleAni();
protected:
	CRTItemField mField[TR_ROW_NUM][TR_COL_NUM];
	CCSprite* mpColEffect[TR_COL_NUM];
	CCSprite* mpRowEffect[TR_ROW_NUM];
	CCArray* mpArrClick;
	CCArray* mpArrDelItem;
	double mdbLastTime;
	ERTOpretateType mOp;
	bool mbIsResetHitTimes;//是否重置连击次数
	bool mbCrazyMode;
	CCRect mRcFieldArea;
	//日常任务累计相关
	bool mbDelItemStata2;		//是否消除圆形糖果
	bool mbUseColou;			//是否

};

#endif /* defined(__FishingJoy__BackgroundLayer__) */
