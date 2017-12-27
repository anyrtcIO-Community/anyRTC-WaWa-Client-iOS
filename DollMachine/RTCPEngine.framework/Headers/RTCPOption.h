//
//  RTCPOption.h
//  RTCPEngine
//
//  Created by derek on 2017/10/30.
//  Copyright © 2017年 MaoZongWu. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum RTCPVideosMode
{
    RTCP_Videos_HD = 0,    //* 1280*720 - 1024kbps
    RTCP_Videos_QHD,       //* 960*540 - 768kbps
    RTCP_Videos_SD,        //* 640*480 - 512kbps
    RTCP_Videos_Low        //* 352*288 - 384kbps
}RTCPVideosMode;


typedef enum {
    RTCP_SCRN_Portrait = 0,
    RTCP_SCRN_LandscapeRight,
    RTCP_SCRN_PortraitUpsideDown,
    RTCP_SCRN_LandscapeLeft,
    RTCP_SCRN_Auto
}RTCPScreenOrientation;


@interface RTCPOption : NSObject

/**
 使用默认配置生成一个 RTCPOption 对象

 @return 生成的 RTCPOption 对象
 */
+ (nonnull RTCPOption *)defaultOption;

/**
 设置视频分辨率
 说明：默认为：RTCP_Videos_SD
 */
@property (nonatomic, assign) RTCPVideosMode videoMode;

/**
 视频方向
 说明：默认为：RTCP_SCRN_Portrait
 */
@property (nonatomic, assign) RTCPScreenOrientation orientation;
/**
 是否是前置摄像头
 说明：默认前置摄像头
 */
@property (nonatomic, assign) BOOL isFont;

@end
