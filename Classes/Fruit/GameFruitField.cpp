#include "GameFruitField.h"
#include "FruitData.h"
#include "GameFruitDefine.h"
#include "RandomUtil.h"
#include "SpriteFrameManage.h"
#include "AudioHelper.h"
#include "AudioDefine.h"
#include "EffectActionHelp.h"
#include "GameItemManager.h"
#include "TaskDefine.h"
USING_NS_CC;
//////////////////////////////////////////////////////////////////////////

void CGameFruitEffect::addMask(int nMask)
{
	mnMask |= nMask;
}

bool CGameFruitEffect::isMask(int nMask)
{
	bool b = ((mnMask&nMask) == nMask);
	if(b)
		return true;
	return false;
}

//////////////////////////////////////////////////////////////////////////
CGameFruit::CGameFruit():mpSprite(NULL),mpAni(NULL),mpBombEff(NULL),mpIce(NULL),mpBombRang(NULL),mpLightning(NULL),mpLightningRow(NULL)
{

}
CGameFruit::~CGameFruit()
{

}
bool CGameFruit::init()
{
// 	if(mpAni)
// 	{
// 		mpAni = CCAnimation::create();
// 		CCString str;
//		for( int i=1;i<=3;i++)
//		{
//			str.initWithFormat("Item/ice%d.png",i);
			//sprintf(szName, "Item/ice1.png", i);
//			mpAni->addSpriteFrameWithFileName(str.getCString());
//		}
// 	}
	CCSpriteFrameManage* cache = CCSpriteFrameManage::getInstance();
	if(mpBombEff == NULL)
		mpBombEff = CCSprite::create();
	if(mpBombRang == NULL)
		mpBombRang = CCSprite::createWithSpriteFrame(cache->spriteFrameByName("item/line.png"));
	if(mpSprite == NULL)
		mpSprite = CCSprite::createWithSpriteFrame(cache->spriteFrameByName("item/fruit1.png"));
	if(mpLightning == NULL)
		mpLightning = CCSprite::create();
	if(mpLightningRow == NULL)
	{
		mpLightningRow = CCSprite::create();
	}
		
	return true;
}
void CGameFruit::ClickFruit()
{
	//pSprite->setScale(0.5);
	//pSprite->setPosition(ccp(visibleSize.width / 2, posEys.y));
	
	CCSpriteFrameManage* cache = CCSpriteFrameManage::getInstance();
	char strName[256]="";
	//sprintf(strName,"Item/fruit%dPress.png",mnType);
	//mpSprite->setDisplayFrame(cache->spriteFrameByName(strName));
	mpSprite->setScale(1.2f);
	CCActionInterval* pScaleBy = CCScaleBy::create(1.f, 0.8);
	CCActionInterval* pAction = CCSequence::create(pScaleBy, pScaleBy->reverse(), NULL);
	mpSprite->runAction(CCRepeatForever::create(pAction));
	CAudioHelper::playSound(eSoundTypeFruiteSelete);
}
void CGameFruit::NoClickFruit()
{
	//mpSprite->stopActionByTag(1);
	mpSprite->stopAllActions();
	CCSpriteFrameManage* cache = CCSpriteFrameManage::getInstance();
	char strName[256]="";
	//sprintf(strName,"Item/fruit%d.png",mnType);
	//mpSprite->setDisplayFrame(cache->spriteFrameByName(strName));
	mpSprite->setScale(1.f);
}
void CGameFruit::RandFruit()
{
	CFruitData* pData = CFruitData::getInstance()->getInstance();

	int nTypeNum = 3;
	if(pData->getScore() >= FRUIT_DIFF_SCORE_1)
		nTypeNum = 4;
	if(pData->getScore() >= FRUIT_DIFF_SCORE_2)
		nTypeNum = 5;

	//use superitem
	if(CItemMan::sharedInstance().useItem(ItemTag_17))
	{
		nTypeNum = 3;
	}

	char strName[256]="";
	int nRand =CRandomUtil::RandomRange(0,nTypeNum - 1);

	int nFruitType = nRand+1;
	chgFruit(nFruitType);

	static int nCounter = 0;
	++nCounter;
 	//if (nCounter == 9)
// 	{
 	//	addEffect(eEffectBomb);
// 	}
// 	if (nCounter == 1)
// 	{
// 		addEffect(eEffectHor);
// 	}
// 	if (nCounter == 2)
// 	{
// 		addEffect(eEffectVertical);
// 	}
// 	if (nCounter == 3)
// 	{
// 		addEffect(eEffectHor);
// 	}
// 	if (nCounter == 4)
// 	{
// 		addEffect(eEffectCross);
// 	}
// 	if (nCounter == 10)
// 	{
// 		addEffect(eEffectColour);
// 	}
// 	if (nCounter == 43)
// 	{
// 		addEffect(eEffectCross);
// 	}
 	//if (nCounter == 11)
// 	{
 	//	addEffect(eEffectMultipleUse);
// 	}
	showEffect();
}
void CGameFruit::chgFruit(int nFruitType){
	CCString strFileName;
	strFileName.initWithFormat("item/fruit%d.png",nFruitType);
	if(mpSprite)
		mpSprite->setDisplayFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName(strFileName.getCString()));
	setType(nFruitType);
}
void CGameFruit::shakeEffect()
{
	//CCFiniteTimeAction* pRotate = CCRotateBy::create(0.05, 10);
	CCActionInterval*  seq = CCSequence::create(CCRotateTo::create(0.05, 10),CCRotateTo::create(0.05, -10),NULL);
	mpSprite->runAction(CCRepeatForever::create(seq));
}
void CGameFruit::executeEffect()
{
	EFruitEffect effect = getEffectVal();
	mpBombRang->setVisible(false);
	switch(effect)
	{
	case eEffectBomb:
		{
			CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTICE_FRUIT_BOMB_EFFECT);
			CEffectActionHelper::play(eHelp5Second,mpSprite->getParent(),mpSprite->getPosition());
			CTaskManProceDt(eDayTaskTypeShare_8,1);
		}
		break;
	case eEffectColour:
		{

		}
		break;
	case eEffectMultipleUse:
		{
			CEffectActionHelper::play(eHelp20000,mpSprite->getParent(),mpSprite->getPosition());
			CTaskManProceDt(eDayTaskTypeFT_35,1);
		}
		break;
	}
}
void CGameFruit::showEffect()
{
	EFruitEffect state = getEffectVal();

	mpBombRang->setVisible(false);
	mpBombRang->stopAllActions();
	mpBombRang->setPosition(mpSprite->getPosition());
	CCString strName;
	strName.initWithFormat("item/effect%d_%d.png",mnType,state);
	if(state == eEffectHor){
		mpSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(strName.getCString())); 
		
		CCAnimation* pAni = CCAnimation::create();
		for( int i=1;i<=5;i++){
			strName.initWithFormat("effect/gem_ef/%d.png",i);
			pAni->addSpriteFrameWithFileName(strName.getCString());
		}
		pAni->setDelayPerUnit(0.12f);
		pAni->setLoops(1);
		mpBombRang->setVisible(true);
		mpBombRang->runAction(CCRepeatForever::create(CCAnimate::create(pAni)));
		
	}else if (state == eEffectVertical)
	{
		
		mpSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(strName.getCString())); 
		CCAnimation* pAni = CCAnimation::create();
		for( int i=1;i<=5;i++){
			strName.initWithFormat("effect/gem_ef/%d.png",i);
			pAni->addSpriteFrameWithFileName(strName.getCString());
		}
		pAni->setDelayPerUnit(0.12f);
		pAni->setLoops(1);
		mpBombRang->setVisible(true);
		mpBombRang->runAction(CCRepeatForever::create(CCAnimate::create(pAni)));
	}else if (state == eEffectBomb)
	{
		mpBombRang->setVisible(true);
		//mpBombCross->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Item/ice1.png")); 
		mpBombRang->setPosition(mpSprite->getPosition());
		mpBombRang->setDisplayFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName("common/bomb.png"));
		mpBombRang->setScale(0.39f);
		CCActionInterval* pScaleBy = CCScaleBy::create(1.f, 1.1f);
		CCActionInterval* pAction = CCSequence::create(pScaleBy, pScaleBy->reverse(), NULL);
		mpBombRang->runAction(CCRepeatForever::create(pAction));
		
	}else if (state == eEffectColour)
	{
// 		mpBombCross->setVisible(true);
// 		mpBombCross->setPosition(mpSprite->getPosition());
// 		mpBombCross->runAction( CCRepeatForever::create(CCRotateBy::create(1, 90)));
		strName.initWithFormat("item/effect%d.png",state);
		mpSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(strName.getCString())); 
		CCAnimation* pAni = CCAnimation::create();
		for( int i=1;i<=5;i++){
			strName.initWithFormat("effect/gem_ef/%d.png",i);
			pAni->addSpriteFrameWithFileName(strName.getCString());
		}
		pAni->setDelayPerUnit(0.12f);
		pAni->setLoops(1);
		mpBombRang->setVisible(true);
		mpBombRang->runAction(CCRepeatForever::create(CCAnimate::create(pAni)));
	}else if (state ==  eEffectCross)
	{
// 		mpBombCross->setVisible(true);
// 		mpBombCross->setPosition(mpSprite->getPosition());
// 		mpBombCross->runAction( CCRepeatForever::create(CCRotateBy::create(1, 90)));
		mpSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(strName.getCString())); 
		CCAnimation* pAni = CCAnimation::create();
		for( int i=1;i<=5;i++){
			strName.initWithFormat("effect/gem_ef/%d.png",i);
			pAni->addSpriteFrameWithFileName(strName.getCString());
		}
		pAni->setDelayPerUnit(0.12f);
		pAni->setLoops(1);
		mpBombRang->setVisible(true);
		mpBombRang->runAction(CCRepeatForever::create(CCAnimate::create(pAni)));
	}else if (state == eEffectMultipleUse)
	{
		//strName.initWithFormat("item/effect%d.png",state);
		//mpSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(strName.getCString())); 
		chgFruit(eFruitTypeMulUse);
		CCAnimation* pAni = CCAnimation::create();
		for( int i=1;i<=5;i++){
			strName.initWithFormat("effect/gem_ef/%d.png",i);
			pAni->addSpriteFrameWithFileName(strName.getCString());
		}
		pAni->setDelayPerUnit(0.12f);
		pAni->setLoops(1);
		mpBombRang->setVisible(true);
		mpBombRang->runAction(CCRepeatForever::create(CCAnimate::create(pAni)));
	}
	return ;
}
EFruitEffect CGameFruit::getEffectVal()
{
	CGameFruitEffect* pEffect = getFrontEffect();
	if (pEffect == NULL)
		return eEffectNone;
	return pEffect->mType;
}
CGameFruitEffect* CGameFruit::getFrontEffect()
{
	if(mVecEffect.empty())
		return NULL;
	return &mVecEffect[0];
}
void CGameFruit::addEffect(EFruitEffect effect)
{
	CGameFruitEffect e;
	e.mType = effect;
	switch(effect)
	{
	case eEffectHor:
	case eEffectVertical:
	case eEffectCross:
		e.addMask(FR_MASK_ALLOW_ONLY_ONE_ITEM_DEL);
		break;
	case eEffectColour:
		break;
	case eEffectBomb:
		e.addMask(FR_MASK_ALLOW_ONLY_ONE_ITEM_DEL);
		e.addMask(FR_MASK_TARGET_EFFECT);
		break;
	case eEffectMultipleUse:
		break;
	}
	if(effect != eEffectBomb)
		mVecEffect.push_back(e);
	else
		mVecEffect.insert(mVecEffect.begin(),e);
}
void CGameFruit::delEffect()
{
	EFruitEffect effect = getEffectVal();
	for (int i = 0; i < mVecEffect.size(); ++i)
	{
		if(mVecEffect[i].mType == effect && mVecEffect[i].mbInvalid)
			mVecEffect.erase(mVecEffect.begin() + i);
	}
}
bool CGameFruitField::isGenIng()
{
// 	if (mpScore->numberOfRunningActions() > 0)
// 	{
// 		return true;
// 	}
// 	if (getFruit()->getSprite()->numberOfRunningActions() > 0)
// 	{
// 		return true;
// 	}
	if (getFruit()->getSprite()->getActionByTag(eFrActionGening))
	{
		return true;
	}
	if (getFruit()->getBombEff()->getActionByTag(eFrActionGening))
	{
		return true;
	}
	return false;
}
void CGameFruit::PlayIceAin(float fTotalTime)
{
	//CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
	CCSpriteFrameManage* cache = CCSpriteFrameManage::getInstance();
	CCAnimation* pAni = CCAnimation::create();
	CCString str;
	for( int i=1;i<=3;i++)
	{
		str.initWithFormat("item/ice%d.png",i);
		//sprintf(szName, "Item/ice1.png", i);
		pAni->addSpriteFrame(cache->spriteFrameByName(str.getCString()));
	}
	pAni->setDelayPerUnit(fTotalTime/3.f);
	pAni->setLoops(1);
	CCFiniteTimeAction*  action3 = CCSequence::create(
		CCAnimate::create(pAni),
		CCCallFuncND::create(this, callfuncND_selector(CGameFruit::AniCallback), (void*)this), 
		NULL);
	mpIce->runAction(action3);
}
void CGameFruit::AniCallback(CCNode* sender, void* data)
{
	CGameFruit* pFruit = (CGameFruit*)data;
	if (pFruit)
	{
		//pFruit->SetByIce(false);
		pFruit->addEffect(eEffectNone);
	}
}
void CGameFruit::delFruit()
{
	mpSprite->setVisible(false);
	//mpBombCross->setVisible(false);
	mpBombRang->setVisible(false);
	//SetState(eEffectNone);
}
bool CGameFruit::isDelFruit()
{
	if (mpSprite->isVisible())
	{
		return true;
	}
	return false;
}
//////////////////////////////////////////////////////////////////////////

CGameFruitField::CGameFruitField():mpFruit(NULL),mpLine(NULL),mpScore(NULL)
{

}
CGameFruitField::~CGameFruitField()
{

}
cocos2d::CCPoint CGameFruitField::GetCentrePos()
{
	return ccp(mRect.getMidX(),mRect.getMidY());
}
void CGameFruitField::ResetScore()
{
	//mpScore->setPosition(GetCentrePos());
}
void CGameFruitField::UpdataScore()
{
	//mpScore->setPosition(GetCentrePos());
	int nNum = CFruitData::getInstance()->getContinueNum();
	int nGetScore = 0;
	if(nNum <= 1)
		return;
	if (nNum < 3)
	{
		nGetScore = 100; //= CCSprite::get("./game_fruit/iPhone-hd/score100.png");
	}else if(nNum < 7)
	{
		nGetScore = 200;
	}else if (nNum < 14)
	{
		nGetScore = 500;
	}else
	{
		nGetScore = 1000;
	}
	//CFruitData::getInstance()->setScore();
	
}
