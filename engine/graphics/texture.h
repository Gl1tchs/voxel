// Copyright (c) 2023 Berke Biricik
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#pragma once

#include <glm/glm.hpp>

enum class TextureFormat {
  kRed,
  kRG,
  kRGB,
  kBGR,
  kRGBA,
  kBGRA,
};

enum class TextureFilteringMode {
  kNearest,
  kLinear,
};

enum class TextureWrappingMode {
  kRepeat,
  kMirroredRepeat,
  kClampToEdge,
  kClampToBorder,
};

struct TextureMetadata final {
  glm::ivec2 size;
  TextureFormat format;
  TextureFilteringMode min_filter;
  TextureFilteringMode mag_filter;
  TextureWrappingMode wrap_s;
  TextureWrappingMode wrap_t;
  bool generate_mipmaps = true;
};

class Texture final {
 public:
  Texture(const TextureMetadata& metadata, const void* pixels = nullptr);
  ~Texture();

  const TextureMetadata& GetMetadata() const;

  uint32_t GetTextureID() const;

  void SetData(void* data, uint32_t size);

  void Bind(uint16_t slot = 0) const;

  bool operator==(const Texture& other) const;

 private:
  TextureMetadata metadata_;

  uint32_t texture_id_;
};
