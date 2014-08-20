#ifndef RT_ITEM_Field_h
#define RT_ITEM_Field_h
#include "cocos2d.h"
#include "RightTouchDefine.h"
#include <vector>
#include "Mask.h"
USING_NS_CC;
class CRTItemEffect
{
public:
	CRTItemEffect():mbInvalid(false),mType(eRTItemEffectNone)
	{}
	~CRTItemEffect(){}
public:
	typedef std::vector<ERTOpretateType> VEC_OP;
	
	//道具效果类型
	ERTItemEffect mType;
	//允许操作类型
	VEC_OP mVecOp;
	//是否无效
	bool mbInvalid;
	//标志
	CBitMask mnMask;
};
class CRTItem:public CCNode
{
	typedef std::vector<CRTItemEffect> VEC_EFFECT;
public:
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	//执行点击
	void executeClick();
	//回退点击
	void reverseClick();
	//设置大小细胞
	void setState(int state);
	int getState();
	//设置细胞形状
	void setType(int nType);
	//更新细胞类型状态
	void updataCell();
	//生成细胞
	void randItem();
	//生成道具
	void randItemEffectGen();
	
	//执行融合
	void executeMerge();
	void executeMerageCallback(CCNode* sender, void* data);
	//显示特效
	void showEffect();
	//执行特效
	void executeEffect();
	
	//设置道具效果类型
	//void setEffect(ERTItemEffect effect);	
	ERTItemEffect getEffect();
	CRTItemEffect* getRealEffect();
	//添加道具特效
	void addEffect(ERTItemEffect effect,bool bFront = false);
	VEC_EFFECT& getVecEffect();
	void delEffect();

	CREATE_FUNC(CRTItem)
	CRTItem();
	~CRTItem();
	
	CC_SYNTHESIZE_READONLY(int,mnType,Type)
	CC_SYNTHESIZE(CCSprite*,mpSprite,Sprite)
	CC_SYNTHESIZE(CCSprite*,mpLight,Light)
	CC_SYNTHESIZE(CCAnimation*,mpAni,Ani);
	CC_SYNTHESIZE(int,mGold,Gold);
	CC_SYNTHESIZE(CCSprite*,mpEffectBelow,EffectBelow);
	CC_SYNTHESIZE(CCSprite*,mpEffectAbove,EffectAbove);
	CC_SYNTHESIZE(bool,mbMerge,Merge);
	CC_SYNTHESIZE(bool,mbExeDelEff,ExeDelEff);
	CC_SYNTHESIZE(bool,mpGenEffect,GenEffect)
	
private:
	int mState;
	//ERTItemEffect mEffect; 
	
	VEC_EFFECT mVecEffect;
	//CC_SYNTHESIZE(EFruitState,mState,State);
};
class CRTItemField :public CCNode
{
public:
	CRTItemField();
	~CRTItemField();

	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

	CCPoint GetCentrePos();
	//生成道具中
	void genIteming();
	//选择错误
	void selWrong();
	//重置
	void reset();
	//是否动作在播放
	bool isActionRun();
	//是否在生成中
	bool isGenIng();
	//生成效果完成回调
	void genCallback(CCNode* sender, void* data);
	//消除效果回调
	void starCallback(CCNode* sender, void* data);
	void effectInCallback(CCNode* sender, void* data);

	void executeEffect();
	//盾牌效果
	void executeSkipErrEff();

	CC_SYNTHESIZE(CCPoint,mPt,Pt);
	CC_SYNTHESIZE(CCRect,mRect,Rect);
	CC_SYNTHESIZE(CCSprite*,mpBg,Bg);
	CC_SYNTHESIZE(CRTItem*,mpItem,Item);
	CC_SYNTHESIZE(CCSprite*,mpSpEffectIn,SpEffectIn)
	
	CREATE_FUNC(CRTItemField)
};
#endif