// Copyright (c) 2023 Berke Umut Biricik All Rights Reserved

#pragma once

#include <chrono>

class Timer final {
 public:
  Timer();

  [[nodiscard]] float Tick();

 private:
  std::chrono::time_point<std::chrono::high_resolution_clock> last_frame_time_;
};
