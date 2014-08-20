

#ifndef __OnceAgain___NewerGuideFriut__
#define __OnceAgain___NewerGuideFriut__
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
class CFruitGuide : public CCNode
{
public:
	CCSprite* pCell;
	CCSprite* pLine;
public:
	virtual bool init()
	{
		CCNode::init();
		pCell = CCSprite::create();
		pLine = CCSprite::createWithSpriteFrame(CCSpriteFrameManage::getInstance()->spriteFrameByName("item/line.png"));  
		pLine->setVisible(false);
		pLine->setAnchorPoint(ccp(0,0.5));
		addChild(pLine);
		addChild(pCell);
		
		return true;
	}
	CREATE_FUNC(CFruitGuide);
};
class CNewerGuideFruit : public CCNode{
    
public:
	typedef std::vector<CFruitGuide*> VEC_CELL;
public:
    CNewerGuideFruit();
	~CNewerGuideFruit();

	virtual void onEnter();
	virtual void onExit();
	void  play();
	
	void actCallfunc(CCNode* sender, void* data);
	 void actAngleCallfunc(CCNode* sender, void* data);
	CCActionInterval* actClick();
	CREATE_FUNC(CNewerGuideFruit);
protected:
	VEC_CELL mVecCell;
	VEC_CELL mVecCellPath;
};

#endif /* defined(__OnceAgain__GameLayer_Base__) */
