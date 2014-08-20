//
//  GameLayer_DiamondMarket.h
//  OnceAgain
//
//  Created by mac on 14-3-25.
//
//

#ifndef __OnceAgain__GameLayer_DiamondMarket__
#define __OnceAgain__GameLayer_DiamondMarket__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "GameLayer_Base.h"
//添加命名空间
USING_NS_CC_EXT;
USING_NS_CC;
class GameLayer_DiamondMarket : public GameLayer_Base
{
public:
    virtual bool init(void);
    virtual void setVisible(bool visible);
    ~GameLayer_DiamondMarket(void);
    GameLayer_DiamondMarket(void){};
    CREATE_FUNC(GameLayer_DiamondMarket);
private:
    UILayer* diamondMarket;
    
    //点击确定按钮.
    void closeBtnCallback(CCObject* pSender);
    
    //点击兑换按钮
    void buyBtnCallback(CCObject* pSender);
    
    //点击确定购买按钮.
    void sureBuyCallback(CCObject* pSender);
    
    void setValue();
public:
	//点击金币购买的特效	数量	种类;
	void sureBuyCallEffect(int i,int iType);
};

#endif /* defined(__OnceAgain__GameLayer_DiamondMarket__) */
