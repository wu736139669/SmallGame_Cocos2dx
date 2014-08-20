//
//  GameLayerPk.h
//  OnceAgain
//
//  Created by mac on 14-4-29.
//
//

#ifndef __OnceAgain__GameLayerPk__
#define __OnceAgain__GameLayerPk__
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class GameLayerPk : public CCLayer {
    
public:
    GameLayerPk();
    ~GameLayerPk();
    
    virtual bool init();
    CREATE_FUNC(GameLayerPk);
    //设置按钮的方法.
    void addSureCallbackFunc(CCObject* target, SEL_CallFunc callfun);
    //确认按钮点击.
    void sureBtnCallback(CCObject* pSender);
private:
	void UpStart(float td);
	void UpRay(float td);
	UIImageView* Ray;						//需要更新的效果；
	UIImageView* Ray2;
	UIImageView* Start1;
	UIImageView* Start2;
	UIImageView* Start3;
	UIImageView* Start4;
	UIImageView* Start5;
	UIImageView* Start6;
	UIImageView* Start7;
	UIImageView* Start8;
	UIImageView* Start9;
	UIImageView* Start10;
	UIImageView* Start11;
	UIImageView* pSatrt1;
	UIImageView* pSatrt2;
	UIImageView* pSatrt3;
	UIImageView* pSatrt4;
	UIImageView* pSatrt5;
	UIImageView* pSatrt6;
	UIImageView* pStar1;
	UIImageView* pStar2;
	UIImageView* pStar3;
	UIImageView* pStar4;
	UIImageView* pStar5;


    CCObject*       m_pListener;
    SEL_CallFunc    m_pfnSelector;
};
#endif /* defined(__OnceAgain__GameLayerPk__) */
