// Copyright (c) 2023 Berke Umut Biricik All Rights Reserved

#include "graphics/vertex_buffer.h"

#include <glad/glad.h>

VertexBuffer::VertexBuffer(uint32_t size) {
  glCreateBuffers(1, &vbo_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  // TODO documentate this constructor and tell the client this defines as DYNAMIC_DRAW
  glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

VertexBuffer::VertexBuffer(const void* vertices, uint32_t size) {
  glCreateBuffers(1, &vbo_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
  glDeleteBuffers(1, &vbo_);
}

void VertexBuffer::Bind() {
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
}

void VertexBuffer::Unbind() {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::SetData(const void* data, uint32_t size) {
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

const BufferLayout& VertexBuffer::GetLayout() {
  return layout_;
}

void VertexBuffer::SetLayout(const BufferLayout& layout) {
  layout_ = layout;
}
