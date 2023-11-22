// Copyright (c) 2023 Berke Biricik
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "graphics/frame_buffer.h"

#include <glad/glad.h>

#include "core/debug/log.h"

FrameBuffer::FrameBuffer(const glm::ivec2& size) : size_(size) {
  glGenFramebuffers(1, &fbo_);
  glBindFramebuffer(GL_FRAMEBUFFER, fbo_);

  glGenRenderbuffers(1, &rbo_);

  Refresh();

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    LOG_ERROR("Framebuffer is not complete!");

  glBindRenderbuffer(GL_RENDERBUFFER, 0);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FrameBuffer::~FrameBuffer() {
  glDeleteFramebuffers(1, &fbo_);
  glDeleteRenderbuffers(1, &rbo_);
}

void FrameBuffer::Bind() const {
  glBindFramebuffer(GL_FRAMEBUFFER, fbo_);
}

void FrameBuffer::Unbind() const {
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::Refresh() {
  TextureMetadata metadata;
  metadata.size = size_;
  metadata.format = TextureFormat::kRGB;
  metadata.min_filter = TextureFilteringMode::kLinear;
  metadata.mag_filter = TextureFilteringMode::kLinear;
  metadata.wrap_s = TextureWrappingMode::kClampToEdge;
  metadata.wrap_t = TextureWrappingMode::kClampToEdge;
  metadata.generate_mipmaps = false;

  texture_ = std::make_shared<Texture>(metadata);

  glBindTexture(GL_TEXTURE_2D, texture_->GetTextureID());
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                         texture_->GetTextureID(), 0);

  glBindRenderbuffer(GL_RENDERBUFFER, rbo_);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size_.x, size_.y);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                            GL_RENDERBUFFER, rbo_);
}

const glm::ivec2& FrameBuffer::GetSize() {
  return size_;
}

void FrameBuffer::SetSize(glm::ivec2 size) {
  size_ = size;
}

std::shared_ptr<Texture> FrameBuffer::GetTexture() {
  return texture_;
}
