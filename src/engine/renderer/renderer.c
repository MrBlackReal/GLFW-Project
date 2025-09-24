#include "renderer.h"

static const float cube_vertices[] = {
    // Position           // Color (optional)
   -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,  // 0
    0.5f, -0.5f, -0.5f,    0.0f, 1.0f, 0.0f,  // 1
    0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 1.0f,  // 2
   -0.5f,  0.5f, -0.5f,    1.0f, 1.0f, 0.0f,  // 3
   -0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 1.0f,  // 4
    0.5f, -0.5f,  0.5f,    0.0f, 1.0f, 1.0f,  // 5
    0.5f,  0.5f,  0.5f,    1.0f, 1.0f, 1.0f,  // 6
   -0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 0.0f   // 7
};

static const unsigned int cube_indices[] = {
    // Back face
    0, 1, 2,
    2, 3, 0,
    // Front face
    4, 5, 6,
    6, 7, 4,
    // Left face
    4, 0, 3,
    3, 7, 4,
    // Right face
    1, 5, 6,
    6, 2, 1,
    // Bottom face
    4, 5, 1,
    1, 0, 4,
    // Top face
    3, 2, 6,
    6, 7, 3
};

unsigned int renderer_create_cube() {
    GLuint vao, vbo, ebo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    return vao;
}

void renderer_draw_cube(unsigned int vao, int shader_program, mat4x4 model, mat4x4 view, mat4x4 projection, float rot[4]) {
    glEnable(GL_DEPTH_TEST);
    glUseProgram(shader_program);

    int modelLoc = glGetUniformLocation(shader_program, "model");
    int viewLoc  = glGetUniformLocation(shader_program, "view");
    int projLoc  = glGetUniformLocation(shader_program, "projection");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (const GLfloat*)model);
    glUniformMatrix4fv(viewLoc,  1, GL_FALSE, (const GLfloat*)view);
    glUniformMatrix4fv(projLoc,  1, GL_FALSE, (const GLfloat*)projection);

    mat4x4_rotate(model, model, rot[0], rot[1], rot[2], rot[3]);

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glDisable(GL_DEPTH_TEST);
}
