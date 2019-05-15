//
//  ARWawaKitDelegate.h
//  RTCWaWaJiEngine
//
//  Created by 余生丶 on 2019/2/14.
//  Copyright © 2019 jh. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ARWaWaJiEnum.h"

@protocol ARWawaKitDelegate <NSObject>

@optional

/**
 连接服务成功
 */
- (void)onConnectServerSuccess;

/**
 与服务断开连接
 */
- (void)onDisconnect;

/**
 与服务重连中
 */
- (void)onReconnect;

/**
 初始化anyRTC成功
 */
- (void)onInitAnyRTCSuccess;

/**
 初始化anyRTC失败
 */
- (void)onInitAnyRTCFailed;

/**
 进入房间回调(抓娃娃机者)
 
 @param rtcpId 通道Id
 @param roomMember 房间总人数
 @param code 状态码
 */
- (void)onJoinRoom:(NSString *)rtcpId roomMember:(int)roomMember code:(int)code;

/**
 离开房间回调(抓娃娃机者)
 
 @param code 状态码
 */
- (void)onLeaveRoom:(int)code;

/**
 娃娃机连接断开回调

 */
- (void)onWawajiDisconnect;

/**
 娃娃机断开重连回调
 
 @param rtcpId 通道Id
 */
- (void)onWawajiReconnect:(NSString *)rtcpId;

/**
 预约结果回调
 
 @param bookMember 预约总人数
 @param code 状态码
 */
- (void)onBookResult:(int)bookMember code:(int)code;

/**
 控制命令回调
 
 @param cmd 命令
 @param code 状态码
 */
- (void)onControlCmd:(ARWaWaJi_CMD_State)cmd code:(int)code;


/**
 抓娃娃结果回调
 
 @param code 1成功，0失败
 */
- (void)onGrabResult:(int)code;


/**
 房间人数变化回调
 
 @param roomMember 房间总人数
 说明：当有人进入或者离开房间会回调该方法。
 */
- (void)onRoomMemberUpdate:(int)roomMember;


/**
 排队人数变化回调
 
 @param bookMember 预约人数
 */
- (void)onBookMemberUpdate:(int)bookMember;


/**
 排队抓娃娃准备回调
 
 */
- (void)onReadyPlay;


/**
 准备超时回调
 
 说明：抓娃娃急者没有点击开始也没有点击取消，会回调该接口。
 */
- (void)onReadyPlayTimeout;


/**
 抓娃娃超时回调
 
 */
- (void)onPlayTimeout;

@end
