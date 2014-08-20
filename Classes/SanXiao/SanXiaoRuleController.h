//
//  SanXiaoRuleController.h
//  OnceAgain
//
//  Created by xiaoqiang on 14-6-16.
//
//

#ifndef __OnceAgain__SanXiaoRuleController__
#define __OnceAgain__SanXiaoRuleController__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameSanXiaoLayer.h"
#include "Singleton.h"

USING_NS_CC_EXT;
USING_NS_CC;

class SanXiaoRuleController :public CSingleton<SanXiaoRuleController> {
public:
    std::vector<ItemBox> refreshItemBoxWithDoMove(std::vector<ItemBox>box);
    std::vector<int> wellBeDelItems(std::vector<ItemBox>box, int kind);
    
    int getDelCountBy3(){return countBy3;};
    int getDelCountBy4(){return countBy4;};
    int getDelCountBy5(){return countBy5;};
    int getHengCount(){ return hengCount;};
    int getZongCount(){return zongCount;};
    
        
    
    std::vector<ItemBox> refreshItemBoxWithClickBoom(std::vector<ItemBox>box, int boomIndex);
    
    std::vector<ItemBox> refreshItemBoxWithHengCross(std::vector<ItemBox>box, int boomIndex);
    
    std::vector<ItemBox> refreshItemBoxWithZongCross(std::vector<ItemBox>box, int boomIndex);
    
    std::vector<ItemBox> refreshItemBoxWithThreeCross(std::vector<ItemBox>box, int boomIndex);
private:
    int countBy3;
    int countBy4;
    int countBy5;
    
    int hengCount;
    int zongCount;
};




#endif /* defined(__OnceAgain__SanXiaoRuleController__) */
