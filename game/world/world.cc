// Copyright (c) 2023 Berke Umut Biricik All Rights Reserved

#include "world/world.h"

#include <cmath>

constexpr size_t kSize = 128;

World::World(std::shared_ptr<Renderer> renderer)
    : renderer_(renderer), noise_data_(kSize * kSize) {
  FastNoiseLite noise;
  noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);

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

      Material material;
      material.color = glm::vec4(glm::vec3(darkness), 1.0f);

      renderer_->DrawCube({new_x, new_y, new_z}, material);
    }
  }
}