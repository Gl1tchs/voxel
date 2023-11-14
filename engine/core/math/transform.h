// Copyright (c) 2023 Berke Umut Biricik All Rights Reserved

#pragma once

#include <glm/glm.hpp>

constexpr glm::vec3 kVec3Up(0.0f, 1.0f, 0.0f);
constexpr glm::vec3 kVec3Down = -kVec3Up;

constexpr glm::vec3 kVec3Right(1.0f, 0.0f, 0.0f);
constexpr glm::vec3 kVec3Left = -kVec3Right;

constexpr glm::vec3 kVec3Forward(0.0f, 0.0f, -1.0f);
constexpr glm::vec3 kVec3Back = -kVec3Forward;

constexpr glm::vec3 kVec3Zero(0.0f, 0.0f, 0.0f);
constexpr glm::vec3 kVec3One(1.0f, 1.0f, 1.0f);

constexpr glm::vec3 kWorldUp = kVec3Up;

struct Transform final {
  glm::vec3 position;
  glm::vec3 rotation;
  glm::vec3 scale;

  Transform(glm::vec3 position = kVec3Zero, glm::vec3 rotation = kVec3Zero,
            glm::vec3 scale = kVec3One);

  void Translate(glm::vec3 translation);

  void Rotate(float angle, glm::vec3 axis);

  [[nodiscard]] glm::vec3 GetForward();

  [[nodiscard]] glm::vec3 GetRight();

  [[nodiscard]] glm::vec3 GetUp();

  [[nodiscard]] glm::mat4 GetModelMatrix() const;

 private:
  void UpdateVectors();

 private:
  glm::vec3 forward_;
  glm::vec3 right_;
  glm::vec3 up_;
};
