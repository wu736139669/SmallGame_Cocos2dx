//
//  GameRankCell.h
//  OnceAgain
//
//  Created by mac on 14-4-24.
//
//

#ifndef __OnceAgain__GameRankCell__
#define __OnceAgain__GameRankCell__

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
class GameRankCell : public CCLayer{
    
public:
    GameRankCell();
    ~GameRankCell();
    CREATE_FUNC(GameRankCell);
    virtual bool init();
    
    //设置排行.
    void setRank(int rank);
    //设置名字
    void setName(const char* name);
    //设置分数
    void setScore(int score);
    //设置按钮的方法.
    void addSendCallbackFunc(CCObject* target, SEL_ReleaseEvent callfun);
    //设置图片.
    void setAvatarImg(const char* imgUrl);
    
private:
    UILayer* cellLyaer;
    CCSprite* scoreSprite;

};

#endif /* defined(__OnceAgain__GameRankCell__) */
