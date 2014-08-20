//
//  GameLayer_MaxScore.h
//  OnceAgain
//
//  Created by mac on 14-4-14.
//
//

#ifndef __OnceAgain__GameLayer_MaxScore__
#define __OnceAgain__GameLayer_MaxScore__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "GameLayer_Base.h"

//添加命名空间
USING_NS_CC_EXT;
USING_NS_CC;
class GameLayer_MaxScore : public GameLayer_Base {


public:
	virtual bool init(void);
	~GameLayer_MaxScore(void);
	GameLayer_MaxScore(void){m_pfnSelector=NULL;m_pListener=NULL;};
	CREATE_FUNC(GameLayer_MaxScore);
	//结果分数.
	CC_SYNTHESIZE(int, resultScore, ResultScore);
	//最高分数
	CC_SYNTHESIZE(int, maxScore, MaxScore);

	//设置按钮的方法.
	void addSureCallbackFunc(CCObject* target, SEL_CallFunc callfun);
	//
	void sureBtnCallback(CCObject* pSender);
	void playAgain(CCObject* pSender);
	//判断显示返回菜单按钮 还是确定按钮；
	void getButton(bool bButton);
	//设置历史最高分.
	void setScoreCallBack();
	//设置分数背景
	void setGradeBack(float td);
	void getGrade(float td);
	void setHighestGradeBack(float td);		//最高分背景
	void setStarMedal(float td);		//星星勋章
	void setEffects(float td);			//特效
	void addGrade(float td);			//add分数
	void getAnimation(float td);		//获得动画效果
	CCSprite *pEffects;					//3个特效
	CCSprite *pEffects2;
	CCSprite *pEffects3;
	CCSprite *addSprite;				//加成
	CCSprite *goldSprite;				//金币
	CCSprite *expSprite;				//经验
	CCSprite *pFalseGrade;				//假分数
	UIImageView *addSpriteBg;
	UIImageView *expSpriteBg;			//获得加成的背景 
	UIImageView *goldSpriteBg;
	UIImageView *addImg;
	UIImageView *expImg;			    //获得加成的图标 
	UIImageView *goldImg;
	UIButton* returnBtn;				//返回列表
	UIButton* againBtn;					//再来一局
	int  iEffectType;					//光效的种类
	int  iAddTypeNum;					//什么时候显示加成和按钮

private:
	UILayer* ul;
	UILayer* ulBg;
	UILabelAtlas* lvLabel;
	UIImageView *star1;
	UIImageView *star2;
	UIImageView *star3;
	UIImageView *star4;
	UIImageView *star5;
	UIImageView *star6;
	UIImageView *star7;
	UIImageView *star8;

	CCObject*       m_pListener;
	SEL_CallFunc    m_pfnSelector;
};

#endif /* defined(__OnceAgain__GameLayer_MaxScore__) */
