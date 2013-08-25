//
//  DMNotificationService.h
//
//  Created by Shai Mishali on 1/24/13.
//
//  DMPushService code by Shai Mishali (shai@dropico.com)
//  DMNotifier code by Nadav Nuni (nadav@dropico.com)
//
//  Copyright (c) 2013 Dropico Media. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <QuartzCore/QuartzCore.h>
#import "Dropico.h"
#import "UIWebView+Blocks.h"

/**
 `DMNotificationService` is the main communication channel between Dropico and its users.
 
 It implements and handles two different method of communication

 1. Push Notifications
 2. Local Notifications based on "Checkpoints"
 */

@interface DMNotificationService : NSObject

/**
 * Notify DMPushService the app just started launching.
 * Should be called from application:didFinishLaunchingWithOptions:
 *
 * @param launchOptions Launch Options dictionary received from application:didFinishLaunchingWithOptions:
 * @param shouldLogin Set to YES if your app needs a connection to the Dropico service, regardless of push state
 */
+ (void) didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
                            needsLogin:(BOOL)shouldLogin;

/**
 * Register for remote notifications
 * Should be called from from application:didRegisterForRemoteNotificationsWithDeviceToken:
 *
 * @param deviceToken Device Token received from device
 */
+ (void) didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken;

/**
 * Update the Dropico Server about a received push notification
 * Should be called from application:didReceiveRemoteNotification:
 *
 * @param userInfo UserInfo dictionary from application:didReceiveRemoteNotification:
 *
 * @return BOOL If this is a Dropico push, return YES - otherwise returns NO.
 */
+ (BOOL) didReceiveRemoteNotification:(NSDictionary *)userInfo;

/**
 * Updates Notifier messages from the server.
 * Should be called from applicationDidBecomeActive:
 *
 */
+ (void) didBecomeActive;

/**
 * Let DMNotificationService know you're at a certain checkpoint and display its notifications, if any are available
 *
 * @param name Name of checkpoint
 */
+ (void) checkpoint: (NSString *) name;


@end
