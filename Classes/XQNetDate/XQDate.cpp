//
//  XQDate.cpp
//  OnceAgain
//
//  Created by xiaohai on 14-4-29.
//
//

#include "XQDate.h"
#include "NetPacket.h"
#include "NetCallBack.h"
void  XQDate::SaveDate(void *pDataPkg, CCObject* target, SEL_MyEvent callfun) {
    //读取数据，以key，value形势组成MyXQDate,并存入myCacheList中，key为msg_type + msg_code,例如，请求为1，2，则key为字符串“12”；
    NetCallBack::setCallBack(target, callfun);
    CResponsePacket* pPkt = (CResponsePacket*)pDataPkg;
    unsigned int unMsgType = pPkt->getMsgType();
    unsigned int unMsgCode = pPkt->getMsgCode();
    
    CSJson::Value root ;
    if (!CJsonHelper::getJsonFromString(pPkt->getContent().c_str(),root)) {
        
    }	
   
    CCString str;
    str.initWithFormat("%d%d",unMsgType, unMsgCode);
    if (unMsgType == 6 && unMsgCode == 5) {
        str.initWithFormat("%d%d%d",unMsgType, unMsgCode, GameType);
    }
    if (HaveDate(str.getCString())) {
        for (int i = 0; i < myCacheList.size(); i++) {
            if (myCacheList[i].keyId == str.getCString()) {
                myCacheList[i].root = root;
            }
        }
    }
    else {
        MyXQDate data;
        data.keyId = str.getCString();
        data.root = root;
        myCacheList.push_back(data);
    }
    
    NetCallBack::doCallBack();
}

void XQDate::setGameType(int GameType1) {

    GameType = GameType1;
}

CSJson::Value XQDate::GetDate(std::string key) {
    for (int i = 0; i < myCacheList.size(); ++i){
		if(myCacheList[i].keyId == key){
			return myCacheList[i].root;
		}
	}
    //通过对应的key获取CCDictionary
    return NULL;
}

bool XQDate::HaveDate(std::string key){
    for (int i = 0; i < myCacheList.size(); i++){
		if(myCacheList[i].keyId == key){
			return true;
		}
	}
	return false;
}

int XQDate::getValueForInt(CSJson::Value root, std::string key) {
    return root[key].asInt();
}

float XQDate::getValueForFloat(CSJson::Value root, std::string key) {
//    CSJson::Value& val = root;
    return root[key].asFloat();
}

double XQDate::getValueForDouble(CSJson::Value root, std::string key) {
//    CSJson::Value& val = root;
    return root[key].asDouble();
}

std::string XQDate::getValueForString(CSJson::Value root, std::string key){
//    CSJson::Value& val = root;
    return root[key].asString();
}


void XQDate::CompleteTask(int gameid, int taskId) {
    CCString str1;
    str1.initWithFormat("%d%d%d", 6, 4, gameid);
    for (int j = 0; j < myCacheList.size(); j++){
        if(myCacheList[j].keyId == str1.getCString()){
                CSJson::Value root = myCacheList[j].root;
                for (int k = 0; k < root.size(); k++) {
                    CSJson::Value& val = root[k];
                    if (val["taskid"].asInt() == taskId) {
                        val["taskcomplete"] = CSJson::Value(1);
        
                    }
                }
            }
        }
}
