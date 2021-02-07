#pragma once

#include <glad/glad.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <string_view>

namespace Leprechaun {
namespace Api {

struct ShaderDescription {
  std::string name = "";
  // TODO: not use const char* for shader soruces
  // shader should be get from resource manager
  const char *vertexShaderSources = nullptr;
  const char *fragmenShaderSources = nullptr;
};

class Shader {
public:
  Shader() = default;
  Shader(ShaderDescription &pipeline);
  Shader(const Shader &) = default;
  ~Shader();

  void use() noexcept;
  void unUse() noexcept;

  void setInt(const std::string &name, const int &value) const noexcept;
  void setFloat(const std::string &name, const float &value) const noexcept;
  void setDouble(const std::string &name, const double &value) const noexcept;
  void setVec2(const std::string &name, const glm::vec2 &value) const noexcept;
  void setVec3(const std::string &name, const glm::vec3 &value) const noexcept;
  void setVec4(const std::string &name, const glm::vec4 &value) const noexcept;
  void setMat2(const std::string &name, const glm::mat2 &value) const noexcept;
  void setMat3(const std::string &name, const glm::mat3 &value) const noexcept;
  void setMat4(const std::string &name, const glm::mat4 &value) const noexcept;

  GLuint getProgram() const noexcept { return mProgram; }
  const char *getName() const noexcept { return mPipeline.name.c_str(); }

private:
  void compileShader();
  void checkCompilerErrors(GLuint &shader, const std::string &type) noexcept;

  void deleteShader(GLuint &shader);
  void destroyProgram();
  GLuint getUniform(const std::string &uniformName) const noexcept;

private:
  GLuint mProgram;
  ShaderDescription mPipeline;
};

} // namespace Api
} // namespace Leprechaun