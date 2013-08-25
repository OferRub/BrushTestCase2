//
//  DMConcurrentURLFetcher.h
//
//  Created by Shai Mishali on 10/29/12.
//  Copyright (c) 2012 Dropico Media LTD. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AFNetworking.h"

#define CHUNKS 4

/**
 `DMConcurrentURLFetcher` downloads a file from any URL concurrently, by splitting it into multiple pieces and downloading simultaneously - Resulting in extremely fast download rates.
 */

@interface DMConcurrentURLFetcher : NSObject{}

/**
 Fetch file from the specified URL.
 The file will be downloaded simulatenously in X Chunks (defined in header. Defaults to 4 pieces)
 
 @param url URL From which to download the file
 @param success Success block called on a successful file download, Returns NSData representation of downloaded file
 @param failure Failure block called on a downloaded failure or unexpected content
 @param progress Progress block called whenever a download progress is made
 
 @return Nothing
 */
-(void)fetchWithURL:(NSURL *)url
            success:(void (^)(NSData *fileData))success
            failure:(void (^)(NSError *error))failure
           progress:(void (^)(float progress))progress;

/**
 Fetch the file previously declared by setting the `url` property manually, 
 Use this after setting successBlock, failureBlock, progressBlock and url manually.
 
 @return Nothing
 */
-(void)fetch;

/**
 Cancel the fetching operation. This would usually take a couple of moments, and won't cancel immediately. 
 
 @return Nothing;
 */
-(void)stop;

/** Success Block - Called when download was successful */
@property (nonatomic, copy)         void (^successBlock)(NSData *fileData);

/** Failure Block - Called when download has failed */
@property (nonatomic, copy)         void (^failureBlock)(NSError *error);

/** Progress Block - Called whenever there's a download progress */
@property (nonatomic, copy)         void (^progressBlock)(float progress);

/** URL - The URL of the downloaded file */
@property (nonatomic, strong)       NSURL *URL;

@end