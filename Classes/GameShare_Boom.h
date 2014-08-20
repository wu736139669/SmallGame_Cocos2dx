//
//  GameShare_Boom.h
//  OnceAgain
//
//  Created by mac on 14-3-6.
//
//

#ifndef __OnceAgain__GameShare_Boom__
#define __OnceAgain__GameShare_Boom__

#include "cocos2d.h"
USING_NS_CC;

#include "GameShare_Texture.h"
#include "GameShare_Msg.h"


class GameShare_Boom : public CCSprite
{
public:
    GameShare_Boom(void);
    virtual bool init();
    virtual ~GameShare_Boom();
    
    CREATE_FUNC(GameShare_Boom);
    CC_SYNTHESIZE(unsigned int, maxEnergy, MaxEnergy);
    void addEnergy(unsigned int energy=1);
    void setEnergy(unsigned int energy=0);
    void resetEnergy();
private:
    // 取得精灵的位置与尺寸
    CCRect rect();
    
};
#endif /* defined(__OnceAgain__GameShare_Boom__) */
