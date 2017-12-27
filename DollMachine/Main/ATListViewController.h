//
//  ATListViewController.h
//  DollMachine
//
//  Created by jh on 2017/12/6.
//  Copyright © 2017年 jh. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ATListViewController : UICollectionViewController<RTCWawaKitDelegate>

@property (nonatomic, strong)NSMutableArray *dataArr;

@property (nonatomic, strong)UIRefreshControl *refreshControl;

@end
