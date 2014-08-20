/********************************************************************
	created:	2014/03/28 
	filename: 	CsvNpcData.h
	author:		王少培
	purpose:	
*********************************************************************/
#include "CsvNpcData.h"
#include "CsvParser.h"
#include <iostream>
#include <string>

using namespace std;

CCsvNpcData::CCsvNpcDataRowLoader::CCsvNpcDataRowLoader(NpcDataMap &Datas): m_Datas(Datas) {
}

bool CCsvNpcData::CCsvNpcDataRowLoader::loadRow(CCsvParser *pParser) {
  assert(pParser != NULL);
  CCsvParser &parser = *pParser;
  SCsvNpcData data;
  parser >> data.m_nID;
  parser >> data.m_nHead;
  parser >> data.m_nBody;
  parser >> data.m_nAct;
  parser >> data.m_nSlot;
  parser >> data.m_strName;
  parser >> data.m_nLv;
  parser >> data.m_nQuality;

  if (pParser->isBad()) {
    return false;
  }

  m_Datas.insert(std::make_pair(data.m_nID, data));
  return true;
}

bool CCsvNpcData::load(CCsvLoader *pLoader) {
  CCsvNpcDataRowLoader rowLoader(m_Datas);
  std::string strPath = getCsvPath();
  return pLoader->loadCsvFile(strPath, &rowLoader);
}

const NpcDataMap &CCsvNpcData::geNpcs() const {
  return m_Datas;
}

const SCsvNpcData *CCsvNpcData::getNpc(int nID) const {
  const SCsvNpcData *pNpc = NULL;
  NpcDataMap::const_iterator iterFind = m_Datas.find(nID);

  if (iterFind != m_Datas.end()) {
    pNpc = &(iterFind->second);
  }

  return pNpc;
}
