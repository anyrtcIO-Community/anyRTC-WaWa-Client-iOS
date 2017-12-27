//
//  ATListModel.h
//  DollMachine
//
//  Created by jh on 2017/12/6.
//  Copyright © 2017年 jh. All rights reserved.
//

#import <Foundation/Foundation.h>

@class Roomlist;
@interface ATListModel : NSObject


@property (nonatomic, strong) NSArray<Roomlist *> *roomlist;


@end
@interface Roomlist : NSObject

@property (nonatomic, copy) NSString *room_url;

@property (nonatomic, copy) NSString *RtcpUrl;//rtcpId

@property (nonatomic, copy) NSString *H5LiveUrl;//h5

@property (nonatomic, assign) NSInteger roomid;

@property (nonatomic, copy) NSString *room_name;

@property (nonatomic, copy) NSString *room_anyrtcid;

@property (nonatomic, copy) NSString *room_create_at;

@property (nonatomic, copy) NSString *room_leave_time;

@property (nonatomic, copy) NSString *room_userid;

@property (nonatomic, copy) NSString *room_username;

@property (nonatomic, copy) NSString *room_usericon;

@property (nonatomic, copy) NSString *room_appid;

@property (nonatomic, assign) NSInteger room_member;

@property (nonatomic, assign) NSInteger room_state;//0正常 1维护中

@end

