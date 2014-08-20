/***************************************************************
* 
*
*  作者：		王少培
*  文件名：		CMyTimer.cpp
*  创建时间：	
*
***************************************************************/
#ifndef __CGameScheduler_H__
#define __CGameScheduler_H__

#include <list>
#include "GameCommon.h"

USING_NS_CC;

class CGameCommand;
class CGameFruit;
// 调度器
class CGameScheduler
{
	// 生命单件
	DECLARE_SINGLETON(CGameScheduler, ms_instance)

public:

	// 构造函数
	CGameScheduler();
	// 析构函数
	~CGameScheduler();

	// 清空所有命令
	void Clear();
	// 删除所有命令
	void DestroyAllCommands();
	// 添加命令
	void AddCommand(CGameCommand* pCommand);
	// 删除命令
	void DestroyCommand(CGameCommand* pCommand);
	// 是否还有命令
	bool IsEmpty() const;
	// 更新时间
	void Update();

private:

	// 执行命令
	void _ExecuteCommands(unsigned int dwNowTime);
	// 清空过期命令
	void _ClearExpireCommands(unsigned int dwNowTime);

private:

	typedef std::list<CGameCommand*>		CommandList;
	typedef std::map<unsigned int, CommandList>		CommandListMap;
	CommandListMap			mCommandLists;		// 命令列表
	unsigned int					mNowTime;			// 当前时间

};






#endif