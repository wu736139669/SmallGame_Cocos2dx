/********************************************************************
	created:	2014/03/28 
	filename: 	CsvBase.h
	author:		王少培
	purpose:	
*********************************************************************/
#ifndef __BRCSVMANAGER_H__
#define __BRCSVMANAGER_H__

#include "Singleton.h"
#include "UniqueData.h"

class CCsvManager: public CUniqueDataSet, public CSingleton<CCsvManager> {
public:
	void registDatas();
	bool loadAllCsv();	

	// 重新加载csv表
	bool reloadCsvTable(const char* sztableName);
};

#define GET_CSV(type) static_cast<type *>(CCsvManager::sharedInstance().getData(type::s_nID))

#endif
