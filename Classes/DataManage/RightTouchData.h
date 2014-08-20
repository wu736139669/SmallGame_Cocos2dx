

#ifndef RIGHT_TOUCH_DATA_H
#define RIGHT_TOUCH_DATA_H
#include "cocos2d.h"
#include "BaseData.h"
#include "GameShare_Property.h"
#include "StrengthenManager.h"
enum ERTEffectType
{	
	//游戏道具效果
	eRTGameEffectColour = 1,	//染色
	eRTGameEffectRow,
	eRTGameEffectCol,
	eRTGameEffectScore,
	
	//付费道具效果
	eRTPayEffectCrazy,		//时间延长
	eRTPayEffectSkipErr,	//避免失误
	eRTPayEffectDelayTime,	//延时
	eRTPayEffectColourOpen, //染色剂开启

	//强化效果
	eRTIntensifyEffectGenBigCell = StrengThenTag_3,	//产生大细胞
	eRTIntensifyEffectSubItemGenVal = StrengThenTag_2,//减少道具能量条
	eRTIntensifyEffectQuickGrow = StrengThenTag_4,	//快速生长
	eRTEffectNone,
};
//基本效果
class CRTBaseEffect
{
protected:
	ERTEffectType meType ;
public:
	CRTBaseEffect(ERTEffectType eType):meType(eType){}
	~CRTBaseEffect(){}
	virtual ERTEffectType getType(){return meType; };
};
//////////////////////////////////////////////////////////////////////////
//付费道具效果
//时间延长
class CRTEffectTimeDelay : public CRTBaseEffect 
{
public:
	CRTEffectTimeDelay():CRTBaseEffect(eRTPayEffectDelayTime){}
};
class CRTEffectCrazy : public CRTBaseEffect 
{
public:
	CRTEffectCrazy():CRTBaseEffect(eRTPayEffectCrazy){}
};
class CRTEffectColourOpen : public CRTBaseEffect 
{
public:
	CRTEffectColourOpen():CRTBaseEffect(eRTPayEffectColourOpen){}
};
class CRTEffectSkipErr : public CRTBaseEffect 
{
public:
	CRTEffectSkipErr():CRTBaseEffect(eRTPayEffectSkipErr){}
};
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//强化相关效果
class CRTIntersifyEffect: public CRTBaseEffect 
{
public:
	CRTIntersifyEffect(ERTEffectType eType):CRTBaseEffect(eType),
		mnLev(0),mnEffectVal(0)
	{}
public:
	int mnLev;
	int mnEffectVal;
};

//大细胞
class CFrIntersifyEffectGenBigCell : public CRTIntersifyEffect 
{
public:
	CFrIntersifyEffectGenBigCell():CRTIntersifyEffect(eRTIntensifyEffectGenBigCell){}
};
//快速生长
class CFrIntersifyEffectQuickGrow : public CRTIntersifyEffect 
{
public:
	CFrIntersifyEffectQuickGrow():CRTIntersifyEffect(eRTIntensifyEffectQuickGrow),mnLimitNum(20),mnHitTimes(0){}
public:
	int mnHitTimes; //连击次数
	int mnLimitNum;
};

class CFrIntersifyEffectSubItemGenVal : public CRTIntersifyEffect 
{
public:
	CFrIntersifyEffectSubItemGenVal():CRTIntersifyEffect(eRTIntensifyEffectSubItemGenVal){}
};

//////////////////////////////////////////////////////////////////////////
class CRightTouchData : public CBaseData
{
	CREATE_FUNC(CRightTouchData);

	//道具出现条件数值
	CC_SYNTHESIZE(int , mnItemGenVal,ItemGenVal);
	//道具出现条件上限
	CC_SYNTHESIZE(int , mnItemGenValLimit,ItemGenValLimit);
	//生成道具
	CC_SYNTHESIZE(bool , mbItemGen,ItemGen);
	
public:
	
    static CRightTouchData* getInstance();

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

	void alterItemGenVal(int delta);

	int getCrazyAdd();

	//virtual int setMode();

	//virtual int getMode();
	void updataMode();

	virtual int getContinueNum();

    //重置游戏数据为默认数值
    virtual void reset();
	//效果相关
	void addEffect(CRTBaseEffect* pEffect);
	void addEffectByItemId(int nItemId);
	CRTBaseEffect* getEffect(ERTEffectType eType);
	void delEffect(ERTEffectType eType);
	void clearEffect();
	void setEffectStrengthenVal(e_GameType eGameType,int nStrengthenId,float fEffVal);
	
protected:
    CRightTouchData();
    ~CRightTouchData();

    virtual bool init();
	std::vector<CRTBaseEffect*> mVecEffect;
};
#endif
