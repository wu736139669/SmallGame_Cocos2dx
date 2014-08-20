/********************************************************************
	created:	2014/04/25 
	filename: 	ImageDownloader.h
	author:		王少培
	purpose:	
*********************************************************************/
#include "ImageDownloader.h"
#include "StringUtil.h"
#include "DataManager.h"
//////////////////////////////////////////////////////////////////////////
//IMPLEMENT_SINGLETON(CCImageNotificationCenter, ms_instance)
CCImageNotificationCenter* CCImageNotificationCenter::ms_instance = NULL;
CCString CCImageNotificationCenter::addObserver(CImageUrlInfo *pInfo)
{
	CCString* observerIDstr =  CCString::createWithFormat("%d",pInfo->nObserverId);

	m_notificationCenter.addObserver(this, callfuncO_selector(CCImageNotificationCenter::imageLoaded), observerIDstr->getCString(), pInfo);

	return observerIDstr->getCString();
}

void CCImageNotificationCenter::removeObserver(const char *name)
{
	m_notificationCenter.removeObserver(this, name);
}

void CCImageNotificationCenter::postNotification(const char *name, CCObject *object)
{
	m_notificationCenter.postNotification(name, object);
}

void CCImageNotificationCenter::imageLoaded(CCObject *obj)
{
	CImageUrlInfo* img = (CImageUrlInfo*)obj;
    img->eLoadState = eImageLoadEnd;
	CCLOG("imageLoaded success,imageName:%s",img->strImageName.getCString());
	CCSprite* sprite = CCImageNotificationCenter::getSpriteFromWriteablePath(img->strImageName.getCString());
	//CCLOG("got sprite 0x%X", sprite);
	//if (img->useMask)
	//{
		//img->layer->addChild(CCImageNotificationCenter::createMaskedSprite(sprite,"mask.png"));
	//}
	//else
	if(sprite && img->pNode!=NULL)
	{
		float scale_ = (float) img->pNode->getContentSize().width  / (float)sprite->getContentSize().width;
		//sprite->setAnchorPoint(ccp(0,0));
		sprite->setScale( scale_ );
		img->pNode->addChild(sprite,10);
		//img->pNode->release();
	}
	this->removeObserver(CStringUtil::ToString(img->nObserverId).c_str());
	//img->release();
}


CCSprite* CCImageNotificationCenter::getSpriteFromWriteablePath(const char* name)
{
	if(!isFileExist(name))
	{
		CCLOG("file no exist : %s",name);
		return NULL;
	}
	std::string path = CCFileUtils::sharedFileUtils()->getWritablePath();
	//path += name;
	path += name;
	path += ".png";
	FILE* fp = fopen(path.c_str(),"rb");
	if (!fp)
		return NULL;
	fseek(fp,0,SEEK_END);
	int len = ftell(fp);
	fseek(fp,0,SEEK_SET);
	char* buf = (char*)malloc(len);
	fread(buf,len,1,fp);
	fclose(fp);
	CCImage* img = new CCImage;
	img->initWithImageData(buf,len);
	free(buf);
	cocos2d::CCTexture2D* texture = new cocos2d::CCTexture2D();
	bool isImg = texture->initWithImage(img);
	img->release();
	if (!isImg)
	{
		delete texture;
		return CCSprite::create("default.png");//加载资源并非图片时返回的默认图
	}
	CCSprite* sprite = CCSprite::createWithTexture(texture);
	texture->release();
	return sprite;
}
 bool CCImageNotificationCenter::isFileExist(const char* name)
 {
	 std::string path = CCFileUtils::sharedFileUtils()->getWritablePath();
	 //path += name;
	 path += name;
	 path += ".png";
	  FILE * pFile; 
	  pFile = fopen (path.c_str(),"r"); 
	 //if(_access(path.c_str(), 0 ) != -1 )
	 if ( pFile!=NULL) 
	 {
		 fclose(pFile);
		 return true;
	 }
	 return false;

 }
//////////////////////////////////////////////////////////////////////////
//
IMPLEMENT_SINGLETON(CImageDownloader, ms_instance)

void CImageDownloader::SendHttpRequest(const char* url, CCNode* pNode, const char* filename,int nObserverId)
{
	unsigned int   n = CStringUtil::HashString((char*)url);

	 	LSTREQUESTIMGINFO::iterator st = mLstReqImgInfo.begin();
	 	LSTREQUESTIMGINFO::iterator en = mLstReqImgInfo.end();
	 	for ( ; st!=en; ++st){
	 		if(st->strImageName.compare(CStringUtil::ToString(n).c_str()) == 0){
	 			return;
	 		}
	 	}

	
    CImageUrlInfo info;
    info.strImageName = CStringUtil::ToString(n).c_str()/*filename*/;
    info.strUrl = url;
    info.pNode = pNode;
    info.eLoadState = eImageLoadStart;
    info.nObserverId = nObserverId;

	if (CCImageNotificationCenter::isFileExist(info.strImageName.getCString()))
	{
		CCImageNotificationCenter::GetInstance()->imageLoaded(&info);
		return;
	}
	pNode->retain();


	mLstReqImgInfo.push_back(info);
}
void CImageDownloader::processEvent()
{
    LSTREQUESTIMGINFO::iterator it = mLstReqImgInfo.begin();
	for (;it!=mLstReqImgInfo.end();)
	{
		CImageUrlInfo& info = *it;
        if(info.eLoadState == eImageLoading){
            return;
        }
		if (info.eLoadState == eImageLoadEnd)
		{
			info.pNode->release();
			mLstReqImgInfo.erase(it++);
		}else if(info.eLoadState == eImageLoadStart)
        {
            SendHttpRequest(&info);
        }
	}
}
void CImageDownloader::clearEvent()
{
    LSTREQUESTIMGINFO::iterator it = mLstReqImgInfo.begin();
	for (;it!=mLstReqImgInfo.end();){
        CImageUrlInfo& info = *it;
        if(info.eLoadState != eImageLoadEnd){
            info.pNode->release();
        }
    }
    mLstReqImgInfo.clear();
}
void CImageDownloader::SendHttpRequest(CImageUrlInfo* pInfo){
    if(pInfo->eLoadState != eImageLoadStart)
		return;
    mpCurImgInfo = pInfo;
	if (mpCurImgInfo->pNode)
	{
		//CCImageNotificationCenter::GetInstance();
		this->observerID = CCImageNotificationCenter::GetInstance()->addObserver(pInfo);
	}else
	{
		int aaa ;
		aaa = 0;
	}
	pInfo->eLoadState = eImageLoading;
	SendHttpRequest(pInfo->strUrl.getCString());
	
}
void CImageDownloader::SendHttpRequest(const char* url)
{
	CCHttpRequest* request = new CCHttpRequest();
	request->setUrl(url);
	//    request->setUrl("http://neoimaging.beareyes.com.cn/png2/ni_png_2_1518.png");
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(this, httpresponse_selector(CImageDownloader::HttpRequestComplete));
	request->setTag("GET IMAGE");
	CCHttpClient::getInstance()->send(request);
	request->release();
}
void CImageDownloader::HttpRequestComplete(CCHttpClient *sender, CCHttpResponse *response)
{
	if (!response)
	{
		mpCurImgInfo->eLoadState = eImageLoadEnd;
        CCImageNotificationCenter::GetInstance()->removeObserver(CStringUtil::ToString(mpCurImgInfo->nObserverId).c_str());
       // mpCurImgInfo->pNode->release();
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
		mpCurImgInfo->eLoadState = eImageLoadEnd;
       // mpCurImgInfo->pNode->release();
        CCImageNotificationCenter::GetInstance()->removeObserver(CStringUtil::ToString(mpCurImgInfo->nObserverId).c_str());
        CCLOG("2222222");
		return;
	}

	// dump data
	std::vector<char> *buffer = response->getResponseData();
	std::string path = CCFileUtils::sharedFileUtils()->getWritablePath();
	std::string bufffff(buffer->begin(),buffer->end());
	//流量统计
	CDataManager::GetInstance().accTotalFlow(buffer->size());
	
	//保存到本地文件
	//path += "dl.png";
    path += mpCurImgInfo->strImageName.getCString();
	path += ".png";
	CCLOG("path: %s",path.c_str());
	FILE *fp = fopen(path.c_str(), "wb+");
	fwrite(bufffff.c_str(), 1,buffer->size(), fp);
	fclose(fp);
	
	
	//传入container的下载请求会添加侦听，待下载完毕自动添加到container上
	if (mpCurImgInfo->pNode)
	{
		// container 是一个CCLayer ，用来显示动态加载的资源
		CCImageNotificationCenter::GetInstance()->getNotificationCenter()->postNotification(CStringUtil::ToString(mpCurImgInfo->nObserverId).c_str());
	}
}