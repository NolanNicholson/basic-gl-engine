#ifndef OPENGL_H
#define OPENGL_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <vector>

bool init_opengl();
bool load_shaders(GLuint &program);

void GLAPIENTRY
MessageCallback(
    GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam);

#endif //OPENGL_H
