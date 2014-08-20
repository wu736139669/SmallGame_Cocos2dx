//
//  GameShare_NetSystem.cpp
//  OnceAgain
//
//  Created by xiaohai on 14-3-7.
//
//

#include "GameShare_NetSystem.h"

static GameShare_NetSystem *s_ShareNetSystem = NULL;

GameShare_NetSystem::GameShare_NetSystem()
{
    //初始化
    curl_global_init(CURL_GLOBAL_ALL);
}

GameShare_NetSystem::~GameShare_NetSystem()
{
    curl_global_cleanup();
}

bool GameShare_NetSystem::init()
{
    if(!CCNode::init())
    {
        return false;
    }
    return true;
}

GameShare_NetSystem* GameShare_NetSystem::ShareNetSystem()
{
    if(s_ShareNetSystem == NULL)
    {
        s_ShareNetSystem = new GameShare_NetSystem();
        s_ShareNetSystem->init();
        return s_ShareNetSystem;
    }
    return s_ShareNetSystem;
}


size_t GameShare_NetSystem::Page_CallBack(void* ptr, size_t size, size_t nmemb, void* stream)
{
    int res_size = 0;
    char* res_Buf = NULL;
    
    res_size = size * nmemb;
    res_Buf = new char[res_size + 1];
    memset(res_Buf, 0x0, res_size + 1);
    memcpy(res_Buf, ptr, res_size);
    
    if(stream != NULL)
    {
        ((GameShare_NetSystem*)stream)->m_sPageResult += res_Buf;
    }
    delete[] res_Buf;
    res_Buf = NULL;
    return res_size;
}


std::string GameShare_NetSystem::NetSystem_HTTPRequest(const char* rpUrl, const char* rpPostParas/*=NULL*/)
{
    CCLog("request is %s", rpUrl);
	m_sPageResult.clear();
    CURLcode resCode;
    std::string sResultPage = "";
    
    CURL* pCurl = curl_easy_init();
    if(pCurl == NULL) return sResultPage;

	struct curl_slist *sCurlList = NULL;
	sCurlList = curl_slist_append(sCurlList, "Accept:text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
	sCurlList = curl_slist_append(sCurlList, "Accept-Encoding:gzip,deflate,sdch");
	sCurlList = curl_slist_append(sCurlList, "Content-Type:application/x-www-form-urlencoded; charset=UTF-8");
	curl_easy_setopt(pCurl, CURLOPT_HTTPHEADER, sCurlList);
    curl_easy_setopt(pCurl, CURLOPT_WRITEFUNCTION, GameShare_NetSystem::Page_CallBack);
    curl_easy_setopt(pCurl, CURLOPT_WRITEDATA, this);
    curl_easy_setopt(pCurl, CURLOPT_URL, rpUrl);
    
    
    
    //是否post
    if(rpPostParas != NULL)
    {
        
        curl_easy_setopt(pCurl, CURLOPT_POSTFIELDS, rpPostParas);
    }
    
    resCode = curl_easy_perform(pCurl);

	char *ip;
	resCode = curl_easy_getinfo(pCurl, CURLINFO_PRIMARY_IP, &ip);
	if(CURLE_OK == resCode)		m_sIp = ip;
	//int httpCode = curl_easy_getinfo(pCurl, CURLINFO_HTTP_CODE);
    //加密
    //CCLOG("%s", m_sPageResult.c_str());
    
    curl_easy_cleanup(pCurl);
    sResultPage = m_sPageResult;
//    CCLOG("============");
//    CCLOG("%s", sResultPage.c_str());
//    CCLOG("=====");
    return sResultPage;
}

void GameShare_NetSystem::EncodeStr()
{
    
}

void GameShare_NetSystem::DecodeStr()
{
    
}