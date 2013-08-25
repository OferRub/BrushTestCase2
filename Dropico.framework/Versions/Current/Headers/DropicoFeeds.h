//
//  DropicoFeeds.h
//
//  Created by Shai Mishali on 11/9/11.
//  Copyright (c) 2011 Dropico Media. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Dropico.h"
#import "DropicoFeedItem.h"

#define FEATURED_PICOFTHEDAY
#define FEATURED_REGULAR

/**
 `DropicoFeeds` handles retrieval of media from various sources (either Social services or Personal content).
 
 ## Retreiving Different Media Sizes
 Each feed item will usually include media in three sizes (Small, Medium, Large), as defined in the FeedMediaSize enumeration.
 In order to get the object needed, use objectAtIndex with the appropriate enumeration key for the "media" item of DropicoFeedItem.
 */

@interface DropicoFeeds : NSObject{}

///----------------------
/// @name Feed Retrieval
///----------------------

/**
 Get a unified photo feed from different services
 
 @param services An array containing the services to be included in the photo feed
 @param success Request success block - Response should include an array of `DropicoFeedItem` objects
 @param failure Request failure block
 
 @return An array of `DropicoFeedItem` objects
 */
+ (void) getSocialPhotoFeedForServices:(NSArray *)services
                               success:(void (^)(DropicoResponse *response))success
                               failure:(void (^)(NSURLRequest *request, DropicoResponse *response, NSError *error))failure;

/**
 Get all the photos uploaded by the currently logged in user. 
 WARNING: This method has been deprecated. Please use getUserFeed:etag:limit:success:failure: instead.
 
 @param etag Retrieve feed items from this specific timestamp on. When omitted, returns all feed items.
 @param success Request success block - Response should include an array of `DropicoFeedItem` objects
 @param failure Request failure block
 
 @return An array of `DropicoFeedItem` objects
 */
+ (void) getMyPhotoFeedWithEtag:(NSNumber *) etag
                        success:(void (^)(DropicoResponse *response))success
                        failure:(void (^)(NSURLRequest *request, DropicoResponse *response, NSError *error))failure __deprecated;

/**
 Get all the photos uploaded buy the specified user.
 If no user has been specified, defaults to the currently logged in user.
 
 @param dropicoID The Dropico ID of the specified user. If omitted, the current user's Dropico ID will be used.
 @param etag Retrieve feed items from this specific timestamp on. When omitted, returns all available feed items.
 @param limit Limit the amount of results retrieved (Defaults to 25).
 @param success Request success block - Response should include an array of `DropicoFeedItem` objects.
 @param failure Request failure block.
 
 @return An array of `DropicoFeedItem` objects
 */
+ (void) getUserFeed:(NSString *) dropicoID
                etag:(NSNumber *) etag
               limit:(NSNumber *) limit
             success:(void (^)(DropicoResponse *response))success
             failure:(void (^)(NSURLRequest *request, DropicoResponse *response, NSError *error))failure;

/**
 Get a live feed of the latest uploads across the Dropico Network
 
 @param services An array containing the services to be included in the live feed (Defaults to all services)
 @param limit Limit the amount of results (Default is 50)
 @param success Request success block - Response should include an array of `DropicoFeedItem` objects
 @param failure Request failure block
 
 @return An array of `DropicoFeedItem` objects
**/
+ (void) getLiveFeedForServices:(NSArray *)services
                          limit:(NSNumber *)limit
                        success:(void (^)(DropicoResponse *response))success
                        failure:(void (^)(NSURLRequest *request, DropicoResponse *response, NSError *error))failure;

/**
 Get the featured Feed
 
 @param etag Retrieve feed items from this specific timestamp on. When omitted, returns all feed items.
 @param success Request success block - Response should include an array of `DropicoFeedItem` objects
 @param failure Request failure block
 
 @return An array of `DropicoFeedItem` objects
 **/
+ (void) getFeaturedFeedWithEtag: (NSNumber *)etag
                         success:(void (^)(DropicoResponse *response))success
                         failure:(void (^)(NSURLRequest *request, DropicoResponse *response, NSError *error))failure;

/**
 Get the global featured items
 
 @param success Request success block - Response should include an array of `DropicoFeedItem` objects
 @param failure Request failure block
 
 @return An array of `DropicoFeedItem` objects
 **/
+ (void) getFeaturedItemsWithSuccess:(void (^)(DropicoResponse *))success
                         failure:(void (^)(NSURLRequest *, DropicoResponse *, NSError *))failure;

@end