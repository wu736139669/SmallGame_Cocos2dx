//
//  GameLayerChallenge.h
//  OnceAgain
//
//  Created by mac on 14-4-25.
//
//

#ifndef __OnceAgain__GameLayerChallenge__
#define __OnceAgain__GameLayerChallenge__

#include "cocos2d.h"
#include "CCScrollviewSimple.h"
#include "GameLayer_Base.h"
#include "GameCommon.h"
USING_NS_CC;
class GameLayerChallenge : public GameLayer_Base ,public CCScrollViewSimpleDelegate
{
    DECLARE_DLG_ID();
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static CCScene* scene();
    
    virtual void onEnter();
    
    virtual bool onPackageFilter(void *pDataPkg);
    
    GameLayerChallenge();
    ~GameLayerChallenge();
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(GameLayerChallenge);
    //点击系统设置上面的关闭.
    void closeSysSetCallback(CCObject* pSender);
    //选项卡按钮点击.
    void btnCallback(CCObject* pSender);
    //设置选项卡状态.
    void setState(int type);
    //点击应战.
    void battleBtnCallback(CCObject* pSender);
    //设置按钮的方法.
    void addSureCallbackFunc(CCObject* target, SEL_ReleaseEvent callfun);
public:
    
    virtual void scrollViewDidScroll(CCScrollviewSimple* view);
    
    
    virtual void scrollViewDidZoom(CCScrollviewSimple* view);
    
private:
    
    
    CCScrollviewSimple *showScrollView;
    
    //发起按钮1
    UIButton* proposeBtn1;
    //发起按钮2
    UIButton* proposeBtn2;
    
    //收到按钮1
    UIButton* reciveBtn1;
    //收到按钮2
    UIButton* reciveBtn2;
    
    //收到挑战列表.
    UILayer *layerReceive;
    //发起挑战列表.
    UILayer *layerSend;
    
    UILayer* ul;
    
    CCObject*       m_pListener;
    SEL_CallFuncO    m_pfnSelector;
};

#endif /* defined(__OnceAgain__GameLayerChallenge__) */
