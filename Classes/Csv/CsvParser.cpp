/********************************************************************
	created:	2014/03/28 
	filename: 	CsvBase.h
	author:		王少培
	purpose:	
*********************************************************************/
#include <iostream>
#include <cstdlib>
#include "CsvParser.h"
using namespace std;

CCsvParser::CCsvParser() {
  m_sData = "";
  m_nPos = 0;
  m_nCol = 0;
  m_bGood = true;
}

void CCsvParser::skipSpaces(void) {
  while (m_nPos < m_sData.length() && m_sData[m_nPos] == ' ')
    m_nPos++;
}

const CCsvParser &CCsvParser::operator <<(const string &In) {
  this->m_sData = In;
  this->m_nPos = 0;
  this->m_nCol = 0;
  this->m_bGood = true;
  return *this;
}

const CCsvParser &CCsvParser::operator <<(const char *In) {
  this->m_sData = In;
  this->m_nPos = 0;
  this->m_nCol = 0;
  this->m_bGood = true;
  return *this;
}

CCsvParser &CCsvParser::operator >>(int &Out) {
  if (!m_bGood)
    return *this;

  string sTmp = "";
  skipSpaces();

  while (m_nPos < m_sData.length() && m_sData[m_nPos] != ',')
    sTmp += m_sData[m_nPos++];

  m_nPos++; // skip past comma

  if (sTmp.empty()) {
    m_bGood = false;
  } else {
    ++m_nCol;
    m_bGood = true;
    Out = atoi(sTmp.c_str());
  }

  return *this;
}

CCsvParser &CCsvParser::operator >>(float &Out) {
  if (!m_bGood)
    return *this;

  string sTmp = "";
  skipSpaces();

  while (m_nPos < m_sData.length() && m_sData[m_nPos] != ',')
    sTmp += m_sData[m_nPos++];

  m_nPos++; // skip past comma

  if (sTmp.empty()) {
    m_bGood = false;
  } else {
    ++m_nCol;
    m_bGood = true;
    Out = atof(sTmp.c_str());
  }

  return *this;
}

CCsvParser &CCsvParser::operator >>(string &Out) {
  if (!m_bGood)
    return *this;

  bool bQuotes = false;
  Out = "";
  skipSpaces();

  // Jump past first " if necessary
  if (m_nPos < m_sData.length() && m_sData[m_nPos] == '"') {
    bQuotes = true;
    m_nPos++;
  }

  while (m_nPos < m_sData.length()) {
    if (!bQuotes && m_sData[m_nPos] == ',')
      break;

    if (bQuotes && m_sData[m_nPos] == '"') {
      if (m_nPos + 1 >= m_sData.length() - 1)
        break;

      if (m_sData[m_nPos + 1] == ',')
        break;
    }

    Out += m_sData[m_nPos++];
  }

  // Jump past last " if necessary
  if (bQuotes && m_nPos < m_sData.length() && m_sData[m_nPos] == '"')
    m_nPos++;

  // Jump past , if necessary
  if (m_nPos < m_sData.length() && m_sData[m_nPos] == ',')
    m_nPos++;

  if (Out.empty()) {
    m_bGood = false;
  } else {
    ++m_nCol;
    m_bGood = true;
  }

  return *this;
}

CCsvParser &CCsvParser::operator >>(unsigned int &Out) {
  if (!m_bGood)
    return *this;

  string sTmp = "";
  skipSpaces();

  while (m_nPos < m_sData.length() && m_sData[m_nPos] != ',')
    sTmp += m_sData[m_nPos++];

  m_nPos++; // skip past comma

  if (sTmp.empty()) {
    m_bGood = false;
  } else {
    ++m_nCol;
    m_bGood = true;
    Out = atol(sTmp.c_str());
  }

  return *this;
}

CCsvParser &CCsvParser::operator >>(bool &Out) {
  if (!m_bGood)
    return *this;

  string sTmp = "";
  skipSpaces();

  while (m_nPos < m_sData.length() && m_sData[m_nPos] != ',')
    sTmp += m_sData[m_nPos++];

  m_nPos++; // skip past comma

  if (sTmp.empty()) {
    m_bGood = false;
  } else {
    ++m_nCol;
    m_bGood = true;
    Out = atol(sTmp.c_str()) != 0;
  }

  return *this;
}

bool CCsvParser::isGood() const {
  return m_bGood;
}

bool CCsvParser::isBad() const {
  return !m_bGood;
}

unsigned int CCsvParser::getErrorCol() const {
  return m_nCol;
}
