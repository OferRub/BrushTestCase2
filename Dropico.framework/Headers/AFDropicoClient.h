//
//  AFDropicoClient.h
//
//  Created by Shai Mishali on 11/1/11.
//  Copyright (c) 2011 Dropico Media. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Dropico.h"
#import "DropicoResponse.h"
#import "AFDropicoClient.h"
#import "AFNetworking.h"
#import "AFDropicoClientDelegate.h"

#define API_BASE @"api.dropico.com"
#define API_SUCCESS_CODE 200 
#define API_MAINTENANCE 666
#define DROPICO_APP_NAME [[AFDropicoClient sharedClient] _appName]
#define raiseNoAppException [NSException raise:@"Dropico was not initialized" format:@"Please call [Dropico initDropicoWithApp] before calling any APIs."]

/**
 `AFDropicoClient` is a thin wrapper around AFNetworking's `AFHTTPClient`
 
 It was designed to create an easy approach for sending data to and getting data from the Dropico API server
 
 ## Some definitions that matter
 - `API_BASE` includes the path to the Dropico API server.
 - `API_SUCCESS_CODE` includes an HTTP 200 OK Success code to test in incoming data.
 - `API_MAINTENANCE` is returned by failure blocks in classes and means the Dropico API Server is currently under maintenance.
 - `DROPICO_APP_NAME` is a macro which returns the name of the application sent in `[Dropico initDropicoWithApp:]`.
 - `raiseNoAppException` is a macro used to throw an exception in case `[Dropico initDropicoWithApp:]` wasn't executed before calling any other Dropico class.
 */

@interface AFDropicoClient : AFHTTPClient{
    NSString *_appName;
}

///---------------------------------------------
/// @name Communicating with the API Server
///---------------------------------------------

/**
 The application name sent to `[Dropico initDropicoWithApp:]` before using any API
 */
@property (nonatomic, strong) NSString *_appName;

/**
 The cookie returned from the login method
 */
@property (nonatomic, strong) NSHTTPCookie *_cookie;

/**
 Dropico Client Delegate
 */

@property (unsafe_unretained) id<AFDropicoClientDelegate> delegate;

/**
 Returns a shared Singleton object of `AFDropicoClient`
 
 @return A Shared Singleton object of `AFDropicoClient`
 */
+ (AFDropicoClient *)sharedClient;

/**
 Send a simple POST request to the Dropico API Server and get a response
 
 @param action Action to call for at the API Server
 @param parameters Parameters to send to the specific action
 @param success Request success block - Response is a `DropicoRespone` object including the `response` (response data) , `code` (respone code) and `time` (time it took to execute the request)
 @param failure Request failure block - error includes a `NSLcalizedDescription` with the error message from the server
 
 @return A `DropicoRespone` object including the `response` (response data) , `code` (respones code) and `time` (time it took to execute the request)
 */
- (void) fetchAPIWithAction:(NSString *) action
                              andParams:(NSDictionary *)parameters
                                success:(void (^)(DropicoResponse *response))success 
                                failure:(void (^)(NSURLRequest *request, DropicoResponse *response, NSError *error))failure;

/**
 Upload a file to the Dropico API Server
 
 @param action Action to call for at the API Server
 @param fileKey POST field key to send file on
 @param fileName Name of the file uploaded
 @param fileData `NSData` object containing the contents of the file to be uploaded
 @param fileMimeType Mime Type of the uploaded file
 @param progressCallback A block function which is being called on every update to the proress of the upload.
    - `bytesWritten` - Number of bytes written in the current chunk
    - `totalBytesWritten` - Total bytes written to the server so far
    - `totalBytesExpectedToWrite` - Total bytes expected to be written to the server (Actually, the file size)
 @param parameters Extra parameters to send to the API for the upload request
 @param success Request success block - Response is a `DropicoRespone` object including the `response` (response data) , `code` (respones code) and `time` (time it took to execute the request)
 @param failure Request failure block - error includes a `NSLcalizedDescription` with the error message from the server
 
 @return A `DropicoRespone` object including the `response` (response data) , `code` (respones code) and `time` (time it took to execute the request) 
 */
- (void) uploadToAPIWithAction:(NSString *)action
                       fileKey:(NSString *)fileKey
                      fileName:(NSString *)fileName
                      fileData:(NSData *)fileData
                  flleMimeType:(NSString *)fileMimeType
        uploadProgressCallback:(void (^)(NSUInteger bytesWritten, long long totalBytesWritten, long long totalBytesExpectedToWrite))progressCallback
                     andParams:(NSDictionary *)parameters
                       success:(void (^)(DropicoResponse *response))success 
                       failure:(void (^)(NSURLRequest *request, DropicoResponse *response, NSError *error))failure;

@end