// Copyright (c) 2023 Berke Biricik
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "ui/imgui_layer.h"

#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>
#include <imgui_internal.h>

ImGuiLayer::ImGuiLayer(std::shared_ptr<State>& state) : Layer(state) {}

void ImGuiLayer::Begin() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

void ImGuiLayer::End() {
  ImGuiIO& io = ImGui::GetIO();
  auto size = GetState()->window->GetSize();
  io.DisplaySize = ImVec2((float)size.x, (float)size.y);

  // Rendering
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    GLFWwindow* backup_current_context = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(backup_current_context);
  }
}

void ImGuiLayer::OnStart() {
  // Setup ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

  float font_size = 18.0f;  // TODO add this as an setting
  io.Fonts->AddFontFromFileTTF("assets/fonts/Roboto/Roboto-Bold.ttf",
                               font_size);
  io.FontDefault = io.Fonts->AddFontFromFileTTF(
      "assets/fonts/Roboto/Roboto-Regular.ttf", font_size);

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  SetStyle();

  // Setup Platform/Renderer bindings
  ImGui_ImplGlfw_InitForOpenGL(GetState()->window->GetNativeWindow(), true);
  ImGui_ImplOpenGL3_Init("#version 450");
}

void ImGuiLayer::OnDestroy() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void ImGuiLayer::SetStyle() {
  ImGuiStyle& style = ImGui::GetStyle();

  // Set background alpha to make it transparent
  ImVec4 bgColor =
      ImVec4(0.0f, 0.0f, 0.0f, 0.5f);  // Adjust the alpha value as needed
  style.Colors[ImGuiCol_WindowBg] = bgColor;
  style.Colors[ImGuiCol_Border] =
      ImVec4(0.4f, 0.4f, 0.4f, 0.0f);  // Transparent border

  // Set text color
  style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

  // Set button color
  style.Colors[ImGuiCol_Button] = ImVec4(0.2f, 0.2f, 0.2f, 0.5f);
  style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.3f, 0.3f, 0.3f, 0.7f);
  style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.1f, 0.1f, 0.1f, 0.7f);
}
