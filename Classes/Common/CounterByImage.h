/********************************************************************
	created:	2014/04/11 
	filename: 	CounterByImage.h
	author:		王少培
	purpose:	
*********************************************************************/
#ifndef __Image_Counter__
#define __Image_Counter__
#include "cocos2d.h"
#include <vector>
USING_NS_CC;
enum{
	eDelimStartIndex = 100,
};
typedef std::vector<std::string> VEC_NUMFILENAME;
class CCounterImage : public cocos2d::CCNode
{
public:
	typedef std::vector<CCNode*> VEC_NUMBER;
	CCounterImage()
		:_delim(NULL),_cellNumberWidth(0){};
	//创建
    static CCounterImage* create(const VEC_NUMFILENAME& vecNumFileName,char* pDelim = NULL,int number = 0,bool bpListLoad = true);
	//初始化
    bool init(const VEC_NUMFILENAME& vecNumFileName,int number = 0 ,char* pDelim = NULL, bool bpListLoad = true);
	//设置数字
    void setNumber(int number,bool bAni = false,unsigned int ceiling = 999999999);
	//设置单个字体宽度
	CC_SYNTHESIZE(int, _cellNumberWidth, CellNumberWidth);
	CC_SYNTHESIZE_READONLY(char*, _delim, Delim);
    CC_SYNTHESIZE_READONLY(int, _number, Number);
	CC_SYNTHESIZE(int, _totalWidth, TotalWidth);
protected:
    void _getNumAtPos(int pos);
	void _updata();
	VEC_NUMBER _vecNumber;
};

#endif 
