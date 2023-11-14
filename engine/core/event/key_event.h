// Copyright (c) 2023 Berke Umut Biricik All Rights Reserved

#pragma once

#include <cstdint>

#include "core/event/event_handler.h"
#include "core/event/key_code.h"

class KeyEvent : public Event {
 protected:
  explicit KeyEvent(const uint32_t key_code) : key_code_(key_code) {}

  uint32_t key_code_;

 public:
  [[nodiscard]] KeyCode GetKeyCode() const {
    return static_cast<KeyCode>(key_code_);
  }
};

class KeyPressEvent final : public KeyEvent {
 public:
  explicit KeyPressEvent(const uint32_t key_code, const bool is_repeat = false)
      : KeyEvent(key_code), repeat_(is_repeat) {}

  [[nodiscard]] bool IsRepeat() const { return repeat_; }

 private:
  bool repeat_;
};

class KeyReleaseEvent final : public KeyEvent {
 public:
  explicit KeyReleaseEvent(const uint32_t key_code) : KeyEvent(key_code) {}
};

class KeyTypeEvent final : public KeyEvent {
 public:
  explicit KeyTypeEvent(const uint32_t key_code) : KeyEvent(key_code) {}
};
