//
//  SanXiaoConfigAnalytical.h
//  OnceAgain
//
//  Created by xiaoqiang on 14-6-13.
//
//

#ifndef __OnceAgain__SanXiaoConfigAnalytical__
#define __OnceAgain__SanXiaoConfigAnalytical__

#include <iostream>
#include "cocos2d.h"
#include "Singleton.h"
#include "json_lib.h"

using namespace std;
USING_NS_CC;

#define picNumByScore "picNumByScore"                   //达到多少分出现5张图片
#define boomAddE "boomAddE"                             //炸弹每次增加能量
#define BatterToBeInsane "BatterToBeInsane"             //多少连击进入疯狂模式
#define BatterToBeSuperInsane "BatterToBeSuperInsane"   //多少连击进入超级疯狂模式
#define InsaneScore "InsaneScore"                       //疯狂模式分数倍率
#define superInsaneScore "superInsaneScore"             //超级疯狂模式分数倍率
#define lateral "lateral"                               //横向消除多次出现道具“横消”
#define longitudinal "longitudinal"                     //纵向消除多次出现道具“纵消”
#define st_scoreAdd_picNum "st_scoreAdd_picNum"         //强化，分数，消除图形数量
#define st_scoreAdd_score "st_scoreAdd_score"           //强化，分数，初始分
#define sd_picNum "sd_picNum"                           //三排消除，数量
#define lj_x "lj_x"                                     //连击计数x
#define lj_y_1 "lj_y_1"                                 //连击计数y
#define lj_y_2 "lj_y_2"                                 //连击计数y
#define lj_y_3 "lj_y_3"                                 //连击计数y
#define lj_gs_1 "lj_gs_1"                               //分数公式1
#define lj_gs_2 "lj_gs_2"                               //分数公式2

class sanxiaoConfigData : public CSingleton<sanxiaoConfigData> {
    
public:
    void getSanXiaoConfig();
    int getIntDataByName(const char* name);
    string getStringDataByName(const char* fileName);
    
private:
    CSJson::Value getJsonFromFile(const char* fileName);
    string getFullPath(const char* path);
protected:
    CSJson::Value sanXiaoData;
};

#endif /* defined(__OnceAgain__SanXiaoConfigAnalytical__) */
