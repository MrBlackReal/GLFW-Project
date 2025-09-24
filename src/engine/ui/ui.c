#include "ui.h"
#include "cimgui_impl.h"
#include <stdio.h>
#include <GLFW/glfw3.h>

bool show_debug = true;
float rotX = 0, rotY = 0, rotZ = 0;
float rot[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
ImVec4 clearColor = {0.35f, 0.35f, 0.35f, 1.f};

bool ui_init(GLFWwindow* window) {
    igCreateContext(NULL);

    if (!ImGui_ImplGlfw_InitForOpenGL(window, true)) {
        fprintf(stderr, "ImGui_ImplGlfw_InitForOpenGL failed\n");
        return false;
    }

    if (!ImGui_ImplOpenGL3_Init("#version 130")) {
        fprintf(stderr, "ImGui_ImplOpenGL3_Init failed\n");
        return false;
    }

    igStyleColorsDark(NULL);
    return true;
}

void ui_render() {
    if (!show_debug)
        return;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    igNewFrame();

    igBegin("Debug Menu", &show_debug, 0);
    
    igSliderFloat("X Rot", &rot[0], -1.0F, 1.0F, "%.2f", 0);
    igSliderFloat("Y Rot", &rot[1], -1.0F, 1.0F, "%.2f", 0);
    igSliderFloat("Z Rot", &rot[2], -1.0F, 1.0F, "%.2f", 0);
    igSliderFloat("Angle", &rot[3], -1.0F, 1.0F, "%.2f", 0);

    igColorEdit3("Clear Color", (float *)&clearColor, 0);
    igEnd();

    igRender();
    ImGui_ImplOpenGL3_RenderDrawData(igGetDrawData());
}

void ui_shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    igDestroyContext(NULL);
}
