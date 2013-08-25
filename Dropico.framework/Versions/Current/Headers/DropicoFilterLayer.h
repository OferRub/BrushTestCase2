//
//  DropicoFilterLayer.h
//
//  Created by Shai Mishali on 11/3/11.
//  Copyright (c) 2011 Dropico Media. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DropicoFilters.h"

@interface DropicoFilterLayer : NSObject{}

@property (nonatomic) CGBlendMode blendMode;
@property (nonatomic, strong) NSString *filename;

- (id) initWithFile: (NSString *)fileName andBlendmode: (CGBlendMode) blendMode;

@end