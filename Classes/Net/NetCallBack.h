//
//  NetCallBack.h
//  OnceAgain
//
//  Created by xiaohai on 14-4-30.
//
//

#ifndef __OnceAgain__NetCallBack__
#define __OnceAgain__NetCallBack__

#include <iostream>
#include "cocos2d.h"
#include "CocosGUI.h"
#include "cocos-ext.h"

NS_CC_EXT_BEGIN;

typedef void (CCObject::*SEL_MyEvent)(CCObject*);
#define coco_myevent(_SELECTOR) (cocos2d::extension::SEL_MyEvent)(&_SELECTOR)

class NetCallBack: public CCObject
{
protected:
    SEL_MyEvent callback;
    cocos2d::CCObject *target;
public:
    void setCallBack(cocos2d::CCObject *target, SEL_MyEvent a);
    void doCallBack();
};
NS_CC_EXT_END
#endif /* defined(__OnceAgain__NetCallBack__) */
