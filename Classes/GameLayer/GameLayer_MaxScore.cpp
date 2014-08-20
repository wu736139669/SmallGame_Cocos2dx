//
//  GameLayer_MaxScore.cpp
//  OnceAgain
//
//  Created by mac on 14-4-14.
//
//

#include "GameLayer_MaxScore.h"
#include "StringUtil.h"
#include "NumSprite.h"
#include "GameShare_Global.h"
#include "Scene_GameItem.h"
#include "TaskManager.h"

GameLayer_MaxScore::~GameLayer_MaxScore()
{
	GUIReader::shareReader()->purgeGUIReader();
	DictionaryHelper::shareHelper()->purgeDictionaryHelper();
	ActionManager::shareManager()->purgeActionManager();
}

bool GameLayer_MaxScore::init()
{
	if (!CCLayer::init()) {
		return false;
	}


	CCSize visiableSize = CCDirector::sharedDirector()->getVisibleSize();

	//背景
	ulBg = UILayer::create();
	ulBg->retain();
	auto layoutBg = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("./CocoStudioResources/GameOver.json"));
	layoutBg->setTag(100);
	ulBg->addWidget(layoutBg);
	ulBg->setContentSize(visiableSize);
	this->addChild(ulBg,10);
	
	addImg = dynamic_cast<UIImageView*>(ulBg->getWidgetByName("AddImg")); 
	goldImg = dynamic_cast<UIImageView*>(ulBg->getWidgetByName("GoldImg"));
	expImg = dynamic_cast<UIImageView*>(ulBg->getWidgetByName("ExperienceImg"));
	addSpriteBg = dynamic_cast<UIImageView*>(ulBg->getWidgetByName("Image_14"));
	goldSpriteBg = dynamic_cast<UIImageView*>(ulBg->getWidgetByName("Image_14_0"));
	expSpriteBg = dynamic_cast<UIImageView*>(ulBg->getWidgetByName("Image_14_0_1"));
	//返回列表按钮.
	returnBtn = dynamic_cast<UIButton*>(ulBg->getWidgetByName("ReturnBtn"));
	returnBtn->setPressedActionEnabled(true);
	returnBtn->addReleaseEvent(this, coco_releaseselector(GameLayer_MaxScore::sureBtnCallback));

	againBtn = dynamic_cast<UIButton*>(ulBg->getWidgetByName("AgainBtn"));
	againBtn->setPressedActionEnabled(true);
	againBtn->addReleaseEvent(this, coco_releaseselector(GameLayer_MaxScore::playAgain));

	addSprite = NumSprite::getNumSprite("./CocoStudioResources/FriendListTimeNumAdd.png","",GameShare_Global::shareGlobal()->gameProperty.totolscore-GameShare_Global::shareGlobal()->gameProperty.prescore, "./CocoStudioResources/FriendListTimeNum", 20.0, 1);
	addSprite->ignoreAnchorPointForPosition(false);
	addSprite->setAnchorPoint(ccp(0.5, 0.5));
	this->addChild(addSprite,10);
	addSprite->setPosition(ccp(430 , 520));
	//添加金币.
    int money = CTaskMan::sharedInstance().getAddMoney() + GameShare_Global::shareGlobal()->gameProperty.addmoney;
	goldSprite = NumSprite::getNumSprite("./CocoStudioResources/FriendListTimeNumAdd.png","", money, "./CocoStudioResources/FriendListTimeNum", 20.0, 1);
	goldSprite->ignoreAnchorPointForPosition(false);
	goldSprite->setAnchorPoint(ccp(0.5, 0.5));
	this->addChild(goldSprite,10);
	goldSprite->setPosition(ccp(430, 460));
	//添加经验
	expSprite = NumSprite::getNumSprite("./CocoStudioResources/FriendListTimeNumAdd.png","",GameShare_Global::shareGlobal()->gameProperty.addexp, "./CocoStudioResources/FriendListTimeNum", 20.0, 1);
	expSprite->ignoreAnchorPointForPosition(false);
	expSprite->setAnchorPoint(ccp(0.5, 0.5));
	this->addChild(expSprite,10);
	expSprite->setPosition(ccp(430, 398));


	ul = UILayer::create();
	auto myLayout  = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("./CocoStudioResources/GameOverMax.json"));
	ul->addWidget(myLayout);
	ul->setContentSize(visiableSize);
	this->addChild(ul,10);

	UIImageView *light = dynamic_cast<UIImageView*>(ul -> getWidgetByName("Image_19"));
	CCRotateBy *rotate = CCRotateBy::create(2, 90);
	light -> runAction(CCRepeatForever::create(rotate));

	//历史最高分图片  
	UIImageView *historyPic = dynamic_cast<UIImageView*>(ul -> getWidgetByName("ScoreMaxPic"));
	historyPic -> setVisible(false);

	UIImageView *hisroryPicUp = dynamic_cast<UIImageView*>(ul -> getWidgetByName("historyScoreUp"));
	hisroryPicUp -> setVisible(false);

	UIImageView *histroyTop = dynamic_cast<UIImageView*>(ul -> getWidgetByName("Image_63"));
	histroyTop -> setVisible(false);

	UIImageView *finishScore = dynamic_cast<UIImageView*>(ul -> getWidgetByName("Image_12"));
	finishScore -> setVisible(false);
	UIImageView* bgImg = dynamic_cast<UIImageView*>(ul->getWidgetByName("ScoreBgImg"));
	//历史最高分
	lvLabel = dynamic_cast<UILabelAtlas*>(ul->getWidgetByName("AtlasLabel_4"));
	lvLabel->setVisible(false);

	star1 = dynamic_cast<UIImageView*>(ul->getWidgetByName("Image_58"));
	star2 = dynamic_cast<UIImageView*>(ul->getWidgetByName("Image_20"));
	star3 = dynamic_cast<UIImageView*>(ul->getWidgetByName("Image_37"));
	star4 = dynamic_cast<UIImageView*>(ul->getWidgetByName("Image_41"));
	star5 = dynamic_cast<UIImageView*>(ul->getWidgetByName("Image_23"));
	star6 = dynamic_cast<UIImageView*>(ul->getWidgetByName("Image_16"));
	star7 = dynamic_cast<UIImageView*>(ul->getWidgetByName("Image_45"));
	star8 = dynamic_cast<UIImageView*>(ul->getWidgetByName("Image_48"));
	CCFiniteTimeAction* seq1 = CCSequence::create(CCScaleTo::create(0.8,1.8),CCScaleTo::create(0.8,2.0),NULL);
	CCFiniteTimeAction* seq2 = CCSequence::create(CCScaleTo::create(0.8,0.8),CCScaleTo::create(0.8,1.0),NULL);
	CCFiniteTimeAction* seq3 = CCSequence::create(CCScaleTo::create(0.8,1.6),CCScaleTo::create(0.8,1.8),NULL);
	CCFiniteTimeAction* seq4 = CCSequence::create(CCScaleTo::create(0.8,0.6),CCScaleTo::create(0.8,0.8),NULL);
	CCFiniteTimeAction* seq5 = CCSequence::create(CCScaleTo::create(0.8,0.3),CCScaleTo::create(0.8,0.5),NULL);
	CCActionInterval * repeatForever1 =CCRepeatForever::create((CCActionInterval* )seq2);
	CCActionInterval * repeatForever2 =CCRepeatForever::create((CCActionInterval* )seq1);
	CCActionInterval * repeatForever3 =CCRepeatForever::create((CCActionInterval* )seq1);
	CCActionInterval * repeatForever4 =CCRepeatForever::create((CCActionInterval* )seq1);
	CCActionInterval * repeatForever5 =CCRepeatForever::create((CCActionInterval* )seq2);
	CCActionInterval * repeatForever6 =CCRepeatForever::create((CCActionInterval* )seq3);
	CCActionInterval * repeatForever7 =CCRepeatForever::create((CCActionInterval* )seq4);
	CCActionInterval * repeatForever8 =CCRepeatForever::create((CCActionInterval* )seq5);
	star1->runAction(repeatForever1);
	star2->runAction(repeatForever2);
	star3->runAction(repeatForever3);
	star4->runAction(repeatForever4);
	star5->runAction(repeatForever5);
	star6->runAction(repeatForever6);
	star7->runAction(repeatForever7);
	star8->runAction(repeatForever8);



	//历史最高分的放大效果
	UIImageView* scarfImg = dynamic_cast<UIImageView*>(ul->getWidgetByName("Image_8"));
	scarfImg->runAction(CCSequence::create(CCScaleTo::create(0.0, 3.0), CCScaleTo::create(0.5, 1.0), CCCallFunc::create(this, callfunc_selector(GameLayer_MaxScore::setScoreCallBack)),NULL));
	int i = GameShare_Global::shareGlobal()->gameProperty.totolscore;
	int j = GameShare_Global::shareGlobal()->gameProperty.highestscore;
	long k =  GameShare_Global::shareGlobal()->gameProperty.historyscore;
	CCString str;
	if(GameShare_Global::shareGlobal()->gameProperty.totolscore >= GameShare_Global::shareGlobal()->gameProperty.historyscore){
		//创造历史最高分的文字效果.
		histroyTop -> setVisible(true);
		historyPic -> setVisible(true);
		hisroryPicUp -> setVisible(true);
		hisroryPicUp -> setScale(0.8);
		CCScaleTo *scale1 = CCScaleTo::create(0.3, 1.1);
		CCScaleTo *scale3 = CCScaleTo::create(0.06, 0.8);
		CCScaleTo *scale4 = CCScaleTo::create(0.06, 1);
		CCScaleTo *scale2 = CCScaleTo::create(0.01, 0.8);
		CCSequence *action = CCSequence::create(scale1, scale3, scale4, CCDelayTime::create(1), scale2, NULL);

		hisroryPicUp -> runAction(CCRepeatForever::create(action));

		//边上星星效果.
		CCAnimation* pAni1 = CCAnimation::create();
		for (int i=1; i<=13; i++) {
			str.initWithFormat("./CocoStudioResources/GameOver/StarEffect_%d.png",i);
			pAni1->addSpriteFrameWithFileName(str.getCString());
		}
		pAni1->setDelayPerUnit(0.8f/9.f);
		pAni1->setLoops(1);

		for (int i=0; i<5; i++) {
			CCSprite* starEffect = CCSprite::create();

			CCFiniteTimeAction* pAction1 = CCRepeatForever::create(CCAnimate::create(pAni1));
			auto *pic_1 = CCSprite::create("./CocoStudioResources/GameOver/StarEffect_1.png");
			starEffect->setTexture(pic_1 -> getTexture());
			starEffect->setTextureRect(CCRectMake(0, 0, pic_1 -> getContentSize().width, pic_1 -> getContentSize().height));
			//        starEffect->runAction(pAction1);
			this->addChild(starEffect,0);
			switch (i) {
			case 0:
				{
					starEffect->setPosition(ccp(bgImg->getPosition().x, bgImg->getPosition().y+240));
					starEffect->runAction(CCSequence::create(CCDelayTime::create(0.5),CCCallFuncO::create(starEffect, callfuncO_selector(CCSprite::runAction),pAction1),NULL));
				}
				break;
			case 1:
				{
					starEffect->setPosition(ccp(bgImg->getPosition().x+230, bgImg->getPosition().y+200));
					starEffect->setRotation(30);
					starEffect->runAction(CCSequence::create(CCDelayTime::create(1.0),CCCallFuncO::create(starEffect, callfuncO_selector(CCSprite::runAction),pAction1),NULL));
				}
				break;
			case 2:
				{
					starEffect->setPosition(ccp(bgImg->getPosition().x-290, bgImg->getPosition().y+140));
					starEffect->setRotation(-50);
					starEffect->runAction(CCSequence::create(CCDelayTime::create(1.5),CCCallFuncO::create(starEffect, callfuncO_selector(CCSprite::runAction),pAction1),NULL));
				}
				break;
			case 3:
				{
					starEffect->setPosition(ccp(bgImg->getPosition().x-270, bgImg->getPosition().y-100));
					starEffect->setRotation(-120);
					starEffect->runAction(CCSequence::create(CCDelayTime::create(2.0),CCCallFuncO::create(starEffect, callfuncO_selector(CCSprite::runAction),pAction1),NULL));
				}
				break;
			case 4:
				{
					starEffect->setPosition(ccp(bgImg->getPosition().x+270, bgImg->getPosition().y-100));
					starEffect->setRotation(120);
					starEffect->runAction(CCSequence::create(CCDelayTime::create(2.5),CCCallFuncO::create(starEffect, callfuncO_selector(CCSprite::runAction),pAction1),NULL));
				}
				break;

			default:
				break;
			}
		}
	}
	else if (GameShare_Global::shareGlobal()->gameProperty.totolscore >= GameShare_Global::shareGlobal()->gameProperty.highestscore)
	{
		UIImageView* gradebg = dynamic_cast<UIImageView*>(ul->getWidgetByName("Image_4"));
		iEffectType = 0;
		iAddTypeNum = 0;
		gradebg->setVisible(false);
		histroyTop -> setVisible(false);
		historyPic -> setVisible(false);
		hisroryPicUp -> setVisible(false);
		finishScore -> setVisible(false);
		addSprite->setVisible(false);
		goldSprite->setVisible(false);
		expSprite->setVisible(false);
		bgImg->setVisible(false);
		returnBtn->setTouchEnabled(false);
		returnBtn->setVisible(false);
		againBtn->setTouchEnable(false);
		againBtn->setVisible(false);
		light->setVisible(false);
		addImg->setVisible(false);
		goldImg->setVisible(false);
		expImg->setVisible(false);
		addSpriteBg->setVisible(false);
		goldSpriteBg->setVisible(false);
		expSpriteBg->setVisible(false);
		star1->setVisible(false);
		star2->setVisible(false);
		star3->setVisible(false);
		star4->setVisible(false);
		star5->setVisible(false);
		star6->setVisible(false);
		star7->setVisible(false);
		star8->setVisible(false);
		CCAnimation *animation = CCAnimation::create();
		CCString str;
		for (int i = 1; i < 5; i++)  
		{  
			str.initWithFormat("./CocoStudioResources/GameOver/yun%d.png",i);
			animation->addSpriteFrameWithFileName(str.getCString());    
		}
		animation->setDelayPerUnit(0.2f);
		animation->setLoops(1);
		CCSprite *cloud = CCSprite::create("./CocoStudioResources/GameOver/yun1.png");
		this->addChild(cloud);
		cloud->setPosition(ccp(310,690));
		//cloud->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
		cloud->runAction(CCRepeat::create(CCAnimate::create(animation),1.0f));
		pEffects = CCSprite::create("./CocoStudioResources/GameOver/flock1.png");
		this->addChild(pEffects);
		pEffects2 = CCSprite::create("./CocoStudioResources/GameOver/flock1.png");
		this->addChild(pEffects2);
		pEffects3 = CCSprite::create("./CocoStudioResources/GameOver/flock1.png");
		this->addChild(pEffects3);
		pEffects->setVisible(false);
		pEffects2->setVisible(false);
		pEffects3->setVisible(false);
		CCSprite *Ray = CCSprite::create("./CocoStudioResources/pk/Ray.png");
		Ray->setPosition(ccp(320,700));
		this->addChild(Ray);
		CCRotateBy *rotate = CCRotateBy::create(2, 90);
		Ray -> runAction(CCRepeatForever::create(rotate));
		this->scheduleOnce(schedule_selector(GameLayer_MaxScore::setGradeBack),1.0f);	
	}
	else{
		//        CCSprite* labelSprite = CCSprite::create("./CocoStudioResources/ResultLastSocreImg.png");
		//        labelSprite->setPosition(ccp(labelSprite->getPositionX(), labelSprite->getPositionY()+80));
		//        bgImg->addRenderer(labelSprite,10);
		finishScore -> setVisible(true);
	}
	//获得最高分.
	return true;
}
void GameLayer_MaxScore::setScoreCallBack()
{
	UIImageView* bgImg = dynamic_cast<UIImageView*>(ul->getWidgetByName("Image_4"));
	//背后的闪光.
	CCSprite* blink = CCSprite::create("./CocoStudioResources/GameOver/BgLight.png");
	blink->runAction(CCRepeatForever::create(CCSequence::create(CCFadeTo::create(1.0, 100),CCFadeTo::create(1.0, 255),NULL)));
	blink->setPosition(ccp(0, 50));
	bgImg->addRenderer(blink, 0);
	//结果的图片
	CCSprite* resultSprite = NumSprite::getNumSprite(GameShare_Global::shareGlobal()->gameProperty.totolscore, "./numberBox/whiteNumber", 40.0, 0.5);
	bgImg->addRenderer(resultSprite,10);
	resultSprite->ignoreAnchorPointForPosition(false);
	resultSprite->setAnchorPoint(ccp(0.5, 0.5));
	resultSprite->setPosition(ccp(0, 10));
	resultSprite->setScale(0.7);
	resultSprite->runAction(CCSequence::create(CCScaleTo::create(0.0, 3.0),CCScaleTo::create(0.5, 1.0),NULL));

	//历史最高分的图片
	CCSprite* maxSprite = NumSprite::getNumSprite(GameShare_Global::shareGlobal()->gameProperty.highestscore, "./numberBox/lightBrown", 85, 0.5);
	maxSprite->ignoreAnchorPointForPosition(false);
	maxSprite->setAnchorPoint(ccp(0.5, 0.5));
	maxSprite->setScale(0.2);
	bgImg->addRenderer(maxSprite,10);
	maxSprite->setPosition(ccp(80, -58));


	//加入星星
	for (int i=0; i<5; i++) {
		CCSprite* starSprite = CCSprite::create("./CocoStudioResources/ItemStrengthern/EffectStar.png");
		CCSequence *seque = CCSequence::create(CCFadeTo::create(0.2, 150),CCFadeTo::create(0.3, 255),NULL);
		CCActionInterval* ccScale = CCSequence::create(CCScaleTo::create(0.2, 0.5), CCScaleTo::create(0.3, 1.0), NULL);
		CCActionInterval *spawn = CCSpawn::create(seque, ccScale, NULL);

		starSprite->runAction(CCRepeatForever::create(spawn));
		bgImg->addRenderer(starSprite, 10);
		switch (i) {
		case 0:
			starSprite->setPosition(ccp(40, 120));
			break;
		case 1:
			starSprite->setPosition(ccp(130, 50));
			break;
		case 2:
			starSprite->setPosition(ccp(60, -30));
			break;
		case 3:
			starSprite->setPosition(ccp(-150, 0));
			break;
		case 4:
			starSprite->setPosition(ccp(-70, -50));
			break;

		default:
			break;
		}
	}
}
void GameLayer_MaxScore::addSureCallbackFunc(cocos2d::CCObject *target, SEL_CallFunc callfun)
{
	this->m_pListener = target;
	this->m_pfnSelector = callfun;


}
void GameLayer_MaxScore::sureBtnCallback(cocos2d::CCObject *pSender)
{
	if (m_pListener && m_pfnSelector)
	{
		(m_pListener->*m_pfnSelector)();
	}
}
void GameLayer_MaxScore::playAgain(CCObject *p) {
	CCScene *scene_GameItem = Scene_GameItem::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.4, scene_GameItem));

}
void GameLayer_MaxScore::getButton(bool bButton)
{
	UIButton* sureBtn = dynamic_cast<UIButton*>(ulBg->getWidgetByName("Sure"));
	sureBtn->setPressedActionEnabled(true);
	sureBtn->addReleaseEvent(this, coco_releaseselector(GameLayer_MaxScore::sureBtnCallback));



	if (bButton==true||GameShare_Global::shareGlobal()->gameProperty.totolscore >= GameShare_Global::shareGlobal()->gameProperty.historyscore)
	{
		sureBtn->setTouchEnabled(true);
		sureBtn->setVisible(true);
		returnBtn->setTouchEnabled(false);
		returnBtn->setVisible(false);
		againBtn->setTouchEnable(false);
		againBtn->setVisible(false);
	} 
	else
	{
		sureBtn->setTouchEnabled(false);
		sureBtn->setVisible(false);
		returnBtn->setTouchEnabled(true);
		returnBtn->setVisible(true);
		againBtn->setTouchEnable(true);
		againBtn->setVisible(true);
	}
	//else
	//{
	//	sureBtn->setTouchEnabled(false);
	//	sureBtn->setVisible(false);
	//	returnBtn->setTouchEnabled(true);
	//	returnBtn->setVisible(true);
	//	againBtn->setTouchEnable(true);
	//	againBtn->setVisible(true);
	//}
}
void GameLayer_MaxScore::setGradeBack(float td)
{
	CCAnimation *animation = CCAnimation::create();
	CCString str;
	for (int i = 1; i < 8; i++)  
	{  
		str.initWithFormat("./CocoStudioResources/GameOver/gradeBg%d.png",i);
		animation->addSpriteFrameWithFileName(str.getCString());    
	}
	animation->setDelayPerUnit(0.1f);
	animation->setLoops(1);
	CCSprite *cloud = CCSprite::create("./CocoStudioResources/GameOver/gradeBg1.png");
	this->addChild(cloud,1);
	cloud->setPosition(ccp(320,710));
	//cloud->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
	cloud->runAction(CCRepeat::create(CCAnimate::create(animation),1.0f));
	this->scheduleOnce(schedule_selector(GameLayer_MaxScore::getGrade),1.0f);
}
void GameLayer_MaxScore::getGrade(float td)
{
	CCAnimation *animation = CCAnimation::create();
	CCString str;
	int iNum=1;
	if(GameShare_Global::shareGlobal()->gameProperty.totolscore>1)
		iNum=2;
	if(GameShare_Global::shareGlobal()->gameProperty.totolscore>10)
		iNum=3;	
	if(GameShare_Global::shareGlobal()->gameProperty.totolscore>15)
		iNum=4;	
	if(GameShare_Global::shareGlobal()->gameProperty.totolscore>50)
		iNum=5;	
	if(GameShare_Global::shareGlobal()->gameProperty.totolscore>120)
		iNum=6;	
	if(GameShare_Global::shareGlobal()->gameProperty.totolscore>500)
		iNum=7;	
	if(GameShare_Global::shareGlobal()->gameProperty.totolscore>2000)
		iNum=8;	
	if(GameShare_Global::shareGlobal()->gameProperty.totolscore>5304)
		iNum=9;	
	for (int i = 1; i < iNum; i++)  
	{  
		str.initWithFormat("./CocoStudioResources/GameOver/grade%d.png",i);
		animation->addSpriteFrameWithFileName(str.getCString()); 
	}
	animation->setDelayPerUnit(0.08f);
	animation->setLoops(1);
	pFalseGrade = CCSprite::create("./CocoStudioResources/GameOver/grade1.png");
	this->addChild(pFalseGrade,10);
	pFalseGrade->setPosition(ccp(320,725));
	pFalseGrade->runAction(CCRepeat::create(CCAnimate::create(animation),1.0f));

	this->scheduleOnce(schedule_selector(GameLayer_MaxScore::addGrade),0.7f);
	//历史最高分的图片
	//CCString str;
	//if(GameShare_Global::shareGlobal()->gameProperty.highestscore>=1000)
	//{
	//	int i = GameShare_Global::shareGlobal()->gameProperty.highestscore/1000;
	//	i = GameShare_Global::shareGlobal()->gameProperty.highestscore - i*1000;
	//	str.initWithFormat("%d",i);
	//	CCSprite *pDot = CCSprite::create("./CocoStudioResources/GameOver/dian.png");
	//	this->addChild(pDot,2);
	//	pDot->setPosition(ccp());
	//	lvLabel->setStringValue(str.getCString());
	//}
}
void GameLayer_MaxScore::addGrade(float td)
{
	this->removeChild(pFalseGrade);
	//结果的图片
	CCSprite* resultSprite = NumSprite::getNumSprite(GameShare_Global::shareGlobal()->gameProperty.totolscore, "./numberBox/whiteNumber", 40.0, 0.5);
	this->addChild(resultSprite,10);
	resultSprite->ignoreAnchorPointForPosition(false);
	resultSprite->setAnchorPoint(ccp(0.5, 0.5));
	resultSprite->setPosition(ccp(320,725));
	resultSprite->setScale(0.8);

	CCSprite* maxSprite = NumSprite::getNumSprite(GameShare_Global::shareGlobal()->gameProperty.historyscore, "./numberBox/newGrade", 85, 0.5);
	maxSprite->ignoreAnchorPointForPosition(false);
	maxSprite->setAnchorPoint(ccp(0.5, 0.5));
	maxSprite->setScale(0.2);
	this->addChild(maxSprite,10);
	maxSprite->setPosition(ccp(380,655));
	//resultSprite->runAction(CCSequence::create(CCScaleTo::create(0.0, 3.0),CCScaleTo::create(0.5, 1.0),NULL));
	this->scheduleOnce(schedule_selector(GameLayer_MaxScore::setHighestGradeBack),0.5f);
}
void GameLayer_MaxScore::setHighestGradeBack(float td)
{
	
	CCSprite *cloud = CCSprite::create("./CocoStudioResources/GameOver/highNum.png");
	this->addChild(cloud,1);
	cloud->setPosition(ccp(320,850));
	 CCActionInterval *easeElasticOut = CCEaseElasticOut::create(CCMoveTo::create(0.15,ccp(320,790)));
	cloud->runAction(easeElasticOut);
	////cloud->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
	////cloud->runAction(CCRepeat::create(CCAnimate::create(animation),1.0f));
	this->scheduleOnce(schedule_selector(GameLayer_MaxScore::setStarMedal),0.5f);

}
void GameLayer_MaxScore::setStarMedal(float td)
{
	CCAnimation *animation = CCAnimation::create();
	CCString str;
	for (int i = 1; i < 5; i++)  
	{  
		str.initWithFormat("./CocoStudioResources/GameOver/star%d.png",i);
		animation->addSpriteFrameWithFileName(str.getCString());    
	}
	animation->setDelayPerUnit(0.1f);
	animation->setLoops(1);
	CCSprite *cloud = CCSprite::create("./CocoStudioResources/GameOver/star1.png");
	this->addChild(cloud);
	cloud->setPosition(ccp(320,850));
	star1->setVisible(true);
	star2->setVisible(true);
	star3->setVisible(true);
	star4->setVisible(true);
	star5->setVisible(true);
	star6->setVisible(true);
	star7->setVisible(true);
	star8->setVisible(true);
	CCFiniteTimeAction* seq1 = CCSequence::create(CCScaleTo::create(0.5,1.8),CCScaleTo::create(0.5,2.0),NULL);
	CCFiniteTimeAction* seq2 = CCSequence::create(CCScaleTo::create(0.5,0.8),CCScaleTo::create(0.5,1.0),NULL);
	CCFiniteTimeAction* seq3 = CCSequence::create(CCScaleTo::create(0.5,1.6),CCScaleTo::create(0.5,1.8),NULL);
	CCFiniteTimeAction* seq4 = CCSequence::create(CCScaleTo::create(0.5,0.6),CCScaleTo::create(0.5,0.8),NULL);
	CCFiniteTimeAction* seq5 = CCSequence::create(CCScaleTo::create(0.5,0.3),CCScaleTo::create(0.5,0.5),NULL);
	CCActionInterval * repeatForever1 =CCRepeatForever::create((CCActionInterval* )seq2);
	CCActionInterval * repeatForever2 =CCRepeatForever::create((CCActionInterval* )seq1);
	CCActionInterval * repeatForever3 =CCRepeatForever::create((CCActionInterval* )seq1);
	CCActionInterval * repeatForever4 =CCRepeatForever::create((CCActionInterval* )seq1);
	CCActionInterval * repeatForever5 =CCRepeatForever::create((CCActionInterval* )seq2);
	CCActionInterval * repeatForever6 =CCRepeatForever::create((CCActionInterval* )seq3);
	CCActionInterval * repeatForever7 =CCRepeatForever::create((CCActionInterval* )seq4);
	CCActionInterval * repeatForever8 =CCRepeatForever::create((CCActionInterval* )seq5);
	star1->runAction(repeatForever1);
	star2->runAction(repeatForever2);
	star3->runAction(repeatForever3);
	star4->runAction(repeatForever4);
	star5->runAction(repeatForever5);
	star6->runAction(repeatForever6);
	star7->runAction(repeatForever7);
	star8->runAction(repeatForever8);
	//cloud->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
	cloud->runAction(CCRepeat::create(CCAnimate::create(animation),1.0f));
	this->schedule(schedule_selector(GameLayer_MaxScore::setEffects),1.0f);
	this->schedule(schedule_selector(GameLayer_MaxScore::getAnimation),0.3f);
}
void GameLayer_MaxScore::setEffects(float td)
{
	if(iEffectType>1)
		iEffectType=0;
	CCAnimation *animation = CCAnimation::create();
	CCString str;
	for (int i = 1; i < 7; i++)  
	{  
		str.initWithFormat("./CocoStudioResources/GameOver/flock%d.png",i);
		animation->addSpriteFrameWithFileName(str.getCString());    
	}
	animation->setDelayPerUnit(0.1f);
	animation->setLoops(1);
	if(iEffectType==0)
	{	
		pEffects->setVisible(true);
		pEffects2->setVisible(true);
		pEffects3->setVisible(true);
		pEffects->setPosition(ccp(100,860));
		pEffects->runAction(CCRepeat::create(CCAnimate::create(animation),1.0f));
		pEffects2->setPosition(ccp(550,860));
		pEffects2->runAction(CCRepeat::create(CCAnimate::create(animation),1.0f));
		pEffects3->setPosition(ccp(360,550));
		pEffects3->runAction(CCRepeat::create(CCAnimate::create(animation),1.0f));
	}
	else 
	{
		pEffects->setVisible(true);
		pEffects2->setVisible(true);
		pEffects3->setVisible(true);
		pEffects->setPosition(ccp(200,960));
		pEffects2->setPosition(ccp(400,960));
		pEffects3->setPosition(ccp(320,560));
		pEffects->runAction(CCRepeat::create(CCAnimate::create(animation),1.0f));
		pEffects2->runAction(CCRepeat::create(CCAnimate::create(animation),1.0f));
		pEffects3->runAction(CCRepeat::create(CCAnimate::create(animation),1.0f));
	}
	iEffectType++;
}
void GameLayer_MaxScore::getAnimation(float td)
{
	if(iAddTypeNum==0)
	{
		addImg->setVisible(true);
		addSprite->setVisible(true);
		addSpriteBg->setVisible(true);
	}
	else if(iAddTypeNum==1)
	{
		goldImg->setVisible(true);
		goldSprite->setVisible(true);
		goldSpriteBg->setVisible(true);
	}
	else if(iAddTypeNum==2)
	{
		expImg->setVisible(true);
		expSprite->setVisible(true);
		expSpriteBg->setVisible(true);
	}
	else if(iAddTypeNum==3)
	{
		returnBtn->setTouchEnabled(true);
		returnBtn->setVisible(true);
		againBtn->setTouchEnable(true);
		againBtn->setVisible(true);
	}
	else
		this->unschedule(schedule_selector(GameLayer_MaxScore::getAnimation));
	
	iAddTypeNum++;
}
