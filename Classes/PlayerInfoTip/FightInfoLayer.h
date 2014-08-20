//
// FightInfoLayer.h
// OnceAgain
//
// Created by xiaohai on 14-5-9.
//
//

#ifndef __OnceAgain__FightInfoLayer__
#define __OnceAgain__FightInfoLayer__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;
USING_NS_CC;

class FightInfoLayer : public CCLayer, public CCTableViewDelegate, public CCTableViewDataSource
{
public:
    FightInfoLayer(){};
    ~FightInfoLayer(){};
    static CCScene* createScene();
    virtual bool init();
    
    virtual void scrollViewDidScroll(CCScrollView* view) {}
    virtual void scrollViewDidZoom(CCScrollView* view) {}
    
    //触摸到某个cell的事件
    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell) {};
    
    //定制每个cell的size
    virtual CCSize tableCellSizeForIndex(CCTableView *table, unsigned int idx);
    
    //定制每个cell的内容
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    
    //确定这个tableview的cell行数
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    
    CREATE_FUNC(FightInfoLayer);

    
private:
    void initData();
    void BindingUIItems();
 
    void creatMyTableView();
    
    CCSprite* getSpriteByScore(long score, CCPoint p,int kind);
    void refreshInfo();
public:
    //外部调用接口
    void setGameInfo(CSJson::Value info);
    
private:
    //绑定ui
    UILayer *ul;
    UIPanel *myTableView;//游戏得分列表
    UILabel *newAllScore;//最新总得分
	UILabel *lvLable;
	UILabel *NameLable;
	UIPanel *MaxScore;
	UIImageView *PlayerIcon;

	int playerLv;
	std::string playerName;
	std::string imgUrl;
	int totalScore;
private:
    //网络请求接口
    
private:
    //网络数据
    CSJson::Value data;
    int playertotalscore;//历史总得分
    CSJson::Value gameinfo;
};

#endif /* defined(__OnceAgain__FightInfoLayer__) */