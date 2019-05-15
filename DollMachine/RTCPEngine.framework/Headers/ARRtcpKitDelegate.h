//
//  ARRtcpKitDelegate.h
//  RTCPEngine
//
//  Created by zjq on 2019/1/16.
//  Copyright © 2019 MaoZongWu. All rights reserved.
//

#ifndef ARRtcpKitDelegate_h
#define ARRtcpKitDelegate_h

#import <UIKit/UIKit.h>
#import "ARRtcpEnum.h"

@protocol ARRtcpKitDelegate <NSObject>

@optional
/**
 发布媒体成功回调
 
 @param pubId RTCP服务生成的通道Id (用于标识通道，每次发布随机生成)
 @param liveInfo 直播信息
 */
- (void)onRTCPublishOK:(NSString *)pubId liveInfo:(NSString *)liveInfo;

/**
 发布媒体失败回调
 
 @param code 状态码
 @param reason 错误原因，RTC错误或者token错误（错误值自己平台定义）
 */
- (void)onRTCPublishFailed:(ARRtcpCode)code reason:(NSString *)reason;

/**
 订阅通道成功的回调
 
 @param pubId RTCP服务生成的通道Id (用于标识通道，每次发布随机生成)
 */
- (void)onRTCSubscribeOK:(NSString *)pubId;

/**
 订阅通道失败的回调
 
 @param pubId RTCP服务生成的通道Id (用于标识通道，每次发布随机生成)
 @param code 状态码
 @param reason 错误原因，RTC错误或者token错误（错误值自己平台定义）
 */
- (void)onRTCSubscribeFailed:(NSString *)pubId code:(ARRtcpCode)code reason:(NSString *)reason;

/**
 订阅后音视频即将显示的回调
 
 @param pubId RTCP服务生成的通道Id (用于标识通道，每次发布随机生成)
 */
- (void)onRTCOpenRemoteVideoRender:(NSString *)pubId;

/**
 订阅的音视频离开的回调
 
 @param pubId RTCP服务生成的通道Id (用于标识通道，每次发布随机生成)
 */
- (void)onRTCCloseRemoteVideoRender:(NSString *)pubId;

/**
 订阅音频后成功的回调
 
 @param pubId RTCP服务生成的通道Id (用于标识通道，每次发布随机生成)
 */
- (void)onRTCOpenRemoteAudioTrack:(NSString *)pubId;

/**
 订阅的音频离开的回调
 
 @param pubId RTCP服务生成的通道Id (用于标识通道，每次发布随机生成)
 */
- (void)onRTCCloseRemoteAudioTrack:(NSString *)pubId;

#pragma mark - 视频第一帧的回调

/**
 本地视频第一帧
 
 @param size 视频窗口大小
 */
- (void)onRTCFirstLocalVideoFrame:(CGSize)size;

/**
 远程视频第一帧
 
 @param size 视频窗口大小
 @param pubId RTCP服务生成的通道Id (用于标识通道，每次发布随机生成)
 */
- (void)onRTCFirstRemoteVideoFrame:(CGSize)size pubId:(NSString *)pubId;

#pragma mark - 视频大小变化回调

/**
 本地窗口大小的回调
 
 @param size 视频窗口大小
 */
- (void)onRTCLocalVideoViewChanged:(CGSize)size;

/**
 远程窗口大小的回调
 
 @param size 视频窗口大小
 @param pubId RTCP服务生成的通道Id (用于标识通道，每次发布随机生成)
 */
- (void)onRTCRemoteVideoViewChanged:(CGSize)size pubId:(NSString *)pubId;

#pragma mark - 音频检测和网络状态
/**
 其他发布者的音频检测回调
 
 @param pubId RTCP服务生成的通道Id (用于标识通道，每次发布随机生成)
 @param level 音频大小（0~100）
 @param time 音频检测在nTime毫秒内不会再回调该方法（单位：毫秒）
 说明：与会者关闭音频后（setLocalAudioEnable为NO）,该回调将不再回调。对方关闭音频检测后（setAudioActiveCheck为NO）,该回调也将不再回调。
 */
- (void)onRTCRemoteAudioActive:(NSString *)pubId audioLevel:(int)level showTime:(int)time;

/**
 本地音频检测回调
 
 @param level 音频大小（0~100）
 @param time 音频检测在nTime毫秒内不会再回调该方法（单位：毫秒）
 说明：本地关闭音频后（setLocalAudioEnable为NO）,该回调将不再回调。本地关闭音频检测后（setAudioActiveCheck为NO）,该回调也将不再回调。
 */
- (void)onRTCLocalAudioActive:(int)level showTime:(int)time;

/**
 其他发布者的网络质量回调
 
 @param pubId RTCP服务生成的通道Id (用于标识通道，每次发布随机生成)
 @param netSpeed 网络上行
 @param packetLost 丢包率
 @param netQuality 网络质量
 */
- (void)onRTCRemoteNetworkStatus:(NSString *)pubId netSpeed:(int)netSpeed packetLost:(int)packetLost netQuality:(ARNetQuality)netQuality;

/**
 本地网络质量回调
 
 @param netSpeed 网络上行
 @param packetLost 丢包率
 @param netQuality 网络质量
 */
- (void)onRTCLocalNetworkStatus:(int)netSpeed packetLost:(int)packetLost netQuality:(ARNetQuality)netQuality;

@end

#endif /* ARRtcpKitDelegate_h */


