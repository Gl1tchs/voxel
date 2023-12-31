// Copyright (c) 2023 Berke Biricik
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

template <EventDerived T>
inline void SubscribeEvent(const EventCallbackFn<T>& callback) {
  event_callbacks<T>.push_back(callback);
}

template <EventDerived T>
inline void UnsubscribeEvent() {
  event_callbacks<T>.clear();
}

template <EventDerived T>
inline void PopEvent() {
  event_callbacks<T>.pop_back();
}

template <EventDerived T>
inline void NotifyEvent(T& event) {
  for (auto& callback : event_callbacks<T>) {
    callback(event);
  }
}
