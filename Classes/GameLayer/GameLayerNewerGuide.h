

#ifndef __OnceAgain__GameLayer_Newer__
#define __OnceAgain__GameLayer_Newer__
#include "cocos2d.h"
#include "CocosGUI.h"
#include "cocos-ext.h"
#include "ComData.h"
#include "BaseData.h"
#include "GameShare_Property.h"
#include <vector>

USING_NS_CC_EXT;
USING_NS_CC;
enum ENewerGuideType{
	eNewerGuideStart,
	eNewerGuideMax,
};
class CGameLayerNewerGuide : public UILayer{
    
public:
	typedef std::vector<CCNode*> VEC_CELL;
public:
    CGameLayerNewerGuide();
	~CGameLayerNewerGuide();

	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	void  play(e_GameType eType);
	void OnBtnClose(CCObject*);
	void setCallfunc(CCObject *target, SEL_CallFuncO callfun);
	CREATE_FUNC(CGameLayerNewerGuide);
protected:
	
private:
	static CGameLayerNewerGuide* m_pInstance;
	CCObject*       m_pListener;
	SEL_CallFuncO    m_pfnSelector;
	CC_SYNTHESIZE(ENewerGuideType,mType,Type);
};

#endif /* defined(__OnceAgain__GameLayer_Base__) */
