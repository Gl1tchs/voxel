// Copyright (c) 2023 Berke Biricik
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

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
