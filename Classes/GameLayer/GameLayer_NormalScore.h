//
//  GameLayer_NormalScore.h
//  OnceAgain
//
//  Created by mac on 14-4-17.
//
//

#ifndef __OnceAgain__GameLayer_NormalScore__
#define __OnceAgain__GameLayer_NormalScore__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "GameLayer_Base.h"
//添加命名空间
USING_NS_CC_EXT;
USING_NS_CC;
class GameLayer_NormalScore : public GameLayer_Base {
    
    
public:
    virtual bool init(void);
    ~GameLayer_NormalScore(void);
    GameLayer_NormalScore(void){};
    CREATE_FUNC(GameLayer_NormalScore);
    void setMaxAndResult(int max, int result);
    
private:
//    //设置历史最高分.
//    void setScoreCallBack();
    UILayer* ul;
    
    
};

#endif /* defined(__OnceAgain__GameLayer_NormalScore__) */
