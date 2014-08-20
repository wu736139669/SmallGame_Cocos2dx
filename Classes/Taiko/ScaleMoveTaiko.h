//
//  ScaleMoveTaiko.h
//  OnceAgain
//
//  Created by 王少培 on 14-5-4.
//
//

#ifndef __OnceAgain__ScaleMoveTaiko__
#define __OnceAgain__ScaleMoveTaiko__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
class CScaleMoveTaiko : public CCActionInterval
{
public:
    /**
     *  @js ctor
     */
    CScaleMoveTaiko()
    :  m_pInnerAction(NULL)
    {}
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CScaleMoveTaiko(void);
    
    //inline float getSpeed(void) { return m_fSpeed; }
    /** alter the speed of the inner function in runtime */
    //inline void setSpeed(float fSpeed) { m_fSpeed = fSpeed; }
    
    /** initializes the action */
    bool initWithAction(CCActionInterval *pAction,const CCPoint& ptStart,const CCPoint& ptTarget);
    /**
     *  @js NA
     *  @lua NA
     */
    virtual CCObject* copyWithZone(CCZone *pZone);
    virtual void startWithTarget(CCNode* pTarget);
    virtual void stop();
    virtual void step(float dt);
    virtual bool isDone(void);
    virtual CCActionInterval* reverse(void);
    
    void setInnerAction(CCActionInterval *pAction);
    
    inline CCActionInterval* getInnerAction()
    {
        return m_pInnerAction;
    }
    
public:
    /** create the action */
    static CScaleMoveTaiko* create(CCActionInterval* pAction,const CCPoint& ptStart,const CCPoint& ptTarget);
protected:
    CCPoint mptStart;
    CCPoint mptTarget;
    CCActionInterval *m_pInnerAction;
};
#endif /* defined(__OnceAgain__ScaleMoveTaiko__) */
