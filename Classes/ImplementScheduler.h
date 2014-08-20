
/***************************************************************
* 
*
*  作者：		王少培
*  文件名：		
*  创建时间：	
*
***************************************************************/
#ifndef __CImplementScheduler_H__
#define __CImplementScheduler_H__

USING_NS_CC;
class CGameFruit;
// 调度器
class CImplementScheduler
{
public:
	// 构造函数
	CImplementScheduler();
	// 析构函数
	~CImplementScheduler();

	//////////////////////////////////////////////////////////////////////////
	//水果连线相关移动
	static void FruitMove( unsigned int startTime, unsigned int duringTime,CCSprite* pFruit, CCPoint& ptDistance);
	static void FruitOut(unsigned int startTime, unsigned int duringTime,CCObject* pFruit);
	static void FruitLightning(unsigned int startTime, unsigned int duringTime,bool bRow,CCSprite* pFruit,CCPoint ptPos,CCObject* pParent = NULL,SEL_CallFuncND pCallFunc = NULL);
	static void FruitBomb(unsigned int startTime, unsigned int duringTime,CCSprite* pFruit);
	static void FruitMoveEnd( unsigned int startTime, unsigned int duringTime,CCNode* pMainLayer);
	static void FruitIceAni(unsigned int startTime, unsigned int duringTime,CGameFruit* pFruit);
	static void ScoreFloat( unsigned int startTime, unsigned int duringTime,CCSprite* pScore,CCPoint pt);
	static void AllMoveEnd( unsigned int startTime, unsigned int duringTime,CCNode* pMainLayer);
	//////////////////////////////////////////////////////////////////////////

};

#endif