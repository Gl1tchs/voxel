// Copyright (c) 2023 Berke Biricik
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#pragma once

#include <memory>

#include "core/window.h"
#include "graphics/renderer.h"

struct State {
  std::shared_ptr<Window> window;
  std::shared_ptr<Renderer> renderer;
  bool running{true};
};
