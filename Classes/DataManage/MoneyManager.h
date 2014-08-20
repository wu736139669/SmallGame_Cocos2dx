

#ifndef MONEY_MANAGER_H
#define MONEY_MANAGER_H
#include "cocos2d.h"
#include <string>
#include "Singleton.h"
#include "JsonHelper.h"
#include "ComData.h"

enum e_ExchangeId {
    DiamondToGold_1 = 1,
    DiamondToGold_2,
    DiamondToGold_3,
    DiamondToGold_4,
    DiamondToGold_5,
    GoldToRice_1,
    GoldToRice_2,
    GoldToRice_3,
    GoldToRice_4,
    GoldToRice_5,
    RMBToDiamond_1,
    RMBToDiamond_2,
    RMBToDiamond_3,
    RMBToDiamond_4,
    RMBToDiamond_5,
    };
class CBasePacket;
struct SMoneySysChgTempData
{
	int ExchangeId;
	std::string ExchangeName;
	int ExchangeFromID;
	int ExchangeFromValue;
	int ExchangeToID;
	int ExchangeToValue;
};
typedef std::vector<SMoneySysChgTempData> VEC_MEONEYSYSCHGTEMPDATA; 

class CMoneyMan :public CSingleton<CMoneyMan>,public ILoadTempData
{	
public:
	CMoneyMan();
	~CMoneyMan();
public:
	VEC_MEONEYSYSCHGTEMPDATA& getMoneyChgTmpData(){return mVecMoneyChgTempData;};

	void parseNetData(CBasePacket* pBasePacket);
	SMoneySysChgTempData* getChgTempData(int nId);
	virtual void reset();

	//////////////////////////////////////////////////////////////////////////
	//网络请求
	void RequestGetMoneyTmpInfo();//请求货币兑换模板数据
	//////////////////////////////////////////////////////////////////////////

	virtual void updataTemplateData(const char* p);
protected:
	VEC_MEONEYSYSCHGTEMPDATA mVecMoneyChgTempData;
};
#endif
