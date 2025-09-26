#pragma once
#include <stdbool.h>

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#define CIMGUI_USE_GLFW
#define CIMGUI_USE_OPENGL3
#include "cimgui.h"
#include "cimgui_impl.h"

extern bool show_debug;
extern float angle, fps, minFps, maxFps, fpsTimer;
extern int rot[3], frames;
extern ImVec4 clearColor;

bool ui_init(GLFWwindow* window);
void ui_render(GLFWwindow* window);
void ui_shutdown();

void update_fps_counter(float deltaTime);
