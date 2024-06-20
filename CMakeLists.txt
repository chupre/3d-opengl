cmake_minimum_required(VERSION 3.0.0)
project(3d-opengl VERSION 0.1.0 LANGUAGES C)

add_executable(3d-opengl source/main.c source/glad.c)

target_link_libraries(3d-opengl glfw m)
include_directories(${CMAKE_SOURCE_DIR}/external ${CMAKE_SOURCE_DIR}/source)

