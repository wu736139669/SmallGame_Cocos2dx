//
//  FirendManager.h
//  OnceAgain
//
//  Created by mac on 14-4-23.
//
//

#ifndef __OnceAgain__FirendManager__
#define __OnceAgain__FirendManager__

#include "cocos2d.h"
#include <string>
#include "Singleton.h"
#include "JsonHelper.h"

//单个游戏排行的cell数据
struct sGameRank {
    int rank;                   //排名
    int playercanrecvpower;     //是否可以送.
    int powernoticeexpiretime;  //过期时间.
    std::string avatarUrl;      //头像url
    std::string name;           //姓名
    bool canPk;                 //是否可以pk
    int score;                  //分数.
    int playerId;               //玩家id.
    int appType;                
    std::string appid;          //用户的社交id
};
typedef std::vector<sGameRank> VEC_GAMERANK;
class CBasePacket;

class CFriendManager : public CSingleton<CFriendManager>{
    
public:
    CFriendManager();
    
    ~CFriendManager();
    
public:
    
    //获得单款游戏的排行.
    VEC_GAMERANK& getGameRankTmpData(){return mVecGameRank;};
    //获得总分的排行.
    VEC_GAMERANK& getAllRankTmpData(){return mVecAllRank;};
    //获得好友列表.
    VEC_GAMERANK& getFriend(){return mVecFriend;};
    //通过id获取信息.
    sGameRank* getInfoById(int playerId);
    
    //获取从后端而来的好友列表
     VEC_GAMERANK& getFriendListFromSql(){return mVecFriendFromSql;};
    
    void parseNetData(CBasePacket* pBasePacket);
    virtual void reset();
    
    //注册好友
    void RequestSetFriend(int apptype, const char* userList);
    //获取指定游戏好友排行榜
    void RequestGetRankByGame(int gameId);
    //获取总分排行.
    void RequestGetAllRank(void);
private:
    //单款游戏排行列表.
    VEC_GAMERANK mVecGameRank;
    //总分排行
    VEC_GAMERANK mVecAllRank;
    //好友列表
    VEC_GAMERANK mVecFriend;
    //后端而来的好友列表
    VEC_GAMERANK mVecFriendFromSql;
};
#endif /* defined(__OnceAgain__FirendManager__) */
