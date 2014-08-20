//
//  GameLayer_Task.h
//  OnceAgain
//
//  Created by mac on 14-3-25.
//
//

#ifndef __OnceAgain__GameLayer_Task__
#define __OnceAgain__GameLayer_Task__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "GameLayer_Base.h"
//添加命名空间
USING_NS_CC_EXT;
USING_NS_CC;
class GameLayer_Task : public GameLayer_Base
{
public:
    virtual bool init(void);
    virtual void setVisible(bool visible);
    ~GameLayer_Task(void);
    GameLayer_Task(void);
    CREATE_FUNC(GameLayer_Task);
    //设置确定的方法.
    void setSureCallbackFunc(CCObject* target, SEL_CallFuncO callfun);
private:
    UILayer* taskUl;
    
    //点击确定按钮.
    void sureBtnCallback(CCObject* pSender);
    
    CCObject*       m_pListener;
    SEL_CallFuncO    m_pfnSelector;
    
};

#endif /* defined(__OnceAgain__GameLayer_Task__) */
