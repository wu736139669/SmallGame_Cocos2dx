

//#include "StaticData.h"
#include "RTBgLayer.h"
USING_NS_CC;
bool CRTBgLayer::init()
{
    if(CCLayer::init()){
		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		//mpBg = CCSprite::create("right_touch/00_board_l.png");
        //CCSprite* background = CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("background"));
		//mpBg->setAnchorPoint(ccp(0,1));
		//mpBg->setPosition(ccp(/*pSprite->getTextureRect().size.width/2 +*/ origin.x, mpBg->getTextureRect().size.height + origin.y + 400));
       // mpBg->setPosition(CCPointMake(winSize.width*0.5,winSize.height*0.5));
        //this->addChild(mpBg);
        return true;
    }
    return false;
}