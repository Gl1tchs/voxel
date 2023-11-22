#ifndef CAMERA_DATA_GLSL_
#define CAMERA_DATA_GLSL_

layout(std140, binding = 0) uniform Camera {
  mat4 view;
  mat4 proj;
  vec3 position;
} u_camera;

#endif // CAMERA_DATA_GLSL_