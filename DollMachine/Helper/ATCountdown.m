//
//  ATCountdown.m
//  MeditationVideo
//
//  Created by 1 on 2017/4/5.
//  Copyright © 2017年 jh. All rights reserved.
//倒计时按钮

#import "ATCountdown.h"

@interface ATCountdown ()

@property (nonatomic, strong) dispatch_source_t timer;

@end

@implementation ATCountdown

- (instancetype)init
{
    self = [super init];
    if (self) {
        
        [self setup];
    }
    return self;
}

- (instancetype)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        
        [self setup];
    }
    return self;
}

- (void)setup {
    [self setTitle:@"不想抓了" forState:UIControlStateNormal];
    self.titleLabel.font = [UIFont systemFontOfSize:10];
    self.backgroundColor = [UIColor clearColor];
}

- (void)timeFailBeginFrom:(NSInteger)timeCount andDescribe:(BOOL)isDoll{
    dispatch_queue_t queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
    self.timer = dispatch_source_create(DISPATCH_SOURCE_TYPE_TIMER, 0, 0, queue);
    dispatch_source_set_timer(self.timer, dispatch_walltime(NULL, 0), 1.0 * NSEC_PER_SEC, 0); // 每秒执行一次
    
    NSTimeInterval seconds = timeCount;
    NSDate *endTime = [NSDate dateWithTimeIntervalSinceNow:seconds]; // 最后期限
    
    dispatch_source_set_event_handler(_timer, ^{
        int interval = [endTime timeIntervalSinceNow];
        if (interval > 0) { // 更新倒计时
            NSString *timeStr = [NSString stringWithFormat:@"不想抓了(%ds)", interval];
            isDoll ? nil : (timeStr = [NSString stringWithFormat:@"抓取\n(%ds)", interval]);
            dispatch_async(dispatch_get_main_queue(), ^{
                if (!isDoll) {
                    self.titleLabel.numberOfLines = 2;
                }
                self.titleLabel.text = timeStr;
                [self setTitle:timeStr forState:UIControlStateNormal];
            });
        } else { // 倒计时结束，关闭
            dispatch_source_cancel(_timer);
            dispatch_async(dispatch_get_main_queue(), ^{
                isDoll?([self setTitle:@"不想抓了" forState:UIControlStateNormal]):([self setTitle:@"抓取" forState:UIControlStateNormal]);
                if (self.block) {
                    self.block();
                }
            });
        }
    });
    dispatch_resume(self.timer);
}

- (void)timeMeterEnd{
    if (self.timer) {
        dispatch_source_cancel(self.timer);
        self.timer = nil;
    }
}

@end
