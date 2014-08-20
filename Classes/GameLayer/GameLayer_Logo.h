//
//  GameLayer_Logo.h
//  OnceAgain
//
//  Created by mac on 14-4-16.
//
//

#ifndef __OnceAgain__GameLayer_Logo__
#define __OnceAgain__GameLayer_Logo__

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class GameLayer_Logo : public CCLayer {
    
    
public:
    GameLayer_Logo();
    ~GameLayer_Logo();
    virtual bool init();
    
    CREATE_FUNC(GameLayer_Logo);
};

#endif /* defined(__OnceAgain__GameLayer_Logo__) */
