#include "input.h"
#include "../ui/ui.h"

void handle_movement(GLFWwindow* window, int key, int action) {
    (void)window;
    (void)key;
    (void)action;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    (void)scancode;
    (void)mods;

    if (key == GLFW_KEY_INSERT && action == GLFW_PRESS)
        show_debug = !show_debug;

    handle_movement(window, key, action);
}