#include "core/engine.h"

#include "core/debug/assert.h"
#include "core/event/event_handler.h"
#include "core/event/events.h"
#include "core/utils/timer.h"

Engine* Engine::engine_ = nullptr;

Engine::Engine() {
  ASSERT(!engine_, "Only one Engine of engine can exists.")
  engine_ = this;

  state_ = std::make_shared<State>();
  state_->window = std::make_shared<Window>();
  state_->renderer = std::make_shared<Renderer>();

  SubscribeEvent<WindowCloseEvent>(
      [this](const WindowCloseEvent& event) { state_->running = false; });

  imgui_layer_ = new ImGuiLayer(state_);
  PushOverlay(imgui_layer_);
}

Engine::~Engine() {}

void Engine::StartEventLoop() {
  Timer timer;
  while (state_->running) {
    float ds = timer.Tick();

    for (Layer* layer : layers_) {
      layer->OnUpdate(ds);
    }

    imgui_layer_->Begin();
    for (Layer* layer : layers_) {
      layer->OnGUI(ds);
    }
    imgui_layer_->End();

    state_->window->SwapBuffers();
  }
}

void Engine::PushLayer(Layer* layer) {
  layers_.PushLayer(layer);
}

void Engine::PushOverlay(Layer* overlay) {
  layers_.PushOverlay(overlay);
}

void Engine::PopLayer(Layer* layer) {
  layers_.PopLayer(layer);
}

void Engine::PopOverlay(Layer* overlay) {
  layers_.PopOverlay(overlay);
}
