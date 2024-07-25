cmake_minimum_required(VERSION 3.0)
project(3D-OpenGL VERSION 0.1.0 LANGUAGES C)

# Include directories
include_directories(external include/game include/render include/game/physics)

# Gather all .c source files
set(SOURCES
    source/game_entry.c
    source/render/shader.c
    source/game/player.c
    source/game/update.c
    source/render/render.c
    source/render/camera.c
    source/render/input.c
    source/render/window.c
    source/game/object.c
    source/game/physics/collision.c
    source/game/vector.c
    source/game/octree.c
)

# Add executable target
add_executable(3D-OpenGL ${SOURCES} external/glad/glad.c)

# Link libraries
if (WIN32)
    target_link_libraries(3D-OpenGL ${CMAKE_CURRENT_SOURCE_DIR}/external/GLFW/glfw3.lib)
else()
    target_link_libraries(3D-OpenGL glfw m)
endif()
