//
//  RendererAdapter.m
//  MetalCpp
//
//  Created by Leleszi Marcell on 2023. 06. 03..
//

#import "RendererAdapter.h"

@implementation RendererAdapter

- (nonnull instancetype)initWithMTKView:(MTKView *)view
{
    self = [super init];
    renderer = new Renderer((__bridge MTL::Device *)view.device);
    return self;
}

- (void)mtkView:(MTKView *)view drawableSizeWillChange:(CGSize)size
{
}

- (void)drawInMTKView:(MTKView *)view
{
    renderer->render((__bridge CA::MetalDrawable *)view.currentDrawable);
}

- (void)dealloc
{
    delete renderer;
}

@end
