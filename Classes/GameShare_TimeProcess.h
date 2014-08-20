//
//  GameShare_TimeProcess.h
//  OnceAgain
//
//  Created by xiaohai on 14-2-25.
//
//
/*
 *         time process layer
 */

#ifndef OnceAgain_GameShare_TimeProcess_h
#define OnceAgain_GameShare_TimeProcess_h

#include "cocos2d.h"
#include "GameSharelist.h"
#include "SimpleAudioEngine.h"  // to play audio
USING_NS_CC;

class GameShare_TimeProcess : public CCLayer
{
public:
    virtual bool init();
   
    //开�?
    void BeginTimeProcess();
    
    //增加秒数
    void AddSeconds(int rnSeconds);
    
    //获取剩余秒数
    size_t GetSecondsRemain();
    
    //设置秒数
    void SetTimeSum(int nTimeSum);
    
    void ShowProcessTimeSum(int nTimeSum);
    
    void TimeInterval(float dt);

private:
    void MoveToCenter(std::vector<cocos2d::CCSprite*> vSprite, CCPoint rPos);
    
    void ValueToSprite(int nCount, std::vector<cocos2d::CCSprite*> & vSprite);
private:
    size_t                                  m_nTimeCount;
    size_t                                  m_nTimeSum;
    cocos2d::CCSprite*                      m_pProcessBackground;
	cocos2d::CCSprite*                      m_pProcess;
	cocos2d::CCSprite*                      m_pProcessStart;
	cocos2d::CCSprite*                      m_pProcessSlot;
    cocos2d::CCSprite*                      m_pTimeLimit;          //last 5 second
    std::vector<cocos2d::CCSprite*>         m_vTimeSumSprite;
    cocos2d::CCSprite*                      m_pTimeNotice;         //time notice

	CC_SYNTHESIZE_READONLY(cocos2d::CCSprite*,m_pTimeOver,TimeOver);
	CC_SYNTHESIZE_READONLY(cocos2d::CCSprite*,m_pProcessEyes,ProcessEyes);
public:
    CREATE_FUNC(GameShare_TimeProcess);
};
#endif
