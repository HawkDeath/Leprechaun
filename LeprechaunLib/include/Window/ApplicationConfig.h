#ifndef LEPRECHAUN_APPLICATIONCONFIG_H
#define LEPRECHAUN_APPLICATIONCONFIG_H
#include <cstdint>
#include <string>

namespace Leprechaun {
struct ApplicationConfig {
  ApplicationConfig() = default;

  struct  {
    std::int32_t width = 1280;
    std::int32_t height = 720;
  } windowSize;

  struct {
    std::int32_t width = 1280;
    std::int32_t height = 720;
  } framebufferSize;

  std::string title = "Leprechaun";
  
};

}

#endif // LEPRECHAUN_APPLICATIONCONFIG_H