# mediasdk_ios
YouYun MediaSDK for iOS.

本SDK只能运行在真机.

1. 导人必要的framework和dylib:

```

    Security.framework
    AVFoundation.framework
    CoreVideo.framework
    CoreMedia.framework
    libresolv.dylib
    libsqlite3.dylib
    CoreTelephony.framework
    QuartzCore.framework
    OpenGLES.framework
    CoreGraphics.framework
    CFNetwork.framework
    SystemConfiguration.framework
    AudioToolbox.framework
    MediaPlayer.framework
    UIKit.framework
    Foundation.framework
```

2. 导入必要的附件文件:

    hold.wav        // 等待提示音
    msg.caf         // 提醒
    msg.wav         // 提醒
    ring.caf        // 来电
    ring.wav        // 来电
    ringback.wav    // 播出等待提示音

3. Targets Build Setting

    Enable Bitcode  NO

    App Transport Security Settings -> Allow Arbitrary Loads -> YES


4. 在 AppDelegate.m 中需要做如下设置:


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

    详细见Demo 程序:

    - (void)applicationWillResignActive:(UIApplication *)application
    {
        [[CoreEngine sharedInstance]willResignActiveAction];
    }

    - (void)applicationDidEnterBackground:(UIApplication *)application
    {
        [[CoreEngine sharedInstance]enterBackgroundMode];
    }

    - (void)applicationDidBecomeActive:(UIApplication *)application
    {
        [[CoreEngine sharedInstance]didBecomeActiveAction];
    }


5. 配置初始化顺序：

    可见Demo CoreEngine.m 文件

        a. 初始化 WChatSDK 实例
        b. 初始化 MediaSDK 实例
        c. 调用 (MediaSDK 实例)startWithWchatPort:(WChatSDK 实例 端口号) 方法
        d. 调用 (WChatSDK 实例)setSipMediaPort:(MediaSDK 实例 端口号) 方法
        e. Auth登录 (registerOrLoginAction 方法)

6. WChatSDK 使用文档

## 初始化&释放

    初始化sdk单例`[WChatSDK sharedInstance]`，通过该单例进行接口调用.

    释放单例`[WChatSDK purgeSharedInstance]`

## 单例调用

#### 1.线上平台初始化

    /**
    *  @brief 注册设备
    *
    *  @param appUDID        设备唯一UDID
    *  @param clientId       开放平台下发的clientID
    *  @param secret         开放平台下发的sectet
    *  @param clientDelegate 回调代理
    */
    -(void)registerApp:(NSString *)appUDID clientId:(NSString *)clientId secret:(NSString*)secret delegate:(id<WChatSDKDelegate>)clientDelegate;

#### 2.测试平台初始化

    /**
    *  @brief 测试平台, 注册设备
    *
    *  @param appUDID        设备唯一UDID
    *  @param clientId       开放平台下发的clientID
    *  @param secret         开放平台下发的sectet
    *  @param clientDelegate 回调代理
    */
    -(void)testRegisterApp:(NSString *)appUDID clientId:(NSString *)clientId secret:(NSString*)secret delegate:(id<WChatSDKDelegate>)clientDelegate;

#### 3.退出登陆
    /**
    *  @brief 登出
    *
    *  @param timeout 调用超时时间
    */
    -(void)wchatLogout:(NSTimeInterval)timeout;

#### 4.前后台切换, 关闭连接, 重连

    /**
    *  @brief 客户端回到前台, 开启服务器消息notice下发, 关闭推送 (进入前台调用)
    *
    *  @param timeout 调用超时时间
    */
    - (void)wchatKeepAlive:(NSTimeInterval)timeout;

    /**
    *  @brief 客户端退到后台, 关闭服务器消息notice下发, 开启推送 (进入后台调用)
    *
    *  @param timeout 调用超时时间
    */
    - (void)wchatPreClose:(NSTimeInterval)timeout;

    /**
    *  @brief 关闭连接
    *
    *  @param timeout 调用超时时间
    */
    - (void)wchatClose:(NSTimeInterval)timeout;

    /**
    *  @brief 重新连接
    */
    - (void)wchatReconnect;

#### 5.初始化sdk

    /**
    *  @brief 初始化sdk
    *
    *  @param cachePath      缓存目录路径, 通常为Documents
    *  @param platform       使用平台, 目前仅支持 (线上平台 OnlinePlatform , 测试平台 TestPlatform)
    *  @param channel        渠道号
    *  @param clientId       客户端id
    *  @param clientVersion  客户端版本号, 如 1.2.3
    *  @param clientLanguage 客户端语言, 如 CN , 规范见 http://en.wikipedia.org/wiki/ISO_3166-1
    *  @param aDelegate      回调代理
    *  @param errPtr         错误句柄
    *
    *  @return 是否操作成功, YES是, NO否
    */
    - (BOOL)init:(NSString *)cachePath platform:(WChatPlatform)platform channel:(NSString *)channel clientId:(NSString *)clientId version:(NSString *)clientVersion language:(NSString *)clientLanguage delegate:(id)aDelegate error:(NSError **)errPtr;


7. MediaSDK 使用文档

## 初始化&释放

    初始化sdk单例`[MediaSDK sharedInstance]`，通过该单例进行接口调用.

    释放单例`[MediaSDK purgeSharedInstance]`


#### 1.设置wchat开放的端口号
    /**
    *  wchat开放的端口号
    *
    *  @param port 端口号
    */
    -(void)startWithWchatPort:(int)port;

#### 2.单人电话
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

#### 3.接听电话
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

#### 4.挂断电话
    /**
    *  挂断电话
    */
    -(void)callTerminate;

    /**
    *  多人电话
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

    Notification 通知

    extern NSString *NotificationMediaCallIncoming;     //来电
    extern NSString *NotificationMediaCallConnected;    //来电接通
    extern NSString *NotificationMediaCallEnd;          //单人电话下，对方挂断 或 直播的时候本机来电话（live_self） 或 直播的时候主播失去连接超时
    extern NSString *NotificationMediaCallRemotePause;  //挂起(被优先级更高任务打断)
    extern NSString *NotificationMediaCallError;        //错误


8. 拨打单人电话流程：

    1. 成功初始化 WChatSDk实例、MediaSDK实例(详细见说明5)
    2. 成功登录、获取UserID(详见说明6.2)
    3. MediaSDK实例调用 callUser:from:enabelVideo:error: 方法
    4. 等待对方应答
    5. MediaSDK实例 调用方法 callTerminate 挂断电话

9. 接听单人电话流程：

    1. 成功初始化 WChatSDk实例、MediaSDK实例(详细见说明5)
    2. 成功登录、获取UserID(详见说明6.2)
    3. 监听通知 NotificationMediaCallIncoming
    4. MediaSDK实例 调用方法 callAccept: 接听电话
    5. MediaSDK实例 调用方法 callTerminate 挂断电话

10. 多人会议

    1. 成功初始化 WChatSDk实例、MediaSDK实例(详细见说明5)
    2. 成功登录、获取UserID(详见说明6.2)
    3. 加入某一个群组 MediaConferenceJoinGroupRequest实例对象
    4. 获取群成员列表 MediaConferenceFetchUsersRequest实例对象 ， 然后选择与会人员
    5. 申请房间 MediaSDK实例 conferenceRequestRoomWithGroupID: 方法，等待服务器响应
    6. 申请房间成功 MediaSDK实例 调用 callRoom:withKey:error: 方法进入房间，调用 conferenceInviteUsers:groupID:roomID:key方法向人员发出邀请，等待被邀请人相应
    7. MediaSDK实例 刷新当前参加会议的人员列表conferenceFetchUsersinRoom:groupID:
    8. MediaSDK实例 调用方法 callTerminate 挂断，离开房间, MediaSDK实例 调用方法 callAccept: 接受会议邀请

    监听通知 conferenceRoomInvite，实现监听是否又被邀请参加会议。












