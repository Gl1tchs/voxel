// Copyright (c) 2023 Berke Umut Biricik All Rights Reserved

#pragma once

#include <memory>

#include "core/window.h"
#include "graphics/renderer.h"

struct State {
  std::shared_ptr<Window> window;
  std::shared_ptr<Renderer> renderer;
  bool running{true};
};
