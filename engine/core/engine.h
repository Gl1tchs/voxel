// Copyright (c) 2023 Berke Umut Biricik All Rights Reserved

#pragma once

#include <memory>
#include <string>
#include <type_traits>

#include "core/layer_stack.h"
#include "core/state.h"
#include "ui/imgui_layer.h"

class Engine {
 public:
  Engine(WindowProps window_props = WindowProps{});
  virtual ~Engine();

  void StartEventLoop();

  std::shared_ptr<State> GetState() { return state_; }
  const std::shared_ptr<State>& GetState() const { return state_; }

  static Engine& Get() { return *engine_; };

  void PushLayer(Layer* layer);

  template <typename T>
    requires std::is_base_of_v<Layer, T>
  void PushLayer() {
    PushLayer(new T(GetState()));
  }

  void PushOverlay(Layer* overlay);

  template <typename T>
    requires std::is_base_of_v<Layer, T>
  void PushOverlay() {
    PushOverlay(new T(GetState()));
  }

  void PopLayer(Layer* layer);
  void PopOverlay(Layer* overlay);

 private:
  static Engine* engine_;
  std::shared_ptr<State> state_;

  LayerStack layers_;
  ImGuiLayer* imgui_layer_;
};
