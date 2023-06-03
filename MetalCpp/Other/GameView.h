//
//  GameView.h
//  MetalCpp
//
//  Created by Leleszi Marcell on 2023. 06. 03..
//

#ifndef GameView_h
#define GameView_h

#import <MetalKit/MetalKit.h>
#import "RendererAdapter.h"

@interface GameView : MTKView

@property (nonatomic, strong) RendererAdapter* rendererAdapter;

@end

#endif /* GameView_h */
