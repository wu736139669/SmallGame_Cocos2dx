//
//  GameLayerFriendTaskCell.h
//  OnceAgain
//
//  Created by mac on 14-4-18.
//
//

#ifndef __OnceAgain__GameLayerFriendTaskCell__
#define __OnceAgain__GameLayerFriendTaskCell__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "NetHttpClient.h"
#include "FriendManager.h"
#include "TaskManager.h"
USING_NS_CC;
USING_NS_CC_EXT;

enum eWeekTaskCell {
    weekTaskCellTypeNo = 1,
    weekTaskCellTypeHave = 2,
    weekTaskCellTypeComp = 3,
    };
class GameLayerFriendTaskCell : public CCLayer{
    
    
public:
    GameLayerFriendTaskCell();
    ~GameLayerFriendTaskCell();
    CREATE_FUNC(GameLayerFriendTaskCell);
    virtual bool init();
    //设置任务详情.
    
    void requestReward(CCObject*p);
    
    void setCallBack(CCObject *p, SEL_CallFunc call);
    void btnClickcallBack(CCObject *p);
    
    void setCellInfo(sWeekTask data);
    
private:
    UILayer* cellLyaer;
    CCObject *target;
    SEL_CallFunc callBack;
    int myTaskId;
    sWeekTask info;
};

#endif /* defined(__OnceAgain__GameLayerFriendTaskCell__) */
