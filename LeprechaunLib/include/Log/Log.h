#pragma once
#include <spdlog/spdlog.h>
#include <stdexcept>

#define RT_THROW(msg) throw std::runtime_error(msg);

#define LOG(...)                                                               \
  do {                                                                         \
    spdlog::info(__VA_ARGS__);                                                 \
  } while (0)
#define WLOG(...)                                                              \
  do {                                                                         \
    spdlog::warn(__VA_ARGS__);                                                 \
  } while (0)
#define ELOG(...)                                                              \
  do {                                                                         \
    spdlog::error(__VA_ARGS__);                                                \
  } while (0)