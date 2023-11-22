// Copyright (c) 2023 Berke Umut Biricik All Rights Reserved

#ifndef CUBE_OUTPUT_GLSL_
#define CUBE_OUTPUT_GLSL_

#include "material.glsl"

struct CubeVertexOutput {
  Material material;
  vec3 frag_pos;
  vec3 normal;
};

#endif // CUBE_OUTPUT_GLSL_