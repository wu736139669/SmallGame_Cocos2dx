
#ifndef _DATA_MANAGER_H
#define _DATA_MANAGER_H

#include "NetHookManager.h"
#include "cocos2d.h"
#include "StrengthenManager.h"
#include "GameShare_Property.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

//每个游戏结束后奖励信息
struct SGameEndAward
{
	float fAddScore;//分数加成
	float fGold;//金币
	float fExp;//经验
};
class CBaseData;
class CDataManager : public INetHook
{
public:
    CDataManager();
    ~CDataManager();
public:
    static CDataManager& GetInstance();

	virtual bool onPackageFilter(void *pDataPkg);
	//游戏
	//更新缓存强化道具
	void updataStrengthenItem(e_GameType eGameType);
	//void Convert(const char* strIn,char* strOut, int sourceCodepage, int targetCodepage);  

	//取得游戏新手教程状态 1 ：未引导，0 ：引导
	bool getGameNewerGuideState(e_GameType eGameType);
	//
	void setGameNewerGuideState(e_GameType eGameType,bool bState);
	//流量统计
	void accTotalFlow(int nByte);
	//取得模板数据
	bool readTemplateData(char* szpFileName,ILoadTempData* pData);
	bool readTemplateData(char* szpFileName,string& strData);
	void wirteToFile(char* szpFileName,string& strWirteData);
    CBaseData* getGameData(int nGameId = -1);
public:
	long getTotalFlow();
protected:
	long mlTotalFlow;
	typedef void (CCObject::*CALLFUNCDATA)(const char*);
	
};

#endif