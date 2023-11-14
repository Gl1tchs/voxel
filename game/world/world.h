// Copyright (c) 2023 Berke Umut Biricik All Rights Reserved

#pragma once

#include <vector>

#include "graphics/renderer.h"

#include <FastNoiseLite.h>

constexpr size_t kMaxHeight = 32;

class World {
 public:
  World(std::shared_ptr<Renderer> renderer);

  void Render();

 private:
  std::shared_ptr<Renderer> renderer_;

  std::vector<float> noise_data_;
};
