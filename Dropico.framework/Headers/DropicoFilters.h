//
//  DropicoFilters.h
//
//  Created by Shai Mishali on 11/1/11.
//  Copyright (c) 2011 Dropico Media. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Dropico.h"
#import "DropicoResponse.h"

/**
 `DropicoFilters` Handles the retrieval of Filters and Filter-related data from the Dropico API Server
 */
@interface DropicoFilters : NSObject{}

///-------------------------------
/// @name Retrieving Filter Data
///-------------------------------

/**
 Get filters from the Dropico API Server
 
 @param filterCategoryID Category to fetch filters from. If omitted, all filters are returned
 @param pro Set to `YES` to include pro filters in the result
 @param etag Retrieve Filters from this specific timestamp on. When omitted, returns all filters.
 @param success Request success block - Response should include an array of `DropicoFilter` objects
 @param failure Request failure block
 
 @return An array of `DropicoFilter` objects
 */
+ (void) getFiltersFromCategory: (NSNumber *) filterCategoryID
                            pro: (BOOL) pro
                           etag: (NSNumber *) etag
                        success: (void (^)(DropicoResponse *response)) success
                        failure:(void (^)(NSURLRequest *request, DropicoResponse *response, NSError *error))failure;
/**
 Get filter categories from the Dropico API Server

 @param etag Retrieve Filter Categories from this specific timestamp on. When omitted, returns all filter categories.
 @param success Request success block - Response should include an array of `DropicoFilterCategory` objects
 @param failure Request failure block
 
 @return An array of `DropicoFilterCategory` objects
 */
+ (void) getFilterCategoriesWithEtag:(NSNumber *) etag
                             success: (void (^)(DropicoResponse *response)) success
                             failure: (void (^)(NSURLRequest *request, DropicoResponse *response, NSError *error)) failure;
/**
 Returns a string representation of a `CGBlendMode`
 
 @param code An inputted `CGBlendMode`
 
 @return A string representation for the inputted `CGBlendMode`
 */
+ (NSString*) blendModeToString:(CGBlendMode)code;

/**
 Returns a value from the CGBlendMode enumeration from a string-represented Blend Mode
 
 @param blend An inputted string-representation of a Blend Mode
 
 @return A value from the CGBlendMode enumeration
 */
+ (CGBlendMode) stringToBlendMode:(NSString *)blend;
@end