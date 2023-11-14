// Copyright (c) 2023 Berke Umut Biricik All Rights Reserved

#include "core/utils/timer.h"

Timer::Timer() : last_frame_time_(std::chrono::high_resolution_clock::now()) {}

float Timer::Tick() {
  auto current_time = std::chrono::high_resolution_clock::now();
  std::chrono::duration<float, std::chrono::seconds::period> delta_time =
      current_time - last_frame_time_;
  last_frame_time_ = current_time;
  return delta_time.count();
}
