#ifndef OPENGL_H
#define OPENGL_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <vector>

bool init_opengl();
bool load_shaders(GLuint &program);
void render(GLuint program);

#endif //OPENGL_H
