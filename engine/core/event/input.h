// Copyright (c) 2023 Berke Umut Biricik All Rights Reserved

#pragma once

#include <unordered_map>

#include <glm/glm.hpp>

#include "core/event/key_code.h"
#include "core/event/mouse_code.h"

class Input {
 public:
  static void Init(const glm::dvec2& initial_mouse_pos);

  static bool IsKeyPressed(KeyCode key);

  static bool IsKeyReleased(KeyCode key);

  static bool IsMouseButtonPressed(MouseCode button);

  static bool IsMouseButtonReleased(MouseCode button);

  static glm::dvec2 GetMousePosition();

 private:
  static std::unordered_map<KeyCode, bool> key_press_states_;
  static std::unordered_map<KeyCode, bool> key_release_states_;

  static std::unordered_map<MouseCode, bool> mouse_press_states_;
  static std::unordered_map<MouseCode, bool> mouse_release_states_;

  static glm::dvec2 mouse_position_;
};