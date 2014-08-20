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

	//����Ч������
	EFruitEffect mType;
	//�������ͣ���ɫ�����õ�
	int mnColourDelType;
	//��־
	int mnMask;
	//�����������
	//VEC_OP mVecOp;
	//�Ƿ���Ч
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

	//��ʾ��Ч
	void showEffect();
	//ִ����Ч
	void executeEffect();
	//����
	void shakeEffect();
	EFruitEffect getEffectVal();
	CGameFruitEffect* getFrontEffect();
	//��ӵ�����Ч
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