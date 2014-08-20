
#include "GameShare_Data.h"
#include "Scene_GameList.h"
#include "GameShare_Global.h"
#include "NetHttpClient.h"
#include "MoneyManager.h"
#include "NetPacket.h"
#include "MsgDefine.h"
#include "PlayerInfoManager.h"
#include "StrengthenManager.h"
#include "GameInfoManager.h"
#include "GameItemManager.h"
#include "GameShare_Msg.h"

USING_NS_CC;

CPlayerInfoMan::CPlayerInfoMan():isTouristLogin(true)
{
    this->reset();
}
CPlayerInfoMan::~CPlayerInfoMan()
{
   // this->flush();
}

void CPlayerInfoMan::reset()
{
   // mPlayerInfo.strUuId = "45cc4350-cedd-11e3-a2fc-002590386cc4";
//	mPlayerInfo.strUuId = "17f9cd86-f074-11e3-b9ce-002590386cc4";//路人甲
    mPlayerInfo.strUuId = "346cde9a-d977-11e3-a2fc-002590386cc4";
    
	 //mPlayerInfo.strUuId = "57911892-def3-11e3-a2fc-002590386cc4";
	//mPlayerInfo.strUuId = "3aa84942-cf46-11e3-a2fc-002590386cc4";
    mPlayerInfo.nId = 0;
    mPlayerInfo.strName = "";
    mPlayerInfo.strImg = "";
    mPlayerInfo.nLevel = 1;
    mPlayerInfo.nPower = 0;
    mPlayerInfo.nMoney = 0;
    mPlayerInfo.nGem = 0;
    mPlayerInfo.strQQ = "";
    mPlayerInfo.strSina = "";
    mPlayerInfo.nScore = 0;
    mPlayerInfo.nExp = 0;
    mPlayerInfo.nDailyTaskId = 1;
    mPlayerInfo.sysInfoNum = 0;
    mPlayerInfo.lastDailyTaskTime = 0;
    mPlayerInfo.riceEndTime = 0;
	mPlayerInfo.nPlayerMedal = 0;
    mPlayerInfo.mGameData.clear();
    mPlayerInfo.mStrengthen.clear();
}

void CPlayerInfoMan::parseNetData(CBasePacket* pBasePacket)
{
	CResponsePacket* pPk = dynamic_cast<CResponsePacket*>(pBasePacket);
	unsigned int unMsgCode = pPk->getMsgCode();
    unsigned int unMsgType = pPk->getMsgType();
    int nResCode = pPk->getResCode();
	CSJson::Value root ;
	if(!CJsonHelper::getJsonFromString(pPk->getContent().c_str(),root))
		return;
    
    
    //登陆失败.
    if (nResCode == 10005) {
        //发出消息.
        CCNotificationCenter::sharedNotificationCenter()->postNotification(kLoginFail, NULL);
        return;
    }
    //赠送饭系统
    if (unMsgType == eNetMsgTypeSend) {
        if (unMsgCode == eNetMsgReceiveRice) {
            mPlayerInfo.nPower++;
        }
        if (unMsgCode == eNetMsgSendRice)
        {
        }
        return;
    }
    switch (unMsgCode)
    {
        case eNetMsgPlayerSysGetPlayerInfo:
        {
            CSJson::Value val = root[0];
            mPlayerInfo.nId = val["playerid"].asInt();
            mPlayerInfo.strName = val["playername"].asCString();
//            mPlayerInfo.strName = "aaaaaa";
            mPlayerInfo.strUuId = val["playeruuid"].asCString();
            mPlayerInfo.strImg = val["playerimg"].asCString();
            mPlayerInfo.nLevel = val["playerlevel"].asInt();
            mPlayerInfo.nPower = val["playerpower"].asInt();
            mPlayerInfo.nMoney = val["playermoney"].asInt();
            mPlayerInfo.nGem = val["playergem"].asInt();
//            mPlayerInfo.strQQ = val["playerqq"].asCString();
//            mPlayerInfo.strSina = val["playersina"].asCString();
//            mPlayerInfo.appId = val["appid"].asCString();
            mPlayerInfo.nScore = val["totalscore"].asInt();
            mPlayerInfo.nExp = val["playerexp"].asFloat()*100;
            mPlayerInfo.nDailyTaskId = val["playerdailytaskid"].asInt();
			mPlayerInfo.nPlayerMedal = val["playermedal"].asInt();
//            mPlayerInfo.riceEndTime = val["playerlastusepowertime"].asInt();
            if (mPlayerInfo.nDailyTaskId == 0) {
                mPlayerInfo.nDailyTaskId = 1;
            }
            mPlayerInfo.lastDailyTaskTime = val["playerlastdailytasktime"].asUInt();
            
            //请求游戏最高分.
            for (int i = Game_Memory; i<Game_Cir; i++) {
                CStrengthenMan::sharedInstance().RequestGetPlayInfoByGameId(i);
                CGameInfoMan::sharedInstance().RequestgetGameMaxScore(i);
            }
            //每日奖励
            NetHttpClient::sendHttpRequest(eNetMsgTypeMissionSys,eNetMsgMissionSysDayTask);


        }
            break;
        case eNetMsgPlayerSysBugGem:
        {
            CSJson::Value val = root[0];
            int nId = val["exchangeid"].asInt();
            SMoneySysChgTempData* pData = CMoneyMan::sharedInstance().getChgTempData(nId);
            if (pData)
            {
                mPlayerInfo.nGem += pData->ExchangeToValue;
            }
        }
            break;
        case eNetMsgPlayerSysChgTiLi:
        {
            CSJson::Value val = root[0];
            int nId = val["exchangeid"].asInt();
            SMoneySysChgTempData* pData = CMoneyMan::sharedInstance().getChgTempData(nId);
            if (pData)
            {
                mPlayerInfo.nGem -= pData->ExchangeFromValue;
                mPlayerInfo.nPower += pData->ExchangeToValue;
            }
        }
            break;
        case eNetMsgPlayerSysChgGold:
        {
            CSJson::Value val = root[0];
            int nId = val["exchangeid"].asInt();
            SMoneySysChgTempData* pData = CMoneyMan::sharedInstance().getChgTempData(nId);
            if (pData)
            {
                mPlayerInfo.nGem -= pData->ExchangeFromValue;
                mPlayerInfo.nMoney += pData->ExchangeToValue;
            }
        }
            break;
        case eNetMsgPlayerSysRegister:
        {
            CCLOG("callback RequestPlayRegist");
            CSJson::Value val = root[0];
            mPlayerInfo.strUuId = val["playeruuid"].asCString();
            GameShare_Data::shareData()->setUserUUID(mPlayerInfo.strUuId);
//            CPlayerInfoMan::sharedInstance().RequestPlayerInfo();
            
        }
            break;
        case eNetMsgPlayerSysReduceEnergy:
        {
            mPlayerInfo.nPower--;
        }
            break;
            
        case eNetMsgPlayerSysGetPlayerRiceInfo:
        {
            CSJson::Value val = root[0];
            mPlayerInfo.riceEndTime = val["timeout"].asInt();
            mPlayerInfo.nPower = val["playerpower"].asInt();
        }
            break;
            
        case eNetMsgPlayerSysGetPlayerMoneyInfo:
        {
            CSJson::Value val = root[0][0];
            mPlayerInfo.nMoney = val["playermoney"].asInt();
            mPlayerInfo.nGem = val["playergem"].asInt();
            mPlayerInfo.nPower = val["playerpower"].asInt();
            
            CCNotificationCenter::sharedNotificationCenter()->postNotification(kRefreshMoney, NULL);
        }
            break;
        default:
            break;
    }
	
		
}

int CPlayerInfoMan::getPlayerLevel() {
    return mPlayerInfo.nLevel;
}

void CPlayerInfoMan::RequestPlayerInfo()
{
	CSJson::Value msg_body;
	msg_body["playeruuid"] = CSJson::Value(CPlayerInfoMan::sharedInstance().getPlayerInfo().strUuId.c_str());
	NetHttpClient::sendHttpRequest(eNetMsgTypePlayerSys,eNetMsgPlayerSysGetPlayerInfo,&msg_body);
}
void CPlayerInfoMan::RequsetRMBToDiamond(int nId)
{
	CSJson::Value msg_body;
	msg_body["exchangeid"] = CSJson::Value(nId);
	NetHttpClient::sendHttpRequest(eNetMsgTypePlayerSys,eNetMsgPlayerSysBugGem,&msg_body);
}
void CPlayerInfoMan::RequestDiamondToRice(int nId)
{
    CSJson::Value msg_body;
	msg_body["exchangeid"] = CSJson::Value(nId);
	NetHttpClient::sendHttpRequest(eNetMsgTypePlayerSys,eNetMsgPlayerSysChgTiLi,&msg_body);
}
void CPlayerInfoMan::RequestDiamondToGold(int nId)
{
    CSJson::Value msg_body;
	msg_body["exchangeid"] = CSJson::Value(nId);
	NetHttpClient::sendHttpRequest(eNetMsgTypePlayerSys,eNetMsgPlayerSysChgGold,&msg_body);
}
void CPlayerInfoMan::RequestAddExp(int exp)
{
    CSJson::Value msg_body;
	msg_body["playeruuid"] = CSJson::Value(CPlayerInfoMan::sharedInstance().getPlayerInfo().strUuId.c_str());
    msg_body["playerexp"] = CSJson::Value(exp);
	NetHttpClient::sendHttpRequest(eNetMsgTypePlayerSys,eNetMsgPlayerSysAddExp,&msg_body);
}
void CPlayerInfoMan::RequestAddGold(int gold)
{
    CSJson::Value msg_body;
    msg_body["playermoney"] = CSJson::Value(gold);
	NetHttpClient::sendHttpRequest(eNetMsgTypePlayerSys,eNetMsgPlayerSysAddGlod,&msg_body);
}
void CPlayerInfoMan::RequestPkInfoMation() {
    
}

void CPlayerInfoMan::RequestPlayerMoneyInfoMation() {
	NetHttpClient::sendHttpRequest(eNetMsgTypePlayerSys,eNetMsgPlayerSysGetPlayerMoneyInfo);
}

void CPlayerInfoMan::RequestPlayRegist(const char *name, const char* avatarUrl, int type, const char *userId, long timeStamp)
{
    unsigned int tempTime = timeStamp;
	CSJson::Value msg_body;
	msg_body["playerregtype"] = CSJson::Value(type);
    msg_body["playername"] = CSJson::Value(name);
    msg_body["playerimg"] = CSJson::Value(avatarUrl);
    msg_body["playerendtime"] = CSJson::Value(tempTime);
    msg_body["appid"] = CSJson::Value(userId);
    
	NetHttpClient::sendHttpRequest(eNetMsgTypePlayerSys,eNetMsgPlayerSysRegister,&msg_body);
    CCLOG("RequestPlayRegist");
}

void CPlayerInfoMan::RequestUseRice()
{
    CSJson::Value msg_body;
	NetHttpClient::sendHttpRequest(eNetMsgTypePlayerSys,eNetMsgPlayerSysReduceEnergy,&msg_body);
}
void CPlayerInfoMan::RequestSendRice(int sendId)
{
    CSJson::Value msg_body;
    msg_body["recvplayerid"] = CSJson::Value(sendId);
    msg_body["sendplayerid"] = CSJson::Value(mPlayerInfo.nId);
	NetHttpClient::sendHttpRequest(eNetMsgTypeSend,eNetMsgSendRice,&msg_body);
}
void CPlayerInfoMan::RequestReceiverice(int recId)
{
    CSJson::Value msg_body;
    msg_body["powernoticeid"] = CSJson::Value(recId);
	NetHttpClient::sendHttpRequest(eNetMsgTypeSend,eNetMsgReceiveRice,&msg_body);
}
sMStrengthen* CPlayerInfoMan::getMStrengthenByGameId(int gameId)
{
    for (int i=0; i < mPlayerInfo.mStrengthen.size(); ++i) {
        if (mPlayerInfo.mStrengthen[i].gameId == gameId) {
            return &mPlayerInfo.mStrengthen[i];
        }
    }
    return NULL;
}
int CPlayerInfoMan::getMStrengthenByGameTag(int gameId, int strengTag, sMGameStrengthen &mGameStrengthen)
{
    sMStrengthen* mStrength = NULL;
    for (int i=0; i < mPlayerInfo.mStrengthen.size(); ++i) {
        if (mPlayerInfo.mStrengthen[i].gameId == gameId) {
             mStrength =  &mPlayerInfo.mStrengthen[i];
        }
    }
    if (mStrength) {
        if (mStrength->mGameStrengthen.size() > strengTag) {
            int strengId = mStrength->mGameStrengthen[strengTag].strengthenId;
            int strengLv = mStrength->mGameStrengthen[strengTag].strengtheLv;
            mGameStrengthen.strengthenId = strengId;
            mGameStrengthen.strengthenlv = strengLv;
            strengLv++;
            sStrengthen* strengThen = CStrengthenMan::sharedInstance().getChgTempData(strengId);
            if (strengThen) {
                mGameStrengthen.strengthenName = strengThen->strengthenName;
                mGameStrengthen.strengthenDetail = strengThen->strengthenDetail;
                mGameStrengthen.strengthenImg = strengThen->strengthenImg;
                
                sStrengthenLv* lvInfo = CStrengthenMan::sharedInstance().getLvInfo(strengLv, strengThen->lvInfo);
                
                if (lvInfo) {
                    mGameStrengthen.strengthenValue = lvInfo->strengthenValue;
                    mGameStrengthen.currencyId = lvInfo->currencyId;
                    mGameStrengthen.currencyValue = lvInfo->currencyValue;
                }else{
                    mGameStrengthen.strengthenValue = "0";
                    mGameStrengthen.currencyId = 0;
                    mGameStrengthen.currencyValue = 0;
                }
                if (strengThen->strengthenMaxLv < strengLv) {
                    return 2;
                }
                return 1;
            }
        }
        
    }
    return 0;
}
int CPlayerInfoMan::getMStrengthenByGameId(int gameId, eStrengthenId strengId, sMGameStrengthen &mGameStrengthen)
{
    sMStrengthen* mStrength = NULL;
    for (int i=0; i < mPlayerInfo.mStrengthen.size(); ++i) {
        if (mPlayerInfo.mStrengthen[i].gameId == gameId) {
            mStrength =  &mPlayerInfo.mStrengthen[i];
			break;
        }
    }
    if (mStrength) {
        for (int i=0; i<mStrength->mGameStrengthen.size(); ++i) {
            if (mStrength->mGameStrengthen[i].strengthenId == strengId) {
                if (mStrength->mGameStrengthen.size() > i) {
                    int strengId = mStrength->mGameStrengthen[i].strengthenId;
                    int strengLv = mStrength->mGameStrengthen[i].strengtheLv;
                    mGameStrengthen.strengthenId = strengId;
                    mGameStrengthen.strengthenlv = strengLv;
                    sStrengthen* strengThen = CStrengthenMan::sharedInstance().getChgTempData(strengId);
                    if (strengThen) {
                        mGameStrengthen.strengthenName = strengThen->strengthenName;
                        mGameStrengthen.strengthenDetail = strengThen->strengthenDetail;
                        mGameStrengthen.strengthenImg = strengThen->strengthenImg;
                        sStrengthenLv* lvInfo = CStrengthenMan::sharedInstance().getLvInfo(strengLv, strengThen->lvInfo);
                        if (lvInfo) {
                            mGameStrengthen.strengthenValue = lvInfo->strengthenValue;
                            mGameStrengthen.currencyId = lvInfo->currencyId;
                            mGameStrengthen.currencyValue = lvInfo->currencyValue;
                        }else
                        {
                            mGameStrengthen.strengthenValue = "0";
                            mGameStrengthen.currencyId = 0;
                            mGameStrengthen.currencyValue = 0;
                        }
                        if (strengThen->strengthenMaxLv <= strengLv) {
                            return 2;
                        }
                        return 1;
                    }
                }

            }
        }
    }
    return 0;
}

void CPlayerInfoMan::setLoginPreson(bool kind) {
    isTouristLogin = kind;
}
void CPlayerInfoMan::setLognFirst(bool kind) {
    isLognFirst = kind;
}

void CPlayerInfoMan::setNowLv(int lv) {
    mPlayerInfo.nLevel = lv;
}