//
//  DropicoNotificationCheckpoint.h
//  Framework-iOS
//
//  Created by Shai Mishali on 1/27/13.
//  Copyright (c) 2013 Dropico Media. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DropicoNotificationCheckpoint : NSObject{
    
}

@property (nonatomic, strong) NSNumber          *interval;
@property (nonatomic, strong) NSMutableArray    *messages;
@property (nonatomic, assign) BOOL              force;


@end
