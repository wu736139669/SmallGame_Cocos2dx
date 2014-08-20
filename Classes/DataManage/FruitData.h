

#ifndef FRUIT_DATA_H
#define FRUIT_DATA_H
#include "cocos2d.h"
#include "BaseData.h"
#include "StrengthenManager.h"
#include "GameShare_Property.h"
enum EFrEffectType
{	
	//游戏道具效果
	eFrGameEffectHor = 1,	//横
	eFrGameEffectVertical,	//竖
	eFrGameEffectCross,		//十字
	eFrGameEffectColour,	//颜色消除

	//付费道具效果
	eFrPayEffectTimeDelay,		//时间延长
	eFrPayEffectAddContinueHit, //连击强化
	eFrPayEffectCrossOpen,		//开启十字爆
	eFrPayEffectColourOpen,		//开启颜色

	//强化效果
	eFrIntensifyEffectGoldFinger = StrengThenTag_7,	//金手指
	eFrIntensifyAnyBall = StrengThenTag_5,			//万能球
	eFrintensifyItem = StrengThenTag_6,				//道具强化
	eFrEffectNone,
};
//基本效果
class CFrBaseEffect
{
protected:
	EFrEffectType meType ;
public:
	CFrBaseEffect(EFrEffectType eType):meType(eType){}
	~CFrBaseEffect(){}
	virtual EFrEffectType getType(){return meType; };
};
//////////////////////////////////////////////////////////////////////////
//时间延长
class CFrEffectTimeDelay : public CFrBaseEffect 
{
public:
	CFrEffectTimeDelay():CFrBaseEffect(eFrPayEffectTimeDelay){}
};
//连击强化
class CFrEffectAddContinueHit : public CFrBaseEffect 
{
public:
	CFrEffectAddContinueHit():CFrBaseEffect(eFrPayEffectAddContinueHit){}
};
//开启十字爆
class CFrEffectCrossOpen : public CFrBaseEffect 
{
public:
	CFrEffectCrossOpen():CFrBaseEffect(eFrPayEffectCrossOpen){}
};
//开启颜色
class CFrEffectColourOpen : public CFrBaseEffect 
{
public:
	CFrEffectColourOpen():CFrBaseEffect(eFrPayEffectColourOpen){}
};
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//游戏中道具相关效果
class CFrGameEffect: public CFrBaseEffect 
{
public:
	CFrGameEffect(EFrEffectType eType,int nLimitNum):CFrBaseEffect(eType),
		mnLimitNum(nLimitNum),mnCounter(0)
	{}
public:
	int mnLimitNum;		//点击上限
	int mnCounter;		//计数
};
//十字消
class CFrGameEffectCross : public CFrGameEffect 
{
public:
	CFrGameEffectCross():CFrGameEffect(eFrGameEffectCross,35){}
};
//颜色消
class CFrGameEffectColour : public CFrGameEffect 
{
public:
	CFrGameEffectColour():CFrGameEffect(eFrGameEffectColour,30){}
};
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//强化相关效果
class CFrIntersifyEffect: public CFrBaseEffect 
{
public:
	CFrIntersifyEffect(EFrEffectType eType):CFrBaseEffect(eType),
	mnLev(0),mnEffectVal(0)
	{}
public:
	int mnLev;
	int mnEffectVal;
};

//金手指
class CFrIntersifyEffectGoldFinger : public CFrIntersifyEffect 
{
public:
	CFrIntersifyEffectGoldFinger():CFrIntersifyEffect(eFrIntensifyEffectGoldFinger),mnAmountHit(100),mnLastTime(0),mnHitTimes(0){}
protected:
public:
	int mnHitTimes; //消除次数次数
	int mnLastTime;
	int mnAmountHit;
};
//万能球
class CFrIntersifyEffectAnyBall : public CFrIntersifyEffect 
{
public:
	CFrIntersifyEffectAnyBall():CFrIntersifyEffect(eFrIntensifyAnyBall){}
};
//道具强化
class CFrIntersifyEffectItem : public CFrIntersifyEffect 
{
public:
	CFrIntersifyEffectItem():CFrIntersifyEffect(eFrintensifyItem){}
};
//////////////////////////////////////////////////////////////////////////

class CFruitData : public CBaseData
{
	CREATE_FUNC(CFruitData);
public:
	
    static CFruitData* getInstance();

	//消图累计
	CC_SYNTHESIZE(int , mnAccumulateRow,AccumulateRow);
	CC_SYNTHESIZE(int , mbAccumulateCol,AccumulateCol);
	CC_SYNTHESIZE(int , mnAccumulateRowLimit,AccumulateRowLimit);
	CC_SYNTHESIZE(int , mbAccumulateColLimit,AccumulateColLimit);


    CC_SYNTHESIZE(bool, mIsBeginner, IsBeginner);
    CC_SYNTHESIZE(float, mSoundVolume, SoundVolume);
    CC_SYNTHESIZE(float, mMusicVolume, MusicVolume);
	
	//清理
    void purge();
    
    //将数据从内存保存到外部文件中
    void flush();
    
    /**
     *	@brief	 对anger的操作
     *
     *	@param 	delta 	正负值均可
     */
    void alterAnger(int delta);

	void alterContinueNum(int delta);

	void alterCrazyContinueNum(int delta);

	void alterScore(int delta);

	virtual int getMode();

	virtual int getContinueNum();

	virtual int getCrazyContinueNum();

    //重置游戏数据为默认数值
    void reset();
	//效果相关
	void addEffect(CFrBaseEffect* pEffect);
	void addEffectByItemId(int nItemId);
	CFrBaseEffect* getEffect(EFrEffectType eType);
	void delEffect(EFrEffectType eType);
	void clearEffect();
	void setEffectStrengthenVal(e_GameType eGameType,int nStrengthenId,float fEffVal);

protected:
    CFruitData();
    ~CFruitData();

    virtual bool init();
	
	std::vector<CFrBaseEffect*> mVecEffect;
	//static CFruitData* s_pFruitData;
};
#endif
