//
//  NetListProcess.cpp
//  OnceAgain
//
//  Created by 王少培 on 14-4-7.
//
//

#include "NetListProcess.h"
#include "NetFactory.h"
#include "NetHttpClient.h"
#include "ImageDownloader.h"
#include "DialogManager.h"
#include "GameLayerLoading.h"
CNetListProcess::CNetListProcess()
{
	CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(this, -1, false);
}
CNetListProcess::~CNetListProcess()
{
	CCDirector::sharedDirector()->getScheduler()->unscheduleUpdateForTarget(this);
}
bool CNetListProcess::init()
{
// 	if(!CCNode::init())
// 	{
// 		return false;
// 	}
	return true;
}

//void CNetListProcess::onEnter()
//{
	//CCNode::onEnter();
//}
//void CNetListProcess::onExit()
//{
	//CCNode::onExit();
	
//}
void CNetListProcess::update(float fDelta)
{
	processNetEvent();
}
void CNetListProcess::processNetEvent()
{
	//图片信息请求
	 CImageDownloader::GetInstance()->processEvent();

	//网络数据请求
	NetReceInfoList TempList ;
	{
		if (mNetInfoList.empty())
			return;
		ScopeLock lock(mLock);
		TempList = mNetInfoList;
		cleanPool();
	}
	
	NetReceInfoList::iterator it = TempList.begin();
	for (;it!=TempList.end();)
	{
		CHttpInfo *pInfo = *it;
		if (!pInfo->getReceData().empty())
		{
			NetHttpClient::sharedInstance().onWriteComplete(pInfo);
		}else
			NetHttpClient::sharedInstance().onTimeout(pInfo);

		delete pInfo;
		pInfo = NULL;
		TempList.erase(it++);
	}
}
bool CNetListProcess::addToPool(CHttpInfo *pInfo) {
	ScopeLock lock(mLock);
	NetReceInfoList::iterator it = mNetInfoList.begin();
	for (;it!=mNetInfoList.end();++it)
	{
		if (*it == pInfo)
			return false;
	}
	mNetInfoList.push_back(pInfo);
	return true;
}
void CNetListProcess::cleanPool()
{
	mNetInfoList.clear();
}
void CNetListProcess::releaseFromPool(CHttpInfo *pInfo,bool bDel) {
	ScopeLock lock(mLock);
	NetReceInfoList::iterator it = mNetInfoList.begin();
	for (;it!=mNetInfoList.end();)
	{
		CHttpInfo* pTemp = *it;
		if (pTemp == pInfo)
		{
			if (bDel){
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
