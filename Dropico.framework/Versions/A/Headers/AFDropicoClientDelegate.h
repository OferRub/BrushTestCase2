//
//  AFDropicoClientDelegate.h
//  Framework-iOS
//
//  Created by Shai Mishali on 7/5/12.
//  Copyright (c) 2012 Dropico Media. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DropicoResponse.h"

/**
 `AFDropicoClientDelegate` lets you know when requests start, fail or succeed and provide extra info on the global level instead of just a block statement per-request
 */
@protocol AFDropicoClientDelegate <NSObject>
@optional

/**
 Called when a request has started
 
 @param action Action used when calling the server
 @param request Request sent to the server
 */

- (void) requestDidStart: (NSString *)action request: (NSURLRequest *) request;

/**
 Called when a request finished successfully
 
 @param action Action used when calling the server
 @param response Response returned from the successful request
 
 @return Nothing
 */
- (void) requestDidSucceed:(NSString *)action withResponse: (DropicoResponse *) response;

/**
 Called when a request finished with a failure
 
 @param action Action used when calling the server
 @param error Error returned from the failed request
 @param request Request sent to the server
 @param response Response returned from the server
 
 @return Nothing
 */
- (void) requestDidFail:(NSString *)action withError: (NSError *) error request: (NSURLRequest *) request andResponse: (NSHTTPURLResponse *) response;

@end
