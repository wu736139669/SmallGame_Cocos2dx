//
// GameMedalLayer.h
// OnceAgain
//
// Created by xiaohai on 14-4-28.
//
//

#ifndef __OnceAgain__GameMedalLayer__
#define __OnceAgain__GameMedalLayer__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "cocos-ext.h"
#include "TaskManager.h"
#include "JudgeMedalGet.h"
#include "NetHttpClient.h"


USING_NS_CC_EXT;
USING_NS_CC;
class Scene_GameOver;
class GameMedalLayer : public CCLayer, public JudgeMedalGet
{
public:
    GameMedalLayer();
    ~GameMedalLayer();
    virtual bool init();
    virtual void onEnter();
    CREATE_FUNC(GameMedalLayer);
    
    virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
//    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
//    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
//    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
private:
    void initData();
    void BindingUIItems();
    
private:
    UILayer* ul;
    UIButton* sureBtn;
    
    Scene_GameOver *target;
    bool isBeforeGame;
    int GameType;
    CCObject* tar;
	CCSize visibleSize;
	CCSprite* m_pRay;
	CCSprite* m_pRay2;
	CCSprite* m_pBadge;
	CCSprite *m_pGrade;
	CCSprite *m_pRay3;
	CCSprite *m_pStart1;
	CCSprite *m_pStart2;
	CCSprite *m_pStart;
	CCLayerColor *m_pBackGroundColor;
    SEL_CallFunc selector;
private:
    void getTodayMadelType();
    std::vector<SMeDalTaskData *>infoList;
    std::vector<cocos2d::CCPoint >pointList;
    void createItems(SMeDalTaskData *medalinfo, int isGet, int i);
	void createItems();
    void exitLayer(CCObject *p);    
    void httpCallBack(CCObject* p);
public:
    void setGameType(int gameId);
    void setCallback(CCObject* target1, SEL_CallFuncO callfun,int btnTag);
    void setCallBackByGameFinish(CCObject* target1, SEL_CallFunc callFun);
    bool isGameFinishCall;
	bool m_bSetBadge;				//设置徽章是否显示
    void SetBadge();
	void SetGrade(float td);		//设置什么时候 adc +1
	void SetStar(float td);			//设置星星 
	void deleteSprite(float td);
	void deleteGrade(float td);
		
};

#endif /* defined(__OnceAgain__GameMedalLayer__) */