/********************************************************************
	created:	2014/04/01 
	filename: 	Thread.h
	author:		王少培
	purpose:	
*********************************************************************/
#ifndef __THREAD_H__
#define __THREAD_H__

class CRunable
{
public:
	CRunable() {}

	virtual ~CRunable() {}

public:
	virtual void start();

	virtual void stop() {};

	virtual void run() = 0;
};


#endif //__THREAD_H__