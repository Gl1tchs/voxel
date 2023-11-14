// Copyright (c) 2023 Berke Umut Biricik All Rights Reserved

#pragma once

#include "graphics/buffer_layout.h"

class VertexBuffer final {
 public:
  VertexBuffer(uint32_t size);
  VertexBuffer(const void* vertices, uint32_t size);
  ~VertexBuffer();

  void Bind();
  void Unbind();

  void SetData(const void* data, uint32_t size);

  const BufferLayout& GetLayout();
  void SetLayout(const BufferLayout& layout);

 private:
  uint32_t vbo_;
  BufferLayout layout_;
};
