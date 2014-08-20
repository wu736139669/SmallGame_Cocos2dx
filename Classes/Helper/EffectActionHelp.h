/********************************************************************
	created:	2014/05/08 
	filename: 	EffectActionHelp.h
	author:		王少培
	purpose:	
*********************************************************************/
#ifndef _EffectActionHelper_H_
#define _EffectActionHelper_H_
#include "cocos2d.h"
USING_NS_CC;
enum EEffectActHelpType{
	eHelp5Second,
	eHelp20000,
	eHelp50000,
	eHelpShield,
	eHelpMul5,
	eHelpTime,
};
class CEffectActionHelper
{
public:
	//动作
	static void play(EEffectActHelpType eType, CCNode* pParent,CCPoint pt = ccp(0,0));
};

#endif