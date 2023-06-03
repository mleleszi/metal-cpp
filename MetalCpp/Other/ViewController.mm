//
//  ViewController.m
//  MetalCpp
//
//  Created by Leleszi Marcell on 2023. 06. 03..
//

#import "ViewController.h"
#import "RendererAdapter.h"

@implementation ViewController
{
    MTKView* view;
    
    RendererAdapter* rendererAdapter;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    view = (MTKView *)self.view;
    view.device = MTLCreateSystemDefaultDevice();
    rendererAdapter = [[RendererAdapter alloc] initWithMTKView:view];
    view.delegate = rendererAdapter;
}

@end
