

#include "GameItemManager.h"
#include "TaikoData.h"
#include "PlayerInfoManager.h"
#include "StringUtil.h"
#include "TaskDefine.h"
USING_NS_CC;
static CTaikoData* s_pTaikoData = NULL;
CTaikoData* CTaikoData::getInstance()
{
    if(s_pTaikoData==NULL){
        s_pTaikoData = CTaikoData::create();
		s_pTaikoData->retain();
        //s_pFruitData->init();
    }
    return s_pTaikoData;
}
void CTaikoData::purge()
{
    CC_SAFE_RELEASE_NULL(s_pTaikoData);
}
CTaikoData::CTaikoData():mnInvaildCellHitTimes(0),mnInvaildCellGenTimes(0),mlLastShakeDrumTime(0)
{
	//mStateOp = ETaikoOpNone;
}
CTaikoData::~CTaikoData()
{
   // this->flush();
	clearEffect();
}
bool CTaikoData::init()
{
	//加入强化
	auto pE = new CTaikoIntensifyAddScore();
	pE->mfEffectVal = 0;
	addEffect(pE);
	auto pE1 = new CTaikoIntensifyGenLongCell();
	pE1->mfEffectVal = 0;
	addEffect(pE1);
	auto pE2 = new CTaikointensifyShakeDrum();
	pE2->mfEffectVal = 0.f ;
	addEffect(pE2);

	//加入游戏道具
	auto pE4 = new CTaikoGameEffectScore();
	addEffect(pE4);
	auto pE5 = new CTaikoGameEffectShakeDrum();
	addEffect(pE5);
	
	
    return true;
}
void CTaikoData::reset()
{
    //int gold = /*STATIC_DATA_INT("default_gold")*/;
	setAnger(0);
		mnInvaildCellHitTimes = 0;
		mnInvaildCellGenTimes = 0;
//     this->setGold(gold);
//     this->setIsBeginner(true);
//     this->setMusicVolume(1);
//     this->setSoundVolume(1);
//     this->flush();
}
int CTaikoData::getContinueNum()
{
	int nNum = mnContinueNum - 1;
	if( nNum < 0)
		return 0;
	return nNum;
}
int CTaikoData::getCrazyContinueNum()
{
	int nNum = mnCrazyContinueNum - 1;
	if( nNum < 0)
		return 0;
	return nNum;
}
void CTaikoData::alterAnger(int delta)
{
    this->setAnger(this->getAnger()+delta);
	if(getAnger() >= 100)
	{
		setGenBomb(true);
		setAnger(0);
	}
}
void CTaikoData::alterContinueNum(int delta)
{
	setContinueNum(mnContinueNum + delta);
	if(getContinueNum() > 1)
	{
		alterAnger(4);
	}
}
void CTaikoData::alterCrazyContinueNum(int delta)
{
	setCrazyContinueNum(mnCrazyContinueNum + delta);
	CCLOG("alterCrazyContinueNum = %d",getCrazyContinueNum());
}

void CTaikoData::alterScore(int delta)
{
	int nScore = delta;
// 	if(CFruitData::getInstance()->getContinueNum() >= 20)
// 	{
// 		nScore *= FRUIT_CRAZY_ADD_2;
// 	}else if(CFruitData::getInstance()->getContinueNum() >= 10)
// 	{
// 		nScore *= FRUIT_CRAZY_ADD_1;
// 	}
	setScore(this->getScore()+nScore);
}
int CTaikoData::getCrazyAdd()
{
	int nVal = 1;
	if(getMode() == eSuperCrazyMode)
	{
		nVal = 3;
	}else if(getMode() == eComCrazyMode)
	{
		nVal = 2;
	}
	return nVal;
}
void CTaikoData::updataMode()
{
	if(mMode == eComCrazyMode && getContinueNum() >= TAIKO_SUPER_MODE_CONTINUE_NEED_TIMES)
	{
		mMode = eSuperCrazyMode;
	}else if(mMode == eNoneMode && getContinueNum() >= TAIKO_COM_MODE_CONTINUE_NEED_TIMES)
	{
		mMode = eComCrazyMode;
	}
}
//////////////////////////////////////////////////////////////////////////
//效果相关
CTaikoBaseEffect* CTaikoData::getEffect(ETaikoEffectType eType)
{
	for (int i = 0; i < mVecEffect.size(); ++i)
	{
		if(mVecEffect[i]->getType() == eType)
			return mVecEffect[i];
	}
	return NULL;
}
void CTaikoData::delEffect(ETaikoEffectType eType)
{
	for (int i = 0; i < mVecEffect.size(); ++i){
		CTaikoBaseEffect* pEffect = mVecEffect[i];
		if (pEffect->getType() == eType){
			CC_SAFE_DELETE(pEffect);
			mVecEffect.erase(mVecEffect.begin()+i);
		}
	}
}
void CTaikoData::addEffect(CTaikoBaseEffect* pEffect)
{
	mVecEffect.push_back(pEffect);
}
void CTaikoData::clearEffect()
{
	for (int i = 0; i < mVecEffect.size(); ++i)
	{
		CTaikoBaseEffect* pEffect = mVecEffect[i];
		CC_SAFE_DELETE(pEffect);
	}
	mVecEffect.clear();
}
float CTaikoData::toSpeed(float fDisplacement,CCPoint ptStart,CCPoint ptEnd)
{
	float fDistance = ccpDistance(ptStart,ptEnd);
	float fSpeed = fDistance / fDisplacement * CCDirector::sharedDirector()->getDeltaTime();
	return fSpeed;
}
float CTaikoData::toDisplacement(float fTargetSpeed,CCPoint ptStart,CCPoint ptEnd)
{
	float fDistance = ccpDistance(ptStart,ptEnd);
	float fDeltaTime = CCDirector::sharedDirector()->getDeltaTime();
	float fDistanceCell = fDeltaTime/fTargetSpeed * fDistance;
	return fDistanceCell;
}
void CTaikoData::setEffectStrengthenVal(e_GameType eGameType,int nStrengthenId,float fEffVal)
{
	if (nStrengthenId == eTaikoIntensifyAddScore){
		CTaikoIntensifyAddScore* pEff = (CTaikoIntensifyAddScore*)CTKData.getEffect(eTaikoIntensifyAddScore);
		if (pEff){
			pEff->mfEffectVal = fEffVal * RAND_GAME_BASE_VAL;
		}
	}else if (nStrengthenId == eTaikoIntensifyGenLongCell)
	{
		CTaikoIntensifyGenLongCell* pEff = (CTaikoIntensifyGenLongCell*)CTKData.getEffect(eTaikoIntensifyGenLongCell);
		if (pEff){
			pEff->mfEffectVal = fEffVal* RAND_GAME_BASE_VAL_10000;
		}
	}else if (nStrengthenId == eTaikointensifyShakeDrum)
	{
		CTaikointensifyShakeDrum* pEff = (CTaikointensifyShakeDrum*)CTKData.getEffect(eTaikointensifyShakeDrum);
		if (pEff){
			pEff->mfEffectVal = fEffVal ;
		}
	}
}
void CTaikoData::addEffectByItemId(int nItemId)
{
	switch(nItemId)
	{
	case ItemTag_2:
		addEffect(new CTaikoPayEffectSkipErr());
		break;
	case ItemTag_3:
		addEffect(new CTaikoEffectTimeDelay());
		break;
	case ItemTag_18:
		addEffect(new CTaikoPayEffectABlow());
		break;
	case ItemTag_19:
		addEffect(new CTaikoPayEffectAddSpeed());
		CTaskManProceDt(eDayTaskTypeShare_10,1);
		break;
	}
	setNoUsePlayItem(false);
}
//////////////////////////////////////////////////////////////////////////