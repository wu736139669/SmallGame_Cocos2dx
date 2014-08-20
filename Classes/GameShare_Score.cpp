//
//  GameShare_Score.cpp
//  OnceAgain
//
//  Created by mac on 14-3-6.
//
//

#include "GameShare_Score.h"
#include "CounterByImage.h"
const float     yValue = 50.0;
const float     xValue = 25.0;

GameShare_Score::~GameShare_Score()
{
    
}

bool GameShare_Score::init()
{
    if (!CCSprite::init()) {
        return false;
    }
    this->setContentSize(CCSize(245, 121));
    score = 0;
    
    //背景图片
   // CCSprite *scoreBgSprite = GameShare_Texture::sharedTexture()->GetSpriteByCCRect(akoopang_image, CCRect(694, 820, 245, 121));
     mpBg = CCSprite::createWithSpriteFrameName("common/score_bg.png");
    this->addChild(mpBg);
    scroeSprite = CCSprite::create();
    this->addChild(scroeSprite);
	scroeSprite->setVisible(false);
    
	VEC_NUMFILENAME vecNumFileName;
	for (int i = 0; i < 10; ++i)
	{
		CCString str;
		str.initWithFormat("common/game_score_%d.png",i);
		vecNumFileName.push_back(str.getCString());	
	}
	mpCounterImage = CCounterImage::create(vecNumFileName,"common/game_score_dot.png");
	mpCounterImage->setPositionY(-20);
	mpCounterImage->setCellNumberWidth(32);
	addChild(mpCounterImage);
	//mpCounterImage->setVisible(false);
	this->setScore(0);
    return true;
}

void GameShare_Score::setScore(long var)
{
    score = var;
    mpCounterImage->setNumber(score,true);
    long temp = score;
    //位数,用于设置横坐标偏移量.
    int digit = 0;
    scroeSprite->removeAllChildren();
    
    while (temp>0 || (digit==0 && temp==0)) {
        int remainder = temp % 10;
        temp = temp/10;
        CCSprite *m_Sprite = CCSprite::create();
        CCRect rc;
        switch(remainder)
        {
            case 0:
            {
                rc.setRect(1694, 972, 70, 70);
                break;
            }
            case 1:
            {
                rc.setRect(1, 1279, 47, 85);
                break;
            }
            case 2:
            {
                rc.setRect(337, 1054, 68, 86);
                break;
            }
            case 3:
            {
                rc.setRect(1687, 1417, 69, 84);
                break;
            }
            case 4:
            {
                rc.setRect(401, 1691, 71, 83);
                break;
            }
            case 5:
            {
                rc.setRect(1699, 105, 70, 85);
                break;
            }
            case 6:
            {
                rc.setRect(981, 1714, 69, 91);
                break;
            }
            case 7:
            {
                rc.setRect(359, 897, 64, 85);
                break;
            }
            case 8:
            {
                rc.setRect(348, 1517, 72, 88);
                break;
            }
            case 9:
            {
                rc.setRect(191, 1699, 65, 91);

                break;
            }
            default:
            {
                break;
            }
        }

        m_Sprite = GameShare_Texture::sharedTexture()->GetSpriteByCCRect(akoopang_image, rc);
        m_Sprite->setScaleX(xValue / rc.size.width);
        m_Sprite->setScaleY(yValue / rc.size.height);
        m_Sprite->setPosition(ccp((digit+(digit/3))*(-20), 0));
        scroeSprite->addChild(m_Sprite);
        if (digit%3==0 && digit>0) {
            CCSprite *comma = GameShare_Texture::sharedTexture()->GetSpriteByCCRect(akoopang_image, CCRect(252, 1076, 32, 36));
            comma->setScale(0.5);
            comma->setPosition(ccp(m_Sprite->getPositionX()+20, -20));
            scroeSprite->addChild(comma);
        }
        digit++;
    }
    scroeSprite->setPosition(ccp(digit*12 - 17, -25));
}
long GameShare_Score::getScore()
{
    return score;
}
