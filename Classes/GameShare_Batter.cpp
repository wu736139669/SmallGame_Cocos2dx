//
//  GameShare_Batter.cpp
//  OnceAgain
//
//  Created by mac on 14-3-7.
//
//

#include "GameShare_Batter.h"
#include "CounterByImage.h"
const float     yValue = 50.0;
const float     xValue = 25.0;

GameShare_Batter::~GameShare_Batter()
{
    
}

bool GameShare_Batter::init()
{
    if (!CCSprite::init()) {
        return false;
    }
   // CCSprite* batterSprite = GameShare_Texture::sharedTexture()->GetSpriteByCCRect(akoopang_image, CCRect(1185, 1161, 164, 94));
	mpContinueHit = CCSprite::createWithSpriteFrameName("common/continue_hit.png");
	//mpContinueHit->setVisible(false);
    //this->addChild(mpContinueHit);
    //batterSprite->setPosition(ccp(120, 0));
    
//     numSprite = CCSprite::create();
//     numSprite->setPosition(ccp(0, 0));
//     this->addChild(numSprite);
//     this->setVisible(false);
	VEC_NUMFILENAME vecNumFileName;
	for (int i = 0; i < 10; ++i)
	{
		CCString str;
		str.initWithFormat("common/num_1/common_num_%d.png",i);
		vecNumFileName.push_back(str.getCString());	
	}
	mpCounterImage = CCounterImage::create(vecNumFileName,"common/game_score_dot.png",0,false);
	//mpCounterImage->setPosition(ccp(120, 0));
	mpCounterImage->setCellNumberWidth(69);
	addChild(mpContinueHit);
	addChild(mpCounterImage);
    return true;
}
int GameShare_Batter::getRealWidth()
{
	return mpCounterImage->getTotalWidth() + mpContinueHit->getContentSize().width;
}
void GameShare_Batter::setBatter(unsigned int batterNum)
{
	if(batterNum == 0)
		return;
	mpCounterImage->setNumber(batterNum,false);
	mpContinueHit->setPositionX(mpCounterImage->getPositionX() + mpCounterImage->getTotalWidth()/2 + mpContinueHit->getContentSize().width/2);
//     long temp = batterNum;
//     //位数,用于设置横坐标偏移量.
//     int digit = 0;
//     numSprite->removeAllChildren();
//     
//     while (temp>0 || (digit==0 && temp==0)) {
//         int remainder = temp % 10;
//         temp = temp/10;
//         CCSprite *m_Sprite = CCSprite::create();
//         CCRect rc;
//         switch(remainder)
//         {
//             case 0:
//             {
//                 rc.setRect(1694, 972, 70, 70);
//                 break;
//             }
//             case 1:
//             {
//                 rc.setRect(1, 1279, 47, 85);
//                 break;
//             }
//             case 2:
//             {
//                 rc.setRect(337, 1054, 68, 86);
//                 break;
//             }
//             case 3:
//             {
//                 rc.setRect(1687, 1417, 69, 84);
//                 break;
//             }
//             case 4:
//             {
//                 rc.setRect(401, 1691, 71, 83);
//                 break;
//             }
//             case 5:
//             {
//                 rc.setRect(1699, 105, 70, 85);
//                 break;
//             }
//             case 6:
//             {
//                 rc.setRect(981, 1714, 69, 91);
//                 break;
//             }
//             case 7:
//             {
//                 rc.setRect(359, 897, 64, 85);
//                 break;
//             }
//             case 8:
//             {
//                 rc.setRect(348, 1517, 72, 88);
//                 break;
//             }
//             case 9:
//             {
//                 rc.setRect(191, 1699, 65, 91);
//                 
//                 break;
//             }
//             default:
//             {
//                 break;
//             }
//         }
//         
//         m_Sprite = GameShare_Texture::sharedTexture()->GetSpriteByCCRect(akoopang_image, rc);
//         m_Sprite->setScaleX(xValue / rc.size.width);
//         m_Sprite->setScaleY(yValue / rc.size.height);
//         m_Sprite->setPosition(ccp((digit+(digit/3))*(-20), 0));
//         numSprite->addChild(m_Sprite);
//         if (digit%3==0 && digit>0) {
//             CCSprite *comma = GameShare_Texture::sharedTexture()->GetSpriteByCCRect(akoopang_image, CCRect(252, 1076, 32, 36));
//             comma->setScale(0.5);
//             comma->setPosition(ccp(m_Sprite->getPositionX()+20, -20));
//             numSprite->addChild(comma);
//         }
//         digit++;
//     }
//     numSprite->setPosition(ccp(digit*12, 0));
//   
	//setScale(0.8f);
	CCActionInterval* pAct = CCScaleTo::create(0.5, 1.05f);
	 CCActionInterval* pAct1 = CCScaleTo::create(0.1, 1.f);
    // this->runAction(CCSequence::create(CCShow::create(),pAct,pAct1,CCHide::create(),NULL));
	this->runAction(CCSequence::create(CCShow::create(),CCDelayTime::create(1.f)/*,CCFadeIn::create(2.f)*/,CCHide::create(),NULL));
}