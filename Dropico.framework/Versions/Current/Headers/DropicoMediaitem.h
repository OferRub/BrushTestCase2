//
//  DropicoMediaItem.h
//
//  Created by Shai Mishali on 11/20/11.
//  Copyright (c) 2011 Dropico Media. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum{
    kMediaTypePhoto,
    kMediatypeVideo
} MediaType;

typedef enum{
    kUploadStateFailed=0,
    kUploadStateAccepted=1,
    kUploadStateProcessing=2,
    kUploadStateComplete=3
} UploadState;

@interface DropicoMediaItem : NSObject{}

@property (nonatomic, strong) NSString *albumID;
@property (nonatomic, strong) NSString *mediaID;
@property (nonatomic, assign) MediaType type;
@property (nonatomic, strong) NSString *title;
@property (nonatomic, strong) NSString *description;
@property (nonatomic, strong) NSString *tags;
@property (nonatomic, strong) NSURL *mediaURL;
@property (nonatomic, strong) NSURL *thumb;
@property (nonatomic, strong) NSDictionary *meta;
@property (nonatomic, strong) NSURL *shortUrl;

@end