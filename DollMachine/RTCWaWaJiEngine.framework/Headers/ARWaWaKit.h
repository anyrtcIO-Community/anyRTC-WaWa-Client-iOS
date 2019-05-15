//
//  ARWaWaKit.h
//  RTCWaWaJiEngine
//
//  Created by 余生丶 on 2019/2/14.
//  Copyright © 2019 jh. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ARWawaKitDelegate.h"
#import "ARWaWaJiEnum.h"

NS_ASSUME_NONNULL_BEGIN

@interface ARWaWaKit : NSObject

+ (instancetype)sharedInstance;

@property (weak, nonatomic) id <ARWawaKitDelegate> delegate;

/**
 配置开发者信息
 
 @param developerId 开发者Id
 @param appId  appId
 @param key    key
 @param token  token
 说明：该方法为配置开发者信息，上述参数均可在https://www.anyrtc.io/manage创建应用后。
 */
- (void)initEngine:(NSString *)developerId appId:(NSString *)appId key:(NSString *)key toke:(NSString *)token;

/**
 获取房间列表
 
 @param complete 房间列表回调
 */
- (void)getRoomListWithBlock:(void(^)(NSDictionary *listDic))complete;

/**
 加入房间
 
 @param anyRTCId 房间id
 @param userId 用户id
 @param userName 房间姓名
 @param userIcon 用户头像
 */
- (void)joinRoom:(NSString *)anyRTCId userId:(NSString *)userId userName:(NSString *)userName userIcon:(NSString *)userIcon;

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
- (void)sendControlCmd:(ARWaWaJi_CMD_State)cmdState;

/**
 离开房间
 */
- (void)leaveRoom;


@end

NS_ASSUME_NONNULL_END
