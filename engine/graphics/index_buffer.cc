// Copyright (c) 2023 Berke Biricik
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "graphics/index_buffer.h"

#include <glad/glad.h>

IndexBuffer::IndexBuffer(uint32_t size) {
  glCreateBuffers(1, &ibo_);
  glBindBuffer(GL_ARRAY_BUFFER, ibo_);
  // TODO documentate this constructor and tell the client this defines as DYNAMIC_DRAW
  glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

IndexBuffer::IndexBuffer(const uint32_t* indices, uint32_t count)
    : count_(count) {
  glCreateBuffers(1, &ibo_);

  // GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
  // Binding with GL_ARRAY_BUFFER allows the data to be loaded regardless of VAO state.
  glBindBuffer(GL_ARRAY_BUFFER, ibo_);
  glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices,
               GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
  glDeleteBuffers(1, &ibo_);
}

void IndexBuffer::Bind() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);
}

void IndexBuffer::Unbind() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::SetData(const void* data, uint32_t size) {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);
  glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, data);
}

uint32_t IndexBuffer::GetCount() {
  return count_;
}
