// Copyright (c) 2023 Berke Umut Biricik All Rights Reserved

#pragma once

#include <cstdint>

class IndexBuffer final {
 public:
  IndexBuffer(uint32_t size);
  IndexBuffer(const uint32_t* indices, uint32_t count);
  ~IndexBuffer();

  void Bind();
  void Unbind();

  void SetData(const void* data, uint32_t size);

  uint32_t GetCount();

 private:
  uint32_t ibo_;
  uint32_t count_;
};
