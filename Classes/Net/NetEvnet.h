/***************************************************************
* 
*
*  作者：   王少培
*  文件名：   
*  创建时间： 2014-3-20
*
***************************************************************/
#ifndef _INetEvent_h_
#define _INetEvent_h_

class CHttpInfo;
class INetEvent
{
public:
	INetEvent(){}
	~INetEvent(){}
	virtual void onConnect(CHttpInfo* pInfo){}
	virtual void onConnectFailed(CHttpInfo *pInfo){}
	virtual bool onConnectRetry(CHttpInfo *pInfo){return true;}
	virtual void onDisconnect(CHttpInfo *pInfo){}
	virtual void onConnectTimeout(CHttpInfo *pInfo){}
	virtual void onData(CHttpInfo *pInfo){}
	virtual void onReconnect(CHttpInfo *pInfo){}
	virtual void onDataComplete(CHttpInfo *pInfo){}
	//客户端数据所有的数据缓冲发送完成后，回调本函数
	virtual void onWriteComplete(CHttpInfo *pInfo){}
	//超时
	virtual void onTimeout(CHttpInfo *pInfo){}
};
#endif