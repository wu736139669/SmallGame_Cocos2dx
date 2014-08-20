
#include "DataManager.h"
#include "JsonHelper.h"
#include "NetPacket.h"
#include "PlayerInfoManager.h"
#include "MoneyManager.h"
#include "TaskManager.h"
#include "FriendManager.h"
#include "InfoSysManager.h"
#include "StrengthenManager.h"
#include "GameInfoManager.h"
#include "GameItemManager.h"
#include "PkSysManager.h"
#include "TaikoData.h"
#include "StringUtil.h"
#include "spine/extension.h"
#include "RightTouchDefine.h"
#include "GameFruitDefine.h"
#include "FruitData.h"
#include "GameShare_Global.h"

CDataManager::CDataManager():INetHook(eNetHookTypeMainInfo),mlTotalFlow(0)
{
	CNetHookManager::sharedNetHookManager()->addHook(this);
}

CDataManager::~CDataManager()
{
  CNetHookManager::sharedNetHookManager()->delHook(this);
}

CDataManager& CDataManager::GetInstance()
{
    static CDataManager dataManager;
    return dataManager;
}
void CDataManager::accTotalFlow(int nByte)
{
	mlTotalFlow += nByte;
	CCLOG("cellFlow = %d K",nByte/1024);
	CCLOG("TotalFlow = %ld K",mlTotalFlow/1024);
}
bool CDataManager::readTemplateData(char* szpFileName,string& strData)
{
	string fullDBPath = CCFileUtils::sharedFileUtils()->getWritablePath() + szpFileName; 
	FILE* fp = fopen(fullDBPath.c_str(),"rb");
	if (fp == NULL)
		return false;
	fseek(fp,0,SEEK_END);
	int len = ftell(fp);
	fseek(fp,0,SEEK_SET);
	char* buf = (char*)malloc(len);
	fread(buf,len,1,fp);
	strData = buf;
	fclose(fp);
	free(buf);
	return true;
}
bool CDataManager::readTemplateData(char* szpFileName,ILoadTempData* pData)
{
	string str;
	if(readTemplateData(szpFileName,str)){
		pData->updataTemplateData(str.c_str());
		return true;
	}
	return false;
}
void CDataManager::wirteToFile(char* szpFileName,string& strWirteData)
{
	string fullDBPath = CCFileUtils::sharedFileUtils()->getWritablePath() + szpFileName; 
	CCLOG("save full : %s",fullDBPath.c_str());
	FILE *fp = fopen(fullDBPath.c_str(), "wb+");
	fwrite(strWirteData.c_str(), 1, strWirteData.size(), fp);
	fclose(fp);
}
CBaseData* CDataManager::getGameData(int nGameId)
{
    if(nGameId == -1)
	{
		nGameId = GameShare_Global::shareGlobal()->gameType ;
	}
    CBaseData* p = NULL;
    switch (nGameId) {
        case Game_Jelly:
            p = &CRtData;
            break;
        case Game_Fruit:
            p = &CFrData;
            break;
        case Game_TaiKo:
            p = &CTKData;
            break;
        default:
            break;
    }
    return p;
}
long CDataManager::getTotalFlow()
{
	return mlTotalFlow;
}
bool CDataManager::onPackageFilter(void *pDataPkg)
{
	CResponsePacket* pPkt = (CResponsePacket*)pDataPkg;
	unsigned int unMsgType = pPkt->getMsgType();
	unsigned int unMsgCode = pPkt->getMsgCode();
	int nMsgState = pPkt->getDataState();
	int nResCode = pPkt->getResCode();
	
	CSJson::Value root ;
	if(!CJsonHelper::getJsonFromString(pPkt->getContent().c_str(),root))
		return true;
	//网络数据传输完成
	if (nMsgState == eNetMsgDataStateComplete)
	{
		//if data is normal
		if (nResCode != eNetMsgResCodeSucceed)
		{
			CCLOG("network err: unMsgType = %d ,unMsgCode = %d, Content = %s",unMsgType , unMsgCode,pPkt->getResMsg().c_str());
			int fontSize = 30;
//			CCLabelTTF* pLabel = CCLabelTTF::create(pPkt->getResMsg().c_str(), "Thonburi", fontSize);
//			pLabel->setColor(ccc3(255,0,0));
//			CCDirector::sharedDirector()->getRunningScene()->addChild(pLabel,200000);
//			pLabel->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2,CCDirector::sharedDirector()->getWinSize().height*(2.f/3.f)));
//			pLabel->runAction(CCSequence::create(CCShow::create(),CCFadeOut::create(2.f),CCRemoveSelf::create(),NULL));
			
			return true;
		}

// 		if(!root.isArray())
// 		{
// 			CCLOG("res_body is empty");
// 			return true;
// 		}
		switch(unMsgType)
		{
        case eNetMsgTypeSend:
		case eNetMsgTypePlayerSys:
			{
				CPlayerInfoMan::sharedInstance().parseNetData(pPkt);
			}
			break;
		case eNetMsgTypeMoneySys:
			{
				CMoneyMan::sharedInstance().parseNetData(pPkt);
			}
			break;
        case eNetMsgTypeMissionSys:
            {
                CTaskMan::sharedInstance().parseNetData(pPkt);
            }
            break;
        case eNetMsgTypeGameSys:
            {
                CGameInfoMan::sharedInstance().parseNetData(pPkt);
            }
            break;
        case eNetMsgTypeIntensifySys:
            {
                CStrengthenMan::sharedInstance().parseNetData(pPkt);
            }
                break;
        case eNetMsgTypeItemSys:
            {
                CItemMan::sharedInstance().parseNetData(pPkt);
            }
            break;
		
        case eNetMsgTypeFriendSys:
            {
                CFriendManager::sharedInstance().parseNetData(pPkt);
            }
                break;
        case eNetMsgTypeMsgSys:
            {
                CInfoSysManager::sharedInstance().parseNetData(pPkt);
            }
                break;
            case eNetMsgTypePk:
            {
                CPkSysManager::sharedInstance().parseNetData(pPkt);
            }
                break;
		}
		
	}
	else if (nMsgState == eNetMsgDataStateTimeOut)
	{
	}
	
// 	 for (CSJson::ValueIterator a  =root.begin(); a!= root.end(); ++a) {
// 
// 		 CSJson::Value value=(CSJson::Value)*a;
// 	 }
	  
	return true;
}

void CDataManager::updataStrengthenItem(e_GameType eGameType)
{
	sMGameStrengthen data ;
	switch(eGameType)
	{
	case Game_TaiKo:
		{
			//音乐达人
			if (CPlayerInfoMan::sharedInstance().getMStrengthenByGameId(eGameType,StrengThenTag_14,data)){
				CTKData.setEffectStrengthenVal(eGameType,StrengThenTag_14,CStringUtil::ToDouble(data.strengthenValue));
			}
			if (CPlayerInfoMan::sharedInstance().getMStrengthenByGameId(eGameType,StrengThenTag_15,data)){
				CTKData.setEffectStrengthenVal(eGameType,StrengThenTag_15,CStringUtil::ToDouble(data.strengthenValue));
				
			}
			if (CPlayerInfoMan::sharedInstance().getMStrengthenByGameId(eGameType,StrengThenTag_16,data)){
				CTKData.setEffectStrengthenVal(eGameType,StrengThenTag_16,CStringUtil::ToDouble(data.strengthenValue));
			}
		}
		break;
	case Game_Fruit:
		{//宝石连线
			if (CPlayerInfoMan::sharedInstance().getMStrengthenByGameId(eGameType,StrengThenTag_5,data)){
				CFrData.setEffectStrengthenVal(eGameType,StrengThenTag_5,CStringUtil::ToDouble(data.strengthenValue));
			}
			if (CPlayerInfoMan::sharedInstance().getMStrengthenByGameId(eGameType,StrengThenTag_6,data)){
				CFrData.setEffectStrengthenVal(eGameType,StrengThenTag_6,CStringUtil::ToDouble(data.strengthenValue));
			}
			if (CPlayerInfoMan::sharedInstance().getMStrengthenByGameId(eGameType,StrengThenTag_7,data)){
				CFrData.setEffectStrengthenVal(eGameType,StrengThenTag_7,CStringUtil::ToDouble(data.strengthenValue));
			}
		}
		break;
	case Game_Jelly:
		{//合体消除
			if (CPlayerInfoMan::sharedInstance().getMStrengthenByGameId(eGameType,StrengThenTag_3,data)){
				CRtData.setEffectStrengthenVal(eGameType,StrengThenTag_3,CStringUtil::ToDouble(data.strengthenValue));
				
			}
			if (CPlayerInfoMan::sharedInstance().getMStrengthenByGameId(eGameType,StrengThenTag_2,data)){
				CRtData.setEffectStrengthenVal(eGameType,StrengThenTag_2,CStringUtil::ToDouble(data.strengthenValue));
			}
			if (CPlayerInfoMan::sharedInstance().getMStrengthenByGameId(eGameType,StrengThenTag_4,data)){
				CRtData.setEffectStrengthenVal(eGameType,StrengThenTag_4,CStringUtil::ToDouble(data.strengthenValue));
			}
		}
		break;
	}
	
}
bool CDataManager::getGameNewerGuideState(e_GameType eGameType)
{
	CCString str;
	str.initWithFormat("NewerGuideState%d",eGameType);
	bool a = CCUserDefault::sharedUserDefault()->getBoolForKey(str.getCString(),false);
	return a;
	//return false;
}
void CDataManager::setGameNewerGuideState(e_GameType eGameType,bool bState)
{
	CCString str;
	str.initWithFormat("NewerGuideState%d",eGameType);
	CCUserDefault::sharedUserDefault()->setBoolForKey(str.getCString(),bState);
}
// void CDataManager::Convert(const char* strIn,char* strOut, int sourceCodepage, int targetCodepage)  
// {  
// 	int len=strlen(strIn);  
// 	int unicodeLen=MultiByteToWideChar(sourceCodepage,0,strIn,-1,NULL,0);  
// 	wchar_t* pUnicode;  
// 	pUnicode=new wchar_t[unicodeLen+1];  
// 	memset(pUnicode,0,(unicodeLen+1)*sizeof(wchar_t));  
// 	MultiByteToWideChar(sourceCodepage,0,strIn,-1,(LPWSTR)pUnicode,unicodeLen);  
// 	BYTE * pTargetData = NULL;  
// 	int targetLen=WideCharToMultiByte(targetCodepage,0,(LPWSTR)pUnicode,-1,(char *)pTargetData,0,NULL,NULL);  
// 	pTargetData=new BYTE[targetLen+1];  
// 	memset(pTargetData,0,targetLen+1);  
// 	WideCharToMultiByte(targetCodepage,0,(LPWSTR)pUnicode,-1,(char *)pTargetData,targetLen,NULL,NULL);  
// 	strcpy(strOut,(char*)pTargetData);  
// 	delete pUnicode;  
// 	delete pTargetData;  
// }  