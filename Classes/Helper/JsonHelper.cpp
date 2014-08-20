/***************************************************************
* 
*
*  作者：   王少培
*  文件名：   
*  创建时间： 2014-3-20
*
***************************************************************/
#include "JsonHelper.h"

bool CJsonHelper::getJsonFromFile(const char* fileName)
{
	CSJson::Value Val;
	unsigned long ilength;
	//这里是将文件解析出来，付给pBuffer字符串
	string strPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName); 
	char* pBuffer = (char *)CCFileUtils::sharedFileUtils()->getFileData(strPath.c_str(), "r", &ilength);
	return getJsonFromString(pBuffer,Val);
	//CCLog("%s",pBuffer);
	 
}
bool CJsonHelper::getJsonFromString(const char* pszData,CSJson::Value& Val)
{
	CSJson::Reader reader;  
	CSJson::Value jsValue;
	//这里将pBuffer的值付给jsValue值
	bool parseRet = reader.parse(pszData, jsValue, false);
	Val = jsValue;
	//CCAssert(parseRet, "Read JsonData Error~!!!!!!!!!");
	return parseRet; 
}