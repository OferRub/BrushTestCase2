//
//  DropicoLogger.h
//
//  Created by Shai Mishali on 11/1/11.
//  Copyright (c) 2011 Dropico Media. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Dropico.h"
/**
 `DropicoLogger` is a helper class that defines the way logging works in the Dropico Framework.
 
 ## Definitions
 
 - `DropicoLog(frmt,args)` - Use to log data in any situation
 - `DropicoLogDebug(frmt,args)` - Use to log data only when Dropico.debugMode is set to YES.
 - `___log_` - Use to output the current method
 */

#define DropicoLog(frmt, ...) NSLog((@"%s [Line %d] " frmt), __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__)
#define DropicoLogDebug(frmt, ...) if([[Dropico sharedManager] debugMode]) NSLog((@"%s [Line %d] " frmt), __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__)

@interface DropicoLogger : NSObject{}

@end