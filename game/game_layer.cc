// Copyright (c) 2023 Berke Biricik
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "game_layer.h"

#include <imgui.h>

#include "core/debug/log.h"
#include "core/event/input.h"
#include "graphics/render_command.h"

GameLayer::GameLayer(std::shared_ptr<State> state)
    : Layer(state), world_(GetState()->renderer) {}

void GameLayer::OnStart() {
  camera_.GetTransform().position.y = 24.0f;

  GetState()->window->SetCursorState(CursorState::kHidden);
  GetState()->window->SetVsync(false);
}

void GameLayer::OnUpdate(float ds) {
  camera_.Update(ds);

  auto size = GetState()->window->GetSize();
  camera_.SetAspectRatio(size.x / size.y);

  RenderCommand::Clear(BufferBits_kColor | BufferBits_kDepth);
  RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
  RenderCommand::SetViewport(0, 0, size.x, size.y);

  auto& renderer = GetState()->renderer;

  renderer->ResetStats();

  renderer->BeginScene({camera_.GetViewMatrix(), camera_.GetProjectionMatrix(),
                        camera_.GetTransform().position});

  world_.Render();

  renderer->EndScene();
}

void GameLayer::OnGUI(float ds) {
  fps_timer += ds;
  frame_count++;

  ImGui::SetNextWindowPos(ImVec2(10.0f, 10.0f), ImGuiCond_Always);
  ImGui::SetNextWindowSize(ImVec2(200.0f, 100.0f), ImGuiCond_Always);

  ImGui::Begin(
      "Stats", nullptr,
      ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
          ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar |
          ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings |
          ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBackground);

  float fps = static_cast<float>(frame_count) / fps_timer;

  ImGui::Text("FPS: %.2f", fps);

  if (fps_timer >= 1.0f) {
    fps_timer = 0.0f;
    frame_count = 0;
  }

  const RenderStats& stats = GetState()->renderer->GetStats();

  ImGui::SeparatorText("Render Stats");

  ImGui::Text("Draw Calls: %d", stats.draw_calls);
  ImGui::Text("Instance Count: %d", stats.instance_count);

  ImGui::End();
}
