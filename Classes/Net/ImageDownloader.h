/********************************************************************
	created:	2014/04/25 
	filename: 	ImageDownloader.h
	author:		王少培
	purpose:	
*********************************************************************/
#ifndef __NetImageDownloader_h__
#define __NetImageDownloader_h__
#include <map>
#include <vector>
#include <string>
#include "MsgDefine.h"
#include "JsonHelper.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameCommon.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

enum EImageLoadState{
    eImageLoadStart,
    eImageLoading,
    eImageLoadEnd,
};
class CImageUrlInfo :public CCObject{
public:
    CCString        strUrl;
    CCString        strImageName;
	int             nObserverId;
    EImageLoadState eLoadState;
    CCNode*         pNode; //父Node
};
//图片结构
class imgstruct : public CCObject
{
public:
	imgstruct(const char* iName, const char* idStr, CCNode* _pNode, bool mask)
	{
		imageName = string(iName);
		observerId = string(idStr);
		pNode = _pNode;
		useMask = mask;
	}
	~imgstruct()
	{
	}

	string          imageName;
	string          observerId;
	CCNode*        pNode; //父layer
	bool            useMask;
};

//图片监听，下载完成触发
class CCImageNotificationCenter:public CCObject
{
	//DECLARE_SINGLETON(CCImageNotificationCenter, ms_instance)
private:
			static CCImageNotificationCenter* ms_instance;
public:
	   static CCImageNotificationCenter* GetInstance(){
		   if (ms_instance == NULL){
			   ms_instance = new  CCImageNotificationCenter;
		   }
			return ms_instance;
		};
	   static void Destroy();
public:
	
	CCImageNotificationCenter():m_observerID(0){};
	~CCImageNotificationCenter(){};

	CCString addObserver(CImageUrlInfo *pInfo);
	void imageLoaded();
	void removeObserver(const char *name);

	void postNotification(const char *name, CCObject *object);

	void imageLoaded(CCObject *obj);
	CCNotificationCenter* getNotificationCenter(){return &m_notificationCenter;};
	static CCSprite* getSpriteFromWriteablePath(const char* name);
	static bool isFileExist(const char* name);

private:
	CCNotificationCenter        m_notificationCenter;
	int                         m_observerID;
};
//////////////////////////////////////////////////////////////////////////
class CImageDownloader : public cocos2d::CCObject
{
	//DECLARE_SINGLETON_CLASS(ImageDownloader);
	DECLARE_SINGLETON(CImageDownloader, ms_instance)
public:
    //请求图片列表
    typedef std::list<CImageUrlInfo> LSTREQUESTIMGINFO;
public:
	CImageDownloader():useMask(false),mpCurImgInfo(NULL){};
	~CImageDownloader(){};

	void CreateLuaFunc();

	//请求图片数据
	void SendHttpRequest(const char* url, CCNode* pNode, const char* filename,int nObserverId);
	void HttpRequestComplete(CCHttpClient *sender, CCHttpResponse *response);
    void processEvent();
    void clearEvent();

protected:
	void SendHttpRequest(CImageUrlInfo* pInfo);
	void SendHttpRequest(const char* url);

	CCString    observerID;
	CCNode*    container;
	bool        useMask;
    LSTREQUESTIMGINFO mLstReqImgInfo;
    CImageUrlInfo* mpCurImgInfo;
};
#endif
