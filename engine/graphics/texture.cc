// Copyright (c) 2023 Berke Umut Biricik All Rights Reserved

#include "graphics/texture.h"

#include <glad/glad.h>

#include "core/debug/assert.h"

int DeserializeTextureFormat(TextureFormat format) {
  switch (format) {
    case TextureFormat::kRed:
      return GL_RED;
    case TextureFormat::kRG:
      return GL_RG;
    case TextureFormat::kRGB:
      return GL_RGB;
    case TextureFormat::kBGR:
      return GL_BGR;
    case TextureFormat::kRGBA:
      return GL_RGBA;
    case TextureFormat::kBGRA:
      return GL_BGRA;
    default:
      return -1;
  }
}

int DeserializeTextureFilteringMode(TextureFilteringMode mode) {
  switch (mode) {
    case TextureFilteringMode::kLinear:
      return GL_LINEAR;
    case TextureFilteringMode::kNearest:
      return GL_NEAREST;
    default:
      return -1;
  }
}

int DeserializeTextureWrappingMode(TextureWrappingMode mode) {
  switch (mode) {
    case TextureWrappingMode::kRepeat:
      return GL_REPEAT;
    case TextureWrappingMode::kMirroredRepeat:
      return GL_MIRRORED_REPEAT;
    case TextureWrappingMode::kClampToEdge:
      return GL_CLAMP_TO_EDGE;
    case TextureWrappingMode::kClampToBorder:
      return GL_CLAMP_TO_BORDER;
    default:
      return -1;
  }
}

Texture::Texture(const TextureMetadata& metadata, const void* pixels)
    : metadata_(metadata) {
  glGenTextures(1, &texture_id_);
  glBindTexture(GL_TEXTURE_2D, texture_id_);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  glTexImage2D(GL_TEXTURE_2D, 0, DeserializeTextureFormat(metadata_.format),
               metadata_.size.x, metadata_.size.y, 0,
               DeserializeTextureFormat(metadata_.format), GL_UNSIGNED_BYTE,
               pixels);

  if (metadata_.generate_mipmaps) {
    glGenerateMipmap(GL_TEXTURE_2D);
  }
}

Texture::~Texture() {
  glDeleteTextures(1, &texture_id_);
}

const TextureMetadata& Texture::GetMetadata() const {
  return metadata_;
}

uint32_t Texture::GetTextureID() const {
  return texture_id_;
}

void Texture::SetData(void* data, uint32_t size) {

  int format = DeserializeTextureFormat(metadata_.format);

  uint32_t bpp = format == GL_RGBA ? 4 : 3;
  ASSERT(size == metadata_.size.x * metadata_.size.y * bpp,
         "Data must be entire texture!")

  glTextureSubImage2D(texture_id_, 0, 0, 0, metadata_.size.x, metadata_.size.y,
                      format, GL_UNSIGNED_BYTE, data);
}

void Texture::Bind(uint16_t slot) const {
  glBindTextureUnit(slot, texture_id_);
}

bool Texture::operator==(const Texture& other) const {
  return texture_id_ == other.GetTextureID();
}
