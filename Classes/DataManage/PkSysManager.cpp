//
//  PkSysManager.cpp
//  OnceAgain
//
//  Created by mac on 14-4-28.
//
//

#include "PkSysManager.h"
#include "NetPacket.h"
#include "NetHttpClient.h"
#include "GameShare_Msg.h"
#include "PlayerInfoManager.h"

CPkSysManager::CPkSysManager()
{
    this->reset();
}
CPkSysManager::~CPkSysManager()
{
    
}
void CPkSysManager::reset()
{
    mVecReceivePk.clear();
    mVecSendPk.clear();
    pkType = PkTypeNormal;
    pkId = -1;
    playerId = -1;
    playerName = "";
    playerScore = 0;
    playerUrl = "";
    myScore = 0;
}

void CPkSysManager::parseNetData(CBasePacket *pBasePacket)
{
    CResponsePacket* pPk = dynamic_cast<CResponsePacket*>(pBasePacket);
	unsigned int unMsgCode = pPk->getMsgCode();
	CSJson::Value root ;
	if(!CJsonHelper::getJsonFromString(pPk->getContent().c_str(),root))
		return;
    switch (unMsgCode) {
        case eNetMsgSendPk:
        {
            CSJson::Value& val = root[0];
            myScore = val["sendplayerscore"].asInt();
        }
            break;
        case eNetMsgReceivePk:
        {
            CSJson::Value& val = root[0];
            playerUrl = val["playerimg"].asCString();
            playerName = val["playername"].asCString();
            playerScore = val["sendplayerscore"].asInt();
            myScore = val["recvplayerscore"].asInt();
			iGold = val["money"].asInt();
		}
            break;
        default:
            break;
    }
}

void CPkSysManager::RequestSendPk(int receiveId, int gameId, int score)
{
    CSJson::Value msg_body;
    msg_body["sendplayerid"] = CSJson::Value(CPlayerInfoMan::sharedInstance().getPlayerInfo().nId);
    msg_body["recvplayerid"] = CSJson::Value(receiveId);
    msg_body["sendplayerscore"] = CSJson::Value(score);
    msg_body["gameid"] = CSJson::Value(gameId);
	NetHttpClient::sendHttpRequest(eNetMsgTypePk,eNetMsgSendPk,&msg_body);
}

void CPkSysManager::RequestReceivePk(int infoId, int score)
{
    CSJson::Value msg_body;
	msg_body["pknoticeid"] = CSJson::Value(infoId);
    msg_body["recvplayerscore"] = CSJson::Value(score);
    msg_body["recvplayerid"] = CSJson::Value(CPlayerInfoMan::sharedInstance().getPlayerInfo().nId);
	NetHttpClient::sendHttpRequest(eNetMsgTypePk,eNetMsgReceivePk,&msg_body);
}
