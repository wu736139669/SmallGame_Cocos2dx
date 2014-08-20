//
//  Scene_GameOver.h
//  OnceAgain
//
//  Created by xiaohai on 14-2-21.
//
//
/*
 *
 *      实现游戏结束场景
 *
 */

#ifndef OnceAgain_Scene_GameOver_h
#define OnceAgain_Scene_GameOver_h

#include "cocos2d.h"
#include "GameSharelist.h"
#include "GameShare_Property.h"
#include "CocosGUI.h"
#include "cocos-ext.h"
#include "GameLayer_LvUp.h"
#include "JudgeMedalGet.h"
//#include "GameShare_Scene.h"
//#include "Game_Memory.h"
//添加命名空间
USING_NS_CC_EXT;
USING_NS_CC;
enum Result_Type
{
    Type_Normal = 0,
    Type_Max = 1
};
class GameMedalLayer;
class Scene_GameOver : public cocos2d::CCLayer, public JudgeMedalGet
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    virtual void onEnter();
    ~Scene_GameOver();
    Scene_GameOver();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    void menuRestartCallBack(CCObject* pSender);
    
    void menuOkCallBack(CCObject* pSender);
    
    //结果分数.
    CC_SYNTHESIZE(int, resultScore, ResultScore);
    //最高分数
    CC_SYNTHESIZE(int, maxScore, MaxScore);
    
    void GameInfoToSprite(const sGameProperty &gameInfo);
    
    void setResultAndMaxScore(long resultScore, long maxScore);
    
    // implement the "static node()" method manually
    CREATE_FUNC(Scene_GameOver);
private:
    //确认按钮的回调.
    void sureBtnCallBack();
    
    //显示等级.
    CCSprite* levelSprite;
    CCSprite* resultSprite;
    CCSprite* maxScoreSprite;
    //得分界面.
    UILayer* ul;
    //获得称号界面.
    UILayer* obtainTitleUl;
    
    //结束任务界面.
    GameMedalLayer* taskUl;
        
    void judgeShowLayers();
    std::vector<CCLayer*>layerList;
    int layerCount;
};
#endif
