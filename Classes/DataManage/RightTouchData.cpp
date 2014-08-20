

#include "RightTouchData.h"
#include "RightTouchDefine.h"
#include "GameItemManager.h"
USING_NS_CC;
static CRightTouchData* s_pFruitData = NULL;
CRightTouchData* CRightTouchData::getInstance()
{
    if(s_pFruitData==NULL){
        s_pFruitData = CRightTouchData::create();
		s_pFruitData->retain();
        //s_pFruitData->init();
    }
    return s_pFruitData;
}
void CRightTouchData::purge()
{
    CC_SAFE_RELEASE_NULL(s_pFruitData);
}
CRightTouchData::CRightTouchData()
{
	mbItemGen = false;
	mnItemGenVal = 0;
	mnItemGenValLimit = 100;
}
CRightTouchData::~CRightTouchData()
{
   // this->flush();
}
bool CRightTouchData::init()
{
	//加入强化
	auto pE = new CFrIntersifyEffectQuickGrow();
	pE->mnEffectVal = 0;
	addEffect(pE);
	auto pE1 = new CFrIntersifyEffectGenBigCell();
	pE1->mnEffectVal = 0;
	addEffect(pE1);
	auto pE2 = new CFrIntersifyEffectSubItemGenVal();
	pE2->mnEffectVal = 0;
	addEffect(pE2);
	return true;
}
void CRightTouchData::reset()
{
	CBaseData::reset();
	setAnger(0);
	mnItemGenVal = 0;
	mbItemGen = false;
	mnItemGenValLimit = 100;
}
void CRightTouchData::alterAnger(int delta)
{
    this->setAnger(this->getAnger()+delta);
	if(getAnger() >= 100)
	{
		setGenBomb(true);
		setAnger(0);
	}
}
void CRightTouchData::alterContinueNum(int delta)
{
	setContinueNum(mnContinueNum + delta);
}
void CRightTouchData::alterCrazyContinueNum(int delta)
{
	setCrazyContinueNum(getCrazyContinueNum() + delta);
}

void CRightTouchData::alterScore(int delta)
{
	int nScore = delta;
	setScore(this->getScore()+nScore);
}
int CRightTouchData::getCrazyAdd()
{
	int nVal = 1;
	if(getContinueNum() >= 20)
	{
		nVal = TR_CRAZY_ADD_2;
	}else if(getContinueNum() >= 10)
	{
		nVal = TR_CRAZY_ADD_1;
	}
	return nVal;
}
void CRightTouchData::alterItemGenVal(int delta)
{
	setItemGenVal(getItemGenVal() + delta);
	
	if(getItemGenVal() >= getItemGenValLimit())
	{
		setItemGen(true);
		setItemGenVal(0);
	}
}

void CRightTouchData::updataMode()
{
	if(mMode == eComCrazyMode && getContinueNum() >= RT_SUPER_MODE_CONTINUE_NEED_TIMES)
	{
		mMode = eSuperCrazyMode;
	}else if(mMode == eNoneMode && getContinueNum() >= 10)
	{
		mMode = eComCrazyMode;
	}
}

int CRightTouchData::getContinueNum()
{
	int nNum = mnContinueNum - 1;
	if( nNum < 0)
		return 0;
	return nNum;

}
CRTBaseEffect* CRightTouchData::getEffect(ERTEffectType eType)
{
	for (int i = 0; i < mVecEffect.size(); ++i)
	{
		if(mVecEffect[i]->getType() == eType)
			return mVecEffect[i];
	}
	return NULL;
}
void CRightTouchData::delEffect(ERTEffectType eType)
{
	for (int i = 0; i < mVecEffect.size(); ++i){
		CRTBaseEffect* pEffect = mVecEffect[i];
		if (pEffect->getType() == eType){
			CC_SAFE_DELETE(pEffect);
			mVecEffect.erase(mVecEffect.begin()+i);
		}
	}
}
void CRightTouchData::addEffect(CRTBaseEffect* pEffect)
{
	mVecEffect.push_back(pEffect);
}
void CRightTouchData::addEffectByItemId(int nItemId)
{
	switch(nItemId)
	{
	case ItemTag_1://疯狂开局
		addEffect(new CRTEffectCrazy());
		break;
	case ItemTag_2://避免失误
		addEffect(new CRTEffectSkipErr());
		break;
	case ItemTag_3://时间延长
		addEffect(new CRTEffectTimeDelay());
		break;
	case ItemTag_4://染色剂
		addEffect(new CRTEffectColourOpen());
		break;
	}    
	setNoUsePlayItem(false);
}
void CRightTouchData::clearEffect()
{
	for (int i = 0; i < mVecEffect.size(); ++i)
	{
		CRTBaseEffect* pEffect = mVecEffect[i];
		CC_SAFE_DELETE(pEffect);
	}
	mVecEffect.clear();
}
void CRightTouchData::setEffectStrengthenVal(e_GameType eGameType,int nStrengthenId,float fEffVal)
{
	if (nStrengthenId == eRTIntensifyEffectGenBigCell){
		CFrIntersifyEffectGenBigCell* pEff = (CFrIntersifyEffectGenBigCell*)CRtData.getEffect(eRTIntensifyEffectGenBigCell);
		if (pEff){
			pEff->mnEffectVal = fEffVal * RAND_GAME_BASE_VAL;
		}
	}else if (nStrengthenId == eRTIntensifyEffectSubItemGenVal)
	{
		CFrIntersifyEffectSubItemGenVal* pEff = (CFrIntersifyEffectSubItemGenVal*)CRtData.getEffect(eRTIntensifyEffectSubItemGenVal);
		if (pEff){
			pEff->mnEffectVal = fEffVal;
		}
	}else if (nStrengthenId == eRTIntensifyEffectQuickGrow)
	{
		CFrIntersifyEffectQuickGrow* pEff = (CFrIntersifyEffectQuickGrow*)CRtData.getEffect(eRTIntensifyEffectQuickGrow);
		if (pEff){
			pEff->mnEffectVal = fEffVal* RAND_GAME_BASE_VAL;
		}
	}
}