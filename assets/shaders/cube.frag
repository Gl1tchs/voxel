// Copyright (c) 2023 Berke Biricik
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#version 450

#include "camera_data.glsl"
#include "cube_output.glsl"
#include "directional_light.glsl"

layout(location = 0) out vec4 o_color;

layout(location = 0) in CubeVertexOutput v_input;

void main() {
  vec3 norm = normalize(v_input.normal);
  vec3 view_dir = normalize(u_camera.position - v_input.frag_pos);

  DirectionalLight light;
  light.direction = vec3(-0.2, -1.0, -0.3);
  light.ambient = vec3(0.2, 0.2, 0.2);
  light.diffuse = vec3(1.0, 1.0, 1.0);
  light.specular = vec3(1.0, 1.0, 1.0);

  vec3 result = CalculateDirectionalLight(light, v_input.material, norm, view_dir);

  o_color = vec4(result, 1.0);
}
