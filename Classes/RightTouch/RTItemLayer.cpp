

//#include "StaticData.h"
#include "RTItemLayer.h"
#include "RightTouchScene.h"
#include "SimpleAudioEngine.h"
#include "RightTouchDefine.h"
#include "TimeUtil.h"
#include "RandomUtil.h"
#include "MathUtil.h"
#include "AudioHelper.h"
#include "AudioDefine.h"
#include "ComData.h"
#include "SpriteFrameManage.h"
#include "GameItemManager.h"
#include "TaskDefine.h"
USING_NS_CC;
CRTItemLayer::~CRTItemLayer()
{
	mpArrClick->release();
	mpArrDelItem->release();
	CRtData.purge();
}
CRTItemLayer::CRTItemLayer():mpArrClick(NULL),mdbLastTime(0),mbIsResetHitTimes(true),mbCrazyMode(false)
	,mbDelItemStata2(false),mbUseColou(false)
{

}
bool CRTItemLayer::init()
{
	CRtData.reset();
	if (GameShare_Scene::init()) {
		mpArrClick = CCArray::create();
		mpArrClick->retain();
		mpArrDelItem = CCArray::create();
		mpArrDelItem->retain();

		//设置分数
		this->setScore(0);
		//设置能力最大值
		boom_setMaxBoomEnergy();
		boom_setEnergy(0);
		//this->addEnergy();

		//设置连击.
		this->setBatter(0);
		//         CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		// 		CCSprite* background = CCSprite::create("right_touch/00_board_l.png");
		//         //CCSprite* background = CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("background"));
		//         background->setPosition(CCPointMake(winSize.width*0.5,winSize.height*0.5));
		//         this->addChild(background);
		start();
		return true;
	}
    return false;
}
void CRTItemLayer::onEnter()
{
	GameShare_Scene::onEnter();

	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(CRTItemLayer::noticeBombEffect), NOTICE_RT_BOMB_EFFECT, NULL);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(CRTItemLayer::noticeColourEffect), NOTICE_RT_COLOUR_EFFECT, NULL);
	CAudioHelper::playBackgroundSound(eSoundTypeRightTouchBackground);
}
void CRTItemLayer::onExit()
{
	GameShare_Scene::onExit();
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, NOTICE_RT_BOMB_EFFECT);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, NOTICE_RT_COLOUR_EFFECT);
	CAudioHelper::stopBackgroundSound();
}
void CRTItemLayer::initBgView()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCSprite* pSprite = CCSprite::create("right_touch/bg.png");
	pSprite->setPosition(ccp(visibleSize.width/2 , visibleSize.height/2));
	this->addChild(pSprite, 0);
	_setTitleAni();
}
void CRTItemLayer::updateData(float delta)
{
	double dbNewTime = CTimeUtil::GetCocos2dxTimer();
	double dbDelta = dbNewTime - mdbLastTime;
	CRtData.updataMode();
	if(CRtData.getMode() == eNoneMode)
	{
		//unsigned int n = CTimeUtil::GetSystemTimeStamp() - dbNewTime;
		if (  dbDelta > RT_COM_MODE_CONTINUE_TIME_LIMIT)
		{
			CRtData.setContinueNum(0);
		}
	}
	if (CRtData.getMode() == eComCrazyMode)
	{
		if (dbDelta > RT_CRAZY_MODE_CONTINUE_TIME_LIMIT)
		{
			CRtData.setContinueNum(0);
			if(mbCrazyMode)
				exitCrazyMode();
		}
	}
	if (CRtData.getMode() == eSuperCrazyMode)
	{
		if (dbDelta > RT_CRAZY_SUPER_MODE_CONTINUE_TIME_LIMIT)
		{
			CRtData.setContinueNum(0);
			if(mbCrazyMode)
				exitCrazyMode();
		}
	}
}
void CRTItemLayer::setCrazyMode(bool bImmediately)
{
	CRtData.updataMode();
	if(bImmediately)
	{
		if (CRtData.getMode() == eSuperCrazyMode){
			//现在参数无用
			Crazy_Start(RT_CRAZY_MODE_CONTINUE_TIME_LIMIT/1000.0,eSuperCrazyMode);
		}
	}else{
		if (CRtData.getMode() == eComCrazyMode){
			if (CRtData.getContinueNum() == 10){
				//现在参数无用
				Crazy_Start(RT_CRAZY_MODE_CONTINUE_TIME_LIMIT/1000.0,eComCrazyMode);
			}else if (CRtData.getContinueNum() > 10){
				//Crazy_ReStart();
			}
		}else if (CRtData.getMode() == eSuperCrazyMode)
		{
			if (CRtData.getContinueNum() == RT_SUPER_MODE_CONTINUE_NEED_TIMES)
			{
				Crazy_Start(RT_CRAZY_MODE_CONTINUE_TIME_LIMIT/1000.0,eSuperCrazyMode);
			}
		}
	}
	
// 	if (CRtData.getMode() == eSuperCrazyMode)
// 	{
// 		if (CRtData.getContinueNum() == RT_SUPER_MODE_CONTINUE_NEED_TIMES)
// 		{
// 			//mbIsResetHitTimes = false;
// 			CCLOG("eSuperCrazyMode");
// 			Crazy_SetTime(RT_CRAZY_SUPER_MODE_CONTINUE_TIME_LIMIT/1000.0);
// 		}else if (CRtData.getContinueNum() > RT_SUPER_MODE_CONTINUE_NEED_TIMES)
// 		{
// 			Crazy_ReStart();
// 		}
// 	}
}
void CRTItemLayer::exitCrazyMode()
{
	CRtData.setMode(eNoneMode);
	Crazy_End();
	mbCrazyMode = false;
}
void CRTItemLayer::delSucceed(ERTOpretateType eOpType)
{
	CRtData.alterContinueNum(1);
	CRtData.alterItemGenVal(RT_GEN_ITEM_VAL);
	processItem(eRTIntensifyEffectQuickGrow);
	if (eOpType == eRTOperateDel)
	{
		CRtData.alterAnger(6);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(TR_SOUND_STAR_MERGE, false);
	}else if(eOpType == eRTOperateMerge)
	{
		CRtData.alterAnger(3);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(TR_SOUND_MERGE, false);
	}else{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(TR_SOUND_MERGE, false);
	}
}
void CRTItemLayer::calcScore()
{
	//连击加成
	int nContinueAddVal = CRtData.getContinueNum() * RT_CONTINUE_DEL_SCORE;
	//消除1个小细胞基本分
	int nDelState1 = 10* (CRtData.getContinueNum()+1);
	//消除1个大细胞基本分
	int nDelState2 = 50* (CRtData.getContinueNum()+1);
	//分数
	int nDeltaScore = 0;
	CCObject* jt=NULL;
	CCARRAY_FOREACH(mpArrDelItem,jt)
	{
		CRTItemField *target = dynamic_cast<CRTItemField*>(jt);
		CRTItemEffect* pEffect = target->getItem()->getRealEffect();
		if (target->getItem()->getState() == eRTItemState1)
		{
			if(pEffect && pEffect->mType == eRTItemEffectScore && pEffect->mbInvalid)
				nDelState1 *= 5;
			nDeltaScore += ((nContinueAddVal + nDelState1) * CRtData.getCrazyAdd());
		}else if (target->getItem()->getState() == eRTItemState2)
		{
			if(pEffect && pEffect->mType == eRTItemEffectScore && pEffect->mbInvalid)
				nDelState2 *= 5;
			nDeltaScore += ((nContinueAddVal + nDelState2) * CRtData.getCrazyAdd());
		}
	}
	CRtData.alterScore(nDeltaScore);
}
bool CRTItemLayer::isExistPath(CRTItemField* pField)
{
	bool bStart = false;
	CCObject* jt = NULL;
	CCARRAY_FOREACH_REVERSE(mpArrClick, jt)
	{
		CRTItemField *target = dynamic_cast<CRTItemField*>(jt);
		if (target->getPt().equals(pField->getPt()))
		{
			return true;
		}
	}
	return false;
}
void CRTItemLayer::click(CCTouch* touch)
{
	CCPoint ptouch = touch->getLocationInView();

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint ccTouchSprite = CCDirector::sharedDirector()->convertToGL(ptouch);
	CRTItemField* pCurSelField = GetFieldByTouch(&ccTouchSprite);
	if(pCurSelField == NULL)
		return ;
	if (pCurSelField->isActionRun()){
		return;
	}
// 	for (int i = 0; i < TR_ROW_NUM; ++i)
// 	{
// 		for (int j = 0; j < TR_COL_NUM; ++j)
// 		{
// 			if(mField[i][j].isActionRun())
// 				return;
// 		}
// 	}
	mOp = eRTOperateNone;
	
	if(pCurSelField)
	{
		if (pCurSelField->isGenIng()){
			return ;
		}
		
		if(mpArrClick->count() == 0)
		{
			mOp = eRTOperateSel;
			pCurSelField->getItem()->executeClick();
			mpArrClick->addObject(pCurSelField);
			if (pCurSelField->getItem()->getEffect() < eRTItemEffectNone && 
				pCurSelField->getItem()->getEffect() != eRTItemEffectScore)
			{
				mOp = eRTOperateItem;

				//单击使用染色剂先这边处理
				if (pCurSelField->getItem()->getEffect() == eRTItemEffectColour)
				{
					//pCurSelField->getItem()->executeEffect();
					CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTICE_RT_COLOUR_EFFECT,pCurSelField->getItem());
					pCurSelField->getItem()->getEffectAbove()->setVisible(false);
					pCurSelField->getItem()->getRealEffect()->mbInvalid = true;
					pCurSelField->getItem()->delEffect();
					pCurSelField->getItem()->reverseClick();
					mpArrClick->removeObject(pCurSelField);
					mOp = eRTOperateSel;
				}
			}
		}
		else
		{
			// 如果存在
			if(isExistPath(pCurSelField)){
				pCurSelField->getItem()->reverseClick();
				mpArrClick->removeObject(pCurSelField);
				return ;
			}
			//不存在
			else
			{
				CRTItemField* pLastField = (CRTItemField*)mpArrClick->lastObject();
				if (pLastField)
				{
					if (pCurSelField->getItem()->getType() == pLastField->getItem()->getType()
						&&pCurSelField->getItem()->getState() == pLastField->getItem()->getState())
					{
						//第一次合体
						if(pCurSelField->getItem()->getState() < TR_STATE_MAX) 
						{
							pCurSelField->getItem()->setMerge(true);
							mOp = eRTOperateMerge;
							pLastField->getItem()->setExeDelEff(false);
							if (pCurSelField->getItem()->getType() == eRTItemTypeRed)
							{
								CTaskManProceDt(eDayTaskTypeRT_17,2);
							}
							if (pCurSelField->getItem()->getType() == eRTItemTypeGreen)
							{
								CTaskManProceDt(eDayTaskTypeRT_18,2);
							}
							if (pCurSelField->getItem()->getType() == eRTItemTypeBule)
							{
								CTaskManProceDt(eDayTaskTypeRT_19,2);
							}
							if (pCurSelField->getItem()->getType() == eRTItemTypeOrg)
							{
								CTaskManProceDt(eDayTaskTypeRT_20,2);
							}
						}
						//第二次消除
						else
						{
							mOp = eRTOperateDel;
							if(pTimeProcessLayer->GetSecondsRemain() <= 10)
							{
								mbDelItemStata2 = true;
							}
							
							if (pCurSelField->getItem()->getType() == eRTItemTypeRed)
							{
								CTaskManProceDt(eDayTaskTypeRT_21,2);
							}
							if (pCurSelField->getItem()->getType() == eRTItemTypeGreen)
							{
								CTaskManProceDt(eDayTaskTypeRT_22,2);
							}
							if (pCurSelField->getItem()->getType() == eRTItemTypeBule)
							{
								CTaskManProceDt(eDayTaskTypeRT_23,2);
							}
							if (pCurSelField->getItem()->getType() == eRTItemTypeOrg)
							{
								CTaskManProceDt(eDayTaskTypeRT_24,2);
							}
						}
						mpArrClick->addObject(pCurSelField);
						
					}else
					{
						pCurSelField->selWrong();
						pLastField->selWrong();
						mpArrClick->removeAllObjects();
						//点击错误
						if (!CItemMan::sharedInstance().useItem(ItemTag_14)&&!useItem(eRTPayEffectSkipErr))
						{
							CRtData.setContinueNum(0);
							CRtData.setCrazyContinueNum(0);
							exitCrazyMode();
						}else
						{
							//effect\shield
							pCurSelField->executeSkipErrEff();
							mdbLastTime = CTimeUtil::GetCocos2dxTimer();
						}
						mOp = eRTOperateErr;
					}
				}
			}
		}
		
		if(mOp == eRTOperateSel||mOp == eRTOperateErr)
			return;

		//计算消除个数
		CCObject* jt = NULL;
		CCARRAY_FOREACH_REVERSE(mpArrClick, jt)
		{
			CRTItemField *target = dynamic_cast<CRTItemField*>(jt);
			calcDelNumByState(target);
			//每日任务累计
			CCObject* temp_jt = NULL;
			if (target->getItem()->getEffect() == eRTItemEffectBomb){
				CCARRAY_FOREACH_REVERSE(mpArrDelItem, temp_jt){
					CRTItemField *target_temp = dynamic_cast<CRTItemField*>(temp_jt);
					if (target_temp->getItem()->getState() == eRTItemState2)
					{
						CTaskManProceDt(eDayTaskTypeRT_29,1);
					}
				}
			}
			if (target->getItem()->getEffect() == eRTItemEffectRow){
				CCARRAY_FOREACH_REVERSE(mpArrDelItem, temp_jt){
					CRTItemField *target_temp = dynamic_cast<CRTItemField*>(temp_jt);
					if (target_temp->getItem()->getState() == eRTItemState2)
					{
						CTaskManProceDt(eDayTaskTypeRT_30,1);
                        CCLog("eRTItemState2");
					}
				}
			}
			if (target->getItem()->getEffect() == eRTItemEffectCol){
				CCARRAY_FOREACH_REVERSE(mpArrDelItem, temp_jt){
					CRTItemField *target_temp = dynamic_cast<CRTItemField*>(temp_jt);
					if (target_temp->getItem()->getState() == eRTItemState2)
					{
						CTaskManProceDt(eDayTaskTypeRT_31,1);
					}
				}
			}
		}

		//执行道具特效
		jt = NULL;
		CCARRAY_FOREACH_REVERSE(mpArrDelItem, jt){
			CRTItemField *target = dynamic_cast<CRTItemField*>(jt);
			target->executeEffect();
			if (target->getItem()->getEffect() == eRTItemEffectCol)
			{

			}
		}

		//计算怒气值
		delSucceed(mOp);

		//计算分数
		calcScore();

		//删除当前道具效果
		CCARRAY_FOREACH_REVERSE(mpArrDelItem, jt)
		{
			CRTItemField *target = dynamic_cast<CRTItemField*>(jt);
			target->getItem()->delEffect();
		}

		//设置数值效果显示
		if(CRtData.getContinueNum() > 0)
			setBatter(CRtData.getContinueNum());
		boom_setEnergy(CRtData.getAnger());
		setScore(CRtData.getScore());
		// CCUserDefault::sharedUserDefault()->setIntegerForKey("medal600001", CRtData.getScore());
		CTaskManProce(eDayTaskTypeShare_1,CRtData.getScore());
		CTaskManProceDt(eDayTaskTypeShare_4,1);
		CTaskManProce(eDayTaskTypeShare_7,CRtData.getContinueNum());
		//设置疯狂模式
		setCrazyMode();

		//随机道具
		//设置符合随机道具条件的数组
		CCArray conformArr;
		CCObject* pConformObj = NULL;
		CCARRAY_FOREACH(mpArrDelItem,pConformObj){
			CRTItemField *pTemp = dynamic_cast<CRTItemField*>(pConformObj);
			if (pTemp&&!pTemp->getItem()->getMerge()){
				conformArr.addObject(pConformObj);
			}
		}
		
		int nRound = -1;
		if (CRtData.getItemGen()){
			if(conformArr.count() > 0)
			{
				nRound = CRandomUtil::RandomRange(0,conformArr.count()-1);
				CRTItemField *target = dynamic_cast<CRTItemField*>(conformArr.objectAtIndex(nRound));
				target->getItem()->randItemEffectGen();
				//随机染色剂
				if(useItem(eRTPayEffectColourOpen)){
					nRound = CRandomUtil::RandomRange(0,conformArr.count()-1);
					CRTItemField *target = dynamic_cast<CRTItemField*>(conformArr.objectAtIndex(nRound));
					target->getItem()->addEffect(eRTItemEffectColour);
				}
			}
			CRtData.setItemGen(false);
		}
		//随机炸弹
		if (CRtData.getGenBomb())
		{
			if(conformArr.count() > 0){
				nRound = CRandomUtil::RandomRange(0,conformArr.count()-1);
				CRTItemField *target = dynamic_cast<CRTItemField*>(conformArr.objectAtIndex(nRound));
				target->getItem()->addEffect(eRTItemEffectBomb);
			}
			CRtData.setGenBomb(false);
		}
		
		//执行消除
		//CCARRAY_FOREACH(mpArrDelItem,jt)
	
		for(int i = 0; i < mpArrDelItem->count(); ++i)
		{
			jt = mpArrDelItem->objectAtIndex(i);
			CRTItemField *target = dynamic_cast<CRTItemField*>(jt);
			//第一次合体
			if(target->getItem()->getMerge())
			{
				target->getItem()->executeMerge();
			}
			//第二次消除
			else
			{
				target->reset();
				target->genIteming();
			}
		}
		
		
		mdbLastTime = CTimeUtil::GetCocos2dxTimer();
		long lTime = CTimeUtil::GetSystemTimeStamp();
		mpArrClick->removeAllObjects();
		mpArrDelItem->removeAllObjects();
	}
}
CRTItemField* CRTItemLayer::GetFieldByTouch(const cocos2d::CCPoint* pPt)
{
	for (int i = 0; i < TR_ROW_NUM; ++i)
	{
		for (int j = 0; j < TR_COL_NUM; ++j)
		{
			if(mField[i][j].getRect().containsPoint(*pPt))
			{
				return &mField[i][j];
			}
		}
	}
	return NULL;
}
bool CRTItemLayer::start()
{
	//CCSprite* pBg = ((CRightTouchScene*)getParent())->getBgLayer()->getBg();
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCSize szBg(0,800);
	CCPoint ptOffset(0,0);
	CCSize csFruit(CMathUtil::round( visibleSize.width / (float)TR_ROW_NUM) ,CMathUtil::round( visibleSize.width / (float)TR_ROW_NUM));
	CCSize picWH(120,120);
	mRcFieldArea = CCRectMake(szBg.width,szBg.height - TR_ROW_NUM * csFruit.height,TR_COL_NUM * csFruit.width,TR_ROW_NUM * csFruit.height);
	for (int y = 0 ; y < TR_COL_NUM; ++y)
	{
		for (int x = 0; x < TR_ROW_NUM;++x)
		{
			char strName[256]="";
			CRTItemField* pField = &mField[y][x];

			//设置线
			pField->setPt(ccp(x,y));
			
			//pField->mRealPt = ccp(mpBg->getPositionX() + j * pField->mpFruit->getTextureRect().size.width + ptOffset.x , mpBg->getPositionY() + i * pField->mpFruit->getTextureRect().size.height + ptOffset.y);
			pField->setRect(CCRect(szBg.width + ptOffset.x + x * csFruit.width
				,/*pBg->getPositionY()*/ szBg.height - csFruit.height - y *csFruit.height + ptOffset.y
				,csFruit.width,csFruit.height));
			pField->setPosition(ccp(pField->getRect().getMidX(), pField->getRect().getMidY()));
			//缩放
			CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
			//CCPoint ptC = ccp(picWH.width/cache->spriteFrameByName("cell0_1.png")->getRect().size.width , picWH.height/cache->spriteFrameByName("cell0_1.png")->getRect().size.height);
			
			CRTItem* pItem = CRTItem::create();
			//pItem->retain();
			pItem->setPosition(ccp(pField->getRect().getMidX(), pField->getRect().getMidY()));
			//pItem->setScale(ptC.x,ptC.y);
			pItem->randItem();
			//mVecFruit.push_back(pFruit);
			pField->setItem(pItem); 
			//冰冻设置
			//pField->getFruit()->SetByIce(false);
			//pField->getFruit()->SetState(eEffectNone);

			addChild(pItem,4);
			addChild(pField,3);
			
		}
	}
	
	return true;
}
void CRTItemLayer::_setTitleAni()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCString strFileName;
	CCAnimation* pAni = CCAnimation::create();
	pAni->addSpriteFrameWithFileName("right_touch/big_mm/1.png");
	pAni->addSpriteFrameWithFileName("right_touch/big_mm/2.png");
	pAni->addSpriteFrameWithFileName("right_touch/big_mm/3.png");
	pAni->addSpriteFrameWithFileName("right_touch/big_mm/4.png");
	pAni->addSpriteFrameWithFileName("right_touch/big_mm/2.png");
	pAni->addSpriteFrameWithFileName("right_touch/big_mm/1.png");
	pAni->addSpriteFrameWithFileName("right_touch/big_mm/2.png");
	pAni->addSpriteFrameWithFileName("right_touch/big_mm/5.png");
	pAni->addSpriteFrameWithFileName("right_touch/big_mm/6.png");
	
	pAni->setDelayPerUnit(0.12f);
	pAni->setLoops(1);
	auto pLighting = CCSprite::create("right_touch/big_mm/1.png");
	pLighting->runAction(CCRepeatForever::create(CCAnimate::create(pAni)));
	pLighting->setPosition(ccp(visibleSize.width/2,visibleSize.height - pLighting->getContentSize().height/2 - 93));
	this->addChild(pLighting,0);
}
void CRTItemLayer::exeIntensifyEffQuickGrow()
{
	if(useItem(eRTIntensifyEffectQuickGrow)){
		CTaskManProceDt(eDayTaskTypeRT_15,1);
		for (int i = 0; i < TR_ROW_NUM; ++i){
			for (int j = 0; j < TR_COL_NUM; ++j){
				if(mField[i][j].getItem()->getState() < TR_STATE_MAX)
					mField[i][j].getItem()->executeMerge();
			}
		}
	}
}
void CRTItemLayer::calcDelNumByState( CRTItemField* pCurField)
{
	CRTItemField* pTempField = NULL;
	ERTItemEffect effcet = pCurField->getItem()->getEffect();
	CRTItemEffect* pE = pCurField->getItem()->getRealEffect();
	bool bTrigger = true;
	if (pE){
		if (pE->mnMask.isMask(eRTEffectMaskMulCellDel))
		{
			if(mpArrClick->count() + mpArrDelItem->count() < 2)
				bTrigger = false;
		}
		bool bOp = false;
		for (int i = 0; i < pE->mVecOp.size(); ++i)
		{
			if(pE->mVecOp[i] == mOp)
				bOp = true;
		}
		if(!bOp)
			bTrigger = false;
		//加判断避免无限递归
		if(pE->mbInvalid) 
			bTrigger = false;
	}
	if(!bTrigger)
	{
		if(!mpArrDelItem->containsObject(pCurField))
			mpArrDelItem->addObject(pCurField);
		return ;
	}
	if(pE)
		pE->mbInvalid = true;

	if(!mpArrDelItem->containsObject(pCurField))
		mpArrDelItem->addObject(pCurField);
	//横炸
	if(effcet == eRTItemEffectRow){
		for (int x = 0; x < TR_ROW_NUM;++x){
			pTempField = &mField[(int)pCurField->getPt().y][x];
			if (pTempField&&!pTempField->isGenIng()){

				calcDelNumByState(pTempField);
			}
		}
	}
	//竖炸
	else if(effcet == eRTItemEffectCol)
	{
		for (int y = 0; y < TR_COL_NUM;++y){
			pTempField = &mField[y][(int)pCurField->getPt().x];
			if (pTempField&&!pTempField->isGenIng()){
		
				calcDelNumByState(pTempField);
			}
		}
	}
	//炸周围
	else if (effcet == eRTItemEffectBomb)
	{
		for (int x = 0; x < 3;++x){
			for (int y = 0; y < 3; ++y )
			{
				int nIndexY = pCurField->getPt().y -1 + y;
				int nIdenxX = pCurField->getPt().x -1 + x;
				if(nIndexY < 0 || nIdenxX < 0 || nIndexY > TR_COL_NUM - 1 || nIdenxX  > TR_ROW_NUM - 1)
					continue;
				pTempField = &mField[nIndexY][nIdenxX];
				if (pTempField&&!pTempField->isGenIng()){
		
					calcDelNumByState(pTempField);
				}
			}
		}
	}
// 	else if (nState == eRTItemEffectGold)
// 	{
// 	}
	else if (effcet == eRTItemEffectScore)
	{
		if (mOp == eRTOperateMerge)
		{
			//第一个有分数加成就付到第二个上面
			CRTItem* pSecondItem =  ((CRTItemField*)mpArrClick->objectAtIndex(1))->getItem();
			if (mpArrClick->objectAtIndex(0) == pCurField)
			{
				pE->mbInvalid = true;
				pCurField->getItem()->delEffect();
				//随机第二个的道具如果有
				CRTItemEffect* pSecondEffect = pSecondItem->getRealEffect();
				if (pSecondEffect)
				{
					int nRand = CRandomUtil::RandomRange(0,1);
					if (nRand&&pSecondEffect->mType != eRTItemEffectBomb)
					{
						pSecondEffect->mbInvalid = true;
						pSecondItem->delEffect();
						pSecondItem->addEffect(eRTItemEffectScore,true);
					}
				}else
					pSecondItem->addEffect(eRTItemEffectScore);
			}else
			{
				pE->mbInvalid = false;
			}
		}
	}
	else if (effcet == eRTItemEffectColour)
	{
// 		CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTICE_RT_COLOUR_EFFECT,pCurField->getItem());
// 		CTaskManProceDt(eDayTaskTypeRT_26,1);
// 		mbUseColou = true;
	}

	return;
}
void CRTItemLayer::msgHandle_CrazyTimeOut(CCObject* obj)
{
	if(mbIsResetHitTimes)
		CRtData.setContinueNum(0);
	else
		mbIsResetHitTimes = true;
}
void CRTItemLayer::msgHanlde_GameTimeOut(CCObject* obj)
{
	if(CRtData.getScore() == 0)
		CTaskManProceDt(eDayTaskTypeShare_11,1);
	if(mbDelItemStata2)
		CTaskManProceDt(eDayTaskTypeRT_25,10);
	if (mbUseColou)
		CTaskManProceDt(eDayTaskTypeRT_14,1);
	if (!CRtData.getUseBomb() && CRtData.getScore() >= 50000)
		CTaskManProceDt(eDayTaskTypeShare_13,1);
	if (CRtData.getNoUsePlayItem())
		CTaskManProceDt(eDayTaskTypeShare_9,1);
	GameShare_Scene::msgHanlde_GameTimeOut(obj);
}

void CRTItemLayer::Crazy_Start(float rfDurationTime,ECrazyMode eMode)
{
	GameShare_Scene::Crazy_Start(rfDurationTime,eMode);
	 unschedule(schedule_selector(GameShare_Scene::Crazy_Check));
	 mbCrazyMode = true;
}
void CRTItemLayer::Crazy_ReStart()
{
	
}
void CRTItemLayer::startGame(float dt/* =1.0 */)
{
// 	auto pE = new CFrIntersifyEffectQuickGrow();
// 	pE->mnEffectVal = 10000;
// 	CRtData.addEffect(pE);
// 	auto pE1 = new CFrIntersifyEffectGenBigCell();
// 	pE1->mnEffectVal = 10000;
// 	CRtData.addEffect(pE1);
// 	auto pE2 = new CFrIntersifyEffectSubItemGenVal();
// 	pE2->mnEffectVal = 99;
// 	CRtData.addEffect(pE2);

	if(useItem(eRTPayEffectCrazy))
	{
		CRtData.setMode(eSuperCrazyMode);
		setCrazyMode(true);
		mdbLastTime = CTimeUtil::GetCocos2dxTimer();
	}
	useItem(eRTIntensifyEffectSubItemGenVal);
	
}
void CRTItemLayer::noticeBombEffect(CCObject* obj)
{
	time_addSecond(5.0);
}
void CRTItemLayer::noticeColourEffect(CCObject* obj)
{
	CRTItem* pItem = dynamic_cast<CRTItem*>(obj);
	if(pItem == NULL)
		return;
	mbUseColou = true;
	CTaskManProceDt(eDayTaskTypeRT_26,1);
	for (int y = 0 ; y < TR_COL_NUM; ++y)
	{
		for (int x = 0; x < TR_ROW_NUM;++x)
		{
			CRTItemField* pField = &mField[y][x];
			if (pField->getItem()->getType() != pItem->getType())
			{
				pField->getItem()->setType(pItem->getType());
				pField->getItem()->updataCell();
			}
		}
	}
}
void CRTItemLayer::noticeTimeInterval(CCObject* obj)
{
	GameShare_Scene::noticeTimeInterval(obj);
	if (((GameShare_TimeProcess*)obj)->GetSecondsRemain() <= 2)
	{
		if (useItem(eRTPayEffectDelayTime))
		{
			useTimeEff();
			return ;
		}
	}
    if (((GameShare_TimeProcess*)obj)->GetSecondsRemain() >= 40) {
        CTaskManProce(eDayTaskTypeShare_5, CRtData.getScore());
    }
}
bool CRTItemLayer::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	click(touch);
	return true;
}
void CRTItemLayer::ccTouchMoved(CCTouch* touch, CCEvent* event)
{

}
void CRTItemLayer::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	
}
void CRTItemLayer::executeEffect(CRTItemField* pField)
{
// 	CCAnimation* pAni = CCAnimation::create();
// 	CCString str;
//  	for (int i = 1; i <= 5; ++i){
// 	 	str.initWithFormat("effect/lighting/%d.png",i);
// 	 	//pAni->addSpriteFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName(str.getCString()));
// 	 	pAni->addSpriteFrameWithFileName(str.getCString());
// 	}
// 	pAni->setDelayPerUnit(0.3f/5.f);
// 	pAni->setLoops(1);
// 	CCFiniteTimeAction*  pAction = CCSequence::create(
// 	 	CCAnimate::create(pAni),
// 	 	CCCallFuncND::create(this, callfuncND_selector(CRTItemField::effectInCallback), (void*)this), 
// 	 	NULL);
// 	CCSprite* p
// 	mpSpEffectIn->runAction(pAction);
// 	mpSpEffectIn->setVisible(true);
}
bool CRTItemLayer::useItem(ERTEffectType eType){
	CRTBaseEffect* pBaseEffect = CRtData.getEffect(eType);
	if (pBaseEffect == NULL)
		return false;
	switch(eType){
	case eRTPayEffectColourOpen:{
				if (CRandomUtil::RandomRange(1,RAND_GAME_BASE_VAL) <= 0.5f * RAND_GAME_BASE_VAL)
				{
					CTaskManProceDt(eDayTaskTypeShare_10,1);
					return true;
				}
				else 
					return false;
		}
		break;
	case eRTPayEffectDelayTime:{
				time_addSecond(5.0);
				CRtData.delEffect(eRTPayEffectDelayTime);
				CTaskManProceDt(eDayTaskTypeShare_10,1);
		}
		break;
	case eRTPayEffectCrazy:{
				CRtData.delEffect(eRTPayEffectCrazy);
				CTaskManProceDt(eDayTaskTypeShare_10,1);
		}
		break;
	case eRTPayEffectSkipErr:{
				CRtData.delEffect(eRTPayEffectSkipErr);
				CTaskManProceDt(eDayTaskTypeShare_10,1);
		}
		break;
	case eRTIntensifyEffectSubItemGenVal:{
				CRtData.setItemGenValLimit(CRtData.getItemGenValLimit() - ((CFrIntersifyEffectSubItemGenVal*)pBaseEffect)->mnEffectVal);
				CCLOG("getItemGenValLimit = %d",CRtData.getItemGenValLimit());
				//CRtData.delEffect(eRTIntensifyEffectSubItemGenVal);
		}
		break;
	case eRTIntensifyEffectQuickGrow:{
				CFrIntersifyEffectQuickGrow* p = ((CFrIntersifyEffectQuickGrow*)pBaseEffect);
				if(p->mnHitTimes >= p->mnLimitNum){
					p->mnHitTimes = 0;
					if (CRandomUtil::RandomRange(1,RAND_GAME_BASE_VAL) <= p->mnEffectVal)
						return true;
				}
				return false;
		}
		break;
	case eRTIntensifyEffectGenBigCell:
		{
			CFrIntersifyEffectGenBigCell* p = ((CFrIntersifyEffectGenBigCell*)pBaseEffect);
				if (CRandomUtil::RandomRange(1,RAND_GAME_BASE_VAL) <= p->mnEffectVal)
					return true;
			return false;
		}
		break;
	}
	return true;
}
void CRTItemLayer::processItem(ERTEffectType eType)
{
	CRTBaseEffect* pBaseEffect = CRtData.getEffect(eType);
	if (pBaseEffect == NULL)
		return;
	switch(eType){
	case eRTIntensifyEffectQuickGrow:{
			((CFrIntersifyEffectQuickGrow*)pBaseEffect)->mnHitTimes += 1;
		}
		break;
	}
}