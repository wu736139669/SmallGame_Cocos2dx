/********************************************************************
	created:	2014/03/28 
	filename: 	BRCsvBase.h
	author:		王少培
	purpose:	
*********************************************************************/
#ifndef __BRUNIQUEID_H__
#define __BRUNIQUEID_H__
template <class T>
class CUniqueID {
public:
  static int generateID() {
    static int s_BaseID = 0;
    return s_BaseID++;
  }
};

#endif