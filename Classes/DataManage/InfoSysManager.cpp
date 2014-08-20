//
//  InfoSysManager.cpp
//  OnceAgain
//
//  Created by mac on 14-4-28.
//
//

#include "InfoSysManager.h"
#include "NetPacket.h"
#include "NetHttpClient.h"
#include "GameShare_Msg.h"
#include "PkSysManager.h"
#include "GameShare_Global.h"
#include "PlayerInfoManager.h"
USING_NS_CC;
CInfoSysManager::CInfoSysManager()
{
    this->reset();
}

CInfoSysManager::~CInfoSysManager()
{
    
}
void CInfoSysManager::reset()
{
    
    mVecInfoSys.clear();
}

void CInfoSysManager::parseNetData(CBasePacket *pBasePacket)
{
    CResponsePacket* pPk = dynamic_cast<CResponsePacket*>(pBasePacket);
	unsigned int unMsgCode = pPk->getMsgCode();
    int nResCode = pPk->getResCode();
	CSJson::Value root ;
	if(!CJsonHelper::getJsonFromString(pPk->getContent().c_str(),root))
		return;
    
    switch (unMsgCode) {
        case eNetMsgGetAllInfo:
        {
            mVecInfoSys.clear();
            if (nResCode == 200) {
                for (int i=0; i < root.size(); ++i) {
                    CSJson::Value& val = root[i];
                    int size = val["size"].asInt();
                    CCLOG("%d",size);
                    for (int j=1; j <= size; ++j) {
                        CCString str;
                        str.initWithFormat("%d",j);
                        CSJson::Value valResult = val[str.getCString()];
                        sInfoSys data;
                        data.type = (eInfoType)val["noticetype"].asInt();
                        data.name = valResult["playername"].asCString();
                        data.avatarImg = valResult["playerimg"].asCString();
                        
                        if (data.type == InfoSendPkType || data.type == InfoRecPkType) {
                            data.gameType = valResult["gameid"].asInt();
                            data.infoId = valResult["pknoticeid"].asInt();
                        }else if(data.type == InfoRiceType){
                            data.infoId = valResult["powernoticeid"].asInt();
                        }
                        mVecInfoSys.push_back(data);
                    }
                }
                
            }
        }
            //发出消息.
            CCNotificationCenter::sharedNotificationCenter()->postNotification(kGetSysInfo, NULL);
            break;
        case eNetMsgGetRiceInfo:
            mVecInfoSys.clear();
            if (nResCode == 200) {
                for (int i = 0; i < root.size(); ++i)
                {
                    sInfoSys data;
                    CSJson::Value& val = root[i];
                    data.infoId = val["powernoticeid"].asInt();
                    data.type = InfoRiceType;
                    mVecInfoSys.push_back(data);
                }
            }
            //发出消息.
            CCNotificationCenter::sharedNotificationCenter()->postNotification(kGetSysInfo, NULL);
            break;
        case eNetMsgGetPkInfo:
        {
            VEC_SPKINFO& sendPk = CPkSysManager::sharedInstance().getSendPk();
            
            sendPk.clear();
            if (nResCode == 200) {

                
                for (int i = 0; i < root.size(); ++i) {
                    sPKInfo data;
                    CSJson::Value& val = root[i];
                    data.pkId = val["pknoticeid"].asInt();
                    data.score = val["sendplayerscore"].asInt();
                    data.avatarUrl = val["playerimg"].asCString();
                    data.pkName = val["playername"].asCString();
                    data.time = val["pknoticeexpiretime"].asInt();
                    if (val["gameid"].asInt() == GameShare_Global::shareGlobal()->gameType)
                    {
                        sendPk.push_back(data);
                    }
                }
            }
            
        }
            break;
    case eNetMsgGetBePkInfo:
        {
            VEC_SPKINFO& receivePk = CPkSysManager::sharedInstance().getReceivePk();
            receivePk.clear();
            if (nResCode == 200) {

                for (int i = 0; i < root.size(); ++i) {
                    sPKInfo data;
                    CSJson::Value& val = root[i];
                    data.pkId = val["pknoticeid"].asInt();
                    data.avatarUrl = val["playerimg"].asCString();
                    data.pkName = val["playername"].asCString();
                    data.time = val["pknoticeexpiretime"].asInt();
                    if (val["gameid"].asInt() == GameShare_Global::shareGlobal()->gameType)
                    {
                        receivePk.push_back(data);
                    }
                }

            }
                    }
            break;
        case eNetMsgReadInfo:
            break;
        case eNetMsgGetInfoNum:
        {
            CSJson::Value& val = root[0];
            CPlayerInfoMan::sharedInstance().getPlayerInfo().sysInfoNum = val["Amount"].asInt();
        }
            break;
        default:
            break;
    }
}

void CInfoSysManager::RequestGetPkInfo()
{
    CSJson::Value msg_body;
	NetHttpClient::sendHttpRequest(eNetMsgTypeMsgSys,eNetMsgGetPkInfo,&msg_body);
}
void CInfoSysManager::RequestGetBePkInfo()
{
    CSJson::Value msg_body;
	NetHttpClient::sendHttpRequest(eNetMsgTypeMsgSys,eNetMsgGetBePkInfo,&msg_body);
}
void CInfoSysManager::RequestReadPkInfo(int infoId)
{
    
}
void CInfoSysManager::RequestGetInfo()
{
    CSJson::Value msg_body;
	NetHttpClient::sendHttpRequest(eNetMsgTypeMsgSys,eNetMsgGetAllInfo,&msg_body);
}
void CInfoSysManager::RequestFriendListFromSql() {
    CSJson::Value msg_body;
    msg_body["playerid"] = CSJson::Value(CPlayerInfoMan::sharedInstance().getPlayerInfo().nId);
	NetHttpClient::sendHttpRequest(eNetMsgTypeFriendSys,eNetMsgFriendSysGetAll,&msg_body);
}
void CInfoSysManager::RequestGetRiceInfo()
{
    CSJson::Value msg_body;
	NetHttpClient::sendHttpRequest(eNetMsgTypeMsgSys,eNetMsgGetRiceInfo,&msg_body);
}

void CInfoSysManager::RequestReadRiceInfo(int infoId)
{
    CSJson::Value msg_body;
	msg_body["systemnoticeid"] = CSJson::Value(infoId);
	NetHttpClient::sendHttpRequest(eNetMsgTypeMsgSys,eNetMsgReadRiceInfo,&msg_body);
}
void CInfoSysManager::RequestGetInfoNum()
{
	NetHttpClient::sendHttpRequest(eNetMsgTypeMsgSys,eNetMsgGetInfoNum,NULL);
}