

#ifndef __OnceAgain__GameLayer_Crazy__
#define __OnceAgain__GameLayer_Crazy__
#include "cocos2d.h"
#include "CocosGUI.h"
#include "cocos-ext.h"
#include "ComData.h"
#include "BaseData.h"
USING_NS_CC_EXT;
USING_NS_CC;
enum{
	eStarEffectIDBegin = 5100,
	eStarEffectIDStar = 5101,
	eStarEffectIDEnd,
};

class CGameLayerCrazyMode : public UILayer{
    
public:
// 	static CGameLayerCrazyMode &sharedInstance(void) {
// 		if (m_pInstance == 0) {
// 			m_pInstance = new CGameLayerCrazyMode::create();
// 		}
// 		return (*m_pInstance);
// 	}
public:
    CGameLayerCrazyMode();
	~CGameLayerCrazyMode();

	virtual bool init();
	void play(ECrazyMode eMode);
	void pause();
	CREATE_FUNC(CGameLayerCrazyMode);
protected:
	//…Ë÷√–«–«∂Øª≠
	void setStarAni(CCSprite* pStar,bool bYellow);
	void setCrazyModeAni();
	void operateAllSchedulerAndActions(cocos2d::CCNode* node, ESwitchFlag flag);
private:
	static CGameLayerCrazyMode* m_pInstance;
};

#endif /* defined(__OnceAgain__GameLayer_Base__) */
