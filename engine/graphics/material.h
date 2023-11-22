// Copyright (c) 2023 Berke Umut Biricik All Rights Reserved

#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "graphics/texture.h"

struct Material {
  glm::vec3 ambient;
  glm::vec3 diffuse;
  glm::vec3 specular;
  float shininess;
  std::shared_ptr<Texture> texture = nullptr;
};
