//
//  JudgeNetEnvironment.h
//  OnceAgain
//
//  Created by xiaoqiang on 14-5-26.
//
//

#ifndef __OnceAgain__JudgeNetEnvironment__
#define __OnceAgain__JudgeNetEnvironment__

typedef enum
{
	// Apple NetworkStatus Compatible Names.
	NoNetWork    = 0,
	ConnWiFi     = 2,
	Conn3G       = 1
} NetState;


// 获取电池电量，范围0到1.0。－1表示电量未知。
float getBatteryLeve();

// 检测WIFI是否可用
bool isWIFIEnabled();


// 检测3G网络是否可用
bool is3GEnabled();

//取得网络连接状况
NetState getNetState();


#endif /* defined(__OnceAgain__JudgeNetEnvironment__) */
