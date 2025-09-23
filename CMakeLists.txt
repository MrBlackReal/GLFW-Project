cmake_minimum_required(VERSION 3.10)
project(GameGLFW)

set(CMAKE_C_STANDARD 11)
set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

include_directories(
    ${GLFW_INCLUDE_DIRS}
    include
)

file(GLOB_RECURSE SRC_FILES src/*.c)
file(GLOB_RECURSE HEADER_FILES include/*.h)

add_executable(Game ${SRC_FILES} ${HEADER_FILES})

target_link_libraries(Game
    ${GLFW_LIBRARIES}
    ${OPENGL_gl_LIBRARY}
    dl m
)
