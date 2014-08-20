#include "GameFruitScene.h"
#include "GameTimer.h"
#include "GameShare_TimeProcess.h"
#include "Scene_GameOver.h"
#include "Constant.h"
#include "FruitData.h"
#include "GameFruitDefine.h"
#include "RandomUtil.h"
#include "SpriteFrameManage.h"
#include "NetHttpClient.h"
#include "NetFactory.h"
#include "MsgDefine.h"
#include "ImplementScheduler.h"
#include "GameScheduler.h"
#include "NetPacket.h"
#include "AudioHelper.h"
#include "AudioDefine.h"
#include "CsvManager.h"
#include "CsvStringData.h"
#include "RightTouchDefine.h"
#include "TaskDefine.h"

USING_NS_CC;
#define _OffsetY_Max  150
static const int FIELD_WIDTH = 87;
static const int FIELD_HIGH = 87;
enum
{
	eUILayerImageFinger = 1001,
};
CGameFruitScene::CGameFruitScene():mpBg(NULL),mulLastTouchTime(0),mulContinueHitTimeLimit(0),mbFinger(true)
	,mbUseCrossBomb(false),mbUseColour(false)
{

}
CGameFruitScene::~CGameFruitScene()
{
	for (int i = 0 ; i < mVecFruit.size(); ++i)
	{
		CGameFruit* pFruit = mVecFruit[i];
		CC_SAFE_RELEASE_NULL(pFruit);
		//mVecFruit[i].release()
	}
	//CFruitData* pData = ;
	CFruitData::getInstance()->purge();
}
CCScene* CGameFruitScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	//    HelloWorld *layer = HelloWorld::create();

	CGameFruitScene *layer = CGameFruitScene::create();

	// add layer as a child to scene
	 scene->addChild(layer);

	// return the scene
	return scene;
}
void CGameFruitScene::initBgView()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCSprite* pSprite = CCSprite::create("./game_fruit/bg.png");
	pSprite->setPosition(ccp(visibleSize.width/2 , visibleSize.height/2));
	this->addChild(pSprite, 0);
    
    
//    CCSprite* topSprite = CCSprite::createWithSpriteFrameName("GameSceneBg/FruitBar.jpg");
//    topSprite->setAnchorPoint(ccp(0, 0));
//    topSprite->setPosition(ccp(0, visibleSize.height-topSprite->getContentSize().height));
//    
//    CCSprite* pSprite = CCSprite::createWithSpriteFrameName("GameSceneBg/GameBg.png");
//    pSprite->setAnchorPoint(ccp(0, 0));
//    pSprite->setPosition(ccp(0 , 0));
//    
//    this->addChild(topSprite, 0);
//    this->addChild(pSprite, 0);
    
	CCAnimation* pAni = CCAnimation::create();
	CCString str;
	for (int i = 1; i <=8; ++i)
	{
	 	str.initWithFormat("role/pig_sister/%d.png",i);
	 	pAni->addSpriteFrameWithFileName(str.getCString());
	}
	 
	pAni->setDelayPerUnit(0.12f);
	pAni->setLoops(1);
	CCSprite* p = CCSprite::create("role/pig_sister/1.png");
	p->setPosition(ccp(visibleSize.width/2 + 20,visibleSize.height - p->getContentSize().height/2 - 93 + 19));
	p->runAction(CCRepeatForever::create(CCAnimate::create(pAni)));
	this->addChild(p, 0);
}
bool CGameFruitScene::init()
{
	if (!GameShare_Scene::init()) {
		return false;
	}
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	CCSpriteFrameManage* cache = CCSpriteFrameManage::getInstance();
	cache->addSpriteFramesWithFile("./game_fruit/game_fruit0.plist", "./game_fruit/game_fruit0.png");  
	for (int i =0; i < FRUIT_TYPE_NUM; ++i)
	{
		char strName[256]="";
		sprintf(strName,"Item/fruit%d.png",i+1);
		mpFruitType[i] = CCSprite::createWithSpriteFrame(cache->spriteFrameByName(strName)); 
		sprintf(strName,"Item/fruit%dPress.png",i+1);
		//mpFruitPressType[i] = CCSprite::createWithSpriteFrame(cache->spriteFrameByName(strName)); ;
	}

	//创建UI层
	m_pUILayer = UILayer::create();
	m_pUILayer->scheduleUpdate();
	m_pUILayer->setVisible(false);
	//m_pUILayer->setTouchEnabled(false);
	this->addChild(m_pUILayer,2);
	//创建image控件
	UIImageView *imageView = UIImageView::create();
	imageView->setTexture("item/finger.png",UI_TEX_TYPE_PLIST);
	imageView->setPosition(ccp(visibleSize.width / 2.f, visibleSize.height - 279.f));
	imageView->addReleaseEvent(this, coco_releaseselector(CGameFruitScene::OnImgEvent));
	imageView->setWidgetTag(eUILayerImageFinger);
	imageView->setTouchEnabled(true);	
	m_pUILayer->addWidget(imageView);

	start();

	//NetHttpClient::sendHttpRequest(eNetMsgTypePlayerSys,eNetMsgCodeAddExp);
// 	CSJson::Value msg_bady;
// 	msg_bady["player_id"] = CSJson::Value(1100);
// 	msg_bady["exp"] = CSJson::Value(999);
// 	NetHttpClient::sendHttpRequest(eNetMsgTypePlayerSys,eNetMsgCodeAddExp,msg_bady);
	return true;
}

void CGameFruitScene::start()
{
	//设置分数
	CFrData.reset();
	CFrData.setScore(0);
	this->setScore(CFrData.getScore());
	//设置能力最大值
	boom_setMaxBoomEnergy();
	boom_setEnergy(0);
	//设置连击.
	if( CFruitData::getInstance()->getContinueNum() > 0)
		this->setBatter(CFruitData::getInstance()->getContinueNum());

	mulContinueHitTimeLimit = FRUIT_CONTINUE_LIMT_TIME;
	//道具延长连击时间
	useItem(eFrPayEffectAddContinueHit);
	
	//设置游戏区数据
	//CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
	CCSpriteFrameManage* cache = CCSpriteFrameManage::getInstance();
	CCPoint ptOffset(1,2);
	CCSize csFruit(88,88);
	CCPoint ptFieldLT = ccp(9,789);
	//CCPoint ptRand(CCRANDOM_0_1() * 7.f,CCRANDOM_0_1() * 7.f);
	for (int y = 0 ; y < FIELD_Y; ++y)
	{
		for (int x = 0; x < FIELD_X;++x)
		{
			char strName[256]="";

			CGameFruitField* pField = &mField[y][x];

			//设置线
			pField->mpLine = CCSprite::createWithSpriteFrame(cache->spriteFrameByName("item/line.png"));  
			pField->mpLine->setAnchorPoint(ccp(0,0.5));
			addChild(pField->mpLine,1);
			//pField->setScore(CCSprite::create("./game_fruit/iPhone-hd/score100.png"));
			//pField->getScore()->setVisible(false);
			//pField->ResetScore();
			//addChild(pField->getScore(),3);
			pField->mpLine->setVisible(false);
			pField->mPt = ccp(x,y);
			//pField->mRealPt = ccp(mpBg->getPositionX() + j * pField->mpFruit->getTextureRect().size.width + ptOffset.x , mpBg->getPositionY() + i * pField->mpFruit->getTextureRect().size.height + ptOffset.y);
			pField->mRect = CCRect(ptFieldLT.x + x * (csFruit.width + ptOffset.x)
				,ptFieldLT.y - csFruit.height - y * (csFruit.height + ptOffset.y)
				,csFruit.width,csFruit.height);
			//设置水果
			CGameFruit* pFruit = CGameFruit::create();
			pFruit->retain();

			pFruit->getSprite()->setPosition(ccp(pField->mRect.getMidX(), pField->mRect.getMidY()));
			pFruit->RandFruit();

			mVecFruit.push_back(pFruit);
			pField->setFruit(pFruit); 
			//冰冻设置
			//pField->getFruit()->SetByIce(false);
			pField->getFruit()->addEffect(eEffectNone);
			//if((int)ptRand.x == x && (int)ptRand.y == y)
			//	pField->getFruit()->SetState(eEffectIce);

			addChild(pFruit->getSprite(),eLayerItem);
			//addChild(pFruit->getIce(),eLayerEffect3);
			addChild(pFruit->getBombEff(),eLayerEffect1);
			addChild(pFruit->getLightning(),eLayerEffect1);
			addChild(pFruit->getLightningRow(),eLayerEffect1);
			addChild(pFruit->getBombRang(),eLayerEffect2);
		}
	}
	mRcFieldArea = CCRectMake(ptFieldLT.x,ptFieldLT.y - (FIELD_X * (csFruit.height + ptOffset.y)),FIELD_Y * (csFruit.width + ptOffset.x),FIELD_X * (csFruit.height + ptOffset.y));
}
CGameFruitField* CGameFruitScene::GetFieldByTouch(const cocos2d::CCPoint* pPt)
{
	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j < 7; ++j)
		{
			if(mField[i][j].mRect.containsPoint(*pPt))
			{
				return &mField[i][j];
			}
		}
	}
	return NULL;
}
// CGameFruitField* CGameFruitScene::GetFieldByIndex(const CCPoint* pPt)
// {
// 	return ;
// }
bool CGameFruitScene::IsConnectRange(CGameFruitField* pTargetField,CGameFruitField* pStartField)
{
	if ((pStartField->mPt.x >= pTargetField->mPt.x - 1 && pStartField->mPt.x <= pTargetField->mPt.x + 1)&&
		(pStartField->mPt.y >= pTargetField->mPt.y - 1 && pStartField->mPt.y <= pTargetField->mPt.y + 1))
	{
		return true;
	}
	return false;
}

void CGameFruitScene::UpdataField()
{
	for (int i = 0; i < mVecFruit.size(); ++i)
	{
		CGameFruitField* pField = GetFieldByTouch(&mVecFruit[i]->getSprite()->getPosition());
		if (pField)
		{
			//if(!mVecFruit[i]->getSprite()->isVisible())
				//mVecFruit[i]->RandFruit();
			pField->setFruit(mVecFruit[i]);
		}
	}
}
bool CGameFruitScene::IsExistPath(CGameFruitField* pField)
{
	for (int i = 0; i < mVecPath.size(); ++i)
	{
		if(mVecPath[i]->mPt.equals(pField->mPt))
		{
			return true;
		}
	}
	return false;
}
float CGameFruitScene::GetCalcScale(CCPoint ptTarget,CCPoint ptStart,float fOriginLen)
{
	float fLen = ccpDistance(ptTarget,ptStart);
	float fScale = fLen/fOriginLen;
	return fScale;
}
float CGameFruitScene::GetCalcAngle(CCPoint ptTarget,CCPoint ptStart)
{
	double len_y =  ptTarget.y - ptStart.y ;
	double len_x = ptTarget.x - ptStart.x  ;

	double tan_yx  = fabs(len_y)/fabs(len_x);
	float angle = 0;
	if(len_y >= 0 && len_x <= 0) {
		angle = atan(tan_yx)*180/M_PI - 90;
	} else if (len_y >= 0 && len_x >= 0) {
		angle = 90 - atan(tan_yx)*180/M_PI;
	} else if(len_y <= 0 && len_x <= 0) {
		angle = -atan(tan_yx)*180/M_PI - 90;
	} else if(len_y <= 0 && len_x >= 0) {
		angle = atan(tan_yx)*180/M_PI + 90;
	}
	return angle - 90;
}
void CGameFruitScene::ClearField()
{
	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j < 7; ++j)
		{
			CGameFruitField& field = mField[i][j];
			field.mpLine->setVisible(false);
			
		}
	}
}

void CGameFruitScene::calcDelNumByState(CGameFruitField* pCurField,bool bIsRecursion)
{
	//处理每格的道具效果
	CGameFruitField* pTempField = NULL;
	EFruitEffect nState = pCurField->getFruit()->getEffectVal();
	CGameFruitEffect* pEffect = pCurField->getFruit()->getFrontEffect();
	if(pEffect&&pEffect->mbInvalid)
		return;
	
	if(!isContainDelVec(pCurField))
		mVecPathTotal.push_back(pCurField);
	
	if(pEffect)
			pEffect->mbInvalid = true;
	
	if (!bIsRecursion)
	{
		return;
	}
	//////////////////////////////////////////////////////////////////////////
	//判断递归
	//横炸
	bool bRecursion = false;
	if(nState == eEffectHor){
		for (int x = 0; x < FIELD_X;++x){
			 pTempField = &mField[(int)pCurField->mPt.y][x];
			if (pTempField&&!pTempField->isGenIng()){
				bRecursion = false; 
				CGameFruitEffect* pTempEffect = pTempField->getFruit()->getFrontEffect();
				if(pTempEffect && (pTempEffect->isMask(FR_MASK_TARGET_EFFECT)||pTempEffect->isMask(FR_MASK_PLAYER_TARGET_EFFECT)))
					bRecursion = true;
				calcDelNumByState(pTempField,bRecursion);
			}
		}
	}
	//竖炸
	else if(nState == eEffectVertical)
	{
		for (int y = 0; y < FIELD_Y;++y){
			 pTempField = &mField[y][(int)pCurField->mPt.x];
			if (pTempField&&!pTempField->isGenIng()){
				bRecursion = false; 
				CGameFruitEffect* pTempEffect = pTempField->getFruit()->getFrontEffect();
				if(pTempEffect && (pTempEffect->isMask(FR_MASK_TARGET_EFFECT)||pTempEffect->isMask(FR_MASK_PLAYER_TARGET_EFFECT)))
					bRecursion = true;
				calcDelNumByState(pTempField,bRecursion);
			}
		}
	}
	//炸周围
	else if (nState == eEffectBomb)
	{
		for (int x = 0; x < FRUIT_BOMB_ROUND;++x){
			for (int y = 0; y < FRUIT_BOMB_ROUND; ++y )
			{
				int nIndexY = pCurField->mPt.y -1 + y;
				int nIdenxX = pCurField->mPt.x -1 + x;
				if(nIndexY < 0 || nIdenxX < 0 || nIndexY > FIELD_Y - 1 || nIdenxX  > FIELD_X - 1)
					continue;
				 pTempField = &mField[nIndexY][nIdenxX];
				if (pTempField&&!pTempField->isGenIng()){
					bRecursion = false; 
					CGameFruitEffect* pTempEffect = pTempField->getFruit()->getFrontEffect();
					if(pTempEffect && (pTempEffect->isMask(FR_MASK_TARGET_EFFECT)||pTempEffect->isMask(FR_MASK_PLAYER_TARGET_EFFECT)))
						bRecursion = true;
					calcDelNumByState(pTempField,bRecursion);
				}
			}
		}
	}else if (nState == eEffectColour)
	{
		CTaskManProceDt(eDayTaskTypeFT_45,1);
		mbUseColour = true;
		for (int x = 0; x < FIELD_X;++x){
			for (int y = 0; y < FIELD_Y;++y)
			{
				pTempField = &mField[y][x];
				if (pTempField&&!pTempField->isGenIng()&&pEffect->mnColourDelType == pTempField->getFruit()->getType()){
					bRecursion = false; 
					CGameFruitEffect* pTempEffect = pTempField->getFruit()->getFrontEffect();
					if(pTempEffect && (pTempEffect->isMask(FR_MASK_TARGET_EFFECT)||pTempEffect->isMask(FR_MASK_PLAYER_TARGET_EFFECT)))
						bRecursion = true;
					calcDelNumByState(pTempField,bRecursion);
				}
			}
		}
	}else if (nState ==  eEffectCross)
	{
		CTaskManProceDt(eDayTaskTypeFT_46,1);
		mbUseCrossBomb  = true;
		for (int y = 0; y < FIELD_Y;++y){
			pTempField = &mField[y][(int)pCurField->mPt.x];
			if (pTempField&&!pTempField->isGenIng()){
				bRecursion = false; 
				CGameFruitEffect* pTempEffect = pTempField->getFruit()->getFrontEffect();
				if(pTempEffect && (pTempEffect->isMask(FR_MASK_TARGET_EFFECT)||pTempEffect->isMask(FR_MASK_PLAYER_TARGET_EFFECT)))
					bRecursion = true;
				calcDelNumByState(pTempField,bRecursion);
			}
		}
		for (int x = 0; x < FIELD_X;++x){
			pTempField = &mField[(int)pCurField->mPt.y][x];
			if (pTempField&&!pTempField->isGenIng()){
				bRecursion = false; 
				CGameFruitEffect* pTempEffect = pTempField->getFruit()->getFrontEffect();
				if(pTempEffect && (pTempEffect->isMask(FR_MASK_TARGET_EFFECT)||pTempEffect->isMask(FR_MASK_PLAYER_TARGET_EFFECT)))
					bRecursion = true;
				calcDelNumByState(pTempField,bRecursion);
			}
		}
	}
	else if (nState == eEffectNone)
	{
		if(!isContainDelVec(pCurField))
			mVecPathTotal.push_back(pCurField);
	}
	return;
}
bool CGameFruitScene::checkEffecValid(CGameFruitField* pCurField)
{
	EFruitEffect effcet = pCurField->getFruit()->getEffectVal();
	CGameFruitEffect* pE = pCurField->getFruit()->getFrontEffect();
	bool bTrigger = true;
	if (pE){
		//加判断避免无限递归
		if(pE->mbInvalid) 
			bTrigger = false;
	}
	if(!bTrigger)
		return false;

	//没有效果时
	//条件：总的消除格数需大于1才有效
	if(effcet == eEffectNone)
	{
		if (mVecPath.size() < 2)
			return false;
	}
	return true;
}
bool CGameFruitScene::isContainDelVec(CGameFruitField* pCurField)
{
	for(int i = 0; i < mVecPathTotal.size(); ++i)
	{
		if (mVecPathTotal[i] == pCurField)
		{
			return true;
		}
	}
	return false;
}
bool CGameFruitScene::isContainPathVec(CGameFruitField* pCurField)
{
	for(int i = 0; i < mVecPath.size(); ++i)
	{
		if (mVecPath[i] == pCurField)
		{
			return true;
		}
	}
	return false;
}
void CGameFruitScene::RandCrazyMode()
{
	int nTypeNum = 3;
	if(CFrData.getScore() >= FRUIT_DIFF_SCORE_1)
		nTypeNum = 4;
	if(CFrData.getScore() >= FRUIT_DIFF_SCORE_2)
		nTypeNum = 5;
	for (int x = 0; x < FIELD_X; ++x)
	{
		int nRand =CCRANDOM_0_1() * (nTypeNum - 1);
		for (int y = 0; y < FIELD_Y; ++y)
		{
			CGameFruitField& field = mField[y][x];
			field.mpLine->setVisible(false);
			field.getFruit()->getSprite()->setVisible(true);
			field.getFruit()->chgFruit(nRand+1);
			field.getFruit()->showEffect();
		}
	}
}
void CGameFruitScene::RandEffcet(EFruitEffect state)
{
	int nRand = CRandomUtil::RandomRange(0,mVecPathTotal.size()-1);
	mVecPathTotal[nRand]->getFruit()->addEffect(state);
	mVecPathTotal[nRand]->getFruit()->showEffect();

}
//单击事件开始
bool CGameFruitScene::ccTouchBegan(cocos2d::CCTouch * pTouch, cocos2d::CCEvent *pEvent)
{
	//NetHttpClient::sendHttpRequest(eNetMsgTypePlayerSys,eNetMsgCodeAddExp);
// 	CSJson::Value msg_bady;
// 	msg_bady["player_id"] = CSJson::Value(1100);
// 	msg_bady["exp"] = CSJson::Value(999);
// 	NetHttpClient::sendHttpRequest(eNetMsgTypePlayerSys,eNetMsgCodeAddExp,msg_bady);
// 	if (!CMyScheduler::GetInstance()->IsEmpty())
// 		return false;

	CCPoint ptouch = pTouch->getLocationInView();

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint ccTouchSprite = ptouch;
	ccTouchSprite.y = (visibleSize.height - ptouch.y);
	if(!mRcFieldArea.containsPoint(ccTouchSprite))
		return false;
	mVecPath.clear();
	ClearField();
	CGameFruitField* pField = GetFieldByTouch(&ccTouchSprite);
	if(pField)
	{
		if (pField->isGenIng())
		{
			return false;
		}
		mVecPath.push_back(pField);
		pField->getFruit()->NoClickFruit();
		pField->getFruit()->ClickFruit();
	}
		
	return true;
}
//单击事件拖动
void CGameFruitScene::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	if(mVecPath.empty())
		return;
	CGameFruitField* pField = mVecPath[mVecPath.size()-1];
	CCSprite *pLine = pField->mpLine;
	if(pField)
	{
		pLine->setVisible(true);
		CCPoint touch = pTouch->getLocationInView();
		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		CCPoint ccTouchSprite = touch;
		ccTouchSprite.y = (visibleSize.height - touch.y);
        CCPoint pt = pField->GetCentrePos();
		pLine->setPosition(pt);

		float angle = GetCalcAngle(ccTouchSprite,pField->GetCentrePos());
		float fScale = GetCalcScale(ccTouchSprite,pField->GetCentrePos(),pLine->getTextureRect().size.width);
		
		pLine->setScaleX(fScale);
		pLine->setRotation(angle);

		CGameFruitField* pPassField = GetFieldByTouch(&ccTouchSprite);
		if (pPassField &&IsConnectRange(pPassField,pField)){
			if(!IsExistPath(pPassField)){
				CGameFruitEffect* pSrcEffect = pField->getFruit()->getFrontEffect();
				CGameFruitEffect* pPassEffect = pPassField->getFruit()->getFrontEffect();
				if(!pPassField->isGenIng())
				{
					//两个都位万能球不连接
					if ((pSrcEffect&&pSrcEffect->mType == eEffectColour)&&(pPassEffect&&pPassEffect->mType == eEffectColour))
						return ;
					if(pPassField->getFruit()->getType() == pField->getFruit()->getType()
						||pPassField->getFruit()->getType() == eFruitTypeMulUse //目标为万能球
						||pField->getFruit()->getType() == eFruitTypeMulUse//原始为万能球
						|| (pSrcEffect&&pSrcEffect->mType == eEffectColour)
						|| (pPassEffect&&pPassEffect->mType == eEffectColour)
						|| mbFinger)
					{
						mVecPath.push_back(pPassField);
						pPassField->getFruit()->ClickFruit();
						CGameFruitField* pFieldLast = mVecPath[mVecPath.size()-1];
						CGameFruitField* pFieldPre = mVecPath[mVecPath.size()-2];
						float angle = GetCalcAngle(pFieldLast->GetCentrePos(),pFieldPre->GetCentrePos());
						float fScale = GetCalcScale(pFieldLast->GetCentrePos(),pFieldPre->GetCentrePos(),pFieldPre->mpLine->getTextureRect().size.width);
						pFieldPre->mpLine->setScaleX(fScale);
						pFieldPre->mpLine->setRotation(angle);

						//处理消除同色效果
						CGameFruitEffect* pSomeDelEffect = NULL;
						bool b = false;
						int nSomeType = 0;
						int nTemp = mVecPath.size() - 2;
						for (int i = mVecPath.size()-1; i >= nTemp; --i){
							if(mVecPath[i]->getFruit()->getEffectVal() == eEffectColour)
							{
								pSomeDelEffect = mVecPath[i]->getFruit()->getFrontEffect();
								b = true;
							}
							else
								nSomeType = mVecPath[i]->getFruit()->getType();
						}
						if(b)
						{
							pSomeDelEffect->mnColourDelType = nSomeType;
							executeDel();
						}
					}
				}
			}else
			{
				if (mVecPath.size() < 2)
					return ;
				CGameFruitField* pPreField = mVecPath[mVecPath.size() - 2];
				if (pPreField && pPreField == pPassField)
				{
					CGameFruitField* pLastField = pField;
					pLastField->mpLine->setVisible(false);
					pLastField->getFruit()->NoClickFruit();
					mVecPath.pop_back();
					pField = pPreField;
				}
			}
			
		}
	}
	
}
//单击事件结束
void CGameFruitScene::ccTouchEnded(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent)
{
	executeDel();
}
void CGameFruitScene::_calcScore()
{
	//设置分数
	int nNum = mVecPathTotal.size();
	int nGetScore = 0;
	if(nNum <= 1)
		return;
	if (nNum < 3)
	{
		nGetScore = 0; //= CCSprite::get("./game_fruit/iPhone-hd/score100.png");
		return;
	}else if(nNum < 7)
	{
		nGetScore = 200;
	}else if (nNum < 14)
	{
		nGetScore = 500;
	}else{
		nGetScore = 1000;
	}
	int nResult = mVecPathTotal.size() * nGetScore + FRUIT_CONTINUE_DEL_SCORE * CFruitData::getInstance()->getContinueNum();

	for (int i = 0; i < mVecPathTotal.size(); ++i){
		if(mVecPathTotal[i]->getFruit()->getType() == eFruitTypeMulUse){
			nResult += 20000;
		}
	}
	CFruitData::getInstance()->alterScore(nResult);
}
bool CGameFruitScene::useItem(EFrEffectType eType)
{
	CFrBaseEffect* pBaseEffect = CFrData.getEffect(eType);
	if (pBaseEffect == NULL)
		return false;
	switch(eType)
	{
	case eFrPayEffectAddContinueHit:{
			mulContinueHitTimeLimit += 1000;
			CFrData.delEffect(eFrPayEffectAddContinueHit);
			CTaskManProceDt(eDayTaskTypeShare_10,1);
		}
		break;
	case eFrPayEffectColourOpen:{
			 CFrData.addEffect(new CFrGameEffectColour);
			CFrData.delEffect(eFrPayEffectColourOpen);
			CTaskManProceDt(eDayTaskTypeShare_10,1);
		}
		break;
	case eFrPayEffectCrossOpen:{
			CFrData.addEffect(new CFrGameEffectCross);
			CFrData.delEffect(eFrPayEffectCrossOpen);
			CTaskManProceDt(eDayTaskTypeShare_10,1);
		}
		break;
	case eFrGameEffectColour:
		{
			//颜色消
			pBaseEffect = CFrData.getEffect(eFrGameEffectColour);
			CFrGameEffectColour* pCross = dynamic_cast<CFrGameEffectColour*>(pBaseEffect);
			if (pCross){
				pCross->mnCounter += mVecPathTotal.size();
			}
		}
		break;
	case eFrGameEffectCross:
		{
			//十字消
			pBaseEffect = CFrData.getEffect(eFrGameEffectCross);

			CFrGameEffectCross* pCross = dynamic_cast<CFrGameEffectCross*>(pBaseEffect);
			if (pCross){
				pCross->mnCounter += mVecPathTotal.size();
			}
		}
		break;
	case eFrPayEffectTimeDelay:{
				time_addSecond(5.0);
				CFrData.delEffect(eFrPayEffectTimeDelay);
				CTaskManProceDt(eDayTaskTypeShare_10,1);
		}
		break;
	case eFrintensifyItem:{
			CFrData.setAccumulateColLimit(CFrData.getAccumulateColLimit() - ((CFrIntersifyEffectItem*)pBaseEffect)->mnEffectVal);
			CFrData.setAccumulateRowLimit(CFrData.getAccumulateRowLimit() - ((CFrIntersifyEffectItem*)pBaseEffect)->mnEffectVal);
		}
		break;
	case eFrIntensifyAnyBall:{
		CFrIntersifyEffectAnyBall* p = ((CFrIntersifyEffectAnyBall*)pBaseEffect);
		CCLOG("eFrIntensifyAnyBall : p->mnEffectVal = %d",p->mnEffectVal);
		if (CRandomUtil::RandomRange(1,RAND_GAME_BASE_VAL) <= p->mnEffectVal)
				return true;
		return false;
		}
		break;
	case eFrIntensifyEffectGoldFinger:{
		CFrIntersifyEffectGoldFinger* pCross = dynamic_cast<CFrIntersifyEffectGoldFinger*>(pBaseEffect);
		if (pCross->mnHitTimes >= pCross->mnAmountHit){
			UIImageView* pUI = dynamic_cast<UIImageView*>(m_pUILayer->getWidgetByTag(eUILayerImageFinger));
			if(pUI->getRenderer()->numberOfRunningActions()<=0){
				pUI->runAction(CCRepeatForever::create(CCSequence::create(CCMoveBy::create(0.1f,ccp(0,-10)),CCMoveBy::create(0.1f,ccp(0,10)),NULL)));
			}
			m_pUILayer->setVisible(true);
			pCross->mnHitTimes = 0;
		}
		}
		break;
	}
	
	return true;
}
void CGameFruitScene::executeDel()
{
	for (int i = 0; i< mVecPath.size(); ++i)
	{
		mVecPath[i]->getFruit()->NoClickFruit();
		mVecPath[i]->mpLine->setVisible(false);
	}

	if (mVecPath.empty())
		return;
	if (mVecPath.size() < 2 ){
		//CFruitData::getInstance()->setContinueNum(0);
		//CFruitData::getInstance()->setCrazyContinueNum(0);
		
		CGameFruitEffect* pEffect = mVecPath[0]->getFruit()->getFrontEffect();
		if (pEffect)
		{
			if(!pEffect->isMask(FR_MASK_ALLOW_ONLY_ONE_ITEM_DEL))
			{
				Crazy_End();
				return;
			}
		}else
		{
			Crazy_End();
			return;
		}
	}

	//计算消除的水果个数
	for (int i = 0 ; i < mVecPath.size(); ++i)
	{
		CGameFruitField* pFieldPath = mVecPath[i];
		CGameFruitEffect* pEffect = pFieldPath->getFruit()->getFrontEffect();
		if (pEffect)
			pEffect->addMask(FR_MASK_PLAYER_TARGET_EFFECT);
	}
	mVecPathTotal.clear();
	for (int i = 0 ; i < mVecPath.size(); ++i)
	{
		CGameFruitField* pFieldPath = mVecPath[i];
		calcDelNumByState(pFieldPath);
	}
	//////////////////////////////////////////////////////////////////////////
	//日常任务统计
	bool bUseEffect = false;
	bool bUseColour = false;
	bool bUseColOrRowOrCross = false;
	for (int i = 0 ; i < mVecPath.size(); ++i)
	{
		
		CGameFruitField* pFieldPath = mVecPath[i];
		int eff = pFieldPath->getFruit()->getEffectVal();
		if(pFieldPath->getFruit()->getFrontEffect())
		{
			bUseEffect = true;
		}
		if (pFieldPath->getFruit()->getEffectVal() == eFrGameEffectColour)
		{
			bUseColour = true;
		}
		if (eff == eFrGameEffectCross||eff == eFrGameEffectVertical || eff == eFrGameEffectHor)
		{
			bUseColOrRowOrCross = true;
		}
	}
	if (bUseEffect)
		CTaskManProceDt(eDayTaskTypeFT_41,mVecPathTotal.size());
	else if(mVecPathTotal.size() > 10)
		CTaskManProceDt(eDayTaskTypeFT_43,1);

	if(bUseColour)
		CTaskManProce(eDayTaskTypeFT_42,mVecPathTotal.size());
	if(bUseColOrRowOrCross)
		CTaskManProceDt(eDayTaskTypeFT_44,mVecPathTotal.size());
	//////////////////////////////////////////////////////////////////////////

	//消除水果
	for (int i = 0 ; i < mVecPathTotal.size(); ++i)
	{
		CGameFruitField* pTempField = mVecPathTotal[i];
		pTempField->UpdataScore();
		pTempField->getFruit()->delFruit();

		if (pTempField->getFruit()->getType() == eFruitType_5)
			CTaskManProceDt(eDayTaskTypeFT_36,1);
		if (pTempField->getFruit()->getType() == eFruitType_2)
			CTaskManProceDt(eDayTaskTypeFT_37,1);
		if (pTempField->getFruit()->getType() == eFruitType_3)
			CTaskManProceDt(eDayTaskTypeFT_38,1);
		if (pTempField->getFruit()->getType() == eFruitType_1)
			CTaskManProceDt(eDayTaskTypeFT_39,1);
		if (pTempField->getFruit()->getType() == eFruitType_4)
			CTaskManProceDt(eDayTaskTypeFT_40,1);
		//漂浮分数
		//CImplementScheduler::ScoreFloat(dwNowTime ,dwScoreMoveTime,pTempField->getScore(),ccp(0,FIELD_HIGH/2));
	}
	//dwAmounTime += dwScoreMoveTime;

	//设置连击次数
	CFruitData::getInstance()->alterContinueNum(1);
	int nContinueNum = CFruitData::getInstance()->getContinueNum();
	if(nContinueNum == 10)
	{
		Crazy_Start(3.0);
	}else if (nContinueNum > 10)
	{
		Crazy_ReStart();
	}
	if(nContinueNum == 20)
	{
		Crazy_Start(3.0,eSuperCrazyMode);
	}else if (nContinueNum > 20)
	{
		Crazy_ReStart();
	}
	if (nContinueNum >= 20)
	{
		CFruitData::getInstance()->alterCrazyContinueNum(1);
	}
	if (nContinueNum == 0)
	{
		CFruitData::getInstance()->setCrazyContinueNum(0);
	}

	//计算分数
	_calcScore();

	//累计消除次数
	CFruitData::getInstance()->setAccumulateCol(CFruitData::getInstance()->getAccumulateCol()+mVecPathTotal.size());
	CFruitData::getInstance()->setAccumulateRow(CFruitData::getInstance()->getAccumulateRow()+mVecPathTotal.size());
	CFrIntersifyEffectGoldFinger* pCross = dynamic_cast<CFrIntersifyEffectGoldFinger*>(CFrData.getEffect(eFrIntensifyEffectGoldFinger));
	if (pCross){
		pCross->mnHitTimes += mVecPathTotal.size();
	}
	useItem(eFrGameEffectColour);
	useItem(eFrGameEffectCross);

	CTaskManProce(eDayTaskTypeShare_1,CFrData.getScore());
	CTaskManProceDt(eDayTaskTypeShare_4,1);
	CTaskManProce(eDayTaskTypeShare_7,CFrData.getContinueNum());

	//执行特效
	for (int i = 0 ; i < mVecPathTotal.size(); ++i)
	{
		mVecPathTotal[i]->getFruit()->executeEffect();
	}
	unsigned int dwNowTime = CGameTimer::GetInstance()->GetNowTime();
	unsigned int dwScoreMoveTime = 500;
	unsigned int dwGenFruitTime = 250;
	unsigned int dwAmounTime = 0;
	for (int i = 0 ; i < mVecPathTotal.size(); ++i){
		CGameFruit* pFruit = mVecPathTotal[i]->getFruit();
		if (pFruit){
			CCSprite* pSpRow = pFruit->getLightningRow();
			CCSprite* pSpCol = pFruit->getLightning();
			CCPoint pt = mVecPathTotal[i]->GetCentrePos();
			pSpCol->setPosition(pt);
			pSpRow->setPosition(pt);
			if (pFruit->getFrontEffect()&&!pFruit->getFrontEffect()->isMask(FR_MASK_PLAYER_TARGET_EFFECT))
			{
				continue;
			}
			if (pFruit->getEffectVal() == eEffectVertical){
				float fOffset = getFieldGameArea().getMidY() - pSpCol->getPositionY();
				CImplementScheduler::FruitLightning(dwNowTime + dwAmounTime,500,false,pSpCol,ccp(0,pSpCol->getPositionY() + fOffset));
			}else if(pFruit->getEffectVal() == eEffectHor)
			{
				float fOffset = getFieldGameArea().getMidX() - pSpRow->getPositionX();
				CImplementScheduler::FruitLightning(dwNowTime + dwAmounTime,500,true,pSpRow,ccp(pSpRow->getPositionX() + fOffset,0));
			}else if (pFruit->getEffectVal() == eEffectCross)
			{
				float fOffset = getFieldGameArea().getMidY() - pSpCol->getPositionY();
				CImplementScheduler::FruitLightning(dwNowTime + dwAmounTime,500,false,pSpCol,ccp(0,pSpCol->getPositionY() + fOffset));
				fOffset = getFieldGameArea().getMidX() - pSpRow->getPositionX();
				CImplementScheduler::FruitLightning(dwNowTime + dwAmounTime,500,true,pSpRow,ccp(pSpRow->getPositionX() + fOffset,0));
			}
		}
	}

	//调用公共接口显示设置
	if(nContinueNum > 0)
		setBatter(nContinueNum);
	setScore(CFruitData::getInstance()->getScore());
	boom_setEnergy(CFruitData::getInstance()->getAnger());
    CCString str;
    str.initWithFormat("medal600001_%d",Game_Fruit);
    
	CCUserDefault::sharedUserDefault()->setIntegerForKey(str.getCString(), CFrData.getScore());
	//道具特效数据删除
	//道具特效消除，避免计分需要道具特效加成
	for (int i = 0 ; i < mVecPathTotal.size(); ++i)
	{
		mVecPathTotal[i]->getFruit()->delEffect();
	}
	//超级疯狂模式
	if(CFruitData::getInstance()->getMode() == eSuperCrazyMode &&
		(CFruitData::getInstance()->getContinueNum() == 20 || CFruitData::getInstance()->getCrazyContinueNum() >= 30))
	{
		RandCrazyMode();
		if(CFruitData::getInstance()->getCrazyContinueNum() >= 30)
			CFruitData::getInstance()->setCrazyContinueNum(0);
	}else
	{
		//生成水果	
		for (int i = 0 ; i < mVecPathTotal.size(); ++i){
			CGameFruit* pFruit = mVecPathTotal[i]->getFruit();
			if (pFruit){
				CCSprite* pSp = pFruit->getBombEff();
				pSp->setScale(0.6f);
				pSp->setPosition(pFruit->getSprite()->getPosition());
				//if (pFruit->getEffectVal() == eEffectVertical)
				//{
				//	pFruit->getLightning()->setPosition(mVecPathTotal[i]->GetCentrePos());
				//	float fOffset = getFieldGameArea().getMidY() - pFruit->getLightning()->getPositionY();
					//CImplementScheduler::FruitLightning(dwNowTime + dwAmounTime,500,false,pFruit->getLightning(),ccp(0,pFruit->getLightning()->getPositionY() + fOffset));
				//}
				CImplementScheduler::FruitBomb(dwNowTime + dwAmounTime,500,pSp);
				CImplementScheduler::FruitOut(dwNowTime + dwAmounTime + 500,dwGenFruitTime,pFruit);
			}
		}
		dwAmounTime += 500;
		dwAmounTime += dwGenFruitTime;
	}
	
	//if (bMoveFruit)
	//{
	//CMyScheduler::GetInstance()->FruitMoveEnd(dwNowTime + dwAmounTime + dwFruitMoveTime  ,0,this);
	//}

	CImplementScheduler::AllMoveEnd(dwNowTime + dwAmounTime,0,this);
	mulLastTouchTime = CGameTimer::GetInstance()->GetNowTime();

	mVecPath.clear();
	ClearField();
}
void CGameFruitScene::AllMoveEnd()
{
	if(CFruitData::getInstance()->getGenBomb())
	{
		if(CFrData.getGenBomb())
		{
			RandEffcet(eEffectBomb);
			CFrData.setGenBomb(false);
		}
	}

	if (CFruitData::getInstance()->getMode() == eComCrazyMode)
	{
	}
	//超级疯狂模式
// 	if(CFruitData::getInstance()->getMode() == eSuperCrazyMode &&
// 		(CFruitData::getInstance()->getContinueNum() == 20 || CFruitData::getInstance()->getCrazyContinueNum() >= 30))
// 	{
// 		RandCrazyMode();
// 		if(CFruitData::getInstance()->getCrazyContinueNum() >= 30)
// 			CFruitData::getInstance()->setCrazyContinueNum(0);
// 	}

	//消图大于50
	CCLOG("getAccumulateCol() = %d",CFruitData::getInstance()->getAccumulateCol());
	if (CFruitData::getInstance()->getAccumulateCol() >= CFrData.getAccumulateColLimit())
	{
		RandEffcet(eEffectHor);
		CFruitData::getInstance()->setAccumulateCol(0);
	}
	CCLOG("getAccumulateRow() = %d",CFruitData::getInstance()->getAccumulateRow());
	if (CFruitData::getInstance()->getAccumulateRow() >= CFrData.getAccumulateRowLimit())
	{
		RandEffcet(eEffectVertical);
		CFruitData::getInstance()->setAccumulateRow(0);
	}

	CFrBaseEffect* pBaseEffect = NULL;
	pBaseEffect = CFrData.getEffect(eFrGameEffectColour);
	if (pBaseEffect){
		CFrGameEffectColour* pCross = dynamic_cast<CFrGameEffectColour*>(pBaseEffect);
		if (pCross && pCross->mnCounter >= pCross->mnLimitNum){
			RandEffcet(eEffectColour);
			pCross->mnCounter = 0;
		}
	}
	pBaseEffect = CFrData.getEffect(eFrGameEffectCross);
	if (pBaseEffect){
		CFrGameEffectCross* pCross = dynamic_cast<CFrGameEffectCross*>(pBaseEffect);
		if (pCross && pCross->mnCounter >= pCross->mnLimitNum){
			RandEffcet(eEffectCross);
			pCross->mnCounter = 0;
		}
	}
	//
	if (useItem(eFrIntensifyAnyBall))
	{
		RandEffcet(eEffectMultipleUse);
	}
	useItem(eFrIntensifyEffectGoldFinger);
	
}

//注册单击事件
void CGameFruitScene::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority + 1, true);
}
void CGameFruitScene::update(float fDelta)
{
	CCNode::update(fDelta);
	CGameScheduler::GetInstance()->Update();
	if (CGameTimer::GetInstance()->GetNowTime() - mulLastTouchTime > mulContinueHitTimeLimit){
		//重置连续次数
		CFruitData::getInstance()->setContinueNum(0);
		CFruitData::getInstance()->setCrazyContinueNum(0);
		//设置连击次数
		CFrIntersifyEffectGoldFinger* pCross = dynamic_cast<CFrIntersifyEffectGoldFinger*>(CFrData.getEffect(eFrIntensifyEffectGoldFinger));
		if (pCross) pCross->mnHitTimes = 0;

	}
	CFrIntersifyEffectGoldFinger* pFinger = (CFrIntersifyEffectGoldFinger*)CFrData.getEffect(eFrIntensifyEffectGoldFinger);
	if (CGameTimer::GetInstance()->GetNowTime() - pFinger->mnLastTime > 2000){
		if (mbFinger){
			for (int y = 0 ; y < FIELD_Y; ++y){
				for (int x = 0; x < FIELD_X;++x){
					CGameFruitField* pField = &mField[y][x];
					pField->getFruit()->getSprite()->stopAllActions();
					pField->getFruit()->getSprite()->setRotation(0);
					pField->getFruit()->getSprite()->setScale(1.f);
				}
			}
			//消除已连接图形
			executeDel();
			mbFinger = false;
		}
	}
		
	CGameTimer::GetInstance()->Update(fDelta*1000.f);
}
void CGameFruitScene::onEnter()
{
	GameShare_Scene::onEnter();
	CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(this, 0, false);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(CGameFruitScene::noticeBombEffect), NOTICE_FRUIT_BOMB_EFFECT, NULL);
	
	CAudioHelper::playBackgroundSound(eSoundTypeFruiteBackground);
}
void CGameFruitScene::onExit()
{
	GameShare_Scene::onExit();
	CCDirector::sharedDirector()->getScheduler()->unscheduleUpdateForTarget(this);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, NOTICE_FRUIT_BOMB_EFFECT);
	
	CAudioHelper::stopBackgroundSound();
}
void CGameFruitScene::noticeBombEffect(CCObject* obj)
{
	time_addSecond(5.0);
}
// a selector callback
void CGameFruitScene::menuCloseCallback(CCObject* pSender)
{
}


void CGameFruitScene::msgHanlde_GameTimeOut(CCObject* obj)
{
	if(CFrData.getScore() == 0)
		CTaskManProceDt(eDayTaskTypeShare_11,1);
	if (mbUseCrossBomb)
	{
		CTaskManProceDt(eDayTaskTypeFT_32,1);
	}
	if (mbUseColour)
	{
		CTaskManProceDt(eDayTaskTypeFT_33,1);
	}
	if (CFrData.getNoUsePlayItem())
		CTaskManProceDt(eDayTaskTypeShare_9,1);
	//游戏道具加时
	GameShare_Scene::msgHanlde_GameTimeOut(obj);
	
}
//疯狂模式结束消息处理函数
void CGameFruitScene::msgHandle_CrazyTimeOut(CCObject* obj)
{
	//重置连续次数
	CFruitData::getInstance()->setContinueNum(0);
	CFruitData::getInstance()->setCrazyContinueNum(0);
}
void CGameFruitScene::OnImgEvent(CCObject* sender){
	if(!m_pUILayer->isVisible())
		return ;
	if(mbFinger)
		return ;
	CTaskManProceDt(eDayTaskTypeFT_34,1); 
	mbFinger = true;
	CFrIntersifyEffectGoldFinger* pFinger = (CFrIntersifyEffectGoldFinger*)CFrData.getEffect(eFrIntensifyEffectGoldFinger);
	m_pUILayer->setVisible(false);
	pFinger->mnLastTime = CGameTimer::GetInstance()->GetNowTime(); 
	//m_pUILayer->getWidgetByTag(eUILayerImageFinger)->setVisible(false);
	for (int y = 0 ; y < FIELD_Y; ++y){
		for (int x = 0; x < FIELD_X;++x){
			CGameFruitField* pField = &mField[y][x];
			pField->getFruit()->shakeEffect();
		}
	}
}
void CGameFruitScene::startGame(float dt/* =1.0 */){
	
	if(useItem(eFrPayEffectAddContinueHit))
	{

	}
	if(useItem(eFrintensifyItem))
	{

	}
	if (useItem(eFrPayEffectColourOpen))
	{
	}
	if (useItem(eFrPayEffectCrossOpen))
	{
	}
	CFrBaseEffect* pBaseEffect = CFrData.getEffect(eFrIntensifyEffectGoldFinger);
	CFrIntersifyEffectGoldFinger* pCross = dynamic_cast<CFrIntersifyEffectGoldFinger*>(pBaseEffect);
	if (pCross){
		pCross->mnAmountHit -= pCross->mnEffectVal;
	}
}

void CGameFruitScene::noticeTimeInterval(CCObject* obj)
{
	GameShare_Scene::noticeTimeInterval(obj);
	if (((GameShare_TimeProcess*)obj)->GetSecondsRemain() <= 2)
	{
		if (useItem(eFrPayEffectTimeDelay))
		{
			useTimeEff();
			return ;
		}

	}

	if (((GameShare_TimeProcess*)obj)->GetSecondsRemain() >= 40) {
		CTaskManProce(eDayTaskTypeShare_5, CFrData.getScore());
	}
}
