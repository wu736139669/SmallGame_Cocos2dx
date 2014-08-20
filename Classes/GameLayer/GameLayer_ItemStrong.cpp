//
//  GameLayer_ItemStrong.cpp
//  OnceAgain
//
//  Created by mac on 14-3-25.
//
//

#include "GameLayer_ItemStrong.h"
#include "GameLayer_Tag.h"
GameLayer_ItemStrong::~GameLayer_ItemStrong()
{
    GUIReader::shareReader()->purgeGUIReader();
    DictionaryHelper::shareHelper()->purgeDictionaryHelper();
    ActionManager::shareManager()->purgeActionManager();
}

GameLayer_ItemStrong::GameLayer_ItemStrong()
{
    itemStrong = NULL;
    m_pListener = NULL;
    m_pfnSelector = NULL;
}
bool GameLayer_ItemStrong::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    //系统设置界面.
    itemStrong = UILayer::create();
    auto layout = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("./CocoStudioResources/ItemStrengthen.json"));
    itemStrong->addWidget(layout);
    //    sysSet->setVisible(true);
    this->addChild(itemStrong, 0, 101);
    
    //设置背景颜色.
    UIPanel* taskPanel = dynamic_cast<UIPanel*>(itemStrong->getWidgetByName("ItemStrengthen"));
    taskPanel->setBackGroundColor(ccBLACK);
    taskPanel->setBackGroundColorOpacity(150);
    //关闭按钮
    UIButton* cancelBtn = dynamic_cast<UIButton*>(itemStrong->getWidgetByName("CloseBtn"));
    cancelBtn->addReleaseEvent(this, coco_releaseselector(GameLayer_ItemStrong::closeBtnCallback));
    cancelBtn->setPressedActionEnabled(true);
 
    
    this->addStarSprite();
    this->setVisible(true);
    return true;
}

void GameLayer_ItemStrong::addStarSprite()
{
    UIImageView* itemBg = dynamic_cast<UIImageView*>(itemStrong->getWidgetByName("ItemBg"));
    for (int i=0; i<5; i++) {
        CCSprite* starSprite = CCSprite::create("./CocoStudioResources/ItemStrengthern/EffectStar.png");
        CCSequence *seque = CCSequence::create(CCFadeTo::create(0.2, 150),CCFadeTo::create(0.3, 255),NULL);
        CCActionInterval* ccScale = CCSequence::create(CCScaleTo::create(0.2, 0.3), CCScaleTo::create(0.3, 0.8), NULL);
        CCActionInterval *spawn = CCSpawn::create(seque, ccScale, NULL);

        starSprite->runAction(CCRepeatForever::create(spawn));
        itemBg->addRenderer(starSprite, 10+i);
        switch (i) {
            case 0:
                starSprite->setPosition(ccp(-50, 50));
                break;
            case 1:
                starSprite->setPosition(ccp(0, 50));
                break;
            case 2:
                starSprite->setPosition(ccp(60, 50));
                break;
            case 3:
                starSprite->setPosition(ccp(-50, -40));
                break;
            case 4:
                starSprite->setPosition(ccp(0, -50));
                break;
                
            default:
                break;
        }
        
        
    }
//    CCSprite* starSprite = CCSprite::createWithSpriteFrameName("ItemStrengthern/EffectStar.png");
//    starSprite->runAction(CCRepeatForever::create(ccScale));
//    itemBg->addRenderer(starSprite, 10);
    
    
}
void GameLayer_ItemStrong::setVisible(bool visible)
{
    CCLayer::setVisible(visible);
    UIPanel* itemPanel = dynamic_cast<UIPanel*>(itemStrong->getWidgetByName("ItemStrengthen"));
    itemPanel->setTouchEnable(visible);
}
void GameLayer_ItemStrong::successLvUp()
{
    UIImageView* itemBg = dynamic_cast<UIImageView*>(itemStrong->getWidgetByName("ItemBg"));
    CCSprite* bgImg = CCSprite::create("./CocoStudioResources/ItemStrengthern/EffectLight.png");
    CCSprite* labelImg = CCSprite::create("./CocoStudioResources/ItemStrengthern/EffectLabel.png");
	labelImg->setScale(2.0);
    itemBg->addRenderer(labelImg,2);
    CCActionInterval* action1 = CCSequence::create(CCScaleTo::create(0.1, 2.5, 3.5), CCScaleTo::create(0.1, 2.5, 2.5), CCScaleTo::create(0.1, 3.5,2.5), CCScaleTo::create(0.1, 2.5, 2.5), CCDelayTime::create(1.0), CCHide::create(), NULL);
    CCActionInterval* action2 = CCSequence::create(CCScaleTo::create(0.2, 1.0, 1.0), CCScaleTo::create(0.5, 2.0, 2.0),CCScaleTo::create(0.5, 1.0,1.0), CCHide::create(),CCCallFunc::create(this, callfunc_selector(GameLayer_ItemStrong::setBtnCanClick)), NULL);
    itemBg->addRenderer(bgImg, 1);
    labelImg->runAction(action1);
    bgImg->runAction(action2);
}
void GameLayer_ItemStrong::sureBtnCallback(cocos2d::CCObject *pSender)
{
    if (m_pfnSelector && m_pListener) {
        UIButton* sureBtn = dynamic_cast<UIButton*>(itemStrong->getWidgetByName("SureBtn"));
        (m_pListener->*m_pfnSelector)(sureBtn);
        sureBtn->setTouchEnable(false);

		//CCSprite *pSprite = CCSprite::create("./CocoStudioResources/ItemStrengthern/EffectLabel.png");
    }
}

void GameLayer_ItemStrong::setBtnCanClick() {
    UIButton* sureBtn = dynamic_cast<UIButton*>(itemStrong->getWidgetByName("SureBtn"));
    sureBtn->setTouchEnable(true);
}

void GameLayer_ItemStrong::setBtnUnClick()
{
    UIButton* sureBtn = dynamic_cast<UIButton*>(itemStrong->getWidgetByName("SureBtn"));
    ccColor3B color = {128,128,128};
    sureBtn->setTouchEnable(false);
    sureBtn->setColor(color);
}
void GameLayer_ItemStrong::closeBtnCallback(CCObject* pSender)
{
    this->removeFromParent();
}
void GameLayer_ItemStrong::setSureCallbackFunc(cocos2d::CCObject *target, SEL_CallFuncO callfun)
{
    
    UIButton* sureBtn = dynamic_cast<UIButton*>(itemStrong->getWidgetByName("SureBtn"));
    sureBtn->setTouchEnable(true);
    this->m_pListener = target;
    this->m_pfnSelector = callfun;
}
void GameLayer_ItemStrong::setSureBtnTag(int tag)
{
    UIButton* sureBtn = dynamic_cast<UIButton*>(itemStrong->getWidgetByName("SureBtn"));
    sureBtn->setTag(tag);
}
void GameLayer_ItemStrong::setItemInfo(const char *str)
{
    UILabel* label = dynamic_cast<UILabel*>(itemStrong->getWidgetByName("ItemInfo"));			//道具升级性能介绍
    label->setText(str);
}
void GameLayer_ItemStrong::setItemCurrency(int str1)
{
    CCString str;
    str.initWithFormat("%d",str1);
    UILabelAtlas* lvLabel = dynamic_cast<UILabelAtlas*>(itemStrong->getWidgetByName("NeedLabel"));
    lvLabel->setStringValue(str.getCString());
}
void GameLayer_ItemStrong::setItemImg(const char *str)
{
    UIImageView* itemImg = dynamic_cast<UIImageView*>(itemStrong->getWidgetByName("ItemImg"));			//设置道具图标
    CCSize size = itemImg->getContentSize();
    itemImg->setTexture(str);
    itemImg->setSize(size);
}
void GameLayer_ItemStrong::setItemLv(int itemLv)
{
	UIImageView* Max = dynamic_cast<UIImageView*>(itemStrong->getWidgetByName("Image_2"));
	UILabelAtlas* lvLabel = dynamic_cast<UILabelAtlas*>(itemStrong->getWidgetByName("ItemLvLabel")); 

	//确定按钮.
	UIButton* sureBtn = dynamic_cast<UIButton*>(itemStrong->getWidgetByName("SureBtn"));
	sureBtn->addReleaseEvent(this, coco_releaseselector(GameLayer_ItemStrong::sureBtnCallback));
	UIImageView *medal = dynamic_cast<UIImageView*>(itemStrong->getWidgetByName("Image_70"));
	medal->setTouchEnabled(false);
	if(itemLv<30)
	{
		//getItemLv(itemLv);
		CCString str;
		str.initWithFormat("%d",itemLv);
		lvLabel->setStringValue(str.getCString());
		Max->setVisible(false);
		lvLabel->setVisible(true);
		medal->setVisible(false);
		sureBtn->setPressedActionEnabled(true);
		sureBtn->setVisible(true);
	}
	else {
	 	 medal->setVisible(true);
		 Max->setVisible(true);
		 lvLabel->setVisible(false);
		 sureBtn->setPressedActionEnabled(false);
		 sureBtn->setVisible(false);
	}
}
void GameLayer_ItemStrong::setItemName(const char *str)
{
    UIImageView* label = dynamic_cast<UIImageView*>(itemStrong->getWidgetByName("ItemLabel"));		//设置道具名字 ;
    label->setTexture(str);
	CCSize size = label->getContentSize();
	label->setSize(size);
}
CCSprite* GameLayer_ItemStrong::getItemLv(int num)
{
	int temp =num;
    //位数,用于设置横坐标偏移量.
    int digit = 0;
    CCSprite* scroeSprite = CCSprite::create();
    float offSetX = 88.0;
    while (temp>0 || (digit==0 && temp==0)) {
        int remainder = temp % 10;
        temp = temp/10;
        CCSprite *m_Sprite;
        CCRect rc;
        switch(remainder)
        {
            case 0:
            {
                m_Sprite = CCSprite::create("./numberBox/lightBrownZero.png");
                break;
            }
            case 1:
            {
                m_Sprite = CCSprite::create("./numberBox/lightBrownOne.png");
                break;
            }
            case 2:
            {
                m_Sprite = CCSprite::create("./numberBox/lightBrownTwo.png");
                break;
            }
            case 3:
            {
                m_Sprite = CCSprite::create("./numberBox/lightBrownThree.png");
                break;
            }
            case 4:
            {
                m_Sprite = CCSprite::create("./numberBox/lightBrownFour.png");
                break;
            }
            case 5:
            {
                m_Sprite = CCSprite::create("./numberBox/lightBrownFive.png");
                break;
            }
            case 6:
            {
                m_Sprite = CCSprite::create("./numberBox/lightBrownSix.png");
                break;
            }
            case 7:
            {
                m_Sprite = CCSprite::create("./numberBox/lightBrownSeven.png");
                break;
            }
            case 8:
            {
                m_Sprite = CCSprite::create("./numberBox/lightBrownEight.png");
                break;
            }
            case 9:
            {
                m_Sprite = CCSprite::create("./numberBox/lightBrownNine.png");
                
                break;
            }
            default:
            {
                m_Sprite = CCSprite::create("./numberBox/lightBrownZero.png");
                break;
            }
        }
        
        m_Sprite->setPosition(ccp((digit)*(-offSetX), 0));
        scroeSprite->addChild(m_Sprite);
        digit++;
    }
	CCArray* array = scroeSprite->getChildren();
	for (int i=0; i<array->count(); i++) {
		CCPoint point = ((CCSprite*)array->objectAtIndex(i))->getPosition();
		point.x += (digit)*offSetX/2.0;
		((CCSprite*)array->objectAtIndex(i))->setPosition(point);
	}
	return scroeSprite;
}


