
#ifndef DAPAO_SCENE_H
#define DAPAO_SCENE_H

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"  ///播放声音文件
#include <vector>
#include "GameShare_Scene.h"

USING_NS_CC;
USING_NS_CC_EXT;
class GameShare_TimeProcess;

class CDaPaoScene : public GameShare_Scene
{
public:
	struct SBulletInfo{
		CCSprite* pBullet;
		int nLev;
		int nCounter;
	};
	typedef std::vector<CCSprite*> VEC_ITEM;
	typedef std::vector<SBulletInfo> VEC_BULLETINFO;
    CDaPaoScene();
    ~CDaPaoScene();
public:

	static cocos2d::CCScene* scene();

	void start();

    //初始化 进行当前层的一些初始化
    virtual bool init();

	virtual void initBgView();
    
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
	void addTarget(VEC_ITEM& vecItem,CCPoint pt,bool bMoveRight);
	void updataBullet(VEC_ITEM& vecItem);
	virtual void msgHandle_CrazyTimeOut(CCObject* obj);

	void callbackBullet(CCNode* n, void* v);

    CREATE_FUNC(CDaPaoScene);
protected:
	
private:
  
   VEC_ITEM _vecItem[3];
	VEC_BULLETINFO _vecBullet;
   GameShare_TimeProcess*   mpTimeProcessLayer;

   unsigned long mulLastTouchTime;
   CCSize _visibleSize;
   CCRect _rcSlot;
};

#endif
