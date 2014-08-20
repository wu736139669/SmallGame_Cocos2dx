//
//  JudgeNetEnvironment.cpp
//  OnceAgain
//
//  Created by xiaoqiang on 14-5-26.
//
//

#include "JudgeNetEnvironment.h"
//#include "SystemInfo.h"
#import "Reachability.h"
NSString* testPage = @"www.baidu.com";

float getBatteryLeve()
{
    [[UIDevice currentDevice] setBatteryMonitoringEnabled:YES];
    return [[UIDevice currentDevice] batteryLevel];
}

// 检测WIFI是否可用
bool isWIFIEnabled()
{
    return ([[Reachability reachabilityForLocalWiFi] currentReachabilityStatus] == ReachableViaWiFi);
}

// 检测3G网络是否可用
bool is3GEnabled()
{
    return ([[Reachability reachabilityForInternetConnection]currentReachabilityStatus] == ReachableViaWWAN);
}


NetState getNetState()
{
    
    Reachability *r = [Reachability reachabilityWithHostname:testPage];
    switch ([r currentReachabilityStatus]) {
        case NotReachable:
            // 没有网络连接
            return NoNetWork;
            break;
        case ReachableViaWWAN:
            // 使用3G网络
            return Conn3G;
            break;
        case ReachableViaWiFi:
            // 使用WiFi网络
            return ConnWiFi;
            break;
    }
    
}


