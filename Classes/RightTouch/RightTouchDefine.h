#ifndef RIGHT_TOUCH_Define_h
#define RIGHT_TOUCH_Define_h
#include "RightTouchData.h"

enum ERTItemState
{
	eRTItemState1 = 1,
	eRTItemState2,
	eRTItemState3,
};
enum ERTItemType
{
	eRTItemTypeRed = 1,		//红色
	eRTItemTypeGreen,			//绿色
	eRTItemTypeBule,			//蓝色
	eRTItemTypeOrg,			//橙色
};
enum ERTItemEffect
{
	eRTItemEffectRow,		//闪电
	eRTItemEffectCol,		//激光
	//eRTItemEffectGold,	//金币加1
	eRTItemEffectScore,		//分数*5
	eRTItemEffectColour,	//染色剂
	eRTItemEffectBomb,
	eRTItemEffectNone,
};
enum ETRItemLayer 
{
	eItemLayerItemBelow,
	eItemLayerItem,
	eItemLayerItemAbove,
};
enum ERTOpretateType
{
	eRTOperateSel,
	eRTOperateMerge,
	eRTOperateDel,
	eRTOperateItem,//使用道具
	eRTOperateErr,
	eRTOperateNone,
};
enum ERTEffectMask
{
	//eRTEffectMaskDelOp			= 0x1 << 0, //允许删除操作
	//eRTEffectMaskUseItemOp		= 0x1 << 1, //允许使用道具
	eRTEffectMaskMulCellDel 	= 0x1 << 2, //允许多格删除
	//eRTEffectMaskOneCellDel 	= 0x1 << 3, //允许单格删除
	//eRTEffectMaskMergeOp		= 0x1 << 4, //允许融合操作
};
//道具效果触发条件
enum ERRItemEffectCondition
{
	eRTConditionMulItemDel,//多个道具消除
	eRTConditionNone,
};

const static int TR_COL_NUM = 5;
const static int TR_ROW_NUM = 5;
//最高状态
const static int TR_STATE_MAX = 2;
const static int TR_TYPE_NUM = 3;

const static char* TR_SOUND_MERGE = "./right_touch/Sounds/merge.mp3";
const static char* TR_SOUND_BG = "./right_touch/Sounds/bg.mp3";
const static char* TR_SOUND_STAR_MERGE = "./right_touch/Sounds/star_megre.mp3";

#define RT_DIFF_SCORE_1 20000
#define RT_DIFF_SCORE_2 100000

#define RT_COM_MODE_CONTINUE_TIME_LIMIT 1500
#define RT_CRAZY_MODE_CONTINUE_TIME_LIMIT 1500
#define RT_CRAZY_SUPER_MODE_CONTINUE_TIME_LIMIT 1000
//合体消除分数系数值
#define RT_CONTINUE_DEL_SCORE 50

#define  TR_CRAZY_ADD_2 3
#define  TR_CRAZY_ADD_1 2
//道具生成数值
#define  RT_GEN_ITEM_VAL 4

//超级疯狂模式连击需要次数
#define RT_SUPER_MODE_CONTINUE_NEED_TIMES 25

static const char* NOTICE_RT_BOMB_EFFECT = "notice_rt_bomb_effect";
static const char* NOTICE_RT_COLOUR_EFFECT = "notice_rt_colour_effect";

#define CRtData (*CRightTouchData::getInstance())

#endif