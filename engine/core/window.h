// Copyright (c) 2023 Berke Biricik
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#pragma once

#include <string>

#include <glm/glm.hpp>

struct GLFWwindow;

enum class CursorState { kNormal, kHidden };

enum class WindowMode {
  kWindowed,
  kFullscreen,
  kWindowedFullscreen,
};

struct WindowProps {
  glm::ivec2 size = {1280, 720};
  WindowMode mode = WindowMode::kWindowed;
  bool vsync = true;
};

class Window final {
 public:
  Window(WindowProps props = WindowProps{});
  ~Window();

  [[nodiscard]] bool IsOpen();

  void SwapBuffers();

  [[nodiscard]] bool GetVsync();
  void SetVsync(bool value);

  [[nodiscard]] WindowMode GetMode();
  void SetMode(const WindowMode& mode);

  [[nodiscard]] glm::ivec2 GetSize();
  void SetSize(const glm::ivec2& size);

  [[nodiscard]] bool IsMinimized();

  void SetCursorState(CursorState state);

  [[nodiscard]] GLFWwindow* GetNativeWindow();

 private:
  void InitEvents();

  GLFWwindow* window_;
  glm::ivec2 size_;
  bool vsync_;
  WindowMode mode_;
};
