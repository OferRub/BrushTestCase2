//
//  DropicoAlbum.h
//
//  Created by Shai Mishali on 11/15/11.
//  Copyright (c) 2011 Dropico Media. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DropicoAlbum : NSObject{}

@property (nonatomic, strong) NSString *id;
@property (nonatomic, strong) NSString *title;
@property (nonatomic, strong) NSString *description;
@property (nonatomic, strong) NSNumber *mediaItemsCount;
@property (nonatomic, strong) NSURL *thumb;
@property (nonatomic, strong) NSString *service;

@end
