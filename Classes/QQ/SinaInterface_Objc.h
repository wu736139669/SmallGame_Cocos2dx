//
//  SinaInterface_Objc.h
//  OnceAgain
//
//  Created by mac on 14-4-1.
//
//

#import <Foundation/Foundation.h>
#import "WeiboSDK.h"

@interface SinaInterface_Objc : NSObject<WeiboSDKDelegate,WBHttpRequestDelegate>
{
    
}
+ (id)shareInstance;

- (void)login;
- (void)getFriend;
- (void)getUserInfo;
- (void)inviteUser:(const char*)uid;
@end
