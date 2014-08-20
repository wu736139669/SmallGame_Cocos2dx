

#include "MoneyManager.h"
#include "NetPacket.h"
#include "NetHttpClient.h"
#include "DataManager.h"
USING_NS_CC;
CMoneyMan::CMoneyMan()
{

}
CMoneyMan::~CMoneyMan()
{
   // this->flush();
}

void CMoneyMan::reset()
{
	
}

void CMoneyMan::parseNetData(CBasePacket* pBasePacket)
{
	CResponsePacket* pPk = dynamic_cast<CResponsePacket*>(pBasePacket);
	unsigned int unMsgCode = pPk->getMsgCode();
	CSJson::Value root ;
	if(!CJsonHelper::getJsonFromString(pPk->getContent().c_str(),root))
		return;
	switch (unMsgCode)
	{
	case eNetMsgGoldSysGetMoneyTmpInfo:
		{
			updataTemplateData(pPk->getContent().c_str());
			CDataManager::GetInstance().wirteToFile(TempFileMoneyInfo,pPk->getContent());
		}
		break;
	}

}
void CMoneyMan::updataTemplateData(const char* p)
{
	CSJson::Value root ;
	if(!CJsonHelper::getJsonFromString(p,root))
		return;
	mVecMoneyChgTempData.clear();
	for (int i = 0; i < root.size(); ++i)
	{
		SMoneySysChgTempData data;
		CSJson::Value& val = root[i];
		data.ExchangeId = val["exchangeid"].asInt(); 
		data.ExchangeName = val["exchangename"].asCString();	
		data.ExchangeFromID = val["exchangefromid"].asInt();	
		data.ExchangeFromValue = val["exchangefromvalue"].asInt();	
		data.ExchangeToID = val["exchangetoid"].asInt();	
		data.ExchangeToValue = val["exchangetovalue"].asInt();	
		mVecMoneyChgTempData.push_back(data);
	}
}
SMoneySysChgTempData* CMoneyMan::getChgTempData(int nId)
{
	for (int i = 0; i < mVecMoneyChgTempData.size(); ++i)
	{
		if(mVecMoneyChgTempData[i].ExchangeId == nId)
		{
			return &mVecMoneyChgTempData[i];
		}
	}
	return NULL;
}

void CMoneyMan::RequestGetMoneyTmpInfo()
{
	if (CDataManager::GetInstance().readTemplateData(TempFileMoneyInfo,this))
		return;
	NetHttpClient::sendHttpRequest(eNetMsgTypeMoneySys,eNetMsgGoldSysGetMoneyTmpInfo);
}