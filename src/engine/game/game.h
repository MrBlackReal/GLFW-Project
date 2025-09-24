#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../../math/linmath.h"
#include <stdbool.h>

typedef struct {
    unsigned int width, height;
    GLFWwindow* window;
    mat4x4 modelMatrix, viewMatrix, projectionMatrix;
} Game;

int  game_init(Game* game, unsigned int width, unsigned int height);
void game_update(Game* game, float deltaTime);
void game_render(Game* game);
void game_cleanup(Game* game);