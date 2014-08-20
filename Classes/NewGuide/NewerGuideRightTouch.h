

#ifndef __OnceAgain___NewerGuideRightTouch__
#define __OnceAgain___NewerGuideRightTouch__
#include "cocos2d.h"
#include "CocosGUI.h"
#include "cocos-ext.h"
#include "ComData.h"
#include "BaseData.h"
#include "GameShare_Property.h"
#include <vector>
USING_NS_CC_EXT;
USING_NS_CC;

class CNewerGuideRihgtTouch : public CCNode{
    
public:
	typedef std::vector<CCNode*> VEC_CELL;
public:
    CNewerGuideRihgtTouch();
	~CNewerGuideRihgtTouch();

	virtual void onEnter();
	virtual void onExit();
	void  play();
	
	void rtActCallfunc(CCNode* sender, void* data);
	CCActionInterval* actClick();
	CREATE_FUNC(CNewerGuideRihgtTouch);
protected:
	VEC_CELL mVecCell;
};

#endif /* defined(__OnceAgain__GameLayer_Base__) */
