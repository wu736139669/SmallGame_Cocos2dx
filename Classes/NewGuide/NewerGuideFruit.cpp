

#include "SpriteFrameManage.h"
#include "GameShare_Global.h"
#include "GameShare_Scene.h"
#include "GameFruitScene.h"
#include "NewerGuideFruit.h"
#include "StringUtil.h"
 CNewerGuideFruit::CNewerGuideFruit()
 {

 }
 CNewerGuideFruit::~CNewerGuideFruit()
 {

 }

 void CNewerGuideFruit::onEnter()
 {
	 CCNode::onEnter();
	 // CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	 play();
	
 }
 void CNewerGuideFruit::onExit()
 {
	 CCNode::onExit();
	// CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
 }
 void CNewerGuideFruit::play()
 {
	 CCSize sz = CCDirector::sharedDirector()->getWinSize();
	 CCSprite* pFinger = CCSprite::create("CocoStudioResources/layoutNewerGuide/finger.png") ;
	 pFinger->setAnchorPoint(ccp(0.f,1.f));
	 pFinger->setFlipY(false);
	 addChild(pFinger,11); 
	 int nType = 1;
	 int nCounter = 0;
	for (int y = 0 ; y < 3; ++y)
	{
		for (int x = 0; x < 3;++x)
		{
			CFruitGuide* pItem = CFruitGuide::create();
			CCString strFileName;
			nType = 1;
			if( nCounter == 0|| nCounter == 1)
				nType = 2;
			if(nCounter == 4)
				nType = 2;
			if(nType == 2)
				mVecCellPath.push_back(pItem);
			strFileName.initWithFormat("item/fruit%d.png",nType);
			pItem->pCell->setDisplayFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName(strFileName.getCString()));
			
			addChild(pItem,10);
			CCPoint ptOffect = ccp(sz.width/2 - (3 * pItem->pCell->getContentSize().width)/2 + pItem->pCell->getContentSize().width/2,
				sz.height/2 + (3 * pItem->pCell->getContentSize().height)/2);
		// ptOffect = ccp(0,0);
			pItem->setPosition(ccp(ptOffect.x + x * pItem->pCell->getContentSize().width,  ptOffect.y - y * pItem->pCell->getContentSize().height));
			mVecCell.push_back(pItem);
			nCounter++;
		}
	}
	
	CCActionInterval* pAct = CCSequence::create(CCShow::create(),CCPlace::create(ccp(mVecCellPath[0]->getPositionX(),mVecCellPath[0]->getPositionY() + 15 )),CCDelayTime::create(0.5f),
		CCMoveBy::create(0.1f,ccp(0,15)),CCMoveBy::create(0.1f,ccp(0,-15)),
		CCMoveTo::create(1.f,ccp(mVecCellPath[1]->getPositionX(),mVecCellPath[1]->getPositionY() )),
		CCCallFuncND::create(this, callfuncND_selector(CNewerGuideFruit::actAngleCallfunc), (void*)"0"),CCDelayTime::create(0.5f),
		CCMoveTo::create(1.f,ccp(mVecCellPath[2]->getPositionX(),mVecCellPath[2]->getPositionY() )),
		CCCallFuncND::create(this, callfuncND_selector(CNewerGuideFruit::actAngleCallfunc), (void*)"1"),CCDelayTime::create(0.5f),
		CCCallFuncND::create(this, callfuncND_selector(CNewerGuideFruit::actCallfunc), (void*)"99"),CCDelayTime::create(1.f),
		
		CCCallFuncND::create(this, callfuncND_selector(CNewerGuideFruit::actCallfunc), (void*)"98"),
		NULL);
	pFinger->runAction(CCRepeatForever::create(pAct)); 

 }
 CCActionInterval* CNewerGuideFruit::actClick()
 {
	 return  CCMoveBy::create(0.1f,ccp(0,15)),CCMoveBy::create(0.1f,ccp(0,-15));
 }

 void CNewerGuideFruit::actAngleCallfunc(CCNode* sender, void* data)
 {
	 std::string str = (char*)data;
	 int nIndex = CStringUtil::ToInt(str);
	 CFruitGuide* pCellSrc = (CFruitGuide*)mVecCellPath[nIndex];
	 CFruitGuide* pCellTarget = (CFruitGuide*)mVecCellPath[nIndex+1];
	 float angle =CGameFruitScene::GetCalcAngle(pCellTarget->getPosition(),pCellSrc->getPosition());
	 float fScale = CGameFruitScene::GetCalcScale(pCellTarget->getPosition(),pCellSrc->getPosition(),pCellSrc->pLine->getTextureRect().size.width);
	 pCellSrc->pLine->setScaleX(fScale);
	 pCellSrc->pLine->setRotation(angle);
	 pCellSrc->pLine->setVisible(true);
  }
 void CNewerGuideFruit::actCallfunc(CCNode* sender, void* data)
 {
	 CCString str = (char*)data;
	 if (str.compare("99") == 0)
	 {
		 for (int j = 0; j < mVecCellPath.size(); ++j)
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
				 CCAnimate::create(pAni),CCHide::create(),
				 NULL);
			 ((CFruitGuide*)mVecCellPath[j])->pCell->runAction(pAction);
			 ((CFruitGuide*)mVecCellPath[j])->pLine->setVisible(false);
		 }
	 }else if (str.compare("98") == 0)
	 {
		  for (int i = 0; i < mVecCell.size(); ++i)
		  {
			 CFruitGuide* pItem =  (CFruitGuide*)mVecCell[i];
			  CCString strFileName;
			 int  nType = 1;
			  if( i == 0|| i == 1)
				  nType = 2;
			  if(i == 4)
				  nType = 2;
			 
			  strFileName.initWithFormat("item/fruit%d.png",nType);
			  pItem->pCell->setDisplayFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName(strFileName.getCString()));
			  pItem->pCell->setVisible(true);
			  pItem->pLine->setVisible(false);
		  }
	 }
 }