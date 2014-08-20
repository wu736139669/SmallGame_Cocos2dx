/***************************************************************
* 
*
*  作者：		王少培
*  文件名：		CGameTimer.cpp
*  创建时间：	
*
***************************************************************/

#include "GameTimer.h"

IMPLEMENT_SINGLETON(CGameTimer, ms_instance)

CGameTimer::CGameTimer()
: mTimeCounter(0)
{

}

CGameTimer::~CGameTimer()
{
	ResetTime();
}

unsigned int CGameTimer::GetNowTime() const
{
	return mTimeCounter;
}

void CGameTimer::ResetTime()
{
	mTimeCounter = 0;
}

void CGameTimer::Update( unsigned int deltaTime )
{
	mTimeCounter += deltaTime;
}