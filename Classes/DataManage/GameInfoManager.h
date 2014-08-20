//
//  GameInfoManager.h
//  OnceAgain
//
//  Created by mac on 14-4-4.
//
//

#ifndef __OnceAgain__GameInfoManager__
#define __OnceAgain__GameInfoManager__

#include "cocos2d.h"
#include <string>
#include "Singleton.h"
#include "JsonHelper.h"
#include "GameItemManager.h"
#include "ComData.h"
#include "JsonHelper.h"
class CBasePacket;
struct sGameInfoData {
    int gameId;
    std::string gameName;
    vector<int> strengthenId;
    vector<int> itemId;
};
typedef vector<sGameInfoData> VEC_GAMEINFODATA;

class CGameInfoMan :public CSingleton<CGameInfoMan>,public ILoadTempData
{
public:
	CGameInfoMan();
	~CGameInfoMan();
public:
	VEC_GAMEINFODATA& getMoneyChgTmpData(){return mVecGameInfoData;};
    
	void parseNetData(CBasePacket* pBasePacket);
	sGameInfoData* getChgTempData(int nId);
    sItemData* getItemDate(int gameid,int itemTag);
	virtual void reset();
    
    void RequestSetGameMaxScore(int gameType, int maxScore); //设置游戏最高分.
    void RequestgetGameMaxScore(int gameType);               //获得游戏最高分.
    void RequestgetGameInfo(void);                           //获得游戏信息.
    virtual void updataTemplateData(CSJson::Value& root);
	virtual void updataTemplateData(const char* str);
protected:
	VEC_GAMEINFODATA mVecGameInfoData;
};
#endif /* defined(__OnceAgain__GameInfoManager__) */
