#include <stdio.h>

#include "engine/game/game.h"
#include "engine/ui/ui.h"
#include "engine/renderer/renderer.h"
#include "engine/input/input.h"
#include "shaders/shaders.h"

int main() {
    Game game;

    if (!game_init(&game, 800, 600))
        return -1;

    glfwSetKeyCallback(game.window, key_callback);

    if (!ui_init(game.window))
        return -1;

    char* vert_src = read_file("assets/shaders/vert.glsl");
    char* frag_src = read_file("assets/shaders/frag.glsl");
    int vert_shader = compile_shader(vert_src, GL_VERTEX_SHADER);
    int frag_shader = compile_shader(frag_src, GL_FRAGMENT_SHADER);
    int shader_program = link_program(vert_shader, frag_shader);
    
    free(vert_src);
    free(frag_src);

    unsigned int cubeVAO = renderer_create_cube();

    float lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(game.window)) {
        float time = glfwGetTime();
        float delta = time - lastTime;
        lastTime = time;

        game_update(&game, delta);

        glViewport(0, 0, game.width, game.height);
        glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderer_draw_cube(cubeVAO, shader_program, game.modelMatrix, game.viewMatrix, game.projectionMatrix, rot);

        ui_render();

        glfwSwapBuffers(game.window);
        glfwPollEvents();
    }

    ui_shutdown();
    game_cleanup(&game);

    return 0;
}
