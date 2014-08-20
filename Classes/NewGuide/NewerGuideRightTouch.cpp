

#include "SpriteFrameManage.h"
#include "RTItem.h"
#include "GameShare_Global.h"
#include "GameShare_Scene.h"
#include "NewerGuideRightTouch.h"

 CNewerGuideRihgtTouch::CNewerGuideRihgtTouch()
 {

 }
 CNewerGuideRihgtTouch::~CNewerGuideRihgtTouch()
 {

 }

 void CNewerGuideRihgtTouch::onEnter()
 {
	 CCNode::onEnter();
	 // CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	 play();
	
 }
 void CNewerGuideRihgtTouch::onExit()
 {
	 CCNode::onExit();
	// CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
 }
 void CNewerGuideRihgtTouch::play()
 {
	 CCSize sz = CCDirector::sharedDirector()->getWinSize();
	 CCSprite* pFinger = CCSprite::create("CocoStudioResources/layoutNewerGuide/finger.png") ;
	 pFinger->setAnchorPoint(ccp(0.f,1.f));
	 pFinger->setFlipY(false);
	 int nCounter = 0;
	for (int y = 0 ; y < 3; ++y)
	{
		for (int x = 0; x < 3;++x)
		{
			CRTItem* pItem = CRTItem::create();
			pItem->setType(1);
			pItem->setState(eRTItemState1);
			if( nCounter == 0|| nCounter==1)
				pItem->setType(2);
			if(nCounter == 2)
			{
				pItem->setType(2);
				pItem->setState(eRTItemState2);
			}
			if(nCounter == 8)
			{
				pItem->setType(3);
				pItem->setState(eRTItemState2);
			}
			pItem->updataCell();
			addChild(pItem,10);
			CCPoint ptOffect = ccp(sz.width/2 - (3 * pItem->getSprite()->getContentSize().width)/2 + pItem->getSprite()->getContentSize().width/2,
				sz.height/2 + (3 * pItem->getSprite()->getContentSize().height)/2);
		// ptOffect = ccp(0,0);
			pItem->setPosition(ccp(ptOffect.x + x * pItem->getSprite()->getContentSize().width,  ptOffect.y - y * pItem->getSprite()->getContentSize().height));
		mVecCell.push_back(pItem);
		nCounter++;
		}
	}
	addChild(pFinger,10); 
	CCActionInterval* pAct = CCSequence::create(CCShow::create(),CCPlace::create(ccp(mVecCell[0]->getPositionX(),mVecCell[0]->getPositionY() + 15 )),CCDelayTime::create(0.5f),
	CCMoveBy::create(0.1f,ccp(0,15)),CCMoveBy::create(0.1f,ccp(0,-15)),
		CCMoveTo::create(1.f,ccp(mVecCell[1]->getPositionX(),mVecCell[1]->getPositionY() )),
		CCMoveBy::create(0.1f,ccp(0,15)),CCMoveBy::create(0.1f,ccp(0,-15)),
		CCCallFuncND::create(this, callfuncND_selector(CNewerGuideRihgtTouch::rtActCallfunc), (void*)"1"),
		CCDelayTime::create(1.f),
	CCMoveBy::create(0.1f,ccp(0,15)),CCMoveBy::create(0.1f,ccp(0,-15)),
		CCMoveTo::create(1.f,ccp(mVecCell[2]->getPositionX(),mVecCell[2]->getPositionY())),
		CCMoveBy::create(0.1f,ccp(0,15)),CCMoveBy::create(0.1f,ccp(0,-15)),
		CCCallFuncND::create(this, callfuncND_selector(CNewerGuideRihgtTouch::rtActCallfunc), (void*)"2"),
		CCDelayTime::create(1.f),
		CCCallFuncND::create(this, callfuncND_selector(CNewerGuideRihgtTouch::rtActCallfunc), (void*)"3"),
		NULL);
	pFinger->runAction(CCRepeatForever::create(pAct)); 

 }
 CCActionInterval* CNewerGuideRihgtTouch::actClick()
 {
	 return  CCMoveBy::create(0.1f,ccp(0,15)),CCMoveBy::create(0.1f,ccp(0,-15));
 }
 void CNewerGuideRihgtTouch::rtActCallfunc(CCNode* sender, void* data)
 {
 	 CCString str = (char*)(data);
 	 if(str.compare("1") == 0){
		  mVecCell[0]->setVisible(true);
		  ((CRTItem*)mVecCell[0])->setType(4);
		  ((CRTItem*)mVecCell[0])->updataCell();
		  CRTItem* pCell = (CRTItem*)mVecCell[1];
		  CCAnimation* pAni = CCAnimation::create();
		   	 CCString str;
		   	 str.initWithFormat("cell%d_%d.png",pCell->getType(),1);
		   	 pAni->addSpriteFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName(str.getCString()));
		   	 str.initWithFormat("cell%d_%d.png",pCell->getType(),12);
		   	 pAni->addSpriteFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName(str.getCString()));
		   	 str.initWithFormat("cell%d_%d.png",pCell->getType(),2);
		   	 pAni->addSpriteFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName(str.getCString()));
		   	 pAni->setDelayPerUnit(0.3/3.f);
		   	 pAni->setLoops(1);
		pCell->getSprite()->runAction(CCAnimate::create(pAni));
	 }else if (str.compare("2") == 0)
	 {
		 CCAnimation* pAni = CCAnimation::create();
		 CCString str;
		 for (int i = 1; i <= 5; ++i){
			 str.initWithFormat("effect/bomb/%d.png",i);
			 pAni->addSpriteFrameWithFileName(str.getCString());
		 }
		 pAni->setDelayPerUnit(0.5f/5.f);
		 pAni->setLoops(1);
		 CCActionInterval*  pAction = CCSequence::create(
			 CCAnimate::create(pAni),
			 NULL);
		 ((CRTItem*)mVecCell[1])->getSprite()->runAction(pAction);

		 pAni = CCAnimation::create();

		 for (int i = 1; i <= 5; ++i){
			 str.initWithFormat("effect/bomb/%d.png",i);
			 pAni->addSpriteFrameWithFileName(str.getCString());
		 }
		 pAni->setDelayPerUnit(0.5f/5.f);
		 pAni->setLoops(1);
		  pAction = CCSequence::create(
			 CCAnimate::create(pAni),
			 NULL);
		 ((CRTItem*)mVecCell[2])->getSprite()->runAction(pAction);
	 }else if (str.compare("3") == 0){
		 int nCounter = 0;
		 for (int y = 0 ; y < 3; ++y){
			 for (int x = 0; x < 3;++x){
				 CRTItem* pItem = (CRTItem*)mVecCell[nCounter];
				 pItem->getSprite()->setVisible(true);
				 if( nCounter == 0|| nCounter==1)
					 pItem->setType(2);
				 if(nCounter == 2)
				 {
					 pItem->setType(2);
					 pItem->setState(eRTItemState2);
				 }
				 if(nCounter == 8)
				 {
					 pItem->setType(3);
					 pItem->setState(eRTItemState2);
				 }
				 pItem->updataCell();
				 nCounter++;
			 }
		 }
	 }
 }