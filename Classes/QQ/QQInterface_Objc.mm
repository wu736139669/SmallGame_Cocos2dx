//
//  QQInterface_Objc.m
//  OnceAgain
//
//  Created by mac on 14-3-31.
//
//

#import "QQInterface_Objc.h"
#import "Constant.h"
#import "GameShare_Global.h"
#import "cocos2d.h"
#import "GameShare_Msg.h"
#import "GameShare_Data.h"
#import "PlayerInfoManager.h"
static QQInterface_Objc *instance = nil;
@implementation QQInterface_Objc
@synthesize tencentOAuth;
@synthesize friendArray = _friendArray;
@synthesize hasNext = _hasNext;
@synthesize userInfo = _userInfo;
+ (id)shareInstance
{
    if (instance == nil)
    {
        instance = [[QQInterface_Objc alloc] init];
    }
    return instance;
}

- (id)init
{
    self = [super init];
    if (self)
    {
        _hasNext = NO;
        _friendArray = [[NSMutableArray alloc] init];
        permissions = [NSArray arrayWithObjects:
                       kOPEN_PERMISSION_GET_USER_INFO,
                       nil];
        
        
        tencentOAuth = [[TencentOAuth alloc] initWithAppId:kQQAppKey
                                               andDelegate:self];
        tencentOAuth.redirectURI = kQQAppRedirectURI;
        
        
        
    }
    return self;
}

- (void)getInfo{
    if ([tencentOAuth getUserInfo]) {
        //        [self loadErrorAction];
    }
}
- (BOOL)isQZoneAuthValid
{
    if (tencentOAuth.accessToken==nil || tencentOAuth.openId==nil ||([tencentOAuth.expirationDate compare:[NSDate date]] == NSOrderedAscending))
    {
        return NO;
    }
    return YES;
}

/**
 * @description 判断登录是否有效，当已登录并且登录未过期时为有效状态
 * @return YES为有效；NO为无效
 */
- (void)login
{
    
    [tencentOAuth authorize:permissions inSafari:NO];
}
-(void)logout
{
    [tencentOAuth logout:nil];
}

//- (void)shareToQZoneWithString:(NSString*)string withInfo:(NSString*)info imageURL:(NSString*)image withUrl:(NSString *)url
//{
//	NSString *utf8String = url;
//    NSString *title = string;
//    NSString *description = info;
//    NSString *previewImageUrl = image;
//    QQApiNewsObject *newsObj = [QQApiNewsObject
//                                objectWithURL:[NSURL URLWithString:utf8String]
//                                title:title
//                                description:description
//                                previewImageURL:[NSURL URLWithString:previewImageUrl]];
//    SendMessageToQQReq *req = [SendMessageToQQReq reqWithContent:newsObj];
//    //将内容分享到qq
//    //QQApiSendResultCode sent = [QQApiInterface sendReq:req];
//    //将内容分享到qzone
//    QQApiSendResultCode sent = [QQApiInterface SendReqToQZone:req];
//    [self handleSendResult:sent];
//}


/**
 * Called when the user successfully logged in.
 */
- (void)tencentDidLogin {
	// 登录成功
    
    if (tencentOAuth.accessToken && 0 != [tencentOAuth.accessToken length])
    {
        
        CPlayerInfoMan::sharedInstance().getPlayerInfo().strQQ = [tencentOAuth.openId UTF8String];
        GameShare_Data::shareData()->setQQID([tencentOAuth.openId UTF8String], [tencentOAuth.accessToken UTF8String], [tencentOAuth.expirationDate timeIntervalSince1970]);
        cocos2d::CCNotificationCenter::sharedNotificationCenter()->postNotification(kQQLoginSuccess, NULL);
    }
    else
    {
    }
    
}


/**
 * Called when the user dismissed the dialog without logging in.
 */
- (void)tencentDidNotLogin:(BOOL)cancelled
{
	if (cancelled)
    {
        NSLog(@"cancelled");
	}
	else
    {
        
	}
	
}

/**
 * Called when the notNewWork.
 */
-(void)tencentDidNotNetWork
{
    NSLog(@"NotNetWork");
}

/**
 * Called when the logout.
 */
-(void)tencentDidLogout
{
}

- (void)handleSendResult:(QQApiSendResultCode)sendResult
{
    switch (sendResult)
    {
        case EQQAPISENDSUCESS:
        case EQQAPIAPPNOTREGISTED:
        {
            
            break;
        }
        case EQQAPIMESSAGECONTENTINVALID:
        case EQQAPIMESSAGECONTENTNULL:
        case EQQAPIMESSAGETYPEINVALID:
        {
            
            break;
        }
        case EQQAPIQQNOTINSTALLED:
        {
            break;
        }
        case EQQAPIQQNOTSUPPORTAPI:
        {
            
            break;
        }
        case EQQAPISENDFAILD:
        {
            
            break;
        }
        default:
        {
            break;
        }
    }
}

#pragma mark qqdelegate
-(void)isOnlineResponse:(NSDictionary *)response
{
    
}
-(void)onReq:(QQBaseReq *)req{
    
}
-(void) onResp:(QQBaseResp*)resp
{
    if([resp isKindOfClass:[SendMessageToQQResp class]])
    {
        if ([[resp result] isEqualToString:@"0"]) {
            
        }else{
        }
        
    }
    
}
@end
