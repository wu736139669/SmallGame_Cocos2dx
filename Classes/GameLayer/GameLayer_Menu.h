//
//  GameLayer_Menu.h
//  OnceAgain
//
//  Created by mac on 14-3-25.
//
//

#ifndef __OnceAgain__GameLayer_Menu__
#define __OnceAgain__GameLayer_Menu__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "GameLayer_Base.h"
#include "GameCommon.h"
//添加命名空间
USING_NS_CC_EXT;
USING_NS_CC;
class GameLayer_Menu : public GameLayer_Base
{
    DECLARE_DLG_ID();
public:
    virtual bool init(void);
    virtual void setVisible(bool visible);
    ~GameLayer_Menu(void);
    GameLayer_Menu(void){gameMenu=NULL;};
    CREATE_FUNC(GameLayer_Menu);
    
    //设置未登陆状态.
    void setNoLogin(bool visiable);
    
    //增加设置按钮方法.
    void addSetBtnCallback(CCObject* target, SEL_CallFuncO callfun);
    //增加任务按钮方法.
    void addTaskBtnCallback(CCObject* target, SEL_CallFuncO  callfun);
    //增加消息按钮方法
    void addSysInfoCallback(CCObject* target, SEL_CallFuncO  callfun);
    //增加好友按钮
    void addFriendCallBack(CCObject* target, SEL_CallFuncO  callfun);
    //排行榜
    void addRankCallBack(CCObject* target, SEL_CallFuncO callfun);
    
    //
    virtual bool onPackageFilter(void *pDataPkg);
    
    //设置消息数量.
    void setInfoNum();
    
private:
    UILayer* gameMenu;
    
    
    //点击确定按钮.
    void sureBtnCallback(CCObject* pSender);
    

    
};
#endif /* defined(__OnceAgain__GameLayer_Menu__) */
