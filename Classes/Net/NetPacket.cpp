
/***************************************************************
* 
*
*  作者：   王少培
*  文件名：   NetPacket.cpp
*  创建时间： 2014-3-20
*
***************************************************************/

#include "NetPacket.h"
CRequestPacket::CRequestPacket(unsigned int unType, unsigned int unCode): CBasePacket(unType,unCode) {
	mstrContent = parse(unType,unCode);
}
CRequestPacket::CRequestPacket(unsigned int unType, unsigned int unCode,const CSJson::Value& msgBady): CBasePacket(unType,unCode) {
	mstrContent = parse(unType,unCode,msgBady);
}
string CRequestPacket::parse(unsigned int unType, unsigned int unCode)
{
	CSJson::Value msg_bady;
	msg_bady["player_id"] = CSJson::Value(1100);
	msg_bady["exp"] = CSJson::Value(999);
	CSJson::Value root;
	root["msg_type"] = CSJson::Value(unType);
	root["msg_code"] = CSJson::Value(unCode);
	root["msg_body"] = msg_bady; 
	root["key_array"].append("array_string");            
	root["key_array"].append(1234);                        
	CSJson::ValueType type = root.type();
	CSJson::FastWriter fast_writer;
	return  fast_writer.write(root);
}
string CRequestPacket::parse(unsigned int unType, unsigned int unCode,const CSJson::Value& msgBady)
{
	CSJson::Value root;
	root["msg_type"] = CSJson::Value(unType);
	root["msg_code"] = CSJson::Value(unCode);
	root["msg_body"] = msgBady;
	CSJson::ValueType type = root.type();
	CSJson::FastWriter fast_writer;
	return  fast_writer.write(root);
}
//////////////////////////////////////////////////////////////////////////
CResponsePacket::CResponsePacket(unsigned int unMsgType,unsigned int unMsgCode,const char* pszResData,eNetMsgDataState eDataState)
	:CBasePacket(unMsgType,unMsgCode),meDataState(eDataState)
{
	parse(pszResData);
}
void CResponsePacket::parse(const char* pszResData)
{
	if(pszResData == NULL)
		return;
	CSJson::Value js ;
	if(!CJsonHelper::getJsonFromString(pszResData,js))
		return;

	mstrResMsg = js["res_msg"].asString();
	mResCode = js["res_code"].asInt();
	CSJson::Value body_root = js["res_body"];
	CSJson::FastWriter fast_writer;
	mstrContent = fast_writer.write(body_root);
}