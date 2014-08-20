//
//  TaskManager.cpp
//  OnceAgain
//
//  Created by mac on 14-4-3.
//
//

#include "TaskManager.h"
#include "NetPacket.h"
#include "NetHttpClient.h"
#include "PlayerInfoManager.h"
#include "GameShare_Msg.h"
#include "GameShare_Global.h"
#include "GameInfoManager.h"
#include "Scene_GameList.h"
#include "GameInfoManager.h"
#include "TaskDefine.h"
USING_NS_CC;
//////////////////////////////////////////////////////////////////////////
//
bool CEveryDayCell::isComplete()
{
	if (mnTaskComplete)
		return true;
	return false;
}
void CEveryDayCell::process()
{

}
//////////////////////////////////////////////////////////////////////////
CTaskMan::CTaskMan()
{
    this->reset();
}
CTaskMan::~CTaskMan()
{
    // this->flush();
}

void CTaskMan::reset()
{
	mVecWeekTask.clear();
    mVecTaskMedalData.clear();
    mVecTaskSystemData.clear();
}
void CTaskMan::resetInside()
{
	clrEveryDayTask(false);
}
void CTaskMan::parseNetData(CBasePacket* pBasePacket)
{
	CResponsePacket* pPk = dynamic_cast<CResponsePacket*>(pBasePacket);
	unsigned int unMsgCode = pPk->getMsgCode();
	CSJson::Value root ;
	if(!CJsonHelper::getJsonFromString(pPk->getContent().c_str(),root))
		return;
 
	switch (unMsgCode)
	{
        case eNetMsgMissionSysDayTask:
		{
            
			mVecTaskSystemData.clear();
			for (int i = 0; i < root.size(); ++i)
			{
              
				sTaskData data;
				CSJson::Value& val = root[i];
            
				data.TaskId = val["taskid"].asInt();
				data.TaskName = val["taskname"].asCString();
				data.TaskDetail = val["taskdetail"].asCString();
                int imgId = val["taskimg"].asInt();
                CCString taskStr;
                taskStr.initWithFormat("%d",imgId);
				data.TaskImg = taskStr.m_sString;
				data.TaskRewardType = val["taskrewardtype"].asInt();
				data.TaskRewardId = val["taskrewardid"].asInt();
                data.TaskRewardValue = val["taskrewardvalue"].asInt();
				mVecTaskSystemData.push_back(data);
			}
            //登陆.
//            GameShare_Global::shareGlobal()->loginType = LoginType_QQ;
            CCScene *scene_GameList = Scene_GameList::scene();
            CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.4, scene_GameList));
		}
        break;
    case eNetMsgMissionSysTask:
        {
            CSJson::Value& val = root[0];
            sTaskData *data = this->getChgTempData(val["taskid"].asInt());
            if (data->TaskRewardId == 4) {
                CPlayerInfoMan::sharedInstance().getPlayerInfo().nMoney += data->TaskRewardValue;
            }
            if (data->TaskRewardId == 5) {
                CPlayerInfoMan::sharedInstance().getPlayerInfo().nGem += data->TaskRewardValue;
            }
            if (data->TaskRewardId == 3) {
                CPlayerInfoMan::sharedInstance().getPlayerInfo().nPower += data->TaskRewardValue;
            }
        }
        break;
	case eNetMsgMissionSysDayTaskTemp:
		{
			mVecTaskMedalData.clear();
			for (int i = 0; i < root.size(); ++i)
			{
				SMeDalTaskData data;
				CSJson::Value& val = root[i];
				data.TaskId = val["taskid"].asInt();
				data.TaskName = val["taskname"].asCString();
				data.TaskDetail = val["taskdetail"].asCString();
			
				data.TaskImg = val["taskimg"].asInt();
				data.TaskRewardType = val["taskrewardtype"].asInt();
				data.TaskRewardId = val["taskrewardid"].asInt();
				data.TaskRewardValue = val["taskrewardvalue"].asInt();
				data.TaskDifficulty = val["taskdifficulty"].asInt();
				data.TaskValue = val["taskvalue"].asInt();
				data.TaskCatelog = val["taskcatelog"].asInt();
				data.TaskRange = val["taskisheap"].asInt();
				mVecTaskMedalData.push_back(data);
                
			}
		}
		break;
    case eNetMsgMissionSysDayTaskSelect:{
            
        }
        break;
	case eNetMsgMissionSysDayTaskComplate:
	case eNetMsgEveryDay:
		{
			VEC_EVERYDAY vecOld = getEveryDayTaskVec();
			clrEveryDayTask();
			
			CSJson::Value* ptempRoot = &root;
			if (unMsgCode == eNetMsgMissionSysDayTaskComplate)
			{
				ptempRoot = &root["arr"];
			}
            CSJson::Value& tempRoot = *ptempRoot;
            
			for (int i = 0; i < tempRoot.size(); i++) {
               
				CSJson::Value& val = tempRoot[i];
				int isGet = val["taskcomplete"].asInt();
				int kid = val["taskid"].asInt();
				int processVal = val["taskcurrentvalue"].asInt();
				SMeDalTaskData *medalinfo = CTaskMan::sharedInstance().getMedalTaskDataById(kid);
				CEveryDayCell cell;
				cell.setData(medalinfo);
				cell.setCounter(processVal);
				cell.setTaskComplete(isGet);
				cell.setTaskId(kid);
				cell.setGameId(GameShare_Global::shareGlobal()->gameType);
				bool isExist = false;
				int k = 0;
				for (; k < vecOld.size(); ++k){
					if(vecOld[k].getTaskId() == cell.getTaskId()&&vecOld[k].getGameId() == cell.getGameId()){
						isExist = true;
						break;
					}
				}
				if (isExist){
					//clent save data
					//cell.setCounter(vecOld[k].getCounter());
					cell.setPlayAni(vecOld[k].getPlayAni());
				}else{
					if (cell.isComplete()){
						cell.setPlayAni(false);
					}
				}
				addEveryDayTask(cell);
			}
		}
		break;
    case eNetMsgMissionSysWeek:{
            mVecWeekTask.clear();
            for (int i = 0; i < root.size(); ++i) {
                sWeekTask data;
                CSJson::Value& val = root[i];
                data.taskId = val["weektaskid"].asInt();
                data.typeId = val["weektaskcatalog"].asInt();

                data.taskName = val["weektaskname"].asCString();
                if (data.typeId == 20 || data.typeId == 21 || data.typeId == 22) {
                    CCString str;
                    sGameInfoData* gameData = CGameInfoMan::sharedInstance().getChgTempData(val["weektaskappendvalue"].asInt());
                    str.initWithFormat(val["weektaskname"].asCString(),gameData->gameName.c_str());
                    data.taskName = str.getCString();
                }
                data.taskValue = val["weektaskvalue"].asInt();
                data.taskAppendvalue = val["weektaskcompletevalue"].asInt();
                data.completeValue = val["isweektaskcomplete"].asInt();
                data.haveGetReward = val["weekgetreward"].asInt();
                mVecWeekTask.push_back(data);
            }
        
        }
            //发出消息.
            CCNotificationCenter::sharedNotificationCenter()->postNotification(kGetWeekTask, NULL);
            break;
    default:
        break;

	}
    
}
sTaskData* CTaskMan::getChgTempData(int nId)
{
	for (int i = 0; i < mVecTaskSystemData.size(); ++i)
	{
		if(mVecTaskSystemData[i].TaskId == nId)
		{
			return &mVecTaskSystemData[i];
		}
	}
	return NULL;
}
SMeDalTaskData*	CTaskMan::getMedalTaskDataById(int nTaskId){
	for (int i = 0; i < mVecTaskMedalData.size(); ++i){
		if(mVecTaskMedalData[i].TaskId == nTaskId){
			return &mVecTaskMedalData[i];
		}
	}
	return NULL;
}
void CTaskMan::addEveryDayTask(CEveryDayCell& Cell)
{
// 	CEveryDayCell* p = getEveryDayTask(Cell.getGameId(),Cell.getData()->TaskCatelog);
// 	if (p)
// 	{
// 		p->setCounter(Cell.getCounter());
// 		return;
// 	}
	mVecEveryInfo.push_back(Cell);
}
void CTaskMan::clrEveryDayTask(bool bAll)
{
	if(bAll)
		mVecEveryInfo.clear();
	else
	{
//		for (int i = 0; i < mVecEveryInfo.size();)
//		{
//			if(mVecEveryInfo[i].getData()->TaskRange == 1)
//			{
//				mVecEveryInfo.erase(mVecEveryInfo.begin() + i);
//			}else
//			{
//				++i;
//			}
//		}
	}
}

CEveryDayCell* CTaskMan::getEveryDayTask(int nGameId,int nTaskType)
{
	for (int i = 0; i < mVecEveryInfo.size(); ++i)
	{
		CEveryDayCell* p = &mVecEveryInfo[i];
		if(p->getData()->TaskCatelog == nTaskType && 
			p->getGameId() == nGameId)
			return p;
	}
	return NULL;
}
void CTaskMan::getEveryDayTaskByGamaId(VEC_EVERYDAYPTR& vecPtr,int nGameId)
{
	if(nGameId == -1)
	{
		nGameId = GameShare_Global::shareGlobal()->gameType ;
	}
	for (int i = 0; i < mVecEveryInfo.size(); ++i)
	{
		CEveryDayCell* p = &mVecEveryInfo[i];
		if(p->getGameId() == nGameId)
			vecPtr.push_back(p);
	}
}
bool CTaskMan::isNewDayTaskComplate(int nGameId)
{
	VEC_EVERYDAYPTR vec;
	getEveryDayTaskByGamaId(vec,nGameId);
	for (int i = 0; i < vec.size(); ++i)
	{
		if(vec[i]->getPlayAni())
			return true;
	}
	return false;
}
void CTaskMan::resetNewDayTask(int nGameId)
{
	VEC_EVERYDAYPTR vec;
	getEveryDayTaskByGamaId(vec,nGameId);
	for (int i = 0; i < vec.size(); ++i)
	{
		if(vec[i]->getPlayAni())
			vec[i]->setPlayAni(false);
	}
}
void CTaskMan::processEveryDayTask(int nTaskType,int nVal,int nGameId )
{
	if(nGameId == -1)
	{
		nGameId = GameShare_Global::shareGlobal()->gameType ;
	}
	CEveryDayCell* pCell = getEveryDayTask(nGameId,nTaskType);
	if (pCell)
	{
		if (pCell->isComplete())
			return;
		pCell->setCounter(nVal);
        CCLog("CTaskMan::processEveryDayTask: TaskId = %d,TaskCatelog = %d, Val = %d, GameId = %d",pCell->getData()->TaskId,nTaskType,nVal,nGameId);
		switch(pCell->getData()->TaskCatelog)
		{
		case eDayTaskTypeTK_59:
			{
				if (pCell->getCounter() <= pCell->getData()->TaskValue )
				{
					pCell->setTaskComplete(true);
					pCell->setPlayAni(true);
				}
			}
			break;
		default:{
				if (pCell->getCounter() >= pCell->getData()->TaskValue )
				{
					pCell->setTaskComplete(true);
					pCell->setPlayAni(true);
				}
			}
			break;
		}
		
	}else
	{

	}
}
void CTaskMan::processEveryDayTaskDelta(int nTaskType,int nDeltaVal,int nGameId )
{
	if(nGameId == -1)
	{
		nGameId = GameShare_Global::shareGlobal()->gameType ;
	}
	CEveryDayCell* pCell = getEveryDayTask(nGameId,nTaskType);
	if (pCell)
		processEveryDayTask(nTaskType,pCell->getCounter() + nDeltaVal,nGameId);
}
void CTaskMan::RequestGetReward(int nId)
{
	CSJson::Value msg_body;
	msg_body["taskid"] = CSJson::Value(nId);
	NetHttpClient::sendHttpRequest(eNetMsgTypeMissionSys,eNetMsgMissionSysTask,&msg_body);
}
void CTaskMan::requestDayTaskTemp()
{
	NetHttpClient::sendHttpRequest(eNetMsgTypeMissionSys,eNetMsgMissionSysDayTaskTemp);
}
void CTaskMan::requestDayTaskSelect(int nGameId)
{
	CSJson::Value msg_body;
	msg_body["gameid"] = CSJson::Value(nGameId);
	NetHttpClient::sendHttpRequest(eNetMsgTypeMissionSys,eNetMsgMissionSysDayTaskSelect, &msg_body);
}
void CTaskMan::requestWeekTaskTemp()
{
    	NetHttpClient::sendHttpRequest(eNetMsgTypeMissionSys,eNetMsgMissionSysWeek);
}
void CTaskMan::requestSaveDayTaskComplateState(int nGameId)
{
	if(nGameId == -1)
	{
		nGameId = GameShare_Global::shareGlobal()->gameType ;
	}
	VEC_EVERYDAYPTR vec;
	CSJson::Value arr;
	CSJson::Value msg_body;
	getEveryDayTaskByGamaId(vec,nGameId);
	for (int i = 0; i < vec.size(); ++i)
	{
		CSJson::Value cell;
		cell["taskcurrentvalue"] = CSJson::Value(vec[i]->getCounter());
		cell["taskid"] = CSJson::Value(vec[i]->getTaskId());
		msg_body["arr"].append(cell);
        //vec[i]->setPlayAni(true);
	}
	msg_body["gameid"] = CSJson::Value(nGameId);
	/*msg_body[""] = msg_arr;*/
	NetHttpClient::sendHttpRequest(eNetMsgTypeMissionSys,eNetMsgMissionSysDayTaskComplate, &msg_body);
}
void CTaskMan::requestDayTasklst(int nGameId)
{
    if(nGameId == -1)
	{
		nGameId = GameShare_Global::shareGlobal()->gameType ;
	}
   
    CSJson::Value msg_body;
    msg_body["gameid"] = CSJson::Value(nGameId);
    NetHttpClient::sendHttpRequest(eNetMsgTypeMissionSys, eNetMsgEveryDay, &msg_body);
}