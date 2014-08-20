

#ifndef RIGHT_TOUCH_SCENE_H
#define RIGHT_TOUCH_SCENE_H
#include "cocos2d.h"

//#include "PanelLayer.h"
//#include "MenuLayer.h"
#include "RTBgLayer.h"
#include "RTTouchLayer.h"
typedef enum{
    eOperatePause = 0,
    eOperateResume
}EOperateFlag;
class CRTItemLayer;
class CRightTouchScene : public cocos2d::CCScene
{
public:
    CREATE_FUNC(CRightTouchScene);
    bool init();
    ~CRightTouchScene();

    //菜单页面相关的函数
    void pause();
    void resume();
    void sound();
    void music();
    void reset();
    void transToMainMenu();

    void scheduleTimeUp();

	virtual void onExit();

protected:

//     CannonLayer* _cannonLayer;
//     FishLayer* _fishLayer;
//     PanelLayer* _panelLayer;
//     MenuLayer* _menuLayer;

    void update(float delta);

    //数据相关
    //void alterGold(int delta);

    //暂停或恢复场景内运行的所有节点
    void operateAllSchedulerAndActions(cocos2d::CCNode* node, EOperateFlag flag);

    //todo 预载入资源，实现StartScene后将其删除
    void preloadResources();
    
    virtual void onEnterTransitionDidFinish();

	CC_SYNTHESIZE(CRTItemLayer*, mpItemLayer,ItemLayer)
	CC_SYNTHESIZE(CRTBgLayer*,mpBgLayer,BgLayer);
	CC_SYNTHESIZE(CRTTouchLayer*,mpTouchLayer,TouchLayer);
};

#endif 
