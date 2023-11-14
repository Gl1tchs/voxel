// Copyright (c) 2023 Berke Umut Biricik All Rights Reserved

#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "graphics/vertex_array.h"

enum BufferBits : uint16_t {
  BufferBits_kDepth = 1 << 0,
  BufferBits_kColor = 1 << 1,
};

enum class DepthFunc { kLess, kLEQUAL };

class RenderCommand {
 public:
  static void Init();

  static void SetViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h);
  static void SetClearColor(const glm::vec4& color);
  static void Clear(uint16_t bits = BufferBits_kColor);

  static void DrawArrays(const std::shared_ptr<VertexArray>& vertex_array,
                         uint32_t vertex_count = 0);

  static void DrawIndexed(const std::shared_ptr<VertexArray>& vertex_array,
                          uint32_t index_Count = 0);

  static void DrawLines(const std::shared_ptr<VertexArray>& vertex_array,
                        uint32_t vertex_count);

  static void DrawArraysInstanced(
      const std::shared_ptr<VertexArray>& vertex_array, uint32_t vertex_count,
      uint32_t instance_count);

  static void DrawElementsInstanced(
      const std::shared_ptr<VertexArray>& vertex_array, uint32_t index_count,
      uint32_t instance_count);

  static void SetLineWidth(float width);

  static void SetDepthFunc(DepthFunc func = DepthFunc::kLess);

  static void SetActiveTexture(uint8_t index = 0);
};
