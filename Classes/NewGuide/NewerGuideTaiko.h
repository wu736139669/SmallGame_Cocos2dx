

#ifndef __OnceAgain___NewerGuideTaiko__
#define __OnceAgain___NewerGuideTaiko__
#include "cocos2d.h"
#include "CocosGUI.h"
#include "cocos-ext.h"
#include "ComData.h"
#include "BaseData.h"
#include "GameShare_Property.h"
#include <vector>
#include "SpriteFrameManage.h"
USING_NS_CC_EXT;
USING_NS_CC;
class CNewerGuideTaiko : public CCNode{
    
public:
	typedef std::vector<CCSprite*> VEC_CELL;
public:
    CNewerGuideTaiko();
	~CNewerGuideTaiko();

	virtual void onEnter();
	virtual void onExit();
	void  play();
	
	void actCallfunc(CCNode* sender, void* data);
	 void actAngleCallfunc(CCNode* sender, void* data);
	CCActionInterval* actClick();
	CREATE_FUNC(CNewerGuideTaiko);
protected:
	VEC_CELL mVecCell;
	CCSprite* mpL;
	CCSprite* mpR;
	CCSprite* mpM;
	CCSprite* mpML;
	CCSprite* mpMR;
	CCSprite* mpFinger;
};

#endif /* defined(__OnceAgain__GameLayer_Base__) */
