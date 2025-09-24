cmake_minimum_required(VERSION 3.10)
project(GameGLFW C CXX)

set(CMAKE_C_STANDARD 11)
set(OpenGL_GL_PREFERENCE GLVND)

# Find OpenGL and GLFW
find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_search_module(GLFW REQUIRED glfw3)

# Include directories (GLFW, OpenGL, and local includes)
include_directories(
    ${GLFW_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIR}
    include
    vendor/cimgui
    vendor/cimgui/imgui
    vendor/cimgui/backends
)

# Find source and header files
file(GLOB_RECURSE SRC_FILES src/*.c)
file(GLOB_RECURSE IMGUI_BACKEND_FILES
    vendor/cimgui/imgui/backends/imgui_impl_glfw.cpp
    vendor/cimgui/imgui/backends/imgui_impl_opengl3.cpp
)

# Add the executable
add_executable(
    Game
    ${SRC_FILES}
)

# Add cimgui subdirectory to handle its source files
add_subdirectory(vendor/cimgui)

# Link libraries (cimgui automatically links imgui as it's part of the submodule)
target_link_libraries(
    Game
    ${GLFW_LIBRARIES}
    ${OPENGL_gl_LIBRARY}
    dl
    m
    cimgui  # Linking cimgui will automatically include imgui
)

target_sources(Game PRIVATE ${IMGUI_BACKEND_FILES})

# Optionally, add compiler flags (useful for debugging)
target_compile_options(Game PRIVATE -Wall -Wextra -g)

