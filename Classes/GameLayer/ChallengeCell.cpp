//
//  ChallengeCell.cpp
//  OnceAgain
//
//  Created by mac on 14-4-28.
//
//

#include "ChallengeCell.h"
#include "StringUtil.h"
#include "ImageDownloader.h"
#include "TimeUtil.h"
#include "CsvStringData.h"
ChallengeCell::ChallengeCell()
{
    
}

ChallengeCell::~ChallengeCell()
{
    GUIReader::shareReader()->purgeGUIReader();
	DictionaryHelper::shareHelper()->purgeDictionaryHelper();
	ActionManager::shareManager()->purgeActionManager();
}

bool ChallengeCell::init()
{
    cellLyaer = UILayer::create();
    auto myLayout = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile(CStringUtil::convertToUIResPath("ChallengeCell1.json").c_str()));
    cellLyaer->addWidget(myLayout);
    this->addChild(cellLyaer, 0, 100);
    UIImageView* cell = dynamic_cast<UIImageView*>(cellLyaer->getWidgetByName("Cell"));
    this->setContentSize(cell->getSize());
    
    return true;
}
void ChallengeCell::setName(const char *name)
{
    UILabel* nameLabel = dynamic_cast<UILabel*>(cellLyaer->getWidgetByName("NameLabel"));
    nameLabel->setText(name);
}

void ChallengeCell::setAvatarImg(const char *imgUrl)
{
    UIImageView* cellBg = dynamic_cast<UIImageView*>(cellLyaer->getWidgetByName("AvatarBg"));
    CCSprite* img =  CCSprite::create();
    img->setContentSize(CCSize(75, 75));
    img->setAnchorPoint(ccp(0, 0));
    cellBg->addRenderer(img, 10);
    CImageDownloader::GetInstance()->SendHttpRequest(imgUrl, img, "1000", 1000);
}
void ChallengeCell::setTime(long time)
{
    DateTime lastTime = CTimeUtil::FromTimeStamp(time);
    DateTime nowTime = CTimeUtil::GetSystemDateTime().dateTime;
    
    TimeSpan leftTime = CTimeUtil::CalcTimeSpan(nowTime, lastTime);
    
    UILabel* label = dynamic_cast<UILabel*>(cellLyaer->getWidgetByName("Time"));
    CCString str;
    str.initWithFormat(GET_STRING_CSV(1030000001),leftTime.day,leftTime.hour,leftTime.minute);
    label->setText(str.getCString());
}
void ChallengeCell::addSendCallbackFunc(cocos2d::CCObject *target, SEL_ReleaseEvent callfun)
{
    UIImageView* cell = dynamic_cast<UIImageView*>(cellLyaer->getWidgetByName("Cell"));
    cell->setTouchEnable(true);
    cell->setTag(this->getTag());
    cell->addReleaseEvent(target, callfun);
}