//
//  CustomPicker.m
//  BrushTestCase2
//
//  Created by Ofer Rubinstein on 8/27/13.
//  Copyright (c) 2013 Ofer Rubinstein. All rights reserved.
//

#import "CustomPicker.h"

@implementation CustomPicker

@synthesize delegate1;

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
    }
    return self;
}

-(UIView *)hitTest:(CGPoint)point withEvent:(UIEvent *)event
{
    UIView * u = [super hitTest:point withEvent:event];
    if (delegate1 && CGRectContainsPoint(self.bounds, point))
        [delegate1 controllerTouch];
    return u;
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
}
*/

@end
