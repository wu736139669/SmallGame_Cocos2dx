//
//  GameItemManager.h
//  OnceAgain
//  道具的管理类.
//  Created by mac on 14-4-4.
//
//

#ifndef __OnceAgain__GameItemManager__
#define __OnceAgain__GameItemManager__

#include "cocos2d.h"
#include <string>
#include "Singleton.h"
#include "JsonHelper.h"
#include "cocos-ext.h"
#include "DataManager.h"
USING_NS_CC_EXT;
class CBasePacket;
enum eItemId {
    ItemTag_1 = 400001,         //疯狂开局
    ItemTag_2 = 400002,         //避免失误
    ItemTag_3 = 400003,         //时间延长
    ItemTag_4 = 400004,         //染色剂
    ItemTag_5 = 400005,         //连击延长2
    ItemTag_6 = 400006,         //十字爆
    ItemTag_7 = 400007,         //同色爆
    ItemTag_8 = 400008,         //连击延长1
    ItemTag_9 = 400009,         //简单排列
    ItemTag_10 = 400010,         //6种牌
    ItemTag_11 = 400011,         //时间延长（超级）
    ItemTag_12 = 400012,         //起始分数
    ItemTag_13 = 400013,         //满级强化
    ItemTag_14 = 400014,         //避免失误（超级）
    ItemTag_15 = 400015,         //疯狂复活1
    ItemTag_16 = 400016,         //疯狂复活2
    ItemTag_17 = 400017,         //超级简单
    ItemTag_18 = 400018,         //一击即中
    ItemTag_19 = 400019,         //快节奏
    ItemTag_20 = 400020,         //更容易,
};
enum eItemType
{
	eItemTypeCommon = 1,			//common item
	eItemTypeSuper,				//super item
	eItemTypeMax,
};
struct sItemData
{
	int ItemId;
    int ItemType;
	std::string ItemName;
    std::string ItemDetail;
    int ItemImg;
	int CurrencyId;
	int CurrencyValue;
};
struct SClientItemData
{
	SClientItemData():pData(NULL),fExtra1(0.f),fNum(0.f)
	{}
	sItemData* pData;
	float fExtra1;
	float fNum;
};
typedef std::vector<sItemData> VEC_ITEMSYSDATA;
typedef std::vector<SClientItemData> VEC_CLIENTITEMDATA;
typedef std::vector<SClientItemData> VEC_PACKAGEITEM;

class CItemMan :public ILoadTempData,public CSingleton<CItemMan>
{
public:
	CItemMan();
	~CItemMan();
public:
	VEC_ITEMSYSDATA& getMoneyChgTmpData(){return mVecItemSystemData;};
	//
	VEC_PACKAGEITEM& getPackageItem(){return mVecPackageItem;}
	//
	void addItem(SClientItemData& item);
	SClientItemData* getItem(int nItemId);
	//
	void releaseItem(int nItemId);
	//
	void clrItem();
	//
	VEC_CLIENTITEMDATA& getVecSuperItem(){return mVecSuperItem;};
	//
	void addSuperItem(sItemData& item);
	//
	void clrSuperItem();
	//
	SClientItemData* getSuperItem(int nItemId);
	//
	bool removeSuperItem(int nItemId);
	//
	int randSuperItem();
    //
	bool useItem(int nItemId,bool bForceUse = false );
	//
	void parseNetData(CBasePacket* pBasePacket);
	//
	sItemData* getChgTempData(int nId);
	//
	virtual void reset();
	// game on the inside reset
	virtual void resetInside();
    
	//////////////////////////////////////////////////////////////////////////
	//request network data
    void RequestBuyItem(int itemId);
    void RequestGetAllItem();                    //获取所有道具.
    void RequestGetItemInfoByGame(int gameId);   //根据游戏id获取道具.
	void RequestGetPackItem();
	//////////////////////////////////////////////////////////////////////////
	
public:
	//overload ILoadTemp Interface
	//updata template data
	virtual void updataTemplateData(const char* str);
protected:
	VEC_ITEMSYSDATA mVecItemSystemData;
	VEC_CLIENTITEMDATA mVecSuperItem;
	VEC_PACKAGEITEM mVecPackageItem;
	CC_SYNTHESIZE(int,mnGameOverBuyItemCounter,GameOverBuyItemCounter);
};
#endif /* defined(__OnceAgain__GameItemManager__) */
