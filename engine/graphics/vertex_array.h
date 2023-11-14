// Copyright (c) 2023 Berke Umut Biricik All Rights Reserved

#pragma once

#include <memory>
#include <vector>

#include "graphics/index_buffer.h"
#include "graphics/vertex_buffer.h"

class VertexArray {
 public:
  VertexArray();
  ~VertexArray();

  void Bind() const;
  void Unbind() const;

  [[nodiscard]] const std::vector<std::shared_ptr<VertexBuffer>>&
  GetVertexBuffers() const;
  void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertex_buffer);

  [[nodiscard]] const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const;
  void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& index_buffer);

 private:
  uint32_t vao_;
  uint32_t vertex_buffer_index_ = 0;
  std::vector<std::shared_ptr<VertexBuffer>> vertex_buffers_;
  std::shared_ptr<IndexBuffer> index_buffer_;
};
