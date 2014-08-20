#ifndef Taiko_Cell_h
#define Taiko_Cell_h
#include "cocos2d.h"
#include "TaikoDefine.h"
#include <vector>
#include "Mask.h"
USING_NS_CC;
class CTaikoCellEffect
{
public:
	CTaikoCellEffect():mbInvalid(false),mType(eTaikoEffectNone)
	{}
	~CTaikoCellEffect(){}
public:
	//道具效果类型
	ETaikoEffect mType;

	//是否无效
	bool mbInvalid;
	//标志
	CBitMask mnMask;
};
struct STaikoCellRandInfo
{
	ETaikoType eType;
	float fProbability;//概率
};
//点击分隔信息(用于延长乐点)
struct STaikoHitSplitInfo
{
	int nArea;
	bool bUse;
	float fPos;
};
//////////////////////////////////////////////////////////////////////////
//细胞提示
class CTaikoCellHint:public CCNode
{
	public:
		CTaikoCellHint():
		  mpHintBg(NULL),mpHint(NULL){}
	public:
		virtual bool init();
	public:
		void showEffect(int nType);
		void executeEffect(int nType);
	CREATE_FUNC(CTaikoCellHint);
	CC_SYNTHESIZE(CCSprite*,mpHintBg,HintBg);
	CC_SYNTHESIZE(CCSprite*,mpHint,Hint);
};
//////////////////////////////////////////////////////////////////////////
class CTaikoCell:public CCNode
{
public:
	typedef std::vector<CTaikoCellEffect> VEC_EFFECT;
	typedef std::vector<STaikoCellRandInfo> VEC_CELLRANDINFO;
	typedef std::vector<STaikoHitSplitInfo> VEC_HITSPLITINFO;
public:
	CTaikoCell();
	~CTaikoCell();
public:
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
public:
	//设置细胞形状
	void setType(int nType);
	//更新细胞类型状态
	void updataCell();
	//生成细胞
	void randCell();
	//生成道具
	void randCellEffectGen();
	//显示特效
	void showEffect();
	//执行特效
	void executeEffect();
	void moveTo(CCPoint& pt);
	void reset();
	void stopHead(float fOffectY);
	ETaikoEffect getEffect();
	CTaikoCellEffect* getFrontEffect();
	//添加道具特效
	void addEffect(ETaikoEffect effect,bool bFront = false);
	void delEffect();
	void executeASpeed();
	void executeDel(bool bAni = true);
	void executeDelCallback();
	CCRect getCollisionArea();
	CCRect getCollisionAreaHead();
	// whether click long cell
	bool isClickLongCell();
	void updataTextureArea(CCPoint ptSplit);
	//变灰
	void toGray();

	VEC_HITSPLITINFO& getVecHitSplitInfo();
	CREATE_FUNC(CTaikoCell)
	
	CC_SYNTHESIZE_READONLY(int,mnType,Type);
	CC_SYNTHESIZE(CCSprite*,mpSprite,Sprite);
	CC_SYNTHESIZE(CCSprite*,mpSpriteEff,SpriteEff);
	CC_SYNTHESIZE(CCSprite*,mpSpriteBg,SpriteBg);
	CC_SYNTHESIZE(CCSprite*,mpSpriteTail,SpriteTail);
	
	CC_SYNTHESIZE(CCSprite*,mpEffectBelow,EffectBelow);
	CC_SYNTHESIZE(CCSprite*,mpEffectAbove,EffectAbove);
	CC_SYNTHESIZE(CTaikoCellHint*,mpHint,Hint);
	CC_SYNTHESIZE(bool,mbExeDelEff,ExeDelEff);
	CC_SYNTHESIZE(bool,mpGenEffect,GenEffect);
	CC_SYNTHESIZE(float,mfSpeed,Speed);
	CC_SYNTHESIZE(float,mfDisplacement,Displacement);
	//是否miss
	CC_SYNTHESIZE(bool,mbMiss,Miss);
	//是否可以使用
	CC_SYNTHESIZE(bool,mbUse,Use);
	CC_SYNTHESIZE(bool,mbClicking,Clicking);
	//加速度
	CC_SYNTHESIZE(float,mfASpeed,ASpeed);
	CC_SYNTHESIZE(float,mfSpeedFactor,SpeedFactor);
	//强制完美
	CC_SYNTHESIZE(ETaikoOperateState,mOpState,OpState);
	CC_SYNTHESIZE(CCRect,mrcCollisionArea,CollisionArea);
	CC_SYNTHESIZE(CCRect,mrcCollisionAreaLong,CollisionAreaLong);
	CC_SYNTHESIZE(CCRect,mrcCollisionAreaTail,CollisionAreaTail);
private:
	VEC_HITSPLITINFO mVecHitSplitInfo;
	VEC_EFFECT mVecEffect;
	VEC_CELLRANDINFO mVecRandInfo;
};
#endif