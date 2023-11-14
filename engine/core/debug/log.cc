// Copyright (c) 2023 Berke Umut Biricik All Rights Reserved

#include "core/debug/log.h"

#include <spdlog/spdlog.h>

void LogTrace(const std::string& fmt) {
  spdlog::trace(fmt);
}

void LogInfo(const std::string& fmt) {
  spdlog::info(fmt);
}

void LogWarning(const std::string& fmt) {
  spdlog::warn(fmt);
}

void LogError(const std::string& fmt) {
  spdlog::error(fmt);
}

void LogCritical(const std::string& fmt) {
  spdlog::critical(fmt);
}
