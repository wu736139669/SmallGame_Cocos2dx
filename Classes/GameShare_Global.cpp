//
//  GameShare_Global.cpp
//  OnceAgain
//
//  Created by mac on 14-2-28.
//
//

#include "GameShare_Global.h"
GameShare_Global*  GameShare_Global::m_shareGlobal = NULL;


 GameShare_Global* GameShare_Global::shareGlobal()
{
    if (m_shareGlobal == NULL) {
        m_shareGlobal = new GameShare_Global(); 
    }
    return m_shareGlobal;
}

GameShare_Global::~GameShare_Global()
{
    delete m_shareGlobal;
    m_shareGlobal = NULL;
}

void GameShare_Global::reSet()
{
//    sinaID = "";
    loginType = LoginType_Tourist;
//    riceNum = 0;
    gameType = Game_Null;
}