#include "game.h"
#include <stdio.h>
#include <glad/glad.h>

int game_init(Game* game, unsigned int width, unsigned int height) {
    game->width = width;
    game->height = height;

    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return 0;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    game->window = glfwCreateWindow(width, height, "GLFW Window", NULL, NULL);
    if (!game->window) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return 0;
    }

    glfwMakeContextCurrent(game->window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Failed to initialize GLAD\n");
        return 0;
    }

    mat4x4_identity(game->modelMatrix);
    mat4x4_identity(game->viewMatrix);
    mat4x4_identity(game->projectionMatrix);

    mat4x4_translate(game->viewMatrix, 0.f, 0.f, -2.5f);

    float aspect_ratio = (float)width / (float)height;
    mat4x4_perspective(game->projectionMatrix, 45.0f * (M_PI / 180.0f), aspect_ratio, 0.1f, 100.0f);

    return 1;
}

void game_update(Game* game, float deltaTime) {
    (void)game;
    (void)deltaTime;
}

void game_cleanup(Game* game) {
    glfwDestroyWindow(game->window);
    glfwTerminate();
}