#ifndef LEPRECHAUN_LOG_H
#define LEPRECHAUN_LOG_H
#include "Logger.h"
#include <stdexcept>

#define RT_THROW(msg) throw std::runtime_error(msg);

#define LOG(...)                                                               \
  do {                                                                         \
    Leprechaun::Logger::print_info(__VA_ARGS__);                               \
  } while (0)
#define WLOG(...)                                                              \
  do {                                                                         \
    Leprechaun::Logger::print_warning(__VA_ARGS__);                            \
  } while (0)
#define ELOG(...)                                                              \
  do {                                                                         \
    Leprechaun::Logger::print_error(__VA_ARGS__);                              \
  } while (0)


#endif // LEPRECHAUN_LOG_H