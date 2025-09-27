#include "ui.h"
#include <stdio.h>
#include <GLFW/glfw3.h>

bool show_debug = false, enableVsync = true, is_running = true;
float angle = 0.f, fps = 0.f, minFps = 0.f, maxFps = 0.f, fpsTimer = 0.f, fov = 45.f;
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

    float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor());

    ImGuiIO *io = igGetIO_Nil();
    io->IniFilename = NULL;

    ImGuiStyle *style = igGetStyle();

    style->FontScaleDpi = main_scale;

	style->WindowPadding = (ImVec2){15, 15};
	style->WindowRounding = 5.0f;
	style->FramePadding = (ImVec2){5, 5};
	style->FrameRounding = 4.0f;
	style->ItemSpacing = (ImVec2){12, 8};
	style->ItemInnerSpacing = (ImVec2){8, 6};
	style->IndentSpacing = 25.0f;
	style->ScrollbarSize = 15.0f;
	style->ScrollbarRounding = 9.0f;
	style->GrabMinSize = 5.0f;
	style->GrabRounding = 3.0f;
 
	style->Colors[ImGuiCol_Text] = (ImVec4){0.80f, 0.80f, 0.83f, 1.00f};
	style->Colors[ImGuiCol_TextDisabled] = (ImVec4){0.24f, 0.23f, 0.29f, 1.00f};
	style->Colors[ImGuiCol_WindowBg] = (ImVec4){0.06f, 0.05f, 0.07f, 1.00f};
	style->Colors[ImGuiCol_PopupBg] = (ImVec4){0.07f, 0.07f, 0.09f, 1.00f};
	style->Colors[ImGuiCol_Border] = (ImVec4){0.80f, 0.80f, 0.83f, 0.88f};
	style->Colors[ImGuiCol_BorderShadow] = (ImVec4){0.92f, 0.91f, 0.88f, 0.00f};
	style->Colors[ImGuiCol_FrameBg] = (ImVec4){0.10f, 0.09f, 0.12f, 1.00f};
	style->Colors[ImGuiCol_FrameBgHovered] = (ImVec4){0.24f, 0.23f, 0.29f, 1.00f};
	style->Colors[ImGuiCol_FrameBgActive] = (ImVec4){0.56f, 0.56f, 0.58f, 1.00f};
	style->Colors[ImGuiCol_TitleBg] = (ImVec4){0.10f, 0.09f, 0.12f, 1.00f};
	style->Colors[ImGuiCol_TitleBgCollapsed] = (ImVec4){1.00f, 0.98f, 0.95f, 0.75f};
	style->Colors[ImGuiCol_TitleBgActive] = (ImVec4){0.07f, 0.07f, 0.09f, 1.00f};
	style->Colors[ImGuiCol_MenuBarBg] = (ImVec4){0.10f, 0.09f, 0.12f, 1.00f};
	style->Colors[ImGuiCol_ScrollbarBg] = (ImVec4){0.10f, 0.09f, 0.12f, 1.00f};
	style->Colors[ImGuiCol_ScrollbarGrab] = (ImVec4){0.80f, 0.80f, 0.83f, 0.31f};
	style->Colors[ImGuiCol_ScrollbarGrabHovered] = (ImVec4){0.56f, 0.56f, 0.58f, 1.00f};
	style->Colors[ImGuiCol_ScrollbarGrabActive] = (ImVec4){0.06f, 0.05f, 0.07f, 1.00f};
	style->Colors[ImGuiCol_CheckMark] = (ImVec4){0.80f, 0.80f, 0.83f, 0.31f};
	style->Colors[ImGuiCol_SliderGrab] = (ImVec4){0.80f, 0.80f, 0.83f, 0.31f};
	style->Colors[ImGuiCol_SliderGrabActive] = (ImVec4){0.06f, 0.05f, 0.07f, 1.00f};
	style->Colors[ImGuiCol_Button] = (ImVec4){0.10f, 0.09f, 0.12f, 1.00f};
	style->Colors[ImGuiCol_ButtonHovered] = (ImVec4){0.24f, 0.23f, 0.29f, 1.00f};
	style->Colors[ImGuiCol_ButtonActive] = (ImVec4){0.56f, 0.56f, 0.58f, 1.00f};
	style->Colors[ImGuiCol_Header] = (ImVec4){0.10f, 0.09f, 0.12f, 1.00f};
	style->Colors[ImGuiCol_HeaderHovered] = (ImVec4){0.56f, 0.56f, 0.58f, 1.00f};
	style->Colors[ImGuiCol_HeaderActive] = (ImVec4){0.06f, 0.05f, 0.07f, 1.00f};
	style->Colors[ImGuiCol_ResizeGrip] = (ImVec4){0.00f, 0.00f, 0.00f, 0.00f};
	style->Colors[ImGuiCol_ResizeGripHovered] = (ImVec4){0.56f, 0.56f, 0.58f, 1.00f};
	style->Colors[ImGuiCol_ResizeGripActive] = (ImVec4){0.06f, 0.05f, 0.07f, 1.00f};
	style->Colors[ImGuiCol_Button] = (ImVec4){0.40f, 0.39f, 0.38f, 0.16f};
	style->Colors[ImGuiCol_ButtonHovered] = (ImVec4){0.40f, 0.39f, 0.38f, 0.39f};
	style->Colors[ImGuiCol_ButtonActive] = (ImVec4){0.40f, 0.39f, 0.38f, 1.00f};
	style->Colors[ImGuiCol_PlotLines] = (ImVec4){0.40f, 0.39f, 0.38f, 0.63f};
	style->Colors[ImGuiCol_PlotLinesHovered] = (ImVec4){0.25f, 1.00f, 0.00f, 1.00f};
	style->Colors[ImGuiCol_PlotHistogram] = (ImVec4){0.40f, 0.39f, 0.38f, 0.63f};
	style->Colors[ImGuiCol_PlotHistogramHovered] = (ImVec4){0.25f, 1.00f, 0.00f, 1.00f};
	style->Colors[ImGuiCol_TextSelectedBg] = (ImVec4){0.25f, 1.00f, 0.00f, 0.43f};
	style->Colors[ImGuiCol_ModalWindowDimBg] = (ImVec4){1.00f, 0.98f, 0.95f, 0.73f};

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

    igShowStyleEditor(igGetStyle());

    igBegin("Debug Menu", &show_debug, 0);
    {
        igText("Running at %.1f FPS (min: %.1f, max: %.1f)", fps, minFps, maxFps);
        igText("Frame took: %.1fms", 1000.f / fps);

        if (igCheckbox("V-Sync", &enableVsync)) {
            glfwSwapInterval(enableVsync);
        }

        igSliderInt("X Rot", &rot[0], -1, 1, "%d", 0);
        igSliderInt("Y Rot", &rot[1], -1, 1, "%d", 0);
        igSliderInt("Z Rot", &rot[2], -1, 1, "%d", 0);

        igSliderFloat("Angle", &angle, -1.0F, 1.0F, "%.2f", 0);
        igSliderFloat("FOV", &fov, 1.0F, 180.0F, "%.2f", 0);

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
