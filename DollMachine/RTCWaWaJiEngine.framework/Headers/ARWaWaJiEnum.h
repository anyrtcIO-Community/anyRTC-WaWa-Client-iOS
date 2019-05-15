//
//  ARWaWaJiEnum.h
//  RTCWaWaJiEngine
//
//  Created by 余生丶 on 2019/2/14.
//  Copyright © 2019 jh. All rights reserved.
//

#ifndef ARWaWaJiEnum_h
#define ARWaWaJiEnum_h

typedef NS_ENUM(NSInteger, ARWaWaJi_CMD_State) {
    ARWaWaJi_CMD_FORWARD = 0,        //向上
    ARWaWaJi_CMD_BACKWARD  = 1,      //向下
    ARWaWaJi_CMD_LEFT = 2,           //向左
    ARWaWaJi_CMD_RIGHT = 3,          //向右
    ARWaWaJi_CMD_GRAB = 4,           //抓取
    ARWaWaJi_CMD_SWITCH_CAMERA = 5,  //切换摄像头
    ARWaWaJi_CMD_UNKNOWN = 6         //未知操作
};

#endif /* ARWaWaJiEnum_h */
