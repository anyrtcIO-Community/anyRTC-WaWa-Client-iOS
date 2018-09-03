//
//  ATDollViewController.m
//  DollMachine
//
//  Created by jh on 2017/11/29.
//  Copyright © 2017年 jh. All rights reserved.
//

#import "ATDollViewController.h"
#import <RTCPEngine/RTCPKit.h>
#import "ATDollView.h"

@interface ATDollViewController ()<RTCPKitDelegate,AVAudioPlayerDelegate,RTCWawaKitDelegate>

@property (weak, nonatomic) IBOutlet UIView *localView;
//操作（上下左右抓取）
@property (weak, nonatomic) IBOutlet UIView *operationsView;
//预约按钮
@property (weak, nonatomic) IBOutlet UIButton *appointmentButton;
//在线人数
@property (weak, nonatomic) IBOutlet UIButton *onlineButton;
//房间id
@property (weak, nonatomic) IBOutlet UIButton *roomButton;
//抓取按钮
@property (weak, nonatomic) IBOutlet ATCountdown *catchButton;
//切换
@property (weak, nonatomic) IBOutlet UIButton *transformButton;
//排队人数
@property (weak, nonatomic) IBOutlet UILabel *lineUpLabel;

@property (nonatomic, strong) RTCPKit *rtcpKit;
//配置信息
@property (nonatomic, strong) RTCPOption *option;
//抓取结果
@property (nonatomic, strong) ATDollView *dollView;

@property (nonatomic, strong) AVAudioPlayer *player;
//娃娃机是否在线
@property (nonatomic, assign) BOOL isOK;
//准备只弹一次（容错）
@property (nonatomic, assign) NSInteger index;
//抓取结果只弹一次（容错）
@property (nonatomic, assign) NSInteger resultIndex;
//抓取结果容错(点击抓取无返回结果)
@property (nonatomic, strong) NSTimer *timer;
@end

@implementation ATDollViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.anyRtcId = self.listModel.room_anyrtcid;
    [self initUI];
    [self itializationRTCPKit:self.listModel.RtcpUrl];
    
    //加入房间
    [RTCWaWaKit sharedInstance].delegate = self;
    [[RTCWaWaKit sharedInstance] joinRoom:self.anyRtcId withUserId:[NSString stringWithFormat:@"iOS_%@",[ATCommon randomAnyRTCString:6]] UserName:[ATCommon randomString:6] withUserIcon:@""];
}

- (void)initUI{
    self.operationsView.hidden = YES;
    self.transformButton.hidden = YES;
    self.appointmentButton.hidden = YES;
    
    self.navigationItem.title = self.listModel.room_username;
    self.roomButton.layer.mask = [ATCommon getMaskLayer:self.roomButton.bounds byRoundingCorners:UIRectCornerTopRight | UIRectCornerBottomRight cornerRadii:20];
    self.transformButton.layer.mask = [ATCommon getMaskLayer:self.transformButton.bounds byRoundingCorners:UIRectCornerTopLeft | UIRectCornerBottomLeft cornerRadii:30];
    
    [self.roomButton setTitle:[NSString stringWithFormat:@"  娃娃机%@",self.anyRtcId] forState:UIControlStateNormal];
}

- (void)itializationRTCPKit:(NSString *)rtcpId{
    //初始化会议工具类
    self.rtcpKit = [[RTCPKit alloc]initWithDelegate:self withOption:self.option];
    //观看直播
    [self.rtcpKit subscribe:rtcpId];
}

#pragma mark - RTCDollKitDelegate
- (void)onJoinRoom:(NSString*)rtcpId andRoomMember:(int)roomMember withCode:(int)code{
    //进入房间通知(抓娃娃机者)
    self.appointmentButton.hidden = NO;
    NSString *onlineStr = [NSString stringWithFormat:@"  %d人正在围观",roomMember];
    [self.onlineButton setTitle:onlineStr forState:UIControlStateNormal];
}

- (void)onLeaveRoom:(int)code{
    //离开房间通知(抓娃娃机者)
    [XHToast showCenterWithText:@"娃娃机维护中..."];
    [self.rtcpKit close];
    [self.navigationController popViewControllerAnimated:YES];
}

- (void)onWawajiDisconnect{
    //娃娃机连接断开通知
}

- (void)onWawajiReconnect:(NSString*)rtcpId{
    //娃娃机断开重连通知
    if (self.rtcpKit) {
        [self.rtcpKit close];
    }
    [self itializationRTCPKit:rtcpId];
}

- (void)onBookResult:(int)bookMember withCode:(int)code{
    //预约结果通知
    self.lineUpLabel.hidden = NO;
    NSString *bookStr = [NSString stringWithFormat:@"您当前排在：第%d位",bookMember];
    self.lineUpLabel.text = bookStr;
}

- (void)onControlCmd:(AnyRTC_CMD_State)eCmd withCode:(int)code{
    //控制命令通知
}

- (void)onGrabResult:(int)code{
    //抓娃娃结果通知
    if (self.resultIndex == 1) {
        
        if (self.timer) {
            //结束本地倒计时
            [self.timer invalidate];
            self.timer = nil;
        }
        
        self.resultIndex ++;
        
        [self.appointmentButton setTitle:@"我要预约" forState:UIControlStateNormal];
        self.transformButton.hidden = YES;

        self.dollView = nil;
        if (code) {
            //抓取成功
            [self playMusic:Doll_Sucess_Style];
            [self.dollView changeStyle:Doll_Sucess_Style];
            UIWindow *window = [[UIApplication sharedApplication] keyWindow];
            [window addSubview:self.dollView];
        } else {
            //抓取失败
            [self playMusic:Doll_Fail_Style];
            [self.dollView changeStyle:Doll_Fail_Style];
            UIWindow *window = [[UIApplication sharedApplication] keyWindow];
            [window addSubview:self.dollView];
        }
    }
}

- (void)onRoomMemberUpdate:(int)roomMember{
    //房间人数变化通知
    NSString *onlineStr = [NSString stringWithFormat:@"  %d人正在围观",roomMember];
    [self.onlineButton setTitle:onlineStr forState:UIControlStateNormal];
}

- (void)onBookMemberUpdate:(int)bookMember{
    //排队人数变化通知
    NSString *bookStr = @"";
    if (self.appointmentButton.selected) {
        bookStr = [NSString  stringWithFormat:@"您当前排在：第%d位",bookMember];
    } else {
        bookStr = [NSString  stringWithFormat:@"当前排队人数：%d",bookMember];
    }
    self.lineUpLabel.text = bookStr;
}

- (void)onReadyPlay{
    //排队抓娃娃准备通知
    self.lineUpLabel.hidden = YES;
    self.operationsView.userInteractionEnabled = YES;
    if (self.index == 1) {
        self.dollView = nil;
        [self.dollView changeStyle:Doll_Read_Style];
        UIWindow *window = [[UIApplication sharedApplication] keyWindow];
        [window addSubview:self.dollView];
        self.operationsView.hidden = NO;
        self.appointmentButton.hidden = YES;
        self.index ++;
    }
}

- (void)onReadyPlayTimeout{
    //准备超时通知
    self.operationsView.hidden = YES;
    self.appointmentButton.hidden = NO;
    self.appointmentButton.selected = NO;
    [self.appointmentButton setTitle:@"我要预约" forState:UIControlStateNormal];
    [self.dollView removeFromSuperview];
}

- (void)onPlayTimeout{
    //抓娃娃超时通知
    self.operationsView.hidden = YES;
    self.transformButton.hidden = YES;
    self.appointmentButton.hidden = NO;
    self.appointmentButton.selected = NO;
}

#pragma mark - RTCPKitDelegate
- (void)onPublishOK:(NSString *)strRtcpId withLiveInfo:(NSString*)strLiveInfo{
    //发布媒体成功回调
}

- (void)onPublishFailed:(int)nCode{
    //发布媒体失败回调
}

- (void)onSubscribeOK:(NSString*)strRtcpId{
    //订阅频道成功的回调
    self.isOK = YES;
    NSLog(@"订阅成功");
}

- (void)onSubscribeFailed:(NSString*)strRtcpId intCode:(int)nCode{
    //订阅频道失败的回调
    self.isOK = NO;
    NSLog(@"订阅失败");
    [XHToast showCenterWithText:@"当前娃娃机离线"];
}

- (void)onRTCOpenVideoRender:(NSString*)strRtcpId{
    //订阅后视频即将显示的回调
    [self.rtcpKit setRTCVideoRender:strRtcpId andRender:self.localView];
}

- (void)onRTCCloseVideoRender:(NSString*)strRtcpId{
    //订阅的视频离开的回调
    [self.rtcpKit close];
    [self.navigationController popViewControllerAnimated:YES];
}

- (void)onRTCCViewChanged:(UIView*)videoView didChangeVideoSize:(CGSize)size{
    //视频窗口大小的回调  480 640
}

#pragma mark - event
- (IBAction)operationEvents:(UIButton *)sender {
    switch (sender.tag) {
        case 99://上
            
            [self playMusic:Doll_Control_Style];
            [[RTCWaWaKit sharedInstance] sendControlCmd:CMD_FORWARD];
            break;
        case 100://右
            
            [self playMusic:Doll_Control_Style];
            [[RTCWaWaKit sharedInstance] sendControlCmd:CMD_RIGHT];
            break;
        case 101://左
            
            [self playMusic:Doll_Control_Style];
            [[RTCWaWaKit sharedInstance] sendControlCmd:CMD_LEFT];
            break;
        case 102://下
            
            [self playMusic:Doll_Control_Style];
            [[RTCWaWaKit sharedInstance] sendControlCmd:CMD_BACKWARD];
            break;
        case 103://切换
            
            [self playMusic:Doll_Control_Style];
            [[RTCWaWaKit sharedInstance] sendControlCmd:CMD_SWITCH_CAMERA];
            break;
        case 104://抓取
            
            self.timer = [NSTimer timerWithTimeInterval:10 target:self selector:@selector(dealWithDollResult) userInfo:nil repeats:NO];
            [[NSRunLoop mainRunLoop] addTimer:self.timer forMode:NSDefaultRunLoopMode];
            
            [self playMusic:Doll_Control_Style];
            [self.catchButton timeMeterEnd];
            [self.catchButton setTitle:@"抓取" forState:UIControlStateNormal];
            self.operationsView.userInteractionEnabled = NO;
            [[RTCWaWaKit sharedInstance] sendControlCmd:CMD_GRAB];
            break;
        case 105://预约
            if (!self.isOK) {
                [XHToast showCenterWithText:@"娃娃机离线，操作不可用"];
                return;
            }
            self.operationsView.userInteractionEnabled = YES;
            self.index = 1;
            sender.selected = !sender.selected;
            
            if (sender.selected) {
                [[RTCWaWaKit sharedInstance] makeBook];
                self.lineUpLabel.hidden = NO;
            } else {
                [[RTCWaWaKit sharedInstance] cancelBook];
                self.lineUpLabel.hidden = YES;
            }
            
            break;
        case 106:
        {
            //离开
            if (self.appointmentButton.selected) {//预约状态
                [[RTCWaWaKit sharedInstance] cancelBook];
            }
            if (self.timer) {
                [self.timer invalidate];
                self.timer = nil;
            }
            [[RTCWaWaKit sharedInstance] leaveRoom];
            [self.navigationController popViewControllerAnimated:YES];
        }
            break;
        case 107:
        {
            [ATCommon callPhone:@"021-65650071-840" control:sender];
        }
            break;
        default:
            break;
    }
}

- (void)dealWithDollResult{
    //抓取后无返回结果
    if (self.timer) {
        [self.timer invalidate];
        self.timer = nil;
    }
    [XHToast showCenterWithText:@"网络异常"];
    self.transformButton.hidden = YES;
    self.operationsView.hidden = YES;
    self.appointmentButton.hidden = NO;
    self.appointmentButton.selected = NO;
}

- (void)playMusic:(DollStyle)style{
    NSString *nameStr = @"";
    switch (style) {
        case Doll_Read_Style:
            nameStr = @"ready_go";
            break;
        case Doll_Sucess_Style:
            nameStr = @"sucess";
            break;
        case Doll_Fail_Style:
            nameStr = @"fail";
            break;
        case Doll_Control_Style:
            nameStr = @"sound";
        default:
            break;
    }
    
    self.player = nil;
    
    AVAudioSession * session = [AVAudioSession sharedInstance];
    [session setActive:YES error:nil];
    [session setCategory:AVAudioSessionCategoryPlayback error:nil];
    
    NSError * error;
    NSURL *tempUrl = [NSURL fileURLWithPath:[[NSBundle mainBundle]pathForResource:nameStr ofType:@"mp3"]];
    self.player = [[AVAudioPlayer alloc]initWithContentsOfURL:tempUrl error:&error];
    self.player.numberOfLoops = 0;
    
    [self.player prepareToPlay];
    self.player.delegate = self;
    [self.player play];
    self.player.volume = 1;
}

#pragma mark - other
- (RTCPOption *)option{
    if (!_option) {
        _option = [RTCPOption defaultOption];
        _option.videoMode = AnyRTCVideoQuality_Medium2;
        _option.orientation = RTC_SCRN_Portrait;
    }
    return _option;
}

- (ATDollView *)dollView{
    if (!_dollView) {
        _dollView = [[[NSBundle mainBundle]loadNibNamed:@"ATDollView" owner:self options:nil] lastObject];
        _dollView.frame = self.view.bounds;
        WEAKSELF;
        _dollView.resultBlock = ^(NSInteger tag) {
            switch (tag) {
                case 50://休息一下
                {
                    weakSelf.operationsView.hidden = YES;
                    weakSelf.appointmentButton.hidden = NO;
                    weakSelf.appointmentButton.selected = NO;
                    [weakSelf.dollView removeFromSuperview];
                }
                    break;
                case 51://再接再厉
                {
                    weakSelf.index = 1;
                    [[RTCWaWaKit sharedInstance] makeBook];
                    weakSelf.operationsView.hidden = YES;
                    weakSelf.appointmentButton.hidden = NO;
                    weakSelf.appointmentButton.selected = YES;
                    [weakSelf.dollView removeFromSuperview];
                }
                    break;
                case 52://放弃
                {
                    weakSelf.operationsView.hidden = YES;
                    weakSelf.appointmentButton.hidden = NO;
                    weakSelf.appointmentButton.selected = NO;
                    [weakSelf.appointmentButton setTitle:@"我要预约" forState:UIControlStateNormal];
                    [[RTCWaWaKit sharedInstance] cancelPlay];
                    [weakSelf.dollView removeFromSuperview];
                }
                    break;
                case 53://开始
                {
                    weakSelf.resultIndex = 1;
                    [[RTCWaWaKit sharedInstance] startPlay];
                    [weakSelf.catchButton timeFailBeginFrom:30 andDescribe:NO];
                    [weakSelf playMusic:Doll_Read_Style];
                    [weakSelf.dollView removeFromSuperview];
                    weakSelf.dollView = nil;
                    weakSelf.transformButton.hidden = NO;
                }
                    break;
                default:
                    break;
            }
        };
    }
    return _dollView;
}

- (void)viewWillAppear:(BOOL)animated{
    [super viewWillAppear:animated];
    self.navigationController.navigationBarHidden = YES;
    [[UIApplication sharedApplication] setStatusBarStyle:UIStatusBarStyleLightContent];
}

- (void)viewWillDisappear:(BOOL)animated{
    [super viewWillDisappear:animated];
    self.navigationController.navigationBarHidden = NO;
    if (self.player) {
        [self.player pause];
        self.player = nil;
    }
}

- (void)dealloc{
    [self.rtcpKit close];
}

@end
