//
//  GameLayerTable.h
//  OnceAgain
//
//  Created by mac on 14-4-18.
//
//

#ifndef __OnceAgain__GameLayerTable__
#define __OnceAgain__GameLayerTable__

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class GameLayerTable : public CCScrollView{
    
    
public:
    //
    void setContentOffset(CCPoint offset, bool animated = false);
    
    //
    static GameLayerTable* create(CCSize size, CCNode* container = NULL);
    
    GameLayerTable();
    ~GameLayerTable();
    
};
#endif /* defined(__OnceAgain__GameLayerTable__) */
