/********************************************************************
	created:	2014/03/28 
	filename: 	CsvStringData.h
	author:		王少培
	purpose:	
*********************************************************************/
#include "CsvParser.h"
#include <iostream>
#include <string>
#include "CsvStringData.h"

using namespace std;

CCsvStringData::CCsvStringDataRowLoader::CCsvStringDataRowLoader(StringDataMap &Datas): m_Datas(Datas) {
}

bool CCsvStringData::CCsvStringDataRowLoader::loadRow(CCsvParser *pParser) {
  assert(pParser != NULL);
  CCsvParser &parser = *pParser;
  SCsvStringData data;
  parser >> data.mID;
  parser >> data.mstrData;

  if (pParser->isBad()) {
    return false;
  }

  m_Datas.insert(std::make_pair(data.mID, data));
  return true;
}

bool CCsvStringData::load(CCsvLoader *pLoader) {
  CCsvStringDataRowLoader rowLoader(m_Datas);
  std::string strPath = getCsvPath();
  return pLoader->loadCsvFile(strPath, &rowLoader);
}

const StringDataMap &CCsvStringData::getSrings() const {
  return m_Datas;
}

const char* CCsvStringData::getString(int nID) const {
  StringDataMap::const_iterator iterFind = m_Datas.find(nID);

  if (iterFind != m_Datas.end()) {
	  return (iterFind->second).mstrData.c_str();
  }
  return NULL;
}
