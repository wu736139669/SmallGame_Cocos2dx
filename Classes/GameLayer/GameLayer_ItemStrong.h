//
//  GameLayer_ItemStrong.h
//  OnceAgain
//
//  Created by mac on 14-3-25.
//
//

#ifndef __OnceAgain__GameLayer_ItemStrong__
#define __OnceAgain__GameLayer_ItemStrong__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "GameLayer_Base.h"
//添加命名空间
USING_NS_CC_EXT;
USING_NS_CC;
class GameLayer_ItemStrong : public GameLayer_Base
{
public:
    virtual bool init(void);
    virtual void setVisible(bool visible);
    ~GameLayer_ItemStrong(void);
    GameLayer_ItemStrong(void);
    CREATE_FUNC(GameLayer_ItemStrong);
    
    //设置确定的方法.
    void setSureCallbackFunc(CCObject* target, SEL_CallFuncO callfun);
    //设置确定按钮的tag
    void setSureBtnTag(int tag);
    //设置显示的字符.
    void setItemInfo(const char* str);
    //设置等级.
    void setItemLv(int itemLv);
    //设置所需货币.
    void setItemCurrency(int str);
    //升级成功
    void successLvUp();
    //设置图片.
    void setItemImg(const char* str);
    //设置名称.
    void setItemName(const char* str);
    //设置按钮灰色不可点击
    void setBtnUnClick();
    
    //设置按钮可点击
    void setBtnCanClick();
	//获得道具的等级
	CCSprite* getItemLv(int num);
private:
    UILayer* itemStrong;
    
    //点击确定按钮.
    void sureBtnCallback(CCObject* pSender);
    //点击关闭按钮.
    void closeBtnCallback(CCObject* pSender);
    //增加闪烁的星星.
    void addStarSprite();
    CCObject*       m_pListener;
    SEL_CallFuncO    m_pfnSelector;
    
};
#endif /* defined(__OnceAgain__GameLayer_ItemStrong__) */
