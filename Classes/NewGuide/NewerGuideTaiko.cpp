

#include "SpriteFrameManage.h"
#include "GameShare_Global.h"
#include "GameShare_Scene.h"
#include "GameFruitScene.h"
#include "NewerGuideFruit.h"
#include "StringUtil.h"
#include "NewerGuideTaiko.h"
#include "TaikoDefine.h"
#include "ComData.h"
#include "NumSprite.h"
 CNewerGuideTaiko::CNewerGuideTaiko()
 {

 }
 CNewerGuideTaiko::~CNewerGuideTaiko()
 {

 }

 void CNewerGuideTaiko::onEnter()
 {
	 CCNode::onEnter();
	 // CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	 play();
	
 }
 void CNewerGuideTaiko::onExit()
 {
	 CCNode::onExit();
	// CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
 }
 void CNewerGuideTaiko::play()
 {
	 CCSize sz = CCDirector::sharedDirector()->getWinSize();
	 mpFinger = CCSprite::create("CocoStudioResources/layoutNewerGuide/finger.png") ;
	 mpFinger->setAnchorPoint(ccp(0.f,0.8f));
	 mpFinger->setFlipY(false);
	 addChild(mpFinger,11); 
	 int nType = 1;
	 int nCounter = 0;
	 CCSprite* pItem = CCSprite::create();
	 CCString strFileName;
	 strFileName.initWithFormat("CocoStudioResources/tai_ko/cell_%d.png",eTaikoType_1);
	//pItem->setDisplayFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName(strFileName.getCString()));
	// pItem->setTexture(CCTexAddImage(strFileName.getCString()));
	 NumSprite::setSpriteTexture(pItem,CCTexAddImage(strFileName.getCString()));
	addChild(pItem,10);
	
	CCPoint ptStart = ccp( sz.width/2, sz.height - 200 - 162);
	CCPoint ptTarget = ccp( sz.width/2, 293);
	pItem->setPosition(ptStart);
	mVecCell.push_back(pItem);
	strFileName.initWithFormat("CocoStudioResources/tai_ko/cell_%d.png",eTaikoType_2);
	mpL = CCSprite::create(strFileName.getCString());
	strFileName.initWithFormat("CocoStudioResources/tai_ko/cell_%d.png",eTaikoType_1);
	mpR = CCSprite::create(strFileName.getCString());
	strFileName.initWithFormat("CocoStudioResources/tai_ko/cyc_in.png");
	mpM = CCSprite::create(strFileName.getCString());
	strFileName.initWithFormat("CocoStudioResources/tai_ko/cyc_big_drum_r.png");
	mpML = CCSprite::create(strFileName.getCString());
	mpML->setFlipX(true);mpML->setAnchorPoint(ccp(0.f,0.f));
	strFileName.initWithFormat("CocoStudioResources/tai_ko/cyc_big_drum_r.png");
	mpMR = CCSprite::create(strFileName.getCString());
	mpMR->setAnchorPoint(ccp(1.f,0.f));
	mpM->setPosition(ptTarget);
	mpML->setPosition(ccp(ptTarget.x - 60 - 119,ptTarget.y - mpML->getContentSize().height/2 - 75));
	mpMR->setPosition(ccp(ptTarget.x + 60 + 119 ,ptTarget.y - mpML->getContentSize().height/2 - 75));
	mpL->setPosition(ccp(ptTarget.x - 200,ptTarget.y));
	mpR->setPosition(ccp(ptTarget.x + 200,ptTarget.y));
	mpML->setVisible(false);
	mpMR->setVisible(false);
	addChild(mpM,9);
	addChild(mpL,10);
	addChild(mpR,10);
	addChild(mpML,10);
	addChild(mpMR,10);
	
	mVecCell[0]->setScale(0.2f);	
	CCActionInterval* pAct = CCSequence::create(CCShow::create(),CCPlace::create(ptStart),CCDelayTime::create(0.5f),
		CCSpawn::create(CCMoveTo::create(2.f,ptTarget),CCScaleTo::create(2.f,1.f),NULL),
		CCCallFuncND::create(this, callfuncND_selector(CNewerGuideTaiko::actCallfunc), (void*)"99"),CCDelayTime::create(2.f),
		CCCallFuncND::create(this, callfuncND_selector(CNewerGuideTaiko::actCallfunc), (void*)"97"),
		//大鼓
		CCPlace::create(ptStart),CCDelayTime::create(0.5f),
		CCSpawn::create(CCMoveTo::create(2.f,ccp(ptTarget.x,ptTarget.y + mpM->getContentSize().height/2) ),CCScaleTo::create(2.f,1.f),NULL),CCHide::create(),
		CCCallFuncND::create(this, callfuncND_selector(CNewerGuideTaiko::actCallfunc), (void*)"96"),CCDelayTime::create(1.f),
		CCCallFuncND::create(this, callfuncND_selector(CNewerGuideTaiko::actCallfunc), (void*)"98"),
		//CCCallFuncND::create(this, callfuncND_selector(CNewerGuideTaiko::actCallfunc), (void*)"98"),
		NULL);
	mVecCell[0]->runAction(CCRepeatForever::create(pAct)); 

 }
 CCActionInterval* CNewerGuideTaiko::actClick()
 {
	 return  CCMoveBy::create(0.2f,ccp(0,15)),CCMoveBy::create(0.2f,ccp(0,-15));
 }

 void CNewerGuideTaiko::actCallfunc(CCNode* sender, void* data)
 {
	 CCString str = (char*)data;
	 if (str.compare("99") == 0)//消除-炸弹特效
	 {
		CCActionInterval*  pAction = CCSequence::create(CCShow::create(),CCPlace::create(mpR->getPosition()),
			 actClick(),/*CCHide::create(),*/
			 NULL);
		 mpFinger->runAction(pAction);
		 CCSprite* spMEff = CCSprite::create();
			 CCAnimation* pAni = CCAnimation::create();
			 CCString str;
			 for (int i = 1; i <= 5; ++i){
				 str.initWithFormat("effect/bomb/%d.png",i);
				 pAni->addSpriteFrameWithFileName(str.getCString());
			 }
			 pAni->setDelayPerUnit(0.5f/5.f);
			 pAni->setLoops(1);

			 pAction = CCSequence::create(CCShow::create(),CCDelayTime::create(0.5f),
				 CCAnimate::create(pAni),CCHide::create(),
				 NULL);
			 mVecCell[0]->runAction(pAction);
			 //addChild(spMEff,11);
			// spMEff->setPosition(mpM->getPosition());
			 // mVecCell[0]->setVisible(false);
	 }else if (str.compare("97") == 0)//引导大鼓准备
	 {
		
		 mVecCell[0]->setScale(0.2f);
		 mVecCell[0]->setVisible(true);
		 mpFinger->setVisible(true);
		 mpFinger->setPosition(mpR->getPosition());
		 CCString strFileName;
		 strFileName.initWithFormat("CocoStudioResources/tai_ko/cell_%d.png",eTaikoType_BigDrum);
		 //mVecCell[0]->setDisplayFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName(strFileName.getCString()));
		// mVecCell[0]->setTexture(CCTexAddImage(strFileName.getCString()));
		 NumSprite::setSpriteTexture(mVecCell[0],CCTexAddImage(strFileName.getCString()));
		 mpL->setVisible(true);
		 mpR->setVisible(true);
		 strFileName.initWithFormat("CocoStudioResources/tai_ko/cyc_big_drum.png");
		// mpM->setTexture(CCTexAddImage(strFileName.getCString()));
		 NumSprite::setSpriteTexture(mpM,CCTexAddImage(strFileName.getCString()));
		 // mpM->setDisplayFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName(strFileName.getCString()));
		  //右边手
		  mpFinger->runAction(CCRepeatForever::create(CCSequence::create(CCMoveBy::create(0.1f,ccp(0,15)),CCMoveBy::create(0.1f,ccp(0,-15)),NULL)));
		  //左边手
		  CCSprite* pFingerL = CCSprite::create("CocoStudioResources/layoutNewerGuide/finger.png");
		  pFingerL->setTag(21);
		  addChild(pFingerL,20); 
		  pFingerL->setFlipX(true);
		  pFingerL->setAnchorPoint(ccp(1.f,1.f));
		  pFingerL->runAction(CCRepeatForever::create(CCSequence::create(CCMoveBy::create(0.1f,ccp(0,15)),CCMoveBy::create(0.1f,ccp(0,-15)),NULL)));
		  pFingerL->setPosition(mpL->getPosition());

		  mpML->setVisible(true);
		  mpMR->setVisible(true);

		  mpMR->setRotation(20.f);
		  mpMR->stopAllActions();
		  CCActionInterval* pActRo = CCRotateBy::create(0.1f,-20.f);
		 CCActionInterval* pAction = CCSequence::create(
			  CCShow::create(),
			  pActRo,
			  pActRo->reverse(),
			  NULL);
		  mpMR->runAction(CCRepeatForever::create( pAction));

		  mpML->setRotation(-20.f);
		  mpML->stopAllActions();
		  pActRo = CCRotateBy::create(0.1f,20.f);
		  pAction = CCSequence::create(
			  CCShow::create(),
			  pActRo,
			  pActRo->reverse(),
			  NULL);
		  mpML->runAction(CCRepeatForever::create( pAction));
	 }
	 else if (str.compare("98") == 0)//重置
	 {
		 //移除左边的手
		 removeChildByTag(21);

		 mpFinger->setVisible(false);
		 mpML->setVisible(false);
		 mpMR->setVisible(false);
		  mpML->stopAllActions();
		   mpMR->stopAllActions();
		 CCString strFileName;
		 strFileName.initWithFormat("CocoStudioResources/tai_ko/cyc_in.png");
		 //mpM = CCSprite::create(strFileName.getCString());
		 //mpM->setTexture(CCTexAddImage(strFileName.getCString()));
		  NumSprite::setSpriteTexture(mpM,CCTexAddImage(strFileName.getCString()));
		 mpL->setVisible(true);
		 mpR->setVisible(true);
		 mVecCell[0]->setScale(0.2f);
		 strFileName.initWithFormat("CocoStudioResources/tai_ko/cell_%d.png",eTaikoType_1);
		// mVecCell[0]->setDisplayFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName(strFileName.getCString()));
		 // mVecCell[0]->setTexture(CCTexAddImage(strFileName.getCString()));
		  NumSprite::setSpriteTexture(mVecCell[0],CCTexAddImage(strFileName.getCString()));
		 mpFinger->stopAllActions();
		 
	 }else if (str.compare("96") == 0)
	 {
// 		 CCActionInterval* pAction = CCSequence::create(CCShow::create(),CCPlace::create(mpM->getPosition()),
// 			 actClick(),CCHide::create(),
// 			 NULL);
// 		 mpFinger->runAction(pAction);
	 }
 }