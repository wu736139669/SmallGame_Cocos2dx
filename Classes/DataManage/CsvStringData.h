#ifndef __CSVSTRINGDATA_H__
#define __CSVSTRINGDATA_H__

#include "CsvBase.h"
#include "CsvLoader.h"
#include "CsvManager.h"
#define GET_STRING_CSV(id) GET_CSV(CCsvStringData)->getString(id)
struct SCsvStringData {
  unsigned int mID;
  std::string mstrData;
};
typedef std::map<int, SCsvStringData> StringDataMap;

class CCsvStringData: public CUniqueDataT<SCsvStringData, CCsvBase> {
  StringDataMap m_Datas;

  class CCsvStringDataRowLoader: public CCsvRowLoader {
    StringDataMap& m_Datas;
  public:
    CCsvStringDataRowLoader(StringDataMap& Datas);

    virtual bool loadRow(CCsvParser *pParser);
  };

public:
  bool load(CCsvLoader *pLoader);

  const StringDataMap& getSrings() const;
  const char* getString(int nID) const;
};

#endif
