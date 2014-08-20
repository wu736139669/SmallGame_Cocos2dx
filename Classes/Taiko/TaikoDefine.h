#ifndef TAIKO_Define_h
#define TAIKO_Define_h
#include "TaikoData.h"
enum ETaikoType{
	eTaikoType_Invalid,
	eTaikoType_1,
	eTaikoType_2,
	eTaikoType_BigDrum,//大鼓
	eTaikoType_1_Long,
	eTaikoType_2_Long,
	eTaikoNone,
};

enum ETaikoEffect
{
	eTaikoEffectBomb = 1,
	eTaikoEffectScore ,	//奖励分数
	eTaikoEffectClickInvalid,	//不能按图形
	eTaikoEffectShakeDrum,		//震鼓奖励阶段
	eTaikoEffectPrefect,	//Perfect道具
	eTaikoEffectIntensifyAddScore,
	eTaikoEffectNone,
};

enum ETaikoCellActTag
{
	eTaikoCellActSpeed = 1,
	eTaikoCellActDrumRod = 10, //鼓的棍子
};

enum ETaiKoSceneLayer
{
	eTaiKoSceneLayerBg,
	eTaiKoSceneLayerGame,
	eTaiKoSceneLayerBgRole,
	eTaiKoSceneLayerOpState = 100,
};

#define KAIKO_SCORE_FACTOR 50
//每个图形的基本分数为500
#define KAIKO_CELL_BASE_SCORE 500
//	不能按图形基本分数为1000
#define KAIKO_INVAIL_CELL_BASE_SCORE 1000
//超级疯狂模式连击需要次数
#define TAIKO_SUPER_MODE_CONTINUE_NEED_TIMES 25
#define TAIKO_COM_MODE_CONTINUE_NEED_TIMES 10

#define CTKData (*CTaikoData::getInstance())
#endif