//
//  NumSprite.cpp
//  OnceAgain
//
//  Created by mac on 14-4-17.
//
//

#include "NumSprite.h"
CCSprite* NumSprite::getNumSprite(std::string addImg, std::string lastImg, int num, std::string imgName, float offSetX ,float offset)
{
    long temp = num;
    //位数,用于设置横坐标偏移量.
    int digit = 0;
    int tempdigit = 0;
    CCString str;
    CCSprite* maxScoreSprite = CCSprite::create();

    if (temp < 0) {
        return maxScoreSprite;
    }
    if (lastImg.length() > 0) {
        CCSprite* lastSprite = CCSprite::create(lastImg.c_str());
        maxScoreSprite->addChild(lastSprite);
        tempdigit += 2;
    }
    while (temp>0 || (digit==0 && temp==0)) {
        int remainder = temp % 10;
        temp = temp/10;
        CCSprite *m_Sprite;
        CCRect rc;
        
        switch(remainder)
        {
            case 0:
            {
                str.initWithFormat("%sZero.png",imgName.c_str());
                break;
            }
            case 1:
            {
                str.initWithFormat("%sOne.png",imgName.c_str());
                
                break;
            }
            case 2:
            {
                str.initWithFormat("%sTwo.png",imgName.c_str());
                break;
            }
            case 3:
            {
                str.initWithFormat("%sThree.png",imgName.c_str());
                break;
            }
            case 4:
            {
                str.initWithFormat("%sFour.png",imgName.c_str());
                break;
            }
            case 5:
            {
                str.initWithFormat("%sFive.png",imgName.c_str());
                break;
            }
            case 6:
            {
                str.initWithFormat("%sSix.png",imgName.c_str());
                break;
            }
            case 7:
            {
                str.initWithFormat("%sSeven.png",imgName.c_str());
                break;
            }
            case 8:
            {
                str.initWithFormat("%sEight.png",imgName.c_str());
                break;
            }
            case 9:
            {
                str.initWithFormat("%sNine.png",imgName.c_str());
                
                break;
            }
            default:
            {
                str.initWithFormat("%sZero.png",imgName.c_str());
                break;
            }
        }
        
        m_Sprite = CCSprite::create(str.getCString());
        m_Sprite->setPosition(ccp((tempdigit+digit+(digit/3))*(-offSetX), 0));
        
        //            m_Sprite->setOpacity(150);
        //            maxScoreSprite->setScale(0.5);
        maxScoreSprite->addChild(m_Sprite);
        if (digit%3==0 && digit>0) {
            str.initWithFormat("%sComma.png",imgName.c_str());
            CCSprite *comma = CCSprite::create(str.getCString());;
            comma->setPosition(ccp(m_Sprite->getPositionX()+offSetX, -10));
            //                comma->setOpacity(150);
            maxScoreSprite->addChild(comma);
        }
        
        //            maxScoreSprite->setOpacity(20);
        maxScoreSprite->setPosition(ccp(80, -100));
        digit++;
        
    }
    CCSprite* addSprite = CCSprite::create(addImg.c_str());
    addSprite->setPosition(ccp((tempdigit+digit+(digit/3))*(-offSetX), 0));
    maxScoreSprite->addChild(addSprite);
    
    CCArray* array = maxScoreSprite->getChildren();
    for (int i=0; i<array->count(); i++) {
        CCPoint point = ((CCSprite*)array->objectAtIndex(i))->getPosition();
        if (offset == 0) {
            point.x += (tempdigit+digit+(digit/3))*(offSetX);
        }else if(offset == 1)
        {
            point.x += 0;
        }else
        {
            point.x += (tempdigit+digit+(digit/3))*(offSetX*offset);
        }
        
        ((CCSprite*)array->objectAtIndex(i))->setPosition(point);
    }
    return maxScoreSprite;
}

CCSprite* NumSprite::getNumSprite(int score, std::string imgName, float offSetX, float offset)
{
    long temp = score;
    //位数,用于设置横坐标偏移量.
    int digit = 0;
    CCString str;
    CCSprite* maxScoreSprite = CCSprite::create();
    if (temp < 0) {
        return maxScoreSprite;
    }
    while (temp>0 || (digit==0 && temp==0)) {
        int remainder = temp % 10;
        temp = temp/10;
        CCSprite *m_Sprite;
        CCRect rc;
        
        switch(remainder)
        {
            case 0:
            {
                str.initWithFormat("%sZero.png",imgName.c_str());
                break;
            }
            case 1:
            {
                str.initWithFormat("%sOne.png",imgName.c_str());
                
                break;
            }
            case 2:
            {
                str.initWithFormat("%sTwo.png",imgName.c_str());
                break;
            }
            case 3:
            {
                str.initWithFormat("%sThree.png",imgName.c_str());
                break;
            }
            case 4:
            {
                str.initWithFormat("%sFour.png",imgName.c_str());
                break;
            }
            case 5:
            {
                str.initWithFormat("%sFive.png",imgName.c_str());
                break;
            }
            case 6:
            {
                str.initWithFormat("%sSix.png",imgName.c_str());
                break;
            }
            case 7:
            {
                str.initWithFormat("%sSeven.png",imgName.c_str());
                break;
            }
            case 8:
            {
                str.initWithFormat("%sEight.png",imgName.c_str());
                break;
            }
            case 9:
            {
                str.initWithFormat("%sNine.png",imgName.c_str());
                
                break;
            }
            default:
            {
                str.initWithFormat("%sZero.png",imgName.c_str());
                break;
            }
        }
        
        m_Sprite = CCSprite::create(str.getCString());
        m_Sprite->setPosition(ccp((digit+(digit/3))*(-offSetX), 0));
        
        //            m_Sprite->setOpacity(150);
        //            maxScoreSprite->setScale(0.5);
        maxScoreSprite->addChild(m_Sprite);
        if (digit%3==0 && digit>0) {
            str.initWithFormat("%sComma.png",imgName.c_str());
            CCSprite *comma = CCSprite::create(str.getCString());;
            comma->setPosition(ccp(m_Sprite->getPositionX()+offSetX, -10));
            //                comma->setOpacity(150);
            maxScoreSprite->addChild(comma);
        }
        
        //            maxScoreSprite->setOpacity(20);
        maxScoreSprite->setPosition(ccp(80, -100));
        digit++;
        
    }
    digit--;
    CCArray* array = maxScoreSprite->getChildren();
    for (int i=0; i<array->count(); i++) {
        CCPoint point = ((CCSprite*)array->objectAtIndex(i))->getPosition();
        if (offset == 0) {
            point.x += (digit+(digit/3))*(offSetX);
        }else if(offset == 1)
        {
            point.x += 0;
        }else
        {
            point.x += (digit+(digit/3))*(offSetX*offset);
        }
        
        ((CCSprite*)array->objectAtIndex(i))->setPosition(point);
    }
    return maxScoreSprite;
}
void NumSprite::setSpriteTexture(CCSprite* p,CCTexture2D* pTex2D)
{
	p->setTexture(pTex2D);
	p->setTextureRect(CCRectMake(0,0,pTex2D->getContentSize().width,pTex2D->getContentSize().height));
}