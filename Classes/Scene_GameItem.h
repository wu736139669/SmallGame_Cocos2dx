//
//  Scene_GameItem.h
//  OnceAgain
//
//  Created by mac on 14-3-21.
//
//

#ifndef __OnceAgain__Scene_GameItem__
#define __OnceAgain__Scene_GameItem__

#include <iostream>

#endif /* defined(__OnceAgain__Scene_GameItem__) */
#include "cocos2d.h"
#include "GameSharelist.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "Constant.h"
#include "GameShare_Texture.h"
#include "GameShare_Global.h"
#include "GameLayer_Alert.h"
#include "GameLayer_Task.h"
#include "GameLayer_ItemStrong.h"
#include "GameLayer_Base.h"
#include "GameCommon.h"
#include "GameLayerPkBar.h"
USING_NS_CC;
USING_NS_CC_EXT;
class Scene_GameItem : public GameLayer_Base
{
    DECLARE_DLG_ID();
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    ~Scene_GameItem();
    Scene_GameItem();
    virtual bool init();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
//    static Scene_GameItem* layer;
    
    virtual bool onPackageFilter(void *pDataPkg);
    virtual void onEnter();
    //    virtual void onExit();
    virtual void onEnterTransitionDidFinish();
    void showRankList();
	void MedalInfoBack(CCObject* p);
    // implement the "static node()" method manually
    CREATE_FUNC(Scene_GameItem);
private:
    //click to start game with no login
//    void startGameNoLogin(CCObject *object);
    //返回按钮.
    void returnBtnCallBack(CCObject *object);
    //游戏开始按钮.
    void startGameCallBack(CCObject *object);
    //进入游戏
    void gointoGameCallBack(CCObject *object);
    //道具使用.
    void itemBtnCallBack(CCObject* object);
    //装备按钮.
    void equipBtnCallBack(CCObject* object);
    //确认购买装备.
    void equipSureCallBack(CCObject* object);
    //任务按钮.
    void taskBtnCallBack(CCObject* object);
    //排行榜
    void rankBtnCallBack(CCObject* object);
    //弹出强化框
    void equipSuperCallBack(CCObject* object);
    
    //强化框能够再次dianji
    void equipSuperBtnCanBenClick(CCObject *p);
    
    //设置pk界面
    void setPkView(bool isPk=false);
    void pkBtnCallBack(CCObject* object);
    //初始化数据.
    void initData();
    //设置道具的选中提示
    void setItemByTag(int btnTag);
    
    //强化界面.
    GameLayer_ItemStrong* gameLayer_Strong;
    //设置装备等级.
    void setLvNum();
    //获取装备等级数字精灵.
    CCSprite* getLvByScore(int lv=0);
    UILayer* ul;
    CCSprite* lvImg1;
    CCSprite* lvImg2;
    CCSprite* lvImg3;
    int needGold;      //购买道具所需要的钱.
    
    
    
    //返回按钮.
    UIButton* returnBtn;
    //勋章任务点击.
    UIButton* taskBtn;
    UIButton* rankBtn;
//    GameLayer_Alert* alertUl;
    
    
};