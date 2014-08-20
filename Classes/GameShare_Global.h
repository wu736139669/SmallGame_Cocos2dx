//
//  GameShare_Global.h
//  OnceAgain
//
//  Created by mac on 14-2-28.
//
//

#ifndef __OnceAgain__GameShare_Global__
#define __OnceAgain__GameShare_Global__

#include "cocos2d.h"
#include "GameShare_Property.h"
#include "platform/CCPlatformMacros.h"

enum LoginType{
    LoginType_Tourist = 0,
    LoginType_Sina = 1,
    LoginType_QQ = 2

};

class GameShare_Global
{
public:
    static GameShare_Global* shareGlobal(void);
    ~GameShare_Global();
    
    e_GameType gameType;                          //Now play game type.
    sGameProperty gameProperty;                  //Now play game property.
    LoginType loginType;

    void reSet();
private:
    GameShare_Global(){};
    
    static GameShare_Global* m_shareGlobal;
    
};

#endif /* defined(__OnceAgain__Global__) */