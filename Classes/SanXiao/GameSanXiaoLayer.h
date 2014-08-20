//
// GameSanXiaoLayer.h
// OnceAgain
//
// Created by xiaoqiang on 14-6-13.
//
//

#ifndef __OnceAgain__GameSanXiaoLayer__
#define __OnceAgain__GameSanXiaoLayer__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "cocos-ext.h"
#include "GameShare_Scene.h"
#include "SanXiaoItemLayer.h"

USING_NS_CC_EXT;
USING_NS_CC;


struct ItemBox {
    SanXiaoItemLayer *itemNode;
    int number;
    CCPoint ItemPoint;
    bool wellRemove;
    int type;
};

class GameSanXiaoLayer : public GameShare_Scene
{
public:
    GameSanXiaoLayer(){};
    ~GameSanXiaoLayer(){};
    static CCScene* createScene();
    virtual bool init();
    virtual void onExit();
    CREATE_FUNC(GameSanXiaoLayer);
    
    
    virtual bool ccTouchBegan(CCTouch *touch, CCEvent *event);
    virtual void ccTouchMoved(CCTouch *touch, CCEvent *event);
    virtual void ccTouchEnded(CCTouch *touch, CCEvent *event);
    
    
    virtual void Update(float fDelta){};
    virtual void initBgView(void);
    //开始游戏.
    virtual void startGame(float dt=1.0);
    
    //时间结束的处理
    virtual void msgHanlde_GameTimeOut(CCObject* obj);
    
    //炸弹能量满的通知.
    virtual void msgHanlde_BoomFull(CCObject* obj);
    
    //疯狂模式结束消息处理函数
    virtual void msgHandle_CrazyTimeOut(CCObject* obj);
    
    virtual void noticeTimeInterval(CCObject* obj);
    
private:
    //ui容器
    CCNode *ITEMSNODE;
  
public:
    //外部调用接口
    
private:
    void initUiData();
    void BindingUIItems();
    int getIndexByPoint(CCPoint p);
    
    void MoveItems(int MoveR);//开始移动
    void callBackByMoveFinish();
    void refreshCallBack();
    
    void begainDeleItem();//开始消除
    void DeleDCallBackRefreshMap();//消除结束后，重新排布
    void RefreshMapCallBack();//重新排布完之后，创建新的Itms填充空位；
    void refreshItemPoints();//更新位置信息
    
    void setMyScore(int kind);
    
    void getPropUsedInfo();//获取道具使用信息
    
private:
    //数据容器
    std::vector<ItemBox>itemList;//所有Item的总容器
    std::vector<ItemBox>ItemInMovingList;//移动中的item容器
    
    std::vector<ItemBox>empytItemBox;//item空缺的容器
    
private:
    //内部数据
    int touchBeginIndex;
    bool canBeTouch;
    int MoveDFinishnumber;
    int NewCreatNumber;
    
    
    int batterScoreModel;
    int batterModel;
    
    bool moveStatus;
    int delItemsCounts;//总共消除的个数
private:
    bool isInPropModel;
    //道具与强化
    bool Prop_superModel;//疯狂开局
    bool Prop_timeAdd;//时间延长
    bool Prop_sameColorDel;//同色消除
    bool Prop_crossDel;//十字消除
    
    bool Strengthen_star;//强化星星
    int Strengthen_star_number;
    bool Strengthen_threeCross;//三排消除
    int Strengthen_threeCross_number;
    bool Strengthen_addScore;//格外加分
    int Strengthen_addScore_number;
    
    int hengXiaoCount;//横向消除计数
    bool isShowHengItem;
    int zongXiaoCount;//纵向消除计数
    bool isShowZongItem;
    
    bool isShowSanHengItem;
    //炸弹
    bool isboomFull;
};

#endif /* defined(__OnceAgain__GameSanXiaoLayer__) */