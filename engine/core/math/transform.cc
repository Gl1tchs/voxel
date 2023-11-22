// Copyright (c) 2023 Berke Biricik
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "core/math/transform.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
    : position(position),
      rotation(rotation),
      scale(scale),
      forward_(kVec3Forward),
      right_(kVec3Right),
      up_(kVec3Up) {}

void Transform::Translate(glm::vec3 translation) {
  position = position + translation;
}

void Transform::Rotate(const float angle, const glm::vec3 axis) {
  rotation += angle * axis;
}

glm::vec3 Transform::GetForward() {
  UpdateVectors();
  return forward_;
}

glm::vec3 Transform::GetRight() {
  UpdateVectors();
  return right_;
}

glm::vec3 Transform::GetUp() {
  UpdateVectors();
  return up_;
}

glm::mat4 Transform::GetModelMatrix() const {
  glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);

  transform = glm::rotate(transform, glm::radians(rotation.x), kVec3Right);
  transform = glm::rotate(transform, glm::radians(rotation.y), kVec3Up);
  transform = glm::rotate(transform, glm::radians(rotation.z), kVec3Forward);

  transform = glm::scale(transform, scale);

  return transform;
}

void Transform::UpdateVectors() {
  glm::fquat orientation = glm::fquat(glm::radians(rotation));

  forward_ = glm::normalize(orientation * kVec3Forward);
  right_ = glm::normalize(orientation * kVec3Right);
  up_ = glm::normalize(glm::cross(right_, forward_));
}