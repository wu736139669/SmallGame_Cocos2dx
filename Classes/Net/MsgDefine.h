
#ifndef _MsgDefine_H_
#define _MsgDefine_H_

enum eNetMsgType 
{
	eNetMsgTypePlayerSys = 1,//玩家系统
	eNetMsgTypeMoneySys = 2,//货币系统
	eNetMsgTypeGameSys = 3,//游戏系统
	eNetMsgTypeItemSys = 4,//道具系统
	eNetMsgTypeIntensifySys = 5,//强化系统
	eNetMsgTypeMissionSys = 6,//任务系统
	eNetMsgTypeTitleSys = 7,//称号系统
	eNetMsgTypeMedalSys = 8,//勋章系统
    eNetMsgTypeTestSys = 9,//测试系统.
    eNetMsgTypeMsgSys = 10, //消息系统.
    eNetMsgTypeFriendSys = 11,//好友系统
    eNetMsgTypePk        = 12, //pk系统.
    eNetMsgTypeSend         = 13, //赠送系统
	eNetMsgTypeBox			= 14,//盒子系统
};
enum eNetMsgCodePlayerSys 
{
	eNetMsgPlayerSysRegister = 1,		//注册
	eNetMsgPlayerSysBugGem = 2,			//用户购买宝石
	eNetMsgPlayerSysChgTiLi = 3,			//宝石兑换体力
	eNetMsgPlayerSysChgGold = 4,			//宝石兑换金币
	eNetMsgPlayerSysAddExp = 5,			//增加经验值
	eNetMsgPlayerSysAddGlod = 6,			//增加金币
	eNetMsgPlayerSysUpLev = 7,			//升级
	eNetMsgPlayerSysGetPlayerInfo = 8,	//获取买家信息
    eNetMsgPlayerSysReduceEnergy =  9,  //减少体力.
    eNetMsgPlayerSysSetRiceStatus = 10, //设置是否可以收饭
    eNetMsgPlayerSysGetPlayerRiceInfo = 11,
    eNetMsgPlayerSysGetPlayerInfoMore = 12, //获取这个玩家的所有信息
    eNetMsgPlayerSysGetPlayerPkInfoMation = 13, //获取这个玩家的pk信息与勋章
    eNetMsgPlayerSysGetPlayerMoneyInfo = 14 //获取这个玩家的金币信息
};
enum eNetMsgCodeGoldSys
{
	eNetMsgGoldSysGetMoneyTmpInfo = 1,	//获取所有货币兑换方案
	eNetMsgGoldSysGetMoneyInfo = 2,//获取所有货币信息
};
enum eNetMsgCodeGameSys
{
    eNetMsgGameSysSetMax = 1,   //设置游戏最高分.
    eNetMsgGameSysGetMax = 2,    //获取游戏最高分.
    eNetMsgGameSysGetGameInfo = 3,  //获取游戏信息.
    
};
enum eNetMsgCodeItemSys
{
    
    eNetMsgItemSysGetAll = 1,     //获取所有道具.
    eNetMsgItemSysBuy    = 2,     //购买道具.
    eNetMsgItemSysGetByGame = 3,   //获得某款游戏道具.
	eNetMsgItemSysGetPlayerPackage = 4, //取得玩家背包道具
};
enum eNetMsgCodeIntensifySys
{
    eNetMsgCodeIntensifySysLvUp = 1, //强化升级
    eNetMsgCodeIntensifySysGetGameInfo = 2,
    eNetMsgCodeIntensifySysGetPlayGameInfo = 3,
    eNetMsgCodeIntensifySysGetAllInfo   = 4,
    eNetMsgCodeIntensifySysGetAllLvInfo = 5
};
enum eNetMsgCodeMissionSys
{
    eNetMsgMissionSysTask = 1,     //完成任务
    eNetMsgMissionSysDayTask = 2,     //获取每日登录
	eNetMsgMissionSysDayTaskTemp = 3, //获取所有任务
	eNetMsgMissionSysDayTaskSelect = 4,//获取游戏的任务列表
    eNetMsgEveryDay = 5,//每日随机3个
	eNetMsgMissionSysDayTaskComplate = 6,
    eNetMsgMissionSysWeek = 7, //获取周任务
    eNetMsgMissionSysWeeked = 8, //完成周任务
    eNetMsgMissionSysWeekRewardKind = 9,//获取抽奖信息
    eNetMsgMissionSysWeekGetReward = 10 //抽奖
};
enum eNetMsgCodeTitleSys
{

};
enum eNetMsgCodeMedalSys
{

};
enum eNetMsgDataState
{
	eNetMsgDataStateComplete = 1,
	eNetMsgDataStateTimeOut = 2,
	eNetMsgDataStateNone
};
enum eNetMsgResCode
{
	eNetMsgResCodeSucceed = 200, //数据返回
	eNetMsgResMax,
};
enum eNetMsgCodeFirendSys {
    eNetMsgFriendSysGetAll = 1,    //获取所有好友.
    eNetMsgFriendSysGetTotal = 2,  //获取总分排行榜.
    eNetMsgFriendSysGetRankByGame = 3,   //获取单个游戏的排行.
    eNetMsgFriendSysSetFriend = 4,       //设置好友.
    eNetMsgFriendSysSendInvite = 5, //发生邀请
    eNetMsgFriendSysGetTime = 6//获取更新时间
    };
enum eNetMsgCodeSendSys {
    eNetMsgSendRice = 1,      //赠送体力
    eNetMsgReceiveRice = 2    //收到体力
    };
enum eNetMsgCodeInfoSys {
    eNetMsgGetAllInfo = 1,             //获取消息.
    eNetMsgGetSysInfo = 2,            //获取系统消息.
    eNetMsgGetPkInfo  = 3,              //获取pk消息.
    eNetMsgGetRiceInfo = 4,             //获取体力消息.
    eNetMsgReadInfo     = 5,            //阅读消息.
    eNetMsgReadSysInfo  = 6,            //阅读系统消息.
    eNetMsgReadPkInfo  = 7,             //阅读pk消息
    eNetMsgReadRiceInfo  = 8,           //阅读体力消息.
    eNetMsgGetBePkInfo = 9,             //被pk消息.
    eNetMsgGetInfoNum = 10,             //获取通知数量.
    };
enum eNetMsgCodePkSys {
    eNetMsgSendPk = 1,              //发出pk
    eNetMsgReceivePk = 2,             //接受pk
    };
#endif