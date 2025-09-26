#include "game.h"
#include "../ui/ui.h"
#include <stdio.h>
#include <glad/glad.h>

void setup_view(Game* game, float fov, unsigned int width, unsigned int height) {
    game->width = width;
    game->height = height;

    mat4x4_perspective(game->projectionMatrix, fov * (M_PI / 180.0f), (float)(width / height), 0.1f, 100.0f);
}

bool game_init(Game* game, unsigned int width, unsigned int height) {
    game->width = width;
    game->height = height;

    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return false;
    }

    fprintf(stdout, "Initialized GLFW!\n");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    game->window = glfwCreateWindow(width, height, "GLFW Window", NULL, NULL);

    if (!game->window) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return false;
    }

    fprintf(stdout, "Created GLFW window! (w: %d, h: %d)\n", width, height);

    glfwMakeContextCurrent(game->window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        fprintf(stderr, "Failed to initialize GLAD\n");
        return false;
    }

    fprintf(stdout, "Loaded GLAD!\n");

    mat4x4_identity(game->modelMatrix);
    mat4x4_identity(game->viewMatrix);
    mat4x4_identity(game->projectionMatrix);

    mat4x4_translate(game->viewMatrix, 0.f, 0.f, -3.f);

    setup_view(game, 45.0f, width, height);

    return true;
}

void game_update(Game* game, float deltaTime) {
    (void)game;
    (void)deltaTime;
}

void game_render(Game* game, float deltaTime) {
    (void)game;
    (void)deltaTime;
}

void game_cleanup(Game* game) {
    glfwDestroyWindow(game->window);
    glfwTerminate();
}