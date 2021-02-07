#include "Renderer/Shader.h"
#include "Log/Log.h"

namespace Leprechaun {
namespace Api {
Shader::Shader(ShaderDescription &pipeline) : mProgram(0), mPipeline(pipeline) {
  compileShader();
}

Shader::~Shader() { destroyProgram(); }

void Shader::use() noexcept { glUseProgram(mProgram); }

void Shader::unUse() noexcept { glUseProgram(0); }

void Shader::setInt(const std::string &name, const int &value) const noexcept {
  auto uniformLocation = getUniform(name);
  glUniform1i(uniformLocation, value);
}

void Shader::setFloat(const std::string &name,
                      const float &value) const noexcept {
  auto uniformLocation = getUniform(name);
  glUniform1f(uniformLocation, value);
}

void Shader::setDouble(const std::string &name,
                       const double &value) const noexcept {
  auto uniformLocation = getUniform(name);
  glUniform1d(uniformLocation, value);
}

void Shader::setVec2(const std::string &name,
                     const glm::vec2 &value) const noexcept {
  auto uniformLocation = getUniform(name);
  glUniform2fv(uniformLocation, 1, &value[0]);
}

void Shader::setVec3(const std::string &name,
                     const glm::vec3 &value) const noexcept {
  auto uniformLocation = getUniform(name);
  glUniform3fv(uniformLocation, 1, &value[0]);
}

void Shader::setVec4(const std::string &name,
                     const glm::vec4 &value) const noexcept {
  auto uniformLocation = getUniform(name);
  glUniform4fv(uniformLocation, 1, &value[0]);
}

void Shader::setMat2(const std::string &name,
                     const glm::mat2 &value) const noexcept {
  auto uniformLocation = getUniform(name);
  glUniformMatrix2fv(uniformLocation, 1, GL_FALSE, &value[0][0]);
}

void Shader::setMat3(const std::string &name,
                     const glm::mat3 &value) const noexcept {
  auto uniformLocation = getUniform(name);
  glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, &value[0][0]);
}

void Shader::setMat4(const std::string &name,
                     const glm::mat4 &value) const noexcept {
  auto uniformLocation = getUniform(name);
  glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &value[0][0]);
}

GLuint Shader::getUniform(const std::string &uniformName) const noexcept {
  return glGetUniformLocation(mProgram, uniformName.c_str());
}

void Shader::compileShader() {

  if (mPipeline.vertexShaderSources == nullptr) {
    WLOG("[Shader] '\'{}\' has not define vertex shader", mPipeline.name)
    return;
  }

  if (mPipeline.fragmenShaderSources == nullptr) {
    WLOG("[Shader] '\'{}\' has not define fragment shader", mPipeline.name)
    return;
  }

  GLuint vertexShader = 0, fragmentShader = 0;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &mPipeline.vertexShaderSources, nullptr);
  glCompileShader(vertexShader);
  checkCompilerErrors(vertexShader, "Vertex");

  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &mPipeline.fragmenShaderSources, nullptr);
  glCompileShader(fragmentShader);
  checkCompilerErrors(fragmentShader, "Fragment");

  mProgram = glCreateProgram();
  glAttachShader(mProgram, vertexShader);
  glAttachShader(mProgram, fragmentShader);

  glLinkProgram(mProgram);
  checkCompilerErrors(mProgram, "Program");
  deleteShader(vertexShader);
  deleteShader(fragmentShader);
}

void Shader::checkCompilerErrors(GLuint &shader,
                                 const std::string &type) noexcept {
  GLint success;
  GLchar bufferInfo[1024];
  if (type == "Program") {
    glGetShaderiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(shader, 1024, nullptr, bufferInfo);
      ELOG("[Shader] \'{0}\' Program link status error {1}", mPipeline.name,
           bufferInfo)
    }
  } else {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(shader, 1024, nullptr, bufferInfo);
      ELOG("[Shader] \'{0}\' {2} compile status error {1}", mPipeline.name,
           bufferInfo, type)
    }
  }
}

void Shader::deleteShader(GLuint &shader) {
  if (shader) {
    glDeleteShader(shader);
  }
}

void Shader::destroyProgram() {
  if (mProgram) {
    glDeleteProgram(mProgram);
    LOG("[Shader] Shader \'{0}\' has been delete", mPipeline.name)
  }
}
} // namespace Api
} // namespace Leprechaun