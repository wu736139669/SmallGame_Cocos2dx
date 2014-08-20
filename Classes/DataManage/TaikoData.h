

#ifndef TaiKo_DATA_H
#define TaiKo_DATA_H
#include <vector>
#include "cocos2d.h"
#include "BaseData.h"
#include "TaikoDefine.h"
#include "../CCPlatformMacros.h"
#include "StrengthenManager.h"
#include "GameShare_Property.h"
enum ETaikoEffectType
{	
	//游戏道具效果
	eTaikoGameEffectScore = 1,	//奖励分数
	eTaikoGameEffectClickInvalid,	//不能按图形
	eTaikoGameEffectShakeDrum,		//震鼓奖励阶段
	eTaikoGameEffectPrefect,	//Perfect道具

	//付费道具效果
	eTaikoPayEffectTimeDelay,		//时间延长
	eTaikoPayEffectSkipErr, //避免失误
	eTaikoPayEffectABlow,		//一击即中
	eTaikoPayEffectAddClickArea,//加大黄圈
	eTaikoPayEffectAddSpeed,		//快节奏

	//强化效果
	eTaikoIntensifyAddScore = StrengThenTag_14,	//分值加成
	eTaikoIntensifyGenLongCell = StrengThenTag_15,			//延长乐点
	eTaikointensifyShakeDrum = StrengThenTag_16,				//震鼓奖励
	eTaikoEffectTypeNone,
};
enum ETaikoOperateState{
	ETaikoOpGreen = 1,
	ETaikoOpPerfect,
	ETaikoOpMiss,
	ETaikoOpProtect,
	ETaikoOpNone
};
//基本效果
class CTaikoBaseEffect
{
protected:
	ETaikoEffectType meType ;
public:
	CTaikoBaseEffect(ETaikoEffectType eType):meType(eType){}
	~CTaikoBaseEffect(){}
	virtual ETaikoEffectType getType(){return meType; };
};
//////////////////////////////////////////////////////////////////////////
//付费道具
//时间延长
class CTaikoEffectTimeDelay : public CTaikoBaseEffect 
{
public:
	CTaikoEffectTimeDelay():CTaikoBaseEffect(eTaikoPayEffectTimeDelay){}
};

class CTaikoPayEffectABlow : public CTaikoBaseEffect 
{
public:
	CTaikoPayEffectABlow():CTaikoBaseEffect(eTaikoPayEffectABlow){}
};

class CTaikoPayEffectAddClickArea : public CTaikoBaseEffect 
{
public:
	CTaikoPayEffectAddClickArea():CTaikoBaseEffect(eTaikoPayEffectAddClickArea){}
};
class CTaikoPayEffectAddSpeed : public CTaikoBaseEffect 
{
public:
	CTaikoPayEffectAddSpeed():CTaikoBaseEffect(eTaikoPayEffectAddSpeed){}
};
class CTaikoPayEffectSkipErr : public CTaikoBaseEffect 
{
public:
	CTaikoPayEffectSkipErr():CTaikoBaseEffect(eTaikoPayEffectSkipErr){}
};
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//游戏中道具相关效果
class CTaikoGameEffect: public CTaikoBaseEffect 
{
public:
	CTaikoGameEffect(ETaikoEffectType eType,int nLimitNum):CTaikoBaseEffect(eType),
		mnLimitNum(nLimitNum),mnCounter(0)
	{}
public:
	int mnLimitNum;		//点击上限/条件值
	int mnCounter;		//计数
};
//奖励分数
class CTaikoGameEffectScore : public CTaikoGameEffect 
{
public:
	CTaikoGameEffectScore():CTaikoGameEffect(eTaikoGameEffectScore,15){}
};
//不能按图形
class CTaikoGameEffectClickInvalid : public CTaikoGameEffect 
{
public:
	CTaikoGameEffectClickInvalid():CTaikoGameEffect(eTaikoGameEffectClickInvalid,5){}
};
//震鼓奖励阶段
class CTaikoGameEffectShakeDrum : public CTaikoGameEffect 
{
public:
	CTaikoGameEffectShakeDrum():CTaikoGameEffect(eTaikoGameEffectShakeDrum,25),mbGening(false),mfGenInterval(3.f),mbClickValid(false){}
public:
	bool mbClickValid;
	bool mbGening;
	float mfGenInterval;
};
//Perfect道具
class CTaikoGameEffectPrefect : public CTaikoGameEffect 
{
public:
	CTaikoGameEffectPrefect():CTaikoGameEffect(eTaikoGameEffectPrefect,20),mnUseTimes(0),mnUseLimit(10),mbPerfectState(false){}
public:
	int mnUseTimes;
	int mnUseLimit;
	bool mbPerfectState;
};
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//强化相关效果
class CTaikoIntersifyEffect: public CTaikoBaseEffect 
{
public:
	CTaikoIntersifyEffect(ETaikoEffectType eType):CTaikoBaseEffect(eType),
	mnLev(0),mfEffectVal(0)
	{}
public:
	int mnLev;
	float mfEffectVal;
};

//分值加成
class CTaikoIntensifyAddScore : public CTaikoIntersifyEffect 
{
public:
	CTaikoIntensifyAddScore():CTaikoIntersifyEffect(eTaikoIntensifyAddScore){}
};
//延长乐点
class CTaikoIntensifyGenLongCell : public CTaikoIntersifyEffect 
{
public:
	CTaikoIntensifyGenLongCell():CTaikoIntersifyEffect(eTaikoIntensifyGenLongCell){}
};
//震鼓奖励
class CTaikointensifyShakeDrum : public CTaikoIntersifyEffect 
{
public:
	CTaikointensifyShakeDrum():CTaikoIntersifyEffect(eTaikointensifyShakeDrum){}
};

//////////////////////////////////////////////////////////////////////////
struct sMGameStrengthen;
class CTaikoData : public CBaseData
{
	CREATE_FUNC(CTaikoData);
public:
	CTaikoData();
	~CTaikoData();
public:
    static CTaikoData* getInstance();

	//清理
    void purge();
    /**
     *	@brief	 对anger的操作
     *
     *	@param 	delta 	正负值均可
     */
    void alterAnger(int delta);
	void alterContinueNum(int delta);
	void alterCrazyContinueNum(int delta);
	void alterScore(int delta);
	int getCrazyAdd();
	void updataMode();

	virtual bool init();
	virtual int getContinueNum();
	virtual int getCrazyContinueNum();
	
    //重置游戏数据为默认数值
    void reset();
	//效果相关
	void addEffect(CTaikoBaseEffect* pEffect);
	void addEffectByItemId(int nItemId);
	CTaikoBaseEffect* getEffect(ETaikoEffectType eType);
	void delEffect(ETaikoEffectType eType);
	void clearEffect();
	float toSpeed(float fDisplacement,CCPoint ptStart,CCPoint ptEnd);
	float toDisplacement(float fTargetSpeed,CCPoint ptStart,CCPoint ptEnd);
	void setEffectStrengthenVal(e_GameType eGameType,int nStrengthenId,float fEffVal);
	
	std::vector<CTaikoBaseEffect*> mVecEffect;
	CC_SYNTHESIZE(ETaikoOperateState,mStateOp,StateOp); 
	CC_SYNTHESIZE(int,mnInvaildCellGenTimes,InvaildCellGenTimes); 
	CC_SYNTHESIZE(int,mnInvaildCellHitTimes,InvaildCellHitTimes); 
	CC_SYNTHESIZE(long,mlLastShakeDrumTime,LastShakeDrumTime);
};
#endif
