

#include "SpriteFrameManage.h"
#include "GameLayerTaiKo.h"
#include "TaikoScene.h"
#include "GameLayer_Tag.h"

IMPLEMENT_DLG_ID(CGameLayerTaiko,GameLayerTaiko_Tag);
 CGameLayerTaiko::CGameLayerTaiko()
 {

 }
 CGameLayerTaiko::~CGameLayerTaiko()
 {

 }

 bool CGameLayerTaiko::init(){
	 if(!UILayer::init())
		return false;
	 auto ly = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("./CocoStudioResources/tai_ko_1.json"));
	 this->addWidget(ly);
	 setTouchEnabled(true);
	UIButton* pBtn0 = dynamic_cast<UIButton*>(getWidgetByName("Btn0"));
	pBtn0->addReleaseEvent(this, coco_releaseselector(CGameLayerTaiko::OnBtn0));
	pBtn0->addPushDownEvent(this, coco_releaseselector(CGameLayerTaiko::OnBtnPushDown0));
	pBtn0->addCancelEvent(this, coco_releaseselector(CGameLayerTaiko::OnBtnCancel0));
	pBtn0->setPressedActionEnabled(true);
	pBtn0->setTouchEnabled(true);
	UIButton* pBtn1 = dynamic_cast<UIButton*>(getWidgetByName("Btn1"));
	pBtn1->addReleaseEvent(this, coco_releaseselector(CGameLayerTaiko::OnBtn1));
	pBtn1->addPushDownEvent(this, coco_releaseselector(CGameLayerTaiko::OnBtnPushDown1));
	pBtn1->addCancelEvent(this, coco_releaseselector(CGameLayerTaiko::OnBtnCancel1));
	pBtn1->setPressedActionEnabled(true);
	pBtn1->setTouchEnabled(true);
	UIButton* pBtnIn = dynamic_cast<UIButton*>(getWidgetByName("BtnIn"));
	pBtnIn->addPushDownEvent(this, coco_releaseselector(CGameLayerTaiko::OnBtnBrum));
	pBtnIn->setPressedActionEnabled(true);
	pBtnIn->setTouchEnabled(true);
	 return true;
 }
 void CGameLayerTaiko::onEnter()
{
	UILayer::onEnter();
	//CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(this, 0, false);
}
 void CGameLayerTaiko::onExit()
{
	UILayer::onExit();
	//CCDirector::sharedDirector()->getScheduler()->unscheduleUpdateForTarget(this);
}
 void CGameLayerTaiko::updata(float fDelta)
 {

 }

 //单击事件开始
//  bool CGameLayerTaiko::ccTouchBegan(cocos2d::CCTouch * pTouch, cocos2d::CCEvent *pEvent)
//  {
// 	 return false;
//  }
//  //单击事件拖动
//  void CGameLayerTaiko::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
//  {
// 
//  }
// 
//  //单击事件结束
//  void CGameLayerTaiko::ccTouchEnded(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent)
//  {
// 
//  }
 void CGameLayerTaiko::OnBtn0(CCObject* pSender)
 {
	 ((CTaikoScene*)getParent())->clickBtn0();
 }
 void CGameLayerTaiko::OnBtnPushDown0(CCObject* pSender)
 {
	  ((CTaikoScene*)getParent())->clickBtnPushDown0();
 }
 void CGameLayerTaiko::OnBtnCancel0(CCObject* pSender)
 {
	  ((CTaikoScene*)getParent())->clickBtnCancel0();
 }
 void CGameLayerTaiko::OnBtn1(CCObject* pSender)
 {
	 ((CTaikoScene*)getParent())->clickBtn1();
 }
 void CGameLayerTaiko::OnBtnPushDown1(CCObject* pSender)
 {
	 ((CTaikoScene*)getParent())->clickBtnPushDown1();
 }
 void CGameLayerTaiko::OnBtnCancel1(CCObject* pSender)
 {
	 ((CTaikoScene*)getParent())->clickBtnCancel1();
 }
 void CGameLayerTaiko::OnBtnBrum(CCObject* pSender)
 {
	 UIButton* pBtnIn = dynamic_cast<UIButton*>(getWidgetByName("BtnIn"));
	 //if(pBtnIn->isVisible())
	//	((CTaikoScene*)getParent())->clickBtnDrum();
 }