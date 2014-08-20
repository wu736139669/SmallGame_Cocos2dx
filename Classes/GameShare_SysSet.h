//
//  GameShare_SysSet.h
//  OnceAgain
//
//  Created by mac on 14-3-13.
//
//

#ifndef __OnceAgain__GameShare_SysSet__
#define __OnceAgain__GameShare_SysSet__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
//添加命名空间
USING_NS_CC_EXT;
USING_NS_CC;
class GameShare_SysSet : public CCLayer
{
public:
    virtual bool init(void);
    virtual void setVisible(bool visible);
    ~GameShare_SysSet(void);
    GameShare_SysSet(void){};
    CREATE_FUNC(GameShare_SysSet);
private:
    UILayer* sysSet;
    
    //点击系统设置上面的关闭.
    void closeSysSetCallback(CCObject* pSender);
    //点击退出登陆按钮.
    void logOutCallback(CCObject* pSender);
    
    //音乐开关按钮.
    void musicSwitchCallBack(CCObject* pSender);
    //音效声音开关
    void musicEffectSwitchCallBack(CCObject* pSender);
    
};
#endif /* defined(__OnceAgain__GameShare_SysSet__) */
