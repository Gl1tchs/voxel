// Copyright (c) 2023 Berke Umut Biricik All Rights Reserved

#pragma once

#include <glm/glm.hpp>

#include "core/math/transform.h"

class Camera {
 public:
  Camera(float fov = 60.0f, float near_clip = 0.1f, float far_clip = 100.0f);

  [[nodiscard]] glm::mat4 GetViewMatrix();

  [[nodiscard]] glm::mat4 GetProjectionMatrix() const;

  [[nodiscard]] const float& GetFov() const { return fov_; }
  void SetFov(float fov) { fov_ = fov; }

  [[nodiscard]] const float& GetNearClip() const { return near_clip_; }
  void SetNearClip(float near_clip) { near_clip_ = near_clip; }

  [[nodiscard]] const float& GetFarClip() const { return far_clip_; }
  void SetFarClip(float far_clip) { far_clip_ = far_clip; }

  [[nodiscard]] const float& GetAspectRatio() const { return aspect_ratio_; }
  void SetAspectRatio(float aspect_ratio) { aspect_ratio_ = aspect_ratio; };

  [[nodiscard]] Transform& GetTransform() { return transform_; }
  [[nodiscard]] const Transform& GetTransform() const { return transform_; }

 private:
  Transform transform_;

  float fov_;
  float near_clip_;
  float far_clip_;
  float aspect_ratio_;
};
