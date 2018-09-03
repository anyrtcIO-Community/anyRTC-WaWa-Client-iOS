//
//  RTCPOption.h
//  RTCPEngine
//
//  Created by derek on 2017/10/30.
//  Copyright © 2017年 MaoZongWu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RTCCommon.h"

@interface RTCPOption : NSObject

/**
 使用默认配置生成一个 RTCPOption 对象

 @return 生成的 RTCPOption 对象
 */
+ (nonnull RTCPOption *)defaultOption;

/**
 设置视频质量
 AnyRTCVideoQuality_Low1 = 0,      // 320*240 - 128kbps
 AnyRTCVideoQuality_Low2,          // 352*288 - 256kbps
 AnyRTCVideoQuality_Low3,          // 352*288 - 384kbps
 AnyRTCVideoQuality_Medium1,       // 640*480 - 384kbps
 AnyRTCVideoQuality_Medium2,       // 640*480 - 512kbps
 AnyRTCVideoQuality_Medium3,       // 640*480 - 768kbps
 AnyRTCVideoQuality_Height1,       // 960*540 - 768kbps
 AnyRTCVideoQuality_Height2,       // 1280*720 - 1024kbps
 AnyRTCVideoQuality_Height3,       // 1920*1080 - 2048kbps
 
 说明:　默认：AnyRTCVideoQuality_Medium2
 */
@property (nonatomic, assign) AnyRTCVideoQualityModel videoMode;

/**
 视频方向
 说明：默认为：RTC_SCRN_Portrait
 */
@property (nonatomic, assign) RTCScreenOrientation orientation;
/**
 是否是前置摄像头
 说明：默认前置摄像头
 */
@property (nonatomic, assign) BOOL isFont;

@end
