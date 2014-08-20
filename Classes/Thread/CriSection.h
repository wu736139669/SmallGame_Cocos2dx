/********************************************************************
	created:	2014/04/01 
	filename: 	CriSection.h
	author:		王少培
	purpose:	
*********************************************************************/
#ifndef __CRISECTION_H__
#define __CRISECTION_H__

#include "ScopeLock.h"
#include "pthread.h"
class CriSectionLock : public Lock
{
public:
	CriSectionLock();

	virtual ~CriSectionLock();

public:
	virtual void enter();

	virtual void leave();

private:
	pthread_mutex_t mMutex;
};

#endif 