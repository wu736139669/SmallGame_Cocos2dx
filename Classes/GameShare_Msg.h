//
//  GameShare_Msg.h
//  OnceAgain
//
//  Created by xiaohai on 14-2-25.
//
//

#ifndef OnceAgain_GameShare_Msg_h
#define OnceAgain_GameShare_Msg_h

const char* const kGameTimeOutNamePer = "GameTimeOutPer"; // time out per procces
const char* const kGameTimeOutName = "Game_TimeOut"; //timeout notify
const char* const kGameResume      = "kGameResume"; //继续游戏.
const char* const kGameBoomFull    = "kGameBoomFull";//炸弹能量满.
const char* const kCrazyTimeOut    = "kCrazyTimeOut";//疯狂模式结束
const char* const kQQLoginSuccess  = "QQLoginSuccess";      //qq登陆成功.
const char* const kSinaLoginSuccess = "SinaLoginSuccess";   //sina登陆成功
const char* const kSinaGetFriendSuccess = "SinaGetFriendSuccess";   //获取好友成功.
const char* const kRegistSuccess = "RegistSuccess";          //注册成功.
const char* const kTimeInterval = "kTimeInterval";          //0.1秒执行一次
const char* const kGetAllScoreRank = "kGetAllScoreRank";    //获取所有总分排行的通知.
const char* const kGetSysInfo   = "kGetSysInfo";            //获取系统消息.
const char* const kReceiveRice = "kGetReceiveRice";         //领取体力
const char* const kLoginFail = "kLoginFail";      //登陆失败.
const char* const kSetScore = "kSetScore";                  //设置游戏结束分数.
const char* const kGetWeekTask = "kGetWeekTask";        //获取周任务
const char* const kGetSysNum = "kGetSysNum";            //获取系统数量.
const char* const kGetFriendInfoList = "kGetFriendInfoList"; //从后端获取所有的好友信息
const char* const kRefreshMoney = "kRefreshMoney"; //刷新体力
const char* const kRequestPlayerMoneyInfo = "kRequestPlayerMoneyInfo"; //请求游戏金币数据
#endif
