//
//  SanXiaoItemLayer.h
//  OnceAgain
//
//  Created by xiaoqiang on 14-6-16.
//
//

#ifndef __OnceAgain__SanXiaoItemLayer__
#define __OnceAgain__SanXiaoItemLayer__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "cocos-ext.h"


USING_NS_CC_EXT;
USING_NS_CC;

#define PicStar 10              //加分星星
#define threeCross 11           //三排消
#define heng_Cross 12     //横消图形
#define zong_Cross 13            //纵消图形
#define sameColorPic 14         //同色消除
#define boomPic 15              //炸弹图片

class SanXiaoItemLayer : public CCLayer
{
public:
    SanXiaoItemLayer(){};
    ~SanXiaoItemLayer(){};
    static CCScene* createScene();
    virtual bool init();
    CREATE_FUNC(SanXiaoItemLayer);
    
private:
    

public:
    //外部调用接口
    void creatItemByTag(int num);
    int getItemType();
    void boomAndDel();
    void onClick();
    void freeClick();
    
private:
    //绑定ui
    void initUiData();
    void BindingUIItems();
    
    void doOpenEyeAction();
    
    CCSprite *picNormol;
    CCSprite *picOnClick;
    
    void removeSelFromp();
    
    
private:
    //网络请求接口
    
private:
    //内部数据
    int picNumber;
    
};

#endif /* defined(__OnceAgain__SanXiaoItemLayer__) */
