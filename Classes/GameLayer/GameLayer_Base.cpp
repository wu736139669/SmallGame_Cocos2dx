//
//  GameLayer_Base.cpp
//  OnceAgain
//
//  Created by mac on 14-4-1.
//
//

#include "GameLayer_Base.h"

bool GameLayer_Base::init()
{
	return CCLayer::init();
}

void GameLayer_Base::onEnter()
{
	CCLayer::onEnter();
}

void GameLayer_Base::onExit()
{
	CCLayer::onExit();
}

void GameLayer_Base::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void GameLayer_Base::setVisible(bool visible)
{
	CCLayer::setVisible(visible);
}

bool GameLayer_Base::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return CCLayer::ccTouchBegan(pTouch,pEvent);
}

void GameLayer_Base::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	 CCLayer::ccTouchMoved(pTouch,pEvent);
}

void GameLayer_Base::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	 CCLayer::ccTouchEnded(pTouch,pEvent);
}

void GameLayer_Base::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
	 CCLayer::ccTouchCancelled(pTouch,pEvent);
}
GameLayer_Base::~GameLayer_Base()
{

}