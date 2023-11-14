set(CORE_SOURCES
  core/debug/assert.h
  core/debug/log.cc
  core/debug/log.h
  core/event/event_handler.h
  core/event/event_handler.inl
  core/event/events.h
  core/event/input.cc
  core/event/input.h
  core/event/key_code.h
  core/event/key_event.h
  core/event/mouse_code.h
  core/event/mouse_event.h
  core/event/window_event.h
  core/math/transform.cc
  core/math/transform.h
  core/utils/timer.cc
  core/utils/timer.h
  core/utils/uuid.cc
  core/utils/uuid.h
  core/engine.cc
  core/engine.h
  core/layer_stack.cc
  core/layer_stack.h
  core/layer.cc
  core/layer.h
  core/prelude.h
  core/state.h
  core/window.cc
  core/window.h
)

set(GRAPHICS_SOURCES
  graphics/buffer_layout.cc
  graphics/buffer_layout.h
  graphics/camera.cc
  graphics/camera.h
  graphics/frame_buffer.cc
  graphics/frame_buffer.h
  graphics/index_buffer.cc
  graphics/index_buffer.h
  graphics/material.h
  graphics/render_command.cc
  graphics/render_command.h
  graphics/renderer.cc
  graphics/renderer.h
  graphics/shader.cc
  graphics/shader.h
  graphics/sky_box.cc
  graphics/sky_box.h
  graphics/texture.cc
  graphics/texture.h
  graphics/uniform_buffer.cc
  graphics/uniform_buffer.h
  graphics/vertex_array.cc
  graphics/vertex_array.h
  graphics/vertex_buffer.cc
  graphics/vertex_buffer.h
)

set(UI_SOURCES
  ui/imgui_layer.cc
  ui/imgui_layer.h
)

set(SOURCES)
list(APPEND SOURCES
  ${CORE_SOURCES}
  ${GRAPHICS_SOURCES}
  ${UI_SOURCES}
)

# Append opengl backend sources
list(APPEND SOURCES ${IMGUI_OPENGL_SOURCES})

add_library(voxel-engine STATIC ${SOURCES})

target_include_directories(voxel-engine PUBLIC
  ${CMAKE_SOURCE_DIR}/engine
  ${VENDOR_DIR}/glm
)

target_include_directories(voxel-engine PRIVATE
  ${VENDOR_DIR}/glad/include
  ${VENDOR_DIR}/glfw/include
  ${VENDOR_DIR}/include
  ${VENDOR_DIR}/imgui
  ${VENDOR_DIR}/spdlog/include
)

target_link_libraries(voxel-engine PRIVATE
  glad
  glfw
  glm
  ImGui
  spdlog
)

target_compile_definitions(voxel-engine PRIVATE GLFW_INCLUDE_NONE)
