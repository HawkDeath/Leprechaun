#pragma once
#include <glad/glad.h>
#include <string_view>
#include <string>

#include <cstdint>

namespace Leprechaun {
namespace Api {
class Texture {
public:
  Texture(const std::string &name);
  ~Texture() = default;
  void loadFromMemory(const uint8_t *data, int w, int h, GLenum colorMode) noexcept;
  void loadFromFile(const std::string_view filename);

  const GLuint &getID() noexcept { return mGpuTextureId; }

private:
  GLuint mGpuTextureId;
  std::string mName;
};

} // namespace Api
} // namespace Leprechaun
