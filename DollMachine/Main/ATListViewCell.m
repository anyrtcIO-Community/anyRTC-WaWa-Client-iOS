//
//  ATListViewCell.m
//  DollMachine
//
//  Created by jh on 2017/12/6.
//  Copyright © 2017年 jh. All rights reserved.
//

#import "ATListViewCell.h"

@implementation ATListViewCell

- (void)awakeFromNib{
    [super awakeFromNib];
}

- (void)setRoomModel:(Roomlist *)roomModel{
    self.roomNameLabel.text = roomModel.room_username;
    self.onlineLabel.attributedText = [ATCommon getAttributedString:[NSString stringWithFormat:@"  %ld",(long)roomModel.room_member] imageSize:CGRectMake(0, 0, 12, 12) image:[UIImage imageNamed:@"people_icon"] index:0];
    if (roomModel.room_state == 0) {
        //正常
        self.stateLabel.attributedText = [ATCommon getAttributedString:@"  游戏中" imageSize:CGRectMake(0, 0, 12, 9) image:[UIImage imageNamed:@"icon_gameing"] index:0];
        self.stateLabel.textColor = [ATCommon getColor:@"#ff834e"];
    } else {
        //维护
        self.stateLabel.attributedText = [ATCommon getAttributedString:@"  维护中" imageSize:CGRectMake(0, 0, 12, 12) image:[UIImage imageNamed:@"icon_weihuing"] index:0];
        self.stateLabel.textColor = [ATCommon getColor:@"#aaaaaa"];
    }

}

@end
