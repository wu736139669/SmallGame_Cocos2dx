//
//  GameLayerSysInfo.h
//  OnceAgain
//
//  Created by mac on 14-4-24.
//
//

#ifndef __OnceAgain__GameLayerSysInfo__
#define __OnceAgain__GameLayerSysInfo__

#include "cocos2d.h"
#include "CCScrollviewSimple.h"
#include "GameLayer_Base.h"
#include "GameCommon.h"
USING_NS_CC;
class GameLayerSysInfo : public GameLayer_Base ,public CCScrollViewSimpleDelegate
{
    DECLARE_DLG_ID();
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static CCScene* scene();
    
    GameLayerSysInfo();
    ~GameLayerSysInfo();
    
    virtual void onEnter();
    
    virtual bool onPackageFilter(void *pDataPkg);
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(GameLayerSysInfo);
    //点击系统设置上面的关闭.
    void closeSysSetCallback(CCObject* pSender);
    
    //接受赠送的体力
    void receiveRiceCallback(CCObject* pSender);
    
    //跳转到列表界面.
    void gotoPkList(CCObject* pSender);
    //成功领取体力.
    void receiveRiceSuccess(CCObject* pSender);
    //获取收到消息界面
	void getNewsList(CCObject* pSender);

    void reloadView();
public:
    
    virtual void scrollViewDidScroll(CCScrollviewSimple* view);
    
    
    virtual void scrollViewDidZoom(CCScrollviewSimple* view);
    
private:
    
    
    CCScrollviewSimple *showScrollView;
    UILayer *layer;
    UILayer* ul;
    int selectTag;
};

#endif /* defined(__OnceAgain__GameLayerSysInfo__) */
