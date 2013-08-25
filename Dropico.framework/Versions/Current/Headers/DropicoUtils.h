//
//  DropicoUtils.h
//
//  Created by Shai Mishali on 11/2/11.
//  Copyright (c) 2011 Dropico Media. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CommonCrypto/CommonDigest.h>
#import "NSData+Base64.h"
#import "Dropico.h"
#import "ZipArchive.h"

#pragma mark - General usage Macros
#define NSApplicationSupportDir [[NSSearchPathForDirectoriesInDomains(NSApplicationSupportDirectory, NSUserDomainMask, YES) lastObject] stringByAppendingPathComponent:[[NSBundle mainBundle] bundleIdentifier]]

#define NSCachesDir [NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) lastObject]

#define canOpenURL(urlString)   [[UIApplication sharedApplication] canOpenURL: [NSURL URLWithString: urlString]]
#define openURL(urlString)      [[UIApplication sharedApplication] openURL: [NSURL URLWithString: urlString]]
#define strToURL(urlString)     [NSURL URLWithString: urlString]

#pragma mark - Math Macros
#define degreesToRadians(degrees) ((degrees * M_PI) / 180.0)
#define P(x,y) CGPointMake(x, y)

#pragma mark - String Macros
#define isEmptyString(_var) (_var == nil || [[_var stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]] isEqualToString:@""])
#define stringsEqual(s1, s2) [s1 isEqualToString: s2]

#pragma mark - NSUserDefaults Macros

#define getDefaultsObject(key)  [[NSUserDefaults standardUserDefaults] objectForKey: key]
#define getDefaultsValue(key)   [[NSUserDefaults standardUserDefaults] valueForKey: key]

#define setDefaultsObject(key, object){\
                [[NSUserDefaults standardUserDefaults] setObject:object forKey:key];\
                [[NSUserDefaults standardUserDefaults] synchronize];\
                }

#define removeDefaultsObject(key)     [[NSUserDefaults standardUserDefaults] removeObjectForKey: key]

/**
 `DropicoUtils` is a general utility class that includes methods for a variety of different usages.
 
 ## Some definitions that matter
 This class includes the following macros:
 
 - `degreesToRadians(degrees)` - Returns a Radian value for the inputted Degree value
 - `P(x,y)` - A shorthand call to `CGPointMake`
 - `isEmptyString(string)` - Tests if an `NSString` object is either `nil` or empty
 - `NSCachesDir` -  A macro defining the _Caches_ directory of the app, used to save non-iCloud _or_ temporary files on device
 */

@interface DropicoUtils : NSObject{}


#pragma mark - Encryption Functions
///----------------------------
/// @name Encryption Methods
///----------------------------

/**
 Returns a MD5 Encoded representation of a inputted string
 
 @param string Input string for encryption
 
 @return MD5 Encoded representation of inputted string
 */
+ (NSString *)MD5Encode:(NSString *)string;

/**
 Returns a SHA1 Encoded representation of a inputted string
 
 @param string Input string for encryption
 
 @return SHA1 Encoded representation of inputted string
 */
+ (NSString *)SHA1Encode:(NSString *)string;

/**
 Returns a Base 64 Encoded representation of a inputted string
 
 @param string Input string for encryption
 
 @return Base 64 Encoded representation of inputted string
 */
+ (NSString *)Base64Encode:(NSString *)string;

#pragma mark - Cookie management

///-------------------------
/// @name Cookie management
///-------------------------

/**
 Clears all HTTP Cookies stored on the device for the currently running app
 */
+ (void) clearStoredCookies;

#pragma mark - Zip Functions

///--------------------------------------
/// @name ZIP Archive Handling Functions
///--------------------------------------

/**
 Create a new ZIP Archive
 
 @param zipFile Name of the new ZIP archive
 
 @return BOOL for success/failure
 */
+ (BOOL) ZIPCreateFile: (NSString *) zipFile;

/**
 Create a new password-protected ZIP Archive
 
 @param zipFile Name of the new ZIP archive
 @param password Password to encrypt the ZIP archive with
 
 @return BOOL for success/failure
 */
+ (BOOL) ZIPCreateFile: (NSString *) zipFile withPassword: (NSString *) password;

/**
 Add file to an existing ZIP Archive
 
 @param zipFile Name of ZIP Archive to add file to
 @param newFile Name of file to add to the ZIP Archive
 
 @return BOOL for success/failure
 */
+ (BOOL) ZIPAddFile: (NSString *) zipFile newFile:(NSString *) newFile;

/**
 Open a stream to a specified ZIP Archive
 
 @param zipFile Name of ZIP Archive to open
 
 @return BOOL for success/failure
 */
+ (BOOL) ZIPExtractOpen: (NSString *) zipFile;

/**
 Open a stream to a specified password-protected ZIP Archive
 
 @param zipFile Name of ZIP Archive to open
 @param password Password of the protected ZIP Archive
 
 @return BOOL for success/failure
 */
+ (BOOL) ZIPExtractOpen: (NSString *) zipFile withPassword: (NSString *) password;

/**
 Extract the contents of a ZIP stream previously opened with either `ZIPExtractOpen:` or `ZIPExtractOpen:withPassword`
 
 @param path Path to extract the ZIP Archive to
 @param overwrite Set to `YES` to overwrite existing files
 
 @return BOOL for success/failure
 */
+ (BOOL) ZIPExtractTo: (NSString *) path overwrite: (BOOL) overwrite;

/**
 Close a ZIP stream previously opened with wither `ZIPExtractOpen:` or `ZIPExtractOpen:withPassword`
 
 @return BOOL for success/failure
 */
+ (BOOL) ZIPExtractClose;


#pragma mark - General Utils

///----------------------
/// @name General Utils
///----------------------

/**
 Returns a general-purpose loader that can be used in any view. 
 
 The loader is automatically positioned in the center of the inputted `view`.
 
 @param view View to add the loader to. The loader will be positioned in the center of this view
 @param string String to display in the loader (e.g. "Please Wait")
 
 @return A general-purpose loader that can be used in any view. 
 */
+ (UIView *) addLoaderToView:(UIView *)view withString:(NSString *)string;

/**
 Gets the string representation of the current device.
 
 Returns one of the following values:
    iPhone 2G
    iPhone 3G
    iPhone 3GS
    iPhone 4 (GSM)
    iPhone 4
    iPhone 4 (CDMA)
    iPhone 4S
    iPhone 5
    iPhone 5 (GSM+CDMA)
    iPod Touch (1st Gen)
    iPod Touch (2nd Gen)
    iPod Touch (3rd Gen)
    iPod Touch (4th Gen)
    iPod Touch (5th Gen)
    iPad
    iPad 3G
    iPad 2 (WiFi)
    iPad 2 (GSM)
    iPad 2 (CDMA)
    iPad 2
    iPad Mini (WiFi)
    iPad Mini
    iPad Mini (GSM+CDMA)
    iPad 3 (WiFi)
    iPad 3 (GSM+CDMA)
    iPad 3
    iPad 4 (WiFi)
    iPad 4
    iPad 4 (GSM+CDMA)
    Simulator
 
 @return NSString Device type
 */
+ (NSString *) deviceType;

/**
 Gets the installed iOS version on the device
 
 @return NSString Device version
 */

+ (NSString *) deviceVersion;

/**
 Set a value for a specific key in the User Defaults
 
 @param value Value to be set
 @param key Key for which the value will be saved
 
 @return Nothing
 */
+ (void) setDefaultsValue:(id)value forKey:(NSString *)key;

/**
 Get the value for a specific key in the User Defaults
 
 @param key Key for which to return a value
 
 @return Value for specificied key
 */
+ (id) getDefaultsValueForkey: (NSString *)key;

/**
 Remove the entry for a specific key in the User Defaults
 
 @param key Key for which to remove the entry
 
 @return Nothing
 */
+ (void) removeDefaultsValueForKey: (NSString *)key;

/**
 Returns whether device has a Retina display or not
 
 @return `YES` for Retina Display enabled device, `NO` otherwise.
 */
+ (BOOL) deviceHasRetina;

/**
 Transform view to fit current device orientation
 
 @param theView The view that needs rotation adjustment
 */

+ (void) rotateToOrientation:(UIView *)theView;

@end