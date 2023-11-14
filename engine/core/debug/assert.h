// Copyright (c) 2023 Berke Umut Biricik All Rights Reserved

#pragma once

#include <filesystem>

#include "core/debug/log.h"

#if defined(VOXEL_PLATFORM_WIN32)
#define DEBUGBREAK() __debugbreak()
#elif defined(VOXEL_PLATFORM_LINUX)
#include <signal.h>
#define DEBUGBREAK() raise(SIGTRAP)
#else
#error "Platform doesn't support debugbreak yet!"
#endif

#define EXPAND_MACRO(x) x
#define STRINGIFY_MACRO(x) #x

#ifdef VOXEL_DEBUG
#define INTERNAL_ASSERT_IMPL(check, msg, ...) \
  if (!(check)) {                                   \
    LOG_ERROR(msg, __VA_ARGS__);             \
    DEBUGBREAK();                                   \
  }

#define INTERNAL_ASSERT_WITH_MSG(check, ...) \
  INTERNAL_ASSERT_IMPL(check, "Assertion failed: {0}", __VA_ARGS__)

#define INTERNAL_ASSERT_NO_MSG(check)                                 \
  INTERNAL_ASSERT_IMPL(check, "Assertion '{0}' failed at {1}:{2}",    \
                       STRINGIFY_MACRO(check),                              \
                       std::filesystem::path(__FILE__).filename().string(), \
                       __LINE__)

#define INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro

#define INTERNAL_ASSERT_GET_MACRO(...)         \
  EXPAND_MACRO(INTERNAL_ASSERT_GET_MACRO_NAME( \
      __VA_ARGS__, INTERNAL_ASSERT_WITH_MSG, INTERNAL_ASSERT_NO_MSG))

#define ASSERT(...) \
  EXPAND_MACRO(INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(__VA_ARGS__))
#else
#define ASSERT(...)
#endif
