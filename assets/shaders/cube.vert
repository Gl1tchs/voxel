#version 450

#include "cube_output.glsl"
#include "camera_data.glsl"

layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec4 a_color;
layout(location = 3) in vec3 a_offset;

layout(location = 0) out CubeVertexOutput v_output;

void main() {
  v_output.color = a_color;

  gl_Position = u_camera.proj * u_camera.view * vec4(a_pos + a_offset, 1.0);
}
