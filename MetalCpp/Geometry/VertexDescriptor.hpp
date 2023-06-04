//
//  VertexDescriptor.hpp
//  MetalCpp
//
//  Created by Leleszi Marcell on 2023. 06. 03..
//

#pragma once

#include <Metal/Metal.hpp>
#include <simd/simd.h>

class VertexDescriptor {
public:
    static std::shared_ptr<MTL::VertexDescriptor> defaultLayout() {
        std::shared_ptr<MTL::VertexDescriptor> vertexDescriptor = std::make_shared<MTL::VertexDescriptor>();

        vertexDescriptor->attributes()->object(0)->setFormat(MTL::VertexFormatFloat3);
        vertexDescriptor->attributes()->object(0)->setOffset(0);
        vertexDescriptor->attributes()->object(0)->setBufferIndex(0);
        vertexDescriptor->layouts()->object(0)->setStride(sizeof(float) * 3);
        
        vertexDescriptor->attributes()->object(1)->setFormat(MTL::VertexFormatFloat3);
        vertexDescriptor->attributes()->object(1)->setOffset(0);
        vertexDescriptor->attributes()->object(1)->setBufferIndex(1);
        vertexDescriptor->layouts()->object(0)->setStride(sizeof(simd::float3));
        
        return vertexDescriptor;
    }
};
