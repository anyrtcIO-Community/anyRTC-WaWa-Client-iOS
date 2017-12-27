//
//  ATDollView.h
//  DollMachine
//
//  Created by jh on 2017/11/29.
//  Copyright © 2017年 jh. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef NS_ENUM(NSInteger, DollStyle) {
    Doll_Read_Style = 0,//准备抓
    Doll_Sucess_Style = 1,//成功
    Doll_Fail_Style = 2,//失败
    Doll_Control_Style = 3 //操作
};

typedef void(^DollResultBlock)(NSInteger tag);

@interface ATDollView : UIView

//成功、失败
@property (weak, nonatomic) IBOutlet UIImageView *resultImageView;
//左
@property (weak, nonatomic) IBOutlet ATCountdown *leftButton;
//右
@property (weak, nonatomic) IBOutlet UIButton *rightButton;

@property (nonatomic, copy) DollResultBlock resultBlock;

@property (nonatomic, assign) DollStyle dollStyle;

- (void)changeStyle:(DollStyle)style;

@end
