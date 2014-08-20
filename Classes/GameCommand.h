
/***************************************************************
* 
*
*  ���ߣ�		������
*  �ļ�����		CGameTimer.cpp
*  ����ʱ�䣺	
*
***************************************************************/
#ifndef __CGameCommand_H__
#define __CGameCommand_H__
#include <string>
#include "cocos2d.h"

USING_NS_CC;
//����
class CGameCommand
{
public:

	// ���캯��
	CGameCommand(unsigned int startTime, unsigned int duringTime);
	// ��������
	virtual ~CGameCommand();
	// ����ִ��ָ��
	virtual void Execute();
	// ��ȡʱ��
	unsigned int GetStartTime() const;
	// ��ȡ����ʱ��
	unsigned int GetDuringTime() const;
	// ��ȡ��ʼʱ��
	unsigned int GetEndTime() const;
	// �ж��Ƿ����
	bool IsDone() const;
	// �����������
	void SetDone(bool bDone);

protected:

	unsigned int				mStartTime;			// ��ʼʱ��
	unsigned int				mDuringTime;		// ����ʱ��
	unsigned int				mEndTime;			// ����ʱ��
	bool				mDone;				// ������־��ִ�й�һ�α�־����Ϊ true
};
#endif