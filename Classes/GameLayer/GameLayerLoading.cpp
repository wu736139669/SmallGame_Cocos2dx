

#include "SpriteFrameManage.h"
#include "GameShare_Global.h"
#include "GameShare_Scene.h"
#include "GameLayerLoading.h"
#include "GameLayer_Tag.h"

IMPLEMENT_DLG_ID(CGameLayerLoading,GameLayerLoading_Tag);
CGameLayerLoading::CGameLayerLoading():m_pListener(NULL),m_pfnSelector(NULL),mpUILayer(NULL)
{

}
CGameLayerLoading::~CGameLayerLoading()
{

}

bool CGameLayerLoading::init()
{
	 //if(!UILayer::init())
	if(!CCLayer::init())
		return false;
	mpUILayer = UILayer::create();
	 //auto ly = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("./CocoStudioResources/layoutLoading/layoutLoading_1.json"));
    auto ly = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("./CocoStudioResources/layoutLoading0/layoutLoading_1.ExportJson"));
    
	 this->mpUILayer->addWidget(ly);
	 addChild(mpUILayer);

// 	 UIPanel* taskPanel = dynamic_cast<UIPanel*>(mpUILayer->getWidgetByName("Panel_20"));
// 	 taskPanel->setBackGroundColor(ccBLACK);
// 	 taskPanel->setBackGroundColorOpacity(150);
	 return true;
}
void CGameLayerLoading::onExit()
{
	 CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}
 void CGameLayerLoading::onEnter()
 {
	// UILayer::onEnter();
	  CCLayer::onEnter();
	  CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(  
		  this,
		  kCCMenuHandlerPriority - 1, // -128-1 = -129”≈œ»º∂    
		  true);
	 play();
 }
 void CGameLayerLoading::play()
 {
	 UIPanel* pBg = dynamic_cast<UIPanel*>(this->mpUILayer->getWidgetByName("Panel_20"));
	 UIImageView* info_click1 = dynamic_cast<UIImageView*>(this->mpUILayer->getWidgetByName("loading"));
	 UIImageView* info_click2 = dynamic_cast<UIImageView*>(this->mpUILayer->getWidgetByName("loading_out"));
	 info_click2->runAction(CCRepeatForever::create(CCRotateBy::create(0.12f,30)));

	 CCAnimation* pAni1 = CCAnimation::create();
	 CCString str;
	 for (int i = 1; i <= 2; ++i){
		 str.initWithFormat("loading_%d.png",i);
		 pAni1->addSpriteFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName(str.getCString()));
	 }
	 pAni1->setDelayPerUnit(0.12f);
	 pAni1->setLoops(1);
	 CCSprite* p = CCSprite::create();
	 p->runAction(CCRepeatForever::create(CCAnimate::create(pAni1)));
	 p->setPosition(info_click1->getPosition());

	 pBg->addRenderer(p,1);
 }
 void CGameLayerLoading::onShow()
 {
// 	 auto p =  dynamic_cast<GameShare_Scene*>(getParent());
// 	 if(p){
// 		 p->removeTouchDelegate();
// 	 }
	 
 }
 void CGameLayerLoading::onHide()
 {
// 	 auto p =  dynamic_cast<GameShare_Scene*>(getParent());
// 	 if(p){
// 		 p->addTouchDelegate();
// 	 }
	
 }
//  void CGameLayerLoading::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
//  {
// 	 OnBtnClose(NULL);
//  }
 
 void CGameLayerLoading::onBtnClose(CCObject* p)
 {
	removeFromParent();
 }
 void CGameLayerLoading::setCallfunc(CCObject *target, SEL_CallFuncO callfun)
 {
	 this->m_pListener = target;
	 this->m_pfnSelector = callfun;
 }
 bool CGameLayerLoading::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)  
 {  
	 //m_bTouchedMenu = m_pMenu->ccTouchBegan(pTouch, pEvent);  
	 return true;  
 }  

 void CGameLayerLoading::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)  
 {  
// 	 if (m_bTouchedMenu) {  
// 		 m_pMenu->ccTouchMoved(pTouch, pEvent);  
// 	 }  
 }  

 void CGameLayerLoading::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)  
 {  
// 	 if (m_bTouchedMenu) {  
// 		 m_pMenu->ccTouchEnded(pTouch, pEvent);  
// 		 m_bTouchedMenu = false;  
// 	 }  
 }  

 void CGameLayerLoading::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)  
 {  
// 	 if (m_bTouchedMenu) {  
// 		 m_pMenu->ccTouchEnded(pTouch, pEvent);  
// 		 m_bTouchedMenu = false;  
// 	 }  
 }