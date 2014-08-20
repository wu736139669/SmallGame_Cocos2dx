
#ifndef __CGameTimer_H__
#define __CGameTimer_H__

#include "GameCommon.h"

class CGameTimer
{
	DECLARE_SINGLETON(CGameTimer, ms_instance)

public:

	// 构造函数
	CGameTimer();
	// 析构函数
	~CGameTimer();
	// 获取当前时间
	unsigned int GetNowTime() const;
	// 重置时间
	void ResetTime();
	// 更新
	void Update(unsigned int deltaTime);

private:

	unsigned int		mTimeCounter;		// 记时
};








#endif