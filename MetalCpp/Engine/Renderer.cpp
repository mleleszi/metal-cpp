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
renderPipelineState(nullptr, [](MTL::RenderPipelineState* const p) { p->release(); }),
quad(device, 1)
{
    buildShaders();
}

void Renderer::buildShaders() {
    const std::unique_ptr<MTL::Library, void(*)(MTL::Library* const)> defaultLibrary(device->newDefaultLibrary(), [](MTL::Library * const l) { l->release(); });
    const std::unique_ptr<MTL::Function, void(*)(MTL::Function* const)> vertexFunction(defaultLibrary.get()->newFunction(NS::String::string("vertex_main", NS::UTF8StringEncoding)), [](MTL::Function * const f) { f->release(); });
    const std::unique_ptr<MTL::Function, void(*)(MTL::Function* const)> fragmentFunction(defaultLibrary.get()->newFunction(NS::String::string("fragment_main", NS::UTF8StringEncoding)), [](MTL::Function* const f) { f->release(); });
    
    const std::unique_ptr<MTL::RenderPipelineDescriptor, void(*)(MTL::RenderPipelineDescriptor * const)> pipelineStateDescriptor(MTL::RenderPipelineDescriptor::alloc()->init(), [](MTL::RenderPipelineDescriptor * const d) { d->release(); });
    pipelineStateDescriptor->setVertexFunction(vertexFunction.get());
    pipelineStateDescriptor->setFragmentFunction(fragmentFunction.get());
    pipelineStateDescriptor->colorAttachments()->object(0)->setPixelFormat(MTL::PixelFormatBGRA8Unorm);
    
    const std::unique_ptr<MTL::VertexDescriptor, void(*)(MTL::VertexDescriptor* const)> vertexDescriptor(MTL::VertexDescriptor::alloc()->init(), [](MTL::VertexDescriptor* v) { v->release(); });
    
    vertexDescriptor->attributes()->object(0)->setFormat(MTL::VertexFormatFloat3);
    vertexDescriptor->attributes()->object(0)->setOffset(0);
    vertexDescriptor->attributes()->object(0)->setBufferIndex(0);
    vertexDescriptor->layouts()->object(0)->setStride(sizeof(float) * 3);
    
    vertexDescriptor->attributes()->object(1)->setFormat(MTL::VertexFormatFloat3);
    vertexDescriptor->attributes()->object(1)->setOffset(0);
    vertexDescriptor->attributes()->object(1)->setBufferIndex(1);
    vertexDescriptor->layouts()->object(1)->setStride(sizeof(simd::float3));
    
    pipelineStateDescriptor->setVertexDescriptor(vertexDescriptor.get());
    
    NS::Error* err {nullptr};
    renderPipelineState.reset(device->newRenderPipelineState(pipelineStateDescriptor.get(), &err));
    if (!renderPipelineState.get()) {
        __builtin_printf("%s", err->localizedDescription()->utf8String());
    }
}

void Renderer::render(const CA::MetalDrawable* const drawable, MTL::RenderPassDescriptor* renderPassDescriptor) {
    renderPassDescriptor->colorAttachments()->object(0)->setTexture(drawable->texture());
    renderPassDescriptor->colorAttachments()->object(0)->setLoadAction(MTL::LoadActionClear);
    renderPassDescriptor->colorAttachments()->object(0)->setClearColor(MTL::ClearColor::Make(1.0, 1.0, 0.8, 1.0));
    
    MTL::CommandBuffer* commandBuffer = commandQueue->commandBuffer();
    MTL::RenderCommandEncoder* renderEncoder = commandBuffer->renderCommandEncoder(renderPassDescriptor);

    
    timer += 0.05;
    float currentTime = std::sin(timer);
    
    renderEncoder->setVertexBytes(&currentTime, sizeof(float), 11);

    renderEncoder->setRenderPipelineState(renderPipelineState.get());
    
    
    renderEncoder->setVertexBuffer(quad.vertexBuffer.get(), 0, 0);
    renderEncoder->setVertexBuffer(quad.colorBuffer.get(), 0, 1);
    
    renderEncoder->drawIndexedPrimitives(MTL::PrimitiveTypePoint, quad.indicies.size(), MTL::IndexTypeUInt16, quad.indexBuffer.get(), 0);
    
    renderEncoder->endEncoding();
    
    commandBuffer->presentDrawable(drawable);
    commandBuffer->commit();
}
