// Copyright (c) 2023 Berke Umut Biricik All Rights Reserved

#pragma once

#include <cstdint>

#include <glm/glm.hpp>

#include "core/event/event_handler.h"
#include "core/event/mouse_code.h"

class MouseMoveEvent final : public Event {
 public:
  explicit MouseMoveEvent(const float x, const float y) : position_(x, y) {}

  /**
   * @brief Get the position of the event
   */
  [[nodiscard]] glm::vec2 GetPosition() const { return position_; }

 private:
  glm::vec2 position_;
};

class MouseScrollEvent final : public Event {
 public:
  explicit MouseScrollEvent(const float x, const float y) : offset_(x, y) {}

  /**
   * @brief Get the scroll offset at the time of the event.
   */
  [[nodiscard]] glm::vec2 GetOffset() const { return offset_; }

 private:
  glm::vec2 offset_;
};

class MouseButtonEvent : public Event {
 public:
  [[nodiscard]] MouseCode GetButtonCode() const {
    return static_cast<MouseCode>(button_code_);
  }

 protected:
  explicit MouseButtonEvent(const uint32_t button_code)
      : button_code_(button_code) {}

  uint32_t button_code_;
};

class MouseButtonPressEvent final : public MouseButtonEvent {
 public:
  explicit MouseButtonPressEvent(const int button_code)
      : MouseButtonEvent(button_code) {}
};

class MouseButtonReleaseEvent final : public MouseButtonEvent {
 public:
  explicit MouseButtonReleaseEvent(const int button_code)
      : MouseButtonEvent(button_code) {}
};
