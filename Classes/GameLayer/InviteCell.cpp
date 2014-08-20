//
//  InviteCell.cpp
//  OnceAgain
//
//  Created by mac on 14-5-6.
//
//

#include "InviteCell.h"
#include "StringUtil.h"
#include "ImageDownloader.h"
#include "GameShare_Global.h"
#include "GameLayer_Alert.h"
#include "CsvStringData.h"
#include "NetHttpClient.h"
#include "MsgDefine.h"
#include "PlayerInfoManager.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include "QQInterface.h"
#include "SinaInterface.h"
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#endif

InviteCell::InviteCell()
{
    m_pListener = NULL;
    mbLoadImg = false;
}
InviteCell::~InviteCell()
{
    GUIReader::shareReader()->purgeGUIReader();
	DictionaryHelper::shareHelper()->purgeDictionaryHelper();
	ActionManager::shareManager()->purgeActionManager();
}

bool InviteCell::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    cellLyaer = UILayer::create();
    auto myLayout = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile(CStringUtil::convertToUIResPath("InviteFriendCell.json").c_str()));
    cellLyaer->addWidget(myLayout);
    this->addChild(cellLyaer, 0, 100);
    UIButton* cell = dynamic_cast<UIButton*>(cellLyaer->getWidgetByName("BgBtn"));
    this->setContentSize(cell->getSize());
    
    UIPanel* addBtn = dynamic_cast<UIPanel*>(cellLyaer->getWidgetByName("AddBtn"));
    addBtn->setTouchEnable(true);
    addBtn->addReleaseEvent(this, coco_releaseselector(InviteCell::sendInvite));
    return true;
}

void InviteCell::setInfo(sGameRank info1) {
    info = info1;
    UILabel* nameLabel = dynamic_cast<UILabel*>(cellLyaer->getWidgetByName("NameLabel"));
    nameLabel -> setText(info.name.c_str());
    UIButton* cellBg = dynamic_cast<UIButton*>(cellLyaer->getWidgetByName("BgBtn"));
    img =  CCSprite::create();
    img->setContentSize(CCSize(95, 95));
    img->setAnchorPoint(ccp(0, 0));
    img->setPosition(ccp(65, 90));
    cellBg->addRenderer(img, 0);
    

    if (info1.powernoticeexpiretime > 0) {
        setPicToBeHide(NULL);
    }
}
void InviteCell::requestIcon()
{
    CImageDownloader::GetInstance()->SendHttpRequest(info.avatarUrl.c_str(), img, "1000", 1000);
   // CCLog("11111111111_img:%s",info.name.c_str());
}
void InviteCell::sendInvite(cocos2d::CCObject *pSender)
{
    CCString str;
    str.initWithFormat(GET_STRING_CSV(1020000002),info.name.c_str());
    GameLayer_Alert* alert = GameLayer_Alert::creatWithOnlySure();
    alert->setSize(22);
    alert->setSureCallbackFunc(this, callfuncO_selector(InviteCell::sendInviteForThisFriend));
    alert->setText(str.getCString());
    
    if (m_pListener) {
        m_pListener->addChild(alert);
    }
}
void InviteCell::sendInviteForThisFriend(cocos2d::CCObject *p) {
    CSJson::Value msg_body;
    msg_body["playerid"] = CSJson::Value(CPlayerInfoMan::sharedInstance().getPlayerInfo().nId);
    msg_body["appid"] = CSJson::Value(info.appid);
    msg_body["apptype"] = CSJson::Value(info.appType);
    NetHttpClient::sharedInstance().XQsendHttpRequest(eNetMsgTypeFriendSys, eNetMsgFriendSysSendInvite, &msg_body, this, coco_myevent(InviteCell::sureSend));
}

void InviteCell::sureSend(cocos2d::CCObject *pSender)
{
    GameLayer_Alert* alert = GameLayer_Alert::creatWithOnlySure(Type_OnlySure);
    alert->setText(GET_STRING_CSV(1020000003));
    alert -> setSureCallbackFunc(this, callfuncO_selector(InviteCell::setPicToBeHide));
    if (m_pListener) {
        m_pListener->addChild(alert);
    }
}
void InviteCell::setPicToBeHide(cocos2d::CCObject *p) {
    UIPanel* addBtn = dynamic_cast<UIPanel*>(cellLyaer->getWidgetByName("AddBtn"));
    UIImageView *pic  = dynamic_cast<UIImageView*>(cellLyaer -> getWidgetByName("AddImg"));
    pic -> setVisible(false);
    addBtn -> setTouchEnable(false);
    addBtn -> setVisible(false);
    
    CCSprite *pic_1 = graylightWithCCSprite(img, false);
    pic_1 -> setAnchorPoint(ccp(0, 0));
    pic_1 -> setPosition(ccp(0, 0));
    img -> removeFromParentAndCleanup(true);
   
    UIButton* cellBg = dynamic_cast<UIButton*>(cellLyaer->getWidgetByName("BgBtn"));
    cellBg -> setColor(ccc3(166, 166, 166));
    cellBg->addRenderer(pic_1, 0);
}

void InviteCell::setNode(cocos2d::CCNode *node)
{
    this->m_pListener = node;
}

void InviteCell::onEnter()
{
    CCLayer::onEnter();

}

CCSprite* InviteCell::graylightWithCCSprite(CCSprite* oldSprite,bool isLight)
{
    //CCSprite转成CCimage
    CCPoint p = oldSprite->getAnchorPoint();
    oldSprite->setAnchorPoint(ccp(0,0));
    CCRenderTexture *outTexture = CCRenderTexture::create((int)oldSprite->getContentSize().width*2,(int)oldSprite->getContentSize().height*2);
    outTexture->begin();
    oldSprite->visit();
    outTexture->end();
    oldSprite->setAnchorPoint(p);
    
    CCImage* finalImage = outTexture->newCCImage();
    unsigned char *pData = finalImage->getData();
    int iIndex = 0;
    
    if(isLight)
    {
        for (int i = 0; i < finalImage->getHeight(); i ++)
        {
            for (int j = 0; j < finalImage->getWidth(); j ++)
            {
                // highlight
                int iHightlightPlus = 50;
                int iBPos = iIndex;
                unsigned int iB = pData[iIndex];
                iIndex ++;
                unsigned int iG = pData[iIndex];
                iIndex ++;
                unsigned int iR = pData[iIndex];
                iIndex ++;
                //unsigned int o = pData[iIndex];
                iIndex ++;  //原来的示例缺少
                iB = (iB + iHightlightPlus > 255 ? 255 : iB + iHightlightPlus);
                iG = (iG + iHightlightPlus > 255 ? 255 : iG + iHightlightPlus);
                iR = (iR + iHightlightPlus > 255 ? 255 : iR + iHightlightPlus);
                //            iR = (iR < 0 ? 0 : iR);
                //            iG = (iG < 0 ? 0 : iG);
                //            iB = (iB < 0 ? 0 : iB);
                pData[iBPos] = (unsigned char)iB;
                pData[iBPos + 1] = (unsigned char)iG;
                pData[iBPos + 2] = (unsigned char)iR;
            }
        }
    }else{
        for (int i = 0; i < finalImage->getHeight(); i ++)
        {
            for (int j = 0; j < finalImage->getWidth(); j ++)
            {
                // gray
                int iBPos = iIndex;
                unsigned int iB = pData[iIndex];
                iIndex ++;
                unsigned int iG = pData[iIndex];
                iIndex ++;
                unsigned int iR = pData[iIndex];
                iIndex ++;
                //unsigned int o = pData[iIndex];
                iIndex ++; //原来的示例缺少
                unsigned int iGray = 0.3 * iR + 0.4 * iG + 0.2 * iB;
                pData[iBPos] = pData[iBPos + 1] = pData[iBPos + 2] = (unsigned char)iGray;
            }
        }
    }
    
    CCTexture2D *texture = new CCTexture2D;
    texture->initWithImage(finalImage);
    CCSprite* newSprite = CCSprite::createWithTexture(texture);
    delete finalImage;
    texture->release();
    return newSprite;
}
