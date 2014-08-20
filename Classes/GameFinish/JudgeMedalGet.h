//
//  JudgeMedalGet.h
//  OnceAgain
//
//  Created by xiaohai on 14-4-28.
//
//

#ifndef __OnceAgain__JudgeMedalGet__
#define __OnceAgain__JudgeMedalGet__

#include <iostream>
#include "cocos2d.h"
#include "CocosGUI.h"
#include "cocos-ext.h"
#include "GameShare_Property.h"
#include "NetCallBack.h"

USING_NS_CC_EXT;
USING_NS_CC;
struct Game_SuperMemory_Condition
{
    std::string a ;
};

class JudgeMedalGet {
public:
//    int GameId;
   static  void clearXMLDate();
   static  void saveDateByInt(int medalId, int value);
   static  void saveDateByfloat(int medal, float value);
   static  void saveDateByDouble(int medal, double value);
   static  void saveDateByBoll(int medal, bool value);
   static  void saveDateByString(int medal, std::string value);
   static  bool JudgeMedalIsGet(int gameid, int medalId, int JudgeNumber);//判断单个勋章是否获得
   static bool JudgeMedalGetByGame(int gameType);
    
    
    static void isMedalInfoHave(int gameid, CCObject*p, SEL_MyEvent c);
};

#endif /* defined(__OnceAgain__JudgeMedalGet__) */
