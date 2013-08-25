//
//  NSObject+Extras.h
//
//  Created by Shai Mishali on 12/6/11.
//  Copyright (c) 2011 Dropico Media. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 An extension for `NSObject` which provides extra functionality
 */

@interface NSObject (Extras){}

/**
 Perform a block after a specifc delay
 
 @param block A block function to perform
 @param delay A delay to run the block after
 */
- (void)performBlock:(void (^)(void))block afterDelay:(NSTimeInterval)delay;

/**
 Perform a block in a background thread
 
 @param block A block function to perform
 */
- (void)performBackgroundBlock:(void (^)(void))block;

@end