

#ifndef Player_Info_H
#define Player_Info_H
#include "cocos2d.h"
#include <string>
#include "Singleton.h"
#include "JsonHelper.h"
#include "StrengthenManager.h"
//区别强化的id

//强化的基础信息.
struct sMGameStrengthen{
    int strengthenId;
    int strengthenlv;
    std::string strengthenValue;
    int currencyId;
    int currencyValue;
    std::string strengthenDetail;
    std::string strengthenName;
    int strengthenImg;
};
struct sMStrengInfo {
    int strengthenId;
    int strengtheLv;
};
typedef vector<sMStrengInfo> VEC_MGAMESTRENGTHEN;
//玩家的游戏强化信息.
struct sMStrengthen {
    int gameId;
    VEC_MGAMESTRENGTHEN mGameStrengthen;

};
typedef vector<sMStrengthen> VEC_MSTRENGTHEN;
struct s_GameData {
    int gameId;       //游戏id.
    int highestScore;    //游戏最高分.
    
};
typedef std::vector<s_GameData> VEC_GAMEDATA;
struct SPlayerInfo
{
	int	nId;                        //玩家ID
	std::string strName;            //玩家名称
	std::string strUuId;            //唯一标识
	std::string strImg;             //玩家头像
	int nLevel;                     //等级
	int	nPower;                     //体力
	int	nMoney;                     //金币
	int	nGem;                       //宝石
	std::string	strQQ;              //QQ号
	std::string	strSina;            //Sina号
    std::string appId;             //appid
	int	nScore;                     //游戏总分
    long lastDailyTaskTime;         //最后一次获取每日任务的时间戳
	int	nExp;                       //经验值
    int nDailyTaskId;               //每日奖励到达的天数.
    int riceEndTime;                //最后一次加饭的时间.
    int sysInfoNum;                 //消息通知数量.
	int nPlayerMedal;				//玩家勋章
    VEC_GAMEDATA mGameData;         //玩家的游戏数据.
    VEC_MSTRENGTHEN mStrengthen;    //玩家的强化信息.
};
typedef vector<SPlayerInfo> VEC_PLAYERINFO;
class CBasePacket;
class CPlayerInfoMan :public CSingleton<CPlayerInfoMan>
{	
public:
	CPlayerInfoMan();
	~CPlayerInfoMan();
public:
    
	SPlayerInfo& getPlayerInfo(){return mPlayerInfo;};

	void parseNetData(CBasePacket* pBasePacket);
	virtual void reset();

    
    
    sMStrengthen* getMStrengthenByGameId(int gameId);
    
    int getPlayerLevel();
    //根据位置获取玩家的强化信息.0代表错误,1代表正确，2代表是最大等级
    int getMStrengthenByGameTag(int gameId, int strengTag, sMGameStrengthen &mGameStrengthen);
    //根据id获取玩家的强化信息.
    int getMStrengthenByGameId(int gameId, eStrengthenId strengId, sMGameStrengthen &mGameStrengthen);
	//////////////////////////////////////////////////////////////////////////
	//网络请求
	void RequestPlayerInfo();
	void RequsetRMBToDiamond(int nId);		//RMB换钻石.
    void RequestDiamondToRice(int nId);     //宝石兑换体力.
    void RequestDiamondToGold(int nId);     //宝石兑换金币.
    void RequestAddGold(int gold);          //增加金币.
    void RequestAddExp(int exp);          //增加经验值.
    void RequestPlayRegist(const char* name, const char* avatarUrl, int type, const char* userId, long timeStamp);               //注册.
    void RequestUseRice();                   //消耗体力.
    
    void RequestSendRice(int sendId);                 //赠送体力.
    void RequestReceiverice(int recId);              //领取体力.
//    void RequestSetGameMaxScore(int gameType, int maxScore); //设置游戏最高分.
//    void RequestgetGameMaxScore(int gameType);               //获得游戏最高分
	//////////////////////////////////////////////////////////////////////////
    void setNowLv(int lv); //设置当前等级
    
    void setLoginPreson(bool kind);
    bool getLoinStatus(){return isTouristLogin;};
    void setLognFirst(bool kind);
    bool getLognFirst(){return isLognFirst;};
    
    void setplayerpower(int num);
    
    void RequestPkInfoMation();
    void RequestPlayerMoneyInfoMation();
protected:
	SPlayerInfo mPlayerInfo;
    bool isTouristLogin;
    bool isLognFirst;
};
#endif
