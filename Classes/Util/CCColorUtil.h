//
//  CCColorUtil.h
//  OnceAgain
//
//  Created by mac on 14-4-16.
//  把精灵变灰色.
//

#ifndef __OnceAgain__CCColorUtil__
#define __OnceAgain__CCColorUtil__

#include "cocos2d.h"
USING_NS_CC;
using namespace cocos2d;
class CCColorUtil
{
public:
    static void addGray(CCSprite* sp);
    static void removeGray(CCSprite* sp);
	static CCSprite* graylightWithCCSprite(CCSprite* oldSprite,bool isLight);
    
};

#endif /* defined(__OnceAgain__CCColorUtil__) */
