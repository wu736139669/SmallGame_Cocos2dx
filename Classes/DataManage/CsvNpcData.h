#ifndef __CSVNPCDATA_H__
#define __CSVNPCDATA_H__

#include "CsvBase.h"
#include "CsvLoader.h"
struct SCsvNpcData {
  int m_nID;
  int m_nHead;
  int m_nBody;
  int m_nAct;
  int m_nSlot;
  int m_nLv;
  int m_nQuality;
  std::string m_strName;
};
typedef std::vector<SCsvNpcData> NpcDataVector;
typedef std::map<int, SCsvNpcData> NpcDataMap;

class CCsvNpcData: public CUniqueDataT<CCsvNpcData, CCsvBase> {
  NpcDataMap m_Datas;

  class CCsvNpcDataRowLoader: public CCsvRowLoader {
    NpcDataMap& m_Datas;
  public:
    CCsvNpcDataRowLoader(NpcDataMap& Datas);

    virtual bool loadRow(CCsvParser *pParser);
  };

public:
  bool load(CCsvLoader *pLoader);

  const NpcDataMap& geNpcs() const;
  const SCsvNpcData* getNpc( int nID ) const;
};

#endif
