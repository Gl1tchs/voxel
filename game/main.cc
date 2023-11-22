// Copyright (c) 2023 Berke Biricik
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "core/prelude.h"

#include "game_layer.h"

int main(int argc, const char* argv[]) {
  Engine* engine = new Engine();
  {
    // Add layers to the loop
    engine->PushLayer<GameLayer>();
  }
  engine->StartEventLoop();
  delete engine;
  return 0;
}
