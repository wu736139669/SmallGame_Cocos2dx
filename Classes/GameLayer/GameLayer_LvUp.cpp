//
//  GameLayer_LvUp.cpp
//  OnceAgain
//
//  Created by mac on 14-4-15.
//
//

#include "GameLayer_LvUp.h"
#include "StringUtil.h"
#include "XQDate.h"
#include "PlayerInfoManager.h"
#include "GameInfoManager.h"
//#include "GameShare_Property.h"
#include "GameShare_Global.h"


GameLayer_LvUp::~GameLayer_LvUp()
{
    GUIReader::shareReader()->purgeGUIReader();
	DictionaryHelper::shareHelper()->purgeDictionaryHelper();
	ActionManager::shareManager()->purgeActionManager();
}

bool GameLayer_LvUp::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //升级.
    levelUpUl = UILayer::create();
    auto levelUpLayout = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("./CocoStudioResources/LevelUplayer.json"));
    levelUpUl->addWidget(levelUpLayout);
    levelUpUl->setContentSize(visibleSize);

    
    this->addChild(levelUpUl);
    UIImageView* box_1 = dynamic_cast<UIImageView*>(levelUpUl->getWidgetByName("Image_11_0"));
    UIImageView* box_2 = dynamic_cast<UIImageView*>(levelUpUl->getWidgetByName("Image_11"));
   
    sGameProperty& gameProperty = GameShare_Global::shareGlobal()->gameProperty;
    //升级获取金币加成奖励.
    CCSprite* levelAddGold = this->getAddGoldByScore(gameProperty.levelrewardvalue);
    levelAddGold ->setPosition(ccp(90, 0));
    box_1->addCCNode(levelAddGold);
    //升级获取的加成.
    CCSprite* experience = this->getAddExperienceScore(gameProperty.leveladdscore);
    experience ->setPosition(ccp(90, 0));
    box_2 -> addCCNode(experience);
    
    centerArrow = dynamic_cast<UIImageView*>(levelUpUl -> getWidgetByName("Image_5"));
    centerArrow -> setAnchorPoint(ccp(0.5, 0));
    centerArrow -> setPosition(ccp(centerArrow->getPosition().x, centerArrow->getPosition().y - 130));
        
    UIButton* levelUpBtn = dynamic_cast<UIButton*>(levelUpUl->getWidgetByName("SureBtn"));
    levelUpBtn->addReleaseEvent(this, coco_releaseselector(GameLayer_LvUp::sureCallback));
    levelUpBtn->setPressedActionEnabled(true);
    //动作
    
    this->setAction();
    
    UIImageView *light = dynamic_cast<UIImageView*>(levelUpUl->getWidgetByName("Light"));
    CCRotateBy *rotate = CCRotateBy::create(2, 45);
    light -> runAction(CCRepeatForever::create(rotate));
    
    CCScaleTo *toBig = CCScaleTo::create(0.4, 1.1);
    CCScaleTo *toS = CCScaleTo::create(0.4, 0.9);
    CCSequence *center = CCSequence::create(toBig, toS, NULL);
    centerArrow -> runAction(CCRepeatForever::create(center));
    
    UIImageView *left  = dynamic_cast<UIImageView*>(levelUpUl -> getWidgetByName("Image_5_1"));
    CCScaleTo *toBig1 = CCScaleTo::create(0.5, 1.2);
    CCScaleTo *toS1 = CCScaleTo::create(0.5, 1);
    CCSequence *center1 = CCSequence::create(toBig1, toS1, NULL);
    left ->runAction(CCRepeatForever::create(center1));
    
    UIImageView *right = dynamic_cast<UIImageView*>(levelUpUl -> getWidgetByName("Image_5_0"));
    CCScaleTo *toBig2 = CCScaleTo::create(0.5, 1.2);
    CCScaleTo *toS2 = CCScaleTo::create(0.5, 1);
    CCSequence *center2 = CCSequence::create(toBig2, toS2, NULL);

    right -> runAction(CCRepeatForever::create(center2));
    
    return true;
}

void GameLayer_LvUp::addSureCallback(CCObject* target1, SEL_CallFunc callfun)
{
    target = target1;
    seletor = callfun;
}
void GameLayer_LvUp::sureCallback(CCObject *p) {
    if (target && seletor) {
        (target->*seletor)();
    }
}

void GameLayer_LvUp::setAction()
{
    //旋转
    UIImageView* lightImg = dynamic_cast<UIImageView*>(levelUpUl->getWidgetByName("Light"));
    lightImg->runAction(CCRepeatForever::create(CCRotateBy::create(10.0, 360)));
    
    //背后的闪光.
    CCSprite* blink = CCSprite::create("./CocoStudioResources/LevelUp/Light.png");
    blink->runAction(CCRepeatForever::create(CCSequence::create(CCFadeTo::create(0.5, 100),CCFadeTo::create(0.5, 255),NULL)));
    
    //加入星星
    for (int i=0; i<5; i++) {
        CCSprite* starSprite = CCSprite::create("./CocoStudioResources/ItemStrengthern/EffectStar.png");
        CCSequence *seque = CCSequence::create(CCFadeTo::create(0.2, 150),CCFadeTo::create(0.3, 255),NULL);
        CCActionInterval* ccScale = CCSequence::create(CCScaleTo::create(0.2, 0.5), CCScaleTo::create(0.3, 1.0), NULL);
        CCActionInterval *spawn = CCSpawn::create(seque, ccScale, NULL);
        
        starSprite->runAction(CCRepeatForever::create(spawn));
        levelUpUl->addChild(starSprite, 10);
        switch (i) {
            case 0:
                starSprite->setPosition(ccp(100, lightImg->getPosition().y+200));
                break;
            case 1:
                starSprite->setPosition(ccp(180, lightImg->getPosition().y-220));
                break;
            case 2:
                starSprite->setPosition(ccp(550, lightImg->getPosition().y-200));
                break;
            case 3:
                starSprite->setPosition(ccp(500, lightImg->getPosition().y+180));
                break;
            case 4:
                starSprite->setPosition(ccp(-70, -50));
                break;
                
            default:
                break;
        }      
    }

}
void GameLayer_LvUp::setLv(int lv1)
{
    UIImageView* levelUpPanel = dynamic_cast<UIImageView*>(levelUpUl->getWidgetByName("LevelUp"));
    //等级.
    lvPic = this->setLevel(lv1);
    lvPic->setPosition(ccp(levelUpPanel->getPosition().x - 35, levelUpPanel->getPosition().y));
    levelUpPanel -> removeFromParent();
    addChild(lvPic, 10);
}

CCSprite* GameLayer_LvUp::setLevel(int level)
{
    int temp = level;
    //位数,用于设置横坐标偏移量.
    int digit = 0;
    CCSprite* levelSprite = CCSprite::create();
    float offSetX = 60.0;
    
    while (temp>0 || (digit==0 && temp==0)) {
        int remainder = temp % 10;
        temp = temp/10;
        CCSprite *m_Sprite;
        CCRect rc;
        CCString str;
        str.initWithFormat("./CocoStudioResources/lvupLayer/images/lv_%d.png",remainder);
        m_Sprite = CCSprite::create(str.getCString());
        m_Sprite->setPosition(ccp((digit+(digit/3))*(-offSetX), 0));
        levelSprite->addChild(m_Sprite);
        digit++;
    }
    CCSprite* lvSprite = CCSprite::create("./CocoStudioResources/lvupLayer/images/lv_lv.png");
    lvSprite->setPosition(ccp((digit+(digit/3))*(-offSetX)-30, 0));
    levelSprite->addChild(lvSprite);
    digit--;
    
    //    scroeSprite->setContentSize(CCSize(30.0*digit, 20));
    CCArray* array = levelSprite->getChildren();
    for (int i=0; i<array->count(); i++) {
        CCPoint point = ((CCSprite*)array->objectAtIndex(i))->getPosition();
        point.x += (digit)*offSetX/2.0;
        ((CCSprite*)array->objectAtIndex(i))->setPosition(point);
    }
    return levelSprite;
}
CCSprite*  GameLayer_LvUp::getAddGoldByScore(long score)
{
    long temp = score;
    //位数,用于设置横坐标偏移量.
    int digit = 0;
    CCSprite* scroeSprite = CCSprite::create();
    
    
    while (temp>0 || (digit==0 && temp==0)) {
        int remainder = temp % 10;
        temp = temp/10;
        CCSprite *m_Sprite;
        CCRect rc;
        switch(remainder)
        {
            case 0:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/FriendListTimeNumZero.png");
                break;
            }
            case 1:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/FriendListTimeNumOne.png");
                break;
            }
            case 2:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/FriendListTimeNumTwo.png");
                break;
            }
            case 3:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/FriendListTimeNumThree.png");
                break;
            }
            case 4:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/FriendListTimeNumFour.png");
                break;
            }
            case 5:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/FriendListTimeNumFive.png");
                break;
            }
            case 6:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/FriendListTimeNumSix.png");
                break;
            }
            case 7:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/FriendListTimeNumSeven.png");
                break;
            }
            case 8:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/FriendListTimeNumEight.png");
                break;
            }
            case 9:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/FriendListTimeNumNine.png");
                
                break;
            }
            default:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/FriendListTimeNumZero.png");
                break;
            }
        }
        
        m_Sprite->setPosition(ccp((digit)*(-15), 0));
        scroeSprite->addChild(m_Sprite);
        
        digit++;
    }
    CCSprite *m_Sprite = CCSprite::create("./CocoStudioResources/FriendListTimeNumAdd.png");
    m_Sprite->setPosition(ccp((digit)*(-15)-10, 0));
    scroeSprite->addChild(m_Sprite);
    
    
    return scroeSprite;
}

CCSprite*  GameLayer_LvUp::getAddExperienceScore(float percent)
{
    int temp = percent*10;
    //位数,用于设置横坐标偏移量.
    int digit = 0;
    CCSprite* scroeSprite = CCSprite::create();
    
	CCSprite *m_pSprite = CCSprite::create("./CocoStudioResources/FriendListTimeNumAdd.png");
	m_pSprite->setPosition(ccp((digit+3)*(-15)-10, 0));
	scroeSprite->addChild(m_pSprite);

    CCSprite *m_Sprite = CCSprite::create("./CocoStudioResources/FriendListTimePercent.png");
    m_Sprite->setPosition(ccp((digit+2)*(15), 0));
    scroeSprite->addChild(m_Sprite);
    digit++;
    while (temp>0 || (digit==0 && temp==0)) {
		int remainder;
		if(percent >=1)
		{
			remainder = temp % 10;
			temp = temp/10;
		}
		else{
			remainder = percent*10;
			temp = temp/10;
		}

        CCSprite *m_Sprite;
        CCRect rc;
        switch(remainder)
        {
            case 0:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/FriendListTimeNumZero.png");
                break;
            }
            case 1:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/FriendListTimeNumOne.png");
                break;
            }
            case 2:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/FriendListTimeNumTwo.png");
                break;
            }
            case 3:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/FriendListTimeNumThree.png");
                break;
            }
            case 4:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/FriendListTimeNumFour.png");
                break;
            }
            case 5:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/FriendListTimeNumFive.png");
                break;
            }
            case 6:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/FriendListTimeNumSix.png");
                break;
            }
            case 7:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/FriendListTimeNumSeven.png");
                break;
            }
            case 8:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/FriendListTimeNumEight.png");
                break;
            }
            case 9:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/FriendListTimeNumNine.png");
                
                break;
            }
            default:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/FriendListTimeNumZero.png");
                break;
            }
        }

		if(percent<1&&digit==1)
		{
			m_Sprite->setPosition(ccp(0, 0));
			scroeSprite->addChild(m_Sprite);
		}
		else {
			m_Sprite->setPosition(ccp((digit-1)*(-15), 0));
			scroeSprite->addChild(m_Sprite);
		}
        
        digit++;

		if(digit==2&&(temp%10!=0)){
				CCSprite *pSprite = CCSprite::create("./CocoStudioResources/FriendListTimeNumdot.png");
				pSprite->setPosition(ccp((digit-1)*(-15),-8));
				pSprite->setScale(0.5);
				scroeSprite->addChild(pSprite);
				digit++;
		}
		else if(digit==2&&percent<1)
		{
			CCSprite *pSprite = CCSprite::create("./CocoStudioResources/FriendListTimeNumZero.png");
			pSprite->setPosition(ccp((digit)*(-15), 0));
			scroeSprite->addChild(pSprite);

			CCSprite *Sprite = CCSprite::create("./CocoStudioResources/FriendListTimeNumdot.png");
			Sprite->setPosition(ccp((digit-1)*(-15), -8));
			Sprite->setScale(0.5);
			scroeSprite->addChild(Sprite);
		}
    }   
    return scroeSprite;
}