//
//  DropicoServices.h
//  
//  Created by Shai Mishali on 11/3/11.
//  Copyright (c) 2011 Dropico Media. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Dropico.h"
#import "DropicoResponse.h"

/**
 Enumeration to describe service-retrieval options.
 */

typedef enum {
    kServiceFilterFlagConnected,
    kServiceFilterFlagAll,
    kServiceFilterFlagReadOnly,
    kServiceFilterFlagWrite,
    kServiceFilterFlagGeo,
    kServiceFilterFlagFeed,
    kServiceFilterFlagSearch
} ServiceFilterFlag;

/**
 `DropicoServices` manages the user's connection to various social/photo-based services.
 */

@interface DropicoServices : NSObject{}

///----------------------------
/// @name Retrieving Services
///----------------------------

/**
 Retrieves a list of available services from the DropicoService.
 
 @param serviceFilter Filters the type of services fetched from the server according to the ServiceFilterFlag enumeration, mandatory
 @param success Success handler - Request success block, Response should contain an array of DropicoService objects
 @param failure Failure handler - Request failure block
 
 @return On success, Response should contain an array of DropicoService objects
 */

+ (void) getServices: (ServiceFilterFlag) serviceFilter
             success: (void (^)(DropicoResponse *response)) success
             failure: (void (^)(NSURLRequest *request, DropicoResponse *response, NSError *error)) failure;

/**
 Helper method to return a string value for a specific ServiceFilterFlag enumeration value.
 
 Internally Used by the `getServices:success:failure` method.
 
 @param serviceFilter Value you wish to get a string representation of
 
 @return An NSString representation of the inputted ServiceFilterFlag enumeration value
 */

+ (NSString *) serviceFlagToString:(ServiceFilterFlag)serviceFilter;

///--------------------------------------------
/// @name Handling authentication to services
///--------------------------------------------

/**
 Returns a special URL to be used for authentication to the target service
 
 @param service The service you wish to authenticate to
 @param success Request success block - Response should be an NSURL object including the special URL you should redirect the user to
 @param failure Request Failure block - Reuest failed block
 
 @return On success, Response should be an NSURL object including the special URL you should redirect the user to
 */

+ (void) getAuthURLForService:(NSString *)service
                     success: (void (^)(DropicoResponse *response)) success
                     failure: (void (^)(NSURLRequest *request, DropicoResponse *response, NSError *error)) failure;

/**
 Returns the auth base for the requested service.
 
 Used to perform NSRange tests during authentication to indicate if you're still authenticating or not.
 
 @param service Service to get a auth base for
 
 @return Auth base for specific service
 */
+ (NSString *) getAuthBaseForService:(NSString *)service;

///--------------------------------------------------
/// @name Handling existing connections to services
///--------------------------------------------------

/**
 Check the status of a connection to a specific service
 
 @param service Service to test the connection for
 @param success Request success block - Response should include a `DropicoPerson` with the details of the connected person if the connection was available, or an NSNumber with a bool value if the connection is not available
 @param failure Request failure block - Reuest failed block
 
 @return On success, a `DropicoPerson` object with the details of the connected person if the connection was available, or an `NSNumber` object with a `BOOL` value if the connection is not available
 */
+ (void) getConnectionToService:(NSString *)service
                      success: (void (^)(DropicoResponse *response)) success
                      failure: (void (^)(NSURLRequest *request, DropicoResponse *response, NSError *error)) failure;

/**
 Disconect a user from a specific service
 
 @param service Service to disconnect
 @param success Request success block
 @param failure Request failure block
 
 @return The output from the DropicoAPI server, should always be `YES` since a disconnection is irrelevant to the current connection status of the user to the service
 */
+ (void) disconnectService:(NSString *)service
                   success: (void (^)(DropicoResponse *response)) success
                   failure: (void (^)(NSURLRequest *request, DropicoResponse *response, NSError *error)) failure;

/**
 Disconnect a user from all his currently-connected services
 
 @param success Request success block
 @param failure Request failure block
 
 @return The output from the DropicoAPI server, should always be `YES` since a disconnection is irrelevant to the current connection status of the user to the services
 */
+ (void) destroyAllConnectionsWithSuccess: (void (^)(DropicoResponse *response)) success
                                  failure: (void (^)(NSURLRequest *request, DropicoResponse *response, NSError *error)) failure;

///---------------------------------------
/// @name Retrieving data from services
///---------------------------------------

/**
 Retrieve all of the users' friends from a specific service.
 
 @warning ___Note:___ This function currently ___only supports Facebook___.
 
 ___Note 2:___ If startFrom and/or numItems are omitted, all friend records will be retrieved.
 
 @param service Service name to retrieve friends from
 @param startFrom The index from which to start the retrieval
 @param numItems The number of items to retrieve from startFrom
 @param params Any additional custom parameters you wish to send to the server
 @param success Request success block
 @param failure Request failure block
 
 @return On success, Respnse should incude an array of DropicoPerson objects
 */
+ (void) getSocialFriends: (NSString *)service
                startFrom: (NSNumber *) startFrom
                 numItems: (NSNumber *) numItems
                   params:(NSDictionary *)params
                  success:(void (^)(DropicoResponse *response))success
                  failure:(void (^)(NSURLRequest *request, DropicoResponse *response, NSError *error))failure;


@end