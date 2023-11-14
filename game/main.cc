// Copyright (c) 2023 Berke Umut Biricik All Rights Reserved

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
