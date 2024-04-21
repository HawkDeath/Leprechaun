#ifndef LEPRECHAUN_LOG_H
#define LEPRECHAUN_LOG_H

#include "Logger.h"
#include <vulkan/vulkan.h>
#include <stdexcept>

#define RT_THROW(msg) throw std::runtime_error(msg);

#define VK_CHECK(x, msg) if ((x) != VK_SUCCESS) { RT_THROW(msg); }

#define LOG(...)                                                               \
  do {                                                                         \
    Leprechaun::get_logger().print_info(__VA_ARGS__);                         \
  } while (0)
#define WLOG(...)                                                              \
  do {                                                                         \
    Leprechaun::get_logger().print_warning(__VA_ARGS__);                      \
  } while (0)
#define ELOG(...)                                                              \
  do {                                                                         \
    Leprechaun::get_logger().print_error(__VA_ARGS__);                        \
  } while (0)


#endif // LEPRECHAUN_LOG_H