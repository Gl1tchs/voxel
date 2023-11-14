// Copyright (c) 2023 Berke Umut Biricik All Rights Reserved

#pragma once

#include <cstdint>

class UniformBuffer final {
 public:
  UniformBuffer(uint32_t size, uint32_t binding);
  ~UniformBuffer();

  void SetData(const void* data, uint32_t size, uint32_t offset = 0);

 private:
  uint32_t ubo_;
};
