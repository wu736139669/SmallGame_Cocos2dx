//
//  SysInfoCell.h
//  OnceAgain
//
//  Created by mac on 14-4-24.
//
//

#ifndef __OnceAgain__SysInfoCell__
#define __OnceAgain__SysInfoCell__

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
enum InfoType {
    InfoTypeSendRice = 1,
    InfoTypeChallenge = 2,
    };
class SysInfoCell : public CCLayer{
    
public:
    SysInfoCell();
    ~SysInfoCell();
    CREATE_FUNC(SysInfoCell);
    virtual bool init();
    
    CC_SYNTHESIZE(int, gameType, GameType);
    //设置排行.
    void setType(InfoType type);
    //设置名字
    void setName(const char* name);
    //设置头像
    void setAvatar(const char* avatarUrl);
    //设置介绍
    void setInfo(const char* info,int size);
    //设置按钮的方法.
    void addSendCallbackFunc(CCObject* target, SEL_ReleaseEvent callfun);
private:
    UILayer* cellLyaer;
    CCSprite* scoreSprite;
};

#endif /* defined(__OnceAgain__SysInfoCell__) */
