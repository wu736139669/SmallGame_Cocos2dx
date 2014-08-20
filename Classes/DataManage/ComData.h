/********************************************************************
	created:	2014/04/03 
	filename: 	ComData.h
	author:		王少培
	purpose:	
*********************************************************************/
#ifndef _COM_DATA_H
#define _COM_DATA_H
#include "JsonHelper.h"

#define  RAND_GAME_BASE_VAL 100 //随机基本基数
#define  RAND_GAME_BASE_VAL_10000 10000 //随机基本基数
#define  GetVSe CCDirector::sharedDirector()->getVisibleSize()
#define  CCTexAddImage(fileName) CCTextureCache::sharedTextureCache()->addImage(fileName)
typedef enum{
	eSwitchPause = 0,
	eSwitcResume
}ESwitchFlag;

enum ECrazyMode
{
	eComCrazyMode,
	eSuperCrazyMode,
	eNoneMode,
};

//////////////////////////////////////////////////////////////////////////
//about load the template data 
#define TempFileItemSysGetAll  "tempItemSysGetAll.json"
#define TempFileMoneyInfo	"tempItemMoneyInfo.json"
#define TempFileIntensifySysAllInfo	"tempIntensifySysAllInfo.json"
#define TempFileGameInfo	"tempGameInfo.json"

class ILoadTempData
{
public:
	virtual void updataTemplateData(const char* str){};
	virtual void updataTemplateData(CSJson::Value& v){}
};

#endif