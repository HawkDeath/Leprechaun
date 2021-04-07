#include "Renderer/Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Leprechaun {
namespace Api {

Texture::Texture(const std::string &name) : mGpuTextureId{0}, mName{name} {
  glGenTextures(1, &mGpuTextureId);
}
void Texture::loadFromFile(const std::string_view filename) {
  int w, h, ch;
  stbi_set_flip_vertically_on_load(true);
  uint8_t *data = stbi_load(filename.data(), &w, &h, &ch, 0);

  loadFromMemory(data, w, h);
  stbi_image_free(data);
}

void Texture::loadFromMemory(const uint8_t *data, int w, int h) noexcept {
  if (data == NULL)
    return;

  glBindTexture(GL_TEXTURE_2D, mGpuTextureId);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
               data);
  glGenerateMipmap(GL_TEXTURE_2D);
}

} // namespace Api
} // namespace Leprechaun