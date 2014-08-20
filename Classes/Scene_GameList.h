//
//  Scene_GameList.h
//  OnceAgain
//
//  Created by xiaohai on 14-2-21.
//
//

#ifndef OnceAgain_Scene_GameList_h
#define OnceAgain_Scene_GameList_h

#include <iostream>
#include "cocos2d.h"
#include "CocosGUI.h"
#include "cocos-ext.h"

#include "Constant.h"
#include "GameTableLayer.h"
#include "GameShare_SysSet.h"
#include "GameLayer_DayLogin.h"
#include "GameLayer_Resource.h"
#include "GameLayer_Menu.h"
#include "GameLayer_GoldMarket.h"
#include "GameLayer_DiamondMarket.h"
#include "GameLayer_RiceMarket.h"
#include "GameShare_Global.h"

//添加命名空间
USING_NS_CC_EXT;
USING_NS_CC;
class Scene_GameList : public CCLayer
{
private:
public:
    ~Scene_GameList(void);
    Scene_GameList();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    // implement the "static node()" method manually
    CREATE_FUNC(Scene_GameList);
    
private:
   
    //游戏列表.
    GameTableLayer* gameLayer;
    //系统设置.
//    GameShare_SysSet* sysSetLayer;
    //每日登陆.
    GameLayer_DayLogin* dayLoginLayer;
    
    //游戏资源
    GameLayer_Resource* gameResource;
    
    //排行榜按钮
    void setRankCallback(CCObject* pSender);
    //设置按钮点击.
    void setButtonCallback(CCObject* pSender);
    //任务按钮
    void setTaskCallback(CCObject* pSender);
    void getTask(CCObject* pSender);
    //好友按钮.
    void setFriendCallback(CCObject* pSender);
    //系统消息按钮。
    void setSysInfoCallback(CCObject* pSender);
    //添加金币.
    void addGoldCallback(CCObject* pSender);
    //添加钻石.
    void addDiamondCallback(CCObject* pSender);
    //添加饭.
    void addRiceCallback(CCObject* pSender);
    //获取好友总分排行
    void getFriendTotalRank(CCObject* pSender);
    //获得消息列表.
    void getInfoList(CCObject* pSender);
    //获取好友列表
    void getFriendList(CCObject* pSender);
    
    //设置系统消息
    void setInfoNumCallback(CCObject* pSender);
    void menuOkCallBack(CCObject* pSender);
    //获取从后端而来的好友信息；
    void getFriendInfoListCallBack(CCObject* pSender);
    
    //注册监听.
    void initListen();
    
    void setListForTheShowFriendScoreList();
    
    UIPanel *back;
    
    GameLayer_Menu* gameMenu;
    
    void refreshInfo(CCObject *p);
    void requestPlayerMoneyInfoMation(CCObject *p);
    
    void addFriendListLayer();
};

#endif
