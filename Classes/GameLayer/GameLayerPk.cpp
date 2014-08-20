//
//  GameLayerPk.cpp
//  OnceAgain
//
//  Created by mac on 14-4-29.
//
//

#include "GameLayerPk.h"
#include "StringUtil.h"
#include "PkSysManager.h"
#include "PlayerInfoManager.h"
#include "ImageDownloader.h"
#include "NumSprite.h"
#include "GameLayerPk2.h"
GameLayerPk::GameLayerPk()
{
    m_pListener = NULL;
    m_pfnSelector = NULL;
}
GameLayerPk::~GameLayerPk()
{
    m_pListener = NULL;
    m_pfnSelector = NULL;
    GUIReader::shareReader()->purgeGUIReader();
	DictionaryHelper::shareHelper()->purgeDictionaryHelper();
	ActionManager::shareManager()->purgeActionManager();
}

bool GameLayerPk::init()
{
    if (!CCLayer::init()) {
        return false;
    }
	if(CPkSysManager::sharedInstance().myScore < CPkSysManager::sharedInstance().playerScore||CPkSysManager::sharedInstance().myScore > CPkSysManager::sharedInstance().playerScore)
	{
		UILayer* ul = UILayer::create();
		if (CPkSysManager::sharedInstance().myScore > CPkSysManager::sharedInstance().playerScore)
		{
			auto myLayout = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile(CStringUtil::convertToUIResPath("pkResult.json").c_str()));
			ul->addWidget(myLayout);
			this->addChild(ul, 0, 100);
		}
		else if (CPkSysManager::sharedInstance().myScore < CPkSysManager::sharedInstance().playerScore)
		{
			auto myLayout = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile(CStringUtil::convertToUIResPath("pkResult2.json").c_str()));
			ul->addWidget(myLayout);
			this->addChild(ul, 0, 100);
		}

		UIButton* sureBtn = dynamic_cast<UIButton*>(ul->getWidgetByName("anniu")); //按钮;
		sureBtn->setPressedActionEnabled(true);
		sureBtn->addReleaseEvent(this, coco_releaseselector(GameLayerPk::sureBtnCallback));

		//设置自己的头像.
		UIImageView* cellBg = dynamic_cast<UIImageView*>(ul->getWidgetByName("SLtouxiang"));	//自己头像
		CCSprite* img =  CCSprite::create();
		img->setContentSize(CCSize(145, 145));
		img->setAnchorPoint(ccp(0, 0));
		img->setScale(0.6f);
		cellBg->addRenderer(img, 10);
		CImageDownloader::GetInstance()->SendHttpRequest(CPlayerInfoMan::sharedInstance().getPlayerInfo().strImg.c_str(), img, "1000", 1000);
		//设置自己的名字
		UILabel* nameLabel = dynamic_cast<UILabel*>(ul->getWidgetByName("SLname"));
		nameLabel->setText(CPlayerInfoMan::sharedInstance().getPlayerInfo().strName.c_str());

		//设置对方的头像
		UIImageView* cellBg2 = dynamic_cast<UIImageView*>(ul->getWidgetByName("touxiang"));
		CCSprite* img2 =  CCSprite::create();
		img2->setContentSize(CCSize(145, 145));
		img2->setAnchorPoint(ccp(0, 0));
		img2->setScale(0.6f);
		cellBg2->addRenderer(img2, 10);
		CImageDownloader::GetInstance()->SendHttpRequest(CPkSysManager::sharedInstance().playerUrl.c_str(), img2, "1000", 1000);
		//设置对方名字
		UILabel* nameLabel2 = dynamic_cast<UILabel*>(ul->getWidgetByName("name"));
		nameLabel2->setText(CPkSysManager::sharedInstance().playerName.c_str());

		//设置自己的分数.
		CCSprite* score = NumSprite::getNumSprite(CPkSysManager::sharedInstance().myScore, "./CocoStudioResources/FriendListTimeNum", 17.0);
		score->setPosition(ccp(-35, 0));
		UIImageView* scoreBg1 = dynamic_cast<UIImageView*>(ul->getWidgetByName("fenshu"));
		scoreBg1->addRenderer(score, 10);
		//设置对方的分数.
		CCSprite* score2 = NumSprite::getNumSprite(CPkSysManager::sharedInstance().playerScore, "./CocoStudioResources/FriendListTimeNum", 17.0);
		score2->setPosition(ccp(-35, 0));
		UIImageView* scoreBg2 = dynamic_cast<UIImageView*>(ul->getWidgetByName("sbFenshu"));
		scoreBg2->addRenderer(score2, 10);

		Ray	= dynamic_cast<UIImageView*>(ul->getWidgetByName("BjRay"));	
		if(CPkSysManager::sharedInstance().myScore > CPkSysManager::sharedInstance().playerScore)
		{
			UIImageView* sb = dynamic_cast<UIImageView*>(ul->getWidgetByName("sb"));
			sb->setZOrder(10.0);
			Start1 = dynamic_cast<UIImageView*>(ul->getWidgetByName("start"));				//黄色星
			Start2 = dynamic_cast<UIImageView*>(ul->getWidgetByName("start10"));
			Start3 = dynamic_cast<UIImageView*>(ul->getWidgetByName("start6"));
			Start4 = dynamic_cast<UIImageView*>(ul->getWidgetByName("start11"));

			Start5 = dynamic_cast<UIImageView*>(ul->getWidgetByName("start2"));				//白色星
			Start6 = dynamic_cast<UIImageView*>(ul->getWidgetByName("start5"));
			Start7 = dynamic_cast<UIImageView*>(ul->getWidgetByName("start3"));
			Start8 = dynamic_cast<UIImageView*>(ul->getWidgetByName("start4"));
			Start8->setZOrder(2);

			Start9= dynamic_cast<UIImageView*>(ul->getWidgetByName("start7"));				//灰色星
			Start10 = dynamic_cast<UIImageView*>(ul->getWidgetByName("start8"));	
			Start11 = dynamic_cast<UIImageView*>(ul->getWidgetByName("start9"));
		}
		else if (CPkSysManager::sharedInstance().myScore < CPkSysManager::sharedInstance().playerScore)
		{
			pStar1 = dynamic_cast<UIImageView*>(ul->getWidgetByName("start"));
			pStar2 = dynamic_cast<UIImageView*>(ul->getWidgetByName("start2"));
			pStar3 = dynamic_cast<UIImageView*>(ul->getWidgetByName("start3"));
			pStar4 = dynamic_cast<UIImageView*>(ul->getWidgetByName("start4"));
			pStar5 = dynamic_cast<UIImageView*>(ul->getWidgetByName("start5"));
		}
	}
	 if(CPkSysManager::sharedInstance().myScore == CPkSysManager::sharedInstance().playerScore){
		UILayer* ul = UILayer::create();
		auto myLayout = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile(CStringUtil::convertToUIResPath("pk.json").c_str()));
		ul->addWidget(myLayout);
		this->addChild(ul, 0, 100);
		//按钮
		UIButton* sureBtn = dynamic_cast<UIButton*>(ul->getWidgetByName("Sure"));
		sureBtn->setPressedActionEnabled(true);
		sureBtn->addReleaseEvent(this, coco_releaseselector(GameLayerPk::sureBtnCallback));

		//设置自己的头像.
		UIImageView* cellBg = dynamic_cast<UIImageView*>(ul->getWidgetByName("Avatar1Bg"));	//自己头像
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
		UIImageView* scoreBg1 = dynamic_cast<UIImageView*>(ul->getWidgetByName("Image_57"));
		scoreBg1->addRenderer(score, 10);
		//设置对方的分数.
		CCSprite* score2 = NumSprite::getNumSprite(CPkSysManager::sharedInstance().playerScore, "./CocoStudioResources/FriendListTimeNum", 17.0);
		score2->setPosition(ccp(-35, 0));
		UIImageView* scoreBg2 = dynamic_cast<UIImageView*>(ul->getWidgetByName("Image_61"));
		scoreBg2->addRenderer(score2, 10);

		UIImageView* pPkPj	= dynamic_cast<UIImageView*>(ul->getWidgetByName("Image_24"));					//平局logo
			Ray2	= dynamic_cast<UIImageView*>(ul->getWidgetByName("Ray"));
		 pSatrt1	= dynamic_cast<UIImageView*>(ul->getWidgetByName("Image_80"));
		 pSatrt2	= dynamic_cast<UIImageView*>(ul->getWidgetByName("Image_3"));
		 pSatrt3	= dynamic_cast<UIImageView*>(ul->getWidgetByName("Image_94"));
		 pSatrt4	= dynamic_cast<UIImageView*>(ul->getWidgetByName("Image_110"));
		 pSatrt5	= dynamic_cast<UIImageView*>(ul->getWidgetByName("Image_116"));
		 pSatrt6	= dynamic_cast<UIImageView*>(ul->getWidgetByName("Image_123"));
	}
	this->schedule(schedule_selector(GameLayerPk::UpStart), 0.2f);
    this->schedule(schedule_selector(GameLayerPk::UpRay), 0.05f);	
    return true;
}
void GameLayerPk::UpRay(float td){
	if(CPkSysManager::sharedInstance().myScore > CPkSysManager::sharedInstance().playerScore||CPkSysManager::sharedInstance().myScore < CPkSysManager::sharedInstance().playerScore)
		Ray->setRotation(Ray->getRotation()+1.5f);
	else if(CPkSysManager::sharedInstance().myScore == CPkSysManager::sharedInstance().playerScore)
		Ray2->setRotation(Ray2->getRotation()+1.5f);
}
void GameLayerPk::UpStart(float td)
{
	 if (CPkSysManager::sharedInstance().myScore > CPkSysManager::sharedInstance().playerScore) {
			if(Start1->getScale()>=1.0f)
				 Start1->setScale(0.8f);
			else 
				 Start1->setScale(1.0f);
			Start2->setScale(Start1->getScale());
			Start3->setScale(Start1->getScale());
			//Start4->setScale(Start1->getScale());
			Start5->setScale(Start1->getScale());
			Start6->setScale(Start1->getScale());
			Start7->setScale(Start1->getScale());
			Start8->setScale(Start1->getScale());
			//Start9->setScale(Start1->getScale());
			//Start10->setScale(Start1->getScale());
			Start11->setScale(Start1->getScale());
	 }else if(CPkSysManager::sharedInstance().myScore < CPkSysManager::sharedInstance().playerScore){
		 if(pStar1->getScale()>=1.0f)
			pStar1->setScale(0.8f);
		 else 
			pStar1->setScale(1.0f);
		 pStar2->setScale(pStar1->getScale());
		 pStar3->setScale(pStar1->getScale());
		 pStar4->setScale(pStar1->getScale());
		 pStar5->setScale(pStar1->getScale());
	 }
	 else if(CPkSysManager::sharedInstance().myScore == CPkSysManager::sharedInstance().playerScore){
		 if(pSatrt1->getScale()>=1.0f)
			 pSatrt1->setScale(0.8f);
		 else 
			 pSatrt1->setScale(1.0f);
		 pSatrt1->setScale(pSatrt1->getScale());
		 pSatrt2->setScale(pSatrt1->getScale());
		 pSatrt3->setScale(pSatrt1->getScale());
		 pSatrt4->setScale(pSatrt1->getScale());
		 pSatrt5->setScale(pSatrt1->getScale());
		 pSatrt6->setScale(pSatrt1->getScale());
	 }
}
void GameLayerPk::addSureCallbackFunc(cocos2d::CCObject *target, SEL_CallFunc callfun)
{
    this->m_pListener = target;
    this->m_pfnSelector = callfun;
}
void GameLayerPk::sureBtnCallback(cocos2d::CCObject *pSender)
{
    
    CPkSysManager::sharedInstance().reset();
    if (m_pListener && m_pfnSelector)
    {
        (m_pListener->*m_pfnSelector)();
    }
   this->removeFromParent();
}