//
//  ViewController1.h
//  BrushTestCase2
//
//  Created by Ofer Rubinstein on 8/12/13.
//  Copyright (c) 2013 Ofer Rubinstein. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "DMCanvas.h"
#import "NPColorPickerView.h"
#import "NPColorQuadView.h"
#import "CustomPicker.h"

@interface ViewController : UIViewController <UIImagePickerControllerDelegate, UINavigationControllerDelegate, UITabBarDelegate, NPColorPickerViewDelegate, UIPickerViewDelegate, UIPickerViewDataSource, drawerDelegate>
{
    IBOutlet DMCanvas *brushView;
    IBOutlet UIView *brushMenu;
    IBOutlet UIView *savePresetDialog;
    IBOutlet UIView *loadPresetDialog;
    IBOutlet NPColorPickerView *colorPickerView;
    IBOutlet NPColorQuadView *colorQuadView;
    IBOutlet CustomPicker * blendModePicker;
    
    IBOutletCollection(UIView) NSArray *brushMenus;
    IBOutlet UIImageView *brushPreview;
    IBOutlet UISlider * generalSizeSlider;
    IBOutlet UITextField * FileName;
    IBOutlet UITextField * LoadFileName;
    IBOutlet UITextField * ColorDisplay;
    BOOL isElementLive;
    BOOL isBrushSelect;
    NSArray *pickerContent;
}

- (IBAction)GeneralSlidersChange:(UISlider *)slider;
- (IBAction)ScatteringSlidersChange:(UISlider *)slider;
- (IBAction)TextureSlidersChange:(UISlider *)slider;
- (IBAction)ColorDynamicSlidersChange:(UISlider *)slider;
- (IBAction)BrushDynamicSlidersChange:(UISlider *)slider;


@end
