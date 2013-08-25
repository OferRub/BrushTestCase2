
//  PhotoCollage
//
//  Created by Ofer Rubinstein on 6/27/13.
//  Copyright (c) 2013 Ofer Rubinstein. All rights reserved.
//

#import <GLKit/GLKit.h>
typedef enum _DMBrushType {
    DMBrushTypeTexture,
    DMBrushTypeSpray,
    DMBrushTypeTouche,
    DMBrushTypeMarker,
    DMBrushTypeGradient,
    DMBrushTypeInk
} DMBrushType;

@class DMBrush;

@interface DMBrushView : GLKView<GLKViewDelegate, DMGraphicsDelegate>
-(void)loadPreset:(NSString *)presetName onBrushLoadComplete:(void (^)(NSDictionary *info))completeHandler;
- (void) savePreset:(NSString *)presetName;
- (void)clearCanvas;
- (void)saveToGallery;
- (void)setBackground:(DMTexture *)background;
- (void)loadBrushWithType:(DMBrushType)type;
- (void)setSize:(double)size;
- (UIColor *)setHue:(float)hue;
- (DMBrush *)getBrush;
- (UIImage *)getPreview;

@end
