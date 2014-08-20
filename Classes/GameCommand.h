
/***************************************************************
* 
*
*  作者：		王少培
*  文件名：		CGameTimer.cpp
*  创建时间：	
*
***************************************************************/
#ifndef __CGameCommand_H__
#define __CGameCommand_H__
#include <string>
#include "cocos2d.h"

USING_NS_CC;
//命令
class CGameCommand
{
public:

	// 构造函数
	CGameCommand(unsigned int startTime, unsigned int duringTime);
	// 析构函数
	virtual ~CGameCommand();
	// 生成执行指令
	virtual void Execute();
	// 获取时间
	unsigned int GetStartTime() const;
	// 获取持续时间
	unsigned int GetDuringTime() const;
	// 获取开始时间
	unsigned int GetEndTime() const;
	// 判断是否结束
	bool IsDone() const;
	// 设置命令结束
	void SetDone(bool bDone);

protected:

	unsigned int				mStartTime;			// 开始时间
	unsigned int				mDuringTime;		// 持续时间
	unsigned int				mEndTime;			// 结束时间
	bool				mDone;				// 结束标志，执行过一次标志设置为 true
};
#endif