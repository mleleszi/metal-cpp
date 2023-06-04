//
//  Quad.cpp
//  MetalCpp
//
//  Created by Leleszi Marcell on 2023. 06. 03..
//

#include "Quad.hpp"

Quad::Quad(MTL::Device* device, float scale = 1)
:   vertexBuffer(nullptr, [](MTL::Buffer* const b) { b->release(); }),
    indexBuffer(nullptr, [](MTL::Buffer* const b) { b->release(); }),
    colorBuffer(nullptr, [](MTL::Buffer* const b) { b->release(); })
{
    std::transform(vertices.begin(), vertices.end(), vertices.begin(), [scale](float vertex) { return vertex * scale; });
    
    vertexBuffer.reset(device->newBuffer(vertices.data(), sizeof(float) * vertices.size(), MTL::ResourceStorageModeShared));
    indexBuffer.reset(device->newBuffer(indicies.data(), sizeof(uint16_t) * indicies.size(), MTL::ResourceStorageModeShared));
    colorBuffer.reset(device->newBuffer(colors.data(), sizeof(simd::float3) * colors.size(), MTL::ResourceStorageModeShared));
}
