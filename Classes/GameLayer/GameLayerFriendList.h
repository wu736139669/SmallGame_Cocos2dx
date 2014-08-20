//
//  GameLayerFirendList.h
//  OnceAgain
//
//  Created by mac on 14-4-16.
//
//

#ifndef __OnceAgain__GameLayerFriendList__
#define __OnceAgain__GameLayerFriendList__

#include "cocos2d.h"
#include "CCScrollviewSimple.h"
#include "GameLayer_Base.h"
#include "GameCommon.h"
#include "GameLayerFriendCell.h"
USING_NS_CC;
class GameLayerFriendList : public GameLayer_Base ,public CCScrollViewSimpleDelegate
{
    DECLARE_DLG_ID();
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static CCScene* scene();
    
    virtual void onEnter();
    virtual void onExit();
    virtual bool onPackageFilter(void *pDataPkg);
    
    GameLayerFriendList();
    ~GameLayerFriendList();
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(GameLayerFriendList);
    //点击系统设置上面的关闭.
    void closeSysSetCallback(CCObject* pSender);
    //送饭方法.
    void sendRiceCallback(CCObject* pSender);
    //进入个人资料.
    void gotoUserInfo();
	//获取 排行榜
	void getTop(CCObject* pSender);
public:
    
    virtual void scrollViewDidScroll(CCScrollviewSimple* view);
    
    
    virtual void scrollViewDidZoom(CCScrollviewSimple* view);
    
private:
     CCSize visibleSize;
    CCScrollviewSimple *showScrollView;
    
    GameLayerFriendCell* mySelfCell;
    
    
    void mySelfCellClickCallBack(CCObject *p);
    void checkBoxCallBack(CCObject *p);
    

    void timeBeginCount(CCObject *p);
    void alertCallBack(CCObject *p);
    
    
    std::vector<GameLayerFriendCell*>timeCountList;
    
    UILayer* ul;
    UILayer *layer;
    UILabel *timeLabel;
    int sendId;
    
    int TIME;
};

#endif /* defined(__OnceAgain__GameLayerFirendList__) */
