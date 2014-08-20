//
// GameTakeRewardLayer.h
// OnceAgain
//
// Created by xiaoqiang on 14-5-23.
//
//

#ifndef __OnceAgain__GameTakeRewardLayer__
#define __OnceAgain__GameTakeRewardLayer__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;
USING_NS_CC;

class GameTakeRewardLayer : public CCLayer
{
public:
    GameTakeRewardLayer();
    ~GameTakeRewardLayer();
    static CCScene* createScene();
    virtual bool init();
    CREATE_FUNC(GameTakeRewardLayer);
    
private:
    void initData();
    void BindingUIItems();
 
    
public:
    //外部调用接口
    
    void setCallBack(CCObject*p , SEL_CallFuncO call);
private:
    //绑定ui
    UILayer *ul;
    
    std::vector<UIImageView*>imgList;
    std::vector<CCSprite*>myImgList;
    std::vector<int>idlist;
private:

    CCObject *target;
    SEL_CallFuncO callback;
    
    int selectorPic;
    
    void touchTabelCallBack(CCObject *p);
    void picRunAction();
    void picClick(CCObject *p);
    
};

#endif /* defined(__OnceAgain__GameTakeRewardLayer__) */