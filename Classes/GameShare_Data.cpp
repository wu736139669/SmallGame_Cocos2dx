//
//  GameShare_Data.cpp
//  OnceAgain
//
//  Created by mac on 14-3-10.
//
//

#include "GameShare_Data.h"

GameShare_Data*  GameShare_Data::m_shareData = NULL;


GameShare_Data* GameShare_Data::shareData()
{
    if (m_shareData == NULL) {
        m_shareData = new GameShare_Data();
    }
    return m_shareData;
}

GameShare_Data::~GameShare_Data()
{
    delete m_shareData;
    m_shareData = NULL;
}

long GameShare_Data::getMaxScoreByName(const char* gameName)
{
   return  CCUserDefault::sharedUserDefault()->getDoubleForKey(gameName);
}
void GameShare_Data::setMaxScore(const char *gameName, long score)
{
    CCUserDefault::sharedUserDefault()->setDoubleForKey(gameName, (double)score);
    CCUserDefault::sharedUserDefault()->flush();
}
std::string GameShare_Data::getSinaID()
{
    return CCUserDefault::sharedUserDefault()->getStringForKey("SINAID");
}
std::string GameShare_Data::getSinaToken()
{
    return CCUserDefault::sharedUserDefault()->getStringForKey("SINATOKEN");
}
long GameShare_Data::getSinaTime()
{
    return CCUserDefault::sharedUserDefault()->getIntegerForKey("SINADATE");
}
void GameShare_Data::setSinaId(std::string sinaId, std::string sinaToken, long sinaDate)
{
    CCUserDefault::sharedUserDefault()->setStringForKey("SINAID", sinaId);
    CCUserDefault::sharedUserDefault()->flush();
    CCUserDefault::sharedUserDefault()->setStringForKey("SINATOKEN", sinaToken);
    CCUserDefault::sharedUserDefault()->flush();
    CCUserDefault::sharedUserDefault()->setIntegerForKey("SINADATE", sinaDate);
    CCUserDefault::sharedUserDefault()->flush();
}
void GameShare_Data::setQQID(std::string qqid, std::string qqToken, long qqDate)
{
    CCUserDefault::sharedUserDefault()->setStringForKey("QQID", qqid);
    CCUserDefault::sharedUserDefault()->flush();
    CCUserDefault::sharedUserDefault()->setStringForKey("QQTOKEN", qqToken);
    CCUserDefault::sharedUserDefault()->flush();
    CCUserDefault::sharedUserDefault()->setIntegerForKey("QQDATE", qqDate);
    CCUserDefault::sharedUserDefault()->flush();
}
std::string GameShare_Data::getQQID()
{
    return CCUserDefault::sharedUserDefault()->getStringForKey("QQID");
}
long GameShare_Data::getQQTime()
{
    return CCUserDefault::sharedUserDefault()->getIntegerForKey("QQDATE");
}
void GameShare_Data::setUserUUID(std::string uuid)
{
    CCUserDefault::sharedUserDefault()->setStringForKey("UUID", uuid);
    CCUserDefault::sharedUserDefault()->flush();
}
std::string GameShare_Data::getUserUUID()
{
    return CCUserDefault::sharedUserDefault()->getStringForKey("UUID");
}

void GameShare_Data::setUserName(std::string userName)
{
    CCUserDefault::sharedUserDefault()->setStringForKey("USERNAME", userName);
    CCUserDefault::sharedUserDefault()->flush();
}
std::string GameShare_Data::getUserName()
{
    return CCUserDefault::sharedUserDefault()->getStringForKey("USERNAME");
}
void GameShare_Data::setUserUrl(std::string userUrl)
{
    CCUserDefault::sharedUserDefault()->setStringForKey("USERURL", userUrl);
    CCUserDefault::sharedUserDefault()->flush();
}
std::string GameShare_Data::getUserUrl()
{
    return CCUserDefault::sharedUserDefault()->getStringForKey("USERURL");
}
