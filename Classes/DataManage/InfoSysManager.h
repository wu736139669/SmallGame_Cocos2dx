//
//  InfoSysManager.h
//  OnceAgain
//
//  Created by mac on 14-4-28.
//
//

#ifndef __OnceAgain__InfoSysManager__
#define __OnceAgain__InfoSysManager__

#include "cocos2d.h"
#include <string>
#include "Singleton.h"
#include "JsonHelper.h"

//消息类型。
enum eInfoType {
    InfoSysType = 1,            //系统类型.
    InfoRiceType =2,             //体力.
    InfoSendPkType = 3,             //pk类型.
    InfoRecPkType = 4,              //接收pk
    };
struct sInfoSys {
    std::string name;           //姓名.
    std::string avatarImg;      //头像.
    std::string detail;         //描述.
    int gameType;               //游戏类型
    int infoId;                 //消息id.
    eInfoType type;             //消息类型.
    
};
typedef std::vector<sInfoSys> VEC_INFOSYS;
class CBasePacket;
class CInfoSysManager : public CSingleton<CInfoSysManager>{

public:
    CInfoSysManager();
    ~CInfoSysManager();
    
    VEC_INFOSYS& getInfoSys(){return mVecInfoSys;};
    
    void parseNetData(CBasePacket* pBasePacket);
    virtual void reset();
    
    //获取消息.
    void RequestGetInfo();
    //获取体力消息.
    void RequestGetRiceInfo();
    //阅读体力消息.
    void RequestReadRiceInfo(int infoId);
    //获取pk消息
    void RequestGetPkInfo();
    //获取被pk消息
    void RequestGetBePkInfo();
    //阅读pk消息
    void RequestReadPkInfo(int infoId);
    //获取通知数量
    void RequestGetInfoNum(void);
    //从后端获取能够邀请的好友列表
    void RequestFriendListFromSql();
private:
    
    VEC_INFOSYS mVecInfoSys;
};
#endif /* defined(__OnceAgain__InfoSysManager__) */
