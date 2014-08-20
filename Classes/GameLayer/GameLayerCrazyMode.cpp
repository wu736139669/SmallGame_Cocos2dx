

#include "GameLayerCrazyMode.h"
#include "SpriteFrameManage.h"
#include "TaskDefine.h"

 CGameLayerCrazyMode* CGameLayerCrazyMode::m_pInstance = NULL;

 CGameLayerCrazyMode::CGameLayerCrazyMode()
 {

 }
 CGameLayerCrazyMode::~CGameLayerCrazyMode()
 {

 }

 bool CGameLayerCrazyMode::init()
 {
	 if(!UILayer::init())
		return false;
	 auto ly = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("./CocoStudioResources/layoutCrazyMode_1.ExportJson"));
	 this->addWidget(ly);
	 setCrazyModeAni();
	 return true;
 }
 void CGameLayerCrazyMode::play(ECrazyMode eMode)
 {
     if(eMode == eComCrazyMode)
         CTaskManProceDt(eDayTaskTypeShare_3,1);
	 //////////////////////////////////////////////////////////////////////////
	 //背景动画效果
	 UIImageView* plightBg = dynamic_cast<UIImageView*>(this->getWidgetByName("crazy_light_bg"));
	 plightBg->setScaleX(0.35f);plightBg->setScaleY(0.26f);
	 float fC = 1.f;
	 CCFiniteTimeAction* pAc1 = CCScaleTo::create(0.2f*fC,0.29f,1.31f);
	 CCFiniteTimeAction* pAc2 = CCScaleTo::create(0.2f*fC,1.20f,0.64f);
	 CCFiniteTimeAction* pAc3 = CCScaleTo::create(0.2f*fC,1.f,1.f);
	 CCFiniteTimeAction* pAcb1 = CCScaleTo::create(0.2f*fC,0.35f,0.26f);
	 CCFiniteTimeAction* pAcb2 = CCScaleTo::create(0.2f*fC,0.29f,1.31f);
	 CCFiniteTimeAction* pAcb3 = CCScaleTo::create(0.2f*fC,1.20f,0.64f);
	 CCFiniteTimeAction* pLightBgEffect = CCRepeat::create(CCSequence::create(CCScaleTo::create(0.2f*fC,0.83f,1.39f),CCScaleTo::create(0.2f*fC,1.f,1.f),NULL),2);
	 CCActionInterval* pAction = CCSequence::create(CCShow::create(),pAc1, pAc2, pAc3,/*pLightBgEffect*/CCDelayTime::create(0.8f),pAcb3,pAcb2,pAcb1,CCHide::create(), NULL);
	 plightBg->runAction(pAction);
	 //文字动画效果
	this->getWidgetByName("crazy_super_txt")->setVisible(false);
	this->getWidgetByName("super_txt")->setVisible(false);
	UIImageView* ptxt = NULL;
	 if (eMode == eSuperCrazyMode){
		 ptxt = dynamic_cast<UIImageView*>(this->getWidgetByName("crazy_super_txt"));
	 }else
	 {
		ptxt = dynamic_cast<UIImageView*>(this->getWidgetByName("super_txt"));
	 }
	 ptxt->setScaleX(0.35f);ptxt->setScaleY(0.26f);
	 CCFiniteTimeAction* pAcTxt1 = CCScaleTo::create(0.2f*fC,0.29f,1.31f);
	 CCFiniteTimeAction* pAcTxt2 = CCScaleTo::create(0.2f*fC,1.20f,0.64f);
	 CCFiniteTimeAction* pAcTxt3 = CCScaleTo::create(0.2f*fC,1.f,1.f);
	 CCFiniteTimeAction* pAcTxtb1 = CCScaleTo::create(0.2f*fC,0.35f,0.26f);
	 CCFiniteTimeAction* pAcTxtb2 = CCScaleTo::create(0.2f*fC,0.29f,1.31f);
	 CCFiniteTimeAction* pAcTxtb3 = CCScaleTo::create(0.2f*fC,1.20f,0.64f);
	 CCActionInterval* pActionTxt = CCSequence::create(CCShow::create(),pAcTxt1, pAcTxt2, pAcTxt3,CCDelayTime::create(1.f),pAcTxtb3,pAcTxtb2,pAcTxtb1,CCHide::create(), NULL);
	 ptxt->runAction(pActionTxt);

	 operateAllSchedulerAndActions(this,eSwitcResume);

	 CCArray* array = this->getChildren();
	 if(array != NULL && array->count()>0){
		 CCObject* iterator;
		 CCARRAY_FOREACH(array, iterator){
			 CCNode* child = (CCNode*)iterator;
			 if(child->getTag() == eStarEffectIDStar)
				 child->setVisible(false);
		 }
	 }
	 if (eMode == eSuperCrazyMode)
	 {
		 array = this->getChildren();
		 if(array != NULL && array->count()>0){
			 CCObject* iterator;
			 CCARRAY_FOREACH(array, iterator){
				 CCNode* child = (CCNode*)iterator;
				 if(child->getTag() == eStarEffectIDStar)
					 child->setVisible(true);
			 }
		 }
	 }
 }
 void CGameLayerCrazyMode::pause()
 {
	 operateAllSchedulerAndActions(this,eSwitchPause);

	 UIImageView* plightBg = dynamic_cast<UIImageView*>(this->getWidgetByName("crazy_light_bg"));
	 plightBg->stopAllActions();
	 UIImageView* ptxt = dynamic_cast<UIImageView*>(this->getWidgetByName("crazy_super_txt"));
	 ptxt->stopAllActions();
 }
 void CGameLayerCrazyMode::operateAllSchedulerAndActions(cocos2d::CCNode* node, ESwitchFlag flag)
 {
	 if(node->isRunning()){
		 switch (flag) {
		 case eSwitchPause:
			 node->pauseSchedulerAndActions();
			 break;
		 case eSwitcResume:
			 node->resumeSchedulerAndActions();
			 break;
		 default:
			 break;
		 }
		 CCArray* array = node->getChildren();
		 if(array != NULL && array->count()>0){
			 CCObject* iterator;
			 CCARRAY_FOREACH(array, iterator){
				 CCNode* child = (CCNode*)iterator;
				 this->operateAllSchedulerAndActions(child, flag);
			 }
		 }
	 }
 }
 void CGameLayerCrazyMode::setCrazyModeAni()
 {
	 CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	 //////////////////////////////////////////////////////////////////////////
	 //星星效果
	 CCSize szOffect(100,80);
	 bool bYellowType = false;
	 //上边
	 for (int i = 0; i < 7; ++i)
	 {
		 auto pStarYellow = CCSprite::createWithSpriteFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName("ct/star_yellow_1.png"));
		 pStarYellow->setTag(eStarEffectIDStar);
		 setStarAni(pStarYellow,bYellowType = !bYellowType);
		 pStarYellow->setPosition(ccp(pStarYellow->getContentSize().width/2 - 20 + ( i * szOffect.width/*pStarYellow->getContentSize().width*/ ),visibleSize.height + 20 - pStarYellow->getContentSize().height/2));
		 //this->addChild(pStarYellow,5);
		 this->addChild(pStarYellow,5);
	 }
	 //下边
	 bYellowType = false;
	 for (int i = 0; i < 7; ++i)
	 {
		 auto pStarYellow = CCSprite::createWithSpriteFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName("ct/star_yellow_1.png"));
		 pStarYellow->setTag(eStarEffectIDStar);
		 setStarAni(pStarYellow,bYellowType = !bYellowType);
		 pStarYellow->setPosition(ccp(pStarYellow->getContentSize().width/2 - 20 + ( i * szOffect.width/*pStarYellow->getContentSize().width*/ ),pStarYellow->getContentSize().height/2 - 20));
		 //this->addChild(pStarYellow,5);
		 this->addChild(pStarYellow,5);
	 }
	 //左边
	 bYellowType = true;
	 for (int i = 0; i < 13; ++i)
	 {
		 auto pStarYellow = CCSprite::createWithSpriteFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName("ct/star_yellow_1.png"));
		 pStarYellow->setTag(eStarEffectIDStar);
		 setStarAni(pStarYellow,bYellowType = !bYellowType);
		 pStarYellow->setPosition(ccp(pStarYellow->getContentSize().width/2 - 20 , visibleSize.height - 98 - szOffect.height * i));
		 //this->addChild(pStarYellow,5);
		 this->addChild(pStarYellow,5);
	 }
	 //右边
	 bYellowType = true;
	 for (int i = 0; i < 13; ++i)
	 {
		 auto pStarYellow = CCSprite::createWithSpriteFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName("ct/star_yellow_1.png"));
		 pStarYellow->setTag(eStarEffectIDStar);
		 setStarAni(pStarYellow,bYellowType = !bYellowType);
		 pStarYellow->setPosition(ccp(visibleSize.width - 20 , visibleSize.height - 98 - szOffect.height * i));
		 //this->addChild(pStarYellow,5);
		 this->addChild(pStarYellow,5);
	 }
	 //上面高光
	 CCString strFileName;
	 CCAnimation* pAni = CCAnimation::create();
	 for (int i = 1; i <= 9; ++i){
		 strFileName.initWithFormat("ct/crazy_light_%d.png",i);
		 pAni->addSpriteFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName(strFileName.getCString()));
	 }
	 pAni->setDelayPerUnit(0.7f/9.f);
	 pAni->setLoops(1);
	 auto pLighting = CCSprite::createWithSpriteFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName("ct/crazy_light_1.png"));
	 pLighting->runAction(CCRepeatForever::create(CCAnimate::create(pAni)));
	 pLighting->setTag(eStarEffectIDBegin);
	 pLighting->setPosition(ccp(visibleSize.width/2 , visibleSize.height - pLighting->getContentSize().height/2));
	 //this->addChild(pLighting,5);
	 this->addChild(pLighting,5);
	 //////////////////////////////////////////////////////////////////////////

	 //////////////////////////////////////////////////////////////////////////
	 //////////////////////////////////////////////////////////////////////////
	 //
	 UIImageView* pSide = dynamic_cast<UIImageView*>(this->getWidgetByName("side_t"));
	 CCActionInterval* pInter1 = CCFadeOut::create(0.15f);
	 pSide->runAction(CCRepeatForever::create(CCSequence::create(pInter1,pInter1->reverse(),NULL)));
	 pSide = dynamic_cast<UIImageView*>(this->getWidgetByName("side_b"));
	 CCActionInterval* pInter2 = CCFadeOut::create(0.15f);
	 pSide->runAction(CCRepeatForever::create(CCSequence::create(pInter2,pInter2->reverse(),NULL)));
	 pSide = dynamic_cast<UIImageView*>(this->getWidgetByName("side_l"));
	 CCActionInterval* pInter3 = CCFadeOut::create(0.15f);
	 pSide->runAction(CCRepeatForever::create(CCSequence::create(pInter3,pInter3->reverse(),NULL)));
	 pSide = dynamic_cast<UIImageView*>(this->getWidgetByName("side_r"));
	 CCActionInterval* pInter4 = CCFadeOut::create(0.15f);
	 pSide->runAction(CCRepeatForever::create(CCSequence::create(pInter4,pInter4->reverse(),NULL)));
	 //上面高光
	 // 	CCString strFileName;
	 // 	CCAnimation* pAni = CCAnimation::create();
	 // 	for (int i = 1; i <= 9; ++i){
	 // 		strFileName.initWithFormat("common/crazy_light_%d.png",i);
	 // 		pAni->addSpriteFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName(strFileName.getCString()));
	 // 	}
	 // 	pAni->setDelayPerUnit(0.7f);
	 // 	pAni->setLoops(1);
	 // 	auto pLighting = dynamic_cast<UIImageView*>(mpUILayer->getWidgetByName("light_top"));
	 // 	pLighting->runAction(CCRepeatForever::create(CCAnimate::create(pAni)));
 }
 void CGameLayerCrazyMode::setStarAni(CCSprite* pStar,bool bYellow)
 {
	 CCString strFileName;
	 int nFrameCounter = 0;
	 CCAnimation* pAni = CCAnimation::create();
	 if (bYellow)
	 {
		 //播放黄色
		 for (int i = 1; i <= 6; ++i){
			 nFrameCounter++;
			 strFileName.initWithFormat("ct/star_yellow_%d.png",i);
			 pAni->addSpriteFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName(strFileName.getCString()));
		 }
		 nFrameCounter++;
		 pAni->addSpriteFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName("ct/star_blank.png"));
		 for (int i = 7; i <= 9; ++i){
			 nFrameCounter++;
			 strFileName.initWithFormat("ct/star_yellow_%d.png",i);
			 pAni->addSpriteFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName(strFileName.getCString()));
		 }
		 //播放紫色
		 for (int i = 1; i <= 6; ++i)
		 {
			 nFrameCounter++;
			 strFileName.initWithFormat("ct/star_purple_%d.png",i);
			 pAni->addSpriteFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName(strFileName.getCString()));
		 }
		 nFrameCounter++;
		 pAni->addSpriteFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName("ct/star_blank.png"));
		 for (int i = 7; i <= 9; ++i){
			 nFrameCounter++;
			 strFileName.initWithFormat("ct/star_purple_%d.png",i);
			 pAni->addSpriteFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName(strFileName.getCString()));
		 }
	 }else
	 {
		 //播放黄色
		 for (int i = 1; i <= 5; ++i){
			 nFrameCounter++;
			 strFileName.initWithFormat("ct/star_white_%d.png",i);
			 pAni->addSpriteFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName(strFileName.getCString()));
		 }
		 for (int i = 1; i <= 5; ++i){
			 nFrameCounter++;
			 strFileName.initWithFormat("ct/star_blue_%d.png",i);
			 pAni->addSpriteFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName(strFileName.getCString()));
		 }
	 }

	 pAni->setDelayPerUnit(0.05f);
	 pAni->setLoops(1);

	 CCActionInterval*  pAction = CCSequence::create(CCAnimate::create(pAni),NULL);
	 pStar->runAction(CCRepeatForever::create(pAction));
 }