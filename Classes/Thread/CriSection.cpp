/********************************************************************
	created:	2014/04/01 
	filename: 	CriSection.h
	author:		王少培
	purpose:	
*********************************************************************/
#include "CriSection.h"

CriSectionLock::CriSectionLock()
{
	pthread_mutex_init(&mMutex,NULL);
}

CriSectionLock::~CriSectionLock()
{
	pthread_mutex_destroy(&mMutex);
}

void CriSectionLock::enter()
{
	pthread_mutex_lock(&mMutex);
}

void CriSectionLock::leave()
{
	pthread_mutex_unlock(&mMutex);
}
