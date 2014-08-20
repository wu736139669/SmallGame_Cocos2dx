//
// PlayerInfoAndFightLayer.h
// OnceAgain
//
// Created by xiaohai on 14-5-9.
//
//

#ifndef __OnceAgain__PlayerInfoAndFightLayer__
#define __OnceAgain__PlayerInfoAndFightLayer__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;
USING_NS_CC;

class PlayerInfoAndFightLayer : public CCLayer
{
public:
    PlayerInfoAndFightLayer(){};
    ~PlayerInfoAndFightLayer(){};
    static CCScene* createScene();
    virtual bool init();
    virtual void onExit();
    CREATE_FUNC(PlayerInfoAndFightLayer);
    
private:
    void initData();
    void BindingUIItems();
 
    void creatLayers();
    
    //按钮点击事件
    void ButtonClickCallBack(CCObject *p);
    
    //判断按钮状态并显示
    void judgeStatu();
public:
    //外部调用接口
    
    
private:
    //绑定ui
    UILayer *ul;
    
    UIButton *Button_1;//个人战绩
    UIButton *Button_2;//个人资料
    UIButton *Btn_close;
    
    UIImageView *TextImage_1;//个人战绩状态图
    UIImageView *TextImage_2;//个人资料状态图
    
    UIPanel *InfoNode;
    UIPanel *FightNode;
    
    
private:
    //网络请求接口
    
private:
    //网络数据
    
};

#endif /* defined(__OnceAgain__PlayerInfoAndFightLayer__) */