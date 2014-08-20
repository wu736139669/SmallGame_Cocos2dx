//
//  GameLayer_DayLogin.h
//  OnceAgain
//
//  Created by mac on 14-3-24.
//
//

#ifndef __OnceAgain__GameLayer_DayLogin__
#define __OnceAgain__GameLayer_DayLogin__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "GameLayer_Base.h"
//添加命名空间
USING_NS_CC_EXT;
USING_NS_CC;
class GameLayer_DayLogin : public GameLayer_Base
{
public:
    virtual bool init(void);
    virtual void setVisible(bool visible);
    void setCallBcak(CCObject *p, SEL_CallFunc call);
    
    ~GameLayer_DayLogin(void);
    GameLayer_DayLogin(void){dayLogin=NULL;};
    CREATE_FUNC(GameLayer_DayLogin);
private:
    UILayer* dayLogin;
    
    //点击确定按钮.
    void sureBtnCallback(CCObject* pSender);
    //显示每日登陆到达的状态.
    void setShowState();
    
    void DoCallBack();
    
    CCObject *target;
    SEL_CallFunc callBack;
};

#endif /* defined(__OnceAgain__GameLayer_DayLogin__) */
