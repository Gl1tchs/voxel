// Copyright (c) 2023 Berke Biricik
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#pragma once

#include <glm/glm.hpp>

#include "graphics/camera.h"

class GameCamera : public Camera {
 public:
  GameCamera();

  void Update(float ds);

  void ResetMousePosition();

  [[nodiscard]] const float& GetSpeed() const { return speed_; }
  void SetSpeed(float speed) { speed_ = speed; }

  [[nodiscard]] const float& GetSensitivity() const { return sensitivity_; }
  void SetSensitivity(float sensitivity) { sensitivity_ = sensitivity; }

 private:
  glm::dvec2 last_mouse_pos_;
  float speed_{5.0f};
  float sensitivity_{0.1f};
};
