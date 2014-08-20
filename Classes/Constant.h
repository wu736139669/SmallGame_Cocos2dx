//
//  Constant.h
//  ChallengesMaster
//
//  Created by mac on 14-2-20.
//  Stor Some const Value
//

#ifndef ChallengesMaster_Constant_h
#define ChallengesMaster_Constant_h


#define OFFSET_Y 50             //y－axis upward bias the center 50 pixcels
#define GAMETABLE_HEIGH 105     //game list heigh
#define GAMETABLE_WEIDTH 550    //game list width


//key for game
#define KEY_MEMORY_MAXSCORE "MEMORY_MAXSCORE"
#define KEY_LINK_MAXSCORE   "LINK_MAXSCORE"
#define KEY_FRUIT_MAXSCORE  "FRUIT_MAXSCORE"
#define KEY_JELLY_MAXSCORE  "JELLY_MAXSCORE"

//key for Music
#define KEY_ISMUSIC         "ISMUSIC"
#define KEY_ISMUSICEFFECT   "ISMUSICEFFECT"
// game
#define GAMENUM 6              //games num

//炸弹的最大能量。
#define BOOM_MAXENERGY          100

//Game Name
#define GAMENAME_LINK            "连连看"
#define GAMENAME_MEMORY          "记忆力"
#define GAMENAME_FRUIT           "水果"
#define GAMENAME_JELLY           "合体"

//添加饭的时间单位s
#define RICEADDTIME       480
//送饭的间隔时间单位s
#define RICESEND        (3600*2)

enum Tag_Layer
{
    Tag_Min = 0,
    Tag_Max = 100
};

//appid
#define kAppID              @"771682876"
#define kQQAppKey     @"100559645"
//#define kQQAppKey     @"222222"
#define kQQAppSecret  @"17fbad3a77765d9bb18229b86bbae4ed"
#define kQQAppRedirectURI         @"www.qq.com"

//新浪微博
#define kSinaAppKey             @"3466829587"
#define kSinaAppSecret          @"f627d4348a43f009afcb4723eeef1a50"
#define kSinaAppRedirectURI     @"https://api.weibo.com/oauth2/default.html"
#endif
