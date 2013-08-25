//
//  DropicoFilter.h
//
//  Created by Shai Mishali on 11/3/11.
//  Copyright (c) 2011 Dropico Media. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DropicoFilterLayer.h"

@interface DropicoFilter : NSObject{}

@property (nonatomic, strong) NSNumber *fid;
@property (nonatomic, strong) NSNumber *fcid;
@property (nonatomic, strong) NSString *alias;
@property (nonatomic, strong) NSString *name;
@property (nonatomic, strong) NSString *desc;
@property (nonatomic, strong) NSNumber *downloads;
@property (nonatomic, assign) BOOL isPro;
@property (nonatomic, assign) BOOL isNew;
@property (nonatomic, strong) NSURL *packageURL;
@property (nonatomic, strong) NSURL *previewURL;
@property (nonatomic, strong) NSNumber *etag;
@property (nonatomic, strong) NSArray *layers;

-(id)initWithName:(NSString *)aName alias:(NSString *)aAlias fid:(uint)aFid fcid:(uint)aFcid andLayers:(NSArray *)aLayers;

@end