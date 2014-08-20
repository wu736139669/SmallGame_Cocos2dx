/********************************************************************
	created:	2014/03/28 
	filename: 	BRCsvBase.h
	author:		王少培
	purpose:	
*********************************************************************/
#ifndef __BRUNIQUEDATA_H__
#define __BRUNIQUEDATA_H__
#include <map>
#include <assert.h>
#include <vector>
#include <string>

class CUniqueDataBase {
public:
  unsigned int *m_pID;
  std::string strTableName;		
  CUniqueDataBase()
    : m_pID(NULL)
	, strTableName("")
  {}
  virtual ~CUniqueDataBase() {}
};

template<class TDataDerived, class TDataBase>
class CUniqueDataT
    : public TDataBase {
public:
  static unsigned int s_nID;
  CUniqueDataT() {
    TDataBase::m_pID = &s_nID;
  }
};

template<class TDataDerived, class TDataBase>
unsigned int CUniqueDataT<TDataDerived, TDataBase>::s_nID = -1;

class CUniqueDataSet {
protected:
  typedef std::vector<CUniqueDataBase *> DataVector;
  DataVector m_Datas;

public:
  CUniqueDataSet() {
  }
  ~CUniqueDataSet() {
    for (DataVector::iterator iter = m_Datas.begin();
         iter != m_Datas.end(); ++iter) {
      delete *iter;
    }
  }

  void addData(CUniqueDataBase *pData, const char* tableName) {
    assert(pData != NULL);
	assert(tableName != NULL);
    assert(*pData->m_pID == -1 || *pData->m_pID == m_Datas.size());
    *pData->m_pID = static_cast<unsigned int>(m_Datas.size());
	pData->strTableName = tableName;
    m_Datas.push_back(pData);
  }

  CUniqueDataBase *getData(unsigned int nID) {
    assert(nID < m_Datas.size());
    return m_Datas[nID];
  }
};
#endif