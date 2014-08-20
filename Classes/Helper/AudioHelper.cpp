/***************************************************************
* 
*
*  作者：   王少培
*  文件名：   
*  创建时间： 2014-3-20
*
***************************************************************/
#include "AudioHelper.h"
#include "AudioDefine.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
USING_NS_CC;
int CAudioHelper::playSound(int nSoundType,bool bLoop)
{
	int nSoundId = 0;
	CCString strPath;
	switch(nSoundType)
	{
	case eSoundTypeFruiteSelete:
		strPath = "./game_fruit/Sounds/selected.mp3";
		break;
	case eSoundTypeFruiteBackground:
		strPath  = "./game_fruit/Sounds/background.mp3";
		break;
	case eSoundTypeRightTouchSelete:
		strPath  = "./right_touch/selected.mp3";
		break;
	case eSoundTypeRightTouchBackground:
		strPath  = "./game_fruit/Sounds/background.mp3";
		break;
	case eSoundTypeRihgtTouchMerge:
		strPath  = "./right_touch/Sounds/selected.mp3";
		break;
	//////////////////////////////////////////////////////////////////////////
	//音乐达人
	case eSoundTypeTaikoClick:
		strPath  = "tai_ko/sound/click.caf";
		break;
	//////////////////////////////////////////////////////////////////////////
	}
	nSoundId = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(strPath.getCString(), bLoop);
	return nSoundId;
}
bool CAudioHelper::playBackgroundSound(int nSoundType,bool bLoop)
{
	int nSoundId = 0;
	CCString strPath;
	switch(nSoundType)
	{
	case eSoundTypeFruiteBackground:
		strPath  = "./game_fruit/Sounds/background.mp3";
		break;
	case eSoundTypeRightTouchBackground:
		strPath  = "./game_fruit/Sounds/background.mp3";
		break;
	case eSoundTypeTaikoBackground:
		strPath  = "tai_ko/sound/bk.mp3";
		break;
	}
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(strPath.getCString(), bLoop);
	return true;
}
bool CAudioHelper::stopBackgroundSound()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	return true;
}