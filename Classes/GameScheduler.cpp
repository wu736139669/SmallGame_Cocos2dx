/***************************************************************
* 
*
*  ���ߣ�		������
*  �ļ�����		CMyTimer.cpp
*  ����ʱ�䣺	
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
	// ��ȡ��ǰʱ��
	unsigned int dwNowTime = CGameTimer::GetInstance()->GetNowTime();
	// ���������ɵ�����
	_ClearExpireCommands(dwNowTime);
	// ִ������
	_ExecuteCommands(CGameTimer::GetInstance()->GetNowTime());
	
}

void CGameScheduler::_ExecuteCommands( unsigned int dwNowTime )
{
	CommandList execList;

	// ����Ҫִ�е����������
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


	// ִ������
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
	// ���¶���
	CommandList clearList;

	// ����Ҫִ�е����������
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
			// �������, ��ӵ�ɾ������
			if (pCommand->IsDone())
			{
				clearList.push_back(pCommand);
			}
		}
	}

	// ������е�������
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






