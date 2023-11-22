// Copyright (c) 2023 Berke Biricik
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef CUBE_OUTPUT_GLSL_
#define CUBE_OUTPUT_GLSL_

#include "material.glsl"

struct CubeVertexOutput {
  Material material;
  vec3 frag_pos;
  vec3 normal;
};

#endif // CUBE_OUTPUT_GLSL_