#ifndef Game_Fruit_Define_h
#define Game_Fruit_Define_h
#include "FruitData.h"

#define FRUIT_SOUND_PATH() "./game_fruit/Sounds/"

#define FRUIT_DIFF_SCORE_1 20000
#define FRUIT_DIFF_SCORE_2 100000
//连击限制时间
#define FRUIT_CONTINUE_LIMT_TIME 3000

#define FRUIT_CRAZY_ADD_1 2
#define FRUIT_CRAZY_ADD_2 3
#define FRUIT_BOMB_ROUND 3
//图形消除累计
#define FRUIT_DEL_ACC 50

//连续消除分数值
#define FRUIT_CONTINUE_DEL_SCORE 50

//水果个数
#define FRUIT_TYPE_NUM 3

enum EFruitEffect
{
	eEffectNone,	
	eEffectHor = 1,		//横
	eEffectVertical,	//竖
	eEffectCross,		//十字
	eEffectColour,		//颜色消除
	eEffectMultipleUse,	//万能球
	eEffectBomb,		//炸弹	
};
enum EFruitLayer
{
	eLayerEffect1=1,
	eLayerItem,
	eLayerEffect2,//炸弹层
	eLayerEffect3,
};

// enum ERTOpretateType
// {
// 	eRTOperateSel,
// 	eRTOperateMerge,
// 	eRTOperateDel,
// 	eRTOperateItem,//使用道具
// 	eRTOperateNone,
// };
//道具效果触发条件
enum EFruitEffectCondition
{
	eFrConditionOneItemDel,//一个道具消除
	eFrConditionMulItemDel,//多个道具消除
	eFrConditionNone,
};

enum EFruitType
{
	eFruitType_1 = 1,		//bule
	eFruitType_2 =  2,		//pink
	eFruitType_3 = 3,		//org
	eFruitType_4 = 4,		//green
	eFruitType_5 = 5,		//red
	eFruitTypeMulUse = 6,	//万能球

};

enum EFruitActionTag
{
	eFrActionGening = 2000,
};

#define  FR_MASK_TARGET_EFFECT 0x2 //触发目标效果
#define  FR_MASK_ALLOW_ONLY_ONE_ITEM_DEL 0x4 //条件：只删除一个物品
#define  FR_MASK_PLAYER_TARGET_EFFECT 0x8 //玩家指定触发效果
#define CFrData (*CFruitData::getInstance())

static const char* NOTICE_FRUIT_BOMB_EFFECT = "notice_fruit_bomb_effect";
#endif