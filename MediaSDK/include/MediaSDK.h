//
//  MediaSDK.h
//  MediaSDK
//
//  Created by 湛奇 on 13-8-21.
//  Copyright (c) 2013年 stylejar. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "MediaDefine.h"
#import "MediaSDKDelegate.h"

@interface MediaSDK : NSObject

@property (nonatomic, weak)   id<MediaSDKDelegate>delegate;     //delegate
@property (nonatomic, assign) BOOL enableSpeaker;               //是否开启外放
@property (nonatomic, assign) BOOL enableMicrophone;            //是否启用麦克
@property (nonatomic, assign) int mediaPort;     //记录mediaport


#pragma mark - Instance & Purge Instance
/**
 *  单例对象
 *
 *  @return 单例对象
 */
+(MediaSDK*)sharedInstance;

/**
 *  释放单例
 */
+(void)purgeSharedInstance;

#pragma mark - start
/**
 *  wchat开放的端口号
 *
 *  @param port 端口号
 */
-(void)startWithWchatPort:(int)port;

#pragma mark - 多媒体电话
/**
 *  单人电话
 *
 *  @param toUid      被叫方uid
 *  @param fromUid    呼叫方uid
 *  @param enableVieo 是否支持视频
 *  @param error       error 错误类型
 *                     1，传统电话通话中：Domain：mediaErrorDomain  code：1001  info：telephone working
 *                     2，网络状况差 不适合通话 请稍后再试：Domain：mediaErrorDomain  code：1002  info：bad network
 */
-(void)callUser:(NSString*)toUid from:(NSString *)fromUid enabelVideo:(BOOL)enableVieo error:(NSError **)error;    //给某人打电话

/**
 *  接听电话
 *  当开始接电话的时候 才能知道 语音传输是不是有问题 看error信息：
 *  网络状况差 不适合通话 请稍后再试：Domain：mediaErrorDomain  code：1002  info：bad network
 *  提示用户 然后 调用挂断的接口(客户端调或用户点击)
 *
 *  @param error       error 错误类型
 *                     1，传统电话通话中：Domain：mediaErrorDomain  code：1001  info：telephone working
 *                     2，网络状况差 不适合通话 请稍后再试：Domain：mediaErrorDomain  code：1002  info：bad network
 */
-(void)callAccept:(NSError **)error;

/**
 *  挂断电话
 */
-(void)callTerminate;

/**
 *  多人电话(多人电话不允许视频)
 *
 *  @param roomid  房间id
 *  @param fromUid 请求人id
 *  @param Key     房间key
 *  @param error   error 错误类型：
 *                  1，参数错误：  Domain：mediaErrorDomain  code：1000  info：bad parameter
 *                  2，传统电话通话中：Domain：mediaErrorDomain  code：1001  info：telephone working
 *                  3，网络状况差 不适合通话 请稍后再试：Domain：mediaErrorDomain  code：1002  info：bad network
 */
-(void)callRoom:(NSString *)roomid from:(NSString *)fromUid withKey:(NSString *)Key error:(NSError **)error; //加入多人电话

#pragma mark - 直播
/**
 *  主播方 开始直播的方法
 *
 *  @param audioIP     音频传输的ip
 *  @param audioPort   音频传输的port
 *  @param videoIP     视频传输的ip
 *  @param videoPort   视频传输的port
 *  @param enableVideo 是否开启视频  开启视频的时候会使用 videoIP videoPort两个参数
 *  @param error       error 错误类型
 *                     1，传统电话通话中：Domain：mediaErrorDomain  code：1001  info：telephone working
 *                     2，网络状况差 不适合通话 请稍后再试：Domain：mediaErrorDomain  code：1002  info：bad network
 */
-(void)liveWithAudioip:(NSString *)audioIP AudioPort:(int)audioPort Videoip:(NSString *)videoIP VideoPort:(int)videoPort enabelVideo:(BOOL)enableVideo error:(NSError **)error;

/**
 *  主播方 发心跳 告诉服务器直播还在连接状态 且 客户端知道服务器还在正常工作
 *
 *  @param url 以用户uid为参数的地址
 */
-(void)startHeartBeatWithURL:(NSString *)url;

/**
 *  收听方 开始收听的预处理 底层的直播初始化工作 并且从服务器得到自己的ip和端口
 *
 *  @param enabelVideo 是否开启视频
 *  @param error       error 错误类型
 *                     1，传统电话通话中：Domain：mediaErrorDomain  code：1001  info：telephone working
 *                     2，网络状况差 不适合通话 请稍后再试：Domain：mediaErrorDomain  code：1002  info：bad network
 */
-(void)startListenforLiveEnableVideo:(BOOL)enabelVideo Error:(NSError **)error;

/**
 *  收听方 设置要收听的ip和port
 *
 *  @param audioIP     音频传输的ip
 *  @param audioPort   音频传输的port
 *  @param videoIP     视频传输的ip
 *  @param videoPort   视频传输的port
 *  @param enableVideo 是否开启视频  开启视频的时候会使用 videoIP videoPort两个参数
 *  @param error       error 错误类型  
 *                     1，传统电话通话中：Domain：mediaErrorDomain  code：1001  info：telephone working
 *                     2，网络状况差 不适合通话 请稍后再试：Domain：mediaErrorDomain  code：1002  info：bad network
 */
-(void)setDestinationAudioIP:(NSString *)audioIP AudioPort:(int)audioPort VideoIP:(NSString *)videoIP VideoPort:(int)videoPort enableVideo:(BOOL)enableVideo error:(NSError **)error;

/**
 *  视频电话、直播方、收听方 设置本地和远程的视频显示窗口  直播方只需设置本地的 收听方只需设置远程的
 *
 *  @param localView  本地视频窗口
 *  @param remoteView 远程视频窗口
 */
-(void)setLocalVideoView:(UIView *)localView RemoteVideoView:(UIView *)remoteView;

/**
 *  直播方切换镜头
 *
 *  @param error 错误
 */
-(void)switchCamera:(NSError **)error;

/**
 *  直播方、收听方 挂断直播和收听
 */
-(void)terminateLive;               

#pragma mark - 语音质量数据

/**
 *  是否上报语音质量数据 (默认开启, 间隔3秒上报一次)
 *
 *  @param isEnable yes 开启, no关闭
 */
-(void)enableReportQualityData:(BOOL)isEnable;

#pragma mark - 降噪处理

/**
 *  是否开启降噪优化
 *
 *  @param isEnable yes 开启, no 不开启
 */
-(void)enableNoiseGate:(BOOL)isEnable;

/**
 *  设置降噪参数
 *
 *  @param ng_thres     阙值
 *  @param ng_floorgain 增益值
 */
-(void)setNoiseGate:(float)ng_thres floorgain:(float)ng_floorgain;

#pragma mark - UIApplication delegate appdelegate中需要添加的方法

/**
 *  进入后台 applicationDidEnterBackground
 *
 *  @return 是否进入后台模式
 */
-(BOOL)enterBackgroundMode;

/**
 *  进入前台, 在 enterBackgroundMode 中实现 以维持mediaSDK 在后台的 voip 激活状态
 */
-(void)keepAlive;

/**
 *  applicationWillResignActive    中添加
 */
-(void)willResignActiveAction;

/**
 *  applicationDidBecomeActive     中添加
 */
-(void)didBecomeActiveAction;

@end

#pragma mark - Notification 通知

//正常流程
extern NSString *NotificationMediaCallIncoming;     //来电
extern NSString *NotificationMediaCallConnected;    //来电接通
extern NSString *NotificationMediaCallEnd;          //单人电话下，对方挂断 或 直播的时候本机来电话（live_self） 或 直播的时候主播失去连接超时
extern NSString *NotificationMediaCallRemotePause;  //挂起(被优先级更高任务打断)

//出错
extern NSString *NotificationMediaCallError;        //错误

//直播
#define liveReceiveIPandPort      @"liveReceiveIPandPortKey"
extern NSString *mediaHeartBeatErrorKey;   //直播中 主播的心跳状态出问题的通知
