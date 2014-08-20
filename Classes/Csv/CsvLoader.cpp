/********************************************************************
	created:	2014/03/28 
	filename: 	CsvBase.h
	author:		王少培
	purpose:	
*********************************************************************/

#include "CsvLoader.h"
#include "CsvParser.h"
#include <iostream>
#include <assert.h>
#include <fstream>
#include <iosfwd>

using namespace std;

CCsvLoader::CCsvLoader() {
	m_pParser = new CCsvParser;
}

CCsvLoader::~CCsvLoader() {
	delete m_pParser;
}

bool CCsvLoader::loadCsvFile(const std::string& strFileName,
		CCsvRowLoader *pRowLoader) {
	assert(pRowLoader != NULL);

	ifstream infile(strFileName.c_str());
	if (!infile) {
		infile.close();
		cout << "open file error! " << strFileName << endl;
		return false;
	}
  cout << "open file ok! " << strFileName << endl;

	unsigned int nCurRow = 0;
	string strRow;
	while (getline(infile, strRow)) {
		strRow.erase(0, strRow.find_first_not_of("\\t\\n\\r")).erase(
				strRow.find_last_not_of("\\t\\n\\r") + 1);

		if (strRow.find_first_of("//") != 0) {
			(*m_pParser) << strRow;
			if (!pRowLoader->loadRow(m_pParser)) {
				cout << "parse file error! " << strFileName << " at row "
						<< nCurRow << endl;
			}

		}
		++nCurRow;
	}

	infile.close();
	return true;
}
