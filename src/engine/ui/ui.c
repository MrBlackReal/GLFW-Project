#include "ui.h"
#include "cimgui_impl.h"
#include <stdio.h>
#include <GLFW/glfw3.h>

bool show_debug = false, enableVsync = true, is_running = true;
float angle = 0.f, fps = 0.f, minFps = 0.f, maxFps = 0.f, fpsTimer = 0.f;
int rot[3] = { 0, 0, 0 }, frames = 0;

ImVec4 clearColor = {0.35f, 0.35f, 0.35f, 1.f};

bool ui_init(GLFWwindow* window) {
    if (!igCreateContext(NULL)) {
        fprintf(stderr, "Failed to setup ImGui Context!\n");
        return false;
    }

    if (!ImGui_ImplGlfw_InitForOpenGL(window, true)) {
        fprintf(stderr, "ImGui_ImplGlfw_InitForOpenGL failed!\n");
        return false;
    }

    if (!ImGui_ImplOpenGL3_Init("#version 130")) {
        fprintf(stderr, "ImGui_ImplOpenGL3_Init failed!\n");
        return false;
    }

    igStyleColorsDark(NULL);

    fprintf(stderr, "Successfully loaded ImGui!\n");

    return true;
}

void ui_render(GLFWwindow* window) {
    if (!show_debug)
        return;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    igNewFrame();

    igBegin("Debug Menu", &show_debug, 0);
    {
        igText("Running at %.1f FPS (min: %.1f, max: %.1f)", fps, minFps, maxFps);

        if (igCheckbox("V-Sync", &enableVsync)) {
            glfwSwapInterval(enableVsync);
        }

        igSliderInt("X Rot", &rot[0], -1, 1, "%d", 0);
        igSliderInt("Y Rot", &rot[1], -1, 1, "%d", 0);
        igSliderInt("Z Rot", &rot[2], -1, 1, "%d", 0);

        igSliderFloat("Angle", &angle, -1.0F, 1.0F, "%.2f", 0);

        igColorEdit3("Clear Color", (float *)&clearColor, 0);

        if (igButton("Exit", (ImVec2){ 40, 20 }))
            glfwSetWindowShouldClose(window, 1);
    }
    igEnd();

    igRender();

    ImDrawData* drawData = igGetDrawData();

    if (!drawData) {
        fprintf(stderr, "Failed to obtain draw data!");
        return;
    }

    ImGui_ImplOpenGL3_RenderDrawData(drawData);
}

void ui_shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    igDestroyContext(NULL);
}

void update_fps_counter(float deltaTime) {
    fpsTimer += deltaTime;
    frames++;

    if (fpsTimer >= 1) {
        fps = frames / fpsTimer;

        if (fps < minFps)
            minFps = fps;

        if (fps > maxFps)
            maxFps = fps;

        frames = 0;
        fpsTimer = 0;
    }
}
