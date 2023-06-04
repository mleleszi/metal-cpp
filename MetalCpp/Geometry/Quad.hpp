//
//  Quad.hpp
//  MetalCpp
//
//  Created by Leleszi Marcell on 2023. 06. 03..
//

#pragma once
#include <Metal/Metal.hpp>
#include <vector>
#include <simd/simd.h>
#include <algorithm>

class Quad {
public:
    Quad(MTL::Device* device, float scale);
    
    std::vector<float> vertices = {
        -1.0,  1.0,  .0,
        1.0,  1.0,  .0,
        -1.0, -1.0,  .0,
        1.0, -1.0,  .0
    };
    std::vector<uint16_t> indicies = {
        0, 3, 2,
        0, 1, 3
    };
    
    std::vector<simd::float3> colors {
        simd::float3{1, 0, 0},   // red
        simd::float3{0, 1, 0},   // green
        simd::float3{0, 0, 1},   // blue
        simd::float3{1, 1, 0}    // yellow
    };
    
    std::unique_ptr<MTL::Buffer, void(*)(MTL::Buffer* const)> vertexBuffer;
    std::unique_ptr<MTL::Buffer, void(*)(MTL::Buffer* const)> indexBuffer;
    std::unique_ptr<MTL::Buffer, void(*)(MTL::Buffer* const)> colorBuffer;
};
