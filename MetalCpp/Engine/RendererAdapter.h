//
//  RendererAdapter.h
//  MetalCpp
//
//  Created by Leleszi Marcell on 2023. 06. 03..
//

#ifndef RendererAdapter_h
#define RendererAdapter_h

#import "QuartzCore/CAMetalLayer.h"
#import "Metal/MTLDevice.h"
#import <MetalKit/MTKView.h>
#import "Renderer.hpp"

@interface RendererAdapter : NSObject<MTKViewDelegate>
{
    Renderer* renderer;
}
-(nonnull instancetype) initWithMTKView: (MTKView* _Nonnull)view;
@end

#endif /* RendererAdapter_h */
