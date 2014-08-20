
#include "Counter.h"
USING_NS_CC;
enum{
    k_Counter_Action = 0
};
CCounter::CCounter()
{
    _digit = 0;
}
CCounter* CCounter::create(CCArray* presenters, int digit)
{
    CCounter* counter = new CCounter();
    counter->init(presenters, digit);
    counter->autorelease();
    return counter;
}
bool CCounter::init(CCArray* presenters, int digit)
{
    _presenters = CCNode::create();
    for (int i = 0; i < 10; i++) {
        CCNode* node = (CCNode*)presenters->objectAtIndex(i);
        int y = node->getContentSize().height*i;
		if (i > 0)
		{
			CCNode* pPreNode = (CCNode*)presenters->objectAtIndex(i - 1);
			y = pPreNode->getPositionY() + pPreNode->getContentSize().height/2 + node->getContentSize().height/2 + 2;
		}
        node->setPosition(CCPointMake(0, y));
        _presenters->addChild(node, 0, i);
    }
    this->addChild(_presenters,0,k_Counter_Action);
    this->setDigit(digit,false);
    return true;
}
void CCounter::setDigit(int digit,bool bAnimate)
{
    if(_digit != digit){
        _digit = digit;
		CCNode* presenter = _presenters->getChildByTag(digit);
		CCPoint dest = presenter->getPosition();
		if(bAnimate)
			animation(digit);
		else
			_moveTo(digit,ccp(0, -dest.y));
    }
}
CCNode* CCounter::getCurrDigit()
{
	 return _presenters->getChildByTag(_digit);
}
int CCounter::getDigit()
{
    return _digit;
}
void CCounter::_moveTo(int digit,const CCPoint& pt)
{
	_presenters->setPosition(pt);
}
void CCounter::animation(int digit)
{
    CCNode* presenter = _presenters->getChildByTag(digit);
    CCPoint dest = presenter->getPosition();
   // this->stopActionByTag(k_Counter_Action);
	_presenters->stopAllActions();
    CCMoveTo* moveTo = CCMoveTo::create(0.5, CCPointMake(0, -dest.y));
    _presenters->runAction(moveTo);
}
void CCounter::visit()
{
   glEnable(GL_SCISSOR_TEST);
    CCNode* presenter = _presenters->getChildByTag(_digit);
    CCSize size = presenter->getContentSize();
    CCPoint location = this->getParent()->convertToWorldSpace(CCPointMake(this->getPosition().x-size.width*0.5, this->getPosition().y-size.height*0.5));
    glScissor(location.x, location.y, size.width * this->getParent()->getScaleX(), (size.height+2) * this->getParent()->getScaleY());
    CCNode::visit();
    glDisable(GL_SCISSOR_TEST);
}