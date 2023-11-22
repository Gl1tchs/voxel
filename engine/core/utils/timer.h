// Copyright (c) 2023 Berke Biricik
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#pragma once

#include <chrono>

class Timer final {
 public:
  Timer();

  [[nodiscard]] float Tick();

 private:
  std::chrono::time_point<std::chrono::high_resolution_clock> last_frame_time_;
};
