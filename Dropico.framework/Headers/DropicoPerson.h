//
//  DropicoPerson.h
//
//  Created by Shai Mishali on 11/8/11.
//  Copyright (c) 2011 Dropico Media. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DropicoPerson : NSObject{}

@property (nonatomic, strong) NSString *id;
@property (nonatomic, strong) NSString *dropicoID;
@property (nonatomic, strong) NSDictionary *serviceInfo;
@property (nonatomic, strong) NSString *name;
@property (nonatomic, strong) NSURL *thumb;
@property (nonatomic, strong) NSURL *profileURL;
@property (nonatomic, assign) BOOL isFriend;

@end