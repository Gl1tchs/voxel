// Copyright (c) 2023 Berke Biricik
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "world/world.h"

#include <cmath>

constexpr size_t kSize = 128;
constexpr size_t kMaxHeight = 16;

static glm::vec4 CalculateColor(double darkness, glm::vec2 position);

World::World(std::shared_ptr<Renderer> renderer)
    : renderer_(renderer), noise_data_(kSize * kSize) {
  FastNoiseLite noise;
  noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);

  int index = 0;
  for (int y = 0; y < kSize; y++) {
    for (int x = 0; x < kSize; x++) {
      noise_data_[index++] = noise.GetNoise((float)x, (float)y);
    }
  }
}

void World::Render() {
  // Calculate the offset to move the terrain to the center
  glm::vec2 offset(static_cast<float>(kSize) / 2.0f,
                   static_cast<float>(kSize) / 2.0f);

  for (size_t y = 0; y < kSize; ++y) {
    for (size_t x = 0; x < kSize; ++x) {
      double darkness = noise_data_[y * kSize + x];

      // Calculate the Y position based on the darkness value
      float pos_y = std::round(darkness * kMaxHeight);

      // Adjust the position based on the offset
      float new_x = static_cast<float>(x) - offset.x;
      float new_y = pos_y;
      float new_z = static_cast<float>(y) - offset.y;

      glm::vec4 color = CalculateColor(
          darkness, {static_cast<float>(x), static_cast<float>(y)});

      Material material;
      material.ambient = color;
      material.diffuse = color;
      material.specular = color;
      material.shininess = 16.0;

      renderer_->DrawCube({new_x, new_y, new_z}, material);
    }
  }
}

glm::vec4 CalculateColor(double darkness, glm::vec2 position) {
  float r = static_cast<float>(darkness) + position.x / kSize;
  float g = 0.5f + position.y / kSize;
  float b = 1.0f - static_cast<float>(darkness) - position.x / kSize;

  return glm::vec4(r, g, b, 1.0);
}