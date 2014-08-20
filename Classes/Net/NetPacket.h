/***************************************************************
* 
*
*  作者：   王少培
*  文件名：   NetPacket.cpp
*  创建时间： 2014-3-20
*
***************************************************************/
#ifndef __NetPacket_h__
#define __NetPacket_h__
#include <map>
#include <vector>
#include <string>
#include "MsgDefine.h"
#include "JsonHelper.h"
using namespace std;

class CBasePacket {
public:
	CBasePacket(unsigned int unType, unsigned int unCode):mMsgType(unType),mMsgCode(unCode) {}
	virtual ~CBasePacket() {}
public: 
	string& getContent(){return mstrContent;}
	void setContent(const char* pszData){mstrContent = pszData;};
	unsigned int getMsgCode(){return mMsgCode;};
	unsigned int getMsgType(){return mMsgType;};
protected:
	unsigned int mMsgType;
	unsigned int mMsgCode;
	string mstrContent;
};
class CRequestPacket : public CBasePacket
{
public:
	CRequestPacket(unsigned int unType, unsigned int unCode);
	CRequestPacket(unsigned int unType, unsigned int unCode,const CSJson::Value& msgBady);
	virtual ~CRequestPacket() {}
public:
	virtual string parse(unsigned int unType, unsigned int unCode);
	virtual string parse(unsigned int unType, unsigned int unCode,const CSJson::Value& msgBady);
};
class CResponsePacket : public CBasePacket
{
public:
	CResponsePacket(unsigned int unMsgType,unsigned int unMsgCode,const char* pszResData,eNetMsgDataState eDataState = eNetMsgDataStateNone);
	virtual ~CResponsePacket() {}

	int getDataState(){return meDataState;}
	unsigned int getResCode(){return mResCode;};
	string& getResMsg(){return mstrResMsg;};
protected:
	virtual void parse(const char* pszResData);
protected:
	eNetMsgDataState meDataState;
	string mstrResMsg;
	unsigned int mResCode;
};
#endif
