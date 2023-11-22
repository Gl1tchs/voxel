// Copyright (c) 2023 Berke Biricik
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#version 450

#include "camera_data.glsl"

layout(location = 0) in vec3 a_pos;

layout(location = 0) out vec3 v_tex_coord;

void main() {
  v_tex_coord = a_pos;
  vec4 pos = u_camera.proj * mat4(mat3(u_camera.view)) * vec4(a_pos, 1.0);
  gl_Position = pos.xyww;
}
