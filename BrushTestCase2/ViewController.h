//
//  ViewController1.h
//  BrushTestCase2
//
//  Created by Ofer Rubinstein on 8/12/13.
//  Copyright (c) 2013 Ofer Rubinstein. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "DMCanvas.h"

@interface ViewController : UIViewController <UIImagePickerControllerDelegate, UINavigationControllerDelegate, UITabBarDelegate>
{
    IBOutlet DMCanvas *brushView;
    IBOutlet UIView *brushMenu;
    IBOutlet UIView *savePresetDialog;
    IBOutlet UIView *loadPresetDialog;
    
    IBOutletCollection(UIView) NSArray *brushMenus;
    IBOutlet UIImageView *brushPreview;
    IBOutlet UISlider * generalSizeSlider;
    IBOutlet UITextField * FileName;
    IBOutlet UITextField * LoadFileName;
    BOOL isElementLive;
}


- (IBAction)GeneralSlidersChange:(UISlider *)slider;
- (IBAction)ScatteringSlidersChange:(UISlider *)slider;
- (IBAction)TextureSlidersChange:(UISlider *)slider;
- (IBAction)ColorDynamicSlidersChange:(UISlider *)slider;
- (IBAction)BrushDynamicSlidersChange:(UISlider *)slider;


@end
