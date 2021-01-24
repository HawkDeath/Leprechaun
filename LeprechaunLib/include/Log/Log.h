#pragma once
#include <spdlog/spdlog.h>

#define LOG(...) spdlog::info(__VA_ARGS__);
#define WLOG(...) spdlog::warn(__VA_ARGS__);
#define ELOG(...) spdlog::error(__VA_ARGS__);