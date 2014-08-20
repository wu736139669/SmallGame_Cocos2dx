#include "AppDelegate.h"
#include "Scene_Welcome.h"
#include "DataManager.h"
#include "CsvManager.h"
#include "NetListProcess.h"

#include "GameUIExportJson.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
	//¥¥Ω® ˝æ›π‹¿Ì
	CDataManager::GetInstance();
	//¥¥Ω®∑µªÿ∞¸¥¶¿Ì
	CNetListProcess::sharedInstance();
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
	//pDirector->setContentScaleFactor()
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	
    pEGLView->setDesignResolutionSize(640, 1136, kResolutionExactFit);

    // turn on display FPS
	bool bDisStats = false;
#ifdef _WIN32
	bDisStats = true;
#endif
    //test
    //bDisStats = true;
    
	pDirector->setDisplayStats(bDisStats);
    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

	//º”‘ÿCsv ˝æ›
	CCsvManager::sharedInstance().registDatas();
	CCsvManager::sharedInstance().loadAllCsv();

    // create a scene. it's an autorelease object
    CCScene *pScene = Scene_Welcome::scene();
    

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
