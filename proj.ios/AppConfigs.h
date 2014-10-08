//
//  AppConfigs.h
//  AdsPopupDemo
//
//  Created by tang.wei on 13-12-13.
//  Copyright (c) 2013年 tang.wei. All rights reserved.
//

/*************************** MoPub账号设置 **************************/

#define IPHONE_BANNER_ID         @"57650908df994eeb8f5cf9f49dcc7ebc"
#define IPHONE_FULLSCREEN_ID     @"d123260417904b8093de54f14f83c53e"

#define IPAD_BANNER_ID           @"be721de817c44e229f46f4f26e0b70fd"
#define IPAD_FULLSCREEN_ID       @"6ee6d83c83d146628550c69794d5e82a"

#define IPHONE_FULLSCREEN_ID_CROSSPROMO   @"c3845b2df38e4324a9c4f74a8c5bfef9"
#define IPAD_FULLSCREEN_ID_CROSSPROMO     @"a6a3903e12ed47efb66d03c752dfaa06"
// 方块广告，如果不需要支持可以留空
#define IPHONE_MEDIUM_RECT_ID    @""
#define IPAD_MEDIUM_RECT_ID      @""

// Chartboost账号，如果不需要支持开启chartboost会话，可以留空
#define CHARTBOOST_APP_ID        @""
#define CHARTBOOST_APP_SIGNATURE @""

/*************************** Flurry账号 ****************************/
// 如果留空不设置，那么表示不支持Flurry
#define FLURRY_KEY               @"FZJ9BQJCVRJWDRF8ZC3B"

/*************************** Privacy Page设置 ****************************/
// 如果留空默认为http://www.xxx.com/privacy.html, 其中xxx为bundle id中间部分
#define PRIVACY_PAGE_URL         @""