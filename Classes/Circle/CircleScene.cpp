

#include "GameShare_TimeProcess.h"
#include "Scene_GameOver.h"
#include "RandomUtil.h"
#include "TaikoScene.h"
#include "CircleScene.h"

USING_NS_CC;
#define _OffsetY_Max  150
static const int FIELD_WIDTH = 87;
static const int FIELD_HIGH = 87;
CCircleScene::CCircleScene():mulLastTouchTime(0)
{

}
CCircleScene::~CCircleScene()
{
// 	for (int i = 0 ; i < mVecFruit.size(); ++i)
// 	{
// 		CGameFruit* pFruit = mVecFruit[i];
// 		CC_SAFE_RELEASE_NULL(pFruit);
// 
// 	}
// 	//CFruitData* pData = ;
// 	CFruitData::getInstance()->purge();
}
CCScene* CCircleScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	//    HelloWorld *layer = HelloWorld::create();

	CCircleScene *layer = CCircleScene::create();

	// add layer as a child to scene
	 scene->addChild(layer);

	// return the scene
	return scene;
}

bool CCircleScene::init()
{
	if (!GameShare_Scene::init()) {
		return false;
	}

	//设置分数
	this->setScore(0/*CFruitData::getInstance()->getScore()*/);
	//设置能力最大值
	boom_setMaxBoomEnergy();
	
	//this->addEnergy();

	//设置连击.
	//if( CFruitData::getInstance()->getContinueNum() > 0)
	//this->setBatter(CFruitData::getInstance()->getContinueNum());

	//InitListerner();
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	

	this->setTouchEnabled(true);
	
	start();
	return true;
	
}
void CCircleScene::start()
{  
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	for (int i = 0; i < 5; ++i)
	{
		CCString str;
		str.initWithFormat("circle/%d.png",i+2);
		mpSp[i] = CCSprite::create(str.getCString());
		mpSp[i]->setVisible(true);
		addChild(mpSp[i],2);
		mpSp[i]->setPosition(ccp(visibleSize.width/2,/*visibleSize.height/2*/340+132));
		if (i == 0)
		{
			mpSp[i]->runAction( CCRepeatForever::create(CCRotateBy::create(0.2, 15)));
		}else if ( i == 1)
		{
			mpSp[i]->runAction( CCRepeatForever::create(CCRotateBy::create(0.4, -15)));
		}else if ( i == 2)
		{
			mpSp[i]->runAction( CCRepeatForever::create(CCRotateBy::create(0.8, 15)));
		}else if ( i == 3)
		{
			mpSp[i]->runAction( CCRepeatForever::create(CCRotateBy::create(0.2, -15)));
		}
		
	}
	
	
}
//单击事件开始
bool CCircleScene::ccTouchBegan(cocos2d::CCTouch * pTouch, cocos2d::CCEvent *pEvent)
{
	CCPoint ptouch = pTouch->getLocationInView();

	//CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	
	return true;
}
//单击事件拖动
void CCircleScene::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	
}

//单击事件结束
void CCircleScene::ccTouchEnded(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent)
{
	
}


//注册单击事件
void CCircleScene::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority + 1, true);
}
void CCircleScene::update(float fDelta)
{
	
}
void CCircleScene::addTarget()
{
	
}
void CCircleScene::onEnter()
{
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(this, 0, false);
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
}
void CCircleScene::onExit()
{
	CCLayer::onExit();
	CCDirector::sharedDirector()->getScheduler()->unscheduleUpdateForTarget(this);
}
// a selector callback
void CCircleScene::menuCloseCallback(CCObject* pSender)
{
}
void CCircleScene::InitListerner()
{
	//CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(CTaikoScene::MsgHanlde_GameTimeOut), kGameTimeOutName, NULL);
}

void CCircleScene::MsgHanlde_GameTimeOut(CCObject* obj)
{
// 	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, kGameTimeOutName);
// 
// 	CCUserDefault::sharedUserDefault()->setDoubleForKey(KEY_LINK_MAXSCORE, (double)m_nSumCount);
// 	CCUserDefault::sharedUserDefault()->flush();
// 	CCScene*        scene = CCScene::create();
// 	Scene_GameOver* layer = Scene_GameOver::create();
// 	layer->ScoreToSprite(m_nSumCount);
// 	scene->addChild(layer);
// 	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, scene));
}
//疯狂模式结束消息处理函数
void CCircleScene::msgHandle_CrazyTimeOut(CCObject* obj)
{
	//重置连续次数
// 	CFruitData::getInstance()->setContinueNum(0);
// 	CFruitData::getInstance()->setCrazyContinueNum(0);
}