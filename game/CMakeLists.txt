set(SOURCES
  world/world.cc
  world/world.h
  game_camera.cc
  game_camera.h
  game_layer.cc
  game_layer.h
  main.cc
)

add_executable(voxel-game ${SOURCES})

target_include_directories(voxel-game PUBLIC
  ${CMAKE_SOURCE_DIR}/game
  ${CMAKE_SOURCE_DIR}/engine
  ${VENDOR_DIR}/glm
  ${VENDOR_DIR}/imgui
  ${VENDOR_DIR}/include
)

target_link_libraries(voxel-game PRIVATE
  voxel-engine
  glm
  ImGui
)

add_custom_command(TARGET voxel-game PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets
  COMMENT "Copying assets to the build destination."
)
