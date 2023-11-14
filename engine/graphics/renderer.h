// Copyright (c) 2023 Berke Umut Biricik All Rights Reserved

#pragma once

#include <array>
#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "core/math/transform.h"
#include "graphics/index_buffer.h"
#include "graphics/material.h"
#include "graphics/shader.h"
#include "graphics/sky_box.h"
#include "graphics/texture.h"
#include "graphics/uniform_buffer.h"
#include "graphics/vertex_array.h"
#include "graphics/vertex_buffer.h"

constexpr size_t kMaxCubeInstanceCount = 25000;

constexpr size_t kCubeVertexCount = 24;
constexpr size_t kCubeIndexCount = 36;

struct CameraData final {
  glm::mat4 view;
  glm::mat4 proj;
};

struct RenderStats final {
  uint32_t draw_calls = 0;
  uint32_t vertex_count = 0;
  uint32_t index_count = 0;
  uint32_t instance_count = 0;
};

struct CubeVertex final {
  glm::vec3 position;
  glm::vec3 normal;
};

struct CubeInstanceData final {
  glm::vec4 color;
  glm::vec3 offset;
};

struct LineVertex final {
  glm::vec4 position;
  glm::vec4 color;
};

template <typename InstanceDataType>
struct InstancedRenderData {
  std::shared_ptr<VertexArray> vertex_array;
  std::shared_ptr<VertexBuffer> vertex_buffer;
  std::shared_ptr<VertexBuffer> instance_buffer;
  std::shared_ptr<IndexBuffer> index_buffer;
  std::shared_ptr<Shader> shader;

  std::vector<InstanceDataType> data;
};

class Renderer final {
 public:
  Renderer();
  ~Renderer();

  void BeginScene(const CameraData& camera_data);

  void EndScene();

  void DrawCube(const glm::vec3& position, const Material& material);

  [[nodiscard]] const RenderStats& GetStats() const { return stats_; }

  void ResetStats();

 private:
  bool NeedsNewBatch(uint32_t index_count, uint32_t old_count);

  void BeginBatch();

  void Flush();

  void NextBatch();

 private:
  InstancedRenderData<CubeInstanceData> cube_data_;

  std::unique_ptr<SkyBox> sky_box_;
  std::unique_ptr<Shader> sky_box_shader_;

  std::shared_ptr<UniformBuffer> camera_uniform_buffer_;

  RenderStats stats_;
};
