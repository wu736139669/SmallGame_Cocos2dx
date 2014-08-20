
/***************************************************************
* 
*
*  作者：		王少培
*  文件名：		
*  创建时间：	
*
***************************************************************/
#include "GameCommand.h"

//------------------------------------------------------

CGameCommand::CGameCommand( unsigned int startTime, unsigned int duringTime )
: mStartTime(startTime)
, mDuringTime(duringTime)
, mEndTime(startTime + duringTime)
, mDone(false)
{

}

CGameCommand::~CGameCommand()
{

}

void CGameCommand::Execute()
{
	mDone = true;
}

unsigned int CGameCommand::GetStartTime() const
{
	return mStartTime;
}

unsigned int CGameCommand::GetDuringTime() const
{
	return mDuringTime;
}

unsigned int CGameCommand::GetEndTime() const
{
	return mEndTime;
}

bool CGameCommand::IsDone() const
{
	return mDone;
}

void CGameCommand::SetDone( bool bDone )
{
	mDone = bDone;
}

//------------------------------------------------------

