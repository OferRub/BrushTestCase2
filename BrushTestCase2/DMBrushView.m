//
//  DMVideoView.m
//  MotionFX
//
//  Created by Ofer Rubinstein on 5/22/13.
//  Copyright (c) 2013 Dropico Media LTD. All rights reserved.
//

#import "DMBrushView.h"
#import "DMView.h"
#import "DMBrush.h"
#import "DMBrushTouche.h"
#import "DMBrushSpray.h"
#import "DMBrushGradient.h"
#import "DMBrushTexture.h"
#import <Dropico/Dropico.h>
#import "DMTexture+Extra.h"
#import "DMProcessor.h"
#import "DMBlend+Extra.h"

@interface DMBrushView()
{
    DMBrushNode * currentErase;
    DMTexture * texture1, * texture2, * background;
    DMTexture * preview;
    DMView        * view1;

    DMColor lastColor, lastGradient;
    CGRect         gRenderRect;
    DMBrush * brush;
    DMBlend * copyBlend, * normalBlend;
}

@end

@implementation DMBrushView

- (void)setup
{
    [[DMGraphics manager] DMGSetup];
    [DMGraphics manager].delegate = self;
    CADisplayLink * mFrameLink = [CADisplayLink displayLinkWithTarget:self
                                                             selector:@selector(doFrame:)];
    [mFrameLink setFrameInterval:1];
    [mFrameLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSRunLoopCommonModes];
    
    self.delegate = self;
    self.drawableDepthFormat = GLKViewDrawableDepthFormat16;
    self.drawableStencilFormat = GLKViewDrawableStencilFormat8;
    self.context = [[DMGraphics manager] factory]->context;
    
    gRenderRect = CGRectMake(0, 0, self.frame.size.width, self.frame.size.height);

//    brush = [[DMBrush alloc] init];
    {
        DMBrushTexture * b1 = [[DMBrushTexture alloc] init];
        [b1 setTexture: [[[DMGraphics manager] factory] loadImageWithPath: [[NSBundle mainBundle] pathForResource:@"Skin" ofType:@"ppng"] isRepeat:NO]];
        [b1 setCanvasTexture: [[[DMGraphics manager] factory] loadImageWithPath: [[NSBundle mainBundle] pathForResource:@"Hair" ofType:@"ppng"] isRepeat:YES]];
        brush = b1;
        [brush setColor: DMMakeColor(1.0, 0.0, 0.0)];
    }
    [self setBackground:nil];
}


- (void)loadBrushWithType:(DMBrushType)type
{
    if (type==DMBrushTypeInk)
        brush = [[DMBrush alloc] init];
    else if (type==DMBrushTypeGradient)
        brush = [[DMBrushGradient alloc] init];
    else if (type==DMBrushTypeTouche)
        brush = [[DMBrushTouche alloc] init];
    else if (type==DMBrushTypeSpray)
        brush = [[DMBrushSpray alloc] init];
    else if (type==DMBrushTypeTexture)
    {
        DMBrushTexture * b1 = [[DMBrushTexture alloc] init];
        [b1 setTexture: [[[DMGraphics manager] factory] loadImageWithPath: [[NSBundle mainBundle] pathForResource:@"Skin" ofType:@"ppng"] isRepeat:NO]];
        [b1 setCanvasTexture: [[[DMGraphics manager] factory] loadImageWithPath: [[NSBundle mainBundle] pathForResource:@"Hair" ofType:@"ppng"] isRepeat:YES]];
        brush = b1;
    }
    [brush setColor: lastColor target: lastGradient];

}

- (void)setSize:(double)size
{
    [brush setSize:CGSizeMake(size, size)];
}

+ (DMColor)calcHue:(double)hue
{
    DMColor c;
    DMColor c1 = [DMProcessor HueToRGB:hue ];
    DMColor c2 = [DMProcessor HueToRGB:hue+1.0 ];
    double x = hue-floor(hue);
    c.red = c2.red*x+c1.red*(1.0-x);
    c.green = c2.green*x+c1.green*(1.0-x);
    c.blue = c2.blue*x+c1.blue*(1.0-x);
    c.red = (c.red-0.5)*0.8+0.5;
    c.green = (c.green-0.5)*0.8+0.5;
    c.blue = (c.blue-0.5)*0.8+0.5;
    return c;
}

- (UIColor *)setHue:(float)hue;
{
    DMColor c;
    if (hue<1.0)
    {
        c = (DMColor){0, 0, 0};
        lastGradient = (DMColor){1, 1, 1};
    }
    else if (hue>7.0)
    {
        c = (DMColor){1, 1, 1};
        lastGradient = (DMColor){0, 0, 0};
    }
    else
    {
        c = [DMBrushView calcHue:hue-1.0];
        lastGradient = [DMBrushView calcHue:hue-floor(hue/6.0)*6.0];
    }
    lastColor = c;
    [brush setColor: c target: lastGradient];
    return [[UIColor alloc] initWithRed:c.red green:c.green blue:c.blue alpha:1.0];
}

- (DMBrush *)getBrush
{
    return brush;
}

- (void) setBackground:(DMTexture *)background
{
//    background = [[[DMGraphics manager] factory] loadImageWithPath:[[NSBundle mainBundle] pathForResource:@"Valley_Oahu" ofType:@"ppng"]];
//    [background load];
//    [brush setBackground:background];
}
#pragma mark - inner functions
-(void) doFrame:(id)data
{
    [self update];
        
    [self display];
}

- (id)init
{
    self = [super init];
    if (self)
    {
    }
    return self;
}

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        [self setup];
    }
    return self;
}

- (id)initWithCoder:(NSCoder *)aDecoder
{
    self = [super initWithCoder:aDecoder];
    if (self)
    {
        [self setup];
    }
    
    return self;
}

- (BOOL)update
{
    BOOL b = YES;
    return b;
}

+ (void) removeFile:(NSURL *)fileURL
{
    NSString *filePath = [fileURL path];
    NSFileManager *fileManager = [NSFileManager defaultManager];
    if ([fileManager fileExistsAtPath:filePath]) {
        NSError *error;
        if ([fileManager removeItemAtPath:filePath error:&error] == NO) {
            NSLog(@"removeItemAtPath %@ error:%@", filePath, error);
        }
    }
}


-(void)DMGraphicsDidEnterToBackground
{
}

-(void)DMGraphicsDidEnterToForeground
{
}


double gRetinaFactor = 2.0;
- (void)renderView: (GLKView *)view
{
    if (view1 == nil)
        view1 = [[DMView alloc] init];
    
    CGRect viewRect = CGRectMake(0, 0, [view drawableWidth], [view drawableHeight]);

    if (!background)
    {
        background = [[[DMGraphics manager] factory] loadImageWithPath:[[NSBundle mainBundle] pathForResource:@"test2" ofType:@"ppng"] isRepeat:NO];
        [background load];
//        UIImageWriteToSavedPhotosAlbum([background getData], nil, nil, nil);
    }
    if (!copyBlend)
        copyBlend = [[[DMGraphics manager] factory] loadBlend:nil blend:DMBlendModeSet isTransformable:YES isPMA:NO];
    if (!normalBlend)
        normalBlend = [[[DMGraphics manager] factory] loadBlend:nil blend:DMBlendModeOutline isTransformable:YES isPMA:NO];

    gRenderRect = viewRect;
    [view1 setView:view viewRect:gRenderRect];
    if (currentErase)
    {
//        [brush clear: texture1 withBackground:background];
    }
    else
    {
        if (!texture1)
        {
            texture1 = [[[DMGraphics manager] factory] createTarget:viewRect.size.width height:viewRect.size.height isDepth:YES];
            [texture1 clearWhite];
            texture2 = [[[DMGraphics manager] factory] createTarget:viewRect.size.width height:viewRect.size.height isDepth:YES];
            [texture2 clearWhite];
            preview = [[[DMGraphics manager] factory] createTarget:854 height:256 isDepth:YES];
            [preview clearWhite];
            [background load];
/*            [copyBlend setOverlay:background];
            [copyBlend drawSprite:texture1 withBackground:nil withPosition:CGPointZero withScale:1.0];
            [copyBlend setOverlay:nil];*/
        }
        [brush renderBrushForTarget:texture1];
    }
    if (texture1)
    {
        [normalBlend setOverlay:background];
        [normalBlend drawSprite:texture2 withBackground:texture1 withPosition:CGPointMake ((texture2.renderSize.width-background.renderSize.width)/2, (texture2.renderSize.height-background.renderSize.height)/2) withScale:1.0];
        [normalBlend setOverlay:nil];
        [view1 presentTexture:texture2 withView:view andRect:gRenderRect];
    }
    else
        [texture1 clearWhite];
}

-(UIImage *)getPreview
{
    [preview clearWhite];
    [brush renderPreview:preview];
    return [preview getDataNoAlpha];
}

- (void)clearCanvas
{
    if (texture1)
    {
        [texture1 clearWhite];
//        [background load];
//        [copyBlend setOverlay:background];
//        [copyBlend drawSprite:texture1 withBackground:nil withPosition:CGPointZero withScale:1.0];
//        [copyBlend setOverlay:nil];
    }
}

- (void)saveToGallery
{
    UIImageWriteToSavedPhotosAlbum([texture1 getDataNoAlpha], self, @selector(image:didFinishSavingWithError:contextInfo:), (__bridge void *)(self));
}

- (void)image:(UIImage *)image didFinishSavingWithError:(NSError *)error contextInfo:(void *)contextInfo{
    
    NSString *str = @"Saved!!!";
    
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Saved." message:str delegate:self cancelButtonTitle:nil otherButtonTitles:@"OK", nil];
    
    [alert show];
    
}

double lastTouch = 0.0;
CGPoint lastPoint, lastLook;

- (void) touchesBegan:(NSSet*)touches withEvent:(UIEvent*)event
{
    if ([touches count]==1)
        currentErase = nil;
    if (currentErase)
        return;
//    NSLog (@"************");
    lastTouch = event.timestamp;
    if ([touches count]>1)
    {
        int i = 0;
        CGPoint point = CGPointZero;
        for (UITouch *touch in touches) {
            point.x += [touch locationInView:self].x;
            point.y += [touch locationInView:self].y;
            i++;
        }
        point.x/=(float)i;
        point.y/=(float)i;
        DMBrushNode * n = [DMBrushNode new];
        n->position = point;
        currentErase = n;
        return;
    }
    CGPoint point = [ [touches anyObject] locationInView:self];
    point.x*=gRetinaFactor;
    point.y*=gRetinaFactor;
    lastPoint = point;
    lastLook = CGPointMake(0, 0);

    [brush drawStroke:(DMBrushStrokeData){point, 1.0/60.0}];
}

- (void)loadPreset:(NSString *)presetName onBrushLoadComplete:(void (^)(NSDictionary *info))completeHandler;
{
    [brush loadPreset:presetName onBrushLoadComplete:completeHandler];
}

- (void) savePreset:(NSString *)presetName
{
    [brush savePreset:presetName];
}

- (void) touchesMoved:(NSSet*)touches withEvent:(UIEvent*)event
{
    if (currentErase)
        return;
    if ([touches count]>1)
    {
        lastTouch = event.timestamp;
        int i = 0;
        CGPoint point = CGPointZero;
        for (UITouch *touch in touches) {
            point.x += [touch locationInView:self].x;
            point.y += [touch locationInView:self].y;
            i++;
        }
        point.x/=(float)i;
        point.y/=(float)i;
        DMBrushNode * n = [DMBrushNode new];
        n->position = point;
        currentErase = n;
        return;
    }
    CGPoint point = [ [touches anyObject] locationInView:self];
    point.x*=gRetinaFactor;
    point.y*=gRetinaFactor;
    CGPoint n1;
    n1.x = point.x-lastPoint.x;
    n1.y = point.y-lastPoint.y;
    float l = sqrt(n1.x*n1.x+n1.y*n1.y);
    n1.x/=l;
    n1.y/=l;
    float dot = n1.x*lastLook.x+n1.y*lastLook.y;
    if (dot>0.3 || sqrt((lastPoint.x-point.x)*(lastPoint.x-point.x)+(lastPoint.y-point.y)*(lastPoint.y-point.y))>20.0)
    {
        double delta = event.timestamp-lastTouch;
        lastTouch = event.timestamp;
        lastPoint = point;
        [brush drawStroke:(DMBrushStrokeData){point, delta}];
        lastLook = n1;
    }
/*    else
    {
        CGPoint n1;
        n1.x = point.x-lastPoint.x;
        n1.y = point.y-lastPoint.y;
        float l = sqrt(n1.x*n1.x+n1.y*n1.y);
        n1.x/=l;
        n1.y/=l;
        float dot = n1.x*lastLook.x+n1.y*lastLook.y;
        if (dot<0.0)
        {
            point.x-=2.0*l*dot*lastLook.x;
            point.y-=2.0*l*dot*lastLook.y;
            n1.x = point.x-lastPoint.x;
            n1.y = point.y-lastPoint.y;
            l = sqrt(n1.x*n1.x+n1.y*n1.y);
            n1.x/=l;
            n1.y/=l;
            lastLook = n1;
        }
    }*/
}


- (void) touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    if (currentErase)
        return;
    if ([touches count]>1)
    {
        lastTouch = event.timestamp;
        int i = 0;
        CGPoint point = CGPointZero;
        for (UITouch *touch in touches) {
            point.x += [touch locationInView:self].x;
            point.y += [touch locationInView:self].y;
            i++;
        }
        point.x/=(float)i;
        point.y/=(float)i;
        DMBrushNode * n = [DMBrushNode new];
        n->position = point;
        currentErase = n;
        return;
    }
    CGPoint point = [ [touches anyObject] locationInView:self];
    point.x*=gRetinaFactor;
    point.y*=gRetinaFactor;
    double delta = event.timestamp-lastTouch;
    lastTouch = event.timestamp;
    [brush drawStroke:(DMBrushStrokeData){point, delta}];
    [brush endDrawing];
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    [self renderView:view];
}

- (void)tearDownGL
{
    [[DMGraphics manager] DMGRelease];
}

- (void)dealloc
{
    [self tearDownGL];
}



#pragma mark - interface

- (void) removeFile:(NSURL *)fileURL
{
    NSString *filePath = [fileURL path];
    NSFileManager *fileManager = [NSFileManager defaultManager];
    if ([fileManager fileExistsAtPath:filePath]) {
        NSError *error;
        if ([fileManager removeItemAtPath:filePath error:&error] == NO) {
            NSLog(@"removeItemAtPath %@ error:%@", filePath, error);
        }
    }
}
@end
