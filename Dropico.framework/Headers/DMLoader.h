//
//  DMLoader.h
//
//  Created by Shai Mishali on 4/24/12.
//  Copyright (c) 2012 Dropico Media LTD. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#import "Dropico.h"

/**
 `DMLoader` is a helpful little Progress/Activity Loader that could be displayed from any view.
 
 It is lightly based on Sam Vermette's SVProgressHUD, with added Animated Progress loader and other adjustments.
 */

@interface DMLoader : UIView

///---------------------------------------------
/// @name Configuring the Loader
///---------------------------------------------

/**
 Execute on the App Delegate launch, or any other task-safe spot. 
 Loads views and progress animation
 
 @return Nothing
 */
+ (void) prepare;

/**
 Set the font used in the loader text
 
 @param font Font used in the loader text
 
 @return Nothing
 */
+ (void) setFont: (UIFont *)font;

///---------------------------------------------
/// @name Controlling the Loader 
///---------------------------------------------
/**
 Show DMLoader without progress, without text, and with a mask.
 
 @return Nothing
 */
+ (void) show;

/**
 Show DMLoader without progress, with text, and with a mask.
 
 @param text Text to display under the loader.
 
 @return Nothing
 */
+ (void) showWithText: (NSString *) text;

/**
 Show DMLoader without either progress, text or a mask.
 
 @return Nothing
 */
+ (void) showClear;

/**
 Show DMLoader without a progress and mask, but with text.
 
 @param text Text to display under the loader.
 
 @return Nothing
 */
+ (void) showClearWithText: (NSString *) text;

/**
 Show DMLoader with a progress and mask, but without text.
 
 @return Nothing
 */
+ (void) showProgress;

/**
 Show DMLoader with a progress, mask and text.
 
 @param text Text do be displayed
 
 @return Nothing
 */

+ (void) showProgressWithText: (NSString *) text;

/**
 Show DMLoader with a progress, but without a mask or text.
 
 @return Nothing
 */
+ (void) showProgressClear;

/**
 Dismiss the currently displayed DMLoader
 
 @return Nothing
 */
+ (void) dismiss;

/**
 Set the progress value after calling either `showProgress` or `showProgressClear`, animating the progress animation.
 
 @param progress Progress of loader from 0.0 to 1.0
 
 @return Nothing
 */
+ (void) setProgress:(CGFloat)progress;

@end