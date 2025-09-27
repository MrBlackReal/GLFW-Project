#include <stdio.h>

#include "engine/game/game.h"
#include "engine/ui/ui.h"
#include "engine/renderer/renderer.h"
#include "engine/input/input.h"
#include "engine/shaders/shaders.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

static Game game;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    (void)window;
    setup_view(&game, 45.0f, width, height);
}

int main() {
    if (!game_init(&game, WINDOW_WIDTH, WINDOW_HEIGHT))
        return -1;

    glfwSetKeyCallback(game.window, key_callback);
    glfwSetFramebufferSizeCallback(game.window, framebuffer_size_callback);

    if (!ui_init(game.window))
        return -1;

    char* vert_src = read_file("assets/shaders/vert.glsl");
    char* frag_src = read_file("assets/shaders/frag.glsl");

    int vert_shader = compile_shader(vert_src, GL_VERTEX_SHADER);
    int frag_shader = compile_shader(frag_src, GL_FRAGMENT_SHADER);
    int shader_program = link_program(vert_shader, frag_shader);
    
    free(vert_src);
    free(frag_src);
    
    {
        GLint i;
        GLint count;

        GLint size; // size of the variable
        GLenum type; // type of the variable (float, vec3 or mat4, etc)

        const GLsizei bufSize = 16; // maximum name length
        GLchar name[bufSize]; // variable name in GLSL
        GLsizei length; // name length

        glGetProgramiv(shader_program, GL_ACTIVE_ATTRIBUTES, &count);
        printf("Active Attributes: %d\n", count);

        for (i = 0; i < count; i++)
        {
            glGetActiveAttrib(shader_program, (GLuint)i, bufSize, &length, &size, &type, name);
            printf("Attribute #%d Type: %u Name: %s\n", i, type, name);
        }

        glGetProgramiv(shader_program, GL_ACTIVE_UNIFORMS, &count);
        printf("Active Uniforms: %d\n", count);

        for (i = 0; i < count; i++)
        {
            glGetActiveUniform(shader_program, (GLuint)i, bufSize, &length, &size, &type, name);

            printf("Uniform #%d Type: %u Name: %s\n", i, type, name);
        }
    }

    unsigned int cubeVAO = renderer_create_cube();

    float lastTime = glfwGetTime();

    while (!glfwWindowShouldClose(game.window)) {
        float time = glfwGetTime();
        float delta = time - lastTime;

        update_fps_counter(delta);

        glfwPollEvents();

        game_update(&game, delta);

        glEnable(GL_DEPTH_TEST);
        {
            game_render(&game, delta);
            
            float rotation[] = { (float)rot[0], (float)rot[1], (float)rot[2], angle };
            renderer_draw_cube(cubeVAO, shader_program, game.modelMatrix, game.viewMatrix, game.projectionMatrix, rotation);
        }
        glDisable(GL_DEPTH_TEST);

        ui_render(game.window);

        glfwSwapBuffers(game.window);

        glViewport(0, 0, game.width, game.height);
        glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        lastTime = time;
    }

    ui_shutdown();
    game_cleanup(&game);

    fprintf(stdout, "Cleaned up! Bye bye!\n");

    return 0;
}
