//
//  XQDate.h
//  OnceAgain
//
//  Created by xiaohai on 14-4-29.
//
//

#ifndef __OnceAgain__XQDate__
#define __OnceAgain__XQDate__

#include <iostream>
#include "cocos2d.h"

#include "CocosGUI.h"
#include "cocos-ext.h"
#include "TaskManager.h"
#include "JudgeMedalGet.h"
#include "Singleton.h"
#include "JsonHelper.h"
#include "NetCallBack.h"

USING_NS_CC_EXT;
USING_NS_CC;


struct MyXQDate
{
	std::string keyId;
	CSJson::Value root;
};

//typedef std::vector<MyXQDate> CACHELIST;

class XQDate :public CSingleton<XQDate>, public NetCallBack{
public:
    //储存数据;
    void SaveDate(void *pDataPkg, CCObject* target, SEL_MyEvent callfun);
    //检索是否已经拥有该数据
    bool HaveDate(std::string key);
    //获取数据
    CSJson::Value GetDate(std::string key);
    
    int getValueForInt(CSJson::Value root, std::string key);
    float getValueForFloat(CSJson::Value root, std::string key);
    double getValueForDouble(CSJson::Value root, std::string key);
    std::string getValueForString(CSJson::Value root, std::string key);
    void setGameType(int gameType);
    
    
    void CompleteTask(int gameid, int taskId);
protected:
    std::vector<MyXQDate> myCacheList;
    int GameType;
};

#endif /* defined(__OnceAgain__XQDate__) */
