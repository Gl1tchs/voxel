// Copyright (c) 2023 Berke Umut Biricik All Rights Reserved

#version 450

#include "camera_data.glsl"
#include "cube_output.glsl"

layout(location = 0) out vec4 o_color;

layout(location = 0) in CubeVertexOutput v_input;

void main() {
  o_color = v_input.color;
}
