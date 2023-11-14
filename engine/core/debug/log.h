// Copyright (c) 2023 Berke Umut Biricik All Rights Reserved

#pragma once

#include <filesystem>
#include <format>
#include <string>

void LogTrace(const std::string& fmt);
void LogInfo(const std::string& fmt);
void LogWarning(const std::string& fmt);
void LogError(const std::string& fmt);
void LogCritical(const std::string& fmt);

#define LOG_TRACE(...) LogTrace(std::format(__VA_ARGS__))
#define LOG_INFO(...) LogInfo(std::format(__VA_ARGS__))
#define LOG_WARNING(...) LogWarning(std::format(__VA_ARGS__))
#define LOG_ERROR(...) LogError(std::format(__VA_ARGS__))
#define LOG_CRITICAL(...) LogCritical(std::format(__VA_ARGS__))
