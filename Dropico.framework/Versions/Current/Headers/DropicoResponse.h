//
//  DropicoResponse.h
//
//  Created by Shai Mishali on 11/1/11.
//  Copyright (c) 2011 Dropico Media. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DropicoResponse : NSObject{}

@property (nonatomic) uint code;
@property (nonatomic, strong) id response;
@property (nonatomic) float time;

@end