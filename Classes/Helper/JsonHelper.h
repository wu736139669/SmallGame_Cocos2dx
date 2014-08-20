/***************************************************************
* 
*
*  作者：   王少培
*  文件名：   
*  创建时间： 2014-3-20
*
***************************************************************/
#ifndef _CJsonHelper_H_
#define  _CJsonHelper_H_
#include "cocos-ext.h"
using namespace std;
USING_NS_CC;
class CJsonHelper
{
public:
	static bool getJsonFromFile(const char* fileName);
	static bool getJsonFromString(const char* pszData,CSJson::Value& Val);
};

#endif