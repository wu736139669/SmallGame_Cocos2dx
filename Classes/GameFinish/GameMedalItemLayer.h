//
// GameMedalItemLayer.h
// OnceAgain
//
// Created by xiaohai on 14-4-28.
//
//

#ifndef __OnceAgain__GameMedalItemLayer__
#define __OnceAgain__GameMedalItemLayer__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "cocos-ext.h"
#include "TaskManager.h"
#include "JudgeMedalGet.h"

USING_NS_CC_EXT;
USING_NS_CC;


class GameMedalItemLayer : public CCLayer, public  JudgeMedalGet
{
public:
    GameMedalItemLayer();
    ~GameMedalItemLayer();
    static CCScene* createScene();
    virtual bool init();
	void BadgeUpdate(float fX,float fY);	//更新渲染徽章图标
	void setRayTime(float td);	//设置光效更新的时间
private:
    void initData();
    void BindingUIItems();
    void isMedalGet();
    CCSprite* getCountNumber(int count);
    void medalGetCallBack(CCObject *p);
private:
	void getGradeTime(float td);
	void getGrade();
	void setRayRotation(float td);//设置光效旋转
	void SetBadgeTime(float td);//设置徽章的更新时间
	void setStart();			//设置星星
	void setStartTwinkle(float td);//设置星星闪烁;
public:
    //外部调用接口
    void setMadelInfo(SMeDalTaskData *info, int isGet, int gameId,bool bPlayerAni = false);//设置勋章信息
	bool m_bBadge;				//	
private:
    //绑定ui
    UILayer* ul;
    UIImageView* madelIcon;//勋章icon
    UIImageView* madelName;//勋章名
    UILabel* RewardNumber;//奖励数值
    UILabel* ScoreNumber;//最高得分数值
    UIImageView* GetMadelNode;//是否获得这枚勋章
    UIImageView* rewardType;//奖励类型
    UIImageView* isSeal;//是否有印章
    int medalId;
    int gameType;
    int numberPicLength;
public:
  	 CREATE_FUNC(GameMedalItemLayer);
};

#endif /* defined(__OnceAgain__GameMedalItemLayer__) */