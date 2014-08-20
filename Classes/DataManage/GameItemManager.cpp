//
//  GameItemManager.cpp
//  OnceAgain
//
//  Created by mac on 14-4-4.
//
//

#include "GameItemManager.h"
#include "NetPacket.h"
#include "NetHttpClient.h"
#include "GameInfoManager.h"
#include "PlayerInfoManager.h"
//#include "DBUtil.h"
#include "spine/extension.h"
#include "DataManager.h"
#include "RandomUtil.h"
#include "GameShare_Global.h"
#include "StringUtil.h"
#include "TaikoDefine.h"
#include "GameFruitDefine.h"
#include "RightTouchDefine.h"
CItemMan::CItemMan():mnGameOverBuyItemCounter(0)
{
    
}
CItemMan::~CItemMan()
{
    // this->flush();
}

void CItemMan::reset()
{
	
}
void CItemMan::resetInside()
{
	mnGameOverBuyItemCounter = 0;
	clrSuperItem();
}
void CItemMan::parseNetData(CBasePacket* pBasePacket)
{
	CResponsePacket* pPk = dynamic_cast<CResponsePacket*>(pBasePacket);
	unsigned int unMsgCode = pPk->getMsgCode();
//	CSJson::Value root = CJsonHelper::getJsonFromString(pPk->getContent().c_str());
    CSJson::Value root ;
	if(!CJsonHelper::getJsonFromString(pPk->getContent().c_str(),root))
		return ;
	switch (unMsgCode)
	{
        case eNetMsgItemSysGetAll:
		{
			updataTemplateData(pPk->getContent().c_str());
			CDataManager::GetInstance().wirteToFile(TempFileItemSysGetAll,pPk->getContent());
		}
        break;
        case eNetMsgItemSysBuy:{
            CSJson::Value& val = root[0];
			int nItemId = val["propsid"].asInt();
            sItemData* itemData = this->getChgTempData(nItemId);
            if (itemData) {
				if (itemData->ItemType == eItemTypeSuper)
				{
					addSuperItem(*itemData);
				}else
				{
					useItem(nItemId,true);
				}
				
                CPlayerInfoMan::sharedInstance().getPlayerInfo().nMoney -= itemData->CurrencyValue;
            }
        }
            break;
        case eNetMsgItemSysGetByGame:
        {
            for (int i=0; i<root.size(); i++) {
                CSJson::Value& val = root[i];
                sGameInfoData* data;
                int gameId = val["gameid"].asInt();
                int itemId = val["propsid"].asInt();
                data = CGameInfoMan::sharedInstance().getChgTempData(gameId);
                if (data) {
                    bool isNew = true;
                    for (int j=0; j<data->itemId.size(); j++) {
                        if (data->itemId[j] == itemId) {
                            isNew =false;
                        }
                    }
                    if (isNew) {
                        data->itemId.push_back(itemId);
                    }
                    
                }else
                {
                    sGameInfoData data;
                    data.gameId = gameId;
                    data.itemId.push_back(itemId);
                    CGameInfoMan::sharedInstance().getMoneyChgTmpData().push_back(data);
                }
            }
        }
            break;
		case eNetMsgItemSysGetPlayerPackage:
			{
				clrItem();
				for (int i=0; i < root.size(); i++) {
					CSJson::Value& val = root[i];
					SClientItemData Info;
					Info.fNum = val["propsnum"].asInt();
					Info.pData = this->getChgTempData(val["propsid"].asInt());
					addItem(Info);
				}
			}
			break;
        default:
            break;
            
	}
    
}
sItemData* CItemMan::getChgTempData(int nId)
{
	for (int i = 0; i < mVecItemSystemData.size(); ++i)
	{
		if(mVecItemSystemData[i].ItemId == nId)
		{
			return &mVecItemSystemData[i];
		}
	}
	return NULL;
}
void CItemMan::addItem(SClientItemData& item)
{
	mVecPackageItem.push_back(item);
}

SClientItemData* CItemMan::getItem(int nItemId)
{
	for (int i = 0; i < mVecPackageItem.size(); ++i)
	{
		if(nItemId == mVecPackageItem[i].pData->ItemId)
			return &mVecPackageItem[i];
	}
	return NULL;
}
void CItemMan::releaseItem(int nItemId)
{
	for (int i = 0; i < mVecPackageItem.size(); ++i)
	{
		if(nItemId == mVecPackageItem[i].pData->ItemId)
		{
			SClientItemData&  s = mVecPackageItem[i];
			s.fNum--;
			if (s.fNum <= 0)
			{
				mVecPackageItem.erase(mVecPackageItem.begin() + i);
			}
		}
			
	}
}
void CItemMan::clrItem()
{
	mVecPackageItem.clear();
}
void CItemMan::addSuperItem(sItemData& item)
{
	SClientItemData data;
	data.pData = &item;
	data.fExtra1 = 0.f;
	mVecSuperItem.push_back(data);
}
void CItemMan::clrSuperItem()
{
	mVecSuperItem.clear();
}
SClientItemData* CItemMan::getSuperItem(int nItemId)
{
	for (int i = 0; i < mVecSuperItem.size(); ++i)
	{
		if(nItemId == mVecSuperItem[i].pData->ItemId)
			return &mVecSuperItem[i];
	}
	return NULL;
}
bool CItemMan::removeSuperItem(int nItemId)
{
	for (int i = 0; i < mVecSuperItem.size(); ++i)
	{
		if(nItemId == mVecSuperItem[i].pData->ItemId){
			mVecSuperItem.erase(mVecSuperItem.begin() + i);
			return true;
		}
	}
	return false;
}
int CItemMan::randSuperItem()
{
	vector<int> vecRand;
	vecRand.push_back(ItemTag_11);
	vecRand.push_back(ItemTag_12);
	vecRand.push_back(ItemTag_13);
    if(GameShare_Global::shareGlobal()->gameType != Game_Fruit)
        vecRand.push_back(ItemTag_14);
	if(GameShare_Global::shareGlobal()->gameType == Game_Fruit)
		vecRand.push_back(ItemTag_17);
	int nIndex = CRandomUtil::RandomRange(0,vecRand.size()-1);
	return vecRand[nIndex];
}
bool CItemMan::useItem(int nItemId,bool bForceUse)
{
	sItemData* itemData = this->getChgTempData(nItemId);
	if(itemData == NULL)
		return false;
	if (itemData) {
		if (itemData->ItemType == eItemTypeSuper)
		{
			SClientItemData*  pSuperItem= getSuperItem(nItemId);
			if(pSuperItem == NULL)
				return false;
			if (pSuperItem){
				switch(nItemId){
				case ItemTag_15:{
								}
								break;
				case ItemTag_16:{
								}
								break;
				case ItemTag_11:{
					removeSuperItem(nItemId);
								}
								break;
				case ItemTag_12:{
					e_GameType eType = GameShare_Global::shareGlobal()->gameType;
					if (eType == Game_TaiKo){
						CTKData.setScore(500000);
					}else if (eType == Game_Fruit){
						CFrData.setScore(500000);
					}else if (eType == Game_Jelly){
						CRtData.setScore(500000);
					}
					removeSuperItem(nItemId);
								}
								break;
				case ItemTag_14:{
					pSuperItem->fExtra1 += 1;
					if(pSuperItem->fExtra1 >= 2){
						removeSuperItem(nItemId);
					}
								}
								break;
				case ItemTag_13:{
					sStrengthenLv*  pStreng = NULL;
					e_GameType eType = GameShare_Global::shareGlobal()->gameType;
					if (eType  == Game_TaiKo){
						pStreng = CStrengthenMan::sharedInstance().getLvInfoByLvAndId(StrengThenTag_14,30);
						if (pStreng){
							CTKData.setEffectStrengthenVal(eType,StrengThenTag_14,CStringUtil::ToDouble(pStreng->strengthenValue));
						}
						pStreng = CStrengthenMan::sharedInstance().getLvInfoByLvAndId(StrengThenTag_15,30);
						if (pStreng){
							CTKData.setEffectStrengthenVal(eType,StrengThenTag_15,CStringUtil::ToDouble(pStreng->strengthenValue));
						}
						pStreng = CStrengthenMan::sharedInstance().getLvInfoByLvAndId(StrengThenTag_16,30);
						if (pStreng){
							CTKData.setEffectStrengthenVal(eType,StrengThenTag_16,CStringUtil::ToDouble(pStreng->strengthenValue));
						}
						removeSuperItem(nItemId);
					}else if(eType  == Game_Jelly){
						pStreng = CStrengthenMan::sharedInstance().getLvInfoByLvAndId(StrengThenTag_3,30);
						if (pStreng){
							CRtData.setEffectStrengthenVal(eType,StrengThenTag_3,CStringUtil::ToDouble(pStreng->strengthenValue));

						}
						pStreng = CStrengthenMan::sharedInstance().getLvInfoByLvAndId(StrengThenTag_2,30);
						if (pStreng){
							CRtData.setEffectStrengthenVal(eType,StrengThenTag_2,CStringUtil::ToDouble(pStreng->strengthenValue));
						}
						pStreng = CStrengthenMan::sharedInstance().getLvInfoByLvAndId(StrengThenTag_4,30);
						if (pStreng){
							CRtData.setEffectStrengthenVal(eType,StrengThenTag_4,CStringUtil::ToDouble(pStreng->strengthenValue));
						}
						removeSuperItem(nItemId);
					}else if (eType == Game_Fruit){
						pStreng = CStrengthenMan::sharedInstance().getLvInfoByLvAndId(StrengThenTag_5,30);
						if (pStreng){
							CFrData.setEffectStrengthenVal(eType,StrengThenTag_5,CStringUtil::ToDouble(pStreng->strengthenValue));
						}
						pStreng = CStrengthenMan::sharedInstance().getLvInfoByLvAndId(StrengThenTag_6,30);
						if (pStreng){
							CFrData.setEffectStrengthenVal(eType,StrengThenTag_6,CStringUtil::ToDouble(pStreng->strengthenValue));
						}
						pStreng = CStrengthenMan::sharedInstance().getLvInfoByLvAndId(StrengThenTag_7,30);
						if (pStreng){
							CFrData.setEffectStrengthenVal(eType,StrengThenTag_7,CStringUtil::ToDouble(pStreng->strengthenValue));
						}
						removeSuperItem(nItemId);
					}
					}
					break;
				}
			}
		}else
		{
			SClientItemData*  pItem= getItem(nItemId);
			if(pItem == NULL && !bForceUse)
				return false;
			if (GameShare_Global::shareGlobal()->gameType == Game_Jelly){
				CRtData.addEffectByItemId(nItemId);
			}
			else if(GameShare_Global::shareGlobal()->gameType == Game_Fruit){
					CFrData.addEffectByItemId(nItemId);	
			}else if (GameShare_Global::shareGlobal()->gameType == Game_TaiKo){
					CTKData.addEffectByItemId(nItemId);	
			}
			releaseItem(nItemId);
		}
	}
	return true;
}

void CItemMan::RequestGetAllItem()
{
	if(CDataManager::GetInstance().readTemplateData(TempFileItemSysGetAll,this))
		return;
	NetHttpClient::sendHttpRequest(eNetMsgTypeItemSys, eNetMsgItemSysGetAll);
// 
// 	string fullDBPath = CCFileUtils::sharedFileUtils()->getWritablePath() + "game.db"; 
// 	DBUtil::initDB(fullDBPath.c_str());
// 	if(DBUtil::tableIsExist("tabItemSysGetAll"))
// 	{
// 		DBUtil::closeDB();
// 	}else
// 	{
// 		string createTableSql = "create table tabItemSysGetAll (propsid integer primary key autoincrement,propstype integer,propsname varchar[36],propsdetail varchar[256],propsimg integer,currencyid integer,currencyvalue integer);";  
// 		DBUtil::createTable(createTableSql.c_str(),"tabItemSysGetAll");
// 		DBUtil::closeDB();
// 		NetHttpClient::sendHttpRequest(eNetMsgTypeItemSys, eNetMsgItemSysGetAll);
// 	}
}
void CItemMan::updataTemplateData(const char* str)
{
	CSJson::Value root ;
	if(!CJsonHelper::getJsonFromString(str,root))
		return ;
	mVecItemSystemData.clear();
	for (int i = 0; i < root.size(); ++i){
		sItemData data;
		CSJson::Value& val = root[i];
		data.ItemId = val["propsid"].asInt();
		data.ItemType = val["propstype"].asInt();
		data.ItemName = val["propsname"].asCString();
		data.ItemDetail = val["propsdetail"].asCString();
		data.ItemImg = val["propsimg"].asInt();
		data.CurrencyId = val["currencyid"].asInt();
		data.CurrencyValue = val["currencyvalue"].asInt();
		mVecItemSystemData.push_back(data);
	}
}
void CItemMan::RequestGetItemInfoByGame(int gameId)
{
    CSJson::Value msg_body;
    msg_body["gameid"] = CSJson::Value(gameId);
    NetHttpClient::sendHttpRequest(eNetMsgTypeItemSys, eNetMsgItemSysGetByGame,&msg_body);
}
void CItemMan::RequestBuyItem(int itemId)
{
    CSJson::Value msg_body;
    msg_body["propsid"] = CSJson::Value(itemId);
    NetHttpClient::sendHttpRequest(eNetMsgTypeItemSys, eNetMsgItemSysBuy,&msg_body);
}
void CItemMan::RequestGetPackItem()
{
	//CSJson::Value msg_body;
	NetHttpClient::sendHttpRequest(eNetMsgTypeItemSys, eNetMsgItemSysGetPlayerPackage);
}