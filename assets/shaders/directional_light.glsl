// Copyright (c) 2023 Berke Biricik
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef DIRECTIONAL_LIGHT_GLSL_
#define DIRECTIONAL_LIGHT_GLSL_

#include "material.glsl"

struct DirectionalLight {
  vec3 direction;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

vec3 CalculateDirectionalLight(DirectionalLight light, Material material, vec3 normal, vec3 view_dir) {
  vec3 light_dir = normalize(-light.direction);

  // Lambertian reflection (diffuse)
  float diff = max(dot(normal, light_dir), 0.0);
  vec3 diffuse = light.diffuse * (material.diffuse * diff);

  // Phong reflection (specular)
  vec3 reflect_dir = reflect(-light_dir, normal);
  float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
  vec3 specular = light.specular * (material.specular * spec);

  // Combine ambient, diffuse, and specular components
  vec3 result = light.ambient * material.ambient + diffuse + specular;

  return result;
}

#endif // DIRECTIONAL_LIGHT_GLSL_