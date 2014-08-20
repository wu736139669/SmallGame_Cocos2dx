/***************************************************************
* 
*
*  ���ߣ�		������
*  �ļ�����		CMyTimer.cpp
*  ����ʱ�䣺	
*
***************************************************************/
#ifndef __CGameScheduler_H__
#define __CGameScheduler_H__

#include <list>
#include "GameCommon.h"

USING_NS_CC;

class CGameCommand;
class CGameFruit;
// ������
class CGameScheduler
{
	// ��������
	DECLARE_SINGLETON(CGameScheduler, ms_instance)

public:

	// ���캯��
	CGameScheduler();
	// ��������
	~CGameScheduler();

	// �����������
	void Clear();
	// ɾ����������
	void DestroyAllCommands();
	// �������
	void AddCommand(CGameCommand* pCommand);
	// ɾ������
	void DestroyCommand(CGameCommand* pCommand);
	// �Ƿ�������
	bool IsEmpty() const;
	// ����ʱ��
	void Update();

private:

	// ִ������
	void _ExecuteCommands(unsigned int dwNowTime);
	// ��չ�������
	void _ClearExpireCommands(unsigned int dwNowTime);

private:

	typedef std::list<CGameCommand*>		CommandList;
	typedef std::map<unsigned int, CommandList>		CommandListMap;
	CommandListMap			mCommandLists;		// �����б�
	unsigned int					mNowTime;			// ��ǰʱ��

};






#endif