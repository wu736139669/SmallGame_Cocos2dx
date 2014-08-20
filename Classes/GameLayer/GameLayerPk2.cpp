//
//  GameLayerPk2.cpp
//  OnceAgain
//
//  Created by mac on 14-5-8.
//
//

#include "GameLayerPk2.h"
#include "StringUtil.h"
#include "PkSysManager.h"
#include "PlayerInfoManager.h"
#include "ImageDownloader.h"
#include "NumSprite.h"
GameLayerPk2::GameLayerPk2()
{
    m_pListener = NULL;
    m_pfnSelector = NULL;
}
GameLayerPk2::~GameLayerPk2()
{
    m_pListener = NULL;
    m_pfnSelector = NULL;
    GUIReader::shareReader()->purgeGUIReader();
	DictionaryHelper::shareHelper()->purgeDictionaryHelper();
	ActionManager::shareManager()->purgeActionManager();
}
bool GameLayerPk2::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    UILayer* ul = UILayer::create();
    auto myLayout = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile(CStringUtil::convertToUIResPath("Pk2.json").c_str()));
    ul->addWidget(myLayout);
    this->addChild(ul, 0, 100);
    
    UIButton* sureBtn = dynamic_cast<UIButton*>(ul->getWidgetByName("Sure"));
    sureBtn->setPressedActionEnabled(true);
    sureBtn->addReleaseEvent(this, coco_releaseselector(GameLayerPk2::sureBtnCallback));
    
    //设置自己的头像.
    UIImageView* cellBg = dynamic_cast<UIImageView*>(ul->getWidgetByName("Avatar1Bg"));
    CCSprite* img =  CCSprite::create();
    img->setContentSize(CCSize(145, 145));
    img->setAnchorPoint(ccp(0, 0));
    cellBg->addRenderer(img, 10);
    CImageDownloader::GetInstance()->SendHttpRequest(CPlayerInfoMan::sharedInstance().getPlayerInfo().strImg.c_str(), img, "1000", 1000);
    //设置自己的名字
    UILabel* nameLabel = dynamic_cast<UILabel*>(ul->getWidgetByName("Name1Label"));
    nameLabel->setText(CPlayerInfoMan::sharedInstance().getPlayerInfo().strName.c_str());
    
    //设置对方的头像
    UIImageView* cellBg2 = dynamic_cast<UIImageView*>(ul->getWidgetByName("Avatar2Bg"));
    CCSprite* img2 =  CCSprite::create();
    img2->setContentSize(CCSize(145, 145));
    img2->setAnchorPoint(ccp(0, 0));
    cellBg2->addRenderer(img2, 10);
    CImageDownloader::GetInstance()->SendHttpRequest(CPkSysManager::sharedInstance().playerUrl.c_str(), img2, "1000", 1000);
    //设置对方名字
    UILabel* nameLabel2 = dynamic_cast<UILabel*>(ul->getWidgetByName("Name2Label"));
    nameLabel2->setText(CPkSysManager::sharedInstance().playerName.c_str());
    
    //设置自己的分数.
    CCSprite* score = NumSprite::getNumSprite(CPkSysManager::sharedInstance().myScore, "./CocoStudioResources/FriendListTimeNum", 17.0);
    score->setPosition(ccp(-35, 0));
    UIImageView* scoreBg1 = dynamic_cast<UIImageView*>(ul->getWidgetByName("ScoreBg"));
    scoreBg1->addRenderer(score, 10);

	//等待迎战;
	m_iSetTime = 1;
	Deng  = dynamic_cast<UIImageView*>(ul->getWidgetByName("Label1"));
	Dai   = dynamic_cast<UIImageView*>(ul->getWidgetByName("Label2"));
	Ying  = dynamic_cast<UIImageView*>(ul->getWidgetByName("Label3"));
	Zhan  = dynamic_cast<UIImageView*>(ul->getWidgetByName("Label4"));
	Dain1  = dynamic_cast<UIImageView*>(ul->getWidgetByName("Label5"));
	Dain2  = dynamic_cast<UIImageView*>(ul->getWidgetByName("Label6"));
	Dain3  = dynamic_cast<UIImageView*>(ul->getWidgetByName("Label7"));
	CCActionInterval*  actionTo = CCJumpTo::create(2, ccp(200,200),50, 4);  
	CCActionInterval*  actionBy = CCJumpBy::create(2, ccp(300,0), 50, 4);  
	actionUp = CCJumpBy::create(0.3f, ccp(0,0), 20,1); 
	CCActionInterval*  actionByBack = actionUp->reverse();

	//设置光效旋转
	UIImageView* Ray2 = dynamic_cast<UIImageView*>(ul->getWidgetByName("lightimg"));
	CCActionInterval * rotateto = CCRotateBy::create(6.0f, 360);
	CCFiniteTimeAction* seq1 = CCSequence::create(rotateto,NULL);
	CCActionInterval * repeatForever2 =CCRepeatForever::create((CCActionInterval* )seq1);
	Ray2->runAction(repeatForever2);
	//Deng->runAction( CCSequence::create(actionUp, NULL));  
	//Dai->runAction( CCSequence::create(actionUp, NULL));

// 	for(int i = 0;i<10;i++)
// 	{
// 		if(i%2==0)
// 		{
// 			
// 			Deng->runAction(actionByBack);
// 		}
// 		else{
// 			
// 			Dai->runAction(actionByBack);
// 		}
// 	}
	//this->schedule(schedule_selector(GameLayerPk2::SetDDTime), 0.2f);
	
	Deng->runAction( CCSequence::create((CCActionInterval*)actionUp->copy(),NULL));
	Dai->runAction( CCSequence::create((CCActionInterval*)actionUp->copy(),NULL));
	Ying->runAction( CCSequence::create((CCActionInterval*)actionUp->copy(),NULL)); 
	Zhan->runAction( CCSequence::create((CCActionInterval*)actionUp->copy(),NULL)); 
	Dain1->runAction( CCSequence::create((CCActionInterval*)actionUp->copy(),NULL)); 
	Dain2->runAction( CCSequence::create((CCActionInterval*)actionUp->copy(),NULL)); 
	Dain3->runAction( CCSequence::create((CCActionInterval*)actionUp->copy(),NULL));
    return true;
}
void GameLayerPk2::addSureCallbackFunc(cocos2d::CCObject *target, SEL_CallFunc callfun)
{
    this->m_pListener = target;
    this->m_pfnSelector = callfun;
}
void GameLayerPk2::sureBtnCallback(cocos2d::CCObject *pSender)
{
    
    CPkSysManager::sharedInstance().reset();
    if (m_pListener && m_pfnSelector)
    {
        (m_pListener->*m_pfnSelector)();
    }
//    this->removeFromParent();
}
void GameLayerPk2::SetDDTime(float td){
	
	if(m_iSetTime==1)
		
	if(m_iSetTime>=7)
		m_iSetTime=1;
	else
		m_iSetTime++;
}
