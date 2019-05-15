//
//  ARRtcpKit.h
//  RTCPEngine
//
//  Created by zjq on 2019/1/16.
//  Copyright © 2019 MaoZongWu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "ARRtcpKitDelegate.h"
#import "ARRtcpOption.h"

NS_ASSUME_NONNULL_BEGIN

@interface ARRtcpKit : NSObject

/**
 实例化RTCPKit对象
 
 @param delegate RTCP相关回调代理
 @param userId 用户自己平台的Id，确保唯一，不能为空
 @param userData 用户自定义信息（限制512字节）
 @return 实时直播对象。
 */
- (instancetype)initWithDelegate:(id<ARRtcpKitDelegate>)delegate userId:(NSString *)userId userData:(NSString *)userData;

#pragma mark Common function

/**
 设置本地视频采集窗口
 
 @param render 视频显示对象
 @param option 配置信息
 */
- (void)setLocalVideoCapturer:(UIView *)render option:(ARRtcpOption *)option;

/**
 设置本地显示模式
 
 @param videoRenderMode 显示模式，默认ARVideoRenderScaleAspectFill，等比例填充视图模式
 */
- (void)updateLocalVideoRenderModel:(ARVideoRenderMode)videoRenderMode;

/**
 设置本地音频是否传输
 
 @param enable YES传输音频，NO不传输音频，默认传输
 */
- (void)setLocalAudioEnable:(BOOL)enable;

/**
 设置本地视频是否传输
 
 @param enable YES传输视频，NO为不传输视频，默认视频传输
 */
- (void)setLocalVideoEnable:(BOOL)enable;

/**
 获取本地音频传输是否打开
 
 @return 音频传输与否
 */
- (BOOL)localAudioEnabled;

/**
 获取本地视频传输是否打开
 
 @return 视频传输与否
 */
- (BOOL)localVideoEnabled;
/**
 设置扬声器开关
 
 @param on YES打开扬声器，NO关闭扬声器，默认打开扬声器
 */
- (void)setSpeakerOn:(BOOL)on;

/**
 切换前后摄像头
 */
- (void)switchCamera;

/**
 设置本地前置摄像头镜像是否打开
 
 @param enable YES为打开，NO为关闭
 @return 本地前置摄像头镜像是否成功打开
 */
- (BOOL)setFontCameraMirrorEnable:(BOOL)enable;

/**
 前置摄像头是否镜像
 
 @return 是否镜像，默认打开。
 */
- (BOOL)fontCameraMirror;

/**
 禁止接收某人视频
 
 @param mute YES禁止，NO接收
 @param pubId RTCP服务生成的通道Id (用于标识通道，每次发布随机生成)
 @return 操作是否成功
 */
- (int)muteRemoteVideoStream:(BOOL)mute pubId:(NSString *)pubId;

/**
 禁止接收某人音频
 
 @param mute YES禁止，NO接收
 @param pubId RTCP服务生成的通道Id (用于标识通道，每次发布随机生成)
 @return 操作是否成功
 */
- (int)muteRemoteAudioStream:(BOOL)mute pubId:(NSString *)pubId;

#pragma mark RTCP function for media

/**
 发布媒体
 
 @param token 令牌:客户端向自己服务申请获得，参考企业级安全指南
 @param type 0为发布音视频，1为只发布音频
 */
- (void)publishByToken:(NSString*_Nullable)token mediaType:(ARMediaType)type;

/**
 取消发布媒体
 
 说明：取消发布媒体之后，下次再发布的时候，还需要在调用setLocalVideoCapturer
 */
- (void)unPublish;

/**
 订阅视频
 
 @param token 令牌:客户端向自己服务申请获得，参考企业级安全指南
 @param pubId RTCP服务生成的通道Id (用于标识通道，每次发布随机生成)
 */
- (void)subscribeByToken:(NSString*_Nullable)token pubId:(NSString *)pubId;

/**
 取消订阅 媒体流
 
 @param pubId RTCP服务生成的通道Id (用于标识通道，每次发布随机生成)
 */
- (void)unSubscribe:(NSString *)pubId;

/**
 设置显示其他人的视频窗口
 
 @param render 对方视频的窗口，本地设置
 @param pubId RTCP服务生成的通道Id (用于标识通道，每次发布随机生成)
 说明：该方法用于订阅成功通后，视频即将显示的回调中(onRTCOpenVideoRender)使用。
 */
- (void)setRemoteVideoRender:(UIView *)render pubId:(NSString *)pubId;

/**
 设置其他人显示模式
 
 @param videoRenderMode 显示模式，默认ARVideoRenderScaleAspectFill，等比例填充视图模式
 */
- (void)updateRTCVideoRenderModel:(ARVideoRenderMode)videoRenderMode;

/**
 关闭离开
 */
- (void)close;


#pragma mark - 音视频流信息监测

/**
 设置音频检测
 
 @param on 是否开启音频检测，默认打开
 */
- (void)setAudioActiveCheck:(BOOL)on;

/**
 获取音频检测是否打开
 */
- (BOOL)audioActiveCheck;

/**
 设置视频网络状态是否打开
 
 @param enable YES打开，NO关闭，默认关闭
 */
- (void)setNetworkStatus:(BOOL)enable;

/**
 获取当前视频网络状态是否打开
 
 @return 获取网络视频状态
 */
- (BOOL)networkStatusEnabled;

@end

NS_ASSUME_NONNULL_END

