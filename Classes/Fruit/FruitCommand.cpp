

#include "GameFruitScene.h"
#include "GameFruitField.h"
#include "FruitData.h"
#include "GameFruitDefine.h"
#include "FruitCommand.h"

//------------------------------------------------------

CRoleMoveCommand::CRoleMoveCommand( unsigned int startTime, unsigned int duringTime, CCSprite* pFruit, CCPoint& ptDistance )
: CGameCommand(startTime, duringTime)
{
	SetFruit(pFruit);
	SetDistance(ptDistance);
}

CRoleMoveCommand::~CRoleMoveCommand()
{

}

void CRoleMoveCommand::Execute()
{
	if (mFruit)
	{
		float fDuringTime = (float)mDuringTime / (float)1000.f;
		CCActionInterval* pMove = CCMoveBy::create(fDuringTime,mDistance);
		CCActionInterval* pMoveEaseIn = CCEaseElasticOut::create(pMove,0.5f);
		mFruit->runAction(pMoveEaseIn);
	}

	CGameCommand::Execute();
}
//////////////////////////////////////////////////////////////////////////
CRoleOutCommand::CRoleOutCommand( unsigned int startTime, unsigned int duringTime, CCObject* pFruit)
	: CGameCommand(startTime, duringTime)
{
	SetFruit(pFruit);
}

void CRoleOutCommand::Execute()
{
	if (mFruit){
		CGameFruit* pFruit = (CGameFruit*)mFruit;
		pFruit->RandFruit();
		CCSprite* p = (CCSprite*)pFruit->getSprite();
		p->setScale(0.2f);
		
		float fDuringTime = (float)mDuringTime / (float)1000.f;
		CCActionInterval* pScale1 = CCScaleTo::create(fDuringTime/2.f, 1.3f);
		CCActionInterval* pScale2 = CCScaleTo::create(fDuringTime/2.f, 1.f);
		CCActionInterval* pAct = CCSequence::create(CCShow::create(),pScale1,pScale2,NULL);
		pAct->setTag(eFrActionGening);
		p->runAction(pAct);
	}

	CGameCommand::Execute();
}
//////////////////////////////////////////////////////////////////////////
CRoleLightningCommand::CRoleLightningCommand(unsigned int startTime, unsigned int duringTime,bool bRow,CCSprite* pFruit,CCPoint ptPos,CCObject* pParent,SEL_CallFuncND pCallFunc)
	: CGameCommand(startTime, duringTime)
{
	setFruit(pFruit);
	setptPos(ptPos);
	setParent(pParent);
	setCallFunc(pCallFunc);
	setRow(bRow);
}

void CRoleLightningCommand::Execute()
{
	CCAnimation* pAni = CCAnimation::create();
	CCString str;
	float fDuringTime = (float)mDuringTime / (float)1000.f;
	mpFruit->setRotation(0.f);
	
	for (int i = 1; i <= 5; ++i){
		str.initWithFormat("effect/lighting/%d.png",i);
		//pAni->addSpriteFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName(str.getCString()));
		pAni->addSpriteFrameWithFileName(str.getCString());
	}
	pAni->setDelayPerUnit(fDuringTime/5.f);
	pAni->setLoops(1);
	if (!mbRow)
	{
		mpFruit->setPositionY(mptPos.y);
	}else
	{
		mpFruit->setPositionX(mptPos.x);
		mpFruit->setRotation(-90.f);
	}
	CCFiniteTimeAction*  pAction = NULL;
	if(mpParent)
	{
		  pAction = CCSequence::create(CCShow::create(),
			CCAnimate::create(pAni),CCHide::create(),
			CCCallFuncND::create(mpParent,mpCallFunc,(void*)mpParent), 
			NULL);
	}else
	{
		 pAction = CCSequence::create(CCShow::create(),
			CCAnimate::create(pAni) ,
			CCHide::create(),
			NULL);
	}
	mpFruit->runAction(pAction);
	CGameCommand::Execute();
}
//////////////////////////////////////////////////////////////////////////
CRoleBombAniCommand::CRoleBombAniCommand(  unsigned int startTime, unsigned int duringTime, CCSprite* pFruit)
	: CGameCommand(startTime, duringTime)
{
	SetFruit(pFruit);
}

CRoleBombAniCommand::~CRoleBombAniCommand()
{

}

void CRoleBombAniCommand::Execute()
{
	float fDuringTime = (float)mDuringTime / (float)1000.f;
	if (mFruit)
	{
		CCAnimation* pAni = CCAnimation::create();
		CCString str;
		
		for (int i = 1; i <= 5; ++i){
			str.initWithFormat("effect/bomb/%d.png",i);
			pAni->addSpriteFrameWithFileName(str.getCString());
		}
		pAni->setDelayPerUnit(fDuringTime/5.f);
		pAni->setLoops(1);
		CCFiniteTimeAction*  pAction = CCSequence::create(
			CCShow::create(),
			CCAnimate::create(pAni),
			CCHide::create(),
			NULL);
		pAction->setTag(eFrActionGening);
		mFruit->runAction(pAction);
	}
	CGameCommand::Execute();
}
//////////////////////////////////////////////////////////////////////////
CRoleMoveEndCommand::CRoleMoveEndCommand( unsigned int startTime, unsigned int duringTime,CCNode* pMainLayer )
	: CGameCommand(startTime, duringTime)
{
	setMainLayer(pMainLayer);
}

CRoleMoveEndCommand::~CRoleMoveEndCommand()
{

}

void CRoleMoveEndCommand::Execute()
{
	if (mpMainLayer)
	{
		((CGameFruitScene*)mpMainLayer)->UpdataField();
	}

	CGameCommand::Execute();
}

//////////////////////////////////////////////////////////////////////////

CScoreFloatCommand::CScoreFloatCommand( unsigned int startTime, unsigned int duringTime,CCSprite* pScore,CCPoint& pt )
	: CGameCommand(startTime, duringTime)
{
	setScore(pScore);
	setPoint(pt);
}

void CScoreFloatCommand::Execute()
{
	if (mpScore)
	{
		mpScore->setVisible(true);
		mpScore->setOpacity(255);
		float fDuringTime = (float)mDuringTime / (float)1000.f;
		 CCActionInterval* pMove = CCMoveBy::create(fDuringTime/2.f, mpPt);
		  CCActionInterval* pFadeIn = CCFadeOut::create(fDuringTime/2.f);
		CCSequence* seq1 = CCSequence::create(pMove,pFadeIn, NULL);
		mpScore->runAction(seq1);
	}

	CGameCommand::Execute();
}
//////////////////////////////////////////////////////////////////////////
CIceAniCommand::CIceAniCommand( unsigned int startTime, unsigned int duringTime,CGameFruit* pFruit )
	: CGameCommand(startTime, duringTime)
{
	setFruit(pFruit);
}

void CIceAniCommand::Execute()
{
	if (mpFruit)
	{
		float fDuringTime = (float)mDuringTime / (float)1000.f;
		mpFruit->PlayIceAin(fDuringTime);
	}

	CGameCommand::Execute();
}
//////////////////////////////////////////////////////////////////////////
CAllMoveEndCommand::CAllMoveEndCommand( unsigned int startTime, unsigned int duringTime,CCNode* pMainLayer )
	: CGameCommand(startTime, duringTime)
{
	setMainLayer(pMainLayer);
}
void CAllMoveEndCommand::Execute()
{
	if (mpMainLayer)
	{
		((CGameFruitScene*)mpMainLayer)->AllMoveEnd();
	}

	CGameCommand::Execute();
}

