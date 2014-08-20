//
// GameMemoryGuideLayer.h
// OnceAgain
//
// Created by xiaohai on 14-5-6.
//
//

#ifndef __OnceAgain__GameMemoryGuideLayer__
#define __OnceAgain__GameMemoryGuideLayer__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;
USING_NS_CC;

class GameMemoryGuideLayer : public CCLayer
{
public:
    GameMemoryGuideLayer(){};
    ~GameMemoryGuideLayer(){};
    static CCScene* createScene();
    virtual bool init();
    CREATE_FUNC(GameMemoryGuideLayer);
    
private:
    void initData();
    void BindingUIItems();
    void loopAnmitaton();
    void anmitionBegin();//动画开始
    
    void allCardClose();
    void closeCard(CCNode*p, void* num);
    void openCard(CCNode*p, void* num);
    void openCardByNum(CCNode*p, void* num);
    
public:
    //外部调用接口
    
    
private:
    //绑定ui
    UILayer *ul;
    
    std::vector<UIImageView*>cardList;
    UIImageView *finger;
    
    CCPoint fingerPoint;
    
private:
    //网络请求接口
    
private:
    //网络数据
    
};

#endif /* defined(__OnceAgain__GameMemoryGuideLayer__) */