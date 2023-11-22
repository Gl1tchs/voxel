// Copyright (c) 2023 Berke Umut Biricik All Rights Reserved

#include "game_camera.h"

#include "core/event/event_handler.h"
#include "core/event/events.h"
#include "core/event/input.h"

GameCamera::GameCamera() {
  last_mouse_pos_ = Input::GetMousePosition();

  if (Input::IsKeyReleased(KeyCode::kLeftShift)) {
    speed_ /= 1.5f;
  }

  SubscribeEvent<KeyPressEvent>([this](const KeyPressEvent& event) {
    if (event.GetKeyCode() == KeyCode::kLeftShift) {
      SetSpeed(15.0f);
    }
  });

  SubscribeEvent<KeyReleaseEvent>([this](const KeyReleaseEvent& event) {
    if (event.GetKeyCode() == KeyCode::kLeftShift) {
      SetSpeed(5.0f);
    }
  });
}

void GameCamera::Update(float ds) {
  glm::vec2 mouse_delta = Input::GetMousePosition() - last_mouse_pos_;

  glm::vec3 new_rotation =
      GetTransform().rotation +
      glm::vec3(-mouse_delta.y, -mouse_delta.x, 0.0f) * sensitivity_;

  // clamp between (-90,90) to make it realistic :)
  new_rotation.x = glm::clamp(new_rotation.x, -89.0f, 89.0f);

  GetTransform().rotation = new_rotation;

  // store last mouse pos to prevent instant rotations
  last_mouse_pos_ = Input::GetMousePosition();

  // forward / backward controls
  if (Input::IsKeyPressed(KeyCode::kW)) {
    GetTransform().position += GetTransform().GetForward() * speed_ * ds;
  }
  if (Input::IsKeyPressed(KeyCode::kS)) {
    GetTransform().position -= GetTransform().GetForward() * speed_ * ds;
  }

  // right / left controls
  if (Input::IsKeyPressed(KeyCode::kD)) {
    GetTransform().position += GetTransform().GetRight() * speed_ * ds;
  }
  if (Input::IsKeyPressed(KeyCode::kA)) {
    GetTransform().position -= GetTransform().GetRight() * speed_ * ds;
  }

  // up / down controls
  if (Input::IsKeyPressed(KeyCode::kE)) {
    GetTransform().position += kWorldUp * speed_ * ds;
  }
  if (Input::IsKeyPressed(KeyCode::kQ)) {
    GetTransform().position -= kWorldUp * speed_ * ds;
  }
}

void GameCamera::ResetMousePosition() {
  last_mouse_pos_ = Input::GetMousePosition();
}
