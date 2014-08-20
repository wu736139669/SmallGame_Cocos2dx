/********************************************************************
	created:	2014/03/28 
	filename: 	BRCsvBase.h
	author:		王少培
	purpose:	
*********************************************************************/
#ifndef __BRCSVBASE_H__
#define __BRCSVBASE_H__
#include "UniqueData.h"
#include "cocos2d.h"
USING_NS_CC;
class CCsvLoader;
class CCsvBase: public CUniqueDataBase {
public:
	virtual bool load(CCsvLoader *pLoader) = 0;

	virtual std::string getCsvPath()
	{
		std::string strPath;
		strPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(strTableName.c_str());
		return strPath;
	}
};

#endif
