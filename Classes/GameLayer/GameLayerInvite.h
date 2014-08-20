//
//  GameLayerInvite.h
//  OnceAgain
//
//  Created by mac on 14-5-6.
//
//

#ifndef __OnceAgain__GameLayerInvite__
#define __OnceAgain__GameLayerInvite__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCScrollviewSimple.h"
#include "GameLayer_Base.h"
#include "GameCommon.h"
USING_NS_CC;
USING_NS_CC_EXT;
class GameLayerInvite : public GameLayer_Base ,public CCScrollViewSimpleDelegate{
    DECLARE_DLG_ID();
public:
    GameLayerInvite();
    ~GameLayerInvite();
    
    virtual bool init();
    virtual void onEnter();
    virtual bool onPackageFilter(void *pDataPkg);
    CREATE_FUNC(GameLayerInvite);
    //点击上面的关闭.
    void closeCallback(CCObject* pSender);
    //设置按钮的方法.
    void addSureCallbackFunc(CCObject* target, SEL_ReleaseEvent callfun);
    //确认按钮点击.
    void sureBtnCallback(CCObject* pSender);
    //设置名字.
    void setName(std::string name);
    //设置图片
    void setAvatar(std::string avatarUrl);
    //
    void addBtnClick(CCObject* pSender);

    void creatScrollView();
    //
    virtual void update(float delta);
public:
    virtual void scrollViewDidScroll(CCScrollviewSimple* view){};
    virtual void scrollViewDidZoom(CCScrollviewSimple* view){};
    
private:
    CCObject*       m_pListener;
    SEL_CallFuncO    m_pfnSelector;
    
    UILayer* ul;
    CCScrollviewSimple *showScrollView;
    
    void refreshCallBack(CCObject *p);
    //是否正在获取好友列表
    bool isGetFriendList;
    
};

#endif /* defined(__OnceAgain__GameLayerInvite__) */
