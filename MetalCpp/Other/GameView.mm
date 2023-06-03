//
//  GameView.m
//  MetalCpp
//
//  Created by Leleszi Marcell on 2023. 06. 03..
//

#import <Foundation/Foundation.h>
#import "GameView.h"

@implementation GameView

- (instancetype)initWithCoder:(NSCoder *)coder {
    self = [super initWithCoder:coder];
    
    self.device = MTLCreateSystemDefaultDevice();
    _rendererAdapter = [[RendererAdapter alloc] initWithMTKView: self];
    self.delegate = _rendererAdapter;
    
    return self;
}

@end
