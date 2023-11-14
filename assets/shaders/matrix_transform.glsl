#ifndef MATRIX_TRANSFORM_GLSL_
#define MATRIX_TRANSFORM_GLSL_

mat4 translate(vec3 offset) {
  return mat4(
    vec4(1.0, 0.0, 0.0, 0.0),
    vec4(0.0, 1.0, 0.0, 0.0),
    vec4(0.0, 0.0, 1.0, 0.0),
    vec4(offset, 1.0)
  );
}

#endif // MATRIX_TRANSFORM_GLSL_