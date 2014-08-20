/***************************************************************
* 
*
*  作者：		王少培
*  文件名：		CMyTimer.cpp
*  创建时间：	
*
***************************************************************/
#include "GameCommand.h"
#include "GameTimer.h"
#include <algorithm>
#include "GameFruitField.h"
#include "FruitCommand.h"
#include "GameScheduler.h"

IMPLEMENT_SINGLETON(CGameScheduler, ms_instance)


CGameScheduler::CGameScheduler()
{

}


CGameScheduler::~CGameScheduler()
{
	DestroyAllCommands();
}

void CGameScheduler::AddCommand( CGameCommand* pCommand )
{
	if (pCommand == NULL)
		return;

	unsigned int dwStartTime = pCommand->GetStartTime();
	
	if (mCommandLists.find(dwStartTime) != mCommandLists.end())
	{
		CommandList& rList = mCommandLists[dwStartTime];
		rList.push_back(pCommand);
	}
	else
	{
		CommandList list;
		list.push_back(pCommand);
		mCommandLists[dwStartTime] = list;
	}
}

void CGameScheduler::DestroyCommand( CGameCommand* pCommand )
{
	if (pCommand == NULL)
		return;

	unsigned int dwStartTime = pCommand->GetStartTime();

	if (mCommandLists.find(dwStartTime) != mCommandLists.end())
	{
		CommandList& rList = mCommandLists[dwStartTime];
		CommandList::iterator it = std::find(rList.begin(), rList.end(), pCommand);
		if (it != rList.end())
		{
			rList.erase(it);
			CC_SAFE_DELETE(pCommand);
			if (rList.empty())
			{
				mCommandLists.erase(dwStartTime);
			}
		}
	}
}

void CGameScheduler::Update()
{
	// 获取当前时间
	unsigned int dwNowTime = CGameTimer::GetInstance()->GetNowTime();
	// 清空所有完成的命令
	_ClearExpireCommands(dwNowTime);
	// 执行命令
	_ExecuteCommands(CGameTimer::GetInstance()->GetNowTime());
	
}

void CGameScheduler::_ExecuteCommands( unsigned int dwNowTime )
{
	CommandList execList;

	// 把需要执行的命令进队列
	CGameCommand* pCommand = NULL;
	CommandList::iterator listIt;
	CommandList::iterator listIe;
	CommandListMap::iterator mapIt = mCommandLists.begin();
	CommandListMap::iterator mapIe = mCommandLists.end();
	for( ; mapIt != mapIe; ++mapIt )
	{
		if (mapIt->first <= dwNowTime)
		{
			CommandList& cmdList = mapIt->second;
			listIt = cmdList.begin();
			listIe = cmdList.end();
			for( ; listIt != listIe; ++listIt )
			{
				pCommand = *listIt;
				if (pCommand->IsDone())
					continue;
				execList.push_back(pCommand);
			}
		}
		else
		{
			break;
		}
	}


	// 执行命令
	listIt = execList.begin();
	listIe = execList.end();
	for( ; listIt != listIe; ++listIt )
	{
		pCommand = *listIt;
		pCommand->Execute();
		pCommand->SetDone(true);
	}
}

void CGameScheduler::_ClearExpireCommands( unsigned int dwNowTime )
{
	// 更新队列
	CommandList clearList;

	// 把需要执行的命令进队列
	CGameCommand* pCommand = NULL;
	CommandList::iterator listIt;
	CommandList::iterator listIe;
	CommandListMap::iterator mapIt = mCommandLists.begin();
	CommandListMap::iterator mapIe = mCommandLists.end();
	for( ; mapIt != mapIe; ++mapIt )
	{
		CommandList& cmdList = mapIt->second;
		listIt = cmdList.begin();
		listIe = cmdList.end();
		for( ; listIt != listIe; ++listIt )
		{
			pCommand = *listIt;
			// 命令结束, 添加到删除队列
			if (pCommand->IsDone())
			{
				clearList.push_back(pCommand);
			}
		}
	}

	// 清楚所有到期命令
	listIt = clearList.begin();
	listIe = clearList.end();
	for( ; listIt != listIe; ++listIt )
	{
		pCommand = *listIt;
		DestroyCommand(pCommand);
	}
	clearList.clear();
}

bool CGameScheduler::IsEmpty() const
{
	return mCommandLists.empty();
}

void CGameScheduler::Clear()
{
	CGameCommand* pCommand = NULL;
	CommandList::iterator listIt;
	CommandList::iterator listIe;
	CommandListMap::iterator mapIt = mCommandLists.begin();
	CommandListMap::iterator mapIe = mCommandLists.end();
	for( ; mapIt != mapIe; ++mapIt )
	{
		listIt = mapIt->second.begin();
		listIe = mapIt->second.end();
		for( ; listIt != listIe; ++listIt )
		{
			pCommand = *listIt;
			pCommand->SetDone(true);
		}
	}
}

void CGameScheduler::DestroyAllCommands()
{
	CGameCommand* pCommand = NULL;
	CommandList::iterator listIt;
	CommandList::iterator listIe;
	CommandListMap::iterator mapIt = mCommandLists.begin();
	CommandListMap::iterator mapIe = mCommandLists.end();
	for( ; mapIt != mapIe; ++mapIt )
	{
		listIt = mapIt->second.begin();
		listIe = mapIt->second.end();
		for( ; listIt != listIe; ++listIt )
		{
			pCommand = *listIt;
			CC_SAFE_DELETE(pCommand);
		}
		mapIt->second.clear();
	}
	mCommandLists.clear();
}






