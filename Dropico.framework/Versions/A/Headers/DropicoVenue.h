//
//  DropicoVenue.h
//
//  Created by Shai Mishali on 11/14/11.
//  Copyright (c) 2011 Dropico Media. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Dropico.h"

@interface DropicoVenue : NSObject{}

@property (nonatomic, strong) NSString *id;
@property (nonatomic, assign, getter = isFavorite) BOOL favorite;
@property (nonatomic, strong) NSString *name;
@property (nonatomic, strong) NSString *primaryCategory;
@property (nonatomic, strong) NSString *address;
@property (nonatomic, strong) NSString *city;
@property (nonatomic, strong) NSString *state;
@property (nonatomic, strong) CLLocation *location;
@property (nonatomic, strong) NSNumber *distance;
@property (nonatomic, strong) NSNumber *peopleAtVenue;

@end
