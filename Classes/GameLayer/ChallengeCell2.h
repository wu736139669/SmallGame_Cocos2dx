//
//  ChallengeCell2.h
//  OnceAgain
//
//  Created by mac on 14-4-28.
//
//

#ifndef __OnceAgain__ChallengeCell2__
#define __OnceAgain__ChallengeCell2__

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
class ChallengeCell2 : public CCLayer{
    
public:
    ChallengeCell2();
    ~ChallengeCell2();
    CREATE_FUNC(ChallengeCell2);
    virtual bool init();
    
    //设置名字
    void setName(const char* name);
    //设置分数.
    void setScore(int score);
    //设置图片.
    void setAvatarImg(const char* imgUrl);
    //设置介绍
//    void setInfo(const char* info);
    //设置时间
    void setTime(long time);
    //设置按钮的方法.
    void addSendCallbackFunc(CCObject* target, SEL_ReleaseEvent callfun);
private:
    UILayer* cellLyaer;
};

#endif /* defined(__OnceAgain__ChallengeCell2__) */
