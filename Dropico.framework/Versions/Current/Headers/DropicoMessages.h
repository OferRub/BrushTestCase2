//
//  DropicoMessages.h
//
//  Created by Shai Mishali on 4/2/12.
//  Copyright (c) 2012 Dropico Media. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Dropico.h"
#import "DropicoMessage.h"

#define kDropicoReadMessages @"kDropicoReadMessages"

/**
 `DropicoMessages` handles retreival of Messages from the Dropico Service
 */
@interface DropicoMessages : NSObject{}

///----------------------------
/// @name Retreiving Messages
///----------------------------

/**
 Get messages from the server
 
 @param success Request success block - Response should include an array of `DropicoAlbum` objects
 @param failure Request failure block
 
 @return An array of `DropicoMessage` objects
 */

+ (void) getMessagesWithSuccess: (void (^)(DropicoResponse *response))success
                     andFailure: (void (^)(NSURLRequest *request, DropicoResponse *response, NSError *error))failure;

/**
 Get unread messages from the server
 
 @param success Request success block - Response should include an array of `DropicoAlbum` objects
 @param failure Request failure block
 
 @return An array of `DropicoMessage` objects
 */

+ (void) getUnreadMessagesWithSuccess: (void (^)(DropicoResponse *response))success
                           andFailure: (void (^)(NSURLRequest *request, DropicoResponse *response, NSError *error))failure;

/**
 Mark a message as read for the current user
 
 @param msg Message to be marked as read
 
 @return Nothing
 */
+ (void) markAsRead: (DropicoMessage *) msg;

/**
 Return whether a message was read by the current user
 
 @param msg Message to check reading status for
 
 @return BOOL YES if message was read, NO otherwise
 */
+ (BOOL) wasMessageRead: (DropicoMessage *) msg;

@end
