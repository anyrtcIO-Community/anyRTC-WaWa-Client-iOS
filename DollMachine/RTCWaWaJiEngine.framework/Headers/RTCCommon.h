//
//  RTCCommon.h
//  RTCWaWaJiEngine
//
//  Created by jh on 2017/12/23.
//  Copyright © 2017年 jh. All rights reserved.
//

#ifndef RTCCommon_h
#define RTCCommon_h

typedef NS_ENUM(NSInteger, AnyRTC_CMD_State) {
    CMD_FORWARD = 0,        //向上
    CMD_BACKWARD  = 1,      //向下
    CMD_LEFT = 2,           //向左
    CMD_RIGHT = 3,          //向右
    CMD_GRAB = 4,           //抓取
    CMD_SWITCH_CAMERA = 5,  //切换摄像头
    CMD_UNKNOWN = 6         //未知操作
};

#endif /* RTCCommon_h */
