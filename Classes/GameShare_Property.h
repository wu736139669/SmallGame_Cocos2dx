//
//  GameShare_Property.h
//  OnceAgain
//
//  Created by mac on 14-2-28.
//
//

#ifndef __OnceAgain__GameShare_Property__
#define __OnceAgain__GameShare_Property__


struct sGameProperty
{
	int historyscore;	//历史最高分；
    int highestscore;   //本周最高分.
    int totolscore;    //最终总分.
    int playermoney;   //玩家总金币.
    int levelrewardvalue;   //升级奖励。
    int playerexp; //玩家总经验.
    int addexp;     //增加的经验.
    int addmoney;   //增加的钱
    int playerlevel; //游戏结束等级
    int levelrewardtype; //游戏升级奖励类型.
    float leveladdscore; //游戏分数增加比率.
    int prescore;       //游戏结束时候的分数.
};

enum e_GameType
{
    Game_Null = 0,
    Game_Memory = 1,	//记忆
    Game_Jelly = 2,		//合体消除
    Game_Fruit = 3,		//宝石连线
    Game_Link = 4,		//快速配对
	Game_TaiKo = 5,		//音乐达人
    Game_SanXiao = 6,  //三消达人
    Game_Cir = 7,
    
};

#endif /* defined(__OnceAgain__GameShare_Property__) */
