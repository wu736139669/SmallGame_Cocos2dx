//
//  SysInfoCell.cpp
//  OnceAgain
//
//  Created by mac on 14-4-24.
//
//

#include "SysInfoCell.h"
#include "StringUtil.h"
#include "NumSprite.h"
#include "ImageDownloader.h"
SysInfoCell::SysInfoCell()
{
    scoreSprite = NULL;
    cellLyaer = NULL;
}
SysInfoCell::~SysInfoCell()
{
    GUIReader::shareReader()->purgeGUIReader();
	DictionaryHelper::shareHelper()->purgeDictionaryHelper();
	ActionManager::shareManager()->purgeActionManager();
}
bool SysInfoCell::init()
{
    cellLyaer = UILayer::create();
    auto myLayout = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile(CStringUtil::convertToUIResPath("SysInfoCell.json").c_str()));
    cellLyaer->addWidget(myLayout);
    this->addChild(cellLyaer, 0, 100);
    UIImageView* cell = dynamic_cast<UIImageView*>(cellLyaer->getWidgetByName("Cell"));
    this->setContentSize(cell->getSize());
    
    return true;
}

void SysInfoCell::setType(InfoType type)
{
    UIButton* btn = dynamic_cast<UIButton*>(cellLyaer->getWidgetByName("Sure"));
    if (type == InfoTypeSendRice) {
        btn->setPressedActionEnabled(true);
        btn->setTextures("./CocoStudioResources/SysInfo/GainBtn.png", "./CocoStudioResources/SysInfo/GainBtn.png", "");
    }
    if (type == InfoTypeChallenge) {
        btn->setPressedActionEnabled(true);
        btn->setTextures("./CocoStudioResources/SysInfo/SeeBtn.png", "./CocoStudioResources/SysInfo/SeeBtn.png", "");
    }
}
void SysInfoCell::setInfo(const char *info, int size)
{
    UILabel* infoLabel = dynamic_cast<UILabel*>(cellLyaer->getWidgetByName("InfoLabel"));
    infoLabel->setFontSize(size);
    infoLabel->setText(info);
}
void SysInfoCell::setName(const char *name)
{
    UILabel* nameLabel = dynamic_cast<UILabel*>(cellLyaer->getWidgetByName("Name"));
    nameLabel->setText(name);
}
void SysInfoCell::setAvatar(const char *imgUrl)
{
    UIImageView* cellBg = dynamic_cast<UIImageView*>(cellLyaer->getWidgetByName("AvatarBg"));
    CCSprite* img =  CCSprite::create();
    img->setAnchorPoint(ccp(0, 0));
    img->setPosition(ccp(cellBg->getContentSize().width/2, cellBg->getContentSize().height/2));
    img->setContentSize(CCSize(70, 70));
    cellBg->addRenderer(img, 10);
    CImageDownloader::GetInstance()->SendHttpRequest(imgUrl, img, "1000", 1000);
}
void SysInfoCell::addSendCallbackFunc(cocos2d::CCObject *target, SEL_ReleaseEvent callfun){
    UIButton* btn = dynamic_cast<UIButton*>(cellLyaer->getWidgetByName("Sure"));
    btn->addReleaseEvent(target, callfun);
    btn->setTag(this->getTag());
    btn->setPressedActionEnabled(true);
}