// Copyright (c) 2023 Berke Biricik
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#pragma once

#include <memory>

#include "core/layer.h"

class ImGuiLayer : public Layer {
 public:
  ImGuiLayer(std::shared_ptr<State>& state);
  ~ImGuiLayer() = default;

  void Begin();

  void End();

 private:
  void OnStart() override;

  void OnDestroy() override;

  void SetStyle();
};
