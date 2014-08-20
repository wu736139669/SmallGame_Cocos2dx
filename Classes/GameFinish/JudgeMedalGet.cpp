//
//  JudgeMedalGet.cpp
//  OnceAgain
//
//  Created by xiaohai on 14-4-28.
//
//

#include "JudgeMedalGet.h"
#include "XQDate.h"
#include "PlayerInfoManager.h"
#include "NetHttpClient.h"
#include "NetPacket.h"
void JudgeMedalGet::clearXMLDate(){
    if (CCUserDefault::sharedUserDefault()->getIntegerForKey("DATETIME")) {
        int dayTime = CCUserDefault::sharedUserDefault()->getIntegerForKey("DATETIME");
        struct cc_timeval now;
        CCTime::gettimeofdayCocos2d(&now, NULL);
        struct tm *tm;
        tm = localtime((const time_t *)&now.tv_sec);
        
        if (dayTime != tm->tm_mday) {
            //清除部分缓存数据
            CCUserDefault::sharedUserDefault()->setIntegerForKey("DATETIME", tm->tm_mday);
//            
//            CCUserDefault::sharedUserDefault()->setBoolForKey("medal600165", false);
//            CCUserDefault::sharedUserDefault()->setBoolForKey("medal600158", false);
//            CCUserDefault::sharedUserDefault()->setBoolForKey("medal600157", false);
        }
    }
}

void JudgeMedalGet::saveDateByInt(int medal, int value) {
    CCString str;
    str.initWithFormat("medal%d", medal);
    CCUserDefault::sharedUserDefault()->setIntegerForKey(str.getCString(), value);
}

void JudgeMedalGet::saveDateByfloat(int medal, float value) {
    CCString str;
    str.initWithFormat("medal%d", medal);
    CCUserDefault::sharedUserDefault()->setFloatForKey(str.getCString(), value);
}

void JudgeMedalGet::saveDateByDouble(int medal, double value) {
    CCString str;
    str.initWithFormat("medal%d", medal);
    CCUserDefault::sharedUserDefault()->setDoubleForKey(str.getCString(), value);
}

void JudgeMedalGet::saveDateByBoll(int medal, bool value) {
    CCString str;
    str.initWithFormat("medal%d", medal);
    CCUserDefault::sharedUserDefault()->setBoolForKey(str.getCString(), value);
}

void JudgeMedalGet::saveDateByString(int medal, std::string value) {
    CCString str;
    str.initWithFormat("medal%d", medal);
    CCUserDefault::sharedUserDefault()->setStringForKey(str.getCString(), value);
}

bool JudgeMedalGet::JudgeMedalIsGet(int gameid, int MedalId,int JudgeNumber) {
    if (MedalId == 600001|| MedalId == 600002 ||MedalId == 600003) {
        CCString str;
        str.initWithFormat("medal600001_%d", gameid);
        int number = CCUserDefault::sharedUserDefault()->getIntegerForKey(str.getCString());
        if (number >= JudgeNumber) {
            return true;
        }
    }
    if (MedalId == 600004|| MedalId == 600005 ||MedalId == 600006) {
        CCString str;
        str.initWithFormat("medal600004_%d", gameid);
        int number = CCUserDefault::sharedUserDefault()->getIntegerForKey(str.getCString());
        if (number >= JudgeNumber) {
            return true;
        }
    }
    if (MedalId == 600007|| MedalId == 600008 ||MedalId == 600009) {
        CCString str;
        str.initWithFormat("medal600007_%d", gameid);
        int number = CCUserDefault::sharedUserDefault()->getIntegerForKey(str.getCString());
        if (number >= JudgeNumber) {
            return true;
        }
    }
    if (MedalId == 600010|| MedalId == 600011 ||MedalId == 600012) {
        CCString str;
        str.initWithFormat("medal600010_%d", gameid);
        int number = CCUserDefault::sharedUserDefault()->getIntegerForKey(str.getCString());
        if (number >= JudgeNumber) {
            return true;
        }
    }
    if (MedalId == 600013|| MedalId == 600014 ||MedalId == 600015) {
        CCString str;
        str.initWithFormat("medal600013_%d", gameid);
        int number = CCUserDefault::sharedUserDefault()->getIntegerForKey(str.getCString());
        if (number >= JudgeNumber) {
            return true;
        }
    }
    if (MedalId == 600016|| MedalId == 600017 ||MedalId == 600018) {
        CCString str;
        str.initWithFormat("medal600016_%d", gameid);
        int number = CCUserDefault::sharedUserDefault()->getIntegerForKey(str.getCString());
        if (number >= JudgeNumber) {
            return true;
        }
    }
    if (MedalId == 600019 || MedalId == 600020 || MedalId == 600021) {
        CCString str;
        str.initWithFormat("medal600019_%d", gameid);
        int number = CCUserDefault::sharedUserDefault()->getIntegerForKey(str.getCString());
        if (number >= JudgeNumber) {
            return true;
        }
    }
    if (MedalId == 600022 || MedalId == 600023 || MedalId == 600024) {
        CCString str;
        str.initWithFormat("medal600022_%d", gameid);
        int number = CCUserDefault::sharedUserDefault()->getIntegerForKey(str.getCString());
        if (number >= JudgeNumber) {
            return true;
        }
    }
    
    if (MedalId == 600157) {
        bool medal600157 = CCUserDefault::sharedUserDefault()->getBoolForKey("P_2");
        if (medal600157) {
            return true;
        }
    }
    if (MedalId == 600158 ) {
        bool medal600158 = CCUserDefault::sharedUserDefault()->getBoolForKey("P_3");
        if (medal600158) {
            return true;
        }
    }
    if (MedalId == 600165) {
         int count = CCUserDefault::sharedUserDefault()->getIntegerForKey("medal600165");
        if (count >= JudgeNumber) {
//            CCUserDefault::sharedUserDefault()->setBoolForKey("medal600165", true);
            return true;
        }
    }
    if (MedalId == 600166) {
         int count = CCUserDefault::sharedUserDefault()->getIntegerForKey("medal600165");
        if (count >= JudgeNumber) {
            return true;
        }
    }
    if (MedalId == 600167) {
         int count = CCUserDefault::sharedUserDefault()->getIntegerForKey("medal600165");
        if (count >= JudgeNumber) {
            return true;
        }
    }
    if (MedalId == 600177) {
        int count = CCUserDefault::sharedUserDefault()->getIntegerForKey("medal600177");
        if (count >= JudgeNumber) {
            return true;
        }
    }
    return false;
}

bool JudgeMedalGet::JudgeMedalGetByGame(int gameType) {
    CCString str;
    str.initWithFormat("65%d", gameType);
    CSJson::Value root = XQDate::sharedInstance().GetDate(str.getCString());
    
    
    for (int j = 0; j < root.size(); j++){
        CSJson::Value &val = root[j];
        int medalId = val["taskid"].asInt();
        int haveGet = val["taskcomplete"].asInt();
        SMeDalTaskData *medalinfo = CTaskMan::sharedInstance().getMedalTaskDataById(medalId);
        
        if (haveGet == 0) {
            if (JudgeMedalIsGet(gameType, medalId, medalinfo->TaskValue)) {
                return true;
            }
        }
    }
    return false;
}

void JudgeMedalGet::isMedalInfoHave(int gameid, CCObject*p, SEL_MyEvent c){
    CCString str1;
    str1.initWithFormat("65%d", gameid);
    CSJson::Value root = XQDate::sharedInstance().GetDate(str1.getCString());
    if (root.size() < 3) {
        CCString str2;
        str2.initWithFormat("%d%d%d", eNetMsgTypeMissionSys, eNetMsgEveryDay, gameid);
        XQDate::sharedInstance().setGameType(gameid);
        CSJson::Value msg_body;
        msg_body["playerid"] = CSJson::Value(CPlayerInfoMan::sharedInstance().getPlayerInfo().nId);
        msg_body["gameid"] = CSJson::Value(gameid);
        NetHttpClient::sharedInstance().XQsendHttpRequest(eNetMsgTypeMissionSys, eNetMsgEveryDay, &msg_body, p, c);
    }
}