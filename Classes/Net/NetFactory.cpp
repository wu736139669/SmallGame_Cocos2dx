/***************************************************************
* 
*
*  作者：   王少培
*  文件名：   NetHookManager.cpp
*  创建时间： 2014-3-20
*
***************************************************************/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "NetFactory.h"
#include "GameShare_NetSystem.h"
#include "NetHttpClient.h"
#include "NetPacket.h"
#include "ScopeLock.h"
#include "NetListProcess.h"
static CNetFactory* spNetFactory = NULL;
//////////////////////////////////////////////////////////////////////////
void CHttpInfo::clr()
{

}
CHttpInfo::~CHttpInfo()
{
	if (mpPacket)
	{
		delete mpPacket;
		mpPacket = NULL;
	}
}
//////////////////////////////////////////////////////////////////////////
 CHttpInfo* CNetFactory::createHttpInfo(INetEvent* pEvent)
 {
	 return new CHttpInfo(pEvent);
 }

bool CNetFactory::addToPool(CHttpInfo *pInfo) {
	ScopeLock lock(mLock);
	NetInfoList::iterator it = mNetInfoList.begin();
	for (;it!=mNetInfoList.end();++it)
	{
		if (*it == pInfo)
			return false;
	}
	mNetInfoList.push_back(pInfo);
    pthread_cond_signal(&s_SleepCondition);
	 return true;
}
int CNetFactory::getNetInfoListAmount()
{
	ScopeLock lock(mLock);
	return mNetInfoList.size();
}
void CNetFactory::releaseFromPool(CHttpInfo *pInfo,bool bDel) {
	ScopeLock lock(mLock);
	NetInfoList::iterator it = mNetInfoList.begin();
	for (;it!=mNetInfoList.end();)
	{
		CHttpInfo* pTemp = *it;
		if (pTemp == pInfo)
		{
			if (bDel)
			{
				delete pTemp;
				pTemp = NULL;
			}
			mNetInfoList.erase(it++);
			//break;
		}else
		{
			++it;
		}
	}
	return ;
}
void CNetFactory::processNetEvent()
{
	do 
	{
        if(mbQuit)
            break;
		if (!mNetInfoList.empty())
		{
			CHttpInfo* pTemp = NULL;
			{
				ScopeLock lock(mLock);
				pTemp = mNetInfoList.front();
				mNetInfoList.pop_front();
				if(pTemp == NULL)
					return;
			}
            
			std::string strResult;
			if(pTemp->getPacket())
				strResult = GameShare_NetSystem::ShareNetSystem()->NetSystem_HTTPRequest(pTemp->getUrl().c_str(),pTemp->getPacket()->getContent().c_str());
			else
				strResult = GameShare_NetSystem::ShareNetSystem()->NetSystem_HTTPRequest(pTemp->getUrl().c_str());
			pTemp->setReceData(strResult.c_str());
			CNetListProcess::sharedInstance().addToPool(pTemp);
		}
		else
        {
            CCLOG("pthread_cond_wait");
            pthread_cond_wait(&s_SleepCondition, &s_SleepMutex);
        }
//#ifdef _WIN32
//			Sleep(50);
//#else
//			usleep(50);
//#endif
	} while (true);
    
    pthread_mutex_destroy(&s_SleepMutex);
    pthread_cond_destroy(&s_SleepCondition);
}
void CNetFactory::processNetEventEx()
{
    do
	{
		if (!mNetInfoList.empty())
		{
			CHttpInfo* pTemp = NULL;
			{
				ScopeLock lock(mLock);
				pTemp = mNetInfoList.front();
				mNetInfoList.pop_front();
				if(pTemp == NULL)
					return;
			}
            
			std::string strResult;
			if(pTemp->getPacket())
            {
                CCHttpRequest* request = new CCHttpRequest();
                request->setUrl(pTemp->getUrl().c_str());
                request->setRequestType(CCHttpRequest::kHttpPost);
                request->setResponseCallback(this, httpresponse_selector(CNetFactory::httpRequestComplete));
                request->setTag("REQUSET GAME DATA");
                CCHttpClient::getInstance()->send(request);
                request->release();
            }
////				strResult = GameShare_NetSystem::ShareNetSystem()->NetSystem_HTTPRequest(pTemp->getUrl().c_str(),pTemp->getPacket()->getContent().c_str());
//			else
//				strResult = GameShare_NetSystem::ShareNetSystem()->NetSystem_HTTPRequest(pTemp->getUrl().c_str());
//			pTemp->setReceData(strResult.c_str());
//			CNetListProcess::sharedInstance().addToPool(pTemp);
		}
	} while (true);
}
void CNetFactory::httpRequestComplete(CCHttpClient *sender, CCHttpResponse *response)
{
	if (!response)
	{
		CCLOG("CCHttpResponse is null");
		return;
	}
    
	// You can get original request type from: response->request->reqType
	if (0 != strlen(response->getHttpRequest()->getTag()))
	{
		CCLog("%s completed", response->getHttpRequest()->getTag());
	}
    
	int statusCode = response->getResponseCode();
	char statusString[64] = {};
	sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
	CCLog("response code: %d", statusCode);
    
	if (!response->isSucceed())
	{
		CCLog("response failed");
		CCLog("error buffer: %s", response->getErrorBuffer());
		return;
	}
        // dump data
        std::vector<char> *buffer = response->getResponseData();
        std::string path = CCFileUtils::sharedFileUtils()->getWritablePath();
        std::string buf(buffer->begin(),buffer->end());

}
void CNetFactory::run()
{
	processNetEvent();

}
void CNetFactory::start()
{
    pthread_mutex_init(&s_SleepMutex, NULL);
    pthread_cond_init(&s_SleepCondition, NULL);
    CRunable::start();
}
CNetFactory *CNetFactory::sharedInstance() {
	if (spNetFactory == NULL)
	{
		spNetFactory  = new CNetFactory;
		spNetFactory->start();
	}
  return spNetFactory;
}

CNetFactory::CNetFactory():mbQuit(false) {
}
