

#include "GameShare_TimeProcess.h"
#include "Scene_GameOver.h"
#include "RandomUtil.h"
#include "TaikoScene.h"
#include "SpriteFrameManage.h"
#include "ComData.h"
#include "GameLayerTaiKo.h"
#include "TaikoCell.h"
#include "TaikoDefine.h"
#include "TaikoData.h"
#include "DataManager.h"
#include "AudioHelper.h"
#include "AudioDefine.h"
#include "ImageDownloader.h"
#include "EffectActionHelp.h"
#include "NumSprite.h"
#include "GameItemManager.h"
#include "TaskDefine.h"

USING_NS_CC;
#define _OffsetY_Max  150

CTaikoScene::CTaikoScene():mfLastTouchTime(0),mbStart(false),mfASpeed(1.f),mfStartSpeed(3.f),mfGenCellInterval(0.f),mbClickCellLong(false),mpDrumEff(NULL),mpOpState(NULL)
	,mbUseHit(false),mbUseQuickRhythm(false),mnCounterPerfectHitTimes(0),mnCounterGreatHitTimes(0),meCurrentHitType(eTaikoNone),meLastHitType(eTaikoNone),mbSaveTask57Score(true)
{
	//char szStr[2048] = "";
	//CDataManager::GetInstance().Convert("\xe5\x82\xbb\xe5\xa6\x9e\xe5\xa6\x9e\xe8\xa6\x81\xe5\xa5\x8b\xe6\x96\x97\xe5\x95\xa6",szStr,CP_UTF8,CP_ACP);
	//int a = 0;
}
CTaikoScene::~CTaikoScene()
{
// 	for (int i = 0 ; i < mVecFruit.size(); ++i)
// 	{
// 		CGameFruit* pFruit = mVecFruit[i];
// 		CC_SAFE_RELEASE_NULL(pFruit);
// 
// 	}
// 	//CFruitData* pData = ;
// 	CFruitData::getInstance()->purge();
	CTKData.purge();
}
CCScene* CTaikoScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	//    HelloWorld *layer = HelloWorld::create();

	CTaikoScene *layer = CTaikoScene::create();

	// add layer as a child to scene
	 scene->addChild(layer);

	// return the scene
	return scene;
}

bool CTaikoScene::init()
{
	if (!GameShare_Scene::init()) {
		return false;
	}
	CTKData.reset();
	//鈥γ嬅封垰鈭懨仿犓?
	this->setScore(0);
	//鈥γ嬅封垰茠鈥孤÷垛棅脫楼脹梅碌
	boom_setMaxBoomEnergy();
	boom_setEnergy(0);
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	
	//CCSpriteFrameManage::getInstance()->addSpriteFramesWithFile("tai_ko/tai_ko0.plist");
	
	//mfCellArriveTimeInterval = 3.f;
	CGameLayerTaiko* p = CGameLayerTaiko::create();
	p->setTouchEnabled(true);
	p->setTag(CGameLayerTaiko::getDialogIDD());
	this->addChild(p,eTaiKoSceneLayerGame);

	CCSprite* pBgRole = CCSprite::create("CocoStudioResources/tai_ko/bg_role.png");
	CCSprite* pYinXiang = CCSprite::create("CocoStudioResources/tai_ko/yinxiang.png");
	
	pBgRole->addChild(pYinXiang);
	pYinXiang->setPosition(ccp(p->getWidgetByName("yinxiang")->getPosition().x + pBgRole->getContentSize().width/2
		,p->getWidgetByName("yinxiang")->getPosition().y + pBgRole->getContentSize().height/2));
	//显示棍子
	CCSprite* pLightL = CCSprite::create("CocoStudioResources/tai_ko/light1.png");
	pLightL->setAnchorPoint(ccp(1.0,0));
	setLightRotateAct(pLightL,0.5f,-60);
	CCSprite* pLightR = CCSprite::create("CocoStudioResources/tai_ko/light1.png");
	pLightR->setAnchorPoint(ccp(0.0,0));
	pLightR->setFlipX(true);
	setLightRotateAct(pLightR,0.5f,60);

	pBgRole->setPosition(ccp(visibleSize.width/2 , visibleSize.height - pBgRole->getContentSize().height/2  ));
	pBgRole->setTag(100);
	this->addChild(pBgRole, eTaiKoSceneLayerBgRole);
	this->addChild(pLightR, 99);
	this->addChild(pLightL, 99);

	mRcTarget = p->getWidgetByName("ImgIn")->getRect();
	mRcTargetGreen = CCRectMake(mRcTarget.getMinX(),mRcTarget.getMidY(),mRcTarget.size.width,mRcTarget.size.height/2);
	mRcTargetPrefect = CCRectMake(mRcTarget.getMinX(),mRcTarget.getMinY(),mRcTarget.size.width,mRcTarget.size.height/2);
	mptStartPos = ccp(GetVSe.width /2, GetVSe.height - 340);
	p->getWidgetByName("BtnIn")->setVisible(false);
	//p->getWidgetByName("BtnIn")->setVisible(true);
	p->getWidgetByName("cyc_big_drum_l_0")->setVisible(false);
	p->getWidgetByName("cyc_big_drum_r")->setVisible(false);

	p->getWidgetByName("bg_role")->setVisible(false);
	pBgRole->setPosition(p->getWidgetByName("bg_role")->getPosition());

	p->getWidgetByName("lightTL")->setVisible(false);
	pLightL->setPosition(p->getWidgetByName("lightTR")->getPosition());
	pLightL->setAnchorPoint(p->getWidgetByName("lightTR")->getAnchorPoint());

	p->getWidgetByName("lightTR")->setVisible(false);
	pLightR->setPosition(p->getWidgetByName("lightTL")->getPosition());
	pLightR->setAnchorPoint(p->getWidgetByName("lightTL")->getAnchorPoint());

	p->getWidgetByName("cyc_big_drum_ef_r")->setVisible(false);
	p->getWidgetByName("cyc_big_drum_ef_l")->setVisible(false);

	//set light position
	UIWidget*  pUIMR= p->getWidgetByName("lightML");
	UIWidget*  pUIML= p->getWidgetByName("lightMR");
	pUIML->setVisible(false);
	pUIMR->setVisible(false);
	CCSprite* pLightML = CCSprite::create("CocoStudioResources/tai_ko/light2.png");
	addChild(pLightML,99);
	pLightML->setAnchorPoint(pUIML->getAnchorPoint());
	pLightML->setPosition(pUIML->getPosition());
	pLightML->setRotation(pUIML->getRotation());
	
	CCSprite* pLightMR = CCSprite::create("CocoStudioResources/tai_ko/light2.png");
	pLightMR->setAnchorPoint(pUIMR->getAnchorPoint());
	pLightMR->setFlipX(true);
	pLightMR->setPosition(pUIMR->getPosition());
	pLightMR->setRotation(pUIMR->getRotation());
	addChild(pLightMR,99);
	//set light ratate
	//setLightRotateAct(p->getWidgetByName("lightML")->getRenderer(),1.0f,80);
	//setLightRotateAct(p->getWidgetByName("lightMR")->getRenderer(),1.0f,-80);
	setLightRotateAct(pLightML,1.0f,-80);
	setLightRotateAct(pLightMR,1.0f,80);

	setLightRotateAct(p->getWidgetByName("lightBL")->getRenderer(),1.0f,-120);
	setLightRotateAct(p->getWidgetByName("lightBR")->getRenderer(),1.0f,120);

	p->getWidgetByName("ufo_l")->getRenderer()->runAction(CCRepeatForever::create(CCSequence::create(CCMoveBy::create(2.f,ccp(0.f,10.f)),CCMoveBy::create(2.f,ccp(0.f,-10.f)),NULL)));
	p->getWidgetByName("ufo_r")->getRenderer()->runAction(CCRepeatForever::create(CCSequence::create(CCMoveBy::create(1.5f,ccp(0.f,8.f)),CCMoveBy::create(2.f,ccp(0.f,-8.f)),NULL)));

	if (mpDrumEff == NULL)
	{
		mpDrumEff = CCSprite::create();
	}
	if (mpOpState == NULL)
	{
		mpOpState = CCSprite::create();
	}
	this->addChild(mpDrumEff,eTaiKoSceneLayerGame);
	this->addChild(mpOpState,eTaiKoSceneLayerBgRole);
	
	UIWidget* pUI = p->getWidgetByName("ImgIn");
	mpDrumEff->setPosition(ccp(pUI->getRect().getMidX() + 4,pUI->getRect().getMaxY() + 64));
	mpOpState->setPosition(ccp(pUI->getRect().getMidX(),pUI->getRect().getMaxY() + 20));

	//任务动画
	auto pRole = CCSprite::create("CocoStudioResources/tai_ko/role/1.png");
	CCAnimation* pAni2 = CCAnimation::create();
	pAni2->addSpriteFrameWithFileName(("CocoStudioResources/tai_ko/role/5.png"));
	pAni2->addSpriteFrameWithFileName(("CocoStudioResources/tai_ko/role/6.png"));
	pAni2->addSpriteFrameWithFileName(("CocoStudioResources/tai_ko/role/4.png"));
	pAni2->addSpriteFrameWithFileName(("CocoStudioResources/tai_ko/role/5.png"));
	pAni2->addSpriteFrameWithFileName(("CocoStudioResources/tai_ko/role/6.png"));
	pAni2->setDelayPerUnit(0.12f);
	pAni2->setLoops(1);
	CCAnimation* pAni1 = CCAnimation::create();
	CCString str;
	//123 123 56456
	for (int i = 1; i <= 3; ++i){
		str.initWithFormat("CocoStudioResources/tai_ko/role/%d.png",i);
		pAni1->addSpriteFrameWithFileName((str.getCString()));
	}
	for (int i = 1; i <= 3; ++i){
		str.initWithFormat("CocoStudioResources/tai_ko/role/%d.png",i);
		pAni1->addSpriteFrameWithFileName((str.getCString()));
	}
	pAni1->setDelayPerUnit(0.12f);
	pAni1->setLoops(1);
	
	CCActionInterval* pInter = CCMoveBy::create(0.12f*6.f,ccp(60,0));
	CCActionInterval* pSeq = CCSequence::create(CCSpawn::create(CCAnimate::create(pAni2),pInter,NULL),CCSpawn::create(CCAnimate::create(pAni1),pInter->reverse(),NULL),NULL);
	pRole->runAction(CCRepeatForever::create(pSeq));
	this->addChild(pRole,98);
	pRole->setPosition(ccp(p->getWidgetByName("bg_role")->getPosition().x,p->getWidgetByName("bg_role")->getPosition().y - 18 + 46) );
	return true;
	
}
void CTaikoScene::setLightRotateAct(CCNode* p,float fTime,float fAngle)
{
		CCActionInterval* pRot = CCRotateBy::create(fTime,-fAngle);
	p->runAction(CCRepeatForever::create(CCSequence::create(pRot,pRot->reverse(),NULL)));
	
}
void CTaikoScene::initBgView()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCSprite* pSprite = CCSprite::create("CocoStudioResources/tai_ko/bg.jpg");
	pSprite->setPosition(ccp(visibleSize.width/2 , visibleSize.height/2));
	this->addChild(pSprite, 0);
//    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
//    
//    
//    CCSprite* topSprite = CCSprite::createWithSpriteFrameName("GameSceneBg/TaikoBar.jpg");
//    topSprite->setAnchorPoint(ccp(0, 0));
//    topSprite->setPosition(ccp(0, visibleSize.height-topSprite->getContentSize().height));
//    
//    CCSprite* pSprite = CCSprite::createWithSpriteFrameName("GameSceneBg/GameBg.png");
//    pSprite->setAnchorPoint(ccp(0, 0));
//    pSprite->setPosition(ccp(0 , 0));
//    
//    this->addChild(topSprite, 0);
//    this->addChild(pSprite, 0);
	
}
void CTaikoScene::start()
{  
}
void CTaikoScene::startGame(float dt)
{
	//////////////////////////////////////////////////////////////////////////
	//测试
	//CTKData.addEffect(new CTaikoPayEffectABlow);
	//////////////////////////////////////////////////////////////////////////
	//一击
	useItem(eTaikoPayEffectABlow);
	
	addTarget();
	mfLastTouchTime = 0.0f;
	mbStart = true;
}
//碌鈥⒙溌犅核浢糕劉聽潞
bool CTaikoScene::ccTouchBegan(cocos2d::CCTouch * pTouch, cocos2d::CCEvent *pEvent)
{
	CCPoint ptouch = pTouch->getLocationInView();

	//CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint ccTouchSprite = CCDirector::sharedDirector()->convertToGL(ptouch);
	return false;
}
//碌鈥⒙溌犅核浢暸撯垈脴
void CTaikoScene::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	
}

//碌鈥⒙溌犅核浳┞仿犅?
void CTaikoScene::ccTouchEnded(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent)
{
	
}

void CTaikoScene::update(float fDelta)
{
	CCNode::update(fDelta);
	if(!mbStart)
		return ;
	mfLastTouchTime += fDelta ;
	float fCellArriveTimeInterval = mfStartSpeed * mfASpeed;
	float fGenCellInterval = mfGenCellInterval;
    _updataGenInterval();
	
	//生成震鼓
	CTaikoGameEffectShakeDrum* pS = (CTaikoGameEffectShakeDrum*)CTKData.getEffect(eTaikoGameEffectShakeDrum);
	if(useItem(eTaikoGameEffectShakeDrum)){
		if(mfLastTouchTime < pS->mfGenInterval){
			if(mVecCellValid.empty())
				addTarget();
			else
			{
				CTaikoCell* pTemp = mVecCellValid[mVecCellValid.size()-1];
				float fSpace = pTemp->getCollisionArea().size.height/3;
				if(pTemp->getType() != eTaikoType_BigDrum )
					fSpace = pTemp->getCollisionArea().size.height;
				if (ccpDistance(pTemp->getPosition(),mptStartPos) >= fSpace){
					addTarget();
				}
			}
			
		}else{
			mfLastTouchTime = 0;
			pS->mbGening = false;
			pS->mnCounter = 0;
		}
	}
	//普遍鼓
	else
	{
		if(mVecCellValid.empty())
			addTarget();
		else
		{
			CTaikoCell* pTemp = mVecCellValid[mVecCellValid.size()-1];
			float fSpace = pTemp->getCollisionArea().size.height;
 			float fLen =   fGenCellInterval/CCDirector::sharedDirector()->getDeltaTime() * pTemp->getDisplacement() ;
			fSpace -= fLen;
			if(fSpace < 20) fSpace = 20;
			if (ccpDistance(ccp(pTemp->getCollisionArea().getMidX(),pTemp->getCollisionArea().getMinY()),mptStartPos) < fSpace){
				mfLastTouchTime = 0.0f;
			}else if (mfLastTouchTime > fGenCellInterval){
				addTarget();
				mfLastTouchTime = 0.0f;
			}
			
		}
	}
	
	
	//碌惟楼脭蟺茠芦炉鈥澝?
	((CGameLayerTaiko*)this->getChildByTag(CGameLayerTaiko::getDialogIDD()))->getWidgetByName("BtnIn")->setVisible(false);
	((CGameLayerTaiko*)this->getChildByTag(CGameLayerTaiko::getDialogIDD()))->getWidgetByName("cyc_big_drum_r")->setVisible(false);
	((CGameLayerTaiko*)this->getChildByTag(CGameLayerTaiko::getDialogIDD()))->getWidgetByName("cyc_big_drum_l_0")->setVisible(false);
// 	((CGameLayerTaiko*)this->getChildByTag(CGameLayerTaiko::getDialogIDD()))->getWidgetByName("BtnIn")->setVisible(true);
// 	((CGameLayerTaiko*)this->getChildByTag(CGameLayerTaiko::getDialogIDD()))->getWidgetByName("cyc_big_drum_r")->setVisible(true);
// 	((CGameLayerTaiko*)this->getChildByTag(CGameLayerTaiko::getDialogIDD()))->getWidgetByName("cyc_big_drum_l_0")->setVisible(true);
	((CGameLayerTaiko*)this->getChildByTag(CGameLayerTaiko::getDialogIDD()))->getWidgetByName("ImgIn")->setVisible(true);
	((CGameLayerTaiko*)this->getChildByTag(CGameLayerTaiko::getDialogIDD()))->getWidgetByName("Btn0")->setVisible(true);
	((CGameLayerTaiko*)this->getChildByTag(CGameLayerTaiko::getDialogIDD()))->getWidgetByName("Btn1")->setVisible(true);
	if (!mVecCellValid.empty()){
		CTaikoCell* pCell = mVecCellValid[0];
		//震鼓类型
		if (pCell->getType() == eTaikoType_BigDrum){
			((CGameLayerTaiko*)this->getChildByTag(CGameLayerTaiko::getDialogIDD()))->getWidgetByName("Btn0")->setVisible(false);
			((CGameLayerTaiko*)this->getChildByTag(CGameLayerTaiko::getDialogIDD()))->getWidgetByName("Btn1")->setVisible(false);
			((CGameLayerTaiko*)this->getChildByTag(CGameLayerTaiko::getDialogIDD()))->getWidgetByName("BtnIn")->setVisible(true);
			((CGameLayerTaiko*)this->getChildByTag(CGameLayerTaiko::getDialogIDD()))->getWidgetByName("cyc_big_drum_r")->setVisible(true);
			((CGameLayerTaiko*)this->getChildByTag(CGameLayerTaiko::getDialogIDD()))->getWidgetByName("cyc_big_drum_l_0")->setVisible(true);
			((CGameLayerTaiko*)this->getChildByTag(CGameLayerTaiko::getDialogIDD()))->getWidgetByName("ImgIn")->setVisible(false);
			//震鼓删除区域
			CTaikoGameEffectShakeDrum* pSD = (CTaikoGameEffectShakeDrum*)CTKData.getEffect(eTaikoGameEffectShakeDrum);
			if (pCell->getCollisionArea().getMinY() <= mRcTarget.getMaxY())
			{
				pCell->executeDel(false);
				pSD->mbClickValid = true;
			}
			//设置震鼓分数加成有效
			if (pSD->mbClickValid)
			{
				if (mVecCellValid.empty())
					pSD->mbClickValid = false;
				else if(mVecCellValid[0]->getType() != eTaikoGameEffectShakeDrum)
					pSD->mbClickValid = false;
			}
		}
		else{
			//延长乐点集中判断
			if (mbClickCellLong)
			{
				CTaikoCellEffect* pRealEffect = pCell->getFrontEffect();
				if(pRealEffect&&pRealEffect->mType == eTaikoEffectBomb)
				{
					_calc(pCell);
					pCell->executeDel(false);
					mbClickCellLong = false;
				}
				else if (pCell->getType() == eTaikoType_1_Long||pCell->getType() == eTaikoType_2_Long)
				{
					if (pCell->getCollisionAreaHead().getMidY() <= mRcTarget.getMidY())
					//if (pCell->getCollisionAreaHead().getMaxY() <= mRcTarget.getMaxY())//test
					{
						pCell->setClicking(true); 
						pCell->stopHead(mRcTarget.getMidY() - pCell->getCollisionAreaHead().getMidY());
						
						//pCell->getsp
						mptSplit = ccp(0,mRcTarget.getMidY() + pCell->getCollisionAreaHead().size.height/2);
						//mptSplit = ccp(0,mRcTarget.getMaxY()); ;
						pCell->updataTextureArea(mptSplit);
						//CCLOG("tailMovePos = %f",pCell->getCollisionAreaHead().getMaxY() + pCell->getVecHitSplitInfo()[0].fPos);
						if (!pCell->getVecHitSplitInfo()[0].bUse && mptSplit.y >= pCell->getCollisionAreaHead().getMaxY() + pCell->getVecHitSplitInfo()[0].fPos)
						{
							_calc(pCell);
							_executeOpStateEff(pCell);
							pCell->getVecHitSplitInfo()[0].bUse = true;

							//3 times add score 10000
							CTKData.alterScore(10000);
							CTaskManProceDt(eDayTaskTypeTK_58,1);
							
						}else if (!pCell->getVecHitSplitInfo()[1].bUse &&mptSplit.y >= pCell->getCollisionAreaHead().getMaxY() + pCell->getVecHitSplitInfo()[1].fPos)
						{
							_calc(pCell);
							pCell->getVecHitSplitInfo()[1].bUse = true;
							_executeOpStateEff(pCell);
							
						}else if (!pCell->getVecHitSplitInfo()[2].bUse &&mptSplit.y >= pCell->getCollisionAreaHead().getMaxY() + pCell->getVecHitSplitInfo()[2].fPos)
						{
							
							_calc(pCell);
							_executeOpStateEff(pCell);
							pCell->getVecHitSplitInfo()[2].bUse = true;
						}
					}
				//	CCLOG("getSpriteTail()->getTextureRect().size.height = %f",pCell->getSpriteTail()->getTextureRect().size.height);
					if(pCell->getSpriteTail()->getTextureRect().size.height <= 0)
					{
						pCell->executeDel(false);
						mbClickCellLong = false;
					}
				}
			}
			//细胞出区域后
			else if (!pCell->getMiss()&&pCell->getCollisionArea().getMinY() <  mRcTarget.getMinY())
			{
				if(pCell->getClicking()){
					pCell->getSprite()->setVisible(false);
					pCell->getSpriteBg()->setVisible(false);
					pCell->getSpriteEff()->setVisible(false);
				}
				//无效类型的细胞
				if (pCell->getType() == eTaikoType_Invalid && pCell->getOpState() != ETaikoOpMiss && pCell->getOpState() != ETaikoOpProtect){
					//CTKData.setStateOp(ETaikoOpPerfect);
					pCell->setOpState(ETaikoOpPerfect);
					_calc(pCell);
					_executeDel();
				}
				//没有点中情况加速
				else if(pCell->getCollisionArea().getMinY() < mRcTarget.getMinY()){
					//pCell->setMiss(true);
					opErr(pCell,false);
					pCell->setUse(false);
					pCell->setASpeed(4.f);
					pCell->executeASpeed();
					delCell(pCell);
					//CEffectActionHelper::play(eHelpShield,pCell);
					
				}
			}
		}
	}
	for (int i = 0; i < mVecCellInvalid.size(); ++i){
		CTaikoCell* pCell = mVecCellInvalid[i];
		if (pCell->getCollisionArea().getMaxY() <= 0 ){
			pCell->setUse(true);
			pCell->setVisible(false);
		}
	}

}
void CTaikoScene::addTarget()
{
	CTaikoCell* p = NULL;
	bool bSuc = false;
	for (int i = 0; i < mVecCellInvalid.size(); i++){
		p = mVecCellInvalid[i];
		if(p->getUse()){
			bSuc = true;
			p->setVisible(true);
			p->reset();
			mVecCellInvalid.erase(mVecCellInvalid.begin() + i);
			break;
		}
	}
	if(!bSuc){
		p = CTaikoCell::create();
		//UIWidget* pUI = ((CGameLayerTaiko*)this->getChildByTag(CGameLayerTaiko::getDialogIDD()))->getWidgetByName("bg");
		//pUI->getRenderer()->addChild(p,1);
		addChild(p,1);
	}
	mVecCellValid.push_back(p);

	//CCLOG("mVecCellInvalid.size = %lu ,mVecCellValid.size = %lu",mVecCellInvalid.size(),mVecCellValid.size());
	//p->setAnchorPoint(ccp(0.5f,0.f));
	p->setSpeed(mfStartSpeed);
    p->setASpeed(mfASpeed);
	p->setSpeedFactor(1.f);
	p->setPosition(mptStartPos);
	p->randCell();
	mptArrivePos = ccp(p->getCollisionArea().getMidX(),-p->getCollisionArea().size.height);

	p->moveTo(mptArrivePos);
	
	//pSp->setAnchorPoint(ccp(0.f,0.5f));

	
}
void CTaikoScene::onEnter()
{
	GameShare_Scene::onEnter();
	CAudioHelper::playBackgroundSound(eSoundTypeTaikoBackground);
	CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(this, 0, false);
}
void CTaikoScene::onExit()
{
	GameShare_Scene::onExit();
	CAudioHelper::stopBackgroundSound();
	CCDirector::sharedDirector()->getScheduler()->unscheduleUpdateForTarget(this);
}

// a selector callback
void CTaikoScene::menuCloseCallback(CCObject* pSender)
{

}

void CTaikoScene::msgHanlde_GameTimeOut(CCObject* obj)
{
	if (mbUseHit)
	{
		CTaskManProceDt(eDayTaskTypeTK_47,1);
	}
	if (mbUseQuickRhythm)
	{
		CTaskManProceDt(eDayTaskTypeTK_48,1);
	}
	if (mnCounterGreatHitTimes > mnCounterPerfectHitTimes)
	{
		CTaskManProceDt(eDayTaskTypeTK_62,1);
	}else if (mnCounterPerfectHitTimes > mnCounterGreatHitTimes)
	{
		CTaskManProceDt(eDayTaskTypeTK_63,1);
	}
	if (CTKData.getInvaildCellGenTimes() <= CTKData.getInvaildCellHitTimes())
	{
		CTaskManProceDt(eDayTaskTypeTK_55,1);
	}
	if (mbSaveTask57Score)
	{
		CTaskManProceDt(eDayTaskTypeTK_57,CTKData.getScore());
	}
	if(CTKData.getScore() == 0)
		CTaskManProceDt(eDayTaskTypeShare_11,1);

	if (!CTKData.getUseBomb() && CTKData.getScore() >= 50000)
		CTaskManProceDt(eDayTaskTypeShare_13,1);
	if (CTKData.getNoUsePlayItem())
		CTaskManProceDt(eDayTaskTypeShare_9,1);

	GameShare_Scene::msgHanlde_GameTimeOut(obj);
	((CGameLayerTaiko*)this->getChildByTag(CGameLayerTaiko::getDialogIDD()))->setTouchEnabled(false);
	
}
void CTaikoScene::msgHanlde_GameTimeOutPer(CCObject* obj)
{
	GameShare_Scene::msgHanlde_GameTimeOutPer(obj);
}
//鈭懨嬅该捚捖Ｂ犖┪┞仿犅撍毰撀⒙ヂ堵棵屸埆脴聽藵
void CTaikoScene::msgHandle_CrazyTimeOut(CCObject* obj)
{
	//梅每梅鈭毬÷ㄢ€撀ヅ捖犓?
// 	CFruitData::getInstance()->setContinueNum(0);
// 	CFruitData::getInstance()->setCrazyContinueNum(0);
}
void CTaikoScene::noticeTimeInterval(CCObject* obj)
{
	GameShare_Scene::noticeTimeInterval(obj);
	((CGameLayerTaiko*)this->getChildByTag(CGameLayerTaiko::getDialogIDD()))->setTouchEnabled(true);
	if (((GameShare_TimeProcess*)obj)->GetSecondsRemain() <= 0)
	{
		((CGameLayerTaiko*)this->getChildByTag(CGameLayerTaiko::getDialogIDD()))->setTouchEnabled(false);
	}
	if (((GameShare_TimeProcess*)obj)->GetSecondsRemain() <= 2)
	{
		if (useItem(eTaikoPayEffectTimeDelay))
		{
			useTimeEff();
			return ;
		}

	}

	if (((GameShare_TimeProcess*)obj)->GetSecondsRemain() >= 40) {
		CTaskManProce(eDayTaskTypeShare_5, CTKData.getScore());
	}
}
void CTaikoScene::clickBtn0()
{
	mbClickCellLong = false;
}
void CTaikoScene::clickBtn1()
{
	mbClickCellLong = false;
}

void CTaikoScene::clickBtnType(int nType){ 
	//test
// 	CCSprite* p1 = (CCSprite*)this->getChildByTag(100);
// 	p1->setAnchorPoint(ccp(0.f,1.f));
// 	static float fyy = p1->getPositionY() - p1->getContentSize().height;
// 	static float fOffectY = 0 ;
// 	p1->setPositionY(mptStartPos.y - fOffectY);
// 	CCRect rc1 = p1->getTextureRect();
// 	rc1.size.height -= fOffectY;
// 	
// 	p1->setTextureRect(rc1);
// 	fOffectY += 5;
	if (clickBtnDrum(nType))
		return;
	CTKData.setStateOp(ETaikoOpNone);
	if(mVecCellValid.empty())
		return;
	CTaikoCell* pCell = NULL;
	int nCounter = 0;
	do{
		if(nCounter >= mVecCellValid.size())
			return;
		pCell = mVecCellValid[nCounter];
		nCounter++;
	}while(pCell->getMiss());
	if (pCell->getType() == eTaikoType_BigDrum)
	{
		return;
	}
	if (pCell->getOpState() == ETaikoOpMiss
		|| pCell->getOpState() == ETaikoOpProtect)
	{
		return;
	}
	mbClickCellLong = false;
	bool bType = false;
	
	if (pCell->getType() == eTaikoType_1_Long&&nType == eTaikoType_1)
	{
		bType = true;
	}else if (pCell->getType() == eTaikoType_2_Long&&nType == eTaikoType_2)
	{
		bType = true;
	}else if(pCell->getType() == nType)
	{
		bType = true;
	}
	//碌鈥灺溾墺鈥ο€露
	if (pCell->getType() != eTaikoType_Invalid && bType)
	{
		//CCRect rc1(mpSp->getPositionX(),mpSp->getPositionY(),mRcTarget->getContentSize().width,mRcTarget->getContentSize().height);
		ETaikoOperateState eOpState = ETaikoOpMiss;
		if(mRcTargetPrefect.containsPoint(ccp(pCell->getCollisionArea().getMidX(),pCell->getCollisionArea().getMinY()))){
			eOpState = ETaikoOpPerfect;
		}else if(mRcTargetGreen.containsPoint(ccp(pCell->getCollisionArea().getMidX(),pCell->getCollisionArea().getMinY()))){
			eOpState = ETaikoOpGreen;
		}
		if (eOpState != ETaikoOpMiss)
		{
			pCell->setOpState(eOpState);
			
			CTaikoGameEffectPrefect* p = (CTaikoGameEffectPrefect*)CTKData.getEffect(eTaikoGameEffectPrefect);
			if (p&&p->mbPerfectState&&p->mnUseTimes > 0)
			{
				pCell->setOpState(ETaikoOpPerfect);
				CCLOG("CTaikoGameEffectPrefect::mnUseTimes = %d",p->mnUseTimes);
			}
			
			if (pCell->getType() == eTaikoType_1_Long||pCell->getType() == eTaikoType_2_Long)
			{
				mbClickCellLong = true;
				mptSplit = ccp(0,pCell->getCollisionArea().getMinY());
				CTaskManProceDt(eDayTaskTypeTK_52,1);
				return;
			}

			//日常任务判断
			if (meCurrentHitType == eTaikoNone)
			{
				 meCurrentHitType = pCell->getType();
				 meLastHitType = meCurrentHitType;
			}else
			{
				meCurrentHitType = pCell->getType();
			}
			if (meLastHitType == eTaikoType_1||meLastHitType == eTaikoType_1_Long)
			{
				if (meCurrentHitType != eTaikoType_1 && meCurrentHitType != eTaikoType_1_Long)
					mbSaveTask57Score = false;
			}else
			{
				if (meCurrentHitType != eTaikoType_2 && meCurrentHitType == eTaikoType_2_Long)
					mbSaveTask57Score = false;
			}
			
			_calc(pCell);
			//鈥γ︹墺藵
			_executeDel();
		}else
		{
			opErr(pCell);
		}
	}
	//碌鈥灺溌犆熲垶鈥?
	else
	{
		opErr(pCell);
	}
}
void CTaikoScene::opErr(CTaikoCell* pCell,bool bDel)
{
	if (!CItemMan::sharedInstance().useItem(ItemTag_14) && !useItem(eTaikoPayEffectSkipErr)){
		if (pCell && (pCell->getOpState() == ETaikoOpProtect))
			return;
		if (pCell && pCell->isClickLongCell())
		{
			return ;
		}
		if(pCell && bDel)
		{
			pCell->setOpState(ETaikoOpMiss);
			//pCell->executeDel(true);
		}
		CTaskManProceDt(eDayTaskTypeShare_12,1);
        CTaskManProce(eDayTaskTypeTK_56, 0);
		pCell->toGray();
		CTKData.setContinueNum(0);
		CTKData.setCrazyContinueNum(0);
		processItem(eTaikoGameEffectScore,0);
		//processItem(eTaikoGameEffectShakeDrum,0);
		processItem(eTaikoGameEffectPrefect,0);
		Crazy_End();
		if(mpOpState == NULL)
			return;
		//mpOpState->setDisplayFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName("tai_ko/miss.png"));
		//mpOpState->setTexture(CCTexAddImage("CocoStudioResources/tai_ko/miss.png"));
		NumSprite::setSpriteTexture(mpOpState,CCTexAddImage("CocoStudioResources/tai_ko/miss.png"));
		CCFiniteTimeAction*  pAction = CCSequence::create(
			CCShow::create(),
			CCFadeOut::create(0.5f),
			CCHide::create(),
			NULL);
		mpOpState->runAction(pAction);
	}else
	{
		if (pCell)
		{
			pCell->setOpState(ETaikoOpProtect);
			CEffectActionHelper::play(eHelpShield,pCell);
		}
	}
	_updataASpeed();
}
void CTaikoScene::callFuncDrumL()
{
	((CGameLayerTaiko*)this->getChildByTag(CGameLayerTaiko::getDialogIDD()))->getWidgetByName("cyc_big_drum_ef_l")->setVisible(true);
}
void CTaikoScene::callFuncDrumLHide()
{
	((CGameLayerTaiko*)this->getChildByTag(CGameLayerTaiko::getDialogIDD()))->getWidgetByName("cyc_big_drum_ef_l")->setVisible(false);
}
void CTaikoScene::callFuncDrumR()
{
	((CGameLayerTaiko*)this->getChildByTag(CGameLayerTaiko::getDialogIDD()))->getWidgetByName("cyc_big_drum_ef_r")->setVisible(true);
}
void CTaikoScene::callFuncDrumRHide()
{
	((CGameLayerTaiko*)this->getChildByTag(CGameLayerTaiko::getDialogIDD()))->getWidgetByName("cyc_big_drum_ef_r")->setVisible(false);
}
void  CTaikoScene::clickBtnPushDown0()
{
	clickBtnType(eTaikoType_1);
}
void  CTaikoScene::clickBtnCancel0()
{
	mbClickCellLong = false;
}
void CTaikoScene::clickBtnPushDown1()
{
	clickBtnType(eTaikoType_2);
}
void CTaikoScene::clickBtnCancel1()
{
	mbClickCellLong = false;
}
bool CTaikoScene::clickBtnDrum(int nType)
{
	CCFiniteTimeAction*  pAction = NULL;
	CGameLayerTaiko* pLayer = ((CGameLayerTaiko*)this->getChildByTag(CGameLayerTaiko::getDialogIDD()));
	UIWidget* pUI = pLayer->getWidgetByName("BtnIn");
	if (pUI->isVisible()/*&&pLayer->getWidgetByName("cyc_big_drum_r")->getRenderer()->numberOfRunningActions()<=0*/)
	{
		if (nType == eTaikoType_1)
		{
			pUI = pLayer->getWidgetByName("cyc_big_drum_r");
			pUI->setRotation(20.f);
			pUI->stopAllActions();
			CCActionInterval* pActRo = CCRotateBy::create(0.1f,-20.f);
			
			CCString str;
			pAction = CCSequence::create(
				CCShow::create(),
				pActRo,
				CCCallFunc::create(this,callfunc_selector(CTaikoScene::callFuncDrumR)),
				pActRo->reverse(),
				CCCallFunc::create(this,callfunc_selector(CTaikoScene::callFuncDrumRHide)),
				NULL);
			pAction->setTag(eTaikoCellActDrumRod);
			pUI->runAction(pAction);
		}
		else if (nType == eTaikoType_2)
		{
			pUI = pLayer->getWidgetByName("cyc_big_drum_l_0");
			pUI->setRotation(-20.f);
			pUI->stopAllActions();
			CCActionInterval* pActRo = CCRotateBy::create(0.1f,20.f);
			
			CCString str;
			pAction = CCSequence::create(
				CCShow::create(),
				pActRo,
				CCCallFunc::create(this,callfunc_selector(CTaikoScene::callFuncDrumL)),
				pActRo->reverse(),
				CCCallFunc::create(this,callfunc_selector(CTaikoScene::callFuncDrumLHide)),
				NULL);
			pUI->runAction(pAction);
		}
		pUI = pLayer->getWidgetByName("BtnIn");
		pUI->stopAllActions();
		pUI->setScale(1.f);
		CCActionInterval* pActScale = CCScaleBy::create(0.1f,1.1f);
		CCActionInterval* pActScale1 = pActScale->reverse();
		pUI->runAction(CCSequence::create(pActScale,pActScale1,NULL));
		CTaskManProceDt(eDayTaskTypeTK_54,1);
	}else
	{
		
		return false;
		
	}
		
	//CCLOG("clickBtnDrum");
	CTaikoGameEffectShakeDrum* pSD = (CTaikoGameEffectShakeDrum*)CTKData.getEffect(eTaikoGameEffectShakeDrum);
	if(pSD->mbClickValid)
		_calcBrumScore();
	return true;
}
void CTaikoScene::_calcBrumScore()
{
	//震鼓加成
	float fScore = 2000; 
	float fAddScore = fScore;
	if (useItem(eTaikointensifyShakeDrum))
	{
		CTaikointensifyShakeDrum* pT = (CTaikointensifyShakeDrum*)CTKData.getEffect(eTaikointensifyShakeDrum);
		fAddScore *= pT->mfEffectVal;
	}
	fScore += fAddScore;
	CTKData.alterScore(fScore);
	setScore(CTKData.getScore());
}
// void CTaikoScene::_calcLongScore(CTaikoCell* pCell)
// {
// 	float fScore = KAIKO_CELL_BASE_SCORE;
// 	CTKData.alterScore(fScore);
// 	setScore(CTKData.getScore());
// }
void CTaikoScene::_executeDel()
{
	if (mVecCellOp.size() == 1)
	{
		_executeOpStateEff(mVecCellOp[0]);
	}
	for (int i =0; i < mVecCellOp.size(); ++i){
		CTaikoCell* p = mVecCellOp[i];
		p->executeDel();
	}
	mpDrumEff->stopAllActions();
	CCAnimation* pAni = CCAnimation::create();
	CCString str;
	for (int i = 1; i <= 5; ++i){
		str.initWithFormat("tai_ko/drum_eff/%d.png",i);
		pAni->addSpriteFrameWithFileName(str.getCString());
	}
	pAni->setDelayPerUnit(0.5/5.f);
	pAni->setLoops(1);
	CCFiniteTimeAction*  pAction = CCSequence::create(
		CCShow::create(),
		CCAnimate::create(pAni),
		CCHide::create(),
		NULL);
	mpDrumEff->runAction(pAction);
}
void CTaikoScene::_executeOpStateEff(CTaikoCell* pCell)
{
	mpOpState->stopAllActions();
	if (pCell->getOpState() == ETaikoOpGreen)
	{
		//mpOpState->setDisplayFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName("tai_ko/great.png"));
		//mpOpState->setTexture(CCTexAddImage("CocoStudioResources/tai_ko/great.png"));
		NumSprite::setSpriteTexture(mpOpState,CCTexAddImage("CocoStudioResources/tai_ko/great.png"));
		CTaskManProceDt(eDayTaskTypeTK_49,1);
		mnCounterGreatHitTimes++;
	}else if (pCell->getOpState() == ETaikoOpPerfect)
	{
		CTaskManProceDt(eDayTaskTypeTK_50,1);
        CTaskManProceDt(eDayTaskTypeTK_56, 1);
		//mpOpState->setDisplayFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName("tai_ko/perfect.png"));
		//mpOpState->setTexture(CCTexAddImage("CocoStudioResources/tai_ko/perfect.png"));
		NumSprite::setSpriteTexture(mpOpState,CCTexAddImage("CocoStudioResources/tai_ko/perfect.png"));
		mnCounterPerfectHitTimes++;
	}else 
	{
		//mpOpState->setDisplayFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName("tai_ko/miss.png"));
		//mpOpState->setTexture(CCTexAddImage("CocoStudioResources/tai_ko/miss.png"));
		NumSprite::setSpriteTexture(mpOpState,CCTexAddImage("CocoStudioResources/tai_ko/miss.png"));
	}
	CCFiniteTimeAction*  pAction = CCSequence::create(
		CCShow::create(),
		CCFadeOut::create(0.5f),
		CCHide::create(),
		NULL);
	mpOpState->runAction(pAction);
}
void CTaikoScene::_updataGenInterval()
{
    float fGenCellInterval = 0.75f;
	if (CTKData.getContinueNum() >= 150)
	{
		fGenCellInterval = 0.2f;
	}else if (CTKData.getContinueNum() >= 100)
	{
		fGenCellInterval = 0.25f;
	}else if (CTKData.getContinueNum() >= 80)
	{
		fGenCellInterval = 0.3f;
	}else if (CTKData.getContinueNum() >= 50)
	{
		fGenCellInterval = 0.375f;
	}else if (CTKData.getContinueNum() >= 30)
	{
		fGenCellInterval = 0.4f;
	}else if (CTKData.getContinueNum() >= 20)
	{
		fGenCellInterval = 0.5f;
	}else if (CTKData.getContinueNum() >= 10) {
        fGenCellInterval = 0.625f;
    } 
	if (useItem(eTaikoPayEffectAddSpeed))
	{
		if (mfGenCellInterval > 0.f && fGenCellInterval > mfGenCellInterval)
			fGenCellInterval = mfGenCellInterval;
	}
	mfGenCellInterval = fGenCellInterval;
}
void CTaikoScene::_executeASpeed(float fASpeed)
{
    for (int i = 0; i < mVecCellValid.size(); ++i) {
        mVecCellValid[i]->setASpeed(fASpeed);
        mVecCellValid[i]->executeASpeed();
    }
}
void CTaikoScene::_setCrazyMode(bool bImmediately)
{
	CTKData.updataMode();
	if(bImmediately)
	{
		if (CTKData.getMode() == eSuperCrazyMode){
			//鐜板湪鍙傛暟鏃犵敤
			Crazy_Start(10.f,eSuperCrazyMode);
		}
	}else{
		if (CTKData.getMode() == eComCrazyMode){
			if (CTKData.getContinueNum() == TAIKO_COM_MODE_CONTINUE_NEED_TIMES){
				//鐜板湪鍙傛暟鏃犵敤
				Crazy_Start(10.f,eComCrazyMode);
			}
		}else if (CTKData.getMode() == eSuperCrazyMode)
		{
			if (CTKData.getContinueNum() == TAIKO_SUPER_MODE_CONTINUE_NEED_TIMES)
			{
				Crazy_Start(10.f,eSuperCrazyMode);
			}
		}
	}
    Crazy_ReStart();
}
void CTaikoScene::_calc(CTaikoCell* pCell)
{
	mVecCellOp.clear();
	mVecCellOp.push_back(pCell);
	//隆篓陋藴鈥γ嬅封垰
	CTKData.alterContinueNum(1);
	_calcOpNum(pCell);
	//处理道具
	processItem(eTaikoGameEffectScore);
	processItem(eTaikoGameEffectShakeDrum);
	processItem(eTaikoGameEffectPrefect);
	
	//鈭懨仿犓澛衡垎脌鈥?
	_calcScore();
	//鈮堚墵鈭喡仿?
	_calcBoom();
	//鈭徛糕€撀?
	boom_setEnergy(CTKData.getAnger());
	setScore(CTKData.getScore());
    
	if(CTKData.getContinueNum() > 0)
		setBatter(CTKData.getContinueNum());

	CTaskManProce(eDayTaskTypeShare_1,CTKData.getScore());
	CTaskManProceDt(eDayTaskTypeShare_4,1);
	CTaskManProce(eDayTaskTypeShare_7,CTKData.getContinueNum());

    //更新速度
    _updataASpeed();

    //璁剧疆鐤媯妯″紡
    _setCrazyMode();
	//聽蟺鈥濃垰鈥撁熛€藲
	for (int i = 0; i < mVecCellOp.size(); ++i)
	{
		mVecCellOp[i]->executeEffect();
	}

	//鈥γ︹墺藵鈥撁熛€藲
	for (int i = 0; i < mVecCellOp.size(); ++i)
	{
		//记录消除不能点击图形的个数
		if (mVecCellOp[i]->getType() == eTaikoType_Invalid)
		{
			CTKData.setInvaildCellHitTimes(CTKData.getInvaildCellHitTimes() + 1);
		}
		mVecCellOp[i]->delEffect();
	}
	CAudioHelper::playSound(eSoundTypeTaikoClick);
}
void CTaikoScene::_updataASpeed()
{
	//璁剧疆鍔犻€?
	float fASpeed = 1.f;
	if (CTKData.getContinueNum() >= 150)
	{
		fASpeed = mfStartSpeed / 1.f;
	}else if (CTKData.getContinueNum() >= 100)
	{
		fASpeed = mfStartSpeed / 1.f;
	}else if (CTKData.getContinueNum() >= 80)
	{
		fASpeed = mfStartSpeed / 1.5f;

	}else if (CTKData.getContinueNum() >= 50)
	{
		fASpeed = mfStartSpeed / 1.5f;
	}else if (CTKData.getContinueNum() >= 30)
	{
		fASpeed = mfStartSpeed / 2.f;
	}else if (CTKData.getContinueNum() >= 20)
	{
		fASpeed = mfStartSpeed / 2.f;
	}else if (CTKData.getContinueNum() >= 10) {
		fASpeed = mfStartSpeed / 2.5f;
	}else
		fASpeed = 1.f;
	if (useItem(eTaikoPayEffectAddSpeed))
	{
		if(fASpeed < mfASpeed)
			fASpeed = mfASpeed;
	}
	mfASpeed = fASpeed;
	_executeASpeed(mfASpeed);
}
void CTaikoScene::_calcOpNum(CTaikoCell* pCell)
{
	ETaikoEffect nEffType = pCell->getEffect();
	CTaikoCellEffect* pEffect = pCell->getFrontEffect();
	if(pEffect&&pEffect->mbInvalid)
		return;
	switch(nEffType){
	case eTaikoEffectBomb:{
			for (int i = 0; i < mVecCellValid.size(); ++i){
				if(isContainOpVec(mVecCellValid[i]))
					continue;
				if(mVecCellValid[i]->getType() == eTaikoType_BigDrum)
					continue;
				mVecCellOp.push_back(mVecCellValid[i]);
				if(mVecCellValid[i]->getType() == eTaikoType_Invalid)
					CTaskManProceDt(eDayTaskTypeTK_60,1);
			}
		}
		break;
	}
}
void CTaikoScene::delCell(CTaikoCell* pCell,bool bCleanup)
{
	for (int i = 0; i < mVecCellValid.size(); ++i){
		if (mVecCellValid[i] == pCell){
			if(bCleanup){
				removeChild(pCell);
			}else{
				//pCell->setVisible(false);
				//pCell->reset();
				mVecCellInvalid.push_back(pCell);
			}
			mVecCellValid.erase(mVecCellValid.begin() + i);
		}
	}
}
bool CTaikoScene::useItem(ETaikoEffectType eType)
{
	CTaikoBaseEffect* pBaseEffect = CTKData.getEffect(eType);
	if (pBaseEffect == NULL)
		return false;
	switch(eType){
	case eTaikoGameEffectScore:{
			CTaikoGameEffectScore* p = (CTaikoGameEffectScore*)pBaseEffect;
			if (p->mnCounter >= p->mnLimitNum){
				p->mnCounter = 0;
			}else
				return false;
		}
		break;
	case eTaikoGameEffectPrefect:
		{
			CTaikoGameEffectPrefect* p = ((CTaikoGameEffectPrefect*)pBaseEffect);
			if (p->mnCounter >= p->mnLimitNum){
				p->mnCounter = 0;
			}else
				return false;
		}
		break;
	case eTaikoGameEffectShakeDrum:
		{
			CTaikoGameEffectShakeDrum* pS = (CTaikoGameEffectShakeDrum*)pBaseEffect;
			if (pS->mnCounter >= pS->mnLimitNum){
				pS->mbGening = true;
			}else
				return false;
		}
		break;
	case eTaikoPayEffectTimeDelay:{
			time_addSecond(5.0);
			CTKData.delEffect(eTaikoPayEffectTimeDelay);
			CTaskManProceDt(eDayTaskTypeShare_10,1);	
		}
		break;
	case eTaikoPayEffectSkipErr:{
			CTKData.delEffect(eTaikoPayEffectSkipErr);
			CTaskManProceDt(eDayTaskTypeShare_10,1);
		}
		break;
	case eTaikoPayEffectABlow:{
			CTKData.addEffect(new CTaikoGameEffectPrefect);
			CTaskManProceDt(eDayTaskTypeShare_10,1);
		}
		break;
	case eTaikoIntensifyAddScore:
		{
			CTaikoIntensifyAddScore* p = ((CTaikoIntensifyAddScore*)pBaseEffect);
			if (CRandomUtil::RandomRange(1,RAND_GAME_BASE_VAL) <= p->mfEffectVal)
				return true;
			return false;
		}
		break;
	case eTaikoIntensifyGenLongCell:
		{
// 			CTaikoIntensifyGenLongCell* p = ((CTaikoIntensifyGenLongCell*)pBaseEffect);
// 			if (CRandomUtil::RandomRange(1,RAND_GAME_BASE_VAL) <= p->mnEffectVal)
// 				return true;
// 			return false;
		}
		break;
	case eTaikointensifyShakeDrum:
		{

		}
		break;
	
	}
	return true;
}
bool CTaikoScene::processItem(ETaikoEffectType eType)
{
	CTaikoBaseEffect* pBaseEffect = CTKData.getEffect(eType);
	if (pBaseEffect == NULL)
		return false;
	switch(eType){
	case eTaikoGameEffectScore:
		{
			CTaikoGameEffectScore* p = (CTaikoGameEffectScore*)pBaseEffect;
			p->mnCounter += 1;
		}
		break;
	case eTaikoGameEffectShakeDrum:
		{
			CTaikoGameEffectShakeDrum* p = (CTaikoGameEffectShakeDrum*)pBaseEffect;
			p->mnCounter += 1;
		}
		break;
	case eTaikoGameEffectPrefect:
		{
			CTaikoGameEffectPrefect* p = (CTaikoGameEffectPrefect*)pBaseEffect;
			p->mnCounter += 1;
		}
		break;
	}
	return true;
}
bool CTaikoScene::processItem(ETaikoEffectType eType,int nVal)
{
	CTaikoBaseEffect* pBaseEffect = CTKData.getEffect(eType);
	if (pBaseEffect == NULL)
		return false;
	switch(eType){
	case eTaikoGameEffectScore:{
			CTaikoGameEffectScore* p = (CTaikoGameEffectScore*)pBaseEffect;
			p->mnCounter = nVal;
		}
		break;
	case eTaikoGameEffectShakeDrum:{
			CTaikoGameEffectShakeDrum* p = (CTaikoGameEffectShakeDrum*)pBaseEffect;
			p->mnCounter = nVal;
		}
		break;
	case eTaikoGameEffectPrefect:{
			CTaikoGameEffectPrefect* p = (CTaikoGameEffectPrefect*)pBaseEffect;
			p->mnCounter = nVal;
		}
		break;
	}
	return true;
}
bool CTaikoScene::isContainOpVec(CTaikoCell* pValidCell){
	for(int i = 0; i < mVecCellOp.size(); ++i){
		if (mVecCellOp[i] == pValidCell){
			return true;
		}
	}
	return false;
}
void CTaikoScene::_calcScore()
{
	int nScore = 0;
	//隆篓陋藴潞鈥濃墺鈥?
	int nContinueAddVal = CTKData.getContinueNum() * KAIKO_SCORE_FACTOR;
	int nCellBaseScore = KAIKO_CELL_BASE_SCORE;
	int nCellInvalidBaseScore = KAIKO_INVAIL_CELL_BASE_SCORE;
	int nCrazyFactor = 1;
	for (int i = 0; i < mVecCellOp.size(); ++i){
		CTaikoCell* p = mVecCellOp[i];
		if(p->getEffect() == eTaikoEffectIntensifyAddScore)
		{
			nCellInvalidBaseScore *= 2;
			nCellBaseScore *= 2;
			CTaskManProceDt(eDayTaskTypeTK_51,1);
		}
			
		if (p->getType() == eTaikoType_Invalid){
			nScore += nCellInvalidBaseScore;
		}else{
			nScore += nCellBaseScore;
		}
		if (p->getOpState() == ETaikoOpGreen){
			nScore = (nContinueAddVal + nScore) * CTKData.getCrazyAdd();
		}else if(p->getOpState() == ETaikoOpPerfect){
			nScore = (nContinueAddVal + nScore) * CTKData.getCrazyAdd() * 2;
		}
		
		//付费道具分数加成
		if (p->getEffect() == eTaikoEffectScore){
			nScore += 20000;
		}
	}
	
	CTKData.alterScore(nScore);
}

void CTaikoScene::_calcBoom(){
	int nBoom = 0;
	for (int i = 0; i < mVecCellOp.size(); ++i){
		CTaikoCell* p = mVecCellOp[i];
		if(p->getOpState() == ETaikoOpGreen)
			nBoom += 1;
		else if (p->getOpState() == ETaikoOpPerfect)
			nBoom += 3;
	}
	CTKData.alterAnger(nBoom);
}