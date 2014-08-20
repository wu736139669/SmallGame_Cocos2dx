
/***************************************************************
* 
*
*  作者：		王少培
*  文件名：		
*  创建时间：	
*
***************************************************************/
#include "GameScheduler.h"
#include "GameCommand.h"
#include "GameTimer.h"
#include <algorithm>
#include "GameFruitField.h"
#include "FruitCommand.h"
#include "ImplementScheduler.h"

CImplementScheduler::CImplementScheduler()
{

}


CImplementScheduler::~CImplementScheduler()
{
}

//////////////////////////////////////////////////////////////////////////
//水果连线相关移动
void CImplementScheduler::FruitMove( unsigned int startTime, unsigned int duringTime,CCSprite* pFruit, CCPoint& ptDistance )
{
	CRoleMoveCommand* pCommand = new CRoleMoveCommand(startTime, duringTime,pFruit,ptDistance);
	CGameScheduler::GetInstance()->AddCommand(pCommand);
}
void CImplementScheduler::FruitOut(unsigned int startTime, unsigned int duringTime,CCObject* pFruit)
{
	CRoleOutCommand* pCommand = new CRoleOutCommand(startTime, duringTime,pFruit);
	CGameScheduler::GetInstance()->AddCommand(pCommand);
}
void CImplementScheduler::FruitLightning(unsigned int startTime, unsigned int duringTime,bool bRow,CCSprite* pFruit,CCPoint ptPos,CCObject* pParent,SEL_CallFuncND pCallFunc)
{
	CRoleLightningCommand* pCommand = new CRoleLightningCommand(startTime, duringTime,bRow,pFruit,ptPos,pParent,pCallFunc);
	CGameScheduler::GetInstance()->AddCommand(pCommand);
}
void CImplementScheduler::FruitBomb(unsigned int startTime, unsigned int duringTime,CCSprite* pFruit)
{
	CRoleBombAniCommand* pCommand = new CRoleBombAniCommand(startTime, duringTime,pFruit);
	CGameScheduler::GetInstance()->AddCommand(pCommand);
}
void CImplementScheduler::FruitMoveEnd( unsigned int startTime, unsigned int duringTime,CCNode* pMainLayer)
{
	CRoleMoveEndCommand* pCommand = new CRoleMoveEndCommand(startTime, duringTime,pMainLayer);
	CGameScheduler::GetInstance()->AddCommand(pCommand);
}
void CImplementScheduler::AllMoveEnd( unsigned int startTime, unsigned int duringTime,CCNode* pMainLayer)
{
	CAllMoveEndCommand* pCommand = new CAllMoveEndCommand(startTime, duringTime,pMainLayer);
	CGameScheduler::GetInstance()->AddCommand(pCommand);
}
void CImplementScheduler::FruitIceAni(unsigned int startTime, unsigned int duringTime,CGameFruit* pFruit)
{
	CIceAniCommand* pCommand = new CIceAniCommand(startTime, duringTime,pFruit);
	CGameScheduler::GetInstance()->AddCommand(pCommand);
}
void CImplementScheduler::ScoreFloat( unsigned int startTime, unsigned int duringTime,CCSprite* pScore,CCPoint pt)
{
	CScoreFloatCommand* pCommand = new CScoreFloatCommand(startTime, duringTime,pScore,pt);
	CGameScheduler::GetInstance()->AddCommand(pCommand);
}
//////////////////////////////////////////////////////////////////////////





