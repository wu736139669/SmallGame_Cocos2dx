//
//  NetListProcess.h
//  OnceAgain
//
//  Created by 王少培 on 14-4-7.
//
//

#ifndef __OnceAgain__NetListProcess__
#define __OnceAgain__NetListProcess__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "Singleton.h"
#include "CriSection.h"
USING_NS_CC;


class CHttpInfo;
class CNetListProcess : public CCObject, public CSingleton<CNetListProcess> {
    
public:
    //接收数据
	typedef std::list<CHttpInfo*> NetReceInfoList;
    
    CNetListProcess();
    ~CNetListProcess();
public:
	virtual bool init();
	virtual void update(float fDelta);

	bool addToPool(CHttpInfo* pInfo);
	void releaseFromPool(CHttpInfo* pInfo,bool bDel);
	void cleanPool();
	void processNetEvent();
public:
	//CREATE_FUNC(CNetListProcess);
	
protected:
	NetReceInfoList mNetInfoList;
    
	CriSectionLock mLock;
    
};

#endif /* defined(__OnceAgain__NetListProcess__) */
