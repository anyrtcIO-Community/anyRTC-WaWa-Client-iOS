//
//  ATDollViewController.h
//  DollMachine
//
//  Created by jh on 2017/11/29.
//  Copyright © 2017年 jh. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ATListModel.h"

@interface ATDollViewController : UIViewController

@property (nonatomic, copy) NSString *anyRtcId;

@property (nonatomic, strong) Roomlist *listModel;

@end
