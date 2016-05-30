//
//  MediaConferenceFetchUsersRequest.h
//  MediaSDK
//
//  Created by Frederic on 15/11/25.
//  Copyright © 2015年 stylejar. All rights reserved.
//
//  查询加入群组的用户列表

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, SHFetchUserListRequestStatus) {
    SHFetchUserListRequestStatusStart ,
    SHFetchUserListRequestStatusLoading ,
    SHFetchUserListRequestStatusError ,
    SHFetchUserListRequestStatusSuccess ,
};

@protocol MediaConferenceFetchUsersRequestDelegate <NSObject>

/**
 *  回调，会反回请求结果
 *
 *  @param resultList 成员ID列表 { "apistatus" : 1,  "result" : { "roles" : [ { "id" : "123", "nickname" : "123" ... } ] }}
 *                                apistatus == 1 请求成功
 *  @param status     请求状态
 */
- (void)fetchUserLists:(id)resultList requestStatus:(SHFetchUserListRequestStatus)status error:(NSError*)error;

@end


@interface MediaConferenceFetchUsersRequest : NSObject

@property (nonatomic, weak) id<MediaConferenceFetchUsersRequestDelegate> delegate;

/**
 *  根据群组ID查询加入群组的用户列表
 *
 *  @param groupID 群组ID(不能为空)
 *  @param userID 当前用户ID(不能为空)
 *  @param mAuth 客户端的Auth token(不能为空)
 */
- (void)fetchFriendsDataWithGroupID:(NSString*)groupID userID:(NSString*)userID mAuth:(NSString*)mAuth;

@end
