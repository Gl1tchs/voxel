// Copyright (c) 2023 Berke Umut Biricik All Rights Reserved

#include "core/event/input.h"

#include "core/event/event_handler.h"
#include "core/event/key_event.h"
#include "core/event/mouse_event.h"

std::unordered_map<KeyCode, bool> Input::key_press_states_ = {};
std::unordered_map<KeyCode, bool> Input::key_release_states_ = {};
std::unordered_map<MouseCode, bool> Input::mouse_press_states_ = {};
std::unordered_map<MouseCode, bool> Input::mouse_release_states_ = {};
glm::dvec2 Input::mouse_position_ = glm::dvec2(0.0f);

void Input::Init(const glm::dvec2& initial_mouse_pos) {
  mouse_position_ = initial_mouse_pos;

  SubscribeEvent<KeyPressEvent>([&](const KeyPressEvent& event) {
    key_press_states_[event.GetKeyCode()] = true;
    key_release_states_[event.GetKeyCode()] = false;
  });

  SubscribeEvent<KeyReleaseEvent>([&](const KeyReleaseEvent& event) {
    key_press_states_[event.GetKeyCode()] = false;
    key_release_states_[event.GetKeyCode()] = true;
  });

  SubscribeEvent<MouseMoveEvent>([&](const MouseMoveEvent& event) {
    mouse_position_ = event.GetPosition();
  });

  SubscribeEvent<MouseButtonPressEvent>(
      [&](const MouseButtonPressEvent& event) {
        mouse_press_states_[event.GetButtonCode()] = true;
        mouse_release_states_[event.GetButtonCode()] = false;
      });

  SubscribeEvent<MouseButtonReleaseEvent>(
      [&](const MouseButtonReleaseEvent& event) {
        mouse_press_states_[event.GetButtonCode()] = false;
        mouse_release_states_[event.GetButtonCode()] = true;
      });
}

bool Input::IsKeyPressed(KeyCode key) {
  auto it = key_press_states_.find(key);
  if (it != key_press_states_.end()) {
    return it->second;
  }
  return false;
}

bool Input::IsKeyReleased(KeyCode key) {
  auto it = key_release_states_.find(key);
  if (it != key_release_states_.end()) {
    return it->second;
  }
  return false;
}

bool Input::IsMouseButtonPressed(MouseCode button) {
  auto it = mouse_press_states_.find(button);
  if (it != mouse_press_states_.end()) {
    return it->second;
  }
  return false;
}

bool Input::IsMouseButtonReleased(MouseCode button) {
  auto it = mouse_release_states_.find(button);
  if (it != mouse_release_states_.end()) {
    return it->second;
  }
  return false;
}

glm::dvec2 Input::GetMousePosition() {
  return mouse_position_;
}
