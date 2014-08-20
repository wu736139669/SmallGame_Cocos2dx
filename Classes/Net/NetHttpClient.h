/***************************************************************
*  
*
*  作者：     王少培
*  文件：     NetHttpClient.h
*  创建时间:  
*
****************************************************************/

#ifndef _NET_HTTP_CLIENT_H
#define _NET_HTTP_CLIENT_H

#include <string>
#include "cocos2d.h"
#include "NetEvnet.h"
#include "JsonHelper.h"
#include "NetCallBack.h"

USING_NS_CC;
USING_NS_CC_EXT;
//http://61.154.127.135/onceagain
//#define  GAME_TEST
//#define URL_REQUEST "tzdr.appserver.once-again.cn/onceagain"
#define URL_REQUEST "61.154.127.135/onceagain"
//#define URL_REQUEST_TEST "http://220.160.111.22:8801/onceagain"
#define URL_REQUEST_TEST "http://192.168.0.218/onceagain"
class CHttpInfo;
class CBasePacket;
class NetHttpClient : public INetEvent, public NetCallBack
{
public:
    NetHttpClient();
    ~NetHttpClient();

    static NetHttpClient& sharedInstance();

	//static bool sendHttpRequest(unsigned int unMsgType,unsigned int unMsgCode);
	static bool sendHttpRequest(unsigned int unMsgType,unsigned int unMsgCode,CSJson::Value* msgBady = NULL,int nPlayerId = -1);
    static bool sendHttpRequest(CBasePacket* pPacket ,const char* lpszUrl = URL_REQUEST, const char* lpszHttpVerb = "POST");
    
    
//    void XQsendHttpRequest(unsigned int unMsgType,unsigned int unMsgCode,CSJson::Value* msgBady = NULL,CCObject* target ,SEL_CallFuncO callfun);
    
    void XQsendHttpRequest(unsigned int unMsgType,unsigned int unMsgCode,CSJson::Value* msgBady,CCObject* target, SEL_MyEvent callfun);

public:
	//////////////////////////////////////////////////////////////////////////
    //继承自INetEvent接口
    virtual void onConnect(CHttpInfo* pHttpInfo);
    virtual void onConnectFailed(CHttpInfo* pHttpInfo);
    virtual bool onConnectRetry(CHttpInfo* pHttpInfo);
    virtual void onDisconnect(CHttpInfo* pHttpInfo);
    virtual void onConnectTimeout(CHttpInfo* pHttpInfo);
    virtual void onData(CHttpInfo* pHttpInfo);
    virtual void onReconnect(CHttpInfo* pHttpInfo);
    virtual void onDataComplete(CHttpInfo* pHttpInfo);
    //客户端数据所有的数据缓冲发送完成后，回调本函数
    virtual void onWriteComplete(CHttpInfo* pHttpInfo);
    //超时
    virtual void onTimeout(CHttpInfo* pHttpInfo);
	//////////////////////////////////////////////////////////////////////////
public:
	void dispatchNetPackage(void *pDataPkg);
private:
    std::string m_strUrl;
    std::string m_HttpResponse;
    
//    CCObject *target;
//    SEL_CallFunc callback;
    
    bool isXQ;
    int unMsgType_xq;
    int unMsgCode_xq;
};


#endif  //_NET_HTTP_CLIENT_H