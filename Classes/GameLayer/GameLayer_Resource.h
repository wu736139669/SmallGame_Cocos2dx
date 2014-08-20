//
//  GameLayer_Resource.h
//  OnceAgain
//
//  Created by mac on 14-3-25.
//
//

#ifndef __OnceAgain__GameLayer_Resource__
#define __OnceAgain__GameLayer_Resource__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "GameLayer_Base.h"
#include "GameCommon.h"


//添加命名空间
USING_NS_CC_EXT;
USING_NS_CC;
class GameLayer_Resource : public GameLayer_Base
{
	DECLARE_DLG_ID();
public:
    virtual void onEnter();
    virtual bool init(void);
    virtual void setVisible(bool visible);
    ~GameLayer_Resource(void);
    GameLayer_Resource(void){};
    CREATE_FUNC(GameLayer_Resource);
    
    void reSetGoldNum(long num);
    void reSetDiamondNum(long num);
    void reSetLv(int num, float persent);
    
    //添加增加金币方法
    void addGoldCallback(CCObject* target, SEL_CallFuncO callfun);
    //添加增加钻石
    void addDiamondCallback(CCObject* target, SEL_CallFuncO callfun);

	virtual bool onPackageFilter(void *pDataPkg);
private:
    UILayer* gameResource;
    CCSprite* getSpriteByScore(long score);
    CCSprite* getLvByNum(int num);
    CCSprite* getLvPrecentageNumber(int num);
//    //点击确定按钮.
//    void sureBtnCallback(CCObject* pSender);
    //点击增加金币
//    void addGoldCallback(CCObject* pSender);
    
    CCSprite* goldNum;
    CCSprite* diamondNum;
    CCSprite* lvNum;
    CCSprite* lvPrecentage;
    
    void reSetLvPrecentageNumber(int num);
};

#endif /* defined(__OnceAgain__GameLayer_Resource__) */
