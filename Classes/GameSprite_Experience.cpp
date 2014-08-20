//
//  Game_Experience.cpp
//  OnceAgain
//
//  Created by mac on 14-3-4.
//
//

#include "GameSprite_Experience.h"
enum KEY_SPRITE{
    Key_Level = 100,
    Key_PercentLabel,
    Key_PercentSprite,
    Key_LabelBg
};
GameSprite_Experience::~GameSprite_Experience()
{
    
}

bool GameSprite_Experience::init()
{
    if (!CCSprite::init()) {
        return false;
    }
    level = 0;
    percent = 0;
    
    //设置大小.
    this->setContentSize(CCSize(150, 90));
    
    //字体背景.
    CCSprite *labelBgSprite = GameShare_Texture::sharedTexture()->GetSpriteByCCRect(akoomenu_image, CCRect(324, 938, 166, 48));
    labelBgSprite->setAnchorPoint(CCPointZero);
    labelBgSprite->setPosition(ccp(0,0));
    labelBgSprite->setTag(Key_LabelBg);
    this->addChild(labelBgSprite,1);
    
    //星星
    CCSprite *starSprite = GameShare_Texture::sharedTexture()->GetSpriteByCCRect(akoomenu_image, CCRect(1664,640,92,82));
    starSprite->setAnchorPoint(ccp(0.5, 0.5));
    starSprite->setPosition(ccp(140,35));
    this->addChild(starSprite,1);
    
    starSprite->runAction(CCRepeatForever::create(CCSequence::create(CCScaleTo::create(1.0, 0.9),CCScaleTo::create(1.0, 1.0),NULL)));
    
    //等级标签
    CCLabelTTF *levelLabel = CCLabelTTF::create("0", "Arial", 30);
    char strScore[32];
    sprintf(strScore,"%d",level);
    levelLabel->setString(strScore);
    levelLabel->setPosition((ccp(starSprite->getPositionX(), starSprite->getPositionY()-5)));
    levelLabel->setTag(Key_Level);
    this->addChild(levelLabel,1);
    
    //显示百分比sprite
    CCSprite *percentSprite = GameShare_Texture::sharedTexture()->GetSpriteByCCRect(akoomenu_image, CCRect(300, 1314, 0, 38));
    percentSprite->setAnchorPoint(CCPointZero);
    percentSprite->setPosition(ccp(labelBgSprite->getPositionX()+6,labelBgSprite->getPositionY()+6));
    percentSprite->setTag(Key_PercentSprite);
    this->addChild(percentSprite);
    
    //百分比标签
    CCLabelTTF *percentLabel = CCLabelTTF::create("0", "Arial", 25);
    sprintf(strScore,"%d%%",percent);
    percentLabel->setString(strScore);
    percentLabel->setPosition(CCPoint(labelBgSprite->getContentSize().width/2, labelBgSprite->getContentSize().height/2));
    percentLabel->setTag(Key_PercentLabel);
    this->addChild(percentLabel,1);
    

    return true;
}

unsigned int GameSprite_Experience::getLevel()
{
    return level;
}
void GameSprite_Experience::setLevel(unsigned int var)
{
    level = var;
    if (this->getChildByTag(Key_Level)) {
        char strScore[32];
        sprintf(strScore,"%d",level);
        ((CCLabelTTF*)this->getChildByTag(Key_Level))->setString(strScore);
    }
    

}

unsigned int GameSprite_Experience::getPercent()
{
    return percent;
}
void GameSprite_Experience::setPercent(unsigned int var)
{
    percent = var;
    if (this->getChildByTag(Key_PercentLabel) && this->getChildByTag(Key_PercentSprite)) {
        CCSprite *percentSprite = (CCSprite*)this->getChildByTag(Key_PercentSprite);
        CCRect rect = percentSprite->getTextureRect();
        rect.size.width = ((float)percent/100.0)*116;
        percentSprite->setTextureRect(rect);
        char strScore[32];
        sprintf(strScore,"%d%%",percent);
        ((CCLabelTTF*)this->getChildByTag(Key_PercentLabel))->setString(strScore);
    }
    
}