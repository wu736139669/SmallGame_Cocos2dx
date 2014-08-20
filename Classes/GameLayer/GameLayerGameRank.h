//
//  GameLayerGameRank.h
//  OnceAgain
//
//  Created by mac on 14-4-24.
//
//

#ifndef __OnceAgain__GameLayerGameRank__
#define __OnceAgain__GameLayerGameRank__

#include "cocos2d.h"
#include "CCScrollviewSimple.h"
#include "GameLayer_Base.h"
#include "GameCommon.h"
USING_NS_CC;
class GameLayerGameRank : public GameLayer_Base, public CCScrollViewSimpleDelegate
{
    DECLARE_DLG_ID();
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static CCScene* scene();
    
    virtual void onEnter();
    
    virtual bool onPackageFilter(void *pDataPkg);
    
    GameLayerGameRank();
    ~GameLayerGameRank();
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(GameLayerGameRank);
    //点击系统设置上面的关闭.
    void closeSysSetCallback(CCObject* pSender);
    
    //查看好友对战列表.
    void seeListCallback(CCObject* pSender);
    
    //添加挑战按钮事件.
    void challengeBtnCallbackFunc(CCObject* pSender);
    //设置按钮的方法.
    void addSureCallbackFunc(CCObject* target, SEL_ReleaseEvent callfun);
public:
    
    virtual void scrollViewDidScroll(CCScrollviewSimple* view);
    
    
    virtual void scrollViewDidZoom(CCScrollviewSimple* view);
    
private:
    
    
    CCScrollviewSimple *showScrollView;
    
    UILayer* ul;
    CCObject*       m_pListener;
    SEL_ReleaseEvent    m_pfnSelector;
    
    
    void requestPkInfoCallBack(CCObject *p);
    
    int modelCount;
    int sendCount;
    int pkrecvCount;
};

#endif /* defined(__OnceAgain__GameLayerGameRank__) */
