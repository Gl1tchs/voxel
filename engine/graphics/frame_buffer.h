// Copyright (c) 2023 Berke Biricik
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "graphics/texture.h"

class FrameBuffer final {
 public:
  FrameBuffer(const glm::ivec2& size);
  ~FrameBuffer();

  void Bind() const;

  void Unbind() const;

  void Refresh();

  [[nodiscard]] const glm::ivec2& GetSize();
  void SetSize(glm::ivec2 size);

  std::shared_ptr<Texture> GetTexture();

 private:
  glm::ivec2 size_;

  uint32_t fbo_;
  uint32_t rbo_;

  std::shared_ptr<Texture> texture_;
};
