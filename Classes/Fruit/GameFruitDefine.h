#ifndef Game_Fruit_Define_h
#define Game_Fruit_Define_h
#include "FruitData.h"

#define FRUIT_SOUND_PATH() "./game_fruit/Sounds/"

#define FRUIT_DIFF_SCORE_1 20000
#define FRUIT_DIFF_SCORE_2 100000
//��������ʱ��
#define FRUIT_CONTINUE_LIMT_TIME 3000

#define FRUIT_CRAZY_ADD_1 2
#define FRUIT_CRAZY_ADD_2 3
#define FRUIT_BOMB_ROUND 3
//ͼ�������ۼ�
#define FRUIT_DEL_ACC 50

//������������ֵ
#define FRUIT_CONTINUE_DEL_SCORE 50

//ˮ������
#define FRUIT_TYPE_NUM 3

enum EFruitEffect
{
	eEffectNone,	
	eEffectHor = 1,		//��
	eEffectVertical,	//��
	eEffectCross,		//ʮ��
	eEffectColour,		//��ɫ����
	eEffectMultipleUse,	//������
	eEffectBomb,		//ը��	
};
enum EFruitLayer
{
	eLayerEffect1=1,
	eLayerItem,
	eLayerEffect2,//ը����
	eLayerEffect3,
};

// enum ERTOpretateType
// {
// 	eRTOperateSel,
// 	eRTOperateMerge,
// 	eRTOperateDel,
// 	eRTOperateItem,//ʹ�õ���
// 	eRTOperateNone,
// };
//����Ч����������
enum EFruitEffectCondition
{
	eFrConditionOneItemDel,//һ����������
	eFrConditionMulItemDel,//�����������
	eFrConditionNone,
};

enum EFruitType
{
	eFruitType_1 = 1,		//bule
	eFruitType_2 =  2,		//pink
	eFruitType_3 = 3,		//org
	eFruitType_4 = 4,		//green
	eFruitType_5 = 5,		//red
	eFruitTypeMulUse = 6,	//������

};

enum EFruitActionTag
{
	eFrActionGening = 2000,
};

#define  FR_MASK_TARGET_EFFECT 0x2 //����Ŀ��Ч��
#define  FR_MASK_ALLOW_ONLY_ONE_ITEM_DEL 0x4 //������ֻɾ��һ����Ʒ
#define  FR_MASK_PLAYER_TARGET_EFFECT 0x8 //���ָ������Ч��
#define CFrData (*CFruitData::getInstance())

static const char* NOTICE_FRUIT_BOMB_EFFECT = "notice_fruit_bomb_effect";
#endif