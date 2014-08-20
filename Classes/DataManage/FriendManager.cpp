//
//  FirendManager.cpp
//  OnceAgain
//
//  Created by mac on 14-4-23.
//
//

#include "FriendManager.h"
#include "NetPacket.h"
#include "NetHttpClient.h"
#include "GameShare_Msg.h"
#include "PlayerInfoManager.h"
USING_NS_CC;
CFriendManager::CFriendManager()
{
    
}

CFriendManager::~CFriendManager()
{
    
}
void CFriendManager::reset()
{
    mVecGameRank.clear();
    mVecGameRank.clear();
    mVecFriend.clear();
}
void CFriendManager::parseNetData(CBasePacket *pBasePacket)
{
    CResponsePacket* pPk = dynamic_cast<CResponsePacket*>(pBasePacket);
	unsigned int unMsgCode = pPk->getMsgCode();
	CSJson::Value root ;
	if(!CJsonHelper::getJsonFromString(pPk->getContent().c_str(),root))
		return;
    switch (unMsgCode) {
        case eNetMsgFriendSysGetAll:
            mVecFriendFromSql.clear();
            for (int i = 0; i < root.size(); i++) {
                sGameRank data;
                CSJson::Value& val = root[i];
                data.avatarUrl = val["appimg"].asString();
				data.name = val["appname"].asString();
				data.playerId = val["playerid"].asInt();
                data.appid = val["appid"].asString();
                data.appType = val["apptype"].asInt();
                data.powernoticeexpiretime = val["inviteexpiretime"].asInt();
                mVecFriendFromSql.push_back(data);
            }
            //发出消息.
           // CCNotificationCenter::sharedNotificationCenter()->postNotification(kGetFriendInfoList, NULL);
            break;
        case eNetMsgFriendSysSetFriend:
            
            break;
        case eNetMsgFriendSysGetRankByGame:
            mVecGameRank.clear();
            for (int i = 0; i < root.size(); ++i)
			{
				sGameRank data;
				CSJson::Value& val = root[i];
				data.avatarUrl = val["playerimg"].asString();
				data.score = val["highestscore"].asInt();
				data.name = val["playername"].asString();
                data.canPk = val["iscanpk"].asBool();
				data.playerId = val["playerid"].asInt();
				mVecGameRank.push_back(data);
			}
            break;
            case eNetMsgFriendSysGetTotal:
            mVecAllRank.clear();
            for (int i = 0; i < root.size(); ++i)
			{
				sGameRank data;
				CSJson::Value& val = root[i];
				data.avatarUrl = val["playerimg"].asString();
				data.score = val["playertotalscore"].asInt();
				data.name = val["playername"].asString();
				data.playerId = val["playerid"].asInt();
                data.powernoticeexpiretime = val["powernoticeexpiretime"].asInt();
                data.playercanrecvpower = val["playercanrecvpower"].asInt();
				mVecAllRank.push_back(data);
			}
            //发出消息.
            CCNotificationCenter::sharedNotificationCenter()->postNotification(kGetAllScoreRank, NULL);
            break;
            case eNetMsgFriendSysSendInvite:
            for (int i = 0; i < root.size(); ++i) {
                CSJson::Value &val = root[i];
                CPlayerInfoMan::sharedInstance().getPlayerInfo().nPower = val["playerpower"].asInt();
            }
            break;
        default:
            break;
    }
}
void CFriendManager::RequestSetFriend(int apptype, const char* userList)
{
    CSJson::Value msg_body;
	msg_body["apptype"] = CSJson::Value(apptype);
    msg_body["appresult"] = CSJson::Value(userList);
	NetHttpClient::sendHttpRequest(eNetMsgTypeFriendSys,eNetMsgFriendSysSetFriend,&msg_body);
}
void CFriendManager::RequestGetRankByGame(int gameId)
{
    CSJson::Value msg_body;
	msg_body["gameid"] = CSJson::Value(gameId);
	NetHttpClient::sendHttpRequest(eNetMsgTypeFriendSys,eNetMsgFriendSysGetRankByGame,&msg_body);
}
void CFriendManager::RequestGetAllRank()
{
	NetHttpClient::sendHttpRequest(eNetMsgTypeFriendSys,eNetMsgFriendSysGetTotal,NULL);
}
sGameRank* CFriendManager::getInfoById(int playerId)
{
    sGameRank* gameRank = NULL;
    for (int i=0; i<mVecGameRank.size(); ++i) {
        if (mVecGameRank[i].playerId == playerId) {
            gameRank = &mVecGameRank[i];
            return gameRank;
        }
    }
    return gameRank;
}