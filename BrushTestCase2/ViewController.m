//
//  ViewController1.m
//  BrushTestCase2
//
//  Created by Ofer Rubinstein on 8/12/13.
//  Copyright (c) 2013 Ofer Rubinstein. All rights reserved.
//

#import "ViewController.h"
#import "DMBrushTexture.h"

#define GENERAL_SPACING 100
#define GENERAL_ANGLE   101
#define GENERAL_ROUNDNESS 102
#define GENERAL_SIZE 103
#define GENERAL_FLOW 104

#define SCATTERRING_SCATTER 120
#define SCATTERRING_COUNT_JITTER 121
#define SCATTERRING_COUNT   122

#define DYNAMICS_ROUNDNESS 130
#define DYNAMICS_ANGLE 131
#define DYNAMICS_SIZE 132
#define DYNAMICS_MINIMUM_STROKE 133

#define COLOR_DYNAMICS_BRIGHTNESS_JITTER 140
#define COLOR_DYNAMICS_HUE_JITTER 141
#define COLOR_DYNAMICS_FB_JITTER 142
#define COLOR_DYNAMICS_SATURATION_JITTER 143
#define COLOR_DYNAMICS_PRURIFY 144

#define TEXTURE_SCALE 150
#define TEXTURE_CONTRAST 151
#define TEXTURE_BRIGHTNESS 152




@interface ViewController ()
{
    DMBrushTextureGeneral general;
    DMBrushTextureScattering scattering;
    DMBrushTextureDynamics dynamics;
    DMBrushTextureColorDynamics colorDynamics;
    DMBrushTextureCanvas canvas;
}


@property (nonatomic, strong) UIPopoverController *popover;
@end

@implementation ViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        isElementLive = NO;
        general = initDMBrushTextureGeneral();
        scattering = initDMBrushTextureScattering();
        dynamics = initDMBrushTextureDynamics();
        colorDynamics = initDMBrushTextureColorDynamics();
        canvas = initDMBrushTextureCanvas();
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view.
//    [brushView loadStencil:@"test2.ppng"];
}


- (IBAction)generalSwitchChange:(UISwitch *)blendModeSwitch
{
    if (![brushView.brushController isKindOfClass:[DMBrushTexture class]])
        return;
    DMBrushTexture *brush= (DMBrushTexture *)brushView.brushController ;
 
    if (blendModeSwitch.on)
        general.blendMode = DMBlendModeMultiply;
    else
        general.blendMode = DMBlendModeNormal;
    [brush setGeneral: general];
    [brush getPreview:brushPreview];
    
}

- (IBAction)GeneralSlidersChange:(UISlider *)slider
{
    UIView *container = slider.superview;
    
    float val = slider.value;
    float percent = val*100.0;
    if (![brushView.brushController isKindOfClass:[DMBrushTexture class]])
        return;
    DMBrushTexture *brush= (DMBrushTexture *)brushView.brushController ;
    
    BOOL update = YES;
    
    switch (container.tag) {
        case GENERAL_SPACING:
            general.spacing = val; 
            break;
        case GENERAL_ANGLE:
            general.angle   = val * M_PI*2.0;
            break;
        case GENERAL_ROUNDNESS:
            general.roundness = val;
            break;
        case GENERAL_SIZE:
            [brushView.brushController  setSize:CGSizeMake(46.0*(val+0.5), 46.0*(val+0.5))];
            break;
        case GENERAL_FLOW:
            [brushView.brushController setAlpha:val];
            break;
            
        default:
            update = NO;
            break;
    }
    
    UITextField *t = (UITextField *)container.subviews[2];
    
    [t setText:[NSString stringWithFormat:@"%d%%", (unsigned int)percent]];
    
    
    if (update)
    {
        [brush setGeneral: general];
        [brush getPreview:brushPreview];
    }
    
}
- (IBAction)ScatteringSlidersChange:(UISlider *)slider
{
    UIView *container = slider.superview;
    
    if (![brushView.brushController isKindOfClass:[DMBrushTexture class]])
        return;

    float val = slider.value;
    DMBrushTexture *brush= (DMBrushTexture *)brushView.brushController ;
    
    BOOL update = YES;
    
    switch (container.tag) {
            case SCATTERRING_SCATTER:
                scattering.scatter = val;
                break;
            case SCATTERRING_COUNT_JITTER:
                scattering.countJitter = val;
                break;
            case SCATTERRING_COUNT:
                scattering.count = val;
                break;
            default:
                update= NO;
                break;
    }
    
    if (update)
    {
        [brush setScattering:scattering];
        [brush getPreview:brushPreview];
    }
    
}

//TODO: update this
- (IBAction)TextureSlidersChange:(UISlider *)slider
{
    UIView *container = slider.superview;
    
    if (![brushView.brushController isKindOfClass:[DMBrushTexture class]])
        return;

    float val = slider.value;
    DMBrushTexture *brush= (DMBrushTexture *)brushView.brushController ;
    
    BOOL update = YES;
    
    switch (container.tag) {
        case TEXTURE_SCALE:
            canvas.scaleX = val;
            canvas.scaleY = val;
            break;
        case TEXTURE_CONTRAST:
            canvas.contrast = val;
            break;
        case TEXTURE_BRIGHTNESS:
            canvas.brightness = val;
            break;
        default:
            update= NO;
    }
    
    
    
    if (update)
    {
        [brush setCanvas:canvas];
        [brush getPreview:brushPreview];
    }
}

- (IBAction)selectSavePreset:(UIButton *)sender {
    savePresetDialog.hidden = NO;
};

- (void)image:(UIImage *)image didFinishSavingWithError:(NSError *)error contextInfo:(void *)contextInfo{
    
    NSString *str = @"Saved!!!";
    
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Saved." message:str delegate:self cancelButtonTitle:nil otherButtonTitles:@"OK", nil];
    
    [alert show];
    
}

- (IBAction)selectSaveToGallery:(UIButton *)sender {
    UIImageWriteToSavedPhotosAlbum([brushView save], self, @selector(image:didFinishSavingWithError:contextInfo:), (__bridge void *)(self));
};

- (IBAction)selectAddElement:(UIButton *)sender {
    if (isElementLive)
    {
        [brushView mergeElement];
//        isElementLive = NO;
    }
    else
    {
        DMTexture * elm = [[[DMGraphics manager] factory] loadWithImage:[brushView saveTransparent]];
        [brushView clearStencil];
        [brushView clearCanvas];
        [brushView setElement:elm];
        isElementLive = YES;
    }
};

- (IBAction)selectBackground:(UIButton *)sender {
     UIImagePickerController *picker = [[UIImagePickerController alloc] init];
     picker.delegate = self;
     picker.allowsEditing = YES;
     picker.sourceType = UIImagePickerControllerSourceTypePhotoLibrary;
     
    
     self.popover = [[UIPopoverController alloc] initWithContentViewController:picker];
     [self.popover presentPopoverFromRect:CGRectMake(100, 100, 320, 480) inView:self.view permittedArrowDirections:UIPopoverArrowDirectionLeft animated:YES];
     
    [brushView stopDraw];
//     [self presentModalViewController:picker animated:YES];
}

- (IBAction)selectPhoto:(UIButton *)sender {
    loadPresetDialog.hidden = NO;
/*
    UIImagePickerController *picker = [[UIImagePickerController alloc] init];
    picker.delegate = self;
    picker.allowsEditing = YES;
    picker.sourceType = UIImagePickerControllerSourceTypePhotoLibrary;
    
    
     self.popover = [[UIPopoverController alloc] initWithContentViewController:picker];
    [self.popover presentPopoverFromRect:CGRectMake(100, 100, 320, 480) inView:self.view permittedArrowDirections:UIPopoverArrowDirectionAny animated:YES];
    
    
    //[self presentModalViewController:picker animated:YES];
  */  
    
}

#pragma mark - Image Picker Controller delegate methods

-(void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info
{
    UIImage *image=[info objectForKey:UIImagePickerControllerOriginalImage];
    DMTexture * background = [[[DMGraphics manager] factory] loadWithImage:image isMipMap:NO isBGR:NO flipY:YES];
    [brushView resumeDraw];
    [brushView setBackground:background];
    [picker dismissModalViewControllerAnimated:YES];
}

- (void)imagePickerControllerDidCancel:(UIImagePickerController *)picker {
    
    [picker dismissViewControllerAnimated:YES completion:NULL];
    
}

//TODO: complete implementation
- (IBAction)ColorDynamicSlidersChange:(UISlider *)slider
{
    UIView *container = slider.superview;
    
    if (![brushView.brushController isKindOfClass:[DMBrushTexture class]])
        return;

    float val = slider.value;
    DMBrushTexture *brush= (DMBrushTexture *)brushView.brushController ;
    
    BOOL update = YES;
    
    switch (container.tag) {
        case COLOR_DYNAMICS_FB_JITTER:
            colorDynamics.backgroundFactor = val;
            break;
        case COLOR_DYNAMICS_HUE_JITTER:
            colorDynamics.hue = val;
            break;
        case COLOR_DYNAMICS_BRIGHTNESS_JITTER:
            colorDynamics.brightness = val;
            break;
            
        case COLOR_DYNAMICS_SATURATION_JITTER:
            colorDynamics.saturation = val;
            break;
        
        case COLOR_DYNAMICS_PRURIFY:
            colorDynamics.purify = val;
            break;
        default:
            update= NO;
    }
    
    
    
    if (update)
    {
        [brush setColorDynamics:colorDynamics];
        [brush getPreview:brushPreview];
    }
}


- (IBAction)BrushDynamicSlidersChange:(UISlider *)slider
{
    
    UIView *container = slider.superview;
    
    if (![brushView.brushController isKindOfClass:[DMBrushTexture class]])
        return;

    float val = slider.value;
    DMBrushTexture *brush= (DMBrushTexture *)brushView.brushController ;
    
    BOOL update = YES;
    
    switch (container.tag) {
        case DYNAMICS_SIZE:
            dynamics.sizeJitter = val;
            break;
        case DYNAMICS_MINIMUM_STROKE:
            dynamics.minStroke = val;
            break;
        case DYNAMICS_ANGLE:
            dynamics.angle = val;
            
        case DYNAMICS_ROUNDNESS:
            dynamics.roundness = val;
            break;
        default:
            update= NO;
    }
    
    if (update)
    {
        [brush setDynamics:dynamics];
        [brush getPreview:brushPreview];
    }

}


- (void)tabBar:(UITabBar *)tabBar didSelectItem:(UITabBarItem *)item
{
    for (int i=0; i<brushMenus.count; i++)
    {
        if (i == item.tag)
            ((UIView *)brushMenus[i]).hidden = NO;
        else
            ((UIView *)brushMenus[i]).hidden = YES;
            
    }
}

- (IBAction)toggleMenu:(id)sender
{
    brushMenu.hidden = !brushMenu.hidden;
}

-(IBAction)touchSavePreset:(id)sender
{
    [brushView savePreset:FileName.text];
    savePresetDialog.hidden = YES;
}

-(IBAction)touchCancelPreset:(id)sender
{
    savePresetDialog.hidden = YES;    
}

-(IBAction)touchLoadPreset:(id)sender
{
    [brushView loadPreset:LoadFileName.text onBrushLoadComplete:^(NSDictionary *info) {
        generalSizeSlider.value = ([[[info valueForKey:kDMBrushTextureGeneral] valueForKey: kDMBrushTextureGeneralSize] floatValue]/46.0)-0.5;
        [brushView.brushController getPreview:brushPreview];
    }];
    loadPresetDialog.hidden = YES;
}

-(IBAction)touchCancelLoadPreset:(id)sender
{
    loadPresetDialog.hidden = YES;
}

-(IBAction)touchErase:(id)sender
{
    [brushView clearCanvas];
}


@end
