/********************************************************************
	created:	2014/05/08 
	filename: 	EffectActionHelp.h
	author:		王少培
	purpose:	
*********************************************************************/

#include "EffectActionHelp.h"
#include "GameUIExportJson.h"
USING_NS_CC;
void CEffectActionHelper::play(EEffectActHelpType eType,CCNode* pParent,CCPoint pt)
{
	CCSprite *p;
	if (eType == eHelp5Second) {
		p = CCSprite::create(img5Second);
		p ->setScale(0.3);
	}
	else if (eType == eHelp20000) {
		p = CCSprite::create(img20000);
		p ->setScale(0.7);
	}
	else if (eType == eHelp50000){
		p = CCSprite::create(img50000);
		p ->setScale(0.7);
	}
	else if(eType == eHelpShield){
		p = CCSprite::create(imgShield);
		p ->setScale(2);
	}else if (eType ==  eHelpMul5)
	{
		p = CCSprite::create("GameMemoryLayer/mul5.png");
		p ->setScale(1);
	}else if (eType == eHelpTime)
	{
		p = CCSprite::create("./CocoStudioResources/GameItem/400003.png");
		p ->setScale(2);
	}
	p->setPosition(pt);
	CCMoveBy *upMove = CCMoveBy::create(0.3, ccp(0, 10));
	CCScaleTo *sizeChange = CCScaleTo::create(0.3, 0.1);
	CCFadeTo *aph = CCFadeTo::create(0.3, 0);
	//CCCallFunc *actionStopCallBack = CCCallFunc::create(this, callfunc_selector(Game_Memory::callBack));
	pParent->addChild(p,1000);
	p -> runAction(CCSequence::create(CCShow::create(),upMove,sizeChange,aph,CCRemoveSelf::create(),NULL));
}