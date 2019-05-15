//
//  ARRtcpEnum.h
//  RTCPEngine
//
//  Created by zjq on 2019/1/16.
//  Copyright © 2019 MaoZongWu. All rights reserved.
//

#ifndef ARRtcpEnum_h
#define ARRtcpEnum_h
#import "ARCommonEnum.h"

typedef NS_ENUM(NSInteger,ARRtcpCode) {
    ARRtcp_OK = 0,                     // 正常
    ARRtcp_UNKNOW,                     // 未知错误
    ARRtcp_EXCEPTION,                  // SDK调用异常
    ARRtcp_EXP_UNINIT,                 // SDK未初始化
    ARRtcp_EXP_PARAMS_INVALIDE,        // 参数非法
    ARRtcp_EXP_NO_NETWORK,             // 没有网络
    ARRtcp_EXP_NOT_FOUND_CAMERA,       // 没有找到摄像头设备
    ARRtcp_EXP_NO_CAMERA_PERMISSION,   // 没有打开摄像头权限:
    ARRtcp_EXP_NO_AUDIO_PERMISSION,    // 没有音频录音权限
    ARRtcp_EXP_NOT_SUPPOAR_WEBARC,     // 浏览器不支持原生的webARc
    
    ARRtcp_NET_ERR = 100,              // 网络错误
    ARRtcp_NET_DISSCONNECT = 101,      // 网络断开
    ARRtcp_LIVE_ERR = 102,             // 直播出错
    ARRtcp_EXP_ERR = 103,              // 异常错误
    ARRtcp_EXP_UNAUTHORIZED = 104,     // 服务未授权
    
    ARRtcp_BAD_REQ  = 201,             // 服务不支持的错误请求
    ARRtcp_AUTH_FAIL = 202,            // 认证失败
    ARRtcp_NO_USER= 203,               // 此开发者信息不存在
    ARRtcp_SVR_ERR = 204,              // 服务器内部错误
    ARRtcp_SQL_ERR = 205,              // 服务器内部数据库错误
    ARRtcp_ARREARS = 206,              // 账号欠费
    ARRtcp_LOCKED = 207,               // 账号被锁定
    ARRtcp_SERVER_NOT_OPEN = 208,      // 服务未开通
    ARRtcp_ALLOC_NO_RES = 209,         // 没有服务资源
    ARRtcp_SERVER_NO_SURPPOAR = 210,   // 不支持的服务
    ARRtcp_FORCE_EXIT = 211,           // 强制离开
    ARRtcp_NOT_START = 800,            // 会议未开始
};

typedef NS_ENUM(NSInteger,ARMediaType){
    ARMediaVideoType = 0,      // 音视频
    ARMediaAudioType = 1       // 音频
};

#endif /* ARRtcpEnum_h */
