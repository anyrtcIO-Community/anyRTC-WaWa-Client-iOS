//
//  ATListViewCell.h
//  DollMachine
//
//  Created by jh on 2017/12/6.
//  Copyright © 2017年 jh. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ATListViewCell : UICollectionViewCell


//在线人数
@property (weak, nonatomic) IBOutlet UILabel *onlineLabel;
//房间名
@property (weak, nonatomic) IBOutlet UILabel *roomNameLabel;
//房间状态
@property (weak, nonatomic) IBOutlet UILabel *stateLabel;

@property (nonatomic, strong) Roomlist *roomModel;

@end
