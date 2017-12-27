//
//  ATMainViewController.m
//  DollMachine
//
//  Created by jh on 2017/11/29.
//  Copyright © 2017年 jh. All rights reserved.
//

#import "ATMainViewController.h"

@interface ATMainViewController ()

@end

@implementation ATMainViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    [[UIApplication sharedApplication] setStatusBarStyle:UIStatusBarStyleLightContent];
}

- (IBAction)joinQRCode:(UIButton *)sender {
    switch (sender.tag) {
        case 99:
        {
            ATListViewController *listVc = [[self storyboard] instantiateViewControllerWithIdentifier:@"ListID"];
            [self.navigationController pushViewController:listVc animated:YES];
        }
            break;
        case 100:
            [ATCommon callPhone:@"021-65650071-840" control:sender];
            break;
        default:
            break;
    }
}

- (void)viewWillAppear:(BOOL)animated{
    [super viewWillAppear:animated];
    self.navigationController.navigationBarHidden = YES;
}

@end
