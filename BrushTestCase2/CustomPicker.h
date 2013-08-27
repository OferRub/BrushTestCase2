//
//  CustomPicker.h
//  BrushTestCase2
//
//  Created by Ofer Rubinstein on 8/27/13.
//  Copyright (c) 2013 Ofer Rubinstein. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol drawerDelegate <NSObject>
- (void)controllerTouch;
@end

@interface CustomPicker : UIPickerView
{
    @public
}

@property(nonatomic,assign)id delegate1;

@end
