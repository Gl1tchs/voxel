#version 450

#include "cube_output.glsl"
#include "camera_data.glsl"

layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec3 a_ambient;
layout(location = 3) in vec3 a_diffuse;
layout(location = 4) in vec3 a_specular;
layout(location = 5) in float a_shininess;
layout(location = 6) in vec3 a_offset;

layout(location = 0) out CubeVertexOutput v_output;

mat4 translate(vec3 offset);

void main() {
  mat4 model = translate(a_offset);

  Material material;
  material.ambient = a_ambient;
  material.diffuse = a_diffuse;
  material.specular = a_specular;
  material.shininess = a_shininess;

  v_output.material = material;
  v_output.frag_pos = vec3(model * vec4(a_pos, 1.0));
  v_output.normal = mat3(transpose(inverse(model))) * a_normal;

  gl_Position = u_camera.proj * u_camera.view * vec4(v_output.frag_pos, 1.0);
}

mat4 translate(vec3 offset) {
  return mat4(
    vec4(1.0, 0.0, 0.0, 0.0),
    vec4(0.0, 1.0, 0.0, 0.0),
    vec4(0.0, 0.0, 1.0, 0.0),
    vec4(offset, 1.0)
  );
}
