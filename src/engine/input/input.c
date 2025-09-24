#include "input.h"
#include "../ui/ui.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    (void)window;
    (void)scancode;
    (void)mods;

    if (key == GLFW_KEY_TAB && action == GLFW_PRESS)
        show_debug = !show_debug;
}