//
//  DropicoNotification.h
//
//  Created by Shai Mishali on 1/24/13.
//  Copyright (c) 2013 Dropico Media. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DropicoUtils.h"

typedef enum{
    kNotificationTypePush,
    KNotificationTypeNotifier
} kNotificationType;

typedef enum{
    kNotificationActionOpenAppPromo,
    kNotificationActionOpenURL,
    kNotificationActionOpenAppStore,
    kNotificationActionOpenReview,
    kNotificationActionOpenInstagramUser,
    kNotificationActionOpenInstagramMedia,
    kNotificationActionOpenInstagramTag
} kNotificationAction;

@interface DropicoNotification : NSObject{}

@property (nonatomic, strong, readonly) NSString    *id;
@property (nonatomic, assign) kNotificationAction   action;
@property (nonatomic, strong) id                    value; // Notification value (URL/AppStore ID)
@property (nonatomic, assign) kNotificationType     type;
@property (nonatomic, strong) NSString              *message;
@property (nonatomic, assign) BOOL                  once;
@property (nonatomic, strong) NSString              *app;

+(NSString *) typeToString: (kNotificationType) type;
+(NSString *) actionToString: (kNotificationAction) action;
+(kNotificationAction)stringToAction:(NSString *) strAct;
@end