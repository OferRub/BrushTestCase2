//
//  DropicoMessage.h
//
//  Created by Shai Mishali on 4/2/12.
//  Copyright (c) 2012 Dropico Media. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DropicoMessage : NSObject;

@property (nonatomic, assign) int mid;
@property (nonatomic, strong) NSString *name;
@property (nonatomic, strong) NSURL *url;
@property (nonatomic, assign) BOOL active;

@end