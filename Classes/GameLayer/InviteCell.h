//
//  InviteCell.h
//  OnceAgain
//
//  Created by mac on 14-5-6.
//
//

#ifndef __OnceAgain__InviteCell__
#define __OnceAgain__InviteCell__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "FriendManager.h"
USING_NS_CC;
USING_NS_CC_EXT;
class InviteCell : public CCLayer{
    
public:
    InviteCell();
    ~InviteCell();
    CREATE_FUNC(InviteCell);
    virtual bool init();
    virtual void onEnter();

    //设置按钮的方法.
    void addSendCallbackFunc(CCObject* target, SEL_ReleaseEvent callfun);
    
    void sendInvite(CCObject* pSender);
    //
    void sureSend(CCObject* pSender);
    void setNode(CCNode* node);
    
    void setInfo(sGameRank info);
    void requestIcon();
    void sendInviteForThisFriend(CCObject*p);
    CC_SYNTHESIZE(bool, mbLoadImg, LoadImg)
private:
    UILayer* cellLyaer;
    CCSprite* scoreSprite;
    CCSprite* img;
    std::string userId;
    const char* name;
    CCNode*  m_pListener;
    CCSprite *graylightWithCCSprite(CCSprite* oldSprite,bool isLight);
    void setPicToBeHide(CCObject *p);
    sGameRank info;
};

#endif /* defined(__OnceAgain__InviteCell__) */
