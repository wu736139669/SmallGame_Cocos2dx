//
// MySelfInfoLayer.h
// OnceAgain
//
// Created by xiaohai on 14-5-9.
//
//

#ifndef __OnceAgain__MySelfInfoLayer__
#define __OnceAgain__MySelfInfoLayer__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;
USING_NS_CC;

class MySelfInfoLayer : public CCLayer
{
public:
    MySelfInfoLayer(){};
    ~MySelfInfoLayer(){};
    static CCScene* createScene();
    virtual bool init();
    CREATE_FUNC(MySelfInfoLayer);
    
private:
    void initData();
    void BindingUIItems();
    void refreshInfo();
    CCSprite *getSpriteByScore(long score,  CCPoint p, int kind);
public:
    //外部调用接口
    
    
private:
    //绑定ui
    UILayer *ul;

	UIPanel *allMedals;
	UILabel *allFightTimes;//总挑战场数
	UILabel *winTimes;//获胜场数
	UILabel *alike;		//平局
	UILabel *loseTimes;//失败场数
	UILabel *GoldNumber;//金牌数
	UILabel *Sliver;//银牌数
	UILabel *Broze;//铜牌数

    
private:
    //网络请求接口
    
private:
    //网络数据
	int medalNumber;
	int totalpk;//总pk数
	int winPk;//pk胜利场数
	int losePk;//输的场数
	int alikePk;
	int goldmodel;//金牌数
	int silverMedal;//银牌数
	int copperMedal;//铜牌数
    
	//网络数据
	CSJson::Value data;    
    
};

#endif /* defined(__OnceAgain__MySelfInfoLayer__) */