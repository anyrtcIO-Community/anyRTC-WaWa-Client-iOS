//
//  ATDollView.m
//  DollMachine
//
//  Created by jh on 2017/11/29.
//  Copyright © 2017年 jh. All rights reserved.
//

#import "ATDollView.h"

@implementation ATDollView

- (void)awakeFromNib{
    [super awakeFromNib];
    self.leftButton.layer.borderColor = [UIColor whiteColor].CGColor;
    self.rightButton.layer.borderColor = [UIColor whiteColor].CGColor;
}

- (void)changeStyle:(DollStyle)style{
    self.dollStyle = style;
    self.leftButton.backgroundColor = [ATCommon getColor:@"#cccccc"];
    switch (style) {
        case Doll_Read_Style:
        {
            [self.leftButton setTitle:@"不想抓了" forState:UIControlStateNormal];
            [self.rightButton setTitle:@"开始游戏" forState:UIControlStateNormal];
            self.resultImageView.image = [UIImage imageNamed:@"img_gamestart"];
            [self.leftButton timeFailBeginFrom:10 andDescribe:YES];
        }
            break;
        case Doll_Sucess_Style:
            self.leftButton.backgroundColor = [ATCommon getColor:@"#3bc2fe"];
            [self.leftButton setTitle:@"休息一下" forState:UIControlStateNormal];
            [self.rightButton setTitle:@"再接再厉" forState:UIControlStateNormal];
            self.resultImageView.image = [UIImage imageNamed:@"img-tailihaile"];
            break;
        case Doll_Fail_Style:
            [self.leftButton setTitle:@"无力再战" forState:UIControlStateNormal];
            [self.rightButton setTitle:@"再来一局" forState:UIControlStateNormal];
            self.resultImageView.image = [UIImage imageNamed:@"img_lose"];
            break;
        default:
            break;
    }
}

- (IBAction)doSomethingClick:(UIButton *)sender {
    [self.leftButton timeMeterEnd];
    NSInteger index = 0;
    switch (self.dollStyle) {
        case Doll_Read_Style:
            (sender.tag == 50) ? (index = 52) : (index = 53);
            break;
        case Doll_Sucess_Style:
        case Doll_Fail_Style:
            (sender.tag == 50) ? (index = 50) : (index = 51);
            break;
        default:
            break;
    }
    
    if (self.resultBlock) {
        self.resultBlock(index);
    }
}
@end
