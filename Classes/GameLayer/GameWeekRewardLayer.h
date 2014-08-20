//
// GameWeekRewardLayer.h
// OnceAgain
//
// Created by xiaohai on 14-5-22.
//
//

#ifndef __OnceAgain__GameWeekRewardLayer__
#define __OnceAgain__GameWeekRewardLayer__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;
USING_NS_CC;

class GameWeekRewardLayer : public CCLayer
{
public:
    GameWeekRewardLayer();
    ~GameWeekRewardLayer();
    static CCScene* createScene();
    virtual bool init();
    CREATE_FUNC(GameWeekRewardLayer);
    
private:
    void initData();
    void BindingUIItems(CCObject *p);
 
    
public:
    //外部调用接口
    
    
private:
    //绑定ui
    UILayer *ul;
    
    void touchWindow(CCObject* p);
    void getWeekRewardBtnClick(CCObject *p);
    
private:
    //网络请求接口
    
private:
    //网络数据
    
};

#endif /* defined(__OnceAgain__GameWeekRewardLayer__) */