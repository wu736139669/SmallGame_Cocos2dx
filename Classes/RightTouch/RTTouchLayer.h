
#ifndef _RT_TOUCH_H_
#define _RT_TOUCH_H_
#include "cocos2d.h"

class CRightTouchScene;

class CRTTouchLayer : public cocos2d::CCLayer
{
public:
    CREATE_FUNC(CRTTouchLayer);
    bool init();
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	//注册单击事件
	//virtual void registerWithTouchDispatcher();
    //开启、关闭触摸的接口
    virtual void setTouchEnabled(bool flag);

	virtual void onEnter();
	virtual void onExit();
protected:
    CRightTouchScene* getGameScene();
    cocos2d::CCPoint locationFromTouch(cocos2d::CCTouch *touch);

};

#endif /* defined(__FishingJoy__TouchLayer__) */
