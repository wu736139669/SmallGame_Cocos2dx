//
// GameNewLinkerItems.h
// OnceAgain
//
// Created by xiaohai on 14-5-19.
//
//

#ifndef __OnceAgain__GameNewLinkerItems__
#define __OnceAgain__GameNewLinkerItems__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;
USING_NS_CC;

class GameNewLinkerItems : public CCSprite ,public CCTouchDelegate
{
public:
    static CCScene* createScene();
    virtual bool init();
    CREATE_FUNC(GameNewLinkerItems);
    
private:
    void picRunClickAction();
    void picLinkRight();
    
public:
    //外部调用接口
    void createPicByTag(int tag, bool isboom, int picKind);
    //被点击
    void picBeClick();
    int getItemType();
    //所有动作停止
    void stopAllAction();
    //获取连线成功状态
    bool getLinkStatus(){return isLinkOk;};
    //播放连线成功动画
    void doLinkOKAction();
    void setOnLinkFalse() {isOnLine = false;};
    bool getOnLinkStatus(){return isOnLine;};
    int getPicType();
private:
    //内部数据
    CCSprite *pic;
    CCSprite *pic_face;
    CCSprite *pic_normol;
    CCSprite *pic_onClick;
    CCSprite *boom_pic;
    int type;
    int picType;
    bool isLinkOk;//是否连线成功
    bool isOnLine;//是否处于连线状态
    bool isBoomMap;
private:
    //网络请求接口
    
private:
    //网络数据
    
};

#endif /* defined(__OnceAgain__GameNewLinkerItems__) */