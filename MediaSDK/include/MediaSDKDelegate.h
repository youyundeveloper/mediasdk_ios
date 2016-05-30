//
//  MediaSDKDelegate.h
//  speexDemo
//
//  Created by c-mbp13 on 13-8-30.
//  Copyright (c) 2013年 stylejar. All rights reserved.
//

#ifndef speexDemo_MediaSDKDelegate_h
#define speexDemo_MediaSDKDelegate_h

#import "MediaDefine.h"

typedef enum
{
    MediaSDKLiveStatusNoSounds   = 0,   //下行无声音数据 (目前检测连续10秒, 10秒都没有数据则触发)
    MediaSDKLiveStatusBadNetwork = 1,   //网络情况差 (连续10次检测语音分数, 低于3分情况出现8次则触发)
}
MediaSDKLiveBadStatus;

@protocol MediaSDKDelegate <NSObject>

@optional

/**
 *  来电回调
 *
 *  @param userId 通话对方用户id
 */
-(void)mediaCallIncomingByUser:(NSString*)userId;

/**
 *  来电接通回调
 *
 *  @param userId 通话对方用户id
 */
-(void)mediaCallConnectedByUser:(NSString*)userId;

/**
 *  单人电话下，对方挂断 或 直播的时候本机来电话（live_self）  或 直播的时候主播失去连接超时
 *
 *  @param userId 通话对方用户id
 */
-(void)mediaCallEndByUser:(NSString*)userId;


/**
 *  挂起(被优先级更高任务打断)
 *
 *  @param userId 通话对方用户id
 */
-(void)mediaCallRemotePauseByUser:(NSString*)userId;

/**
 *  错误回调
 *
 *  @param error  错误信息
 *  @param userId 通话对方用户id
 */
-(void)mediaCallError:(NSError*)error fromUser:(NSString*)userId;

/**
 *  上报直播差状态
 *
 *  @param status 直播状态 MediaSDKLiveBadStatus
 */
-(void)liveBadStatus:(MediaSDKLiveBadStatus)status;

@end
#endif
