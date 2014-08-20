

#ifndef __OnceAgain__GameLayer_TaiKo__
#define __OnceAgain__GameLayer_TaiKo__
#include "GameCommon.h"
#include "cocos2d.h"
#include "CocosGUI.h"
#include "cocos-ext.h"
#include "ComData.h"
#include "BaseData.h"
USING_NS_CC_EXT;
USING_NS_CC;

class CGameLayerTaiko : public UILayer{
    
	DECLARE_DLG_ID();
public:
    CGameLayerTaiko();
	~CGameLayerTaiko();

	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	virtual void updata(float fDelta);
	
	//////////////////////////////////////////////////////////////////////////
	//点击事件
	//单击事件开始
// 	virtual bool ccTouchBegan(cocos2d::CCTouch * pTouch, cocos2d::CCEvent *pEvent);
// 	//单击事件拖动
// 	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
// 	//单击事件结束
// 	virtual void ccTouchEnded(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);

	void OnBtn0(CCObject* pSender);
	void OnBtnPushDown0(CCObject* pSender);
	void OnBtnCancel0(CCObject* pSender);
	void OnBtn1(CCObject* pSender);
	void OnBtnPushDown1(CCObject* pSender);
	void OnBtnCancel1(CCObject* pSender);
	void OnBtnBrum(CCObject* pSender);
	//////////////////////////////////////////////////////////////////////////

	CREATE_FUNC(CGameLayerTaiko);
protected:

};

#endif /* defined(__OnceAgain__GameLayer_Base__) */
