//
// FightItemLayer.h
// OnceAgain
//
// Created by xiaohai on 14-5-9.
//
//

#ifndef __OnceAgain__FightItemLayer__
#define __OnceAgain__FightItemLayer__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;
USING_NS_CC;

class FightItemLayer : public CCLayer
{
public:
    FightItemLayer(){};
    ~FightItemLayer(){};
    static CCScene* createScene();
    virtual bool init();
    CREATE_FUNC(FightItemLayer);
    
private:
    void initData();
    void BindingUIItems();
 
    CCSprite* getSpriteByScore(long score);
public:
    //外部调用接口
    void setInfo(CSJson::Value);
    
private:
    //绑定ui
    UILayer *ul;
    UIImageView *Gameicon;
    UILabel *GameName;
    UILabel *ScoreNumber;
private:
    //网络请求接口
    
private:
    //网络数据
    
};

#endif /* defined(__OnceAgain__FightItemLayer__) */