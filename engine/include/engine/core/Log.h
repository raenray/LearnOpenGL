#pragma once

#include <memory>
#include <spdlog/spdlog.h>


#define LOG_CORE_TRACE(...) spdlog::trace(__VA_ARGS__)
#define LOG_CORE_DEBUG(...) spdlog::debug(__VA_ARGS__)
#define LOG_CORE_INFO(...) spdlog::info(__VA_ARGS__)
#define LOG_CORE_WARN(...) spdlog::warn(__VA_ARGS__)
#define LOG_CORE_ERROR(...) spdlog::error(__VA_ARGS__)
#define LOG_CORE_CRITICAL(...) spdlog::critical(__VA_ARGS__)

#define LOG_TRACE(...) spdlog::trace(__VA_ARGS__)
#define LOG_DEBUG(...) spdlog::debug(__VA_ARGS__)
#define LOG_INFO(...) spdlog::info(__VA_ARGS__)
#define LOG_WARN(...) spdlog::warn(__VA_ARGS__)
#define LOG_ERROR(...) spdlog::error(__VA_ARGS__)
#define LOG_CRITICAL(...) spdlog::critical(__VA_ARGS__)
