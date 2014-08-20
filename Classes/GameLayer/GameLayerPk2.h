//
//  GameLayerPk2.h
//  OnceAgain
//
//  Created by mac on 14-5-8.
//
//

#ifndef __OnceAgain__GameLayerPk2__
#define __OnceAgain__GameLayerPk2__

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class GameLayerPk2 : public CCLayer {
    
public:
    GameLayerPk2();
    ~GameLayerPk2();
    
    virtual bool init();
    CREATE_FUNC(GameLayerPk2);
    //设置按钮的方法.
    void addSureCallbackFunc(CCObject* target, SEL_CallFunc callfun);
    //确认按钮点击.
    void sureBtnCallback(CCObject* pSender);
private:
    CCObject*       m_pListener;
    SEL_CallFunc    m_pfnSelector;

	int m_iSetTime;		
	void SetDDTime(float td);				//设置等待迎战；
	UIImageView* Deng;
	UIImageView* Dai;
	UIImageView* Ying;
	UIImageView* Zhan;
	UIImageView* Dain1;
	UIImageView* Dain2;
	UIImageView* Dain3;
	CCActionInterval*  actionUp;
};

#endif /* defined(__OnceAgain__GameLayerPk2__) */
