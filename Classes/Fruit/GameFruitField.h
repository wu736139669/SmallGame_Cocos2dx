#ifndef Game_Fruit_Field_h
#define Game_Fruit_Field_h
#include "cocos2d.h"
#include "GameFruitDefine.h"
USING_NS_CC;
class CGameFruitEffect
{
public:
	CGameFruitEffect():mbInvalid(false),mType(eEffectNone),mnMask(0),mnColourDelType(-1)
	{}
	~CGameFruitEffect(){}
public:
	void addMask(int nMask);
	bool isMask(int nMask);
public:
	//typedef std::vector<ERTOpretateType> VEC_OP;

	//道具效果类型
	EFruitEffect mType;
	//消除类型，颜色消除用到
	int mnColourDelType;
	//标志
	int mnMask;
	//允许操作类型
	//VEC_OP mVecOp;
	//是否无效
	bool mbInvalid;
};
class CGameFruit:public CCObject
{
	typedef std::vector<CGameFruitEffect> VEC_EFFECT;
public:
	virtual bool init();
	void ClickFruit();
	void NoClickFruit();
	void RandFruit();
	void chgFruit(int nFruitType);
	void PlayIceAin(float fTotalTime);
	void AniCallback(CCNode* sender, void* data);
	void delFruit();
	bool isDelFruit();

	//显示特效
	void showEffect();
	//执行特效
	void executeEffect();
	//抖动
	void shakeEffect();
	EFruitEffect getEffectVal();
	CGameFruitEffect* getFrontEffect();
	//添加道具特效
	void addEffect(EFruitEffect effect);
	VEC_EFFECT& getVecEffect();
	void delEffect();

	CREATE_FUNC(CGameFruit)
	CGameFruit();
	~CGameFruit();
	
	CC_SYNTHESIZE(int,mnType,Type)
	CC_SYNTHESIZE(CCSprite*,mpSprite,Sprite)
	CC_SYNTHESIZE(CCAnimation*,mpAni,Ani);
	CC_SYNTHESIZE(CCSprite*,mpIce,Ice);
	CC_SYNTHESIZE(CCSprite*,mpBombEff,BombEff);
	CC_SYNTHESIZE(CCSprite*,mpBombRang,BombRang);
	CC_SYNTHESIZE(CCSprite*,mpLightning,Lightning);

	CC_SYNTHESIZE(CCSprite*,mpLightningRow,LightningRow);
private:
	VEC_EFFECT mVecEffect;
	//CC_SYNTHESIZE(EFruitState,mState,State);
};
class CGameFruitField 
{
public:
	CGameFruitField();
	~CGameFruitField();

	CCPoint GetCentrePos();
	void ResetScore();
	void UpdataScore();
	bool isGenIng();
	
public:
	CCPoint mPt;
	CCPoint mRealPt;
	CCRect mRect;
	CCSprite* mpLine;

	CC_SYNTHESIZE(CCSprite*,mpScore,Score);
	CC_SYNTHESIZE(CGameFruit*,mpFruit,Fruit);
};
#endif