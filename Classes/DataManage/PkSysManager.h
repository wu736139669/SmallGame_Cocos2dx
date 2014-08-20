//
//  PkSysManager.h
//  OnceAgain
//
//  Created by mac on 14-4-28.
//
//

#ifndef __OnceAgain__PkSysManager__
#define __OnceAgain__PkSysManager__

#include "cocos2d.h"
#include <string>
#include "Singleton.h"
#include "JsonHelper.h"

enum eGamePkType {
    PkTypeNormal = 1,           //普通模式.
    PkTypeSend = 2,             //发出pk模式.
    PkTypeReceive = 3,          //接受pk模式.
    };
struct sPKInfo {
    int score;                  //分数.
    std::string avatarUrl;      //头像
    std::string pkName;         //姓名.
    int pkId;                   //id
    int time;                   //过期时间.
    std::string detail;         //描述.
};
typedef std::vector<sPKInfo> VEC_SPKINFO;
class CBasePacket;

class CPkSysManager : public CSingleton<CPkSysManager>{
    
public:
    CPkSysManager();
    ~CPkSysManager();
    
    VEC_SPKINFO& getSendPk(){return mVecSendPk;};
    VEC_SPKINFO& getReceivePk(){return mVecReceivePk;};
    void parseNetData(CBasePacket* pBasePacket);
    virtual void reset();
    
    //发送pk.
    void RequestSendPk(int receiveId , int gameId, int score);
    //获取pk.
    void RequestReceivePk(int infoId, int score);
    

private:
    
    VEC_SPKINFO mVecSendPk;
    VEC_SPKINFO mVecReceivePk;
//    VEC_SPKINFO mVec
public:
    eGamePkType pkType;             //pk类型
    int pkId;                       //pkid
    int playerId;                   //pk对象id
    int playerScore;                //对方的分数
    int myScore;
	int iGold;						//
    std::string playerUrl;          //对方的头像地址
    std::string playerName;        //对方的名字
};
#endif /* defined(__OnceAgain__PkSysManager__) */
