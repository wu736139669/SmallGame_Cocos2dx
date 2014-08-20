//
//  SanXiaoConfigAnalytical.cpp
//  OnceAgain
//
//  Created by xiaoqiang on 14-6-13.
//
//

#include "SanXiaoConfigAnalytical.h"

#define SXFILD "SanXiao/SanXiaoConfig.json"

CSJson::Value sanxiaoConfigData::getJsonFromFile(const char* fileName){
    CSJson::Reader reader;
    CSJson::Value jsValue;
    unsigned long ilength;
    char* pBuffer = (char *)CCFileUtils::sharedFileUtils()->getFileData(getFullPath(fileName).c_str(), "r", &ilength);
    bool parseRet = reader.parse(pBuffer, jsValue, false);
    CCAssert(parseRet, "Read GridData Error~!!!!!!!!!");
    return jsValue;
}

string sanxiaoConfigData::getFullPath(const char* path){
    return cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename(path);
}

void sanxiaoConfigData::getSanXiaoConfig() {
    if (sanXiaoData.size() > 0) {
        return;
    }
    sanXiaoData = getJsonFromFile(SXFILD);
}

string sanxiaoConfigData::getStringDataByName(const char *fileName) {
    for (int i = 0; i < sanXiaoData.size(); i++) {
        CSJson::Value &val = sanXiaoData[0];
        return val[fileName].asCString();
    }
    return "";
}

int sanxiaoConfigData::getIntDataByName(const char *name) {
    for (int i = 0; i < sanXiaoData.size(); i++) {
        CSJson::Value &val = sanXiaoData[0];
        return val[name].asInt();
    }
    return 0;
}
