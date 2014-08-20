//
//  GameLayerFriendTaskList.h
//  OnceAgain
//
//  Created by mac on 14-4-18.
//
//

#ifndef __OnceAgain__GameLayerFriendTaskList__
#define __OnceAgain__GameLayerFriendTaskList__

#include "cocos2d.h"
#include "CCScrollviewSimple.h"
#include "FriendManager.h"
#include "TaskManager.h"
USING_NS_CC;
class GameLayerFriendTaskList : public cocos2d::CCLayer , public CCTableViewDelegate, public CCTableViewDataSource
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    virtual void onExit();
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static CCScene* scene();
    
    GameLayerFriendTaskList();
    ~GameLayerFriendTaskList();
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(GameLayerFriendTaskList);
    //点击系统设置上面的关闭.
    void closeSysSetCallback(CCObject* pSender);
    
public:
    
    virtual void scrollViewDidScroll(CCScrollView* view) {}
    virtual void scrollViewDidZoom(CCScrollView* view) {}
    
    //触摸到某个cell的事件
    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell) {};
    
    //定制每个cell的size
    virtual CCSize tableCellSizeForIndex(CCTableView *table, unsigned int idx);
    
    //定制每个cell的内容
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    
    //确定这个tableview的cell行数
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    
private:
    
    CCTableView *mytableview;
    CCScrollviewSimple *showScrollView;
    void getRewardCallBack();
    void topBtnCallBack(CCObject *p);
    std::vector<sWeekTask>datalist;
    
    void reloadMyTableView(CCObject *p);
};

#endif /* defined(__OnceAgain__GameLayerFriendTaskList__) */
