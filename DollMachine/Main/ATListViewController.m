//
//  ATListViewController.m
//  DollMachine
//
//  Created by jh on 2017/12/6.
//  Copyright © 2017年 jh. All rights reserved.
//

#import "ATListViewController.h"
#import "ATListViewCell.h"
#import "ATCollectionReusableView.h"

@implementation ATListViewController

static NSString * const reuseIdentifier = @"ListCellID";

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor whiteColor];
    self.navigationController.navigationBar.barTintColor = [UIColor whiteColor];
    [self.navigationController.navigationBar setTitleTextAttributes:@{NSForegroundColorAttributeName:[UIColor blackColor]}];
    
    //设置导航
    [self setNavBar];
    
    [self.collectionView registerNib:[UINib nibWithNibName:@"ATCollectionReusableView" bundle:nil] forSupplementaryViewOfKind:UICollectionElementKindSectionHeader withReuseIdentifier:@"ListReusable"];
    
    [[RTCWaWaKit sharedInstance]initEngineWithAnyRTCInfo:developerID andAppId:appID andKey:key andToke:token];
    [RTCWaWaKit sharedInstance].delegate = self;
    
    [self refreshData];
}

- (void)refreshData{
    self.refreshControl = [[UIRefreshControl alloc] init];
    self.refreshControl.tintColor = [UIColor grayColor];
    [self.refreshControl addTarget:self action:@selector(refershControlAction:) forControlEvents:UIControlEventValueChanged];
    [self.collectionView addSubview:self.refreshControl];
    [self.collectionView setAlwaysBounceVertical:YES];
}

-(void)refershControlAction:(UIRefreshControl*)con{
    self.refreshControl.attributedTitle = [[NSAttributedString alloc]initWithString:@"开始刷新了~~"];
    [self refreshloadNewData];
}

- (void)onInitAnyRTCSuccess{
    [self refreshloadNewData];
}

- (void)refreshloadNewData{
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(5 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        if ([self.refreshControl isRefreshing]) {
            [self.refreshControl endRefreshing];
        }
    });
    
    [[RTCWaWaKit sharedInstance] getRoomListWithBlock:^(NSDictionary *listDic) {
        [self.refreshControl endRefreshing];
        [self.dataArr removeAllObjects];
        ATListModel *listModel = [ATListModel mj_objectWithKeyValues:listDic];
        for (NSInteger i = listModel.roomlist.count - 1; i >= 0; i--) {
            [self.dataArr addObject:listModel.roomlist[i]];
        }
        
        [self.collectionView reloadData];
    }];
    
}

- (void)setNavBar{
    self.navigationItem.title = @"anyRTC在线娃娃机";
    
    UIButton *leftBtn=[UIButton buttonWithType:UIButtonTypeCustom];
    [leftBtn setImage:[UIImage imageNamed:@""] forState:UIControlStateNormal];
    leftBtn.frame = CGRectZero;
    self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc]initWithCustomView:leftBtn];
    
    UIButton *rightBtn=[UIButton buttonWithType:UIButtonTypeCustom];
    [rightBtn setImage:[UIImage imageNamed:@"button_kefu"] forState:UIControlStateNormal];
    rightBtn.frame=CGRectMake(0, 0, 30, 30);
    [rightBtn addTarget:self action:@selector(doSomethingEvent:) forControlEvents:UIControlEventTouchUpInside];
    self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc]initWithCustomView:rightBtn];
    [self.navigationController.navigationBar setShadowImage:[UIImage new]];
}

- (void)doSomethingEvent:(UIButton *)sender{
    [ATCommon callPhone:@"021-65650071-840" control:sender];
}

#pragma mark <UICollectionViewDataSource>
- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section {
    return self.dataArr.count;
}

- (UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath {
    ATListViewCell* cell  = [collectionView dequeueReusableCellWithReuseIdentifier:reuseIdentifier forIndexPath:indexPath];
    Roomlist *listModel = self.dataArr[indexPath.row];
    cell.roomModel = listModel;
    return cell;
}

- (void)collectionView:(UICollectionView *)collectionView didSelectItemAtIndexPath:(NSIndexPath *)indexPath{
    
    Roomlist *listModel = self.dataArr[indexPath.row];
    if (listModel.room_state == 1) {
        [XHToast showCenterWithText:@"当前娃娃机正在维护..."];
        return;
    }
    ATDollViewController *dollVc = [[self storyboard] instantiateViewControllerWithIdentifier:@"DollId"];
    dollVc.listModel = listModel;
    [self.navigationController pushViewController:dollVc animated:YES];
}

- (UICollectionReusableView *)collectionView:(UICollectionView *)collectionView viewForSupplementaryElementOfKind:(NSString *)kind atIndexPath:(NSIndexPath *)indexPath{
    if ([kind isEqualToString:UICollectionElementKindSectionHeader]) {
        ATCollectionReusableView *reusableView = [collectionView dequeueReusableSupplementaryViewOfKind:UICollectionElementKindSectionHeader withReuseIdentifier:@"ListReusable" forIndexPath:indexPath];
        return reusableView;
    }
    return nil;
}

- (CGSize)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout *)collectionViewLayout referenceSizeForHeaderInSection:(NSInteger)section {
    CGFloat widthX = self.view.frame.size.width;
    return CGSizeMake(widthX, (widthX- 40)/1.9 + 40);
}

- (NSMutableArray *)dataArr{
    if (!_dataArr) {
        _dataArr = [NSMutableArray arrayWithCapacity:4];
    }
    return _dataArr;
}

- (void)viewWillAppear:(BOOL)animated{
    [super viewWillAppear:animated];
    self.navigationController.navigationBarHidden = NO;
    [[UIApplication sharedApplication]setStatusBarStyle:UIStatusBarStyleDefault];
}

- (void)viewWillDisappear:(BOOL)animated{
    [super viewWillDisappear:animated];
    self.navigationController.navigationBarHidden = YES;
}

@end

