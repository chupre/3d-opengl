cmake_minimum_required(VERSION 3.0)
project(3D-OpenGL VERSION 0.1.0 LANGUAGES C)

# Include directories
include_directories(external include/game include/render)

# Gather all .c source files
set(SOURCES
    source/main.c
    source/render/shader.c
    source/game/player.c
    source/game/update.c
    source/render/render.c
    source/render/camera.c
    source/render/keyboard_input.c
    source/render/window.c
    source/game/prop.c
)

# Add executable target
add_executable(3D-OpenGL ${SOURCES} external/glad/glad.c)

# Optionally link libraries
target_link_libraries(3D-OpenGL glfw m)
