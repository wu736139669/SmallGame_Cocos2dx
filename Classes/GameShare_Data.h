//
//  GameShare_Data.h
//  OnceAgain
//
//  Created by mac on 14-3-10.
//
//

#ifndef __OnceAgain__GameShare_Data__
#define __OnceAgain__GameShare_Data__

#include "cocos2d.h"

#include "GameShare_Property.h"
USING_NS_CC;
class GameShare_Data
{
public:
    static GameShare_Data* shareData(void);
    //游戏分数.
    long getMaxScoreByName(const char* gameName);
    void setMaxScore(const char* gameName, long score);
    
    //获取社交的接口
    std::string getSinaID();
    std::string getSinaToken();
    long getSinaTime();
    void setSinaId(std::string sinaId, std::string sinaToken, long sinaDate);
    void setQQID(std::string qqId, std::string qqToken, long qqDate);
    std::string getQQID();
    long getQQTime();
    
    //用户的uuid
    void setUserUUID(std::string uuid);
    std::string getUserUUID();
    
    //用户的姓名.
    void setUserName(std::string userName);
    std::string getUserName(void);
    //用户的头像url
    void setUserUrl(std::string userUrl);
    std::string getUserUrl(void);
    
    
    virtual ~GameShare_Data(void);
    
private:
    GameShare_Data(){};
    static GameShare_Data* m_shareData;
};
#endif /* defined(__OnceAgain__GameShare_Data__) */
