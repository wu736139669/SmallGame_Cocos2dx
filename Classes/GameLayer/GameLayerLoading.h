

#ifndef __OnceAgain__GameLayer_Loading__
#define __OnceAgain__GameLayer_Loading__
#include "cocos2d.h"
#include "CocosGUI.h"
#include "cocos-ext.h"
#include "ComData.h"
#include "BaseData.h"
#include "GameShare_Property.h"
#include <vector>
#include "GameCommon.h"

USING_NS_CC_EXT;
USING_NS_CC;

class CGameLayerLoading : public GameLayer_Base/*,public UILayer*/{
    DECLARE_DLG_ID();
public:
    CGameLayerLoading();
	virtual ~CGameLayerLoading();
	
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);  
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);  
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);  
	virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent); 
	//
	virtual void onShow();
	//
	virtual void onHide();
	//
	void setCallfunc(CCObject *target, SEL_CallFuncO callfun);
	//
	void play();
	//
	void onBtnClose(CCObject* p);

	CREATE_FUNC(CGameLayerLoading);
protected:
	CCObject*       m_pListener;
	SEL_CallFuncO    m_pfnSelector;
	UILayer*		mpUILayer;
};

#endif /* defined(__OnceAgain__GameLayer_Base__) */
