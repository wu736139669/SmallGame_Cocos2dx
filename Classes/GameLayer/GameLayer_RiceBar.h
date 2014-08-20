//
//  GameLayer_RiceBar.h
//  OnceAgain
//
//  Created by mac on 14-3-25.
//
//

#ifndef __OnceAgain__GameLayer_RiceBar__
#define __OnceAgain__GameLayer_RiceBar__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "GameLayer_Base.h"
#include "GameCommon.h"
//#include "XQDate.h"
//添加命名空间
USING_NS_CC_EXT;
USING_NS_CC;
class GameLayer_RiceBar : public GameLayer_Base
{
    DECLARE_DLG_ID();
public:
    virtual bool init(void);
    virtual void setVisible(bool visible);
    ~GameLayer_RiceBar(void);
    GameLayer_RiceBar(void){iFaceType = 0,bSprite=false,riceBar=NULL;};
    CREATE_FUNC(GameLayer_RiceBar);
    
    virtual void onEnter();
    //设置添加饭的方法.
    void addRiceCallbackFunc(CCObject* target, SEL_CallFuncO callfun);
    
    void setRiceNum(int riceNum);
    
    virtual bool onPackageFilter(void *pDataPkg);
private:
    UILayer* riceBar;
    
    int addRiceTime;
    long nowTime;
    //点击确定按钮.
    void addRiceCallback(CCObject* pSender);
    
    //计时器刷新.
    void timeUpdate(float dt);
    
	//体力表情 
	void RiceFace(float td);

    bool willrequistInfo;
    
    void checkTimeIsUp();
private:
	CCSprite* pFace0; 
	CCSprite* pFace1; 
	CCSprite* pFace2; 
	CCSprite* pFace3; 
	CCSprite* pFace4; 
	int iFaceType;
	int iFaceRend;
	CCAnimation *animation;
	bool bSprite;//设置只add一次 精灵
};

#endif /* defined(__OnceAgain__GameLayer_RiceBar__) */
