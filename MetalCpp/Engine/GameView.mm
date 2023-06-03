//
//  GameView.m
//  MetalCpp
//
//  Created by Leleszi Marcell on 2023. 06. 03..
//

#import "GameView.h"

@implementation GameView

- (instancetype)init
{
    self = [super init];
    
    self.device = MTLCreateSystemDefaultDevice();
    _rendererAdapter = [[RendererAdapter alloc] initWithMTKView:self];
    self.delegate = _rendererAdapter;
    
    return self;
}

@end
