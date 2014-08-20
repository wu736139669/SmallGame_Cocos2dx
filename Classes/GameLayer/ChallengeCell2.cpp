//
//  ChallengeCell2.cpp
//  OnceAgain
//
//  Created by mac on 14-4-28.
//
//

#include "ChallengeCell2.h"
#include "StringUtil.h"
#include "ImageDownloader.h"
#include "NumSprite.h"
#include "TimeUtil.h"
#include "CsvStringData.h"
#include "StringUtil.h"
ChallengeCell2::ChallengeCell2()
{
    cellLyaer = NULL;
    
}

ChallengeCell2::~ChallengeCell2()
{
    GUIReader::shareReader()->purgeGUIReader();
	DictionaryHelper::shareHelper()->purgeDictionaryHelper();
	ActionManager::shareManager()->purgeActionManager();
}

bool ChallengeCell2::init()
{
    cellLyaer = UILayer::create();
    auto myLayout = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile(CStringUtil::convertToUIResPath("ChallengeCell2.json").c_str()));
    cellLyaer->addWidget(myLayout);
    this->addChild(cellLyaer, 0, 100);
    UIImageView* cell = dynamic_cast<UIImageView*>(cellLyaer->getWidgetByName("Cell"));
    this->setContentSize(cell->getSize());
    
    return true;
}
void ChallengeCell2::setAvatarImg(const char *imgUrl)
{
    UIImageView* cellBg = dynamic_cast<UIImageView*>(cellLyaer->getWidgetByName("AvatarBg"));
    CCSprite* img =  CCSprite::create();
    img->setContentSize(CCSize(75, 75));
    img->setAnchorPoint(ccp(0, 0));
    cellBg->addRenderer(img, 10);
    CImageDownloader::GetInstance()->SendHttpRequest(imgUrl, img, "1000", 1000);
}
void ChallengeCell2::setName(const char *name)
{
    UILabel* nameLabel = dynamic_cast<UILabel*>(cellLyaer->getWidgetByName("Name"));
    nameLabel->setText(name);
}
void ChallengeCell2::setScore(int score)
{
    CCSprite* scoreSprite = NumSprite::getNumSprite(score, "./CocoStudioResources/ResouceNum", 17.0);
    scoreSprite->setPosition(ccp(80, 30));
    scoreSprite->setScale(0.8);
    cellLyaer->addChild(scoreSprite);
}
void ChallengeCell2::setTime(long time)
{
    DateTime lastTime = CTimeUtil::FromTimeStamp(time);
    DateTime nowTime = CTimeUtil::GetSystemDateTime().dateTime;
    
    TimeSpan leftTime = CTimeUtil::CalcTimeSpan(nowTime, lastTime);
    
    UILabel* label = dynamic_cast<UILabel*>(cellLyaer->getWidgetByName("Time"));
    CCString str;
    str.initWithFormat(GET_STRING_CSV(1030000001),leftTime.day,leftTime.hour,leftTime.minute);
    label->setText(str.getCString());
}