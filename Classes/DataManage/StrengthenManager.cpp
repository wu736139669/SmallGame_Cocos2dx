//
//  StrengthenManager.cpp
//  OnceAgain
//
//  Created by mac on 14-4-8.
//
//

#include "StrengthenManager.h"
#include "NetPacket.h"
#include "NetHttpClient.h"
#include "PlayerInfoManager.h"
#include "GameInfoManager.h"
#include "ComData.h"
USING_NS_CC;

CStrengthenMan::CStrengthenMan()
{
    
}
CStrengthenMan::~CStrengthenMan()
{
    // this->flush();
}

void CStrengthenMan::reset()
{
	
}
void CStrengthenMan::updataTemplateData(const char* str)
{
	CSJson::Value root ;
	if(!CJsonHelper::getJsonFromString(str,root))
		return;
	mVecStrengthenData.clear();
	for (int i = 0; i < root.size(); ++i)
	{
		sStrengthen data;
		CSJson::Value& val = root[i];
		data.strengthenId = val["strengthenid"].asInt();
		data.strengthenName = val["strengthenname"].asCString();
		data.strengthenDetail = val["strengthendetail"].asString();
		data.strengthenImg = val["strengthenimg"].asInt();
		data.strengthenMaxLv = val["strengthenmaxlevel"].asInt();
		mVecStrengthenData.push_back(data);
	}
	this->RequestGetAllLvInfo();
}
void CStrengthenMan::parseNetData(CBasePacket* pBasePacket)
{
	CResponsePacket* pPk = dynamic_cast<CResponsePacket*>(pBasePacket);
	unsigned int unMsgCode = pPk->getMsgCode();
	CSJson::Value root ;
	if(!CJsonHelper::getJsonFromString(pPk->getContent().c_str(),root))
		return;
	switch (unMsgCode)
	{
        case eNetMsgCodeIntensifySysGetAllInfo:
		{
			updataTemplateData(pPk->getContent().c_str());
			CDataManager::GetInstance().wirteToFile(TempFileIntensifySysAllInfo,pPk->getContent());

		}
            break;
        case eNetMsgCodeIntensifySysGetAllLvInfo:
        {
            for (int i=0; i < root.size(); ++i) {
                sStrengthenLv data;
                CSJson::Value& val = root[i];
                data.strengthenLv = val["strengthenlevel"].asInt();
                data.strengthenValue = val["strengthenvalue"].asCString();
                data.currencyId = val["currencyid"].asInt();
                data.currencyValue = val["currencyvalue"].asInt();
                int strengthenId = val["strengthenid"].asInt();
                sStrengthen* tempData = this->getChgTempData(strengthenId);
                if (tempData) {
                    tempData->lvInfo.push_back(data);
                }
            }
        }
            break;
        case eNetMsgCodeIntensifySysGetGameInfo:
        {
            for (int i=0; i < root.size(); ++i) {
                CSJson::Value& val = root[i];
                int gameId = val["gameid"].asInt();
                int strengthenId = val["strengthenid"].asInt();
                int level = 0;
                
                sGameInfoData* data;
                data = CGameInfoMan::sharedInstance().getChgTempData(gameId);
                if (data) {
                    data->strengthenId.push_back(strengthenId);
                }else
                {
                    sGameInfoData tData;
                    tData.gameId = gameId;
                    tData.strengthenId.push_back(strengthenId);
                    CGameInfoMan::sharedInstance().getMoneyChgTmpData().push_back(tData);
                }
                //玩家信息也加入.
                 VEC_MSTRENGTHEN& playData = CPlayerInfoMan::sharedInstance().getPlayerInfo().mStrengthen;
                
                
                    //
                    bool isNew = true;
                    for (int j=0; j<playData.size(); j++) {
                        if (gameId == playData[j].gameId) {
                            isNew = false;
                        }
                    }
                    if (isNew) {
                        sMStrengthen gameData;
                        gameData.gameId = gameId;
                        sMStrengInfo tData;
                        tData.strengthenId = strengthenId;
                        tData.strengtheLv = level;
                        gameData.mGameStrengthen.push_back(tData);
                        playData.push_back(gameData);
                    }

               
                for (int j=0; j<playData.size(); j++) {
                    if (gameId == playData[j].gameId) {
                        if (playData[j].mGameStrengthen.size() > i) {
                            playData[j].mGameStrengthen[i].strengthenId = strengthenId;
                            playData[j].mGameStrengthen[i].strengtheLv = level;
                        }else
                        {
                            
                            sMStrengInfo tData;
                            tData.strengthenId = strengthenId;
                            tData.strengtheLv = level;
                            playData[j].mGameStrengthen.push_back(tData);
                        }
                    }
                }
            }
            
            
        }
            break;
        case eNetMsgCodeIntensifySysGetPlayGameInfo:
        {
            
            for (int i=0; i<root.size(); i++) {
                CSJson::Value& val = root[i];
                int gameId = val["gameid"].asInt();
                int strengthenId = val["strengthenid"].asInt();
                int level = val["level"].asInt();
                //玩家信息也加入.
                VEC_MSTRENGTHEN& playData = CPlayerInfoMan::sharedInstance().getPlayerInfo().mStrengthen;
                if (playData.size() <=0) {
                    sMStrengthen gameData;
                    gameData.gameId = gameId;
                    sMStrengInfo tData;
                    tData.strengthenId = strengthenId;
                    tData.strengtheLv = level;
                    gameData.mGameStrengthen.push_back(tData);
                    playData.push_back(gameData);
                    continue;
                }
                for (int j=0; j<playData.size(); j++) {
                    if (gameId == playData[j].gameId) {
                        if (playData[j].mGameStrengthen.size() > i) {
                            for (int k=0; k<playData[j].mGameStrengthen.size(); k++) {
                                if (strengthenId == playData[j].mGameStrengthen[k].strengthenId) {
                                    playData[j].mGameStrengthen[k].strengthenId = strengthenId;
                                    playData[j].mGameStrengthen[k].strengtheLv = level;
                                }
                            }
                        }else{
                            sMStrengInfo tData;
                            tData.strengthenId = strengthenId;
                            tData.strengtheLv = level;
                            playData[j].mGameStrengthen.push_back(tData);
                        }
                    }
                }
                
            }
            
        }
            break;
        case eNetMsgCodeIntensifySysLvUp:
        {
            CSJson::Value& val = root[0];
            int gameId = val["gameid"].asInt();
            int strengthenId = val["strengthenid"].asInt();
            CPlayerInfoMan::sharedInstance().getPlayerInfo().nMoney = val["playermoney"].asInt();
            VEC_MSTRENGTHEN& data = CPlayerInfoMan::sharedInstance().getPlayerInfo().mStrengthen;
            if (data.size() <= 0) {
                sMStrengthen tData;
                tData.gameId = gameId;
                sMStrengInfo tGameData;
                tGameData.strengtheLv = 1;
                tGameData.strengthenId = strengthenId;
                tData.mGameStrengthen.push_back(tGameData);
                data.push_back(tData);
            }
            for (int j=0; j<data.size(); j++) {
                if (gameId == data[j].gameId) {
                    bool isNew = true;
                    for (int i=0; i<data[j].mGameStrengthen.size(); i++) {
                        if (data[j].mGameStrengthen[i].strengthenId == strengthenId) {
                            data[j].mGameStrengthen[i].strengtheLv++;
                            isNew = false;
                            break;
                        }
                    }
                    if (isNew) {
                        sMStrengInfo tData;
                        tData.strengthenId = strengthenId;
                        tData.strengtheLv = 1;
                        data[j].mGameStrengthen.push_back(tData);
                    }
                    break;
                }
            }
            
        }
            break;
        default:
            break;
            
	}
    
}

sStrengthen* CStrengthenMan::getChgTempData(int nId)
{
	for (int i = 0; i < mVecStrengthenData.size(); ++i)
	{
		if(mVecStrengthenData[i].strengthenId == nId)
		{
			return &mVecStrengthenData[i];
		}
	}
	return NULL;
}
sStrengthenLv* CStrengthenMan::getLvInfo(int lv, VEC_STRENGTHENLV& lvInfo)
{
    for (int i = 0; i < lvInfo.size(); ++i)
    {
        if (lvInfo[i].strengthenLv == lv)
        {
            return &lvInfo[i];
        }
    }
    return NULL;
}
sStrengthenLv* CStrengthenMan::getLvInfoByLvAndId(int strengId,int lv)
{
	sStrengthen* strengThen = CStrengthenMan::sharedInstance().getChgTempData(strengId);
	if(strengThen == NULL)
		return NULL;
	lv = lv > strengThen->strengthenMaxLv ? strengThen->strengthenMaxLv : lv;
	sStrengthenLv* lvInfo = CStrengthenMan::sharedInstance().getLvInfo(lv, strengThen->lvInfo);
	if(lvInfo == NULL)
		return NULL;
	return lvInfo;
}
void CStrengthenMan::RequestGetAllStrength()
{
	if (CDataManager::GetInstance().readTemplateData(TempFileIntensifySysAllInfo,this))
		return;
    CSJson::Value msg_body;
	NetHttpClient::sendHttpRequest(eNetMsgTypeIntensifySys,eNetMsgCodeIntensifySysGetAllInfo,&msg_body);
}
void CStrengthenMan::RequestGetAllLvInfo()
{
    CSJson::Value msg_body;
	NetHttpClient::sendHttpRequest(eNetMsgTypeIntensifySys,eNetMsgCodeIntensifySysGetAllLvInfo,&msg_body);
}
void CStrengthenMan::RequestGetInfoByGameId(int gameId)
{
    CSJson::Value msg_body;
	msg_body["gameid"] = CSJson::Value(gameId);
	NetHttpClient::sendHttpRequest(eNetMsgTypeIntensifySys,eNetMsgCodeIntensifySysGetGameInfo,&msg_body);
}
void CStrengthenMan::RequestGetPlayInfoByGameId(int gameId)
{
    CSJson::Value msg_body;
	msg_body["gameid"] = CSJson::Value(gameId);
	NetHttpClient::sendHttpRequest(eNetMsgTypeIntensifySys,eNetMsgCodeIntensifySysGetPlayGameInfo,&msg_body);
}
void CStrengthenMan::RequestStrengthenLvUp(int strengthenId, int gameId)
{
    CSJson::Value msg_body;
	msg_body["gameid"] = CSJson::Value(gameId);
    msg_body["strengthenid"] = CSJson::Value(strengthenId);
	NetHttpClient::sendHttpRequest(eNetMsgTypeIntensifySys,eNetMsgCodeIntensifySysLvUp,&msg_body);
}