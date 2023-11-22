// Copyright (c) 2023 Berke Biricik
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "graphics/vertex_array.h"

#include <glad/glad.h>

#include "core/debug/assert.h"

static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
  switch (type) {
    case ShaderDataType::kFloat:
      return GL_FLOAT;
    case ShaderDataType::kFloat2:
      return GL_FLOAT;
    case ShaderDataType::kFloat3:
      return GL_FLOAT;
    case ShaderDataType::kFloat4:
      return GL_FLOAT;
    case ShaderDataType::kMat3:
      return GL_FLOAT;
    case ShaderDataType::kMat4:
      return GL_FLOAT;
    case ShaderDataType::kInt:
      return GL_INT;
    case ShaderDataType::kInt2:
      return GL_INT;
    case ShaderDataType::kInt3:
      return GL_INT;
    case ShaderDataType::kInt4:
      return GL_INT;
    case ShaderDataType::kBool:
      return GL_BOOL;
    default:
      ASSERT(false, "Unknown ShaderDataType!");
      return 0;
  }
}

VertexArray::VertexArray() {
  glCreateVertexArrays(1, &vao_);
}

VertexArray::~VertexArray() {
  glDeleteVertexArrays(1, &vao_);
}

void VertexArray::Bind() const {
  glBindVertexArray(vao_);
}

void VertexArray::Unbind() const {
  glBindVertexArray(0);
}

const std::vector<std::shared_ptr<VertexBuffer>>&
VertexArray::GetVertexBuffers() const {
  return vertex_buffers_;
}

void VertexArray::AddVertexBuffer(
    const std::shared_ptr<VertexBuffer>& vertex_buffer) {
  ASSERT(vertex_buffer->GetLayout().GetElements().size(),
         "Vertex Buffer has no layout!");

  glBindVertexArray(vao_);

  vertex_buffer->Bind();

  const auto layout = vertex_buffer->GetLayout();
  for (const auto& element : layout) {
    switch (element.type) {
      case ShaderDataType::kFloat:
      case ShaderDataType::kFloat2:
      case ShaderDataType::kFloat3:
      case ShaderDataType::kFloat4: {
        glEnableVertexAttribArray(vertex_buffer_index_);
        glVertexAttribPointer(vertex_buffer_index_, element.GetComponentCount(),
                              ShaderDataTypeToOpenGLBaseType(element.type),
                              element.normalized ? GL_TRUE : GL_FALSE,
                              layout.GetStride(), (const void*)element.offset);
        if (element.divisor) {
          glVertexAttribDivisor(vertex_buffer_index_, element.divisor);
        }
        vertex_buffer_index_++;
        break;
      }
      case ShaderDataType::kInt:
      case ShaderDataType::kInt2:
      case ShaderDataType::kInt3:
      case ShaderDataType::kInt4:
      case ShaderDataType::kBool: {
        glEnableVertexAttribArray(vertex_buffer_index_);
        glVertexAttribIPointer(vertex_buffer_index_,
                               element.GetComponentCount(),
                               ShaderDataTypeToOpenGLBaseType(element.type),
                               layout.GetStride(), (const void*)element.offset);
        if (element.divisor) {
          glVertexAttribDivisor(vertex_buffer_index_, element.divisor);
        }
        vertex_buffer_index_++;
        break;
      }
      case ShaderDataType::kMat3:
      case ShaderDataType::kMat4: {
        int count = element.GetComponentCount();
        for (int i = 0; i < count; i++) {
          glEnableVertexAttribArray(vertex_buffer_index_);
          glVertexAttribPointer(
              vertex_buffer_index_, count,
              ShaderDataTypeToOpenGLBaseType(element.type),
              element.normalized ? GL_TRUE : GL_FALSE, layout.GetStride(),
              (const void*)(element.offset + sizeof(float) * count * i));
          glVertexAttribDivisor(vertex_buffer_index_, 1);
          vertex_buffer_index_++;
        }
        break;
      }
      default:
        ASSERT(false, "Unknown ShaderDataType!");
    }
  }

  vertex_buffers_.push_back(vertex_buffer);
}

const std::shared_ptr<IndexBuffer>& VertexArray::GetIndexBuffer() const {
  return index_buffer_;
}

void VertexArray::SetIndexBuffer(
    const std::shared_ptr<IndexBuffer>& index_buffer) {
  glBindVertexArray(vao_);
  index_buffer->Bind();

  index_buffer_ = index_buffer;
}
