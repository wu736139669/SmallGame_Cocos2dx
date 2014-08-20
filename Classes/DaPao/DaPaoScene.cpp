

#include "GameShare_TimeProcess.h"
#include "Scene_GameOver.h"
#include "RandomUtil.h"

#include "DaPaoScene.h"
#include "SpriteFrameManage.h"

USING_NS_CC;
#define _OffsetY_Max  150
static const int FIELD_WIDTH = 87;
static const int FIELD_HIGH = 87;
enum
{
	eDaPaoPoint = 10,
	eDaPaoPointSlot,
};
CDaPaoScene::CDaPaoScene():mulLastTouchTime(0)
{

}
CDaPaoScene::~CDaPaoScene()
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
CCScene* CDaPaoScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	//    HelloWorld *layer = HelloWorld::create();

	CDaPaoScene *layer = CDaPaoScene::create();

	// add layer as a child to scene
	 scene->addChild(layer);

	// return the scene
	return scene;
}
void CDaPaoScene::initBgView()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCSprite* pSprite = CCSprite::createWithSpriteFrameName("da_pao/bg.png");
	pSprite->setPosition(ccp(visibleSize.width/2 , visibleSize.height/2));
	this->addChild(pSprite, 0);
}
bool CDaPaoScene::init()
{
	 CCSpriteFrameManage::getInstance()->addSpriteFramesWithFile("./da_pao/DaPao0.plist", "./da_pao/DaPao0.png");  
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
	_visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	

	this->setTouchEnabled(true);
	
	start();
	return true;
	
}
void CDaPaoScene::start()
{  
	
	CCSprite* p =  CCSprite::createWithSpriteFrameName("da_pao/point_slot.png");
	p->setPosition(ccp(p->getContentSize().width/2,_visibleSize.height/2 - 200 ));
	p->setTag(eDaPaoPointSlot);
	addChild(p,2);
	CCRect rc(p->getPositionX() - p->getContentSize().width/2,
		p->getPositionY() - p->getContentSize().height/2,
		p->getContentSize().width,
		p->getContentSize().height
		);
	_rcSlot = rc;
	CCSprite* p1 =  CCSprite::createWithSpriteFrameName("da_pao/point.png");
	p1->setPosition(ccp(rc.getMinX(),rc.getMidY()));
	p1->setTag(eDaPaoPoint);
	addChild(p1,2);
	p1->runAction(CCMoveTo::create(1.5f,ccp(rc.getMaxX(),rc.getMidY())));
}
//单击事件开始
bool CDaPaoScene::ccTouchBegan(cocos2d::CCTouch * pTouch, cocos2d::CCEvent *pEvent)
{
	CCPoint ptouch = pTouch->getLocationInView();
	CCPoint ccTouchSprite = CCDirector::sharedDirector()->convertToGL(ptouch);
	CCSprite* p = CCSprite::createWithSpriteFrameName("da_pao/bullet.png");
	p->setPosition(ccp(_visibleSize.width/2, _visibleSize.height - 946));
	addChild(p,2);
	
	//CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	int nLev = 0;
	if (getChildByTag(eDaPaoPoint)->getPositionX() < _rcSlot.getMinX() + (_rcSlot.size.width / 3.f) * 1)
	{
		nLev = 1;
	}
	else if (getChildByTag(eDaPaoPoint)->getPositionX() < _rcSlot.getMinX() + (_rcSlot.size.width / 3.f) * 2)
	{
		nLev = 2;
	}else{
		nLev = 3;
	}
	SBulletInfo sInfo = {p,nLev,nLev};
	_vecBullet.push_back(sInfo);
	p->runAction(CCSequence::create(CCMoveTo::create(1.f,ccp(ccTouchSprite.x,ccTouchSprite.y)),CCCallFuncND::create(this,callfuncND_selector(CDaPaoScene::callbackBullet)
		,(void*)_vecBullet[_vecBullet.size() - 1].pBullet),NULL));
	this->getChildByTag(eDaPaoPoint)->setPosition(ccp(_rcSlot.getMinX(),_rcSlot.getMidY()));
	this->getChildByTag(eDaPaoPoint)->stopAllActions();
	this->getChildByTag(eDaPaoPoint)->runAction(CCMoveTo::create(1.5f,ccp(_rcSlot.getMaxX(),_rcSlot.getMidY())));
	return true;
}
//单击事件拖动
void CDaPaoScene::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	
}

//单击事件结束
void CDaPaoScene::ccTouchEnded(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent)
{
	
}

void CDaPaoScene::callbackBullet(CCNode* n, void* v)
{
	for (int i = 0; i < _vecBullet.size(); ++i)
	{
		CCSprite* p = _vecBullet[i].pBullet;
		if ( (CCNode*)p == n)
		{
			removeChild(p);
			_vecBullet.erase(_vecBullet.begin() + i);

		}
	}
}
//注册单击事件
void CDaPaoScene::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority + 1, true);
}
void CDaPaoScene::update(float fDelta)
{
	CCNode::update(fDelta);
	addTarget(_vecItem[2],ccp(0,_visibleSize.height - 393 - 105 - 105),true);
	
	addTarget(_vecItem[1],ccp(_visibleSize.width,_visibleSize.height - 393 - 105),false);
	addTarget(_vecItem[0],ccp(0,_visibleSize.height - 393),true);
	
	updataBullet(_vecItem[2]);
	updataBullet(_vecItem[1]);
	updataBullet(_vecItem[0]);
}
void CDaPaoScene::updataBullet(VEC_ITEM& vecItem)
{
	for (int j = 0; j < vecItem.size(); ++j)
	{
		CCSprite* pTempItem = vecItem[j];
		CCRect rcItem(pTempItem->getPositionX() - pTempItem->getContentSize().width/2,
			pTempItem->getPositionY()-pTempItem->getContentSize().height/2,
			pTempItem->getContentSize().width,pTempItem->getContentSize().height);
		for (int i = 0; i< _vecBullet.size(); ++i)
		{
			CCSprite* pTempBullet = _vecBullet[i].pBullet;
			// 			CCRect rcBullet(pTempBullet->getPositionX() - pTempBullet->getContentSize().width/2,
			// 				pTempBullet->getPositionY()-pTempBullet->getContentSize().height/2,
			// 				pTempBullet->getContentSize().width,pTempBullet->getContentSize().height);
			if(rcItem.containsPoint(pTempBullet->getPosition()))
			{
				removeChild(vecItem[j]);
				vecItem.erase(vecItem.begin()+j);
				//vecItem[j]->setVisible(false);
				_vecBullet[i].nCounter--;
				CCLOG("nCounter:%d",_vecBullet[i].nCounter);
				if (_vecBullet[i].nCounter <= 0)
				{
					removeChild(pTempBullet);
					_vecBullet.erase(_vecBullet.begin() + i);
				}

			}

		}

	}
}
void CDaPaoScene::addTarget(VEC_ITEM& vecItem,CCPoint pt,bool bMoveRight)
{
	//mulLastTouchTime += fDelta * 1000;
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint pt1 = pt;
	if (vecItem.empty()){
		CCSprite* p =  CCSprite::createWithSpriteFrameName("da_pao/item.png");
		p->setPosition(pt1);
		if(bMoveRight)
			p->runAction(CCMoveTo::create(4.f,ccp(_visibleSize.width + p->getContentSize().width/2,pt1.y)));
		else
			p->runAction(CCMoveTo::create(4.f,ccp(-p->getContentSize().width/2,pt1.y)));
		addChild(p,1);
		vecItem.push_back(p);
	}else{
		float fDir = ccpDistance(vecItem[vecItem.size()-1]->getPosition(),pt1);
		if( fDir >= 100){
			CCSprite* p =  CCSprite::createWithSpriteFrameName("da_pao/item.png");
			p->setPosition(pt1);
			if(bMoveRight)
				p->runAction(CCMoveTo::create(4.f,ccp(_visibleSize.width + p->getContentSize().width/2,pt1.y)));
			else
				p->runAction(CCMoveTo::create(4.f,ccp(-p->getContentSize().width/2,pt1.y)));
			addChild(p,1);
			vecItem.push_back(p);
		}
	}
	if (!vecItem.empty()){
		CCSprite* p = vecItem[0];
		if (p->getPositionX() > _visibleSize.width){
			//vecItem[vecItem.size()-1]->setPositionX(-vecItem[vecItem.size()-1]->getContentSize().width/2);
			vecItem.erase(vecItem.begin());
			removeChild(p);
		}
	}
	//////////////////////////////////////////////////////////////////////////
	
}
void CDaPaoScene::onEnter()
{
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(this, 0, false);
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
}
void CDaPaoScene::onExit()
{
	CCLayer::onExit();
	CCDirector::sharedDirector()->getScheduler()->unscheduleUpdateForTarget(this);
}
// a selector callback
void CDaPaoScene::menuCloseCallback(CCObject* pSender)
{
}
void CDaPaoScene::InitListerner()
{
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(CDaPaoScene::MsgHanlde_GameTimeOut), kGameTimeOutName, NULL);
}

void CDaPaoScene::MsgHanlde_GameTimeOut(CCObject* obj)
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
void CDaPaoScene::msgHandle_CrazyTimeOut(CCObject* obj)
{
	//重置连续次数
// 	CFruitData::getInstance()->setContinueNum(0);
// 	CFruitData::getInstance()->setCrazyContinueNum(0);
}