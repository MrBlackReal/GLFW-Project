#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void handle_movement(GLFWwindow* window, int key, int action);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);