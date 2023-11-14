// Copyright (c) 2023 Berke Umut Biricik All Rights Reserved

#pragma once

#include <cstdint>
#include <initializer_list>
#include <string>
#include <vector>

enum class ShaderDataType {
  kNone = 0,
  kFloat,
  kFloat2,
  kFloat3,
  kFloat4,
  kMat3,
  kMat4,
  kInt,
  kInt2,
  kInt3,
  kInt4,
  kBool,
};

uint32_t GetShaderDataTypeSize(ShaderDataType type);

struct BufferElement final {
  ShaderDataType type;
  std::string name;
  uint32_t size;
  uint64_t offset;
  bool normalized;
  uint32_t divisor;

  BufferElement(ShaderDataType type, const std::string& name,
                bool normalized = false, uint32_t divisor = 0);

  uint32_t GetComponentCount() const;
};

class BufferLayout final {
 public:
  BufferLayout() = default;

  BufferLayout(std::initializer_list<BufferElement> elements);

  uint32_t GetStride() const { return stride_; }

  const std::vector<BufferElement>& GetElements() const { return elements_; }

  std::vector<BufferElement>::iterator begin() { return elements_.begin(); }
  std::vector<BufferElement>::iterator end() { return elements_.end(); }
  std::vector<BufferElement>::const_iterator begin() const {
    return elements_.begin();
  }
  std::vector<BufferElement>::const_iterator end() const {
    return elements_.end();
  }

 private:
  void CalculateOffsetAndStride();

  std::vector<BufferElement> elements_;
  uint32_t stride_ = 0;
};
