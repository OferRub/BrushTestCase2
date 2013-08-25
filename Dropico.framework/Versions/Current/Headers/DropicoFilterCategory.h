//
//  DropicoFilterCategory.h
//
//  Created by Shai Mishali on 11/3/11.
//  Copyright (c) 2011 Dropico Media. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DropicoFilterCategory : NSObject{}

@property (nonatomic, strong) NSNumber *fcid;
@property (nonatomic, strong) NSString *alias;
@property (nonatomic, strong) NSString *name;
@property (nonatomic, strong) NSURL *icon;
@property (nonatomic, strong) NSNumber *etag;

@end
