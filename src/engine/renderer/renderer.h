#pragma once
#include <glad/glad.h>
#include "../../math/linmath.h"

unsigned int renderer_create_cube();
void renderer_draw_cube(unsigned int vao, int shader_program, mat4x4 model, mat4x4 view, mat4x4 projection, float rot[4]);