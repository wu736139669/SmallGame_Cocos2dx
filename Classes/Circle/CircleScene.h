
#ifndef CIRCLE_SCENE_H
#define CIRCLE_SCENE_H

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"  ///播放声音文件
#include <vector>
#include "GameShare_Scene.h"

USING_NS_CC;
USING_NS_CC_EXT;
class GameShare_TimeProcess;

class CCircleScene : public GameShare_Scene
{
public:
    CCircleScene();
    ~CCircleScene();
public:

	static cocos2d::CCScene* scene();

	void start();

    //初始化 进行当前层的一些初始化
    virtual bool init();
    
    //单击事件开始
    virtual bool ccTouchBegan(cocos2d::CCTouch * pTouch, cocos2d::CCEvent *pEvent);
    //单击事件拖动
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    //单击事件结束
    virtual void ccTouchEnded(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
    //注册单击事件
    virtual void registerWithTouchDispatcher();
	virtual void onEnter();
	virtual void onExit();
    virtual void update(float fDelta);
    // a selector callback
    virtual void menuCloseCallback(CCObject* pSender);

	void InitListerner();
	void MsgHanlde_GameTimeOut(CCObject* obj);
	void addTarget();
	virtual void msgHandle_CrazyTimeOut(CCObject* obj);

    CREATE_FUNC(CCircleScene);
protected:
	
private:
  
   CCSprite* mpSp[5];
  
   GameShare_TimeProcess*   mpTimeProcessLayer;

   unsigned long mulLastTouchTime;
};

#endif
