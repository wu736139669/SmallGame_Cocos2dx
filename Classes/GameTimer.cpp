/***************************************************************
* 
*
*  ���ߣ�		������
*  �ļ�����		CGameTimer.cpp
*  ����ʱ�䣺	
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