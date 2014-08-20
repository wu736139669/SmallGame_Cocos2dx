#ifndef _TASK_DEFINE_H
#define _TASK_DEFINE_H
#include "TaskManager.h"

enum EEveryDayTaskType
{
	//////////////////////////////////////////////////////////////////////////
	//公共任务
	// 	1	'游戏分数达到%s分'
	// 	2	'该游戏玩%s次'
	// 	3	'一局游戏触发%s次疯狂模式'
	// 	4	'一局游戏获得%s连击数'
	// 	5	'20秒内获得%s分'
	// 	6	'超级疯狂模式持续%s秒'
	// 	7	'连击不断达到%s连击'
	// 	8	'一局触发炸弹%s次'
	// 	9	' 不使用付费道具完成%s局游戏'
	// 	10	' 随意使用%s个付费道具完成游戏'
	// 	11	'玩%s局游戏获得0分'
	// 	12	'在一局游戏中失误次数为%s'
	// 	13	'不触发炸弹完成%s局游戏 并达到50000分数'
	eDayTaskTypeShare_1 = 1,			//游戏分数
	eDayTaskTypeShare_2,
	eDayTaskTypeShare_3,				//疯狂模式
	eDayTaskTypeShare_4,
	eDayTaskTypeShare_5,
	eDayTaskTypeShare_6,
	eDayTaskTypeShare_7,
	eDayTaskTypeShare_8,
	eDayTaskTypeShare_9,
	eDayTaskTypeShare_10,
	eDayTaskTypeShare_11,
	eDayTaskTypeShare_12,
	eDayTaskTypeShare_13,
	//////////////////////////////////////////////////////////////////////////
	//	合体消除
	// 	14	'使用“染色剂”完成%s局游戏'
	// 	15	'触发%s次魔力爆破'
	// 	16	'直接出现圆形糖果累积达到%s个'
	// 	17	'融合红色星型糖果达到%s个'
	// 	18	'融合绿色星型糖果达到%s个'
	// 	19	'融合蓝色星型糖果达到%s个'
	// 	20	'融合黄色星型糖果达到%s个'
	// 	21	'消除红色圆形糖果达到%s个'
	// 	22	'消除绿色圆形糖果达到%s个'
	// 	23	'消除蓝色圆形糖果达到%s个'
	// 	24	'消除黄色圆形糖果达到%s个'
	// 	25	'前%s秒不能消除圆形糖果'
	// 	26	'一局触发染色剂达到%s次'
	// 	27	'一局触发横消达到%s次'
	// 	28	'一局触发竖消达到%s次'
	// 	29	'触发炸弹后一次炸掉圆形糖果达到%s个'
	// 	30	'触发横消后一次消除的圆形糖果达到%s个'
	// 	31	'触发竖消后一次消除的圆形糖果达到%s个'
	eDayTaskTypeRT_14,
	eDayTaskTypeRT_15,
	eDayTaskTypeRT_16,
	eDayTaskTypeRT_17,
	eDayTaskTypeRT_18,
	eDayTaskTypeRT_19,
	eDayTaskTypeRT_20,
	eDayTaskTypeRT_21,
	eDayTaskTypeRT_22,
	eDayTaskTypeRT_23,
	eDayTaskTypeRT_24,
	eDayTaskTypeRT_25,
	eDayTaskTypeRT_26,
	eDayTaskTypeRT_27,
	eDayTaskTypeRT_28,
	eDayTaskTypeRT_29,
	eDayTaskTypeRT_30,
	eDayTaskTypeRT_31,

	//////////////////////////////////////////////////////////////////////////
	//	宝石连线
	// 	32	'使用道具“十字爆”完成%s局游戏'
	// 	33	'使用道具“同色爆”完成%s局游戏'
	// 	34	'一局触发金手指达到%s次'
	// 	35	'触发万能球达到%s次'
	// 	36	'消除红色宝石%s个'
	// 	37	'消除紫色宝石%s个'
	// 	38	'消除黄色宝石%s个'
	// 	39	'消除蓝色宝石%s个'
	// 	40	'消除绿色宝石%s个'
	// 	41	'用道具消除的宝石达到%s个'
	// 	42	'同色消除一次消除宝石%s个'
	// 	43	'一局游戏中一次手动消除10个宝石以上达到%s次'
	// 	44	'利用横消竖消消除%s个宝石'
	// 	45	'一局触发%s次同色消除'
	// 	46	'一局触发%s次十字消除'
	eDayTaskTypeFT_32,
	eDayTaskTypeFT_33,
	eDayTaskTypeFT_34,
	eDayTaskTypeFT_35,
	eDayTaskTypeFT_36,
	eDayTaskTypeFT_37,
	eDayTaskTypeFT_38,
	eDayTaskTypeFT_39,
	eDayTaskTypeFT_40,
	eDayTaskTypeFT_41,
	eDayTaskTypeFT_42,
	eDayTaskTypeFT_43,
	eDayTaskTypeFT_44,
	eDayTaskTypeFT_45,
	eDayTaskTypeFT_46,

	//////////////////////////////////////////////////////////////////////////
	//  音乐达人
	// 	47	'使用道具“一击即中”完成%s局游戏'
	// 	48	'使用道具“快节奏”完成%s局游戏'
	// 	49	'获得Great奖励%s次'
	// 	50	'获得Perfect奖励%s次'
	// 	51	'按到附加加分效果乐点%s次'
	// 	52	'按到延长乐点%s次'
	// 	53	'一局中达成震鼓奖励%s次'
	// 	54	'在一次震鼓奖励中获得%s点击数'
	// 	55	'在%s局游戏中出现的恶魔图形都按到'
	// 	56	'连续获得%s次perfect'
	// 	57	'一局游戏中只按一种乐点达成%s分数'
	// 	58	'一局游戏从延长乐点中获得%s额外分数'
	// 	59	'两次震鼓奖励的间隔时间不超过%s秒'
	// 	60	'用炸弹炸掉%s个恶魔图形'
	// 	61	'获得奖励分数20000分达到%s次'
	// 	62	'%s局游戏中Great次数大于Perect次数'
	// 	63	'%s局游戏中Perect次数大于Greatt次数'
	eDayTaskTypeTK_47,
	eDayTaskTypeTK_48,
	eDayTaskTypeTK_49,
	eDayTaskTypeTK_50,
	eDayTaskTypeTK_51,
	eDayTaskTypeTK_52,
	eDayTaskTypeTK_53,
	eDayTaskTypeTK_54,
	eDayTaskTypeTK_55,
	eDayTaskTypeTK_56,
	eDayTaskTypeTK_57,
	eDayTaskTypeTK_58,
	eDayTaskTypeTK_59,
	eDayTaskTypeTK_60,
	eDayTaskTypeTK_61,
	eDayTaskTypeTK_62,
	eDayTaskTypeTK_63,

	//////////////////////////////////////////////////////////////////////////
	//	超级记忆
	// 	64	'使用道具“简单排列”完成%s局游戏'
	// 	65	'使用道具“6种牌”完成%s局游戏'
	// 	66	'一局游戏出现%s种牌'
	// 	67	'成功配对%s对牌'
	// 	68	'一局获得额外分数20000分达到%s次'
	// 	69	'获得额外分数20000分达到%s次'
	// 	70	'配对金币牌达到%s次'
	// 	71	'触发奖励牌%s次'
	// 	72	'连续失误%s次'
	// 	73	'连续%s轮内都有配对到同一种牌'
	// 	74	'使用道具“简单排列”触发的效果达到%s次'
	// 	75	'一局游戏获得的金币达到%s'
    eDayTaskTypeTK_64,
    eDayTaskTypeTK_65,
    eDayTaskTypeTK_66,
    eDayTaskTypeTK_67,
    eDayTaskTypeTK_68,
    eDayTaskTypeTK_69,
    eDayTaskTypeTK_70,
    eDayTaskTypeTK_71,
    eDayTaskTypeTK_72,
    eDayTaskTypeTK_73,
    eDayTaskTypeTK_74,
    eDayTaskTypeTK_75,
    

	//////////////////////////////////////////////////////////////////////////
	//	快速配对
	// 	76	'使用道具“连击延长1”完成%s局游戏'
	// 	77	'使用道具“疯狂开局”完成%s局游戏'
	// 	78	'配对礼物盒达到%s次'
	// 	78	'配对礼物盒达到%s次'
	// 	78	'配对礼物盒达到%s次'
	// 	79	'触发简单排列效果%s次'
	// 	79	'触发简单排列效果%s次'
	// 	79	'触发简单排列效果%s次'
	// 	80	'触发星星头像效果%s次'
	// 	80	'触发星星头像效果%s次'
	// 	80	'触发星星头像效果%s次'
	// 	81	'前10秒内成功配对%s对'
	// 	81	'前10秒内成功配对%s对'
	// 	81	'前10秒内成功配对%s对'
    eDayTaskTypeTK_76,
    eDayTaskTypeTK_77,
    eDayTaskTypeTK_78,
    eDayTaskTypeTK_79,
    eDayTaskTypeTK_80,
    eDayTaskTypeTK_81,
    
    
    //////////////////////////////////////////////////////////////////////////
    //  躲避达人
    //  82.使用道具“加速装填”完成%s局游戏
    //  83.一局游戏中发射炮弹%s发
    //  84.打中对方炮台%s次
    //  85.打死小怪兽%s只
    //  86.阻挡炮弹轰炸%s次
    //  87.触发“行动停止”效果%s次
    //  88.触发“行动减缓”效果%s次
    //  89.被炮弹轰炸%s次
    //  90.打中可爱怪兽%s次
    //  91.打出%s发分裂弹
    //  92.在5秒内打出%s发炮弹
    eDayTaskTypeTK_82,
    eDayTaskTypeTK_83,
    eDayTaskTypeTK_84,
    eDayTaskTypeTK_85,
    eDayTaskTypeTK_86,
    eDayTaskTypeTK_87,
    eDayTaskTypeTK_88,
    eDayTaskTypeTK_89,
    eDayTaskTypeTK_90,
    eDayTaskTypeTK_91,
    eDayTaskTypeTK_92,
    
    
    ////////////////////////////////////////////////////////////////////////
    //  三消达人
    //  93.使用道具“同色消除”完成%s局游戏
    //  94.使用道具“十字消除”完成%s局游戏
    //  95.消除红色水母%s个
    //  96.消除紫色水母%s个
    //  97.消除黄色水母%s个
    //  98.消除蓝色水母%s个
    //  99.消除绿色水母%s个
    //  100.用道具消除的水母达到%s个
    //  101.一局游戏触发%s次同色消除
    //  102.一局游戏触发%s次十字消除
    //  103.一局游戏从加分块中获得%s额外分数
    //  104.一局游戏触发三排消除达到%s次
    eDayTaskTypeTK_93,
    eDayTaskTypeTK_94,
    eDayTaskTypeTK_95,
    eDayTaskTypeTK_96,
    eDayTaskTypeTK_97,
    eDayTaskTypeTK_98,
    eDayTaskTypeTK_99,
    eDayTaskTypeTK_100,
    eDayTaskTypeTK_101,
    eDayTaskTypeTK_102,
    eDayTaskTypeTK_103,
    eDayTaskTypeTK_104
};
//process every day task value accumulative
#define CTaskManProce(taskType,Val) CTaskMan::sharedInstance().processEveryDayTask(taskType,Val)
#define CTaskManProceDt(taskType,deltaVal)  CTaskMan::sharedInstance().processEveryDayTaskDelta(taskType,deltaVal)
#endif