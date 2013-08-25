//
//  Dropico.h
//
//  Created by Shai Mishali on 11/1/11.
//  Copyright (c) 2011 Dropico Media. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <QuartzCore/QuartzCore.h>
#import <CoreLocation/CoreLocation.h>
#import "Reachability.h"

// Libraries
#import "DropicoLogger.h"
#import "AFDropicoClient.h"
#import "UIDevice+IdentifierAddition.h"
#import "NSObject+Extras.h"
#import "UIView+Positioning.h"
#import "UIWebView+Blocks.h"
#import "UIAlertView+MKBlockAdditions.h"

// Classes
#import "DropicoUser.h"
#import "DropicoServices.h"
#import "DropicoMedia.h"
#import "DropicoFilters.h"
#import "DropicoFeeds.h"
#import "DropicoGeo.h"
#import "DropicoUtils.h"
#import "DropicoMessages.h"
#import "DMLoader.h"
#import "DMConcurrentURLFetcher.h"
#import "DMNotificationService.h"
#import "DMSupportForm.h"

// Data Models
#import "DropicoResponse.h"
#import "DropicoPerson.h"
#import "DropicoFilter.h"
#import "DropicoFilterLayer.h"
#import "DropicoFilterCategory.h"
#import "DropicoService.h"
#import "DropicoFeedItem.h"
#import "DropicoVenue.h"
#import "DropicoAlbum.h"
#import "DropicoMediaitem.h"
#import "DropicoMessage.h"
#import "DropicoNotification.h"
#import "DropicoNotificationCheckpoint.h"

#define _userDefaults [NSUserDefaults standardUserDefaults]
#define _sharedDropico [Dropico sharedManager]
/**
 `Dropico` is the main class in `Dropico.framework`.
 
 v1.1 (Oct 30th, 2012)
 
 It makes sure everything needed is imported and lets you initialize the user's connection to the Dropico API Server.   
 
 @warning *Important:* You must call initDropicoWithApp: before calling any other Dropico classes

 ## Important definitions
 - `_userDefauls` is a short-hand macro to bring the standard NSUserDefaults object
 - `_sharedDropico` is a short-hand macro to bring the shared Dropico singleton object
 */

@class Reachability;

@interface Dropico : NSObject{}

///---------------------------------------
/// @name Properties
///---------------------------------------

/**
 Set whether or not to be on Debug mode. Set to YES to get Debug-logs and make sure push tokens are set to sandbox, default is YES.
 */
@property (assign) BOOL debugMode;
/**
 Set a block method to get notified whenever the internet connectivity status changes.
 */
@property (nonatomic, copy) void (^onInternetStatusChange)(BOOL);
/**
 Set a block method to get notified whenever a request failed because of server maintenance.
 */
@property (nonatomic, copy) void (^onMaintenance)();
/**
 Whether or not the client has valid Internet Connectivity.
 */
@property (nonatomic, assign) BOOL isReachable;
/**
 Latest internet status retrieved from reachability
 */
@property (nonatomic, assign) NetworkStatus networkStatus;
/**
 Private cache used to store data needed for the current living session.
 */
@property (nonatomic, strong) NSMutableDictionary *privateCache;
/**
 Whether or not calls to the API should be performed via Secure Sockets Layer over HTTPS (SSL), Defaults to YES
 */
@property (nonatomic, assign) BOOL withSSL;

///--------------------------------------------
/// @name Working with the Dropico API Server
///--------------------------------------------

/**
 Returns a Shared Dropico object
 
 @return a Shared Singleton Dropico object
 */
+ (id) sharedManager;

/**
 Initializes the connection to the Dropico API server.
 
 ___Note:___ This method must be called before calling any other Dropico class or method.
 
 @param appName The name of the application requesting access to the Dropico API
 
 */
+ (void) initDropicoWithApp:(NSString *)appName;

/**
 Return if this is the first one of the current app
 */
+ (BOOL) isFirstRun;
@end