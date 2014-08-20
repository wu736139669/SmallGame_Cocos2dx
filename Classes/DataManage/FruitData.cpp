

#include "FruitData.h"
#include "GameFruitDefine.h"
#include "GameItemManager.h"
USING_NS_CC;
static CFruitData* s_pFruitData = NULL;
CFruitData* CFruitData::getInstance()
{
    if(s_pFruitData==NULL){
        s_pFruitData = CFruitData::create();
		s_pFruitData->retain();
        //s_pFruitData->init();
    }
    return s_pFruitData;
}
void CFruitData::purge()
{
    CC_SAFE_RELEASE_NULL(s_pFruitData);
}
CFruitData::CFruitData()
{
	 mnAnger = 0;
	mnScore = 0;
	 mnContinueNum = 0;
	 mnCrazyContinueNum = 0;
	 mbGenBomb = 0;
	mnAccumulateRow = -5;
	 mbAccumulateCol = 0;
	 mnAccumulateRowLimit = FRUIT_DEL_ACC;
	 mbAccumulateColLimit = FRUIT_DEL_ACC;
}
CFruitData::~CFruitData()
{
   // this->flush();
	clearEffect();
}
bool CFruitData::init()
{
//     mIsBeginner = CCUserDefault::sharedUserDefault()->getBoolForKey("beginner",true);
//     if(mIsBeginner == true){
//         this->reset();
//         this->flush();
//         this->setIsBeginner(false);
//     }else{
//         mIsBeginner = CCUserDefault::sharedUserDefault()->getBoolForKey("beginner");
// //          = CCUserDefault::sharedUserDefault()->getFloatForKey("sound");
// //         _musicVolume = CCUserDefault::sharedUserDefault()->getFloatForKey("music");
//        // mnAnger = CCUserDefault::sharedUserDefault()->getIntegerForKey("anger");
//         CCUserDefault::sharedUserDefault()->purgeSharedUserDefault();
//     }
	//加入强化
	auto pE = new CFrIntersifyEffectGoldFinger();
	pE->mnEffectVal = 0;
	addEffect(pE);
	auto pE1 = new CFrIntersifyEffectAnyBall();
	pE1->mnEffectVal = 0;
	addEffect(pE1);
	auto pE2 = new CFrIntersifyEffectItem();
	pE2->mnEffectVal = 0;
	addEffect(pE2);
    return true;
}
void CFruitData::reset()
{
    //int gold = /*STATIC_DATA_INT("default_gold")*/;
	setAnger(0);
	mnAccumulateRow = -5;
	mbAccumulateCol = 0;
	mnAccumulateRowLimit = FRUIT_DEL_ACC;
	mbAccumulateColLimit = FRUIT_DEL_ACC;
		
//     this->setGold(gold);
//     this->setIsBeginner(true);
//     this->setMusicVolume(1);
//     this->setSoundVolume(1);
//     this->flush();
}
int CFruitData::getContinueNum()
{
	int nNum = mnContinueNum - 1;
	if( nNum < 0)
		return 0;
	return nNum;
}
int CFruitData::getCrazyContinueNum()
{
	int nNum = mnCrazyContinueNum - 1;
	if( nNum < 0)
		return 0;
	return nNum;
}
void CFruitData::alterAnger(int delta)
{
    this->setAnger(this->getAnger()+delta);
	if(getAnger() >= 100)
	{
		setGenBomb(true);
		setAnger(0);
	}
}
void CFruitData::alterContinueNum(int delta)
{
	setContinueNum(mnContinueNum + delta);
	if(getContinueNum() > 1)
	{
		alterAnger(5);
	}
}
void CFruitData::alterCrazyContinueNum(int delta)
{
	setCrazyContinueNum(mnCrazyContinueNum + delta);
	CCLOG("alterCrazyContinueNum = %d",getCrazyContinueNum());
}

void CFruitData::alterScore(int delta)
{
	int nScore = delta;
	if(CFruitData::getInstance()->getContinueNum() >= 20)
	{
		nScore *= FRUIT_CRAZY_ADD_2;
	}else if(CFruitData::getInstance()->getContinueNum() >= 10)
	{
		nScore *= FRUIT_CRAZY_ADD_1;
	}
	setScore(this->getScore()+nScore);
}
int CFruitData::getMode()
{
	if(CFruitData::getInstance()->getContinueNum() >= 20)
	{
		return eSuperCrazyMode;
	}else if(CFruitData::getInstance()->getContinueNum() >= 10)
	{
		return eComCrazyMode;
	}
	return eNoneMode;
}
void CFruitData::flush()
{
    CCUserDefault::sharedUserDefault()->setFloatForKey("sound", this->getSoundVolume());
    CCUserDefault::sharedUserDefault()->setBoolForKey("beginner", this->getIsBeginner());
    CCUserDefault::sharedUserDefault()->setIntegerForKey("anger", this->getAnger());
    CCUserDefault::sharedUserDefault()->setFloatForKey("music", this->getMusicVolume());
    CCUserDefault::sharedUserDefault()->flush();
    CCUserDefault::sharedUserDefault()->purgeSharedUserDefault();
}
//////////////////////////////////////////////////////////////////////////
//效果相关
CFrBaseEffect* CFruitData::getEffect(EFrEffectType eType)
{
	for (int i = 0; i < mVecEffect.size(); ++i)
	{
		if(mVecEffect[i]->getType() == eType)
			return mVecEffect[i];
	}
	return NULL;
}
void CFruitData::delEffect(EFrEffectType eType)
{
	for (int i = 0; i < mVecEffect.size(); ++i){
		CFrBaseEffect* pEffect = mVecEffect[i];
		if (pEffect->getType() == eType){
			CC_SAFE_DELETE(pEffect);
			mVecEffect.erase(mVecEffect.begin()+i);
		}
	}
}
void CFruitData::addEffect(CFrBaseEffect* pEffect)
{
	mVecEffect.push_back(pEffect);
}
void CFruitData::clearEffect()
{
	for (int i = 0; i < mVecEffect.size(); ++i)
	{
		CFrBaseEffect* pEffect = mVecEffect[i];
		CC_SAFE_DELETE(pEffect);
	}
	mVecEffect.clear();
}
void CFruitData::addEffectByItemId(int nItemId)
{
	switch(nItemId)
	{
	case ItemTag_5:
		addEffect(new CFrEffectAddContinueHit());
		break;
	case ItemTag_7:
		addEffect(new CFrEffectColourOpen());
		break;
	case ItemTag_6:
		addEffect(new CFrEffectCrossOpen());
		break;
	case ItemTag_3:
		addEffect(new CFrEffectTimeDelay());
		break;
	}
	setNoUsePlayItem(false);
}

void CFruitData::setEffectStrengthenVal(e_GameType eGameType,int nStrengthenId,float fEffVal)
{
	if (nStrengthenId == eFrIntensifyAnyBall){
		CFrIntersifyEffectAnyBall* pEff = (CFrIntersifyEffectAnyBall*)getEffect(eFrIntensifyAnyBall);
		if (pEff){
			pEff->mnEffectVal = fEffVal * RAND_GAME_BASE_VAL;
		}
	}else if (nStrengthenId == eFrintensifyItem)
	{
		CFrIntersifyEffectItem* pEff = (CFrIntersifyEffectItem*)getEffect(eFrintensifyItem);
		if (pEff){
			pEff->mnEffectVal = fEffVal ;
		}
	}else if (nStrengthenId == eFrIntensifyEffectGoldFinger)
	{
		CFrIntersifyEffectGoldFinger* pEff = (CFrIntersifyEffectGoldFinger*)getEffect(eFrIntensifyEffectGoldFinger);
		if (pEff){
			pEff->mnEffectVal = fEffVal;
		}
	}
}