#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "linmath.h"
#include "shaders/shaders.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define FOV 45.f

static const float vertices[] = {
    -0.5f, -0.5f, 0.0f, 1.0, 0.0, 0.0,   // red color for this vertex
	 0.5f, -0.5f, 0.0f, 0.0, 1.0, 0.0,   // green color
	 0.0f,  0.5f, 0.0f, 0.0, 0.0, 1.0    // blue color for our top vertex
};

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

struct Game {
    unsigned int width, height;
    GLFWwindow* window;
    mat4x4 modelMatrix, viewMatrix, projectionMatrix;
};

int main() {

    struct Game game;

    game.width = WINDOW_WIDTH;
    game.height = WINDOW_HEIGHT;

    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);

    game.window = glfwCreateWindow(game.width, game.height, "GLFW Window", NULL, NULL);
    
    if (!game.window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(game.window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Failed to initialize GLAD\n");
        return -1;
    }

    char* vert_src = read_file("assets/shaders/vert.glsl");
    char* frag_src = read_file("assets/shaders/frag.glsl");

    int vert_shader = compile_shader(vert_src, GL_VERTEX_SHADER);
    int frag_shader = compile_shader(frag_src, GL_FRAGMENT_SHADER);

    int shader_program = glCreateProgram();
    glAttachShader(shader_program, vert_shader);
    glAttachShader(shader_program, frag_shader);
    glLinkProgram(shader_program);

    free(vert_src);
    free(frag_src);

    float aspect_ratio = WINDOW_WIDTH / WINDOW_HEIGHT;

    mat4x4 modelMatrix, viewMatrix, projectionMatrix;

    mat4x4_identity(modelMatrix);
    mat4x4_identity(viewMatrix);
    mat4x4_identity(projectionMatrix);

    mat4x4_translate(viewMatrix, 0.f, 0.f, -3.f);
    
    mat4x4_perspective(projectionMatrix, FOV * (M_PI / 100.0f), aspect_ratio, 0.1f, 100.0f);

    int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    int modelLoc = glGetUniformLocation(shader_program, "model");
    int viewLoc = glGetUniformLocation(shader_program, "view");
    int projLoc = glGetUniformLocation(shader_program, "projection");

    while (!glfwWindowShouldClose(game.window)) {
        float time = glfwGetTime();
        
        mat4x4_rotate_X(modelMatrix, modelMatrix, 0.01f);
        mat4x4_rotate_Y(modelMatrix, modelMatrix, 0.01f);
        mat4x4_rotate_Z(modelMatrix, modelMatrix, 0.01f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        glUseProgram(shader_program);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (const GLfloat*) modelMatrix);
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (const GLfloat*) viewMatrix);
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, (const GLfloat*) projectionMatrix);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glDisable(GL_DEPTH_TEST);

        glfwSwapBuffers(game.window);
        glfwPollEvents();
    }

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteProgram(shader_program);
    glDeleteShader(vert_shader);
    glDeleteShader(frag_shader);

    glfwDestroyWindow(game.window);
    glfwTerminate();

    return 0;
}
