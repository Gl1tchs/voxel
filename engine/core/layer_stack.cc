// Copyright (c) 2023 Berke Umut Biricik All Rights Reserved

#include "core/layer_stack.h"

LayerStack::~LayerStack() {
  for (Layer* layer : layers_) {
    layer->OnDestroy();
    delete layer;
  }
}

void LayerStack::PushLayer(Layer* layer) {
  layers_.emplace(layers_.begin() + layer_insert_idx_, layer);
  layer_insert_idx_++;

  layer->OnStart();
}

void LayerStack::PushOverlay(Layer* overlay) {
  layers_.emplace_back(overlay);

  overlay->OnStart();
}

void LayerStack::PopLayer(Layer* layer) {
  auto it =
      std::find(layers_.begin(), layers_.begin() + layer_insert_idx_, layer);
  if (it != layers_.begin() + layer_insert_idx_) {
    layer->OnDestroy();
    layers_.erase(it);
    layer_insert_idx_--;
  }
}

void LayerStack::PopOverlay(Layer* overlay) {
  auto it =
      std::find(layers_.begin() + layer_insert_idx_, layers_.end(), overlay);
  if (it != layers_.end()) {
    overlay->OnDestroy();
    layers_.erase(it);
  }
}
