//
//  Scene_Welcome.h
//  OnceAgain
//
//  Created by xiaohai on 14-2-21.
//
//
/*
 *
 *       Scene_Welcome
 *
 */

#ifndef OnceAgain_Scene_Welcome_h
#define OnceAgain_Scene_Welcome_h

#include "cocos2d.h"
#include "GameSharelist.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#include "Constant.h"
#include "Scene_GameList.h"
#include "GameShare_Texture.h"
#include "GameShare_Global.h"
#include "GameShare_Data.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#include "QQInterface.h"
#include "SinaInterface.h"


#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#endif

USING_NS_CC;
USING_NS_CC_EXT;
class Scene_Welcome : public CCLayer

{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    virtual void onEnter();
    //    virtual void onExit();
    virtual void onEnterTransitionDidFinish();
    
    // implement the "static node()" method manually
    CREATE_FUNC(Scene_Welcome);
private:
    //click to start game with no login
    void startGameNoLogin(CCObject* object);
    void startGameQQLogin(CCObject* object);
    void startGameSinaLogin(CCObject* object);
    
    void qqLoginSuccess(CCObject* object);
    void sinaLoginSuccess(CCObject* object);
    
    void loginFail(CCObject* object);
    //设置当前按钮的状态
    void setBtnState(bool isLogin);
	void requestLoadData();
    UILayer* ul;
};

#endif
