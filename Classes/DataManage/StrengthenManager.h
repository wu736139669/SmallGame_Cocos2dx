//
//  StrengthenManager.h
//  OnceAgain
//
//  Created by mac on 14-4-8.
//
//

#ifndef __OnceAgain__StrengthenManager__
#define __OnceAgain__StrengthenManager__

#include "cocos2d.h"
#include <string>
#include "Singleton.h"
#include "JsonHelper.h"
#include "ComData.h"

class CBasePacket;
enum eStrengthenId {
    StrengThenTag_2 = 50001,   //魔力之源
    StrengThenTag_3 = 50002,   //魔力加强
    StrengThenTag_4 = 50003,    //魔力爆发
    StrengThenTag_5 = 50004,    //万能宝石
    StrengThenTag_6 = 50005,    //宝石精华
    StrengThenTag_7 = 50006,    //金手指
    StrengThenTag_8 = 50007,    //萌系头像
    StrengThenTag_9 = 50008,    //神奇星星
    StrengThenTag_10 = 50009,   //列队排阵
    StrengThenTag_11 = 50010,  //金币牌
    StrengThenTag_12 = 50011,  //高分牌
    StrengThenTag_13 = 50012,  //奖励牌
    StrengThenTag_14 = 50013,  //分值加成
    StrengThenTag_15 = 50014,  //延长乐点
    StrengThenTag_16 = 50015,  //震鼓奖励
    StrengThenTag_17 = 50022,  //三消，星星
    StrengThenTag_18 = 50023,  //三消，同色消除
    StrengThenTag_19 = 50024,  //三消，格外分数
    };
struct sStrengthenLv {
    int strengthenLv;
    std::string strengthenValue;
    int currencyId;
    int currencyValue;
};
typedef std::vector<sStrengthenLv> VEC_STRENGTHENLV;
struct sStrengthen {
    int strengthenId;
    std::string strengthenName;
    std::string strengthenDetail;
    int strengthenMaxLv;
    int strengthenImg;
    VEC_STRENGTHENLV lvInfo;
};
typedef std::vector<sStrengthen> VEC_STRENGTHEN;
class CStrengthenMan : public CSingleton<CStrengthenMan>,public ILoadTempData
{
public:
    CStrengthenMan();
    ~CStrengthenMan();
public:
    VEC_STRENGTHEN& getStrengthenTmpData(){return mVecStrengthenData;};
    
    void parseNetData(CBasePacket* pBasePacket);
	sStrengthen* getChgTempData(int nId);
    sStrengthenLv* getLvInfo(int lv, VEC_STRENGTHENLV& lvInfo);
	sStrengthenLv* getLvInfoByLvAndId(int nId,int lv);
	virtual void reset();
    
    void RequestGetAllStrength();        //获取所有的强化.
    void RequestGetAllLvInfo();          //获取所有强化等级.
    void RequestGetInfoByGameId(int gameId); //获取某款游戏信息.
    void RequestGetPlayInfoByGameId(int gameId);  //获取玩家的某款游戏信息.
    void RequestStrengthenLvUp(int strengthenId, int gameId); //升级强化.

	virtual void updataTemplateData(const char* str);
protected:
	VEC_STRENGTHEN mVecStrengthenData;
};
#endif /* defined(__OnceAgain__StrengthenManager__) */
