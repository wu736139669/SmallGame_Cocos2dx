//
//  Scene_Reward.h
//  OnceAgain
//
//  Created by mac on 14-4-17.
//
//

#ifndef __OnceAgain__Scene_Reward__
#define __OnceAgain__Scene_Reward__

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
class Scene_Reward : public CCLayer {
    
    
public:
    virtual bool init();
    Scene_Reward();
    ~Scene_Reward();
    
    static cocos2d::CCScene* scene();
    CREATE_FUNC(Scene_Reward);
private:
    void rewardBtnCallback(CCObject* pSender);
};
#endif /* defined(__OnceAgain__Scene_Reward__) */
