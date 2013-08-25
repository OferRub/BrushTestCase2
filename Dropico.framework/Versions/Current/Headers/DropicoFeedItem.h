//
//  DropicoFeedItem.h
//
//  Created by Shai Mishali on 11/9/11.
//  Copyright (c) 2011 Dropico Media. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Dropico.h"
#import "DropicoFeeds.h"
#import "DropicoPerson.h"

typedef enum {
    kPersonalFeedSourceAll,
    kPersonalFeedSourceFriends,
    kPersonalFeedSourceShare
} PersonalFeedSource;

typedef enum{
    kFeedTypePhoto,
    kFeedTypeVideo
} FeedType;

typedef enum{
    kFeaturedNone=0,
    kFeaturedRegular=1,
    kFeaturedPicOfTheDay=2
} FeaturedType;

typedef enum{
    kFeedMediaSizeLarge,
    kFeedMediaSizeMedium,
    kFeedMediaSizeSmall
} FeedMediaSize;


@interface DropicoFeedMedia : NSObject {}
@property (nonatomic, assign) FeedMediaSize     sizeType;
@property (nonatomic, assign) CGSize            size;
@property (nonatomic, strong) NSURL             *url;
@end

@interface DropicoFeedItem : NSObject{}

@property (nonatomic, strong) NSString          *service;
@property (nonatomic, assign) FeedType          type;
@property (nonatomic, strong) NSString          *title;
@property (nonatomic, strong) NSDate            *date;
@property (nonatomic, strong) NSArray           *media;
@property (nonatomic, strong) NSURL             *feedURL;
@property (nonatomic, strong) DropicoPerson     *owner;
@property (nonatomic, assign) FeaturedType      featured;
@property (nonatomic, assign) PersonalFeedSource source;
@property (nonatomic, strong) NSString          *app;
@property (nonatomic, strong) NSDictionary      *venue;


- (DropicoFeedMedia *) getMediaForSize: (FeedMediaSize) mediaSize;

@end
