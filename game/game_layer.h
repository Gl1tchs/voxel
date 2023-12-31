// Copyright (c) 2023 Berke Biricik
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "core/layer.h"

#include "game_camera.h"
#include "world/world.h"

class GameLayer : public Layer {
 public:
  GameLayer(std::shared_ptr<State> state);
  virtual ~GameLayer() = default;

 private:
  void OnStart() override;

  void OnUpdate(float ds) override;

  void OnGUI(float ds) override;

 private:
  World world_;
  GameCamera camera_;

  float fps_timer = 0.0f;
  int frame_count = 0;
};
