//
//  GameLayer_Alert.h
//  OnceAgain
//
//  Created by mac on 14-3-24.
//
//

#ifndef __OnceAgain__GameLayer_Alert__
#define __OnceAgain__GameLayer_Alert__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "GameLayer_Base.h"
//添加命名空间
USING_NS_CC_EXT;
USING_NS_CC;
enum Type{
    Type_Noraml = 1,
    Type_OnlySure = 2
};
class GameLayer_Alert : public GameLayer_Base
{
public:
    static GameLayer_Alert* creatWithOnlySure(int type = Type_Noraml);
    virtual bool init(int type = Type_Noraml);
    virtual void setVisible(bool visible);
    ~GameLayer_Alert(void);
    GameLayer_Alert(void);
    
    //设置显示的字符.
    void setText(const char* str);
    //
    void setSize(int size);
    //设置确定按钮的tag
    
    void setSureBtnTag(int tag);
    //设置确定的方法.
    void setSureCallbackFunc(CCObject* target, SEL_CallFuncO callfun);
//    CREATE_FUNC(GameLayer_Alert);
private:
    UILayer* alertUl;
    //点击确定按钮.
    void sureBtnCallback(CCObject* pSender);
    //点击取消按钮.
    void cancelBtnCallback(CCObject* pSender);
    //点击关闭按钮.
    void closeBtnCallback(CCObject* pSender);
    
    CCObject*       m_pListener;
    SEL_CallFuncO    m_pfnSelector;
    
};

#endif /* defined(__OnceAgain__GameLayer_Alert__) */
