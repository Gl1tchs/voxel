// Copyright (c) 2023 Berke Biricik
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#pragma once

#include <vector>

#include "graphics/renderer.h"

#include <FastNoiseLite.h>

class World {
 public:
  World(std::shared_ptr<Renderer> renderer);

  void Render();

 private:
  std::shared_ptr<Renderer> renderer_;

  std::vector<float> noise_data_;
};
