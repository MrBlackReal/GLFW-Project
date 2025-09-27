#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../../math/linmath.h"
#include <stdbool.h>

typedef struct {
    float x, y, z;
    char type;
} Voxel;

typedef struct {
    float* verts;
    GLuint* indices;
    size_t capacity, count;
} Mesh;

typedef struct {
    Mesh* mesh;
    GLuint vao, vbo;
} RenderMesh;

typedef struct {
    unsigned int width, height;
    GLFWwindow* window;
    mat4x4 modelMatrix, viewMatrix, projectionMatrix;
} Game;

void setup_view(Game* game, float fov, unsigned int width, unsigned int height);

bool game_init(Game* game, unsigned int width, unsigned int height);
void game_update(Game* game, float deltaTime);
void game_render(Game* game, float deltaTime);
void game_cleanup(Game* game);