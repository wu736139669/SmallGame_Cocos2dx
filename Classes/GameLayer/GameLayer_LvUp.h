//
//  GameLayer_LvUp.h
//  OnceAgain
//
//  Created by mac on 14-4-15.
//
//

#ifndef __OnceAgain__GameLayer_LvUp__
#define __OnceAgain__GameLayer_LvUp__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "GameLayer_Base.h"
//添加命名空间
USING_NS_CC_EXT;
USING_NS_CC;
class GameLayer_LvUp : public GameLayer_Base {
    
    
public:
    virtual bool init(void);
    ~GameLayer_LvUp(void);
    GameLayer_LvUp(void){};
    CREATE_FUNC(GameLayer_LvUp);
//    //结果分数.
//    CC_SYNTHESIZE(int, lv, Lv);
    void setLv(int lv);
    void addSureCallback(CCObject* target, SEL_CallFunc callfun);
private:
    //设置结果分数.
    CCSprite* getNumSprite(int score, std::string imgName, float offSetX);
//    //设置历史最高分.
    //升级界面.
    UILayer* levelUpUl;
    
    //升级数字改变
    void lvChange();
    
    int lv;
    
    CCSprite *lvPic;
    
    //动画效果.
    void setAction();
    //设置等级.
    CCSprite* setLevel(int level);
    //获得金币奖励的精灵.
    CCSprite* getAddGoldByScore(long score);
    //获得等级加成的精灵.
    CCSprite* getAddExperienceScore(float percent);
    
    UIImageView *centerArrow;
    
    void sureCallback(CCObject *p);
    CCObject *target;
    SEL_CallFunc seletor;
};
#endif /* defined(__OnceAgain__GameLayer_LvUp__) */
