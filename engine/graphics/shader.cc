// Copyright (c) 2023 Berke Biricik
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "graphics/shader.h"

#include <fstream>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "core/debug/assert.h"

std::string SerializeShaderType(ShaderType type) {
  switch (type) {
    case ShaderType::kVertex:
      return "vertex";
    case ShaderType::kFragment:
      return "fragment";
    case ShaderType::kGeometry:
      return "geometry";
    default:
      return "";
  }
}

ShaderType DeserializeShaderType(const std::string& value) {
  if (value == "vertex")
    return ShaderType::kVertex;
  else if (value == "fragment")
    return ShaderType::kFragment;
  else if (value == "geometry")
    return ShaderType::kGeometry;
  else
    return ShaderType::kNone;
}

int GetOpenGLShaderType(ShaderType type) {
  switch (type) {
    case ShaderType::kVertex:
      return GL_VERTEX_SHADER;
    case ShaderType::kFragment:
      return GL_FRAGMENT_SHADER;
    case ShaderType::kGeometry:
      return GL_GEOMETRY_SHADER;
    default:
      return 0;
  }
}

Shader::Shader(const std::string& vs_source, const std::string& fs_source,
               const std::string& gs_source) {
  program_ = glCreateProgram();

  const uint32_t vertex_shader = CompileShader(vs_source, ShaderType::kVertex);
  glAttachShader(program_, vertex_shader);

  const uint32_t fragment_shader =
      CompileShader(fs_source, ShaderType::kFragment);
  glAttachShader(program_, fragment_shader);

  uint32_t geometry_shader{0};
  if (!gs_source.empty()) {
    geometry_shader = CompileShader(gs_source, ShaderType::kGeometry);
    glAttachShader(program_, geometry_shader);
  }

  glLinkProgram(program_);

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  if (geometry_shader != 0) {
    glDeleteShader(geometry_shader);
  }
}

Shader::Shader(const std::filesystem::path& vs_path,
               const std::filesystem::path& fs_path,
               const std::filesystem::path& gs_path) {
  program_ = glCreateProgram();

  const std::string vertex_source = LoadShaderSource(vs_path);
  const uint32_t vertex_shader =
      CompileShader(vertex_source, ShaderType::kVertex);
  glAttachShader(program_, vertex_shader);

  const std::string fragment_source = LoadShaderSource(fs_path);
  const uint32_t fragment_shader =
      CompileShader(fragment_source, ShaderType::kFragment);
  glAttachShader(program_, fragment_shader);

  uint32_t geometry_shader{0};
  if (!gs_path.empty()) {
    const std::string geometry_source = LoadShaderSource(gs_path);
    geometry_shader = CompileShader(geometry_source, ShaderType::kGeometry);
    glAttachShader(program_, geometry_shader);
  }

  glLinkProgram(program_);

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  if (geometry_shader != 0) {
    glDeleteShader(geometry_shader);
  }
}

Shader::~Shader() {
  glDeleteProgram(program_);
}

void Shader::Bind() const {
  glUseProgram(program_);
}

void Shader::Unbind() const {
  glUseProgram(0);
}

std::string Shader::LoadShaderSource(const std::filesystem::path& path) {
  if (!std::filesystem::exists(path)) {
    LOG_ERROR("Shader file not found at: {0}", path.string());
    return "";
  }

  const std::string include_identifier = "#include ";
  static bool is_recursive_call = false;

  std::string full_source_code;
  std::ifstream file(path);

  if (!file.is_open()) {
    LOG_ERROR("Could not open the shader at: {0}", path.string());
    return full_source_code;
  }

  std::string line_buffer;
  while (std::getline(file, line_buffer)) {
    if (line_buffer.find(include_identifier) != std::string::npos) {
      line_buffer.erase(0, include_identifier.size());

      line_buffer.erase(0, 1);
      line_buffer.erase(line_buffer.size() - 1);

      std::filesystem::path p = path.parent_path();
      line_buffer.insert(0, p.string() + "/");

      is_recursive_call = true;
      full_source_code += LoadShaderSource(line_buffer);

      continue;
    }

    full_source_code += line_buffer + '\n';
  }

  if (!is_recursive_call)
    full_source_code += '\0';

  file.close();

  return full_source_code;
}

int Shader::GetUniformLocation(const std::string& name) const {
  return glGetUniformLocation(program_, name.c_str());
}

void Shader::SetUniform(const std::string& name, const int value) const {
  glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform(const std::string& name, const float value) const {
  glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniform(const std::string& name, const glm::vec2 value) const {
  glUniform2f(GetUniformLocation(name), value.x, value.y);
}

void Shader::SetUniform(const std::string& name, const glm::vec3 value) const {
  glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
}

void Shader::SetUniform(const std::string& name, const glm::vec4 value) const {
  glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
}

void Shader::SetUniform(const std::string& name, const glm::mat4& value) const {
  glUniformMatrix4fv(GetUniformLocation(name), 1, false, glm::value_ptr(value));
}

void Shader::SetUniform(const std::string& name, int count,
                        const int* value) const {
  glUniform1iv(GetUniformLocation(name), count, value);
}

void Shader::SetUniform(const std::string& name, int count,
                        const float* value) const {
  glUniform1fv(GetUniformLocation(name), count, value);
}

void Shader::SetUniform(const std::string& name, int count,
                        const glm::vec2* value) const {
  glUniform2fv(GetUniformLocation(name), count, glm::value_ptr(value[0]));
}

void Shader::SetUniform(const std::string& name, int count,
                        const glm::vec3* value) const {
  glUniform3fv(GetUniformLocation(name), count, glm::value_ptr(value[0]));
}

void Shader::SetUniform(const std::string& name, int count,
                        const glm::vec4* value) const {
  glUniform4fv(GetUniformLocation(name), count, glm::value_ptr(value[0]));
}

bool Shader::CheckCompileErrors(const uint32_t shader, const ShaderType type) {
  int success;
  char info_log[512];

  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, nullptr, info_log);
    LOG_ERROR("Unable to link shader of type: {0}\n{1}",
              SerializeShaderType(type), info_log);
    return false;
  }

  return true;
}

uint32_t Shader::CompileShader(const std::string& source, ShaderType type) {
  ASSERT(type != ShaderType::kNone)

  const char* source_c_str = source.c_str();
  const uint32_t shader = glCreateShader(GetOpenGLShaderType(type));
  glShaderSource(shader, 1, &source_c_str, nullptr);
  glCompileShader(shader);

  ASSERT(CheckCompileErrors(shader, type))

  return shader;
}
