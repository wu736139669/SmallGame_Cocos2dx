//
//  GameInfoManager.cpp
//  OnceAgain
//
//  Created by mac on 14-4-4.
//
//

#include "GameInfoManager.h"

#include "NetPacket.h"
#include "NetHttpClient.h"
#include "PlayerInfoManager.h"
#include "GameShare_Msg.h"
#include "GameShare_Global.h"
USING_NS_CC;

CGameInfoMan::CGameInfoMan()
{
    mVecGameInfoData.clear();
}
CGameInfoMan::~CGameInfoMan()
{
    // this->flush();
}

void CGameInfoMan::reset()
{
	
}

void CGameInfoMan::parseNetData(CBasePacket* pBasePacket)
{
	CResponsePacket* pPk = dynamic_cast<CResponsePacket*>(pBasePacket);
	unsigned int unMsgCode = pPk->getMsgCode();
	CSJson::Value root ;
	if(!CJsonHelper::getJsonFromString(pPk->getContent().c_str(),root))
		return;
    switch (unMsgCode) {
        case eNetMsgGameSysSetMax:
        {
            bool isNew = true;
            CSJson::Value val = root[0];
            int tempId = val["gameid"].asInt();
            SPlayerInfo& mPlayerInfo = CPlayerInfoMan::sharedInstance().getPlayerInfo();
            sGameProperty& gameProperty = GameShare_Global::shareGlobal()->gameProperty;
       
            int maxScore = val["totolscore"].asInt();
			gameProperty.historyscore = val["historyscore"].asInt();
            gameProperty.highestscore = val["highestscore"].asInt();
            gameProperty.totolscore = val["totolscore"].asInt();
            gameProperty.playermoney = val["playermoney"].asInt();
            gameProperty.playerexp = val["playerexp"].asFloat()*100;
            gameProperty.levelrewardvalue = val["levelrewardvalue"].asInt();
            gameProperty.playerlevel = val["playerlevel"].asInt();
            gameProperty.levelrewardtype = val["levelrewardtype"].asInt();
            gameProperty.leveladdscore = val["leveladdscore"].asFloat();
            gameProperty.addexp = val["addexp"].asInt();
            gameProperty.addmoney = val["addmoney"].asInt();
            gameProperty.prescore = val["score"].asInt();
            mPlayerInfo.nMoney = gameProperty.playermoney;
            mPlayerInfo.nExp = gameProperty.playerexp;
            
            if (mPlayerInfo.nLevel < gameProperty.playerlevel) {
                
            }
            
            for (int i = 0; i < mPlayerInfo.mGameData.size(); ++i)
            {
                if(mPlayerInfo.mGameData[i].gameId == tempId)
                {
                    if(mPlayerInfo.mGameData[i].highestScore < maxScore){
                        mPlayerInfo.mGameData[i].highestScore = val["totolscore"].asInt();
                    }
                    isNew = false;
                    break;
                }
                
            }
            
            if (isNew) {
                s_GameData data;
                data.gameId = tempId;
                data.highestScore = val["score"].asInt();
                mPlayerInfo.mGameData.push_back(data);
            }
			//发出消息.
			CCNotificationCenter::sharedNotificationCenter()->postNotification(kSetScore, NULL);
      }
    break;
        case eNetMsgGameSysGetMax:
        {
            bool isNew = true;
            CSJson::Value val = root[0];
            int tempId = val["gameid"].asInt();
            SPlayerInfo& mPlayerInfo = CPlayerInfoMan::sharedInstance().getPlayerInfo();
            for (int i = 0; i < mPlayerInfo.mGameData.size(); ++i)
            {
                if(mPlayerInfo.mGameData[i].gameId == tempId)
                {
                    mPlayerInfo.mGameData[i].highestScore = val["highestscore"].asInt();
                    isNew = false;
                    break;
                }
                
            }
            if (isNew) {
                s_GameData data;
                data.gameId = tempId;
                data.highestScore = val["highestscore"].asInt();
                mPlayerInfo.mGameData.push_back(data);
            }
        }
            break;
        case eNetMsgGameSysGetGameInfo:
        {
			updataTemplateData(root);
            CDataManager::GetInstance().wirteToFile(TempFileGameInfo,pPk->getContent());
        }
            break;
        default:
            break;
    }
}

void CGameInfoMan::updataTemplateData(CSJson::Value& root)
{
	for (int i = 0; i < root.size(); ++i) {
		CSJson::Value val = root[i];
		int gameId = val["gameid"].asInt();
		std::string gameName = val["gamename"].asCString();
		sGameInfoData* data;
		data = this->getChgTempData(gameId);
		if (data) {
			data->gameName = gameName;
		}else
		{
			sGameInfoData tData;
			tData.gameId = gameId;
			tData.gameName = gameName;
			mVecGameInfoData.push_back(tData);
		}
	}
}
void CGameInfoMan::updataTemplateData(const char* str)
{
	CSJson::Value root ;
	if(!CJsonHelper::getJsonFromString(str,root))
		return;
	updataTemplateData(root);
}
sGameInfoData* CGameInfoMan::getChgTempData(int nId)
{
	for (int i = 0; i < mVecGameInfoData.size(); ++i)
	{
		if(mVecGameInfoData[i].gameId == nId)
		{
			return &mVecGameInfoData[i];
		}
	}
	return NULL;
}
sItemData* CGameInfoMan::getItemDate(int gameid, int itemTag)
{
    for (int i = 0; i < mVecGameInfoData.size(); ++i)
	{
		if(mVecGameInfoData[i].gameId == gameid)
		{
			if (mVecGameInfoData[i].itemId.size() > itemTag) {
                return CItemMan::sharedInstance().getChgTempData(mVecGameInfoData[i].itemId[itemTag]);
            }
		}
	}
    return NULL;
}
void CGameInfoMan::RequestSetGameMaxScore(int gameType, int maxScore)
{
    CSJson::Value msg_body;
	msg_body["gameid"] = CSJson::Value(gameType);
    msg_body["score"] = CSJson::Value(maxScore);
	NetHttpClient::sendHttpRequest(eNetMsgTypeGameSys,eNetMsgGameSysSetMax,&msg_body);
}
void CGameInfoMan::RequestgetGameMaxScore(int gameType)
{
    CSJson::Value msg_body;
	msg_body["gameid"] = CSJson::Value(gameType);
	NetHttpClient::sendHttpRequest(eNetMsgTypeGameSys,eNetMsgGameSysGetMax,&msg_body);
}
void CGameInfoMan::RequestgetGameInfo()
{
	if (CDataManager::GetInstance().readTemplateData(TempFileGameInfo,this))
		return;
    CSJson::Value msg_body;
    NetHttpClient::sendHttpRequest(eNetMsgTypeGameSys,eNetMsgGameSysGetGameInfo,&msg_body);
}