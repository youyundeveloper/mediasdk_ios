//
//  MediaDefine.h
//  MediaSDK
//
//  Created by c-mbp13 on 14-9-17.
//  Copyright (c) 2014年 stylejar. All rights reserved.
//

#ifndef MediaSDK_MediaDefine_h
#define MediaSDK_MediaDefine_h

#define MediaSDKVersion     "0.3.1"

//语音质量数据
typedef struct {
    float quality;              /**<System calculate quality value */
    float download_bandwidth;   /**<Download bandwidth measurement of received stream, expressed in kbit/s, including IP/UDP/RTP headers*/
    float upload_bandwidth;     /**<Download bandwidth measurement of sent stream, expressed in kbit/s, including IP/UDP/RTP headers*/
    float local_late_rate;      /**<percentage of packet received too late over last second*/
    float local_loss_rate;      /**<percentage of lost packet over last second*/
} MediaSDKQualityData;


#endif
