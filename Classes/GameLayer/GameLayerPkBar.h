//
//  GameLayerPkBar.h
//  OnceAgain
//
//  Created by mac on 14-4-30.
//
//

#ifndef __OnceAgain__GameLayerPkBar__
#define __OnceAgain__GameLayerPkBar__

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
class GameLayerPkBar : public CCLayer {
    
public:
    GameLayerPkBar();
    ~GameLayerPkBar();
    
    virtual bool init();
    CREATE_FUNC(GameLayerPkBar);
    //设置按钮的方法.
    void addSureCallbackFunc(CCObject* target, SEL_ReleaseEvent callfun);
    //确认按钮点击.
    void sureBtnCallback(CCObject* pSender);
    //设置名字.
    void setName(std::string name);
    //设置图片
    void setAvatar(std::string avatarUrl);
    //设置类型，应战还是挑战
    void setType(int type=0);
private:
    CCObject*       m_pListener;
    SEL_CallFuncO    m_pfnSelector;
    
    UILayer* ul;
};
#endif /* defined(__OnceAgain__GameLayerPkBar__) */
