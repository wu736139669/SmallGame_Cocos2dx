
#ifndef __CGameTimer_H__
#define __CGameTimer_H__

#include "GameCommon.h"

class CGameTimer
{
	DECLARE_SINGLETON(CGameTimer, ms_instance)

public:

	// ���캯��
	CGameTimer();
	// ��������
	~CGameTimer();
	// ��ȡ��ǰʱ��
	unsigned int GetNowTime() const;
	// ����ʱ��
	void ResetTime();
	// ����
	void Update(unsigned int deltaTime);

private:

	unsigned int		mTimeCounter;		// ��ʱ
};








#endif