//
//  Renderer.hpp
//  MetalCpp
//
//  Created by Leleszi Marcell on 2023. 06. 03..
//

#pragma once

#include <Metal/Metal.hpp>
#include <QuartzCore/CAMetalDrawable.hpp>
#include <memory>
#include <cmath>

#include "Quad.hpp"

class Renderer {
public:
    Renderer(MTL::Device* const device);
    void render(const CA::MetalDrawable* const drawable, MTL::RenderPassDescriptor* renderPassDescriptor);
private:
    MTL::Device* const device;
    std::unique_ptr<MTL::CommandQueue, void(*)(MTL::CommandQueue *)> commandQueue;
    std::unique_ptr<MTL::RenderPipelineState, void(*)(MTL::RenderPipelineState *)> renderPipelineState;
    
    float timer = 0;
    Quad quad;
    
    void buildShaders();
};
