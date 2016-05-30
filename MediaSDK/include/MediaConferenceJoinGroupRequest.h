//
//  MediaConferenceJoinGroupRequest.h
//  MediaSDK
//
//  Created by Frederic on 15/11/25.
//  Copyright © 2015年 stylejar. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, SHJoinGroupRequestStatus) {
    SHJoinGroupRequestStatusStart ,
    SHJoinGroupRequestStatusLoading ,
    SHJoinGroupRequestStatusError ,
    SHJoinGroupRequestStatusSuccess ,
};

@protocol MediaConferenceJoinGroupRequestDelegate <NSObject>

- (void)joinGroupResponse:(id)response requestStatus:(SHJoinGroupRequestStatus)status error:(NSError*)error;

@end


@interface MediaConferenceJoinGroupRequest : NSObject

@property (nonatomic, weak) id<MediaConferenceJoinGroupRequestDelegate> delegate;

/**
 *  根据群组ID申请加入群组
 *
 *  @param groupID 群组ID(不能为空)
 *  @param userID 当前用户ID(不能为空)
 *  @param mAuth 客户端的Auth token(不能为空)
 */
- (void)joinGroupWithGroupID:(NSString*)groupID userID:(NSString*)userID mAuth:(NSString*)mAuth;

@end
