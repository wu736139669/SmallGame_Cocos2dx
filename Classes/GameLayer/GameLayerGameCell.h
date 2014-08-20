//
//  GameLayerGameCell.h
//  OnceAgain
//
//  Created by mac on 14-4-16.
//
//

#ifndef __OnceAgain__GameLayerGameCell__
#define __OnceAgain__GameLayerGameCell__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class GameLayerGameCell : public CCTableViewCell{
    
    
public:
    GameLayerGameCell();
    ~GameLayerGameCell();
    CREATE_FUNC(GameLayerGameCell);
    virtual bool init();
    
};

#endif /* defined(__OnceAgain__GameLayerGameCell__) */
