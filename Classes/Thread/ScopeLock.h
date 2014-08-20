/********************************************************************
	created:	2014/04/01 
	filename: 	ScopeLock.h
	author:		王少培
	purpose:	
*********************************************************************/
#ifndef __SCOPELOCK_H__
#define __SCOPELOCK_H__

class Lock
{
public:
	Lock() {}
	virtual ~Lock() {}

public:
	virtual void enter() = 0;

	virtual void leave() = 0;
};

class ScopeLock
{
public:
	ScopeLock(Lock& lock) : mLock(lock)
	{
		mLock.enter();
	}

	~ScopeLock()
	{
		mLock.leave();
	}

private:
	Lock& mLock;
};



#endif //__SCOPELOCK_H__