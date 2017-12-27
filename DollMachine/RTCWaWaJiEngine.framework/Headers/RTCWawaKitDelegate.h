//
//  RTCWawaKitDelegate.h
//  RTCWaWaJiEngine
//
//  Created by jh on 2017/12/27.
//  Copyright © 2017年 jh. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RTCCommon.h"

@protocol RTCWawaKitDelegate <NSObject>

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
 @param code 状态码
 @param rtcpId 通道Id
 @param roomMember 房间总人数
 */
- (void)onJoinRoom:(NSString*)rtcpId andRoomMember:(int)roomMember withCode:(int)code;

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
- (void)onWawajiReconnect:(NSString*)rtcpId;

/**
 预约结果回调
 
 @param bookMember 预约总人数
 @param code code值
 */
- (void)onBookResult:(int)bookMember withCode:(int)code;

/**
 控制命令回调
 
 @param eCmd 命令
 @param code 状态码
 */
- (void)onControlCmd:(AnyRTC_CMD_State)eCmd withCode:(int)code;


/**
 抓娃娃结果回调
 @param code 1成功 0失败
 */
- (void)onGrabResult:(int)code;


/**
 房间人数变化回调
 @param roomMember 房间总人数
 说明：当有人进入或者离开房间会回调该方法
 */
- (void)onRoomMemberUpdate:(int)roomMember;


/**
 排队人数变化回调
 @param bookMember 房间总人数
 说明：预约总人数变化回调
 */
- (void)onBookMemberUpdate:(int)bookMember;


/**
 排队抓娃娃准备回调
 
 */
- (void)onReadyPlay;


/**
 准备超时回调
 
 说明：该你抓了，但是没有点击开始也没有点击取消，会回调该接口
 */
- (void)onReadyPlayTimeout;


/**
 抓娃娃超时回调
 
 */
- (void)onPlayTimeout;

@end
