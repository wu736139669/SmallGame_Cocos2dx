//
//  GameShare_Batter.h
//  OnceAgain
//
//  Created by mac on 14-3-7.
//
//

#ifndef __OnceAgain__GameShare_Batter__
#define __OnceAgain__GameShare_Batter__


#include "cocos2d.h"

#include "GameShare_Texture.h"

USING_NS_CC;
class CCounterImage;
class GameShare_Batter : public CCSprite
{
public:
    GameShare_Batter(void){mpContinueHit=NULL;};
    ~GameShare_Batter(void);
    virtual bool init(void);
    
    void setBatter(unsigned int batterNum);
    int getRealWidth();
    CREATE_FUNC(GameShare_Batter);
private:
    CCSprite *mpContinueHit;
	CCounterImage* mpCounterImage;
};

#endif /* defined(__OnceAgain__GameShare_Batter__) */
