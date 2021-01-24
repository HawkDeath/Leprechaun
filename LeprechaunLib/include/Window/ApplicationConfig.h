#pragma once

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
    std::int32_t majorVersion = 4;
    std::int32_t minorVersion = 6;
  } openGlSettings;

  struct {
    std::int32_t width = 1280;
    std::int32_t height = 720;
  } framebufferSize;

  std::string title = "Leprechaun";
  
};

}