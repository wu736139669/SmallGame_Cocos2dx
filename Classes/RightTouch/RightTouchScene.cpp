//#include "StaticData.h"
#include "RightTouchScene.h"
#include "RTItemLayer.h"
#include "SimpleAudioEngine.h"
#include "AudioHelper.h"
#include "AudioDefine.h"
#include "SpriteFrameManage.h"
USING_NS_CC;

void CRightTouchScene::preloadResources()
{
    CCSpriteFrameManage::getInstance()->addSpriteFramesWithFile("right_touch/right_touch0.plist");
    
//     int frameCount = STATIC_DATA_INT("fish_frame_count");
//     for (int type = k_Fish_Type_Red; type < k_Fish_Type_Count; type++) {
//         CCArray* spriteFrames = CCArray::createWithCapacity(frameCount);
//         for(int i = 0;i < frameCount;i++){
//             CCString* filename = CCString::createWithFormat(STATIC_DATA_STRING("fish_frame_name_format"),type,i);
//             CCSpriteFrame* spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(filename->getCString());
//             spriteFrames->addObject(spriteFrame);
//         }
//         CCAnimation* fishAnimation = CCAnimation::createWithSpriteFrames(spriteFrames);
//         fishAnimation->setDelayPerUnit(STATIC_DATA_FLOAT("fish_frame_delay"));
//         CCString* animationName = CCString::createWithFormat(STATIC_DATA_STRING("fish_animation"), type);
//         CCAnimationCache::sharedAnimationCache()->addAnimation(fishAnimation, animationName->getCString());
//     }
    
    //FishingJoyData::sharedFishingJoyData();
    //PersonalAudioEngine::sharedEngine();
}
void CRightTouchScene::onEnterTransitionDidFinish()
{
    CCScene::onEnterTransitionDidFinish();
	//CAudioHelper::playBackgroundSound(eSoundTypeRightTouchBackground);
}
void CRightTouchScene::onExit()
{
	CCScene::onExit();
	CAudioHelper::stopBackgroundSound();
}
bool CRightTouchScene::init()
{
    preloadResources();
    if(CCScene::init()){
		
       // mpBgLayer = CRTBgLayer::create();
        //this->addChild(mpBgLayer);
        
         mpItemLayer = CRTItemLayer::create();
         this->addChild(mpItemLayer);
//         
//         _cannonLayer = CannonLayer::create();
//         this->addChild(_cannonLayer);
        
//         _panelLayer = PanelLayer::create();
//         this->addChild(_panelLayer);

//         _menuLayer = MenuLayer::create();
//         CC_SAFE_RETAIN(_menuLayer);
        
       // mpTouchLayer = CRTTouchLayer::create();
        //this->addChild(mpTouchLayer);
        
        this->scheduleUpdate();
        return true;
    }
    return false;
}
void CRightTouchScene::pause()
{
    //PersonalAudioEngine::sharedEngine()->pauseBackgroundMusic();
    //PersonalAudioEngine::sharedEngine()->playEffect(STATIC_DATA_STRING("sound_button"));
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    this->operateAllSchedulerAndActions(this, eOperatePause);
    mpTouchLayer->setTouchEnabled(false);
   // this->addChild(_menuLayer);
}
void CRightTouchScene::resume()
{
    this->operateAllSchedulerAndActions(this, eOperateResume);

	CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    //PersonalAudioEngine::sharedEngine()->resumeBackgroundMusic();
   // this->removeChild(_menuLayer, false);
    mpTouchLayer->setTouchEnabled(true);
}
void CRightTouchScene::operateAllSchedulerAndActions(cocos2d::CCNode* node, EOperateFlag flag)
{
    if(node->isRunning()){
        switch (flag) {
            case eOperatePause:
                node->pauseSchedulerAndActions();
                break;
            case eOperateResume:
                node->resumeSchedulerAndActions();
                break;
            default:
                break;
        }
        CCArray* array = node->getChildren();
        if(array != NULL && array->count()>0){
            CCObject* iterator;
            CCARRAY_FOREACH(array, iterator){
                CCNode* child = (CCNode*)iterator;
                this->operateAllSchedulerAndActions(child, flag);
            }
        }
    }
}
void CRightTouchScene::sound()
{
   // bool flag = FishingJoyData::sharedFishingJoyData()->getSoundVolume()>0;
    //PersonalAudioEngine::sharedEngine()->setEffectsVolume(!flag);
}
void CRightTouchScene::music()
{
    //bool flag = FishingJoyData::sharedFishingJoyData()->getMusicVolume()>0;
    //PersonalAudioEngine::sharedEngine()->setBackgroundMusicVolume(!flag);
}
void CRightTouchScene::reset()
{
}
void CRightTouchScene::transToMainMenu()
{
}
CRightTouchScene::~CRightTouchScene()
{
    //CC_SAFE_RELEASE(_menuLayer);
}

void CRightTouchScene::update(float delta)
{
	if(mpItemLayer)
	 mpItemLayer->updateData(delta);
}

//void CRightTouchScene::alterGold(int delta)
//{
    //FishingJoyData::sharedFishingJoyData()->alterGold(delta);
    //_panelLayer->getGoldCounterLayer()->setNumber(FishingJoyData::sharedFishingJoyData()->getGold());
//}
void CRightTouchScene::scheduleTimeUp()
{
    //this->alterGold(STATIC_DATA_INT("recovery_gold"));
}
