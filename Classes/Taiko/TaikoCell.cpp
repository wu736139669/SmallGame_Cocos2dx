
#include "RandomUtil.h"
#include "SpriteFrameManage.h"
#include "AudioHelper.h"
#include "AudioDefine.h"
#include "TaikoDefine.h"
#include "TaikoCell.h"
#include "TaikoScene.h"
#include "ScaleMoveTaiko.h"
#include "EffectActionHelp.h"
#include "CCColorUtil.h"
#include "NumSprite.h"
#include "TaskDefine.h"
#include "TimeUtil.h"
//////////////////////////////////////////////////////////////////////////
//细胞提示
bool CTaikoCellHint::init()
{
	CCNode::init();
	if(mpHintBg == NULL){
		mpHintBg = CCSprite::create("CocoStudioResources/tai_ko/bg_hint.png");
		//mpHintBg->setAnchorPoint(ccp(0.5f,0.f));
	}
	if(mpHint == NULL){
		mpHint = CCSprite::create();
		//mpHint->setAnchorPoint(ccp(0.5f,0.f));
	}

	addChild(mpHintBg,0);
	addChild(mpHint,1);
	return true;
}
void CTaikoCellHint::showEffect(int nType)
{
	mpHint->setVisible(false);
	switch (nType)
	{
	case eTaikoEffectBomb:
		{
			mpHint->setDisplayFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName("common/bomb.png"));
			//mpHint->setAnchorPoint(ccp(0.5f,0.f));
			mpHint->setPositionX(10.f);
			mpHint->setScale(0.6f);
			CCActionInterval* pScaleBy = CCScaleBy::create(1.f, 1.1f);
			CCActionInterval* pAction = CCSequence::create(pScaleBy, pScaleBy->reverse(), NULL);
			mpHint->runAction(CCRepeatForever::create(pAction));
			mpHint->setVisible(true);
		}
		break;
	case eTaikoEffectScore:	//奖励分数
		{
			CCTexture2D* p = CCTextureCache::sharedTextureCache()->addImage("GameMemoryLayer/20000.png");
			//mpHint->setDisplayFrame(CCSpriteFrame::createWithTexture(p,));
			mpHint->setTexture(p);
			mpHint->setTextureRect(CCRectMake(0,0,p->getContentSize().width,p->getContentSize().height));
			//mpHint->setAnchorPoint(ccp(0.5f,0.f));
			mpHint->setPositionX(10.f);
			mpHint->setScale(0.7f);
			mpHint->setVisible(true);
		}
		break;
	case eTaikoEffectClickInvalid:	//不能按图形
		{

		}
		break;
	case eTaikoEffectShakeDrum:		//震鼓奖励阶段
		{

		}
		break;
	case eTaikoEffectPrefect:	//Perfect道具
		{
			/*mpHint->setDisplayFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName("CocoStudioResources/tai_ko/hint_perfect.png"));*/
			//mpHint->setTexture(CCTexAddImage("CocoStudioResources/tai_ko/hint_perfect.png"));
			NumSprite::setSpriteTexture(mpHint,CCTexAddImage("CocoStudioResources/tai_ko/hint_perfect.png"));
			mpHint->setPositionX(10.f);
			mpHint->setScale(0.4f);
			CCActionInterval* pScaleBy = CCScaleBy::create(1.f, 1.1f);
			CCActionInterval* pAction = CCSequence::create(pScaleBy, pScaleBy->reverse(), NULL);
			mpHint->runAction(CCRepeatForever::create(pAction));
			mpHint->setVisible(true);
		}
		break;
	}
}
void CTaikoCellHint::executeEffect(int nType)
{
	switch (nType)
	{
	case eTaikoEffectBomb:
		{
			
		}
		break;
	}
	
}
//////////////////////////////////////////////////////////////////////////
enum ETaikoLayer
{
	eTaikoLayerBelow = 0,
	eTaiKoLayerCell = 1,
	eTaiKoLayerAbove = 2,
};
CTaikoCell::CTaikoCell():mpSprite(NULL),mnType(1),mpSpriteTail(NULL)
	,mpEffectBelow(NULL),mpEffectAbove(NULL),mbExeDelEff(true),mfASpeed(1.f),mfSpeed(3.f),mbMiss(false)
	,mpHint(NULL),mbUse(true),mOpState(ETaikoOpNone),mpSpriteBg(NULL),mbClicking(false),mpSpriteEff(NULL),mfSpeedFactor(1.f)
	//mEffect(eRTItemEffectNone)
{

}
CTaikoCell::~CTaikoCell()
{

}
void CTaikoCell::reset()
{
	mbUse = true;
	mnType = 1;
	mpEffectBelow->setVisible(false);
	mpEffectAbove->setVisible(false);
	mpSpriteTail->setVisible(false);
	mpSpriteBg->setVisible(false);
	mbExeDelEff = true;
	mfASpeed = 1.f;
	mfSpeed = 3.f;
	mbMiss = false;
	mpHint->setVisible(false);
	mVecEffect.clear();
	mVecRandInfo.clear();
	mOpState = ETaikoOpNone;
}
bool CTaikoCell::init()
{
	if(mpSpriteEff == NULL)
		mpSpriteEff = CCSprite::create();
	if (mpSprite == NULL)
		mpSprite = CCSprite::create();
	if(mpSpriteTail == NULL)
		mpSpriteTail = CCSprite::create();
	if(mpEffectAbove == NULL){
		mpEffectAbove = CCSprite::create("CocoStudioResources/tai_ko/bg_hint.png");
		mpEffectAbove->setVisible(false);
		mpEffectAbove->setAnchorPoint(ccp(0.5f,0.f));
	}
	if(mpEffectBelow == NULL){
		mpEffectBelow = CCSprite::create();
		mpEffectBelow->setVisible(false);
		mpEffectBelow->setAnchorPoint(ccp(0.5f,0.f));
	}
	if (mpSpriteBg == NULL)
	{
		mpSpriteBg = CCSprite::create();
		mpSpriteBg->setVisible(false);
	}
	if (mpHint == NULL)
	{
		mpHint = CTaikoCellHint::create();
		//mpHint->setAnchorPoint(ccp(0.5f,0.f));
		mpHint->setVisible(false);
	}
	addChild(mpSpriteTail,eTaiKoLayerCell);
	addChild(mpSpriteBg,eTaiKoLayerCell);
	addChild(mpSprite,eTaiKoLayerCell);
	addChild(mpSpriteEff,eTaiKoLayerCell);
	
	addChild(mpEffectBelow,eTaikoLayerBelow);
	addChild(mpEffectAbove,eTaiKoLayerAbove);
	addChild(mpHint,eTaikoLayerBelow);
	return true;
}
void CTaikoCell::onEnter()
{
	CCNode::onEnter();
}
void CTaikoCell::onExit()
{
	CCNode::onExit();
}

void CTaikoCell::randCell()
{ 
// 	int nTypeNum = 2;
// 	if (CRightTouchData::getInstance()->getScore() > RT_DIFF_SCORE_1)
// 		nTypeNum = 3;
// 	if (CRightTouchData::getInstance()->getScore() > RT_DIFF_SCORE_2)
// 		nTypeNum = 4;

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
// 		//addEffect(eRTItemEffectCol);
// 		addEffect(eTaikoEffectBomb);
// 	}
// 	if(ncounter == 7)
// 	{
// 		addEffect(eRTItemEffectColour);
// 	}
// 	if(ncounter == 10)
// 		addEffect(eRTItemEffectBomb);
// 	if (ncounter == 8)
// 	{
// 		addEffect(eRTItemEffectScore);
// 	}
// 	if (ncounter == 9)
// 	{
// 		addEffect(eRTItemEffectScore);
// 	}
	//////////////////////////////////////////////////////////////////////////
	
	STaikoCellRandInfo info ;
	info.eType = eTaikoNone;
	info.fProbability = 0.f;
	//memset(&info,0,sizeof(info));
	//使用的
	float fUsePro = 0;
	//未用的
	float fUnuse = RAND_GAME_BASE_VAL_10000;
	if (((CTaikoScene*)getParent())->useItem(eTaikoIntensifyGenLongCell))
	{
		CTaikoIntensifyGenLongCell* p = (CTaikoIntensifyGenLongCell*)CTKData.getEffect(eTaikoIntensifyGenLongCell);
		info.eType = eTaikoType_1_Long;
		fUsePro = (fUnuse >= p->mfEffectVal/2) ? (fUsePro + p->mfEffectVal/2) : fUnuse;
		info.fProbability = fUsePro;
		mVecRandInfo.push_back(info);
		fUnuse = fUnuse > 0 ? RAND_GAME_BASE_VAL_10000 - fUsePro : 0;

		info.eType = eTaikoType_2_Long;
		fUsePro = (fUnuse >= p->mfEffectVal/2) ? (fUsePro + p->mfEffectVal/2) : fUnuse;
		info.fProbability = fUsePro;
		mVecRandInfo.push_back(info);
		fUnuse = fUnuse > 0 ?  RAND_GAME_BASE_VAL_10000 - fUsePro : 0;
	}
	info.eType = eTaikoType_Invalid;
	fUsePro = (fUnuse >= 0.05f * RAND_GAME_BASE_VAL_10000) ? (fUsePro + 0.05f * RAND_GAME_BASE_VAL_10000) : fUnuse;
	info.fProbability = fUsePro;
	mVecRandInfo.push_back(info);
	fUnuse = fUnuse > 0 ? RAND_GAME_BASE_VAL_10000 - fUsePro :0;

	info.eType = eTaikoType_1;
	fUsePro = fUnuse >= fUnuse/2.f ? fUsePro + fUnuse/2.f : fUnuse;
	info.fProbability = fUsePro;
	mVecRandInfo.push_back(info);
	fUnuse = fUnuse > 0 ? RAND_GAME_BASE_VAL_10000 - fUsePro : 0;

	info.eType = eTaikoType_2;
	fUsePro += fUnuse ;
	info.fProbability = fUsePro;
	mVecRandInfo.push_back(info);

	ETaikoType eType ;
	int nPro = CRandomUtil::RandomRange(1,RAND_GAME_BASE_VAL_10000);
	for (int i = 0; i < mVecRandInfo.size(); ++i){
		if(nPro <= mVecRandInfo[i].fProbability) {
			eType = mVecRandInfo[i].eType;
			break;
		}
	}
	CTaikoGameEffectShakeDrum* pS = (CTaikoGameEffectShakeDrum*)CTKData.getEffect(eTaikoGameEffectShakeDrum);
	if (pS->mbGening){
		eType = eTaikoType_BigDrum;
		CTaskManProceDt(eDayTaskTypeTK_53,1);
		//重置55类型任务
		CTaskManProceDt(eDayTaskTypeTK_55,0);

		long lTime = CTimeUtil::GetCocos2dxTimer() - CTKData.getLastShakeDrumTime();
		CTaskManProce(eDayTaskTypeTK_59,lTime/1000);
		CTKData.setLastShakeDrumTime(CTimeUtil::GetCocos2dxTimer());
	}
	setType(eType);
	updataCell();
	if (eType == eTaikoType_Invalid)
	{
		CTKData.setInvaildCellGenTimes(CTKData.getInvaildCellGenTimes() + 1);
	}
	if (eType != eTaikoType_BigDrum)
	{
		randCellEffectGen();
		showEffect();
	}
	//setPosition(ccp(GetVSe.width /2, GetVSe.height - 340));
}
void CTaikoCell::randCellEffectGen()
{
	//int nTemp = CRandomUtil::RandomRange(0,eRTItemEffectScore);//不生成炸弹
	//附在在道具上优先出现炸弹
	if(CTKData.getGenBomb()){
		addEffect(eTaikoEffectBomb);
		CTKData.setGenBomb(false);
	}
	//分数奖励0
	else if (((CTaikoScene*)getParent())->useItem(eTaikoGameEffectScore)){
		addEffect(eTaikoEffectScore);
	}
	//出现prefect道具
	else if (((CTaikoScene*)getParent())->useItem(eTaikoGameEffectPrefect)){
		addEffect(eTaikoEffectPrefect);
	}else if (((CTaikoScene*)getParent())->useItem(eTaikoIntensifyAddScore))
	{
		if (mnType != eTaikoType_1_Long && mnType != eTaikoType_2_Long)
			addEffect(eTaikoEffectIntensifyAddScore);
	}
	//prefect道具触发成功
	CTaikoGameEffectPrefect* p = (CTaikoGameEffectPrefect*)CTKData.getEffect(eTaikoGameEffectPrefect);
	if(p){
		if (p->mnUseTimes <= p->mnUseLimit){
			if (p->mbPerfectState){
				p->mnUseTimes += 1;
				mOpState = ETaikoOpPerfect;
			}
		}else{
			p->mnUseTimes = 0;
			p->mbPerfectState = false;
		}
	}
}
void CTaikoCell::moveTo(CCPoint& ptTarget)
{
 	//setScaleX(0.35f);
 	//setScaleY(0.2f);
	stopAllActions();
	setScale(0.1f/*1.f*/);
//    setScale(0.f);
	CCActionInterval* pActMove = NULL;
	if (mnType == eTaikoType_1_Long || mnType == eTaikoType_2_Long)
	{

	}else
	{
		
	}
	
	mfDisplacement =  CTKData.toDisplacement(mfSpeed,((CTaikoScene*)getParent())->getStartPos(),ccp(((CTaikoScene*)getParent())->getRcTarget().getMidX(), ((CTaikoScene*)getParent())->getRcTarget().getMinY()));
	float fWholeSpeed = CTKData.toSpeed(mfDisplacement,((CTaikoScene*)getParent())->getStartPos(),ptTarget);
	pActMove = CCMoveTo::create(fWholeSpeed,ccp(ptTarget.x,ptTarget.y));
	//CCActionInterval* pAct = CCSpawn::create(pActMove /*,CCScaleTo::create(mfSpeed - 1.f,1.f,1.f)*/,NULL);
    //CCAction* pSpd = CCSpeed::create(pAct,mfASpeed);
    CCActionInterval* pActScale = CScaleMoveTaiko::create(pActMove,((CTaikoScene*)getParent())->getStartPos()
                                                          ,ccp(((CTaikoScene*)getParent())->getRcTarget().getMidX(), ((CTaikoScene*)getParent())->getRcTarget().getMinY()));
    CCAction* pSpd = CCSpeed::create(pActScale,mfASpeed);

	pSpd->setTag(eTaikoCellActSpeed);
	runAction(pSpd);
}
void CTaikoCell::stopHead(float fOffectY)
{
// 	mpSprite->pauseSchedulerAndActions();
// 	mpSpriteBg->pauseSchedulerAndActions();
	//mpSprite->stopAllActions();
	//mpSpriteBg->stopAllActions();
   // CCLOG("getContentSize===%f",fOffectY);
 
	//mpSprite->setVisible(false);
	//mpSpriteBg->setVisible(false);
    mpSprite->setPositionY(fOffectY);
    //mpSprite->setScale(1.f);
    mpSpriteBg->setPositionY(fOffectY - (mpSpriteBg->getContentSize().height/2 - mpSprite->getContentSize().height/2));
	mpSpriteEff->setPositionY(fOffectY );
    //mpSpriteBg->setScale(1.f);
    //CCLOG("stopHead===%f",mpSprite->getPositionY());
}
void CTaikoCell::setType(int nType)
{
	mnType = nType;
}
void CTaikoCell::updataCell()
{
	mpSpriteTail->setVisible(false);
	mpSpriteTail->setScale(1.f);
	mpSpriteBg->setVisible(false);
    mpSprite->setPosition(ccp(0,0));
    mpSpriteBg->setPosition(ccp(0, 0));
	mpSpriteEff->setPosition(ccp(0, 0));
	mpSpriteEff->stopAllActions();
	mpSpriteEff->setVisible(false);
 	mpSprite->setAnchorPoint(ccp(0.5f,0.f));
 	mpSpriteEff->setAnchorPoint(ccp(0.5f,0.f));
 	mpSpriteBg->setAnchorPoint(ccp(0.5f,0.f));
	mpSprite->setVisible(true);
	mbClicking = false;
	CCString str;
	str.initWithFormat("CocoStudioResources/tai_ko/cell_%d.png",mnType);
	if (mnType == eTaikoType_1_Long){
		str.initWithFormat("CocoStudioResources/tai_ko/cell_1.png");
		//mpSprite->setDisplayFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName(str.getCString()));
		//mpSprite->setTexture(CCTexAddImage(str.getCString()));
		//mpSprite->setTextureRect(CCRectMake(0,0,CCTexAddImage(str.getCString())->getContentSize().width,CCTexAddImage(str.getCString())->getContentSize().height));
		NumSprite::setSpriteTexture(mpSprite,CCTexAddImage(str.getCString()));
		mpSpriteBg->setVisible(true);
		str.initWithFormat("CocoStudioResources/tai_ko/cell_bg_1.png");
		/*mpSpriteBg->setDisplayFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName(str.getCString()));*/
		//mpSpriteBg->setTexture(CCTexAddImage(str.getCString()));

		NumSprite::setSpriteTexture(mpSpriteBg,CCTexAddImage(str.getCString()));
		mpSpriteBg->setPositionY(mpSprite->getContentSize().height/2 - mpSpriteBg->getContentSize().height/2);
		str.initWithFormat("CocoStudioResources/tai_ko/cell_long_1.png");
		/*mpSpriteTail->setDisplayFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName(str.getCString()));*/

		//mpSpriteTail->setTexture(CCTexAddImage(str.getCString()));
		NumSprite::setSpriteTexture(mpSpriteTail,CCTexAddImage(str.getCString()));
		mpSpriteTail->setVisible(true);
		mpSpriteTail->setAnchorPoint(ccp(0.5f,1.f));
		//mpSpriteTail->setAnchorPoint(ccp(0.5f,1.f));
		mpSpriteTail->setPositionY(mpSpriteTail->getContentSize().height + mpSprite->getContentSize().height/*/2*/);
		
		//setContentSize(mpSprite->getContentSize() + mpSpriteTail->getContentSize());
	}
	else if (mnType == eTaikoType_2_Long)
	{
		str.initWithFormat("CocoStudioResources/tai_ko/cell_2.png");
		/*mpSprite->setDisplayFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName(str.getCString()));*/
		//mpSprite->setTexture(CCTexAddImage(str.getCString()));
		NumSprite::setSpriteTexture(mpSprite,CCTexAddImage(str.getCString()));

		str.initWithFormat("CocoStudioResources/tai_ko/cell_bg_2.png");
		/*mpSpriteBg->setDisplayFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName(str.getCString()));*/
		//mpSpriteBg->setTexture(CCTexAddImage(str.getCString()));
		NumSprite::setSpriteTexture(mpSpriteBg,CCTexAddImage(str.getCString()));
		mpSpriteBg->setVisible(true);
		mpSpriteBg->setPositionY(mpSprite->getContentSize().height/2 - mpSpriteBg->getContentSize().height/2);
		
		str.initWithFormat("CocoStudioResources/tai_ko/cell_long_2.png");
		//mpSpriteTail->setTexture(CCTexAddImage(str.getCString()));
		NumSprite::setSpriteTexture(mpSpriteTail,CCTexAddImage(str.getCString()));
		mpSpriteTail->setVisible(true);
		mpSpriteTail->setAnchorPoint(ccp(0.5f,1.f));
		mpSpriteTail->setPositionY(mpSpriteTail->getContentSize().height + mpSprite->getContentSize().height/*/2*/);
		
		//setContentSize(mpSprite->getContentSize() + mpSpriteTail->getContentSize());
	}else 
	{
		//mpSprite->setTexture(CCTexAddImage(str.getCString()));
		NumSprite::setSpriteTexture(mpSprite,CCTexAddImage(str.getCString()));
	}
	mrcCollisionArea =  mpSprite->getTextureRect();
	mrcCollisionAreaTail = mpSpriteTail->getTextureRect();
	mrcCollisionAreaLong = CCRectMake(0,0,mrcCollisionArea.size.width,mrcCollisionArea.size.height + mpSpriteTail->getContentSize().height);
	mpSprite->setVisible(true);
	mVecHitSplitInfo.clear();
	STaikoHitSplitInfo s1 = {0,false, 2.f/3.f * mrcCollisionAreaTail.size.height};
	mVecHitSplitInfo.push_back(s1);
	STaikoHitSplitInfo s2 = {0,false, 1.f/3.f * mrcCollisionAreaTail.size.height};
	mVecHitSplitInfo.push_back(s2);
	STaikoHitSplitInfo s3 = {0,false, 0.f/3.f * mrcCollisionAreaTail.size.height};
	mVecHitSplitInfo.push_back(s3);
	//CCSprite* pSp = CCSprite::createWithSpriteFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName(str.getCString()));
}


void CTaikoCell::executeASpeed()
{
	CCSpeed* p = dynamic_cast<CCSpeed*>(getActionByTag(eTaikoCellActSpeed));
	if(p) p->setSpeed(mfASpeed*mfSpeedFactor);
}
void CTaikoCell::executeDel(bool bAni )
{
	stopAllActions();
	mpHint->setVisible(false);
	mpSpriteEff->setVisible(false);
	if (bAni)
	{
		mbUse = false;
		mpSprite->setVisible(false);
		if (getType() == eTaikoType_2_Long || getType() == eTaikoType_1_Long)
		{
			mpSpriteEff->setVisible(false);
			mpSpriteBg->setVisible(false);
			mpSpriteTail->setVisible(false);
		}
		CCAnimation* pAni = CCAnimation::create();
		CCString str;

		for (int i = 1; i <= 5; ++i){
			str.initWithFormat("effect/bomb/%d.png",i);
			pAni->addSpriteFrameWithFileName(str.getCString());
		}
		pAni->setDelayPerUnit(0.5/5.f);
		pAni->setLoops(1);
		CCFiniteTimeAction*  pAction = CCSequence::create(
			CCShow::create(),
			CCAnimate::create(pAni),
			CCHide::create(),
			CCCallFunc::create(this,callfunc_selector(CTaikoCell::executeDelCallback)),
			NULL);
		mpEffectAbove->runAction(pAction);
		mpEffectAbove->setVisible(true);
		
		
	}else
	{
		setVisible(false);
		CCLOG("CTaikoCell::setVisible(false)");
	}
	
	
	((CTaikoScene*)getParent())->delCell(this);
}
void CTaikoCell::executeDelCallback()
{
	mbUse = true;
	
}
CCRect CTaikoCell::getCollisionArea()
{
	//CCRect rc = mpSprite->getTextureRect();
	CCPoint startInNodeSpace = CCPointZero;
	CCPoint startInWorldSpace = this->convertToWorldSpace(startInNodeSpace);
	//CCPoint targetInNodeSpace = this->getParent()->convertToNodeSpace(startInNodeSpace);
	CCRect rcTemp(startInWorldSpace.x - mrcCollisionArea.size.width/2, startInWorldSpace.y /*- mrcCollisionArea.size.height/2*/, mrcCollisionArea.size.width,mrcCollisionArea.size.height);
	if (getType() == eTaikoType_1_Long||getType() == eTaikoType_2_Long)
	{
		rcTemp = CCRectMake(startInWorldSpace.x - mrcCollisionArea.size.width/2, startInWorldSpace.y /*- mrcCollisionArea.size.height/2*/, mrcCollisionAreaLong.size.width,mrcCollisionAreaLong.size.height);
	}
	return rcTemp;
}
CCRect CTaikoCell::getCollisionAreaHead()
{
	CCPoint startInWorldSpace = this->convertToWorldSpace(CCPointZero);
	return CCRectMake(startInWorldSpace.x - mrcCollisionArea.size.width/2, startInWorldSpace.y/* - mrcCollisionArea.size.height/2*/, mrcCollisionArea.size.width,mrcCollisionArea.size.height);
}
void CTaikoCell::updataTextureArea(CCPoint ptSplit)
{
	//CCPoint ptTemp = ptSplit;
	//CCPoint ptTemp = this->convertToWorldSpace(ccp(mpSpriteTail->getPositionX() - mrcCollisionAreaTail.size.width/2,mpSpriteTail->getPositionY()));
	//CCRect rcAreaTail = CCRectMake(ptTemp.x,ptTemp.y,mrcCollisionAreaTail.size.width,mrcCollisionAreaTail.size.height);
	float fOffset = getCollisionArea().getMaxY() - ptSplit.y;
	CCRect rcTailTex = mpSpriteTail->getTextureRect();
	//if (fOffset >= 0.f){
		rcTailTex.size.height = fOffset;
		if (rcTailTex.size.height<=0){
			mpSprite->setVisible(false);
			mpSpriteTail->setVisible(false);
		}	
		mpSpriteTail->setTextureRect(rcTailTex);
		CCLOG("CTaikoCell::updataTextureArea() height = %f",rcTailTex.size.height);
	//}
}
bool CTaikoCell::isClickLongCell()
{
	for (int i = 0; i < mVecHitSplitInfo.size(); ++i)
	{
		if (mVecHitSplitInfo[i].bUse)
		{
			return true;
		}
	}
	return false;
}
void CTaikoCell::toGray()
{
	CCSprite* p = CCColorUtil::graylightWithCCSprite(mpSprite,false);
	mpSprite->setDisplayFrame(p->displayFrame());
	if (mnType == eTaikoType_1_Long||mnType == eTaikoType_2_Long)
	{
		//CCPoint ptAnchor = mpSpriteBg->getPosition();
		p = CCColorUtil::graylightWithCCSprite(mpSpriteBg,false);
		mpSpriteBg->setDisplayFrame(p->displayFrame());
		p = CCColorUtil::graylightWithCCSprite(mpSpriteTail,false);
		mpSpriteTail->setDisplayFrame(p->displayFrame());
	}
	 
}
CTaikoCell::VEC_HITSPLITINFO& CTaikoCell::getVecHitSplitInfo()
{
	return mVecHitSplitInfo;
}
//////////////////////////////////////////////////////////////////////////
//特效相关
void CTaikoCell::addEffect(ETaikoEffect effect,bool bFront)
{
	CTaikoCellEffect e;
	e.mType = effect;
	// 	switch(effect)
	// 	{
	// 	case eRTItemEffectScore:
	// 		e.mnMask.setMask(eRTEffectMaskMulCellDel);
	// 		
	// 		break;
	// 	}
	if (effect == eTaikoEffectBomb || bFront)
		mVecEffect.insert(mVecEffect.begin(),e);
	else
		mVecEffect.push_back(e);
}
ETaikoEffect CTaikoCell::getEffect()
{
	if(mVecEffect.empty())
		return eTaikoEffectNone;
	return mVecEffect[0].mType;
}
CTaikoCellEffect* CTaikoCell::getFrontEffect()
{
	if(mVecEffect.empty())
		return NULL;
	return &mVecEffect[0];
}
void CTaikoCell::delEffect()
{
	ETaikoEffect effect = getEffect();
	for (int i = 0; i < mVecEffect.size(); ++i)
	{
		if(mVecEffect[i].mType == effect && mVecEffect[i].mbInvalid)
			mVecEffect.erase(mVecEffect.begin() + i);
	}
}
void CTaikoCell::showEffect()
{
	ETaikoEffect effect = getEffect();
	mpEffectBelow->setVisible(false);
	mpEffectAbove->setVisible(false);
	mpSpriteEff->setVisible(false);
	mpEffectAbove->setScale(1.0f);
	mpEffectAbove->setRotation(0);
	mpEffectAbove->stopAllActions();
	mpHint->setVisible(false);
	mpHint->setPositionY(mpSprite->getContentSize().height/2);
	 if (effect == eTaikoEffectBomb){
		 mpHint->setPositionX(mpSprite->getContentSize().width/2 + mpSprite->getContentSize().width/2);
		 mpHint->showEffect(eTaikoEffectBomb);
		 mpHint->setVisible(true);
	}else if (effect == eTaikoEffectPrefect)
	{
		mpHint->setPositionX(mpSprite->getContentSize().width/2 + mpSprite->getContentSize().width/2);
		mpHint->showEffect(effect);
		mpHint->setVisible(true);
	}else if (effect == eTaikoEffectScore)
	{
		mpHint->setPositionX(mpSprite->getContentSize().width/2 + mpSprite->getContentSize().width/2);
		mpHint->showEffect(effect);
		mpHint->setVisible(true);
	}else if (effect == eTaikoEffectIntensifyAddScore)
	{
		CCAnimation* pAni = CCAnimation::create();
		CCString str;
		for (int i = 1; i <= 5; ++i){
			str.initWithFormat("tai_ko/bule_eff/%d.png",i);
			if(mnType == eTaikoType_2_Long || mnType == eTaikoType_2)
				str.initWithFormat("tai_ko/red_eff/%d.png",i);
			pAni->addSpriteFrameWithFileName(str.getCString());
		}
		pAni->setDelayPerUnit(0.1f);
		pAni->setLoops(1);
		mpSpriteEff->setVisible(true);
		mpSpriteEff->runAction(CCRepeatForever::create(CCAnimate::create(pAni)));
	}
// 	 else if (effect == eRTItemEffectColour)
// 	{
// 		mpEffectAbove->setDisplayFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName("rt_colour.png"));
// 		mpEffectAbove->setVisible(true);
// 		mpEffectAbove->setScale(1.f);
// 		CCActionInterval* pScaleBy = CCScaleBy::create(1.f, 1.1f);
// 		CCActionInterval* pAction = CCSequence::create(pScaleBy, pScaleBy->reverse(), NULL);
// 		mpEffectAbove->runAction(CCRepeatForever::create(pAction));
// 	}
}
void CTaikoCell::executeEffect()
{
	ETaikoEffect effect = getEffect();
	CTaikoCellEffect* pRealEffect = getFrontEffect();
	mpHint->executeEffect(effect);
	switch(effect){
	case eTaikoEffectBomb:{
		if (!pRealEffect->mbInvalid)
		{
			((CTaikoScene*)getParent())->time_addSecond(5.0);
			CEffectActionHelper::play(eHelp5Second,getParent(),getPosition());
			pRealEffect->mbInvalid = true;
			CTaskManProceDt(eDayTaskTypeShare_8,1);
			CTKData.setUseBomb(true);
		}
		}
		break;
	case eTaikoEffectPrefect:{
			CTaikoGameEffectPrefect* p = (CTaikoGameEffectPrefect*)CTKData.getEffect(eTaikoGameEffectPrefect);
			if(p)
				p->mbPerfectState = true;
		}
		break;
	case eTaikoEffectScore:{
// 		CCSprite* p = CCSprite::create("GameMemoryLayer/20000.png");   
// 		p->setScale(0.7f);
// 		p->setPositionY(p->getPositionY()-22);
// 		CCFiniteTimeAction*  pAction = CCSequence::create(
// 			CCShow::create(),
// 			CCFadeOut::create(0.5f),
// 			CCHide::create(),
// 			CCRemoveSelf::create(),
// 			NULL);
// 		p->runAction(pAction);
// 		addChild(p,20);
		if (!pRealEffect->mbInvalid)
		{
			CEffectActionHelper::play(eHelp20000,getParent(),getPosition());
			pRealEffect->mbInvalid = true;
			CTaskManProceDt(eDayTaskTypeTK_61,1);
			
		}
		
		}
		break;
	}
	mpHint->setVisible(false);
}

//////////////////////////////////////////////////////////////////////////