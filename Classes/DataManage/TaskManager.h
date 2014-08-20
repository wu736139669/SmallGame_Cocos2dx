//
//  TaskManager.h
//  OnceAgain
//
//  Created by mac on 14-4-3.
//  任务表管理.
//

#ifndef __OnceAgain__TaskManager__
#define __OnceAgain__TaskManager__

#include "cocos2d.h"
#include <string>
#include "Singleton.h"
#include "JsonHelper.h"
class CBasePacket;
enum e_TaskId {
    TaskId_1 = 1,
    TaskId_2,
    TaskId_3,
    TaskId_4,
    TaskId_5,
    TaskId_6,
    TaskId_7,
};
struct sTaskData
{
	int TaskId;
	std::string TaskName;
    std::string TaskDetail;
    std::string TaskImg;
	int TaskRewardType;
	int TaskRewardId;
	int TaskRewardValue;
};
typedef std::vector<sTaskData> VEC_TASKSYSTEMDATA;

struct SMeDalTaskData
{
	int TaskId;
	std::string TaskName;
	std::string TaskDetail;
	int TaskImg;
	int TaskRewardType;
	int TaskRewardId;
	int TaskRewardValue;
	int TaskDifficulty;
	int TaskValue;
	int TaskCatelog;
	int TaskRange;
};
typedef std::vector<SMeDalTaskData> VEC_MEDALTASKDATA;

//周任务类型.
enum eWeekType {
    weekType1 = 20,
    weekType2 = 21,
    weekType3 = 22,
    weekType4 = 23,
    weekType5 = 24,
    weekType6 = 25,
    weekType7 = 26,
    weekType8 = 27,
    weekType9 = 28,
    };
struct sWeekTask {
    int taskId;
    int typeId;
    std::string taskName;
    int taskValue; //总值
    int completeValue; //是否完成
    bool isComplete;
    int taskAppendvalue;  //当前完成数值
    int haveGetReward;
};
typedef std::vector<sWeekTask> VEC_SWEEKTASK;
class CEveryDayCell
{
public:
	CEveryDayCell():mnCounter(0),mnTaskComplete(0),mnTaskId(0),mnGameId(0),mbPlayAni(false)
	{}
public:
	bool isComplete();
	void process();
	CC_SYNTHESIZE(SMeDalTaskData*,mpData,Data);
	CC_SYNTHESIZE(int,mnCounter,Counter);
	CC_SYNTHESIZE(int,mnTaskComplete,TaskComplete);
	CC_SYNTHESIZE(int,mnTaskId,TaskId);
	CC_SYNTHESIZE(int,mnGameId,GameId);
	CC_SYNTHESIZE(bool,mbPlayAni,PlayAni);
};
typedef std::vector<CEveryDayCell> VEC_EVERYDAY;
typedef std::vector<CEveryDayCell*> VEC_EVERYDAYPTR;
class CTaskMan :public CSingleton<CTaskMan>
{
public:
	CTaskMan();
	~CTaskMan();
public:
	virtual void reset();
	virtual void resetInside();
	//网络解析
	void parseNetData(CBasePacket* pBasePacket);

	VEC_TASKSYSTEMDATA& getMoneyChgTmpData(){return mVecTaskSystemData;};
	VEC_MEDALTASKDATA& getMedalTaskData(){return mVecTaskMedalData;}
    VEC_SWEEKTASK& getWeekTaskData(){return mVecWeekTask;}
	//取得每日游戏勋章任务模板数据
	SMeDalTaskData*	getMedalTaskDataById(int nTaskId);
	//
	sTaskData* getChgTempData(int nId);
	//
	void addEveryDayTask(CEveryDayCell& pCell);
	//
	void processEveryDayTask(int nTaskType,int nVal = 1,int nGameId = -1);
	//
	void processEveryDayTaskDelta(int nTaskType,int nDeltaVal = 1,int nGameId = -1);
	//
	CEveryDayCell* getEveryDayTask(int nGameId,int nTaskType);
	//
	void clrEveryDayTask(bool bAll = true);
	//
	void getEveryDayTaskByGamaId(VEC_EVERYDAYPTR& vecPtr,int nGameId = -1);
	//
	VEC_EVERYDAY& getEveryDayTaskVec(){return mVecEveryInfo;};
	//
	bool isNewDayTaskComplate(int nGameId);
	//
	void resetNewDayTask(int nGameId);
	

	 //获取任务奖励
    void RequestGetReward(int nId);      
	//请求每日游戏勋章任务模板
	void requestDayTaskTemp();
	//请求每日随机到游戏勋章任务
	void requestDayTaskSelect(int nGameId);
    //请求获取周任务.
    void requestWeekTaskTemp();
	//请求保存每日任务完成状态
	void requestSaveDayTaskComplateState(int nGameId = -1);
    //请求每日任务列表
    void requestDayTasklst(int nGameId = -1);
    //
    void setAddMoney(int number){addMoney = number;};
    int getAddMoney(){return addMoney;};
protected:
	VEC_TASKSYSTEMDATA mVecTaskSystemData;//每日任务模版
	VEC_MEDALTASKDATA mVecTaskMedalData;//勋章任务数据
    VEC_SWEEKTASK mVecWeekTask;//周任务模版
	VEC_EVERYDAY mVecEveryInfo;
    int addMoney;
};
#endif /* defined(__OnceAgain__TaskManager__) */
