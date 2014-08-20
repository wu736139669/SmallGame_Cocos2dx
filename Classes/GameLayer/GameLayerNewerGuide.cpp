

#include "SpriteFrameManage.h"
#include "GameLayerNewerGuide.h"
#include "RTItem.h"
#include "GameShare_Global.h"
#include "GameShare_Scene.h"
#include "NewerGuideRightTouch.h"
#include "GameLinkerGuideLayer.h"
#include "GameMemoryGuideLayer.h"
#include "NewerGuideFruit.h"
#include "NewerGuideTaiko.h"

CGameLayerNewerGuide* CGameLayerNewerGuide::m_pInstance = NULL;

CGameLayerNewerGuide::CGameLayerNewerGuide():m_pListener(NULL),m_pfnSelector(NULL),mType(eNewerGuideMax)
{

}
CGameLayerNewerGuide::~CGameLayerNewerGuide()
{

}

bool CGameLayerNewerGuide::init()
{
	 if(!UILayer::init())
		return false;
	 auto ly = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("./CocoStudioResources/layoutNewerGuide/layoutNewerGuide_1.json"));
	 this->addWidget(ly);

	 //…Ë÷√±≥æ∞—’…�?
	 UIPanel* taskPanel = dynamic_cast<UIPanel*>(getWidgetByName("Panel_20"));
	 taskPanel->setBackGroundColor(ccBLACK);
	 taskPanel->setBackGroundColorOpacity(150);
	 setTouchPriority(kCCMenuHandlerPriority - 1);
	 return true;
}
 void CGameLayerNewerGuide::onEnter()
 {
	 UILayer::onEnter();
	 play(GameShare_Global::shareGlobal()->gameType);
 }
 void CGameLayerNewerGuide::onExit()
 {
	 UILayer::onExit();
 }
 void CGameLayerNewerGuide::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
 {
	 OnBtnClose(NULL);
 }
 void CGameLayerNewerGuide::play(e_GameType eType )
 {
	UIPanel* pBg = dynamic_cast<UIPanel*>(this->getWidgetByName("Panel_20"));

	UIImageView* info_click1 = dynamic_cast<UIImageView*>(this->getWidgetByName("info_click1"));
	info_click1->setZOrder(13);
	UIImageView* info1 = dynamic_cast<UIImageView*>(this->getWidgetByName("info1"));
	info1->setZOrder(13);
	UIImageView* info_click = dynamic_cast<UIImageView*>(this->getWidgetByName("info_click"));
	UIImageView* info = dynamic_cast<UIImageView*>(this->getWidgetByName("info"));
	this->getWidgetByName("info_click1")->setVisible(false);
	this->getWidgetByName("info1")->setVisible(false);
	this->getWidgetByName("info_click")->setVisible(true);
	this->getWidgetByName("info")->setVisible(true);

	 switch(eType)
	 {
	 case Game_TaiKo:
		 {
			 this->getWidgetByName("info_click1")->setVisible(true);
			 this->getWidgetByName("info1")->setVisible(true);
			 this->getWidgetByName("info_click")->setVisible(false);
			 this->getWidgetByName("info")->setVisible(false);
			 info->setTexture("CocoStudioResources/layoutNewerGuide/taiko_info.png");
			 pBg->getParent()->addRenderer(CNewerGuideTaiko::create(),1);
		 }
		 break;
	 case Game_Fruit:
		 {
			 info->setTexture("CocoStudioResources/layoutNewerGuide/friut_info.png");
			pBg->getParent()->addRenderer(CNewerGuideFruit::create(),1);
		 }
		 break;
	 case Game_Memory:
		 {
             info_click -> removeFromParent();
             info -> removeFromParent();
             auto *layer = GameMemoryGuideLayer::create();
             layer -> setAnchorPoint(ccp(0,0));
             this -> addChild(layer);
//			 info->setTexture("CocoStudioResources/layoutNewerGuide/memory_info.png");
		 }
		 break;
	 case Game_Link:
		 {
             info_click -> removeFromParent();
             info -> removeFromParent();
             auto *layer = GameLinkerGuideLayer::create();
             layer -> setAnchorPoint(ccp(0,0));
             this -> addChild(layer);
//			 info->setTexture("CocoStudioResources/layoutNewerGuide/link_info.png");
		 }
		 break;
	 case Game_Jelly:
		 {
			 info->setTexture("CocoStudioResources/layoutNewerGuide/rihgt_touch_info.png");
			 pBg->getParent()->addRenderer(CNewerGuideRihgtTouch::create(),1);
          }
        break;
	 }
 }
 void CGameLayerNewerGuide::OnBtnClose(CCObject* p)
 {
	((GameShare_Scene*)getParent())->clickLayerClose();
	 removeFromParent();
 }
 void CGameLayerNewerGuide::setCallfunc(CCObject *target, SEL_CallFuncO callfun)
 {
	 this->m_pListener = target;
	 this->m_pfnSelector = callfun;
 }