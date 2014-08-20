//
//  GameShare_TimeProcess.cpp
//  OnceAgain
//
//  Created by xiaohai on 14-2-25.
//
//

#include "GameShare_TimeProcess.h"
#include "SpriteFrameManage.h"

bool GameShare_TimeProcess::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    CCRect rectBrown(832, 1, 127,127);
    
    m_pTimeLimit = NULL;
//	//time process background
//	CCRect rcProcessBackground(1, 1, 320, 80);
//	m_pProcessBackground = GameShare_Texture::sharedTexture()->GetSpriteByCCRect(akooline_image, rcProcessBackground);
//	m_pProcessBackground->setScale(2);
//    m_pProcessBackground->setAnchorPoint(CCPointZero);
//    m_pProcessBackground->setPosition(ccp(0,0));
//	m_pProcessBackground->setVisible(true);
//	this->addChild(m_pProcessBackground);
   
    //process bar
	m_pProcessSlot = CCSprite::createWithSpriteFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName("common/process_time_slot.png")); 
	m_pProcessSlot->setPosition(ccp(visibleSize.width / 2, 80 + 45));
	m_pProcessSlot->setVisible(true);
	this->addChild(m_pProcessSlot);

	CCRect rcProcess(50, 4, 640, 38);
	m_pProcess = CCSprite::createWithSpriteFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName("common/process_time_bar.png")); 
	m_pProcess->setPosition(ccp(visibleSize.width / 2, 80 + 45));
	m_pProcess->setVisible(true);
	this->addChild(m_pProcess);

	//process Eye
	CCRect rcProcessEye(458, 598, 30, 20);
	m_pProcessEyes = CCSprite::createWithSpriteFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName("common/process_time_head.png"));
	m_pProcessEyes->setPosition(ccp(visibleSize.width - rcProcessEye.size.width, 80 + 45 + rcProcessEye.size.height / 2 - 5));
	this->addChild(m_pProcessEyes);

	CCAnimation* pAni = CCAnimation::create();
	CCString str;
	str.initWithFormat("common/process_time_start0.png");
	pAni->addSpriteFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName(str.getCString()));
	str.initWithFormat("common/process_time_start.png");
	pAni->addSpriteFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName(str.getCString()));
	pAni->setDelayPerUnit(0.5f);
	pAni->setLoops(1);

	m_pProcessStart = CCSprite::createWithSpriteFrameName("common/process_time_start0.png"); 
	m_pProcessStart->setPosition(ccp(m_pProcessStart->getContentSize().width / 2, 80 + 49));
	m_pProcessStart->setVisible(true);
	m_pProcessStart->runAction(CCRepeatForever::create(CCAnimate::create(pAni)));
	this->addChild(m_pProcessStart);
    
    // 10 second notice
    m_pTimeNotice = CCSprite::create("./CocoStudioResources/blackcolor.jpg");
    m_pTimeNotice->setScale(20);
    m_pTimeNotice->setOpacity(218);
    m_pTimeNotice->setContentSize(visibleSize);
    m_pTimeNotice->setAnchorPoint(ccp(0, 0));
    m_pTimeNotice->setPosition(ccp(0,0));
    m_pTimeNotice->setVisible(false);
    this->addChild(m_pTimeNotice, 5);
    
    //time over
    CCRect rcTimeOver(7, 204, 348, 250);
    //m_pTimeOver = GameShare_Texture::sharedTexture()->GetSpriteByCCRect(akooakoo_image, rcTimeOver);
	m_pTimeOver = CCSprite::createWithSpriteFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName("common/time_out.png"));
    m_pTimeOver->setVisible(false);
    m_pTimeOver->setPosition(ccp(2.5 * 127, 4 * 127));
    this->addChild(m_pTimeOver, 5);
#ifndef _WIN32 
	SetTimeSum(60);
#else
	SetTimeSum(15);
#endif
    //SetTimeSum(5);
    return true;
}

// start time
void GameShare_TimeProcess::BeginTimeProcess()
{
	schedule(schedule_selector(GameShare_TimeProcess::TimeInterval), 0.1);
}

//to move Batch sprite
void GameShare_TimeProcess::MoveToCenter(std::vector<cocos2d::CCSprite*> vSprite, CCPoint rPos)
{
    // adjust distance
    if(vSprite.size() == 0) return;
    size_t nMinIndex = vSprite.size() / 2;
    if(nMinIndex == 0)
        nMinIndex = 0;
    
    
    float nMoveDis = (rPos.x - vSprite[nMinIndex]->getPositionX());
    float yMoveDis = (rPos.y - vSprite[nMinIndex]->getPositionY());
    
    for(size_t i = 0; i < vSprite.size(); i++)
    {
        vSprite[i]->setPositionX(nMoveDis + vSprite[i]->getPositionX());
        if(rPos.y <= 0.1)
            continue;
        vSprite[i]->setPositionY(yMoveDis + vSprite[i]->getPositionY());
    }
}

size_t GameShare_TimeProcess::GetSecondsRemain()
{
    return m_nTimeSum;
}

void GameShare_TimeProcess::TimeInterval(float dt)
{
    CCNotificationCenter::sharedNotificationCenter()->postNotification(kTimeInterval, this);
    
    m_nTimeCount++;
    if(m_nTimeCount >= 10)
    {
        m_nTimeSum --;
        m_nTimeCount = 0;
        ShowProcessTimeSum(m_nTimeSum);
    }
	float fX = m_pProcess->getPositionX();
	m_pProcess->setPositionX(fX - 640 / 600.0);
    
    
    CCPoint posEys = m_pProcessEyes->getPosition();
    m_pProcessEyes->setPosition(ccp(posEys.x - 640 / 600.0, posEys.y));
    
    if(fX + 320.0 < 0)
    {
        // sent notify
        //CCNotificationCenter::sharedNotificationCenter()->postNotification(kGameTimeOutName, NULL);
		CCNotificationCenter::sharedNotificationCenter()->postNotification(kGameTimeOutNamePer, NULL);
		m_nTimeCount = 0;
    }
}

void GameShare_TimeProcess::AddSeconds(int rnSeconds)
{
    m_nTimeSum += rnSeconds;
//    if(m_nTimeSum > 60)
//        m_nTimeSum = 60;
//    
    SetTimeSum(m_nTimeSum);
}

void GameShare_TimeProcess::SetTimeSum(int nTimeSum)
{
    m_nTimeSum = nTimeSum;
    
    //根据时间大小 调整位置

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    float fX = visibleSize.width / 2;
    int time;
    if (nTimeSum > 60) {
        time = 60;
    }
    else
        time = nTimeSum;
    
    float fFlowDis = 10 * (60 - time) * 640 / 600.0;
    m_pProcess->setPositionX(fX - fFlowDis);
    
    
    CCRect rcProcessEye(458, 598, 30, 20);
    fX = visibleSize.width - rcProcessEye.size.width;
    m_pProcessEyes->setPositionX(fX - fFlowDis);
    
    ShowProcessTimeSum(m_nTimeSum);
}

void GameShare_TimeProcess::ShowProcessTimeSum(int nTimeSum)
{
    ValueToSprite(nTimeSum, m_vTimeSumSprite);
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint posEys = m_pProcessEyes->getPosition();
    
    for(int i = 0; i < m_vTimeSumSprite.size(); i++)
    {
        m_vTimeSumSprite[i]->setScale(0.4);
    }
    
    CCPoint rCenterPos(visibleSize.width / 2, posEys.y);
    MoveToCenter(m_vTimeSumSprite, rCenterPos);

    if(nTimeSum <= 5)
    {
        CCRect rcNum(982, 795, 280, 94);
        switch(nTimeSum)
        {
            case 0:
            {
                rcNum.setRect(504, 1358, 61, 69);
                break;
            }
            case 1:
            {
                rcNum.setRect(1, 1525, 37, 66);
                break;
            }
            case 2:
            {
                rcNum.setRect(402, 1865, 49, 67);
                break;
            }
            case 3:
            {
                rcNum.setRect(511, 1515, 50, 72);
                break;
            }
            case 4:
            {
                rcNum.setRect(191, 1862, 57, 66);
                break;
            }
            case 5:
            {
                rcNum.setRect(1521, 1814, 50, 68);
                break;
            }
            default:
                return;
        }
        if(m_pTimeLimit != NULL)
            this->removeChild(m_pTimeLimit);
        m_pTimeLimit = GameShare_Texture::sharedTexture()->GetSpriteByCCRect(akoopang_image ,rcNum);
        m_pTimeLimit->setVisible(true);
        m_pTimeLimit->setScale(0.5);
        m_pTimeLimit->setPosition(ccp(visibleSize.width / 2, posEys.y));
        //
        CCActionInterval* rpAction = CCSequence::create(CCScaleTo::create(0.3, 2), CCScaleTo::create(0.8, 0.5), NULL);
        
        m_pTimeLimit->runAction(rpAction);
        this->addChild(m_pTimeLimit, 1);
    }
    
    if(nTimeSum <= 10 && m_pTimeNotice != NULL)
    {
        m_pTimeNotice->stopAllActions();
        m_pTimeNotice->setOpacity(128);
        CCActionInterval* rpAction = CCSequence::create(CCShow::create(), CCFadeTo::create(0.7, 25), CCHide::create(), NULL);
        
        m_pTimeNotice->runAction(rpAction);
    }
}

void GameShare_TimeProcess::ValueToSprite(int nCount, std::vector<cocos2d::CCSprite*> & vSprite)
{
    for(size_t i = 0; i < vSprite.size(); i++)
    {
        vSprite[i]->setVisible(false);
        this->removeChild(vSprite[i]);
    }
vSprite.clear();
    int nMax = nCount;
    int nMin;
    CCRect rc;
    CCSprite*       m_Sprite;
    float           yValue = 50.0;
    float           xValue = 25.0;
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    int nSeparated = 0;
    int nAddtionLen = 0;
    while(true)
    {
        nMin = nMax % 10;
        m_Sprite = NULL;
        switch(nMin)
        {
            case 0:
            {
                rc.setRect(1694, 972, 70, 70);
                m_Sprite = GameShare_Texture::sharedTexture()->GetSpriteByCCRect(akoopang_image, rc);
                m_Sprite->setScaleX(xValue / 70.0);
                m_Sprite->setScaleY(yValue / 70.0);
                break;
            }
            case 1:
            {
                rc.setRect(1, 1279, 47, 85);
                m_Sprite = GameShare_Texture::sharedTexture()->GetSpriteByCCRect(akoopang_image, rc);
                m_Sprite->setScaleX(xValue / 47.0);
                m_Sprite->setScaleY(yValue / 85.0);
                break;
            }
            case 2:
            {
                rc.setRect(337, 1054, 68, 86);
                m_Sprite = GameShare_Texture::sharedTexture()->GetSpriteByCCRect(akoopang_image, rc);
                m_Sprite->setScaleX(xValue / 68.0);
                m_Sprite->setScaleY(yValue / 86.0);
                break;
            }
            case 3:
            {
                rc.setRect(1687, 1417, 69, 84);
                m_Sprite = GameShare_Texture::sharedTexture()->GetSpriteByCCRect(akoopang_image, rc);
                m_Sprite->setScaleX(xValue / 69.0);
                m_Sprite->setScaleY(yValue / 84.0);
                break;
            }
            case 4:
            {
                rc.setRect(401, 1691, 71, 83);
                m_Sprite = GameShare_Texture::sharedTexture()->GetSpriteByCCRect(akoopang_image, rc);
                m_Sprite->setScaleX(xValue / 71.0);
                m_Sprite->setScaleY(yValue / 83.0);
                break;
            }
            case 5:
            {
                rc.setRect(1699, 105, 70, 85);
                m_Sprite = GameShare_Texture::sharedTexture()->GetSpriteByCCRect(akoopang_image, rc);
                m_Sprite->setScaleX(xValue / 70.0);
                m_Sprite->setScaleY(yValue / 85.0);
                break;
            }
            case 6:
            {
                rc.setRect(981, 1714, 69, 91);
                m_Sprite = GameShare_Texture::sharedTexture()->GetSpriteByCCRect(akoopang_image, rc);
                m_Sprite->setScaleX(xValue / 69.0);
                m_Sprite->setScaleY(yValue / 91.0);
                break;
            }
            case 7:
            {
                rc.setRect(359, 897, 64, 85);
                m_Sprite = GameShare_Texture::sharedTexture()->GetSpriteByCCRect(akoopang_image, rc);
                m_Sprite->setScaleX(xValue / 64.0);
                m_Sprite->setScaleY(yValue / 85.0);
                break;
            }
            case 8:
            {
                rc.setRect(348, 1517, 72, 88);
                m_Sprite = GameShare_Texture::sharedTexture()->GetSpriteByCCRect(akoopang_image, rc);
                m_Sprite->setScaleX(xValue / 72.0);
                m_Sprite->setScaleY(yValue / 88.0);
                break;
            }
            case 9:
            {
                rc.setRect(191, 1699, 65, 91);
                m_Sprite = GameShare_Texture::sharedTexture()->GetSpriteByCCRect(akoopang_image, rc);
                m_Sprite->setScaleX(xValue / 65.0);
                m_Sprite->setScaleY(yValue / 91.0);
                break;
            }
            default:
            {
                break;
            }
        }
        if(m_Sprite != NULL)
        {
            if((nSeparated % 3) == 0 && nSeparated > 0)
            {
                rc.setRect(252, 1076, 32, 36);
                cocos2d::CCSprite* Tmpprite = GameShare_Texture::sharedTexture()->GetSpriteByCCRect(akoopang_image, rc);
                CCLog("nAddtionLen = %d", nAddtionLen);
                Tmpprite->setPosition(ccp(visibleSize.width / 2 - nSeparated * 25 - nAddtionLen, (visibleSize.height - 130 - 18)));
                Tmpprite->setScale(0.5);
                this->addChild(Tmpprite, 1);
                vSprite.push_back(Tmpprite);
                nAddtionLen += 16;
            }
            m_Sprite->setPosition(ccp(visibleSize.width / 2 - nSeparated * 25 - nAddtionLen, (visibleSize.height - 130)));
            nSeparated++;
			if(nCount<=5)
				m_Sprite->setVisible(false);
			else 
				m_Sprite->setVisible(true);
            this->addChild(m_Sprite, 1);
            vSprite.push_back(m_Sprite);
       
        }
        else{
            
        }
        
        nMax = nMax / 10;
        if(nMax == 0) break;
    }

}