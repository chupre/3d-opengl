cmake_minimum_required(VERSION 3.0)
project(3D-OpengGL VERSION 0.1.0 LANGUAGES C)

# Include directories
include_directories(external include)

# Gather all .c source files
set(SOURCES
    source/main.c
    source/shader.c
    source/player.c
    source/update.c
    source/render.c
    source/camera.c
    source/keyboard_input.c
    source/window.c
    source/prop.c
)

# Add executable target
add_executable(3D-OpengGL ${SOURCES} external/glad/glad.c)

# Optionally link libraries
target_link_libraries(3D-OpengGL glfw m)