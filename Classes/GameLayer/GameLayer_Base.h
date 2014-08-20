//
//  GameLayer_Base.h
//  OnceAgain
//
//  Created by mac on 14-4-1.
//
//

#ifndef __OnceAgain__GameLayer_Base__
#define __OnceAgain__GameLayer_Base__
#include "cocos2d.h"
#include "NetHookManager.h"
#include "UILayer.h"
USING_NS_CC;
USING_NS_CC_EXT;
class GameLayer_Base : public CCLayer/*UILayer*/ ,public INetHook{
    
    
public:
    GameLayer_Base():INetHook(ENetHookTypeDialog){};
	virtual ~GameLayer_Base();
public:
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	virtual void onEnterTransitionDidFinish();
	virtual void setVisible(bool visible);
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	//
	virtual void onShow(){};
	//
	virtual void onHide(){};
};

#endif /* defined(__OnceAgain__GameLayer_Base__) */
