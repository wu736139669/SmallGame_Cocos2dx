//
//  GameShare_NetSystem.h
//  OnceAgain
//
//  Created by xiaohai on 14-3-7.
//
//

#ifndef OnceAgain_GameShare_NetSystem_h
#define OnceAgain_GameShare_NetSystem_h

#include "cocos2d.h"
#include "curl/curl.h"
USING_NS_CC;
class GameShare_NetSystem: public CCNode
{
public:
    GameShare_NetSystem();
    ~GameShare_NetSystem();
    
public:
    virtual bool init();
    
    static GameShare_NetSystem* ShareNetSystem();
    
    static size_t Page_CallBack(void* ptr, size_t size, size_t nmemb, void* stream);

    std::string NetSystem_HTTPRequest(const char* rpUrl, const char* rpPostParas = NULL);
    
    
private:
    void EncodeStr();
    void DecodeStr();
public:
    std::string     m_sPageResult;
	std::string		m_sIp;
};

#endif
