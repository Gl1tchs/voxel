// Copyright (c) 2023 Berke Biricik
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "graphics/buffer_layout.h"

#include "core/debug/assert.h"

uint32_t GetShaderDataTypeSize(ShaderDataType type) {
  switch (type) {
    case ShaderDataType::kFloat:
      return 4;
    case ShaderDataType::kFloat2:
      return 4 * 2;
    case ShaderDataType::kFloat3:
      return 4 * 3;
    case ShaderDataType::kFloat4:
      return 4 * 4;
    case ShaderDataType::kMat3:
      return 4 * 3 * 3;
    case ShaderDataType::kMat4:
      return 4 * 4 * 4;
    case ShaderDataType::kInt:
      return 4;
    case ShaderDataType::kInt2:
      return 4 * 2;
    case ShaderDataType::kInt3:
      return 4 * 3;
    case ShaderDataType::kInt4:
      return 4 * 4;
    case ShaderDataType::kBool:
      return 1;
    default:
      ASSERT(false, "Unknown ShaderDataType!")
      return 0;
  }
}

BufferElement::BufferElement(ShaderDataType type, const std::string& name,
                             bool normalized, uint32_t divisor)
    : type(type),
      name(name),
      size(GetShaderDataTypeSize(type)),
      offset(0),
      normalized(normalized),
      divisor(divisor) {}

uint32_t BufferElement::GetComponentCount() const {
  switch (type) {
    case ShaderDataType::kFloat:
      return 1;
    case ShaderDataType::kFloat2:
      return 2;
    case ShaderDataType::kFloat3:
      return 3;
    case ShaderDataType::kFloat4:
      return 4;
    case ShaderDataType::kMat3:
      return 3;  // 3 * float3
    case ShaderDataType::kMat4:
      return 4;  // 4 * float4
    case ShaderDataType::kInt:
      return 1;
    case ShaderDataType::kInt2:
      return 2;
    case ShaderDataType::kInt3:
      return 3;
    case ShaderDataType::kInt4:
      return 4;
    case ShaderDataType::kBool:
      return 1;
    default:
      ASSERT(false, "Unknown ShaderDataType!")
      return 0;
  }
}

BufferLayout::BufferLayout(std::initializer_list<BufferElement> elements)
    : elements_(elements) {
  CalculateOffsetAndStride();
}

void BufferLayout::CalculateOffsetAndStride() {
  size_t offset = 0;
  stride_ = 0;
  for (auto& element : elements_) {
    element.offset = offset;
    offset += element.size;
    stride_ += element.size;
  }
}
