/********************************************************************
	created:	2014/03/28 
	filename: 	CsvBase.h
	author:		王少培
	purpose:	
*********************************************************************/
#ifndef __BRCSVLOADER_H__
#define __BRCSVLOADER_H__

#include <string>
#include <vector>

class CCsvParser;
class CCsvRowLoader {
public:
	virtual ~CCsvRowLoader() {
	}
	virtual bool loadRow(CCsvParser *pParser) = 0;
};

class CCsvLoader {
	CCsvParser *m_pParser;

public:
	CCsvLoader();
	~CCsvLoader();

	bool loadCsvFile(const std::string& strFileName,
			CCsvRowLoader *pRowLoader);
};

#endif
