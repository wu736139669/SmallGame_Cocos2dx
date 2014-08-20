/***************************************************************
* 
*
*  作者：   王少培
*  文件名：   
*  创建时间： 2014-3-20
*
***************************************************************/
#include "NetHttpClient.h"
#include "NetHookManager.h"
#include "GameShare_NetSystem.h"
#include "NetFactory.h"
#include "NetPacket.h"
#include "MsgDefine.h"
#include "PlayerInfoManager.h"
#include "DialogManager.h"
#include "CsvStringData.h"
#include "XQDate.h"
#include "GameLayerLoading.h"
#include "DataManager.h"

NetHttpClient::NetHttpClient() 
{
    isXQ = false;
}

NetHttpClient::~NetHttpClient()
{
}

NetHttpClient& NetHttpClient::sharedInstance()
{
    static NetHttpClient gNetHttpClient;
    return gNetHttpClient;
}
bool NetHttpClient::sendHttpRequest(unsigned int unMsgType,unsigned int unMsgCode,CSJson::Value* msgBady,int nPlayerId)
{
	//是否游客登入
// 	if (CPlayerInfoMan::sharedInstance().getLoinStatus())
// 		return false;
	CCString strUrl = URL_REQUEST;
#ifdef GAME_TEST
	strUrl = URL_REQUEST_TEST;
#endif 
	//if(strcmp(GET_STRING_CSV(999999997),"1") == 0)
	CCTransitionScene* pScene = dynamic_cast<CCTransitionScene*>(CCDirector::sharedDirector()->getRunningScene());
	if(pScene == NULL)
		ShowDlg(CGameLayerLoading,CCDirector::sharedDirector()->getRunningScene(),10000);
	if(msgBady)
	{
		CSJson::Value& body = (*msgBady);
		if(nPlayerId == -1)
			nPlayerId = (CPlayerInfoMan::sharedInstance().getPlayerInfo().nId);
		body["playerid"] = CSJson::Value(nPlayerId);
		return sendHttpRequest(new CRequestPacket(unMsgType,unMsgCode,*msgBady),strUrl.getCString());
	}
	else
	{
		CSJson::Value tempNull;
		if(nPlayerId == -1)
			nPlayerId = (CPlayerInfoMan::sharedInstance().getPlayerInfo().nId);
		tempNull["playerid"] = CSJson::Value(nPlayerId);
		return sendHttpRequest(new CRequestPacket(unMsgType,unMsgCode,tempNull),strUrl.getCString());
	}
		
}
// bool NetHttpClient::sendHttpRequest(unsigned int unMsgType,unsigned int unMsgCode)
// {
// 	return sendHttpRequest(new CRequestPacket(unMsgType,unMsgCode));
// }
bool NetHttpClient::sendHttpRequest(CBasePacket* pPacket,const char* lpszUrl, const char* lpszHttpVerb)
{
    //m_HttpResponse.clear();
	CHttpInfo* pHttpInfo =  CNetFactory::sharedInstance()->createHttpInfo(&NetHttpClient::sharedInstance());
    if (0 == strcmp(lpszHttpVerb, "GET"))
    {
        //m_strUrl = lpszUrl;
        //std::string str = GameShare_NetSystem::ShareNetSystem()->NetSystem_HTTPRequest(lpszUrl);
		//NetHttpClient::sharedInstance().onDataComplete((void*)str.c_str());
		pHttpInfo->setUrl(lpszUrl);
		
	}else if (0 == strcmp(lpszHttpVerb, "POST")) 
	{
		pHttpInfo->setUrl(lpszUrl);
		pHttpInfo->setPacket(pPacket);
	}
    
	CCLOG("[NetHttpClient::sendHttpRequest]:%s", pHttpInfo->getPacket()->getContent().c_str());
	CNetFactory::sharedInstance()->addToPool(pHttpInfo);
    return true;
}

void NetHttpClient::onConnect(CHttpInfo* pHttpInfo)
{
    CCLog("[NetHttpClient::OnConnect]:%s", m_strUrl.c_str());
}

void NetHttpClient::onConnectFailed(CHttpInfo* pHttpInfo)
{
    CCLog("[NetHttpClient::OnConnectFailed]");
}

bool NetHttpClient::onConnectRetry(CHttpInfo* pHttpInfo)
{
    CCLog("[NetHttpClient::OnConnectRetry]");

    return true;
}

void NetHttpClient::onDisconnect(CHttpInfo* pHttpInfo)
{
    CCLog("[NetHttpClient::OnDisconnect]");
}

void NetHttpClient::onConnectTimeout(CHttpInfo* pHttpInfo)
{
    CCLog("[NetHttpClient::OnConnectTimeout]");
}

void NetHttpClient::onData(CHttpInfo* pHttpInfo)
{
   
}

void NetHttpClient::onReconnect(CHttpInfo* pHttpInfo)
{
    CCLog("[NetHttpClient::OnReconnect]");
}

void NetHttpClient::onDataComplete(CHttpInfo* pHttpInfo)
{
    
}

void NetHttpClient::onWriteComplete(CHttpInfo* pHttpInfo)
{
#ifdef _WIN32
	if(pHttpInfo->getReceData().size() < 1024*16)
#endif
    CCLOG("[NetHttpClient::onWriteComplete]:%s", pHttpInfo->getReceData().c_str());
	CDataManager::GetInstance().accTotalFlow(pHttpInfo->getReceData().size());
	CResponsePacket* pResPacket = new CResponsePacket(pHttpInfo->getPacket()->getMsgType(),pHttpInfo->getPacket()->getMsgCode(),pHttpInfo->getReceData().c_str(),eNetMsgDataStateComplete);
	
	dispatchNetPackage((void*)pResPacket);
	//释放
	if(pResPacket)
	{
		delete pResPacket;
		pResPacket = NULL;
	}
	if(CNetFactory::sharedInstance()->getNetInfoListAmount() == 0)
		ReleaseDlg(CGameLayerLoading);
}

void NetHttpClient::onTimeout(CHttpInfo* pHttpInfo)
{
	CCLOG("[NetHttpClient::onTimeout]:%s", pHttpInfo->getReceData().c_str());

	CResponsePacket* pResPacket = new CResponsePacket(pHttpInfo->getPacket()->getMsgType(),pHttpInfo->getPacket()->getMsgCode(),pHttpInfo->getReceData().c_str(),eNetMsgDataStateTimeOut);
	dispatchNetPackage((void*)pResPacket);
	//释放
	if(pResPacket)
	{
		delete pResPacket;
		pResPacket = NULL;
	}
		ReleaseDlg(CGameLayerLoading);
}
void NetHttpClient::dispatchNetPackage(void *pDataPkg)
{
    
    CNetHookManager::sharedNetHookManager()->onPackageFilter(pDataPkg);
    
    CResponsePacket* pPkt = (CResponsePacket*)pDataPkg;
    unsigned int unMsgType = pPkt->getMsgType();
    unsigned int unMsgCode = pPkt->getMsgCode();
	if (isXQ && unMsgType_xq == unMsgType && unMsgCode_xq == unMsgCode) {
		XQDate::sharedInstance().SaveDate(pDataPkg, target, callback);
		isXQ = false;
		//        NetCallBack::doCallBack();
	}
    CDialogManager::onPackageFilter(pDataPkg);
}

////////////////////////////////////////////////
void NetHttpClient::XQsendHttpRequest(unsigned int unMsgType,unsigned int unMsgCode,CSJson::Value* msgBady,CCObject* target1, SEL_MyEvent callfun){
    isXQ = true;
//    NetCallBack::setCallBack(target1, callfun);
    target = target1;
    callback = callfun;
    unMsgCode_xq = unMsgCode;
    unMsgType_xq = unMsgType;
    if(msgBady->isMember("playerid"))
        sendHttpRequest(unMsgType, unMsgCode, msgBady,(*msgBady)["playerid"].asInt());
    else
        sendHttpRequest(unMsgType, unMsgCode, msgBady);
  
}