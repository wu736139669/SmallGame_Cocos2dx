//
//  GameLayer_SuperItem.h
//  OnceAgain
//
//  Created by mac on 14-3-25.
//
//

#ifndef __OnceAgain__GameLayer_SuperItem__
#define __OnceAgain__GameLayer_SuperItem__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "GameLayer_Base.h"
#include "GameCommon.h"
//添加命名空间
USING_NS_CC_EXT;
USING_NS_CC;
enum ESuperItemEven
{
	eSuperItemCommon,
	eSuperItemBuyCrazy,
};
class GameLayer_SuperItem : public GameLayer_Base
{
	DECLARE_DLG_ID();
public:
    virtual bool init(void);
    virtual void setVisible(bool visible);
    ~GameLayer_SuperItem(void);
    GameLayer_SuperItem(void):mnItemID(0),meEvent(eSuperItemCommon){};
    CREATE_FUNC(GameLayer_SuperItem);
    
    //暂停弹出.
    //static CCScene* scene(CCRenderTexture *spr,bool isFlip);
    //设置确定的方法.
    void setSureCallbackFunc(CCObject* target, SEL_CallFuncO pCallfuncOk, SEL_CallFuncO pCallfuncCancel);
    //设置确定按钮的tag
    void setSureBtnTag(int tag);
    //设置显示的字符.
    void setItemInfo(const char* str);
	//proccse net pack
     virtual bool onPackageFilter(void *pDataPkg);
    //
	void setItem(int nItemId);
private:
    UILayer* superItem;
    
    //点击确定按钮.
    void sureBtnCallback(CCObject* pSender);
    //点击关闭按钮.
    void closeBtnCallback(CCObject* pSender);
	//
	void _close();
    
    void requestItems(CCObject *p);
    
    CCObject*       m_pListener;
    SEL_CallFuncO    m_pfnSelector;
	SEL_CallFuncO    m_pfnSelectorClose;
	int mnItemID;
	CC_SYNTHESIZE(ESuperItemEven,meEvent,Event);
};

#endif /* defined(__OnceAgain__GameLayer_SuperItem__) */
