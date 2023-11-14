// Copyright (c) 2023 Berke Umut Biricik All Rights Reserved

#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include <glm/glm.hpp>

enum class ShaderType { kNone = 0, kVertex, kFragment, kGeometry };

[[nodiscard]] std::string SerializeShaderType(ShaderType type);

[[nodiscard]] ShaderType DeserializeShaderType(const std::string& value);

class Shader final {
 public:
  Shader(const std::string& vs_source, const std::string& fs_source,
         const std::string& gs_source = std::string());
  Shader(const std::filesystem::path& vs_path,
         const std::filesystem::path& fs_path,
         const std::filesystem::path& gs_path = std::filesystem::path());
  ~Shader();

  void Bind() const;

  void Unbind() const;

  void SetUniform(const std::string& name, int value) const;
  void SetUniform(const std::string& name, float value) const;
  void SetUniform(const std::string& name, glm::vec2 value) const;
  void SetUniform(const std::string& name, glm::vec3 value) const;
  void SetUniform(const std::string& name, glm::vec4 value) const;
  void SetUniform(const std::string& name, const glm::mat4& value) const;
  void SetUniform(const std::string& name, int count, const int* value) const;
  void SetUniform(const std::string& name, int count, const float* value) const;
  void SetUniform(const std::string& name, int count,
                  const glm::vec2* value) const;
  void SetUniform(const std::string& name, int count,
                  const glm::vec3* value) const;
  void SetUniform(const std::string& name, int count,
                  const glm::vec4* value) const;

  [[nodiscard]] uint32_t GetProgramID() const { return program_; }

 private:
  [[nodiscard]] static std::string LoadShaderSource(
      const std::filesystem::path& path);

  [[nodiscard]] int GetUniformLocation(const std::string& name) const;

  [[nodiscard]] static bool CheckCompileErrors(uint32_t shader,
                                               ShaderType type);

  [[nodiscard]] static uint32_t CompileShader(const std::string& source,
                                              ShaderType type);

 private:
  uint32_t program_;
};