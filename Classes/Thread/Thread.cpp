/********************************************************************
	created:	2014/04/01 
	filename: 	Thread.h
	author:		王少培
	purpose:	
*********************************************************************/

#include "Thread.h"
#include "ccMacros.h"
#include "pthread.h"

void* threadFunc(void *arg)
{
	CRunable* pThread = (CRunable*)arg;
	pThread->run();
    pthread_exit(NULL);
	return 0;
}

void CRunable::start()
{
	int nResult=0;
	pthread_t thread;
	if(nResult = pthread_create(&thread,NULL,threadFunc,this))
	{
		CCLOG("thread create failed: %d\n",nResult);
	}
    pthread_detach(thread);
	//pthread_join(thread,NULL);
}
