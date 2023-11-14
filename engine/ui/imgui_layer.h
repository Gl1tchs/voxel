// Copyright (c) 2023 Berke Umut Biricik All Rights Reserved

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
