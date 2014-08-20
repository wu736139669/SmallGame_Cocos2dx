//
//  GameDemo.h
//  OnceAgain
//
//  Created by mac on 14-3-10.
//
//

#ifndef __OnceAgain__GameDemo__
#define __OnceAgain__GameDemo__

#include "cocos2d.h"
#include "GameShare_Scene.h"

class GameDemo : public GameShare_Scene
{
public:
    GameDemo(void){};
    ~GameDemo(void);
    virtual bool init();
    static cocos2d::CCScene* scene();
    
    CREATE_FUNC(GameDemo);
    
private:
//    //设置背景。
//    void initBgView(void);
//    //开始游戏.
//    void startGame(float dt=1.0);
//    //时间结束的处理
//    virtual void msgHanlde_GameTimeOut(CCObject* obj);
//    //炸弹能量满的通知.
//    virtual void msgHanlde_BoomFull(CCObject* obj);
};

#endif /* defined(__OnceAgain__GameDemo__) */
