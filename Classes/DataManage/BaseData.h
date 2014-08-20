

#ifndef BASE_DATA_H
#define BASE_DATA_H
#include "cocos2d.h"
#include "ComData.h"

class CBaseData : public cocos2d::CCObject
{
	//怒气值
	CC_SYNTHESIZE(int , mnAnger, Anger);
	//分数
	CC_SYNTHESIZE(int ,mnScore,Score);
	//连击次数
	CC_SYNTHESIZE(int , mnContinueNum,ContinueNum);
	//疯狂连击次数
	CC_SYNTHESIZE(int , mnCrazyContinueNum,CrazyContinueNum);
	//是否生成炸弹
	CC_SYNTHESIZE(bool , mbGenBomb,GenBomb);
	//模式
	CC_SYNTHESIZE(ECrazyMode , mMode,Mode);

	//////////////////////////////////////////////////////////////////////////
	//日常任务计数相关
	//是否使用炸弹
	CC_SYNTHESIZE(bool,mbUseBomb,UseBomb);
	CC_SYNTHESIZE(bool,mbNoUsePlayItem,NoUsePlayItem);
    CC_SYNTHESIZE(double,mfLastCrazyTime,LastCrazyTime);
	//////////////////////////////////////////////////////////////////////////
	virtual void reset();
public:

protected:
    CBaseData();
    ~CBaseData();

	//static CFruitData* s_pFruitData;
};
#endif
