//
// GameLinkerGuideLayer.h
// OnceAgain
//
// Created by xiaohai on 14-5-6.
//
//

#ifndef __OnceAgain__GameLinkerGuideLayer__
#define __OnceAgain__GameLinkerGuideLayer__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;
USING_NS_CC;

class GameLinkerGuideLayer : public CCLayer
{
public:
    GameLinkerGuideLayer(){};
    ~GameLinkerGuideLayer(){};
    static CCScene* createScene();
    virtual bool init();
//    virtual void registerWithTouchDispatcher();
//    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    CREATE_FUNC(GameLinkerGuideLayer);
    
private:
    void initData();
    void BindingUIItems();
    void loopAnimaton();
    
    void lineHind();
    
    void checkFingerPoint(float a);
    
    
public:
    //外部调用接口
    
    
private:
    //绑定ui
    UILayer *ul;
    UIImageView *finger;
    UIImageView *line_1;
    UIImageView *line_2;
    UIImageView *endImg;
    
    CCPoint fingerPoint;
    
private:
    //网络请求接口
    
private:
    //网络数据
    
};

#endif /* defined(__OnceAgain__GameLinkerGuideLayer__) */