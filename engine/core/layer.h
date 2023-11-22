// Copyright (c) 2023 Berke Biricik
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#pragma once

#include <memory>

#include "core/state.h"

class Layer {
 public:
  Layer(std::shared_ptr<State> state);
  virtual ~Layer() = default;

 private:
  virtual void OnStart() {}

  virtual void OnDestroy() {}

  virtual void OnUpdate(float ds) {}

  virtual void OnGUI(float ds) {}

 protected:
  std::shared_ptr<State>& GetState() { return state_; }
  const std::shared_ptr<State>& GetState() const { return state_; }

 private:
  std::shared_ptr<State> state_;

  friend class Engine;
  friend class LayerStack;
};
