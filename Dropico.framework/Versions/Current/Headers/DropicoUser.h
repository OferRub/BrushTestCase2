//
//  DropicoUser.h
//
//  Created by Shai Mishali on 11/2/11.
//  Copyright (c) 2011 Dropico Media. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Dropico.h"
#import "DropicoResponse.h"

/**
 The `DropicoUser` class handles everything related to how a user is represented by the Dropico Server.
 
 It handles everything between Login/Logout , Registration of users or devices, and registration to the mailing list.
 */


@interface DropicoUser : NSObject{}

///-------------------------
/// @name Logging in/out
///-------------------------

/**
 Login to the Dropico Server with an existing user
 
 @param user User name
 @param pass Password
 @param deviceToken Device Push token
 @param success Request success block - Login was successful
 @param failure Request failure block - Login was unsuccessful, or the request to the server itself was unsuccessful

 @return A boolean login status
 */
+ (void) doLogin: (NSString *) user
    withPassword: (NSString *)pass
  andDeviceToken:(NSString *)deviceToken
         success:(void (^)(DropicoResponse *response))success
         failure:(void (^)(NSURLRequest *request, DropicoResponse *response, NSError *error)) failure;

/**
 Login to the Dropico Server with a device
 
 @warning ___Note:___ `doLoginWithDevice:success:failure:` will automatically register your device if it isn't registered to Dropico by calling `registerUserWithDevice:success:failure:`.
 
 @param device The device to login with.
 @param success Request success block - User was successfully logged in
 @param failure Request login block - Login reqest was unsuccessful
 
 @return Status of login
 */
+ (void) doLoginWithDevice: (UIDevice *) device
                   success:(void (^)(DropicoResponse *response))success
                   failure:(void (^)(NSURLRequest *request, DropicoResponse *response, NSError *error)) failure __attribute__((deprecated));

/**
 Login to the Dropico Server with a device and Device Push Token
 
 @warning ___Note:___ `doLoginWithDevice:deviceToken:success:failure:` will automatically register your device if it isn't registered to Dropico by calling `registerUserWithDevice:success:failure:`.
 
 @param device The device to login with.
 @param deviceToken Device Push token
 @param success Request success block - User was successfully logged in
 @param failure Request login block - Login reqest was unsuccessful
 
 @return Status of login
 */

+ (void) doLoginWithDevice: (UIDevice *) device
               deviceToken: (NSString *) deviceToken
                   success:(void (^)(DropicoResponse *response))success
                   failure:(void (^)(NSURLRequest *request, DropicoResponse *response, NSError *error)) failure;


/**
 Logs out of the system by clearing all of the HTTP Cookies saved on the device for the currently running app.
 
 ___Note:___ There is no need to call `[DropicoUtils clearStoredCookies]`, it is executed automatically by this method.
 */
+ (void) logout;

///--------------------------------
/// @name Registering users/devices
///--------------------------------

/**
 Register a new user
 
 @param user Username
 @param pass Password
 @param success Request success block - the user was successfully registered
 @param failure Request failure block
 
 @return Response from the Dropico Server
 */

+ (void) registerUser: (NSString *) user
         withPassword: (NSString *) pass
              success:(void (^)(DropicoResponse *response))success
              failure:(void (^)(NSURLRequest *request, DropicoResponse *response, NSError *error)) failure;

/**
 Register a new device
 
 @warning ___Note:___ There is usually no need to directly call this method, since it'll be automatically called by `doLoginWithDevice:success:failure:` if login is unsuccessful and registration is required.
 
 @param device Device to register
 @param success Request success block
 @param failure Request failure block
 
 @return Response from the Dropico Server
 
 */
+ (void) registerUserWithDevice: (UIDevice *) device
                        success:(void (^)(DropicoResponse *response))success
                        failure:(void (^)(NSURLRequest *request, DropicoResponse *response, NSError *error)) failure;

///----------------------
/// @name User Identity
///----------------------

/**
 Validate if the requested nickname is available and valid
 
 @param nickname The requested nickname
 @param success Request success block (if nickname available and has no issues)
 @param failure Request failure block (if nickname isn't avialble or is invalid)
 
 @return Response from the Dropico Server
 */
+ (void) validateNickname:(NSString *) nickname
                  success:(void (^)(DropicoResponse *response))success
                  failure:(void (^)(NSURLRequest *request, DropicoResponse *response, NSError *error)) failure;

/**
 Update the user's identity
 
 @param nickname The user's nickname (will return error if used by another user)
 @param photo URL to the user's photo
 @param success Request success block
 @param failure Request failure block
 
 @return Response from the Dropico Server
 */
+ (void) updateIdentity: (NSString *) nickname
                  photo: (NSURL *) photo
                success:(void (^)(DropicoResponse *response))success
                failure:(void (^)(NSURLRequest *request, DropicoResponse *response, NSError *error)) failure;

///----------------------
/// @name Mailing List
///----------------------

/**
 Subscribe a user to the Dropico mailing list
 
 @param email Email address to subscribe
 @param success Request success block
 @param failure Request failure block
 
 @return Response from the Dropico Server
*/
+ (void) subscribeMailing:(NSString *)email
                    success:(void (^)(DropicoResponse *response))success
                    failure:(void (^)(NSURLRequest *request, DropicoResponse *response, NSError *error)) failure;

/**
 Unsubscribe a user from the Dropico mailing list
 
 @param email Email address to unsubscribe
 @param success Request success block
 @param failure Request failure block
 
 @return Response from the Dropico Server
 **/

+ (void) unsubscribeMailing:(NSString *)email
                    success:(void (^)(DropicoResponse *response))success
                    failure:(void (^)(NSURLRequest *request, DropicoResponse *response, NSError *error)) failure;


@end