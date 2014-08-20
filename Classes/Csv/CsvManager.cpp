/********************************************************************
	created:	2014/03/28 
	filename: 	CsvBase.h
	author:		王少培
	purpose:	
*********************************************************************/
#include "CsvManager.h"
#include "CsvLoader.h"
#include "CsvBase.h"
#include "CsvStringData.h"

#define REGIST_CSV(dataType, tableName) this->addData(new dataType, tableName)

bool CCsvManager::loadAllCsv() {
  CCsvLoader csvLoader;
  DataVector::iterator iteEnd = m_Datas.end();

  for (DataVector::iterator ite = m_Datas.begin(); ite != m_Datas.end();
       ++ite) {
    if (!static_cast<CCsvBase *>(*ite)->load(&csvLoader))
      return false;
  }

  return true;
}

void CCsvManager::registDatas() {
   REGIST_CSV(CCsvStringData, "csv/zhStringData.csv");
}

bool CCsvManager::reloadCsvTable( const char* sztableName )
{
	CCsvLoader csvLoader;
	DataVector::iterator iter = m_Datas.begin();
	for (; iter != m_Datas.end(); iter++)
	{
		CCsvBase* pBase = static_cast<CCsvBase*>(*iter);
		if(pBase && !pBase->strTableName.compare(sztableName))
		{
			pBase->load(&csvLoader);
			return true;
		}
	}
	return false;
}
