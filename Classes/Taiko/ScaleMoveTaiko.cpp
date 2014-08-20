//
//  ScaleMoveTaiko.cpp
//  OnceAgain
//
//  Created by 王少培 on 14-5-4.
//
//

#include "ScaleMoveTaiko.h"
#include "TaikoCell.h"
CScaleMoveTaiko::~CScaleMoveTaiko()
{
    CC_SAFE_RELEASE(m_pInnerAction);
}

CScaleMoveTaiko* CScaleMoveTaiko::create(CCActionInterval* pAction,const CCPoint& ptStart,const CCPoint& ptTarget)
{
    CScaleMoveTaiko *pRet = new CScaleMoveTaiko();
    if (pRet && pRet->initWithAction(pAction,ptStart,ptTarget))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool CScaleMoveTaiko::initWithAction(CCActionInterval *pAction,const CCPoint& ptStart,const CCPoint& ptTarget)
{
    CCAssert(pAction != NULL, "");
    pAction->retain();
    m_pInnerAction = pAction;
    //m_fSpeed = fSpeed;
    mptStart = ptStart;
    mptTarget = ptTarget;
    return true;
}

CCObject *CScaleMoveTaiko::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CScaleMoveTaiko* pRet = NULL;
    if(pZone && pZone->m_pCopyObject) //in case of being called at sub class
    {
        pRet = (CScaleMoveTaiko*)(pZone->m_pCopyObject);
    }
    else
    {
        pRet = new CScaleMoveTaiko();
        pZone = pNewZone = new CCZone(pRet);
    }
    CCAction::copyWithZone(pZone);
    
    pRet->initWithAction( (CCActionInterval*)(m_pInnerAction->copy()->autorelease()) , mptStart,mptTarget );
    
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}

void CScaleMoveTaiko::startWithTarget(CCNode* pTarget)
{
    CCAction::startWithTarget(pTarget);
    m_pInnerAction->startWithTarget(pTarget);
}

void CScaleMoveTaiko::stop()
{
    m_pInnerAction->stop();
    CCAction::stop();
}

void CScaleMoveTaiko::step(float dt)
{
    m_pInnerAction->step(dt);
    float fLen = ccpDistance(mptStart, mptTarget);
    float fCurrLen = ccpDistance(mptStart, m_pTarget->getPosition());
    if(fCurrLen <= fLen)
    {
        float fDeta = fCurrLen/fLen;
        //if(fDeta >= m_pTarget->getScale())
		if(fDeta>1.f)
			fDeta = 1.f;
         m_pTarget->setScale(fDeta);
		 //CCLOG("%d fDeta = %f",m_pTarget,fDeta);
		//if(fDeta >= m_pTarget->getScale())
// 		{
			((CTaikoCell*)m_pTarget)->setSpeedFactor(1.f+ fDeta);
			((CTaikoCell*)m_pTarget)->executeASpeed();
// 		}
    }
}

bool CScaleMoveTaiko::isDone()
{
    return m_pInnerAction->isDone();
}

CCActionInterval *CScaleMoveTaiko::reverse()
{
    return (CCActionInterval*)(CScaleMoveTaiko::create(m_pInnerAction->reverse(), mptStart,mptTarget));
}

void CScaleMoveTaiko::setInnerAction(CCActionInterval *pAction)
{
    if (m_pInnerAction != pAction)
    {
        CC_SAFE_RELEASE(m_pInnerAction);
        m_pInnerAction = pAction;
        CC_SAFE_RETAIN(m_pInnerAction);
    }
}