//
//  ATListModel.m
//  DollMachine
//
//  Created by jh on 2017/12/6.
//  Copyright © 2017年 jh. All rights reserved.
//

#import "ATListModel.h"

@implementation ATListModel


+ (NSDictionary *)objectClassInArray{
    return @{@"roomlist" : [Roomlist class]};
}
@end
@implementation Roomlist

- (void)setRoom_url:(NSString *)room_url{
    _room_url = room_url;
    if (room_url && ![room_url isEqualToString:@""]) {
        
        NSDictionary *dict = [self JSONValue:room_url];
        if (dict) {
            _RtcpUrl = [dict objectForKey:@"RtcpUrl"];
            _H5LiveUrl = [dict objectForKey:@"H5LiveUrl"];
        }
    }
}

- (id)JSONValue:(NSString*)jsonStrong
{
    if ([jsonStrong isKindOfClass:[NSDictionary class]]) {
        return jsonStrong;
    }
    NSData* data = [jsonStrong dataUsingEncoding:NSUTF8StringEncoding];
    __autoreleasing NSError* error = nil;
    id result = [NSJSONSerialization JSONObjectWithData:data options:kNilOptions error:&error];
    if (error != nil) return nil;
    return result;
}

@end


