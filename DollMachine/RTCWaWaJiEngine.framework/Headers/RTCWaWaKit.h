//
//  RTCWaWaKit.h
//  RTCWaWaJiEngine
//
//  Created by jh on 2017/12/23.
//  Copyright © 2017年 jh. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RTCWawaKitDelegate.h"
#import "RTCCommon.h"

@interface RTCWaWaKit : NSObject

+ (instancetype)sharedInstance;

@property (weak, nonatomic) id <RTCWawaKitDelegate> delegate;

/**
 配置开发者信息
 @param strDeveloperId 开发者Id；
 @param strAppId     AppId；
 @param strAppKey    AppKey；
 @param strAppToken  AppToken；
 说明：该方法为配置开发者信息，上述参数均可在https://www.anyrtc.io/ manage创建应用后。
 */
- (void)initEngineWithAnyRTCInfo:(NSString*)strDeveloperId andAppId:(NSString*)strAppId andKey:(NSString*)strAppKey andToke:(NSString*)strAppToken;

/**
 获取房间列表
 @param complete 房间列表回调;
 */
- (void)getRoomListWithBlock:(void(^)(NSDictionary *listDic))complete;

/**
 加入房间
 @param anyRtcId 房间id;
 @param userId 用户id;
 @param userName 房间姓名;
 @param userIcon 用户头像;
 */
- (void)joinRoom:(NSString *)anyRtcId withUserId:(NSString *)userId UserName:(NSString *)userName withUserIcon:(NSString *)userIcon;

/**
 预约
 */
- (void)makeBook;

/**
 取消预约
 */
- (void)cancelBook;

/**
 开始游戏
 */
- (void)startPlay;

/**
 取消游戏
 */
- (void)cancelPlay;

/**
 控制命令
 @param cmdState 指令
 */
- (void)sendControlCmd:(AnyRTC_CMD_State)cmdState;

/**
 离开房间
 */
- (void)leaveRoom;

@end


