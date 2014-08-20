/***************************************************************
* 
*
*  作者：   王少培
*  文件名：   NetHookManager.cpp
*  创建时间： 2014-3-20
*
***************************************************************/
#ifndef __NetFactory_h__
#define __NetFactory_h__
#include <map>
#include "NetEvnet.h"
#include <vector>
#include <string>
#include "Thread.h"
#include "CriSection.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include <list>
USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class INetEvent;
class CBasePacket;
class CHttpInfo {
public:
	CHttpInfo(INetEvent* pEvent): mpNetEvent(pEvent),mpPacket(NULL) {}
	virtual ~CHttpInfo();
public: 
	string& getUrl(){return mstrUrl;};;
	void setUrl(const char* pUrl){mstrUrl = pUrl;}
	void setReceData(const char* pData){mstrReceData = pData;};
	void setPacket(CBasePacket* pPacket){ mpPacket = pPacket;};
	CBasePacket* getPacket(){return mpPacket;}
	string& getReceData(){return mstrReceData;};
	void clr();
protected:
	INetEvent* mpNetEvent;
	CBasePacket* mpPacket;
	string mstrUrl;
	string mstrReceData;
};

class CNetFactory : public CRunable,public CCObject{
 // typedef std::vector<CHttpInfo*> NetInfoList;
  
public:
  CNetFactory();
public:
	typedef std::list<CHttpInfo*> NetInfoList;
	
	static CNetFactory *sharedInstance();

    virtual void start();
	virtual void run();
	CHttpInfo* createHttpInfo(INetEvent* pEvent);
	bool addToPool(CHttpInfo* pInfo);
	void releaseFromPool(CHttpInfo* pInfo,bool bDel );
	void processNetEvent();
    void processNetEventEx();
	void dispatchNetPackage();
	int getNetInfoListAmount();
    void httpRequestComplete(CCHttpClient *sender, CCHttpResponse *response);
    CC_SYNTHESIZE(bool,mbQuit ,Quit)
protected:
	NetInfoList mNetInfoList;
	//NetInfoList mNetInfoList;
	CriSectionLock mLock;
     pthread_mutex_t		s_SleepMutex;
     pthread_cond_t		s_SleepCondition;
};
#endif
