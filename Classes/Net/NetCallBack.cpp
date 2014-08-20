//
//  NetCallBack.cpp
//  OnceAgain
//
//  Created by xiaohai on 14-4-30.
//
//

#include "NetCallBack.h"


void cocos2d::extension::NetCallBack::setCallBack(cocos2d::CCObject* target1,SEL_MyEvent selector)
{
    target = target1;
    callback = selector;
};

void cocos2d::extension::NetCallBack::doCallBack()
{
    if (target && callback) {
        (target->*callback)(this);
    }
};