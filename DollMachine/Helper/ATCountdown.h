//
//  ATCountdown.h
//  MeditationVideo
//
//  Created by 1 on 2017/4/5.
//  Copyright © 2017年 jh. All rights reserved.
// 倒计时按钮

#import <UIKit/UIKit.h>

typedef void(^DestructionBlock)(void);

@interface ATCountdown : UIButton

@property (nonatomic, copy)DestructionBlock block;

// 由于有些时间需求不同，特意露出方法，倒计时时间次数
- (void)timeFailBeginFrom:(NSInteger)timeCount andDescribe:(BOOL)isDoll;

- (void)timeMeterEnd;

@end
