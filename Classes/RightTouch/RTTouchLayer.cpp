
#include "RightTouchScene.h"
#include "RTTouchLayer.h"
#include "RTItemLayer.h"
USING_NS_CC;
bool CRTTouchLayer::init()
{
   // this->setTouchEnabled(true);
    return true;
}
CRightTouchScene* CRTTouchLayer::getGameScene()
{
    return (CRightTouchScene*)this->getParent();
}
bool CRTTouchLayer::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    
    return true;
}
void CRTTouchLayer::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    
}
void CRTTouchLayer::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
   this->getGameScene()->getItemLayer()->click( touch);
}
// void CRTTouchLayer::registerWithTouchDispatcher()
// {
// 	//CCDirector* pDirector = CCDirector::sharedDirector();
// 	//pDirector->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority + 1, true);
// }
void CRTTouchLayer::setTouchEnabled(bool flag)
{
    if (m_bTouchEnabled != flag){
        m_bTouchEnabled = flag;
        if(flag){
            CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
        }else{
            CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
        }
    }
}
void CRTTouchLayer::onEnter()
{
	setTouchEnabled(true);
}
void CRTTouchLayer::onExit()
{
	setTouchEnabled(false);
}
CCPoint CRTTouchLayer::locationFromTouch(CCTouch* touch)
{
    //把点从UI坐标系转到GL坐标系
    return CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
}