

#include "BaseData.h"
USING_NS_CC;

CBaseData::CBaseData()
{
	 mnAnger = 0;
	mnScore = 0;
	 mnContinueNum = 0;
	 mnCrazyContinueNum = 0;
	 mbGenBomb = 0;
	 mMode = eNoneMode;
	 mbUseBomb = false;
	 mbNoUsePlayItem = true;
    mfLastCrazyTime = -1.f;
}
CBaseData::~CBaseData()
{
   // this->flush();
}

void CBaseData::reset()
{
	mnAnger = 0;
	mnScore = 0;
	mnContinueNum = 0;
	mnCrazyContinueNum = 0;
	mbGenBomb = 0;
	mMode = eNoneMode;
    mfLastCrazyTime = -1.f;
}
