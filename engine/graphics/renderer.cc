// Copyright (c) 2023 Berke Umut Biricik All Rights Reserved

#include "graphics/renderer.h"

#include <numeric>

#include "graphics/render_command.h"

constexpr CubeVertex kCubeVertices[kCubeVertexCount] = {
    // Front face
    {{-0.5f, -0.5f, 0.5f}, kVec3Forward},
    {{0.5f, -0.5f, 0.5f}, kVec3Forward},
    {{0.5f, 0.5f, 0.5f}, kVec3Forward},
    {{-0.5f, 0.5f, 0.5f}, kVec3Forward},

    // Back face
    {{0.5f, -0.5f, -0.5f}, kVec3Back},
    {{-0.5f, -0.5f, -0.5f}, kVec3Back},
    {{-0.5f, 0.5f, -0.5f}, kVec3Back},
    {{0.5f, 0.5f, -0.5f}, kVec3Back},

    // Right face
    {{0.5f, -0.5f, 0.5f}, kVec3Right},
    {{0.5f, -0.5f, -0.5f}, kVec3Right},
    {{0.5f, 0.5f, -0.5f}, kVec3Right},
    {{0.5f, 0.5f, 0.5f}, kVec3Right},

    // Left face
    {{-0.5f, -0.5f, -0.5f}, kVec3Left},
    {{-0.5f, -0.5f, 0.5f}, kVec3Left},
    {{-0.5f, 0.5f, 0.5f}, kVec3Left},
    {{-0.5f, 0.5f, -0.5f}, kVec3Left},

    // Top face
    {{-0.5f, 0.5f, 0.5f}, kVec3Up},
    {{0.5f, 0.5f, 0.5f}, kVec3Up},
    {{0.5f, 0.5f, -0.5f}, kVec3Up},
    {{-0.5f, 0.5f, -0.5f}, kVec3Up},

    // Bottom face
    {{-0.5f, -0.5f, -0.5f}, kVec3Down},
    {{0.5f, -0.5f, -0.5f}, kVec3Down},
    {{0.5f, -0.5f, 0.5f}, kVec3Down},
    {{-0.5f, -0.5f, 0.5f}, kVec3Down},
};

constexpr uint32_t kCubeIndices[kCubeIndexCount] = {
    0,  1,  2,  2,  3,  0,   // Front face
    4,  5,  6,  6,  7,  4,   // Back face
    8,  9,  10, 10, 11, 8,   // Right face
    12, 13, 14, 14, 15, 12,  // Left face
    16, 17, 18, 18, 19, 16,  // Top face
    20, 21, 22, 22, 23, 20   // Bottom face
};

Renderer::Renderer() {
  RenderCommand::Init();

  // Cube render data initialization
  {
    cube_data_.vertex_array = std::make_shared<VertexArray>();

    // create vertex buffer
    cube_data_.vertex_buffer =
        std::make_shared<VertexBuffer>(kCubeVertices, sizeof(kCubeVertices));
    cube_data_.vertex_buffer->SetLayout(
        {{ShaderDataType::kFloat3, "a_pos"},
         {ShaderDataType::kFloat3, "a_normal"}});
    cube_data_.vertex_array->AddVertexBuffer(cube_data_.vertex_buffer);

    // create instance buffer
    cube_data_.instance_buffer = std::make_shared<VertexBuffer>(
        kMaxCubeInstanceCount * sizeof(CubeInstanceData));
    cube_data_.instance_buffer->SetLayout(
        {{ShaderDataType::kFloat3, "a_ambient", false, 1},
         {ShaderDataType::kFloat3, "a_diffuse", false, 1},
         {ShaderDataType::kFloat3, "a_specular", false, 1},
         {ShaderDataType::kFloat, "a_shininess", false, 1},
         {ShaderDataType::kFloat3, "a_offset", false, 1}});
    cube_data_.vertex_array->AddVertexBuffer(cube_data_.instance_buffer);

    // create index buffer
    cube_data_.index_buffer =
        std::make_shared<IndexBuffer>(kCubeIndices, kCubeIndexCount);
    cube_data_.vertex_array->SetIndexBuffer(cube_data_.index_buffer);

    // create shader
    cube_data_.shader = std::make_shared<Shader>(
        std::filesystem::path("assets/shaders/cube.vert"),
        std::filesystem::path("assets/shaders/cube.frag"));
  }

  // Sky box initialization
  {
    std::vector<std::string> faces{
        "assets/textures/skybox/right.jpg", "assets/textures/skybox/left.jpg",
        "assets/textures/skybox/top.jpg",   "assets/textures/skybox/bottom.jpg",
        "assets/textures/skybox/front.jpg", "assets/textures/skybox/back.jpg"};

    sky_box_ = std::make_unique<SkyBox>(faces);

    sky_box_shader_ = std::make_unique<Shader>(
        std::filesystem::path("assets/shaders/sky_box.vert"),
        std::filesystem::path("assets/shaders/sky_box.frag"));

    sky_box_shader_->Bind();
    sky_box_shader_->SetUniform("u_skybox", 0);
  }

  camera_uniform_buffer_ =
      std::make_shared<UniformBuffer>(sizeof(CameraData), 0);
}

Renderer::~Renderer() {}

void Renderer::BeginScene(const CameraData& camera_data) {
  camera_uniform_buffer_->SetData(&camera_data, sizeof(CameraData));

  BeginBatch();
}

void Renderer::EndScene() {
  Flush();
}

void Renderer::DrawCube(const glm::vec3& position, const Material& material) {
  if (cube_data_.data.size() + 1 >= kMaxCubeInstanceCount) {
    NextBatch();
  }

  cube_data_.data.push_back({material.ambient, material.diffuse,
                             material.specular, material.shininess, position});

  stats_.instance_count++;
}

void Renderer::ResetStats() {
  memset(&stats_, 0, sizeof(RenderStats));
}

void Renderer::BeginBatch() {
  cube_data_.data.clear();
}

void Renderer::Flush() {
  if (cube_data_.data.size() > 0) {
    cube_data_.instance_buffer->SetData(
        cube_data_.data.data(),
        cube_data_.data.size() * sizeof(CubeInstanceData));

    cube_data_.shader->Bind();
    RenderCommand::DrawElementsInstanced(
        cube_data_.vertex_array, kCubeIndexCount, cube_data_.data.size());

    stats_.draw_calls++;
  }

  {
    RenderCommand::SetDepthFunc(DepthFunc::kLEQUAL);

    sky_box_shader_->Bind();
    RenderCommand::SetActiveTexture(0);
    sky_box_->Bind();
    RenderCommand::DrawArrays(sky_box_->GetVertexArray(), kSkyBoxVertexCount);

    RenderCommand::SetDepthFunc(DepthFunc::kLess);
  }
}

void Renderer::NextBatch() {
  Flush();
  BeginBatch();
}
