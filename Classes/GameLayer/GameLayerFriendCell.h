//
//  GameLayerFriendCell.h
//  OnceAgain
//
//  Created by mac on 14-4-17.
//
//

#ifndef __OnceAgain__GameLayerFriendCell__
#define __OnceAgain__GameLayerFriendCell__

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
enum FriendSendType {
    FriendSendTypeSend = 1,
    FriendSendTypeNoSend = 2,
    FriendSendTypeIsSend = 3,
    FriendChallenge = 4
    };
class GameLayerFriendCell : public CCLayer{
  
    
public:
    GameLayerFriendCell();
    ~GameLayerFriendCell();
    CREATE_FUNC(GameLayerFriendCell);
    virtual bool init();
    virtual void onEnter();
    //设置排行.
    void setRank(int rank);
    //设置名字
    void setName(const char* name);
    //设置分数
    void setScore(int score);
    //设置类型
    void setSendType(FriendSendType type, int time=0);
    //设置按钮的方法.
    void addSendCallbackFunc(CCObject* target, SEL_ReleaseEvent callfun);
    //设置图片.
    void setAvatarImg(const char* imgUrl);
    
    void addMySelfCallBack(CCObject* target, SEL_ReleaseEvent callfun, int tag);
    
    void changePicType(int tag);
    
    //点击进入个人资料.
    void setInfoCallback(CCObject* targer, SEL_CallFunc callfun);
    void setPlayerId(int num);
    
    void setBtnType();
    
    void setTiemCount(int dt);
    void beginTiemCountdown();
    void timeCountCallBack();
    
    void getPlayerInfo(CCObject *p);
    
private:
    UILayer* cellLyaer;
    CCSprite* scoreSprite;
    
    CCObject *target;
    SEL_CallFuncND callback;
    
    CCObject *target_1;
    SEL_CallFunc callBack_1;
    
    int timeLess;
    int playerId;
    
    void getPlayerInfoCallBack(CCObject *p);
};

#endif /* defined(__OnceAgain__GameLayerFriendCell__) */
