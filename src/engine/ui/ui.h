#pragma once
#include <stdbool.h>

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#define CIMGUI_USE_GLFW
#define CIMGUI_USE_OPENGL3
#include "cimgui.h"
#include "cimgui_impl.h"

extern bool show_debug;
extern float rotX, rotY, rotZ;
extern float rot[4];
extern ImVec4 clearColor;

bool ui_init(GLFWwindow* window);
void ui_render();
void ui_shutdown();
