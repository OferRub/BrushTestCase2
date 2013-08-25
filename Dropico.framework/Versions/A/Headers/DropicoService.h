//
//  DropicoService.h
//
//  Created by Shai Mishali on 11/3/11.
//  Copyright (c) 2011 Dropico Media. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DropicoService : NSObject{}

@property (nonatomic, strong) NSString *label;
@property (nonatomic, strong) NSString *name;
@property (nonatomic, strong) NSURL *icon;
@property (nonatomic, strong) NSDictionary *rules;
@property (nonatomic, assign) BOOL isConnected;

@end