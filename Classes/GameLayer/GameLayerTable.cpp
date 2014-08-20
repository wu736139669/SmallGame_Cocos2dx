//
//  GameLayerTable.cpp
//  OnceAgain
//
//  Created by mac on 14-4-18.
//
//

#include "GameLayerTable.h"
#define BOUNCE_DURATION 1.5
GameLayerTable::GameLayerTable()
{
    
}
GameLayerTable::~GameLayerTable()
{
}

void GameLayerTable::setContentOffset(CCPoint offset, bool animated)
{
    if (animated)
    { //animate scrolling
        this->setContentOffsetInDuration(offset, BOUNCE_DURATION);
    }
    else
    { //set the container position directly
        if (!m_bBounceable)
        {
            const CCPoint minOffset = this->minContainerOffset();
            const CCPoint maxOffset = this->maxContainerOffset();
            
            offset.x = MAX(minOffset.x, MIN(maxOffset.x, offset.x));
            offset.y = MAX(minOffset.y, MIN(maxOffset.y, offset.y));
        }
        
        m_pContainer->setPosition(offset);
        
        if (m_pDelegate != NULL)
        {
            m_pDelegate->scrollViewDidScroll(this);
        }
    }
}

GameLayerTable* GameLayerTable::create(CCSize size, CCNode* container/* = NULL*/)
{
    GameLayerTable* pRet = new GameLayerTable();
    if (pRet && pRet->initWithViewSize(size, container))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}