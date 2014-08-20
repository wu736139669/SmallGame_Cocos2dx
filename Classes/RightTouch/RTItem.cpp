
#include "RTItem.h"
#include "RightTouchData.h"
#include "RandomUtil.h"
#include "SpriteFrameManage.h"
#include "AudioHelper.h"
#include "AudioDefine.h"
#include "RTItemLayer.h"
#include "ImageDownloader.h"
#include "StringUtil.h"
#include "EffectActionHelp.h"
#include "GameUIExportJson.h"
#include "TaskDefine.h"

//////////////////////////////////////////////////////////////////////////
CRTItem::CRTItem():mpSprite(NULL),mpAni(NULL),mnType(1),
	mState(1),mpLight(NULL),mpEffectBelow(NULL),mpEffectAbove(NULL),mbMerge(false),mbExeDelEff(true)
	//mEffect(eRTItemEffectNone)
{

}
CRTItem::~CRTItem()
{

}
bool CRTItem::init()
{
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	if (mpSprite == NULL)
		mpSprite = CCSprite::createWithSpriteFrame(cache->spriteFrameByName("cell1_1.png"));
	if(mpLight == NULL)
	{
		mpLight = CCSprite::createWithSpriteFrame(cache->spriteFrameByName("cell_sel.png"));
		mpLight->setVisible(false);
	}
	if(mpEffectAbove == NULL)
	{
		mpEffectAbove = CCSprite::createWithSpriteFrame(cache->spriteFrameByName("cell_sel.png"));
		mpEffectAbove->setVisible(false);
	}
	if(mpEffectBelow == NULL)
	{
		mpEffectBelow = CCSprite::createWithSpriteFrame(cache->spriteFrameByName("cell_sel.png"));
		mpEffectBelow->setVisible(false);
	}
		
	addChild(mpSprite,eItemLayerItem);
	addChild(mpLight,eItemLayerItemBelow);
	addChild(mpEffectBelow,eItemLayerItemBelow);
	addChild(mpEffectAbove,eItemLayerItemAbove);
	//static int sId = 1000;
	//sId += 1;
	//CImageDownloader::GetInstance()->SendHttpRequest("http://neoimaging.beareyes.com.cn/png2/ni_png_2_1518.png", this, CStringUtil::ToString(sId).c_str(), sId);
	return true;
}
void CRTItem::onEnter()
{
	CCNode::onEnter();
}
void CRTItem::onExit()
{
	CCNode::onExit();
}
void CRTItem::reverseClick()
{
	mpLight->setVisible(false);
}
void CRTItem::executeClick()
{
// 	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
// 	char strName[256]="";
// 	sprintf(strName,"Item/fruit%dPress.png",mnType);
// 	mpSprite->setDisplayFrame(cache->spriteFrameByName(strName));
// 	mpSprite->setScale(1.2f);
// 	CCActionInterval* pScaleBy = CCScaleBy::create(1.f, 0.8);
// 	CCActionInterval* pAction = CCSequence::create(pScaleBy, pScaleBy->reverse(), NULL);
// 	mpSprite->runAction(CCRepeatForever::create(pAction));
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
	CCString str;
	if(mState == TR_STATE_MAX)
		str.initWithFormat("cell_sel_star.png");
	else
		str.initWithFormat("cell_sel.png");
	mpLight->setDisplayFrame(cache->spriteFrameByName(str.getCString()));
	mpLight->setVisible(true);
	CAudioHelper::playSound(eSoundTypeRightTouchSelete);
}

void CRTItem::randItem()
{ 
	int nTypeNum = 2;
	if (CRightTouchData::getInstance()->getScore() > RT_DIFF_SCORE_1)
		nTypeNum = 3;
	if (CRightTouchData::getInstance()->getScore() > RT_DIFF_SCORE_2)
		nTypeNum = 4;

	//测试数据
	static int ncounter = 0;
	ncounter++;
	
// 	if(ncounter == 1)
// 		addEffect(eRTItemEffectRow);
// 	if(ncounter == 2)
// 	{
// 		addEffect(eRTItemEffectCol);
// 		addEffect(eRTItemEffectCol);
// 	}
// 		
// 	if(ncounter == 5)
// 	{
// 		addEffect(eRTItemEffectCol);
// 		addEffect(eRTItemEffectBomb);
// 	}
// 	if(ncounter == 7)
// 	{
// 		addEffect(eRTItemEffectColour);
// 	}
// 	if(ncounter == 10)
// 		addEffect(eRTItemEffectBomb);
 	//if (ncounter == 8)
// 	{
 	//	addEffect(eRTItemEffectScore);
// 	}
// 	if (ncounter == 9)
// 	{
// 		addEffect(eRTItemEffectScore);
// 	}
	//////////////////////////////////////////////////////////////////////////
		
	int nRandType = CRandomUtil::RandomRange(1,nTypeNum);
	setType(nRandType);
	//useItem(eRTIntensifyEffectGenBigCell)
	CRTItemLayer* p = ((CRTItemLayer*)getParent());
	if(p&&p->useItem(eRTIntensifyEffectGenBigCell))
	{
		setState(eRTItemState2);
		CTaskManProceDt(eDayTaskTypeRT_16,1);
	}	
	else
		setState(eRTItemState1);
	updataCell();
	showEffect();
// 	if (ncounter == 1)
// 	{
// 		setContentSize(CCSizeMake(50,50));
// 		CImageDownloader::GetInstance()->SendHttpRequest("http:\/\/tp1.sinaimg.cn\/2686746864\/180\/5622541917\/1",this,"1000",1000);
// 	}
	//randItemEffectGen();
}
void CRTItem::randItemEffectGen()
{
	//if(getGenEffect())
		//return;
	int nTemp = CRandomUtil::RandomRange(0,eRTItemEffectScore);//不生成炸弹
	//setEffect((ERTItemEffect)nTemp);
	addEffect((ERTItemEffect)nTemp);
	//setGenEffect(false);
}
void CRTItem::executeMerge()
{
	CCSpriteFrameManage* cache = CCSpriteFrameManage::getInstance();
	CCAnimation* pAni = CCAnimation::create();
	CCString str;
	str.initWithFormat("cell%d_%d.png",mnType,1);
	pAni->addSpriteFrame(cache->spriteFrameByName(str.getCString()));
	str.initWithFormat("cell%d_%d.png",mnType,12);
	pAni->addSpriteFrame(cache->spriteFrameByName(str.getCString()));
	str.initWithFormat("cell%d_%d.png",mnType,2);
	pAni->addSpriteFrame(cache->spriteFrameByName(str.getCString()));

	pAni->setDelayPerUnit(0.3/3.f);
	pAni->setLoops(1);
	CCFiniteTimeAction*  action3 = CCSequence::create(
		CCAnimate::create(pAni),
		CCCallFuncND::create(this, callfuncND_selector(CRTItem::executeMerageCallback), (void*)this), 
		NULL);
	mpSprite->runAction(action3);
}
void CRTItem::executeMerageCallback(CCNode* sender, void* data)
{
	if(getState() < eRTItemState2)
		setState(getState()+1);
	updataCell();
	setMerge(false);
	showEffect();
}
void CRTItem::setState(int state)
{
	if(mpSprite == NULL)
		return;
	mState = state;
	return ;
}
int CRTItem::getState()
{
	return mState;
 }
void CRTItem::addEffect(ERTItemEffect effect,bool bFront)
{
	CRTItemEffect e;
	e.mType = effect;
	switch(effect)
	{
	case eRTItemEffectScore:
		e.mnMask.setMask(eRTEffectMaskMulCellDel);
		e.mVecOp.push_back(eRTOperateDel);
		e.mVecOp.push_back(eRTOperateItem);
		e.mVecOp.push_back(eRTOperateMerge);
		break;
	case eRTItemEffectRow:
	case eRTItemEffectCol:
	case eRTItemEffectBomb:
	case eRTItemEffectColour:
		e.mVecOp.push_back(eRTOperateItem);
		e.mVecOp.push_back(eRTOperateDel);
		break;
	}
	if (effect == eRTItemEffectBomb || bFront)
		mVecEffect.insert(mVecEffect.begin(),e);
	else
		mVecEffect.push_back(e);
}
// void CRTItem::setEffect(ERTItemEffect effect)
// {
// 	mEffect = effect;
// }
ERTItemEffect CRTItem::getEffect()
{
	if(mVecEffect.empty())
		return eRTItemEffectNone;
	return mVecEffect[0].mType;
}
CRTItemEffect* CRTItem::getRealEffect()
{
	if(mVecEffect.empty())
		return NULL;
	return &mVecEffect[0];
}
void CRTItem::delEffect()
{
	ERTItemEffect effect = getEffect();
	for (int i = 0; i < mVecEffect.size(); ++i)
	{
		if(mVecEffect[i].mType == effect && mVecEffect[i].mbInvalid)
			mVecEffect.erase(mVecEffect.begin() + i);
	}
}
void CRTItem::showEffect()
{
	ERTItemEffect effect = getEffect();
	mpEffectBelow->setVisible(false);
	mpEffectAbove->setVisible(false);
	mpEffectAbove->setScale(1.0f);
	mpEffectAbove->setRotation(0);
	mpEffectAbove->stopAllActions();
	if (effect ==  eRTItemEffectCol)
	{
		mpEffectAbove->setDisplayFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName("rt_col.png"));
		mpEffectAbove->setVisible(true);
		CCFiniteTimeAction* pRotate = CCRotateBy::create(0.05, 10);
		CCFiniteTimeAction*  seq = CCSequence::create(CCRotateBy::create(0.05, 10),pRotate->reverse(),CCRotateTo::create(0.0f, 0),NULL);
		CCActionInterval*  rep1 = CCRepeat::create(seq, 4);
		CCActionInterval*  seq1 = CCSequence::create(rep1, CCDelayTime::create(1.2),NULL);
		mpEffectAbove->runAction( CCRepeatForever::create(seq1));
	}else if (effect ==  eRTItemEffectRow)
	{
		mpEffectAbove->setDisplayFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName("rt_row.png"));
		mpEffectAbove->setVisible(true);
		CCFiniteTimeAction* pRotate = CCRotateBy::create(0.05, 10);
		CCFiniteTimeAction*  seq = CCSequence::create(CCRotateBy::create(0.05, 10),pRotate->reverse(),NULL);
		 CCActionInterval*  rep1 = CCRepeat::create(seq, 4);
		 CCActionInterval*  seq1 = CCSequence::create(rep1, CCDelayTime::create(1.2),NULL);
		mpEffectAbove->runAction( CCRepeatForever::create(seq1));

	}else if (effect ==  eRTItemEffectScore)
	{
		mpEffectAbove->setDisplayFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName("rt_x5.png"));
		mpEffectAbove->setVisible(true);
	}else if (effect == eRTItemEffectBomb)
	{
		mpEffectAbove->setDisplayFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName("common/bomb.png"));
		mpEffectAbove->setScale(0.6f);
		CCActionInterval* pScaleBy = CCScaleBy::create(1.f, 1.1f);
		CCActionInterval* pAction = CCSequence::create(pScaleBy, pScaleBy->reverse(), NULL);
		mpEffectAbove->runAction(CCRepeatForever::create(pAction));
		mpEffectAbove->setVisible(true);
	}else if (effect == eRTItemEffectColour)
	{
		mpEffectAbove->setDisplayFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName("rt_colour.png"));
		mpEffectAbove->setVisible(true);
		mpEffectAbove->setScale(1.f);
		CCActionInterval* pScaleBy = CCScaleBy::create(1.f, 1.1f);
		CCActionInterval* pAction = CCSequence::create(pScaleBy, pScaleBy->reverse(), NULL);
		mpEffectAbove->runAction(CCRepeatForever::create(pAction));
	}
}
void CRTItem::executeEffect()
{
	ERTItemEffect effect = getEffect();
	CRTItemEffect* pRealEffect = getRealEffect();
	switch(effect)
	{
	case eRTItemEffectBomb:{
			if(pRealEffect->mbInvalid){
				CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTICE_RT_BOMB_EFFECT);
				CTaskManProceDt(eDayTaskTypeShare_8,1);
				CRtData.setUseBomb(true);
			}
		}
		break;
	case eRTItemEffectColour:
		{
			
		}
	case eRTItemEffectCol:
		{
		}
		break;
	}
}

void CRTItem::setType(int nType)
{
	if(mpSprite == NULL)
		return;
	mnType = nType;
}
void CRTItem::updataCell()
{
	CCString str;
	str.initWithFormat("cell%d_%d.png",mnType,mState);
	CCSpriteFrameManage* cache = CCSpriteFrameManage::getInstance();
	mpSprite->setDisplayFrame(cache->spriteFrameByName(str.getCString()));
}
// void CGameFruit::PlayIceAin(float fTotalTime)
// {
// 	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
// 	CCAnimation* pAni = CCAnimation::create();
// 	CCString str;
// 	for( int i=1;i<=3;i++)
// 	{
// 		str.initWithFormat("Item/ice%d.png",i);
// 		//sprintf(szName, "Item/ice1.png", i);
// 		pAni->addSpriteFrame(cache->spriteFrameByName(str.getCString()));
// 	}
// 	pAni->setDelayPerUnit(fTotalTime/3.f);
// 	pAni->setLoops(1);
// 	CCFiniteTimeAction*  action3 = CCSequence::create(
// 		CCAnimate::create(pAni),
// 		CCCallFuncND::create(this, callfuncND_selector(CGameFruit::AniCallback), (void*)this), 
// 		NULL);
// 	mpIce->runAction(action3);
// }
// void CGameFruit::AniCallback(CCNode* sender, void* data)
// {
// 	CGameFruit* pFruit = (CGameFruit*)data;
// 	if (pFruit)
// 	{
// 		//pFruit->SetByIce(false);
// 		pFruit->SetState(eEffectNone);
// 	}
// }
//////////////////////////////////////////////////////////////////////////

CRTItemField::CRTItemField():mpBg(NULL),mpItem(NULL)
{

}
CRTItemField::~CRTItemField()
{

}
bool CRTItemField::init()
{
	CCNode::init();
	
	return true;
}
void CRTItemField::onEnter()
{
	CCNode::onEnter();
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	if (mpBg == NULL)
	{
		//mpBg = CCSprite::createWithSpriteFrame(cache->spriteFrameByName("cell_bg.png"));
		mpBg = CCSprite::create();
		mpBg->setVisible(false);
		addChild(mpBg);
		mpSpEffectIn = CCSprite::create();
		mpSpEffectIn->setVisible(false);
		addChild(mpSpEffectIn);
	}
		
}
void CRTItemField::onExit()
{
	CCNode::onExit();
}
CCPoint CRTItemField::GetCentrePos()
{
	return ccp(mRect.getMidX(),mRect.getMidY());
}
void CRTItemField::genIteming()
{
	getItem()->getSprite()->setVisible(false);
	getItem()->getLight()->setVisible(false);
	//if (mpItem->getState() == TR_STATE_MAX)
	{
		//消除效果
// 		CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
// 		CCString str;
// 		if(getItem()->getState() == TR_STATE_MAX)
// 			str.initWithFormat("cell_sel%d.png",getItem()->getType());
// 		CCSpriteFrame* pFrame = cache->spriteFrameByName(str.getCString());
// 		if(pFrame)
// 		{
// 			mpSpEffectOut->setDisplayFrame(pFrame);
// 		}
// 		mpSpEffectOut->setVisible(true);
// 
// 		//外圈放大
// 		mpSpEffectOut->setScale(1.f);
// 	
// 		CCFiniteTimeAction*  action1 = CCSequence::create(
// 			CCScaleTo::create(0.5f,3.f,3.f),
// 			CCCallFuncND::create(this, callfuncND_selector(CRTItemField::starCallback), (void*)this),
// 			NULL);
// 		mpSpEffectOut->runAction(action1);
		CCAnimation* pAni = CCAnimation::create();
		CCString str;
		if(mpItem->getExeDelEff()){	
			for (int i = 1; i <= 5; ++i){
				str.initWithFormat("effect/bomb/%d.png",i);
				pAni->addSpriteFrameWithFileName(str.getCString());
			}
			pAni->setDelayPerUnit(0.5f/5.f);
			pAni->setLoops(1);
			CCFiniteTimeAction*  pAction = CCSequence::create(
				CCAnimate::create(pAni),
				CCCallFuncND::create(this, callfuncND_selector(CRTItemField::genCallback), (void*)this), 
				NULL);
			mpBg->setVisible(true);
			mpBg->runAction(pAction);
		}else
		{
//			CCFiniteTimeAction*  action1 = CCSequence::create(
// 			CCScaleTo::create(0.5f,3.f,3.f),
// 			CCCallFuncND::create(this, callfuncND_selector(CRTItemField::starCallback), (void*)this),
// 			NULL);
// 		mpSpEffectOut->runAction(action1);
			for (int i = 1; i <= 3; ++i){
				str.initWithFormat("effect/merge/%d.png",i);
				pAni->addSpriteFrameWithFileName(str.getCString());
			}
			pAni->setDelayPerUnit(0.4f/3.f);
			pAni->setLoops(1);
			CCFiniteTimeAction*  pAction = CCSequence::create(
				CCAnimate::create(pAni),
				CCCallFuncND::create(this, callfuncND_selector(CRTItemField::starCallback), (void*)this), 
				NULL);
			mpBg->setVisible(true);
			mpBg->runAction(pAction);
			mpItem->setExeDelEff(true);
		}
	}
}
void CRTItemField::starCallback(CCNode* sender, void* data)
{
	//mpSpEffectIn->setVisible(false);
	//mpSpEffectOut->setVisible(false);
	genCallback(NULL,NULL);
	((CRTItemLayer*)getParent())->exeIntensifyEffQuickGrow();
}
void CRTItemField::executeSkipErrEff()
{
// 	CCString strFileName;
// 	CCAnimation* pAni = CCAnimation::create();
// 	for (int i = 1; i <= 3; ++i){
// 		strFileName.initWithFormat("effect/shield/%d.png",i);
// 		pAni->addSpriteFrameWithFileName(strFileName.getCString());
// 	}
// 	pAni->setDelayPerUnit(0.1f);
// 	pAni->setLoops(1);
	//mpItem->getEffectAbove()->runAction(CCSequence::create(CCShow::create(),CCAnimate::create(pAni),CCHide::create(),NULL));
	CEffectActionHelper::play(eHelpShield,mpItem);
}
void CRTItemField::executeEffect()
{
	mpItem->executeEffect();
	if (mpItem->getRealEffect()&&!mpItem->getRealEffect()->mbInvalid )
		return;
	if (mpItem->getEffect() == eRTItemEffectBomb)
	{
		CEffectActionHelper::play(eHelp5Second,this);
	}else if (mpItem->getEffect() == eRTItemEffectScore)
	{
		CEffectActionHelper::play(eHelpMul5,this);
	}
	else if (mpItem->getEffect() == eRTItemEffectCol)
	{
		float fOffset = ((CRTItemLayer*)this->getParent())->getFieldGameArea().getMidY() - getPositionY();
		mpSpEffectIn->setPositionY(mpSpEffectIn->getPositionY() + fOffset);

		CCAnimation* pAni = CCAnimation::create();
		CCString str;
		for (int i = 1; i <= 5; ++i){
			str.initWithFormat("effect/lighting/%d.png",i);
			//pAni->addSpriteFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName(str.getCString()));
			pAni->addSpriteFrameWithFileName(str.getCString());
		}
		pAni->setDelayPerUnit(0.5f/5.f);
		pAni->setLoops(1);
		CCFiniteTimeAction*  pAction = CCSequence::create(
		 	CCAnimate::create(pAni),
		 	CCCallFuncND::create(this, callfuncND_selector(CRTItemField::effectInCallback), (void*)this), 
		 	NULL);
		mpSpEffectIn->runAction(pAction);
		mpSpEffectIn->setVisible(true);
		CTaskManProceDt(eDayTaskTypeRT_28,1);
		
	}else if (mpItem->getEffect() == eRTItemEffectRow)
	{
		float fOffset = ((CRTItemLayer*)this->getParent())->getFieldGameArea().getMidX() - getPositionX();
		mpSpEffectIn->setPositionX(mpSpEffectIn->getPositionX() + fOffset);
		mpSpEffectIn->setRotation(-90.f);
		CCAnimation* pAni = CCAnimation::create();
		CCString str;
		for (int i = 1; i <= 5; ++i){
			str.initWithFormat("effect/lighting/%d.png",i);
			pAni->addSpriteFrameWithFileName(str.getCString());
		}
		pAni->setDelayPerUnit(0.5f/5.f);
		pAni->setLoops(1);
		CCFiniteTimeAction*  pAction = CCSequence::create(
			CCAnimate::create(pAni),
			CCCallFuncND::create(this, callfuncND_selector(CRTItemField::effectInCallback), (void*)this), 
			NULL);
		mpSpEffectIn->runAction(pAction);
		mpSpEffectIn->setVisible(true);
		CTaskManProceDt(eDayTaskTypeRT_27,1);
	}
}
void CRTItemField::effectInCallback(CCNode* sender, void* data)
{
	mpSpEffectIn->setPosition(ccp(0,0));
	mpSpEffectIn->setVisible(false);
	mpSpEffectIn->setRotation(0);
}
void CRTItemField::genCallback(CCNode* sender, void* data)
{
	mpBg->setVisible(false);
	getItem()->setVisible(true);
	getItem()->getSprite()->setVisible(true);
	getItem()->randItem();
	getItem()->updataCell();

	//getItem()->delEffect();
}
void CRTItemField::selWrong()
{
	getItem()->getLight()->setVisible(false);
	getItem()->runAction(
		CCRepeat::create(
		CCSequence::create(
		CCMoveBy::create(0.05f, ccp(10,0)),
		CCMoveBy::create(0.05f, ccp(-10,0)),
		NULL),5));
	CTaskManProceDt(eDayTaskTypeShare_12,1);
}
void CRTItemField::reset()
{
	mpItem->getLight()->setVisible(false);
	mpItem->setVisible(false);
	mpItem->getEffectAbove()->setVisible(true);
	mpItem->getEffectBelow()->setVisible(false);
}
bool CRTItemField::isActionRun()
{
	if(mpItem == NULL)
		return false;
	if(mpBg == NULL)
		return false;
	if(mpItem->numberOfRunningActions() > 0)
		return true;
	if(mpItem->getSprite()->numberOfRunningActions() > 0)
		return true;
// 	if(mpBg->numberOfRunningActions() > 0)
// 	return true;

	return false;
}
bool CRTItemField::isGenIng()
{
	if(mpBg->numberOfRunningActions() > 0)
		return true;
	return false;
}