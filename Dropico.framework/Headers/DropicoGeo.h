//
//  DropicoGeo.h
//
//  Created by Shai Mishali on 11/14/11.
//  Copyright (c) 2011 Dropico Media. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Dropico.h"

/**
 `DropicoGeo` handles all communication related to Geographic Location and Venues in front of the Dropico Server.
 */

@interface DropicoGeo : NSObject{}

///------------------------
/// @name Getting Venues
///------------------------

/**
 Get nearby venues
 
 @param location A `CLLocation` object containing the user's geographic coordinates
 @param limit Limit the amount of results returned, defults to 50
 @param filter Filter the results by a specific string
 @param success Request success block - Response should include an array of `DropicoVenue` objects
 @param failure Request failure block
 
 @returns An array of `DropicoVenue` objects
 */
+ (void) getNearbyVenues: (CLLocation*) location
                   limit:(NSNumber*)limit
                  filter:(NSString*)filter
                 success:(void (^)(DropicoResponse *response))success
                 failure:(void (^)(NSURLRequest *request, DropicoResponse *response, NSError *error))failure;

@end
