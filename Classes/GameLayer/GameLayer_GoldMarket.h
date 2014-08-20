//
//  GameLayer_GoldMarket.h
//  OnceAgain
//
//  Created by mac on 14-3-25.
//
//

#ifndef __OnceAgain__GameLayer_GoldMarket__
#define __OnceAgain__GameLayer_GoldMarket__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "GameLayer_Base.h"
//添加命名空间
USING_NS_CC_EXT;
USING_NS_CC;
class GameLayer_GoldMarket : public GameLayer_Base
{
public:
    virtual bool init(void);
    virtual void setVisible(bool visible);
    ~GameLayer_GoldMarket(void);
    GameLayer_GoldMarket(void){goldMarket=NULL;};
    CREATE_FUNC(GameLayer_GoldMarket);
private:
    UILayer* goldMarket;
    
    //点击确定按钮.
    void closeBtnCallback(CCObject* pSender);
    
    //点击兑换按钮
    void buyBtnCallback(CCObject* pSender);
    
    //点击确定购买按钮.
    void sureBuyCallback(CCObject* pSender);

    void setValue();
public:
	//点击金币购买的特效	数量	种类
	void sureBuyCallEffect(int i,int iType);
};

#endif /* defined(__OnceAgain__GameLayer_GoldMarket__) */
