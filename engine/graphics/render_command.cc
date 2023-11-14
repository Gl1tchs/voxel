// Copyright (c) 2023 Berke Umut Biricik All Rights Reserved

#include "graphics/render_command.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "core/debug/assert.h"

static void OpenGLMessageCallback(uint32_t source, uint32_t type, uint32_t id,
                                  uint32_t severity, int32_t length,
                                  const char* message, const void* user_param);

void RenderCommand::Init() {
  int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  ASSERT(status, "Failed to initialize Glad!")

#ifdef VOXEL_DEBUG
  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(OpenGLMessageCallback, nullptr);
#endif

  LOG_TRACE("OpenGL Info:");
  LOG_TRACE("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
  LOG_TRACE("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
  LOG_TRACE("  Version: {0}", (const char*)glGetString(GL_VERSION));

  ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5),
         "Requires at least OpenGL version of 4.5!")

  glEnable(GL_BLEND);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glEnable(GL_LINE_SMOOTH);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
}

void RenderCommand::SetViewport(uint32_t x, uint32_t y, uint32_t w,
                                uint32_t h) {
  glViewport(x, y, w, h);
}

void RenderCommand::SetClearColor(const glm::vec4& color) {
  glClearColor(color.x, color.y, color.z, color.w);
}

[[nodiscard]] static bool HasFlag(uint16_t flags, BufferBits flag) {
  return (flags & flag) != 0;
}

void RenderCommand::Clear(uint16_t bits) {
  uint16_t flags = 0;

  if (HasFlag(bits, BufferBits_kColor)) {
    flags |= GL_COLOR_BUFFER_BIT;
  }

  if (HasFlag(bits, BufferBits_kDepth)) {
    flags |= GL_DEPTH_BUFFER_BIT;
  }

  glClear(flags);
}

void RenderCommand::DrawArrays(const std::shared_ptr<VertexArray>& vertex_array,
                               uint32_t vertex_count) {
  vertex_array->Bind();
  glDrawArrays(GL_TRIANGLES, 0, vertex_count);
}

void RenderCommand::DrawIndexed(
    const std::shared_ptr<VertexArray>& vertex_array, uint32_t index_count) {
  vertex_array->Bind();
  uint32_t count =
      index_count ? index_count : vertex_array->GetIndexBuffer()->GetCount();
  glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}

void RenderCommand::DrawLines(const std::shared_ptr<VertexArray>& vertex_array,
                              uint32_t vertex_count) {
  vertex_array->Bind();
  glDrawArrays(GL_LINES, 0, vertex_count);
}

void RenderCommand::DrawArraysInstanced(
    const std::shared_ptr<VertexArray>& vertex_array, uint32_t vertex_count,
    uint32_t instance_count) {
  vertex_array->Bind();
  glDrawArraysInstanced(GL_TRIANGLES, 0, vertex_count, instance_count);
}

void RenderCommand::DrawElementsInstanced(
    const std::shared_ptr<VertexArray>& vertex_array, uint32_t index_count,
    uint32_t instance_count) {
  vertex_array->Bind();
  glDrawElementsInstanced(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, nullptr,
                          instance_count);
}

void RenderCommand::SetLineWidth(float width) {
  glLineWidth(width);
}

void RenderCommand::SetActiveTexture(uint8_t index) {
  glActiveTexture(GL_TEXTURE0 + index);
}

void RenderCommand::SetDepthFunc(DepthFunc func) {
  int gl_func;
  switch (func) {
    case DepthFunc::kLess:
      gl_func = GL_LESS;
      break;
    case DepthFunc::kLEQUAL:
      gl_func = GL_LEQUAL;
      break;
    default:
      gl_func = GL_LESS;
      break;
  }

  glDepthFunc(gl_func);
}

void OpenGLMessageCallback(uint32_t source, uint32_t type, uint32_t id,
                           uint32_t severity, int32_t, const char* message,
                           const void*) {
  // Convert GLenum parameters to strings
  std::string source_string;
  switch (source) {
    case GL_DEBUG_SOURCE_API:
      source_string = "API";
      break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
      source_string = "Window System";
      break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
      source_string = "Shader Compiler";
      break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:
      source_string = "Third Party";
      break;
    case GL_DEBUG_SOURCE_APPLICATION:
      source_string = "Application";
      break;
    case GL_DEBUG_SOURCE_OTHER:
      source_string = "Other";
      break;
    default:
      source_string = "Unknown";
      break;
  }

  std::string type_string;
  switch (type) {
    case GL_DEBUG_TYPE_ERROR:
      type_string = "Error";
      break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
      type_string = "Deprecated Behavior";
      break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
      type_string = "Undefined Behavior";
      break;
    case GL_DEBUG_TYPE_PORTABILITY:
      type_string = "Portability";
      break;
    case GL_DEBUG_TYPE_PERFORMANCE:
      type_string = "Performance";
      break;
    case GL_DEBUG_TYPE_MARKER:
      type_string = "Marker";
      break;
    case GL_DEBUG_TYPE_PUSH_GROUP:
      type_string = "Push Group";
      break;
    case GL_DEBUG_TYPE_POP_GROUP:
      type_string = "Pop Group";
      break;
    case GL_DEBUG_TYPE_OTHER:
      type_string = "Other";
      break;
    default:
      type_string = "Unknown";
      break;
  }

  std::string severity_string;
  switch (severity) {
    case GL_DEBUG_SEVERITY_HIGH:
      severity_string = "High";
      break;
    case GL_DEBUG_SEVERITY_MEDIUM:
      severity_string = "Medium";
      break;
    case GL_DEBUG_SEVERITY_LOW:
      severity_string = "Low";
      break;
    case GL_DEBUG_SEVERITY_NOTIFICATION:
      severity_string = "Notification";
      break;
    default:
      severity_string = "Unknown";
      break;
  }

  LOG_TRACE("OpenGL Debug Message:");
  LOG_TRACE("Source: {0}", source_string);
  LOG_TRACE("Type: {0}", type_string);
  LOG_TRACE("ID: {0}", id);
  LOG_TRACE("Severity: {0}", severity_string);
  LOG_TRACE("Message: {0}", message);
}