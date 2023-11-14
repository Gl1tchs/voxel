// Copyright (c) 2023 Berke Umut Biricik All Rights Reserved

#pragma once

#include <functional>
#include <type_traits>

class Event {
 protected:
  Event() = default;
};

template <typename T>
concept EventDerived = std::is_base_of_v<Event, T>;

template <EventDerived T>
using EventCallbackFn = std::function<void(const T&)>;

template <typename T>
auto event_callbacks = std::vector<EventCallbackFn<T>>();

template <EventDerived T>
void SubscribeEvent(const EventCallbackFn<T>& callback);

template <EventDerived T>
void UnsubscribeEvent();

template <EventDerived T>
void PopEvent();

template <EventDerived T>
void NotifyEvent(T& event);

#include "core/event/event_handler.inl"
