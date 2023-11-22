// Copyright (c) 2023 Berke Biricik
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "graphics/camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(float fov, float near_clip, float far_clip)
    : fov_(fov),
      near_clip_(near_clip),
      far_clip_(far_clip),
      aspect_ratio_(1.0f) {}

glm::mat4 Camera::GetViewMatrix() {
  return glm::lookAt(transform_.position,
                     transform_.position + transform_.GetForward(),
                     transform_.GetUp());
}

glm::mat4 Camera::GetProjectionMatrix() const {
  return glm::perspective(glm::radians(fov_), aspect_ratio_, near_clip_,
                          far_clip_);
}