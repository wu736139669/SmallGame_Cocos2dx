//
//  SinaInterface_Objc.m
//  OnceAgain
//
//  Created by mac on 14-4-1.
//
//

#import "SinaInterface_Objc.h"
#import "GameShare_Global.h"
#import "GameShare_Data.h"
#import "Constant.h"
#import "GameShare_Msg.h"
#import "PlayerInfoManager.h"
#import "FriendManager.h"
#include "SBJson.h"
static SinaInterface_Objc *instance = nil;
@implementation SinaInterface_Objc


+ (id)shareInstance
{
    if (instance == nil)
    {
        instance = [[SinaInterface_Objc alloc] init];
        
    }
    return instance;
}


- (id)init
{
    self = [super init];
    if (self)
    {
        [WeiboSDK enableDebugMode:YES];
        [WeiboSDK registerApp:kSinaAppKey];
    }
    
    return self;
}

- (void)login
{
    WBAuthorizeRequest *request = [WBAuthorizeRequest request];
    request.redirectURI = kSinaAppRedirectURI;
//    request.scope = @"invitation_write,all";
    [WeiboSDK sendRequest:request];
}
-(void)inviteUser:(const char *)uid
{
    NSString *jsonData = @"{\"text\": \"新浪新闻是新浪网官方出品的新闻客户端，用户可以第一时间获取新浪网提供的高品质的全球资讯新闻，随时随地享受专业的资讯服务，加入一起吧\",\"url\": \"http://app.sina.com.cn/appdetail.php?appID=84475\",\"invite_logo\":\"http://sinastorage.com/appimage/iconapk/1b/75/76a9bb371f7848d2a7270b1c6fcf751b.png\"}";
    
    NSString* sinaId = [NSString stringWithUTF8String:GameShare_Data::shareData()->getSinaID().c_str()];
    
    NSString* sinaToken = [NSString stringWithUTF8String:GameShare_Data::shareData()->getSinaToken().c_str()];
    
//    [WeiboSDK inviteFriend:jsonData withUid:[NSString stringWithUTF8String:uid] withToken:sinaToken delegate:self];
        [WBHttpRequest requestWithAccessToken:sinaToken url:@"https://m.api.weibo.com/2/messages/invite.json" httpMethod:@"POST" params:[[NSDictionary alloc] initWithObjectsAndKeys:[NSString stringWithUTF8String:uid], @"uid",@"新浪新闻是新浪网官方出品的新闻客户端，用户可以第一时间获取新浪网提供的高品质的全球资讯新闻，随时随地享受专业的资讯服务，加入一起吧", @"text", nil] delegate:self];
}
- (void)getFriend
{
    NSString* sinaId = [NSString stringWithUTF8String:GameShare_Data::shareData()->getSinaID().c_str()];
    
    NSString* sinaToken = [NSString stringWithUTF8String:GameShare_Data::shareData()->getSinaToken().c_str()];
    [WBHttpRequest requestWithAccessToken:sinaToken url:@"https://api.weibo.com/2/friendships/friends/bilateral.json" httpMethod:@"GET" params:[[NSDictionary alloc] initWithObjectsAndKeys:sinaId, @"uid", nil] delegate:self];
    NSLog(@"getFriend");
}
-(void)getUserInfo
{
    NSString* sinaId = [NSString stringWithUTF8String:GameShare_Data::shareData()->getSinaID().c_str()];
    
    NSString* sinaToken = [NSString stringWithUTF8String:GameShare_Data::shareData()->getSinaToken().c_str()];
    [WBHttpRequest requestWithAccessToken:sinaToken url:@"https://api.weibo.com/2/users/show.json" httpMethod:@"GET" params:[[NSDictionary alloc] initWithObjectsAndKeys:sinaId, @"uid", nil] delegate:self];
}
-(void)request:(WBHttpRequest *)request didReceiveResponse:(NSURLResponse *)response
{ 
}
-(void)request:(WBHttpRequest *)request didFailWithError:(NSError *)error
{
    NSLog(@"error");
}
-(void)request:(WBHttpRequest *)request didFinishLoadingWithResult:(NSString *)result
{
    
    if ([request.url hasSuffix:@"2/friendships/friends/bilateral.json"]) {
        
        VEC_GAMERANK& friendList = CFriendManager::sharedInstance().getFriend();
        friendList.clear();
        SBJsonParser* jsonParser = [[SBJsonParser alloc] init];
        NSDictionary *dic = [jsonParser objectWithString:result];
        NSArray* array = [dic objectForKey:@"users"];
        for (int i=0; i<array.count; i++) {
            sGameRank data;
            NSDictionary* userDic = [array objectAtIndex:i];
            data.avatarUrl = [[userDic objectForKey:@"profile_image_url"] UTF8String];
            data.name = [[userDic objectForKey:@"name"] UTF8String];
            data.appid = [[userDic objectForKey:@"idstr"] UTF8String];
            friendList.push_back(data);
        }
        NSLog(@"RequestSetFriend");
        CFriendManager::sharedInstance().RequestSetFriend(1, [result UTF8String]);
       // cocos2d::CCNotificationCenter::sharedNotificationCenter()->postNotification(kSinaGetFriendSuccess, NULL);
    }
    if ([request.url hasSuffix:@"2/users/show.json"]) {
        SBJsonParser* jsonParser = [[SBJsonParser alloc] init];
        NSDictionary *dic = [jsonParser objectWithString:result];
        NSString* name = [dic objectForKey:@"name"];
        NSString* url = [dic objectForKey:@"avatar_large"];
        GameShare_Data::shareData()->setUserUrl([url UTF8String]);
        GameShare_Data::shareData()->setUserName([name UTF8String]);
        
        cocos2d::CCNotificationCenter::sharedNotificationCenter()->postNotification(kSinaLoginSuccess, NULL);
    }
    
}
- (void)didReceiveWeiboResponse:(WBBaseResponse *)response
{
    if ([response isKindOfClass:WBSendMessageToWeiboResponse.class])
    {

    }
    else if ([response isKindOfClass:WBAuthorizeResponse.class])
    {
        if (response.statusCode == WeiboSDKResponseStatusCodeSuccess) {
//            NSString *message = [NSString stringWithFormat:@"响应状态: %d\nresponse.userId: %@\nresponse.accessToken: %@\n响应UserInfo数据: %@\n原请求UserInfo数据: %@",
//                                 response.statusCode,
//                                 [(WBAuthorizeResponse *)response userID],
//                                 [(WBAuthorizeResponse *)response accessToken],
//                                 response.userInfo,
//                                 response.requestUserInfo];
//            NSLog(message);
            CPlayerInfoMan::sharedInstance().getPlayerInfo().strSina = [[(WBAuthorizeResponse *)response userID] UTF8String];
            GameShare_Data::shareData()->setSinaId([[(WBAuthorizeResponse *)response userID] UTF8String], [[(WBAuthorizeResponse *)response accessToken] UTF8String], [[(WBAuthorizeResponse *)response expirationDate] timeIntervalSince1970] );
            
            [self getUserInfo];

        }
       
    }
}
- (void)didReceiveWeiboRequest:(WBBaseRequest *)request
{
    if ([request isKindOfClass:WBProvideMessageForWeiboRequest.class])
    {
    }
}
@end