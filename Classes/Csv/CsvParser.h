/********************************************************************
	created:	2014/03/28 
	filename: 	BRCsvBase.h
	author:		王少培
	purpose:	
*********************************************************************/
#ifndef __BRCSVPARSER_H__
#define __BRCSVPARSER_H__

#include <string>

class CCsvParser {
private:
	bool m_bGood;
	unsigned int m_nCol;
	std::string m_sData;
	std::string::size_type m_nPos;
	void skipSpaces(void);
public:
	CCsvParser();
	const CCsvParser &operator <<(const std::string &In);
	const CCsvParser &operator <<(const char *In);
	CCsvParser &operator >>(int &Out);
	CCsvParser &operator >>(unsigned int &Out);
	CCsvParser &operator >>(float &Out);
	CCsvParser &operator >>(bool &Out);
	CCsvParser &operator >>(std::string &Out);
	bool isGood() const;
	bool isBad() const;
	unsigned int getErrorCol() const;
};

#endif
