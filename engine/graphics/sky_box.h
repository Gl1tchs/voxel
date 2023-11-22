// Copyright (c) 2023 Berke Biricik
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "graphics/vertex_array.h"
#include "graphics/vertex_buffer.h"

constexpr uint32_t kSkyBoxVertexCount = 36;

class SkyBox {
 public:
  SkyBox(const std::vector<std::string>& face_paths);

  void Bind();

  void UnBind();

  [[nodiscard]] const std::shared_ptr<VertexArray>& GetVertexArray() {
    return vertex_array_;
  }

 private:
  std::shared_ptr<VertexArray> vertex_array_;
  std::shared_ptr<VertexBuffer> vertex_buffer_;

  uint32_t texture_id_;
};
