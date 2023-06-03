//
//  Renderer.cpp
//  MetalCpp
//
//  Created by Leleszi Marcell on 2023. 06. 03..
//

#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION

#include <vector>
#include <iostream>

#include "Renderer.hpp"

Renderer::Renderer(MTL::Device* const device)
: device(device),
commandQueue(device->newCommandQueue(), [](MTL::CommandQueue* const q) { q->release(); }),
renderPipelineState(nullptr, [](MTL::RenderPipelineState* const p) { p->release(); })
{
    buildShaders();
}

void Renderer::buildShaders() {
    const std::unique_ptr<MTL::Library, void(*)(MTL::Library* const)> defaultLibrary(device->newDefaultLibrary(), [](MTL::Library * const l) { l->release(); });
    const std::unique_ptr<MTL::Function, void(*)(MTL::Function* const)> vertexFunction(defaultLibrary.get()->newFunction(NS::String::string("basic_vertex", NS::UTF8StringEncoding)), [](MTL::Function * const f) { f->release(); });
    const std::unique_ptr<MTL::Function, void(*)(MTL::Function* const)> fragmentFunction(defaultLibrary.get()->newFunction(NS::String::string("basic_fragment", NS::UTF8StringEncoding)), [](MTL::Function* const f) { f->release(); });
    
    const std::unique_ptr<MTL::RenderPipelineDescriptor, void(*)(MTL::RenderPipelineDescriptor * const)> pipelineStateDescriptor(MTL::RenderPipelineDescriptor::alloc()->init(), [](MTL::RenderPipelineDescriptor * const d) { d->release(); });
    pipelineStateDescriptor.get()->setVertexFunction(vertexFunction.get());
    pipelineStateDescriptor.get()->setFragmentFunction(fragmentFunction.get());
    pipelineStateDescriptor.get()->colorAttachments()->object(0)->setPixelFormat(MTL::PixelFormatBGRA8Unorm);
    
    
    NS::Error* err {nullptr};
    renderPipelineState.reset(device->newRenderPipelineState(pipelineStateDescriptor.get(), &err));
    if (!renderPipelineState.get()) {
        __builtin_printf("%s", err->localizedDescription()->utf8String());
    }
}

void Renderer::render(const CA::MetalDrawable* const drawable) {
    std::unique_ptr<MTL::RenderPassDescriptor, void(*)(MTL::RenderPassDescriptor* const)> renderPassDescriptor(MTL::RenderPassDescriptor::alloc()->init(), [](MTL::RenderPassDescriptor* const r) { r->release(); });
    
    renderPassDescriptor->colorAttachments()->object(0)->setTexture(drawable->texture());
    renderPassDescriptor->colorAttachments()->object(0)->setLoadAction(MTL::LoadActionClear);
    renderPassDescriptor->colorAttachments()->object(0)->setClearColor(MTL::ClearColor::Make(1.0, 0.0, 1.0, 1.0));
    
    MTL::CommandBuffer* commandBuffer = commandQueue->commandBuffer();
    
    const std::vector<float> vertexData = {
        0.0, 0.5, 0.0,
        -1.0, -0.5, 0.0,
        1.0, -0.5, 0.0
    };
    
    std::unique_ptr<MTL::Buffer, void(*)(MTL::Buffer* const)> vertexBuffer(device->newBuffer(vertexData.data(), sizeof(float) * vertexData.size(), MTL::ResourceStorageModeShared), [](MTL::Buffer* const b) { b->release(); });
    
    MTL::RenderCommandEncoder* renderEncoder = commandBuffer->renderCommandEncoder(renderPassDescriptor.get());
    renderEncoder->setRenderPipelineState(renderPipelineState.get());
    renderEncoder->setVertexBuffer(vertexBuffer.get(), 0, 0);
    renderEncoder->drawPrimitives(MTL::PrimitiveTypeTriangle, NS::UInteger(0), NS::UInteger(3), NS::UInteger(1));
    renderEncoder->endEncoding();
    
    commandBuffer->presentDrawable(drawable);
    commandBuffer->commit();
}
