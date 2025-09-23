#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

char* read_file(const char* path);
int compile_shader(const char* source, GLenum type);