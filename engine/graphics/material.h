// Copyright (c) 2023 Berke Umut Biricik All Rights Reserved

#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "graphics/texture.h"

struct Material {
  glm::vec4 color = glm::vec4(1.0f);
  std::shared_ptr<Texture> texture = nullptr;
  // TODO ambient, diffusion etc.
};
