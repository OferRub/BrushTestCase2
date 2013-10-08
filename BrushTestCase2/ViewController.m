//
//  ViewController1.m
//  BrushTestCase2
//
//  Created by Ofer Rubinstein on 8/12/13.
//  Copyright (c) 2013 Ofer Rubinstein. All rights reserved.
//

#import "ViewController.h"
#import "DMBrushTexture.h"
#import "DMBrushInkTexture.h"
#import "DMProcessor.h"

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
    unsigned int gradient;
    DMColor color, currentColor, secondColor;
    DMBrushTextureGeneral general;
    DMBrushTextureScattering scattering;
    DMBrushTextureDynamics dynamics;
    DMBrushTextureColorDynamics colorDynamics;
    DMBrushTextureCanvas canvas;
}


@property (nonatomic, strong) UIPopoverController *popover;
@end

@implementation ViewController

#pragma mark – Picker Datasource:
- (NSInteger)numberOfComponentsInPickerView:(UIPickerView *)pickerView
{
    return 1;
}
- (NSInteger)pickerView:(UIPickerView *)pickerView numberOfRowsInComponent:(NSInteger)component
{
    return pickerContent.count;
}
#pragma mark – Picker Delegate:
- (NSString *)pickerView:(UIPickerView *)pickerView titleForRow:(NSInteger)row forComponent:(NSInteger)component
{
    return [pickerContent objectAtIndex:row];
}

- (void)pickerView:(UIPickerView *)pickerView didSelectRow:(NSInteger)row inComponent:(NSInteger)component
{
    switch (row) {
        case 0:
            brushView.brushController.blendMode = DMBlendModeNormal;
            break;
        case 1:
            brushView.brushController.blendMode = DMBlendModeScreen;
            break;
        case 2:
            brushView.brushController.blendMode = DMBlendModeMultiply;
            break;
        case 3:
            brushView.brushController.blendMode = DMBlendModeAdd;
            break;
        default:
            break;
    }
    [brushView resumeDraw];
}

/*- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
}*/

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        gradient = 0;
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
    
    pickerContent = [[NSArray alloc] initWithObjects:
                     @"Normal", @"Screen",
                     @"Multiply", @"Add", nil];

    blendModePicker.delegate1 = self;
    [colorPickerView setDelegate:self];
	// Do any additional setup after loading the view.
    [brushView loadStencil:@"Fairy 2.ppng"];
//    [brushView loadOverlay:@"MammothOverlay.ppng"];
}

- (void)controllerTouch
{
    [brushView stopDraw];
}

-(void)NPColorPickerView:(NPColorPickerView *)view didSelectColor:(UIColor *)color1
{
    float a = 1.0;
    [color1 getRed:&color.red green:&color.green blue:&color.blue alpha:&a];
    [self setColor:color];
    ColorDisplay.backgroundColor = [[UIColor alloc] initWithRed:color.red green:color.green blue:color.blue alpha:1.0];
}

- (IBAction)borderSwitchChange:(UISwitch *)blendModeSwitch
{
    brushView.brushController.border = blendModeSwitch.on;
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

- (IBAction)sizeSliderChange:(UISlider *)slider
{
    float val = slider.value;
    [brushView.brushController  setSize:CGSizeMake(46.0*(val+0.5), 46.0*(val+0.5))];
}

-(void)setColor:(DMColor)color1
{
    float chroma = [DMProcessor RGBToChroma:color1];
    float hue = [DMProcessor RGBToHue:color1];
    float luma = [DMProcessor RGBToLuma601:color1];
    if (gradient==0)
    {
        [brushView.brushController setColor: color1];
        currentColor = color1;
    }
    else if (gradient==1)
    {
        currentColor = color1;
//        luma =  MIN((luma+0.5)/2., luma);
//        DMColor targetColor = [DMProcessor CHLToRGBwithChroma:chroma andHue:hue andLuma:luma+0.1];
        DMColor targetColor = DMMakeColor(2.0, 2.0, 2.0);
        targetColor.red += color1.red;
        targetColor.green += color1.green;
        targetColor.blue += color1.blue;
        targetColor.red/=3.0;
        targetColor.green/=3.0;
        targetColor.blue/=3.0;
        [brushView.brushController setColor: color1 target: targetColor];
    }
    else if (gradient==2)
    {
        currentColor = color1;
        //        luma =  MIN((luma+0.5)/2., luma);
        hue+=1.;
        hue = hue-floor(hue/6.0)*6.0;
        DMColor targetColor = [DMProcessor CHLToRGBwithChroma:chroma andHue:hue andMinLuma:luma];
        [brushView.brushController setColor: color1 target: targetColor];
    }
    else if (gradient==3)
    {
        secondColor = color1;
        //        luma =  MIN((luma+0.5)/2., luma);
        hue-=1.;
        hue = hue+6.0-floor((hue+6.0)/6.0)*6.0;
        DMColor targetColor = [DMProcessor CHLToRGBwithChroma:chroma andHue:hue andMinLuma:luma];
        hue+=2.;
        hue = hue-floor(hue/6.0)*6.0;
        color1 = [DMProcessor CHLToRGBwithChroma:chroma andHue:hue andMinLuma:luma];

        [brushView.brushController setColor: targetColor target: secondColor];
        [brushView.brushController setColorThird: color1];
    }
}
- (IBAction)redSliderChange:(UISlider *)slider
{
    float val = slider.value;
    color.red = val;
    [self setColor:color];
    ColorDisplay.backgroundColor = [[UIColor alloc] initWithRed:color.red green:color.green blue:color.blue alpha:1.0];
}

- (IBAction)greenSliderChange:(UISlider *)slider
{
    float val = slider.value;
    color.green = val;
    [self setColor:color];
    ColorDisplay.backgroundColor = [[UIColor alloc] initWithRed:color.red green:color.green blue:color.blue alpha:1.0];
}

- (IBAction)blueSliderChange:(UISlider *)slider
{
    float val = slider.value;
    color.blue = val;
    [self setColor:color];
    ColorDisplay.backgroundColor = [[UIColor alloc] initWithRed:color.red green:color.green blue:color.blue alpha:1.0];
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
        [brushView unloadStencil];
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
     
    isBrushSelect = NO;

     self.popover = [[UIPopoverController alloc] initWithContentViewController:picker];
     [self.popover presentPopoverFromRect:CGRectMake(100, 100, 320, 480) inView:self.view permittedArrowDirections:UIPopoverArrowDirectionLeft animated:YES];
     
    [brushView stopDraw];
//     [self presentModalViewController:picker animated:YES];
}

- (IBAction)selectInkTexture:(UIButton *)sender
{
     UIImagePickerController *picker = [[UIImagePickerController alloc] init];
     picker.delegate = self;
     picker.allowsEditing = YES;
     picker.sourceType = UIImagePickerControllerSourceTypePhotoLibrary;
     
    isBrushSelect = YES;
     self.popover = [[UIPopoverController alloc] initWithContentViewController:picker];
     [self.popover presentPopoverFromRect:CGRectMake(100, 100, 320, 480) inView:self.view permittedArrowDirections:UIPopoverArrowDirectionAny animated:YES];
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
    [brushView resumeDraw];
    if (isBrushSelect)
    {
        DMTexture * texture = [[[DMGraphics manager] factory] loadWithImage:image isMipMap:NO isBGR:NO repeat:YES flipY:YES];
        [brushView setBrushType:DMBrushTypeInkTexture];
        [((DMBrushInkTexture *)brushView.brushController) setTexture: texture];
    }
    else
    {
        DMTexture * texture = [[[DMGraphics manager] factory] loadWithImage:image isMipMap:NO isBGR:NO repeat:NO flipY:YES];
        [brushView setBackground:texture];
    }
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

-(IBAction)touchInk:(id)sender
{
    gradient = 0;
    [brushView setBrushType:DMBrushTypeInk];
}

-(IBAction)touchInkGradient:(id)sender
{
    gradient = 1;
    [brushView setBrushType:DMBrushTypeGradient];
}

-(IBAction)touchInkGradient2:(id)sender
{
    gradient = 2;
    [brushView setBrushType:DMBrushTypeGradient];
}

-(IBAction)touchInkGradient3:(id)sender
{
    gradient = 3;
    [brushView setBrushType:DMBrushTypeGradientThree];
}

-(IBAction)touchBrush1:(id)sender
{
    gradient = 0;
    [brushView setBrushType:DMBrushTypeTexture];
}
-(IBAction)touchBrush2:(id)sender
{
    gradient = 0;
    [brushView setBrushType:DMBrushTypeTexture];
/*    [brushView loadPreset:@"a" onBrushLoadComplete:^(NSDictionary *info) {
        generalSizeSlider.value = ([[[info valueForKey:kDMBrushTextureGeneral] valueForKey: kDMBrushTextureGeneralSize] floatValue]/46.0)-0.5;
        [brushView.brushController getPreview:brushPreview];
    }];*/
}

- (IBAction) flipStencil: (id) sender {
    UISwitch *onoff = (UISwitch *) sender;
    if (onoff.on)
        [brushView loadStencil:@"MammothOutline.ppng"];
    else
        [brushView unloadStencil];
}

- (IBAction) flipOverlay: (id) sender {
    UISwitch *onoff = (UISwitch *) sender;
    if (onoff.on)
        [brushView loadOverlay:@"MammothOverlay.ppng"];
    else
        [brushView unloadOverlay];
}


-(IBAction)touchBrush3:(id)sender
{
    gradient = 0;
    [brushView setBrushType:DMBrushTypeTexture];
}
-(IBAction)touchBrush4:(id)sender
{
    gradient = 0;
    [brushView setBrushType:DMBrushTypeTexture];
}
-(IBAction)touchBrush5:(id)sender
{
    gradient = 0;
    [brushView setBrushType:DMBrushTypeTexture];
}


@end
