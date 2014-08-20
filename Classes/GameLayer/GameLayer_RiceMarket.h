//
//  GameLayer_RiceMarket.h
//  OnceAgain
//
//  Created by mac on 14-3-25.
//
//

#ifndef __OnceAgain__GameLayer_RiceMarket__
#define __OnceAgain__GameLayer_RiceMarket__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "GameLayer_Base.h"
//添加命名空间
USING_NS_CC_EXT;
USING_NS_CC;
class GameLayer_RiceMarket : public GameLayer_Base
{
public:
    virtual bool init(void);
    virtual void setVisible(bool visible);
    ~GameLayer_RiceMarket(void);
    GameLayer_RiceMarket(void){};
    CREATE_FUNC(GameLayer_RiceMarket);
private:
    UILayer* riceMarket;
    
    //点击确定按钮.
    void closeBtnCallback(CCObject* pSender);
    
    //点击兑换按钮
    void buyBtnCallback(CCObject* pSender);
    
    //点击确定购买按钮.
    void sureBuyCallback(CCObject* pSender);
    
    void setValue();
};

#endif /* defined(__OnceAgain__GameLayer_RiceMarket__) */
