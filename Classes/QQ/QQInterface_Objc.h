//
//  QQInterface_Objc.h
//  OnceAgain
//
//  Created by mac on 14-3-31.
//
//

#import <Foundation/Foundation.h>
#import <TencentOpenAPI/TencentOAuth.h>
#import "TencentOpenAPI/QQApiInterface.h"
@interface QQInterface_Objc : NSObject<TencentSessionDelegate, QQApiInterfaceDelegate>
{
    NSArray *permissions;
    NSMutableArray *_friendArray;
    BOOL _hasNext;
    NSMutableDictionary *_userInfo;
}
@property (nonatomic, strong) TencentOAuth* tencentOAuth;
@property (nonatomic, strong) NSMutableArray* friendArray;
@property (nonatomic, strong) NSMutableDictionary *userInfo;
@property (nonatomic, assign)BOOL hasNext;

+ (id)shareInstance;
- (BOOL)isQZoneAuthValid;
//- (BOOL)isQZoneAuthValid:(NSString*)accessToken withOpenId:(NSString*)openId withDate:(NSDate*)date;
//- (void)shareToQZoneWithString:(CCString*)string withInfo:(CCString*)info imageURL:(CCString*)image withUrl:(CCString*)url;
//-(void)getFriend:(NSInteger) index;
//-(void)invitFriend:(NSString*)info;
-(void)getInfo;
//-(void)getOtherUserInfo:(NSString *)accessToken withId:(NSString*)openId;
-(void)login;

@end
