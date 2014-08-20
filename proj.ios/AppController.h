#import <UIKit/UIKit.h>
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#include "QQInterface.h"
#include "SinaInterface_Objc.h"
#include "WeiboSDK.h"
#import <TencentOpenAPI/TencentOAuth.h>
#import "TencentOpenAPI/QQApiInterface.h"
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#endif
@class RootViewController;

@interface AppController : NSObject <UIApplicationDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
}

@end

